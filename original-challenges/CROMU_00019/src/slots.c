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

#include <libcgc.h>
#include "stdlib.h"
#include "slots.h"
#include "casino.h"
#include "prng.h"


// Print the slot machine state
void print_board(int board_size, unsigned char board[][board_size])
{
	for (int y=0; y<board_size; y++)
	{
		for(int x=0; x<board_size; x++)
		{
			printf("@c ", board[x][y]);
		}
		printf("\n");
	}
}

// Runs the slot machine game
void slots(player_info *player)
{
	player_info placeholder;
	if (player == 0)
	{
		player = &placeholder;
	}
	
	// Accept board size
	char input;
	printf("Enter number of rows (2 to 5):");
	receive_fixed_input(&input, '\n', sizeof(input));
	if ((input < '2') || (input > '5'))
	{
		return;
	}
	int board_size = input - '0';

	while (input != 'q')
	{	
		if (player->wallet >= 2)
		{
			player->wallet -= 2;
		}
		player->slots_score += 1;
		unsigned char board[board_size][board_size];
		bzero(board, sizeof(board));

		// Adjust number of characters used to control odds of winning
		char max_char = '/';
		switch(board_size)
		{
			case 3:
				max_char = '!' + 6;
				break;
			case 4:
				max_char = '!' + 4;
				break;
			case 5:
				max_char = '!' + 2;
				break;
		}

		// Generate board
		for (int x=0; x < board_size; x++)
		{
			for(int y=0; y < board_size; y++)
			{
				board[x][y] = random_in_range('!', max_char);
			}	
		}
		print_board(board_size, board);

		// Check for a win
		// Column check
		int x, y;
		for (x = 0; x < board_size; x++)
		{
			for (y = 1; y < board_size; y++)
			{
				if (board[x][y] != board[x][0])
				{
					break;
				}
			}
			if (y == board_size)
			{
				printf("Column match: @d!\n", x);
				if (player)
				{
					player->wallet += payouts[SLOTS_COLUMN_MATCH];
				}
			}
		}

		// Row check
		for (y = 0; y < board_size; y++)
		{
			for (x = 1; x < board_size; x++)
			{
				if (board[x][y] != board[0][y])
				{
					break;
				}
			}
			if (x == board_size)
			{
				printf("Row match: @d!\n", y);
				if (player)
				{
					player->wallet += payouts[SLOTS_ROW_MATCH];
				}
			}
		}
		printf("Enter q to quit, any other key to play again:");
		receive_fixed_input(&input, '\n', sizeof(input));
	}
}