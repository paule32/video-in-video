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
#ifndef TTIMER_H
#define TTIMER_H

#include "SDL.h"
#include "SDL_timer.h"

class TTimer
{
public:
    TTimer(int p_interval = 1000)
    {
        interval = p_interval;
        accumulator = 0;
        total = 0;
        cur_time = last_time = SDL_GetTicks();
    }
    int ready()
    {
        return accumulator > interval;
    }
    int check()
    {
        if( ready() )
        {
            accumulator -= interval;
            return 1;
        }
        return 0;
    }
    void update()
    {
        int delta;
        cur_time = SDL_GetTicks();
        delta = cur_time - last_time;
        total += delta;
        accumulator += delta;
        last_time = cur_time;
    }
private:
    int last_time;
    int cur_time;
    int accumulator;
    int total;
    int interval;
};

#endif // TTIMER_H
