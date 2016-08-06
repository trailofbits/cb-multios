/*

Author: James Nuttall (james@cromulence.co)

Copyright (c) 2014 Cromulence LLC

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

// dimensions of the chess board
#define WIDTH 8
#define HEIGHT 8

// Defines a single location on the 8x8 board
typedef struct Location
{
	int x;
	int y;
} Location;

// Defines a move: source and destination locations
typedef struct Move
{
	Location src;
	Location dst;
} Move;

void initboard(void);
int checklegal(Move);
void swap(Move);
int parseUserInput(Move*);

/* CHESS PIECES */

// white
#define PAWN_WHITE 'a'
#define KNIGHT_WHITE 'b'
#define BISHOP_WHITE 'c'
#define ROOK_WHITE 'd'
#define KING_WHITE 'e'
#define QUEEN_WHITE 'f'

// black
#define PAWN_BLACK 'g'
#define KNIGHT_BLACK 'h'
#define BISHOP_BLACK 'i'
#define ROOK_BLACK 'j'
#define KING_BLACK 'k'
#define QUEEN_BLACK 'l'

#define EMPTY '.'
#define BLACK_PIECE 0
#define WHITE_PIECE 1

#define BLACK_TEAM	0
#define WHITE_TEAM  1

#define PROMPT_WHITE "WHITE: "
#define PROMPT_BLACK "BLACK: "
#define WARNING "Not a legal move format\n"
#define OK "OK\n"
#define NO "NO\n"

// parseUserInput return values
#define INPUT_ERROR -1
#define INVALID_INPUT 0
#define GOOD_INPUT 1
#define DISPLAY_BOARD 2
#define END_GAME 3

#define COLLISION 0
#define NO_COLLISION 1

