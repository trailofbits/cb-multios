/*

Author: Debbie Nuttall <debbie@cromulence.co>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef POKER_H
#define POKER_H

#include "casino.h"

static const int poker_value[SIZE_OF_DECK + 1] = {
    0, // Placeholder for non-card
    2, 3, 4, 5, 6, 7, 8, 9, 10,  	// 2D - 10D
    11, 12, 13, 14,                 // JD - AD
    2, 3, 4, 5, 6, 7, 8, 9, 10,  	// 2S - 10S
    11, 12, 13, 14,                 // JS - AS
    2, 3, 4, 5, 6, 7, 8, 9, 10,  	// 2H - 10H
    11, 12, 13, 14,                 // JH - AH
    2, 3, 4, 5, 6, 7, 8, 9, 10,  	// 2C - 10C
    11, 12, 13, 14,                 // JC - AC
};

void poker(player_info *player);

#endif // POKER_H