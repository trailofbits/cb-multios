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
#include "moves.h"

// current player
char CURR_PLAYER[6];

int main(void) {
	char srcx, srcy, dstx, dsty;
	// board
	char board[X_MAX][Y_MAX];

	InitBoard(board);
	strcpy(CURR_PLAYER, "WHITE");
	PrintBoard(board);

	while (1) {
		if (!AcceptMove(board, &srcx, &srcy, &dstx, &dsty)) {
			puts("good game");
			return(0);
		}	

		if (!IsValidMove(board, srcx, srcy, dstx, dsty)) {
			puts("NO");
			continue;
		}

		MakeMove(board, srcx, srcy, dstx, dsty);

		if (!strcmp(CURR_PLAYER, "WHITE")) {
			strcpy(CURR_PLAYER, "BLACK");
		} else {
			strcpy(CURR_PLAYER, "WHITE");
		}

		puts("OK");
	}

	return(0);
}
