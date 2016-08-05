/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#ifndef BOARD_H_
#define BOARD_H_

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3

enum {BLANK=0, COMPUTER=64, HUMAN=-64};
enum {BAD_MOVE=0, SUCCESS=1, GAME_IN_PROGRESS=2, GAME_OVER=4, WINNER_HUMAN=8, WINNER_COMP=16, TIE=32, ERROR=-1};

typedef struct board
{
    char ttt_board[BOARD_HEIGHT][BOARD_WIDTH];
    int num_moves;
    int winner;
} board_t;

board_t *create_board();
void clear_board(board_t *board);
int check_winning_board(board_t *board);
int do_move(board_t *board, int posy, int posx, int player);
void print_board(board_t *board);
int undo_move(board_t *board, int posy, int posx);

#endif
