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
#include <iostream>
#include <string>

#include "SDL.h"
#include "tapplication.h"
#include "tgraphicsitem.h"
#include "ttimer.h"

void TGraphicsText::draw()
{
    surface = TTF_RenderText_Shaded(font->font, str.c_str(),
    font->fgColor.sdl_color,
    font->bgColor.sdl_color);

    SDL_Rect textLocation = { xpos, ypos, 0, 0 };
    SDL_BlitSurface(surface, NULL, appScreen, &textLocation);
}

void TGraphicsRectangle::draw()
{
    SDL_FillRect(appScreen, &rect,
    SDL_MapRGB(appScreen->format,
        color.sdl_color.r,
        color.sdl_color.g,
        color.sdl_color.b));
}

void TGraphicsImage::draw()
{
    rect = { xpos, ypos, width, height };
    SDL_BlitSurface(surface, NULL, appScreen, &rect);
}

void TGraphicsTicker::draw()
{
    rect = {0,100,1024,26};
    SDL_FillRect(appScreen, &rect,
    SDL_MapRGB(appScreen->format,
        font->bgColor.sdl_color.r,
        font->bgColor.sdl_color.g,
        font->bgColor.sdl_color.b));

    surface = TTF_RenderText_Shaded(font->font, name.c_str(),
    font->fgColor.sdl_color,
    font->bgColor.sdl_color);

    if (xpos < 10)
    xpos = 1024; else
    xpos = xpos - 4;
    rect = {xpos,ypos,220,26};
    SDL_Rect textLocation = rect;
    SDL_BlitSurface(surface, NULL, appScreen, &textLocation);
}
