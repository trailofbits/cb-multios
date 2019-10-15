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

#ifndef TT_BOARD
#define TT_BOARD

#define EMPTY ' '

typedef struct tt_move_coords {
	unsigned char row;
	unsigned char col;
} tt_move_coords;

typedef struct tt_scores {
	unsigned char player;
	unsigned char computer;
} tt_scores;

typedef struct tt_data {
	char top[3];
	char middle[3];
	char bottom[3];
	char player_char;
	char comp_char;
	unsigned char moves;
	char winner;
} tt_data;

typedef struct tt_game {
	tt_data * data;
	tt_scores * scores;
} tt_game;

void cgc_make_board(tt_data * data, char * board);
void cgc_init_game_data(tt_data * data);
void cgc_set_player_chars(tt_data * data, char player_char);
void cgc_reset_scores(tt_scores * scores);
int cgc_has_valid_coords(tt_move_coords * move);
int cgc_coords_unoccupied(tt_data * data, tt_move_coords * move);
void cgc_game_board_set_at_coord(tt_data * data, tt_move_coords * move);
char cgc_game_board_get_at_coord(tt_data * data, tt_move_coords * move);
int cgc_is_valid_move(tt_data * data, tt_move_coords * move);
int cgc_update_board(tt_data * data, tt_move_coords * move);
int cgc_have_winner(tt_data * data);
int cgc_have_moves_remaining(tt_data * data);
char cgc_is_player_winner(tt_data * data);
int cgc_is_players_turn(tt_data * data);
void cgc_move_complete(tt_data * data);
void cgc_computer_move(tt_data * data, tt_move_coords * move);
void cgc_update_score(tt_game * game);
#endif