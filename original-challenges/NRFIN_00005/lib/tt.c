/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <libcgc.h>
#include "libc.h"
#include "tt.h"

char PLAYERS[2] = {'P', 'Q'};

// fill a clean game board char array with current row values
// board must be a char buff[(17 * 8) + 1] = char buf[137]
// 136 chars and 1 '\0'
void make_board(tt_data * data, char * board) {

	// row buffers are 18 chars: 16 + \n + \0
	char *TOP_NUMBERS = "     0   1   2  \n";  // top numbers
	char *ROW_DIVIDER = "   +---+---+---+\n";  // row divider
	char *top_row =     " 0 | ~o | ~o | ~o |\n";  // top row
					 // "   +---+---+---+\n"
	char *middle_row =  " 1 | ~o | ~o | ~o |\n";  // middle row
					 // "   +---+---+---+\n"
	char *bottom_row =  " 2 | ~o | ~o | ~o |\n";  // bottom row
					 // "   +---+---+---+\n"

	strncpy( board + 17 * 0, TOP_NUMBERS, 17);
	strncpy( board + 17 * 1, ROW_DIVIDER, 17);
	snprintf(board + 17 * 2, 18, top_row, 
			 data->top[0], 
			 data->top[1], 
			 data->top[2]);
	strncpy( board + 17 * 3, ROW_DIVIDER, 17);
	snprintf(board + 17 * 4, 18, middle_row, 
			 data->middle[0], 
			 data->middle[1], 
			 data->middle[2]);
	strncpy( board + 17 * 5, ROW_DIVIDER, 17);
	snprintf(board + 17 * 6, 18, bottom_row, 
			 data->bottom[0], 
			 data->bottom[1], 
			 data->bottom[2]);
	strncpy( board + 17 * 7, ROW_DIVIDER, 17);
	board[17 * 8] = '\0';
}

// initialize game data
void init_game_data(tt_data * data) {
	memset(data->top, EMPTY, 3);
	memset(data->middle, EMPTY, 3);
	memset(data->bottom, EMPTY, 3);
	data->moves = 0;
	data->winner = EMPTY;
}

void set_player_chars(tt_data * data, char player_char) {
	if(player_char == PLAYERS[0]) {
		data->player_char = PLAYERS[0];
		data->comp_char = PLAYERS[1];
	} else {
		data->player_char = PLAYERS[1];
		data->comp_char = PLAYERS[0];
	}
}

void reset_scores(tt_scores * scores) {
	scores->player = 0;
	scores->computer = 0;
}

// test to determine if coordinates are within the game board
// if yes, return 1
// if no, return 0
int has_valid_coords(tt_move_coords * move) {
	// don't have to check if row/col >= 0, because they are uint's
	return (move->row <= 2 && move->col <= 2);
}

// test to determine if coordinates are unoccupied
// if yes, return 1
// if no, return 0
int coords_unoccupied(tt_data * data, tt_move_coords * move) {
	return (game_board_get_at_coord(data, move) == EMPTY);
}

// set letter of current player at coords in game board
void game_board_set_at_coord(tt_data * data, tt_move_coords * move) {
	int row = move->row;
	int col = move->col;
	switch(row) {
	case 0: 
		data->top[col] = PLAYERS[data->moves % 2];
		break;
	case 1: 
		data->middle[col] = PLAYERS[data->moves % 2];
		break;
	case 2:
		data->bottom[col] = PLAYERS[data->moves % 2];
		break;
	}
}

// get letter at coords in game board
char game_board_get_at_coord(tt_data * data, tt_move_coords * move) {
	int row = move->row;
	int col = move->col;
	char ch;
	switch(row) {
	case 0: 
		ch = data->top[col];
		break;
	case 1: 
		ch = data->middle[col];
		break;
	case 2:
	default: 
		ch = data->bottom[col];
	}
	return ch;
}

// determine if coordinates are a valid move
// - coordinate is inside the board
// - coordinate is an available play
// if yes, return 1
// if no, return 0
int is_valid_move(tt_data * data, tt_move_coords * move) {
	return (has_valid_coords(move) && coords_unoccupied(data, move));
}

// attempt to update board with players move
// return 0 on success, 1 on failure.
int update_board(tt_data * data, tt_move_coords * move) {

	int result = 0;

	if(is_valid_move(data, move)) {
		game_board_set_at_coord(data, move);
	} else {
		result = 1;
	}

	return result;
}

// check to see if a player has won.
// return 1, if yes. return 0 if no.
int have_winner(tt_data * data) {

	int result = 1;

	if (data->moves < 3) { return 0; }

	// top row
	if (data->top[0] == data->top[1] && 
		data->top[1] == data->top[2] && 
		data->top[0] != EMPTY) {
		data->winner = data->top[0];
	}
	// middle row
	else if (data->middle[0] == data->middle[1] && 
		data->middle[1] == data->middle[2] && 
		data->middle[0] != EMPTY) {
		data->winner = data->middle[0];
	}
	// bottom row
	else if (data->bottom[0] == data->bottom[1] && 
		data->bottom[1] == data->bottom[2] && 
		data->bottom[0] != EMPTY) {
		data->winner = data->bottom[0];
	}
	// first col
	else if (data->top[0] == data->middle[0] && 
		data->middle[0] == data->bottom[0] && 
		data->bottom[0] != EMPTY) {
		data->winner = data->top[0];
	}
	// second col
	else if (data->top[1] == data->middle[1] && 
		data->middle[1] == data->bottom[1] && 
		data->bottom[1] != EMPTY) {
		data->winner = data->top[1];
	}
	// third col
	else if (data->top[2] == data->middle[2] && 
		data->middle[2] == data->bottom[2] && 
		data->bottom[2] != EMPTY) {
		data->winner = data->top[2];
	}
	// diag top left - bottom right
	else if (data->top[0] == data->middle[1] && 
		data->middle[1] == data->bottom[2] && 
		data->bottom[2] != EMPTY) {
		data->winner = data->top[0];
	}
	// diag bottom left - top right
	else if (data->top[2] == data->middle[1] && 
		data->middle[1] == data->bottom[0] && 
		data->bottom[0] != EMPTY) {
		data->winner = data->top[2];
	}
	// no winner
	else {
		result = 0;
	}

	return result;
}

// Determine if there are any more moves remaining.
// if yes, return 1. if no, return 0.
// There are 9 moves in the game.
int have_moves_remaining(tt_data * data) {
	int result = 0;
	if (data->moves < 9) {
		result = 1;
	}
	return result;
}

// Determine if player won
// if yes, return 1
// if no, return 0
char is_player_winner(tt_data * data) {
	return (data->winner == data->player_char);
}

// Determine if it is the client/player's turn
// if yes, return 1
// if no, return 0
int is_players_turn(tt_data * data) {
	return (data->player_char == PLAYERS[data->moves % 2]);
}

// Change to next player
void move_complete(tt_data * data) {
	data->moves++;
}

// select a randomly generated valid move for the computer
void computer_move(tt_data * data, tt_move_coords * move) {
	tt_move_coords tmp_move;
	tmp_move.row = prng_get_next() % 3;
	tmp_move.col = prng_get_next() % 3;
	while(!is_valid_move(data, &tmp_move)) {
		tmp_move.row = prng_get_next() % 3;
		tmp_move.col = prng_get_next() % 3;
	}

	move->row = tmp_move.row;
	move->col = tmp_move.col;
}

// should be called when there are no more moves or a player has won.
void update_score(tt_game * game) {

	if(game->data->winner == game->data->player_char) {
		game->scores->player++;
	}
	// if computer wins or
	// if there is a draw, victory goes to the computer
	else {
		game->scores->computer++;
	}
}
