// -----------------------------------------------------------------------------
// Copyright (c) 2019 kallup.jens@web.de
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
// THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
// -----------------------------------------------------------------------------
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include <SDL/SDL.h>
#include <SDL/SDL_mutex.h>

#include <vlc/vlc.h>
#include <vlc/libvlc.h>


#include "tapplication.h"
#include "tfont.h"
#include "tpainter.h"
#include "tgraphicsitem.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 800;

#define VIDEOWIDTH 630
#define VIDEOHEIGHT 350

const int CAM1_WIDTH  = 140;
const int CAM2_WIDTH  = 240;
const int CAM3_WIDTH  = 240;
const int CAM4_WIDTH  = 240;

const int CAM1_HEIGHT = 140;

const char* WINDOW_TITLE = "Video-in-Video  v1.0 (c) 2019 Jens Kallup";

SDL_Surface *appScreen;

struct ctx {
    SDL_Surface *surf;
    SDL_mutex *mutex;
};

struct ctx ctx;

struct ctx cam1_ctx;
struct ctx cam2_ctx;
struct ctx cam3_ctx;
struct ctx cam4_ctx;

#include "cam0_src.h"
#include "cam1_src.h"

SDL_bool videoinit = SDL_FALSE;

void OnQuit(void) {
    if (videoinit) {
        SDL_VideoQuit();
    }
    SDL_Quit();
}


TApplication::TApplication() //QWidget *parent) : QMainWindow(parent)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    int options = SDL_ANYFORMAT | SDL_HWSURFACE | SDL_DOUBLEBUF;

    appScreen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, options);
    SDL_WM_SetCaption( WINDOW_TITLE, 0 );

    // main picture
    inst = libvlc_new(0, NULL);
    m    = libvlc_media_new_location(inst,"screen://");
    mp   = libvlc_media_player_new_from_media(m);
           libvlc_media_release(m);
    libvlc_video_set_callbacks(mp, lock, unlock, display, &ctx);
    libvlc_video_set_format   (mp, "RV16", VIDEOWIDTH, VIDEOHEIGHT, VIDEOWIDTH*2);
    libvlc_media_player_play  (mp);

    // cam-1
    cam1_inst = libvlc_new(0,NULL);
    cam1_m    = libvlc_media_new_location(cam1_inst,"v4l2:///dev/video0");
    cam1_mp   = libvlc_media_player_new_from_media(cam1_m);
                libvlc_media_release(cam1_m);
    libvlc_video_set_callbacks(cam1_mp, cam1_lock, cam1_unlock, cam1_display, &cam1_ctx);
    libvlc_video_set_format   (cam1_mp, "RV16", CAM1_WIDTH,CAM1_HEIGHT, CAM1_WIDTH*2);
    libvlc_media_player_play  (cam1_mp);
}

TApplication::~TApplication()
{
    // cam-1
    libvlc_media_player_stop   (cam1_mp);
    libvlc_media_player_release(cam1_mp);
    libvlc_release(cam1_inst);

    libvlc_media_player_stop   (mp);
    libvlc_media_player_release(mp);
    libvlc_release(inst);

    TTF_Quit();
    SDL_Quit();
}

int TApplication::run(TPainter &paint)
{
    SDL_Event event;
    this->paint = &paint;

    SDL_Surface *empty;
    SDL_Rect      rect;

    SDL_Rect cam1_rect;
    SDL_Rect cam2_rect;

    int done = 0, action = 0, pause = 0, n = 0;

    empty     = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOWIDTH, VIDEOHEIGHT, 32, 0, 0, 0, 0);
    ctx.surf  = SDL_CreateRGBSurface(SDL_SWSURFACE, VIDEOWIDTH, VIDEOHEIGHT, 16, 0x001f, 0x07e0, 0xf800, 0);
    ctx.mutex = SDL_CreateMutex();

    rect.x = 190;
    rect.y = 160;
    rect.w = 820;
    rect.h = 350;

    // cam-1
    cam1_ctx.surf  = SDL_CreateRGBSurface(SDL_SWSURFACE, CAM1_WIDTH, CAM1_HEIGHT, 16, 0x001f, 0x07e0, 0xf800, 0);
    cam1_ctx.mutex = SDL_CreateMutex();

    cam1_rect.x =  90;
    cam1_rect.y = 160;
    cam1_rect.w = CAM1_WIDTH;
    cam1_rect.h = CAM1_HEIGHT;

    /*
    // cam-2
    cam2_ctx.surf  = SDL_CreateRGBSurface(SDL_SWSURFACE, CAM2_WIDTH, CAM2_HEIGHT, 16, 0x001f, 0x07e0, 0xf800, 0);
    cam2_ctx.mutex = SDL_CreateMutex();

    cam2_rect.x =  90;
    cam2_rect.y = 160;
    cam2_rect.w = CAM1_WIDTH;
    cam2_rect.h = CAM1_HEIGHT; */


    bool mousebutton_left = false;
    int quit = 0;
    while (!quit)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    mousebutton_left = true;
                }
            }
            if (event.type == SDL_MOUSEBUTTONUP) {
                mousebutton_left = false;
            }

            if (event.type == SDL_MOUSEMOTION) {
                if (mousebutton_left == true) {
                    bool result = GetComponentUnderMouse(event);
                    if (!result) {
                        quit = 1;
                    }
                }
            }
        }

        SDL_FillRect(appScreen, NULL, SDL_MapRGB(appScreen->format,0x47,0x47,0x47));

        paint.paint();

        // main-picture
        SDL_LockMutex(ctx.mutex);
        SDL_BlitSurface(ctx.surf, NULL, appScreen, &rect);
        SDL_UnlockMutex(ctx.mutex);

        // cam-1
        SDL_LockMutex(cam1_ctx.mutex);
        SDL_BlitSurface(cam1_ctx.surf, NULL, appScreen, &cam1_rect);
        SDL_UnlockMutex(cam1_ctx.mutex);

        SDL_Flip(appScreen);
        SDL_BlitSurface(empty, NULL, appScreen, &rect);
    }
    return 0;
}

bool TApplication::GetComponentUnderMouse(SDL_Event &event)
{
    for(auto it = std::begin(paint->objects); it != std::end(paint->objects); ++it) {
        try {
            TGraphicsText *item = dynamic_cast<TGraphicsText*>(*it);
            if (item)
            if (item->name == "Label1") {
                item->xpos  = event.motion.x;
                item->ypos  = event.motion.y;
                item->draw();
            }
        }   catch (...) { printf("ERRRRR\n"); }
    }

    return true;
}
