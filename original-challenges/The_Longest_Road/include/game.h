/*

Author: James Nuttall (james@cromulence.co)

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
#ifndef __GAME_H__
#define __GAME_H__

#define MAX_PIECES 128

// each piece has a pointer for each of its sides
// if pointer is null, no road on that side
// if pointer is not null but doesn't point to another piede yet, it will be set to ROAD
// if pointer is not null and not equal to ROAD, it points to another piece, 
//   with the Road_Link's side set to the side of the piece we're connecting to
#define ROAD -3
#define NO_ROAD -4

// describes the piece and side where a road connects to
typedef struct 
{
	char target; // number of target piece this connects to
	char side;  // 0-3, which side on the target piece this road connects with
} Road_Link;


// describes a game piece
// each side can be null (no road)
// or can be a pointer to another game piece
typedef struct
{
	// describes each side and what it points to
	char piece_num; // just keeps track of each piece
	Road_Link sides[4];
} Piece;

typedef struct
{
	Piece stack[MAX_PIECES];
	int top_element; // how many pieces in this stack (-1 because zero counting)?
} Game_Stack;

Game_Stack game_stack;

// stores
extern char current_max_road_len;

extern int goal_len; // length the user is trying to reach

void push_piece(Piece *piece);
void pop_piece(Piece *piece);
int connect_pieces(Piece *pieceA, char sideA, Piece *pieceB, char sideB);
int get_max_road_len();
int isTopPiecePlaced();
void piece_to_pkt(Piece *piece, char* str);
int discard_piece();
int create_random_piece(Piece *piece);
int get_piece(char pce);

#endif