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
#ifndef TGRAPHICSITEM_H
#define TGRAPHICSITEM_H

#include <iostream>
#include <typeinfo>

#include "SDL.h"

#include "tapplication.h"
#include "tfont.h"
#include "tcolor.h"

class TApplication;
class TGraphicsItem
{
public:
    virtual void draw() = 0;
    SDL_Surface * surface;
    int zIndex;
    int itemType;

    Sint16 xpos;
    Sint16 ypos;

    Uint16 width;
    Uint16 height;

    SDL_Rect rect;
    TFont *font;

    std::string name;
};

class TGraphicsText: public TGraphicsItem
{
public:
    TGraphicsText() { }
    void draw();

    std::string str;
};

class TGraphicsRectangle: public TGraphicsItem
{
public:
    TGraphicsRectangle() { }
    void draw();

    TColor color;
};

class TGraphicsImage: public TGraphicsItem
{
public:
    TGraphicsImage(int x, int y, std::string name) { }
    void draw();
};

class TGraphicsTicker: public TGraphicsItem
{
public:
    TGraphicsTicker(int x, int y, std::string name) { }
    void draw();
};

#endif // TGRAPHICSITEM_H
