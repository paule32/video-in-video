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
#ifndef TAPPLICATION_H
#define TAPPLICATION_H

#include <SDL/SDL_video.h>
#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <SDL/SDL_opengl.h>

#include <vlc/vlc.h>

#include "tfont.h"
#include "tcolor.h"
#include "tpainter.h"
#include "tgraphicsitem.h"

class TPainter;
class TApplication //: public QMainWindow
{
    //Q_OBJECT
public:
    explicit TApplication();
    ~TApplication();

    int run(TPainter &paint);
    bool GetComponentUnderMouse(SDL_Event &event);

    SDL_Surface * screen;
    TPainter * paint;

    libvlc_instance_t * inst;
    libvlc_media_t *m;
    libvlc_media_player_t *mp;

    libvlc_instance_t * cam1_inst;
    libvlc_instance_t * cam2_inst;
    libvlc_instance_t * cam3_inst;
    libvlc_instance_t * cam4_inst;

    libvlc_media_t *cam1_m;
    libvlc_media_t *cam2_m;
    libvlc_media_t *cam3_m;
    libvlc_media_t *cam4_m;

    libvlc_media_player_t *cam1_mp;
    libvlc_media_player_t *cam2_mp;
    libvlc_media_player_t *cam3_mp;
    libvlc_media_player_t *cam4_mp;
};

extern SDL_Surface *appScreen;

#endif // TAPPLICATION_H
