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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_board.h"
#include "cgc_moves.h"

// current player
char cgc_CURR_PLAYER[6];

int main(int cgc_argc, char *cgc_argv[]) {
	char srcx, srcy, dstx, dsty;
	// board
	char board[X_MAX][Y_MAX];

	cgc_InitBoard(board);
	cgc_strcpy(cgc_CURR_PLAYER, "WHITE");
	cgc_PrintBoard(board);

	while (1) {
		if (!cgc_AcceptMove(board, &srcx, &srcy, &dstx, &dsty)) {
			cgc_puts("good game");
			return(0);
		}

		if (!cgc_IsValidMove(board, srcx, srcy, dstx, dsty)) {
			cgc_puts("NO");
			continue;
		}

		cgc_MakeMove(board, srcx, srcy, dstx, dsty);

		if (!cgc_strcmp(cgc_CURR_PLAYER, "WHITE")) {
			cgc_strcpy(cgc_CURR_PLAYER, "BLACK");
		} else {
			cgc_strcpy(cgc_CURR_PLAYER, "WHITE");
		}

		cgc_puts("OK");
	}

	return(0);
}
