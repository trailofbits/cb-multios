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
#include "game.h"
#include "math_lib.h"


char current_max_road_len = 0;

int getNextPieceNum()
{
	if (game_stack.top_element == -1)
		return 0;

	return (game_stack.stack[game_stack.top_element].piece_num + 1);
}

// returns a piece with road info in it
int create_random_piece(Piece *piece)
{
	// check if we've hit our max limit first
	if (game_stack.top_element >= MAX_PIECES)
		return 33;

	// top piece must be placed before another piece is placed
	if (isTopPiecePlaced() == FAIL && game_stack.top_element > 0)
		return 22;

	piece->piece_num = getNextPieceNum();

	if (game_stack.top_element == -1)
	{
		// this is the first piece, it will only have one road off of it
		int side = random_in_range(1,3);
		for (int i = 0; i < 4; i++)
		{
			if (i == side)
				piece->sides[i].target = ROAD;
			else
				piece->sides[i].target = NO_ROAD;
		}
	}
	else
	{
		int side1 = random_in_range(0,3);
		int side2 = side1;

		// get another, different side for a road
		while (side2 == side1)
			side2 = random_in_range(0,3);

		for (int i = 0; i < 4; i++)
		{
			if (i == side1 || i == side2)
				piece->sides[i].target = ROAD;
			else
				piece->sides[i].target = NO_ROAD;
		}
	}

	if (game_stack.top_element < 0)
		current_max_road_len++;

	push_piece(piece);
	return SUCCESS;
}

// discards the piece on top of the stack if it hasn't been placed already
int discard_piece()
{
	// stack is empty, no discarding allowed
	if (game_stack.top_element < 0)
		return FAIL;

	// if top piece has been placed, return false (can't discard this piece)
	if (isTopPiecePlaced() == SUCCESS)
		return FAIL;

	game_stack.top_element--;
	return SUCCESS;
}

// connect pieceA/sideA to pieceB,sideB
int connect_pieces(Piece *pieceA, char sideA, Piece *pieceB, char sideB)
{
	// only allow road to road connections
	if (pieceA->sides[sideA].target != ROAD ||
		pieceB->sides[sideB].target != ROAD)
	{
		// can't connect pieces on non-road sides
		printf("a: @d, b: @d...", pieceA->sides[sideA].target, pieceB->sides[sideB].target);
		
		for (int i = 0; i < game_stack.top_element; i++)
		{
			char str[10];
			piece_to_pkt(&game_stack.stack[i], str);
			printf("piece @d: @s", i, str);
		}

		return FAIL;
	}
	
	// connect pieceA/sideA to pieceB,sideB
	pieceA->sides[sideA].target = pieceB->piece_num;
	pieceA->sides[sideA].side = sideB;

	pieceB->sides[sideB].target = pieceA->piece_num;
	pieceB->sides[sideB].side = sideA;

	current_max_road_len++;
	return SUCCESS;
}

// Save the given piece's values to the stack
// this is used when a new piece is created 
void push_piece(Piece *piece)
{
	if (game_stack.top_element >= MAX_PIECES)
		return;

	game_stack.top_element++;
	game_stack.stack[game_stack.top_element].piece_num = piece->piece_num;
	game_stack.stack[game_stack.top_element].sides[0].target = piece->sides[0].target;
	game_stack.stack[game_stack.top_element].sides[0].side = piece->sides[0].side;
	game_stack.stack[game_stack.top_element].sides[1].target = piece->sides[1].target;
	game_stack.stack[game_stack.top_element].sides[1].side = piece->sides[1].side;
	game_stack.stack[game_stack.top_element].sides[2].target = piece->sides[2].target;
	game_stack.stack[game_stack.top_element].sides[2].side = piece->sides[2].side;
	game_stack.stack[game_stack.top_element].sides[3].target = piece->sides[3].target;
	game_stack.stack[game_stack.top_element].sides[3].side = piece->sides[3].side;
}

int get_max_road_len()
{
	return current_max_road_len;
}

// check the stack to see if the top piece has been placed
// return TRUE if placed
// return FALSE if not placed
int isTopPiecePlaced()
{
	if (game_stack.top_element < 0)
		return SUCCESS; // no pieces yet

	// return TRUE if the top piece on the game_stack is placed
	// placed: one of the four sides has a valid link
	for (int i = 0; i < 4; i++)
	{
		if (game_stack.stack[game_stack.top_element].sides[i].target != NO_ROAD &&
			game_stack.stack[game_stack.top_element].sides[i].target != ROAD)
		{
			return SUCCESS;
		}
	}
	return FAIL;
}

// turn the piece's data into a format we can send in the packet
// piece is the incoming packet data
// str is an allocated string at least 9 chars long
void piece_to_pkt(Piece *piece, char* str)
{
	str[0] = piece->piece_num + '0';
	if (piece->sides[0].target == ROAD)
	{
		str[1] = '0';
		str[2] = 'y';
	}
	else
	{
		str[1] = '0';
		str[2] = 'n';
	}
	if (piece->sides[1].target == ROAD)
	{
		str[3] = '1';
		str[4] = 'y';
	}
	else
	{
		str[3] = '1';
		str[4] = 'n';
	}
	if (piece->sides[2].target == ROAD)
	{
		str[5] = '2';
		str[6] = 'y';
	}
	else
	{
		str[5] = '2';
		str[6] = 'n';
	}
	if (piece->sides[3].target == ROAD)
	{
		str[7] = '3';
		str[8] = 'y';
	}
	else
	{
		str[7] = '3';
		str[8] = 'n';
	}
}

// look up piece by number and return a pointer to the struct
int get_piece(char pce_num)
{
	// iterate through each piece and find one that matches pce_num
	for (int i = 0; i <= game_stack.top_element; i++)
	{
		if (game_stack.stack[i].piece_num == pce_num)
		{
			return i;
		}
	}
	return -1;
}

