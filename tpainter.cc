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
#include "tpainter.h"
#include "tfont.h"
#include "tgraphicsitem.h"
#include "ttimer.h"

TTimer ticker_timer(2000);

TPainter::TPainter()
{
    objects.clear();
}

void TPainter::paint()
{
    for(auto it = std::begin(objects); it != std::end(objects); ++it)
    {
        {
            TGraphicsText *item = dynamic_cast<TGraphicsText*>(*it);
            if (item) {
                item->draw();
                continue;
            }
        }   {
            TGraphicsRectangle *item = dynamic_cast<TGraphicsRectangle*>(*it);
            if (item) {
                item->draw();
                continue;
            }
        }   {
            TGraphicsImage *item = dynamic_cast<TGraphicsImage*>(*it);
            if (item) {
                item->draw();
                continue;
            }
        }   {
            TGraphicsTicker *item = dynamic_cast<TGraphicsTicker*>(*it);
            if (item) {
                //if (ticker_timer.check())
                {
                    SDL_Delay(30);
                    item->draw();
                }
                continue;
            }
        }
    }
}

void TPainter::drawText(TFont *font, int xpos, int ypos, std::string str)
{
    TGraphicsText *text = new TGraphicsText;
    text->xpos = xpos;
    text->ypos = ypos;
    text->str  = str;
    text->font = font;
    text->name = "Label1";

    text->font->fgColor = font->fgColor;
    text->font->bgColor = font->bgColor;

    objects.push_back(text);
}

void TPainter::drawRectangle(Sint16 xpos, Sint16 ypos, Uint16 width, Uint16 height, TColor color)
{
    TGraphicsRectangle *rect = new TGraphicsRectangle;
    rect->rect  = { xpos, ypos, width, height };
    rect->color = color;

    objects.push_back(rect);
}

void TPainter::drawImage(int xpos, int ypos, std::string name)
{
    TGraphicsImage *img = new TGraphicsImage(xpos,ypos,name);
    img->surface = SDL_LoadBMP(name.c_str());

    img->xpos = xpos;
    img->ypos = ypos;

    objects.push_back(img);
}

void TPainter::drawTicker(TFont *font, int xpos, int ypos, std::string name)
{
    TGraphicsTicker *ticker = new TGraphicsTicker(xpos,ypos,name);
    ticker->font = font;

    ticker->xpos = 1024;
    ticker->ypos = ypos;

    ticker->name = name;

    objects.push_back(ticker);
}
