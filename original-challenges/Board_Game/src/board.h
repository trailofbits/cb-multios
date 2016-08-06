/*

Author: Joe Rogers <joe@cromulence.co>

Copyright (c) 2014-2015 Cromulence LLC

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
#ifndef BOARD_H
#define BOARD_H

// board size
#define X_MAX (8)
#define Y_MAX (8)

// White pieces
#define W_ROOK ('d')
#define W_KNIGHT ('b')
#define W_BISHOP ('c')
#define W_QUEEN ('f')
#define W_KING ('e')
#define W_PAWN ('a')
#define W_PIECES ("dbcfea")

// Black pieces
#define B_ROOK ('j')
#define B_KNIGHT ('h')
#define B_BISHOP ('i')
#define B_QUEEN ('l')
#define B_KING ('k')
#define B_PAWN ('g')
#define B_PIECES ("jhilkg")

// empty location
#define EMPTY ('\0')

void PrintBoard(char b[X_MAX][Y_MAX]);
void InitBoard(char b[X_MAX][Y_MAX]);

#endif
