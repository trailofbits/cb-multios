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
#include <libcgc.h>
#include "stdlib.h"
#include "board.h"

void PrintBoard(char b[X_MAX][Y_MAX]) {
	char x, y;
	char buf[Y_MAX+1];
	size_t txcount;

	for (y = Y_MAX-1; y >= 0; y--) {
		for (x = 0; x < X_MAX; x++) {
			if (b[x][y] == '\0') {
				buf[x] = '.';
			} else {
				buf[x] = b[x][y];
			}
		}
		buf[x] = '\0';
		printf("@s\n", buf);
	}
}

void InitBoard(char b[X_MAX][Y_MAX]) {
	char x, y;

	// init white side
	b[0][0] = b[7][0] = W_ROOK;
	b[1][0] = b[6][0] = W_KNIGHT;
	b[2][0] = b[5][0] = W_BISHOP;
	b[3][0] = W_QUEEN;
	b[4][0] = W_KING;
	y = 1;
	for (x = 0; x < X_MAX; x++) {
		b[x][y] = W_PAWN;
	}

	// init field between
	for (y = 2; y < 6; y++) {
		for (x = 0; x < Y_MAX; x++) {
			b[x][y] = EMPTY;
		}
	}

	// init black side
	y = 6;
	for (x = 0; x < X_MAX; x++) {
		b[x][y] = B_PAWN;
	}
	b[0][7] = b[7][7] = B_ROOK;
	b[1][7] = b[6][7] = B_KNIGHT;
	b[2][7] = b[5][7] = B_BISHOP;
	b[3][7] = B_QUEEN;
	b[4][7] = B_KING;

}
