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
#ifndef TPAINTER_H
#define TPAINTER_H

#include <iostream>
#include <vector>

#include "tapplication.h"
#include "tfont.h"

class TApplication;
class TGraphicsItem;

class TPainter
{
public:
    TPainter();
    void drawImage(int xpos, int ypos, std::string name);
    void drawText(TFont *font, int xpos, int ypos, std::string str);
    void drawTicker(TFont *font, int xpos, int ypos, std::string name);
    void drawRectangle(Sint16 xpos, Sint16 ypos, Uint16 width, Uint16 height, TColor color);

    void paint();

    std::vector<TGraphicsItem*> objects;
};

#endif // TPAINTER_H
