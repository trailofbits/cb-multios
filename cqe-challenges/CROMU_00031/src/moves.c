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

// current player
extern char CURR_PLAYER[];

// calculate absolute value
int abs(int v) {
	if (v < 0)
		return(v*-1);
	else
		return(v);
}

int IsDiagClear(char b[X_MAX][Y_MAX], char srcx, char srcy, char dstx, char dsty) {
	char x, y;

	// make sure there are no obstructions
	if (srcx < dstx) {
		if (srcy < dsty) {
			for (x = srcx+1, y=srcy+1; x < dstx && y < dsty; x++,y++) {	
				if (b[x][y] != EMPTY) {
					return(0);
				}
			}
		} else {
			for (x = srcx+1, y=srcy-1; x < dstx && y > dsty; x++,y--) {	
				if (b[x][y] != EMPTY) {
					return(0);
				}
			}
		}
	} else {
		if (srcy < dsty) {
			for (x = srcx-1, y=srcy+1; x > dstx && y < dsty; x--,y++) {	
				if (b[x][y] != EMPTY) {
					return(0);
				}
			}
		} else {
			for (x = srcx-1, y=srcy-1; x > dstx && y > dsty; x--,y--) {	
				if (b[x][y] != EMPTY) {
					return(0);
				}
			}
		}
	}
	return(1);
}

int IsLateralClear(char b[X_MAX][Y_MAX], char srcx, char srcy, char dstx, char dsty) {
	char x, y;

	if (srcx < dstx) {
		for (x = srcx+1; x < dstx; x++) {
			if (b[x][srcy] != EMPTY) {
				return(0);
			}
		}
	} else if (srcx > dstx) {
		for (x = dstx+1; x < srcx; x++) {
			if (b[x][srcy] != EMPTY) {
				return(0);
			}
		}
	} else if (srcy < dsty) {
		for (y = srcy+1; y < dsty; y++) {
			if (b[srcx][y] != EMPTY) {
				return(0);
			}
		}
	} else if (srcy > dsty) {
		for (y = dsty+1; y < srcy; y++) {
			if (b[srcx][y] != EMPTY) {
				return(0);
			}
		}
	}

	return(1);
}

// see if the piece is contained in PIECES
int IsMemberPiece(char *PIECES, char piece) {
	char *t;

	t = strchr(PIECES, piece);
	if (t == NULL) {
		return(0);
	} else {
		if (t == PIECES+strlen(PIECES)) {
			return(0);
		} else {
			return(1);
		}
	}

}

int IsValidMove(char b[X_MAX][Y_MAX], char srcx, char srcy, char dstx, char dsty) {
	char x, y;

	if (srcx == dstx && srcy == dsty) {
		return(0);
	}

	// make sure the src coordinate is the current player's piece
	if (!strcmp(CURR_PLAYER, "WHITE") && IsMemberPiece(W_PIECES, b[srcx][srcy]) == 0) {
		return(0);
	} else if (!strcmp(CURR_PLAYER, "BLACK") && IsMemberPiece(B_PIECES, b[srcx][srcy]) == 0) {
		return(0);
	}

	// make sure the dest coordinate isn't the current player's piece
	if (!strcmp(CURR_PLAYER, "WHITE") && IsMemberPiece(W_PIECES, b[dstx][dsty])) {
		return(0);
	} else if (!strcmp(CURR_PLAYER, "BLACK") && IsMemberPiece(B_PIECES, b[dstx][dsty])) {
		return(0);
	}

	switch (b[srcx][srcy]) {
		case W_ROOK:
		case B_ROOK: 
			// make sure the move is in a straight line
			if (srcx != dstx && srcy != dsty)
				return(0);

			// make sure there are no obstructions
			return(IsLateralClear(b,srcx,srcy,dstx,dsty));

		case W_KNIGHT:
		case B_KNIGHT: 
			// make sure it's a valid move
			if (srcx+2 == dstx && srcy+1 == dsty) {
				return(1);
			} else if (srcx-2 == dstx && srcy+1 == dsty) {
				return(1);
			} else if (srcx+2 == dstx && srcy-1 == dsty) {
				return(1);
			} else if (srcx-2 == dstx && srcy-1 == dsty) {
				return(1);
			} else if (srcx+1 == dstx && srcy+2 == dsty) {
				return(1);
			} else if (srcx+1 == dstx && srcy-2 == dsty) {
				return(1);
			} else if (srcx-1 == dstx && srcy+2 == dsty) {
				return(1);
			} else if (srcx-1 == dstx && srcy-2 == dsty) {
				return(1);
			} else {
				return(0);
			}

		case W_BISHOP:
		case B_BISHOP:
			// make sure dst is on a diagonal
			if (abs(dstx-srcx) != abs(dsty-srcy))
				return(0);

			return(IsDiagClear(b,srcx,srcy,dstx,dsty));

		case W_QUEEN:
		case B_QUEEN:
			// see if it's a straight line move
			if (srcx == dstx || srcy == dsty) {
				// make sure there are no obstructions
				return(IsLateralClear(b,srcx,srcy,dstx,dsty));
			}

			// see if it's a diagonal move
			if (abs(dstx-srcx) == abs(dsty-srcy)) {
				return(IsDiagClear(b,srcx,srcy,dstx,dsty));
			}

			return(0);

		case W_KING:
		case B_KING:
			if (abs(srcx-dstx) > 1 || abs(srcy-dsty) > 1)
				return(0);

			return(1);

		case W_PAWN:
			if (srcx == dstx && srcy+1 == dsty)
				return(1);

			return(0);

		case B_PAWN:
			// handle single step forward
			if (srcx == dstx && srcy-1 == dsty)
				return(1);

			return(0);

		case EMPTY:
			return(0);
	}
	
	return(0);
}

int AcceptMove(char b[X_MAX][Y_MAX], char *srcx, char *srcy, char *dstx, char *dsty) {
	struct {
		char input[15];
		char allowed_chars[9];
	} s = {"", "01234567"};
	char *coord1, *coord2;
	int i;
	size_t rxcount;

	while (1) {
		printf("@s: ", CURR_PLAYER);
		bzero(s.input, 15);
#ifdef PATCHED
		if ((rxcount = receive_until(s.input, '\n', 14)) == 0) {
#else
		if ((rxcount = receive_until(s.input, '\n', 16)) == 0) {
#endif
			if (rxcount == 0) {
				_terminate(1);
			}
		}

		if (s.input[strlen(s.input)-1] == '\n') {
			s.input[strlen(s.input)-1] = '\0';
		}

		// see if the player just wants to display the board
		if (!strcmp("9", s.input)) {
			PrintBoard(b);
			continue;
		}

		// see if the player wants to exit
		if (!strcmp("666", s.input)) {
			return(0);
		}	

		if (strlen(s.input) > 7) {
			puts("incorrect input");
			puts("Not a legal move format");
			continue;
		}

		// try to parse move 
		coord1 = coord2 = NULL;
		for (i = 0; i < strlen(s.input); i++) {
			if (s.input[i] == ' ') {
				s.input[i] = '\0';
				coord2 = s.input+i+1;
				coord1 = s.input;
			}
		}
		if (coord1 == NULL) {
			puts("incorrect input");
			puts("Not a legal move format");
			continue;
		}
	
		// parse each coordinate
		if (!strchr(s.allowed_chars, coord1[0]) || 
		    (coord1[1] != ',') ||
		    !strchr(s.allowed_chars, coord1[2]) ||
		    strlen(coord1) != 3) {
			puts("incorrect input");
			puts("Not a legal move format");
			continue;
		}
		*srcx = coord1[0] - '0';
		*srcy = coord1[2] - '0';
		if (!strchr(s.allowed_chars, coord2[0]) || 
		    (coord2[1] != ',') ||
		    !strchr(s.allowed_chars, coord2[2]) ||
		    strlen(coord2) != 3) {
			puts("incorrect input");
			puts("Not a legal move format");
			continue;
		}
		*dstx = coord2[0] - '0';
		*dsty = coord2[2] - '0';

		break;
	}

	return(1);
}

void MakeMove(char b[X_MAX][Y_MAX], char srcx, char srcy, char dstx, char dsty) {
	char t;

	// if dst is occupied, swap
	if (b[dstx][dsty] != EMPTY) {
		t = b[dstx][dsty];
		b[dstx][dsty] = b[srcx][srcy];
		b[srcx][srcy] = t;
		return;
	}

	b[dstx][dsty] = b[srcx][srcy];
	b[srcx][srcy] = EMPTY;

	return;
}
