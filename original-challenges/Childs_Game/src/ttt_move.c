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
#include <stdio.h>
#include "board.h"

static const unsigned int *secret = (const unsigned int *)0x4347C000;
static int idx = 0;

static int find_minmax(board_t *board, int depth, int player, int *best_posy, int *best_posx)
{
    if (player == COMPUTER && board->num_moves == 0) {
        unsigned int corner = secret[idx++] % 4;
        idx %= 1024;
        switch(corner) {
        case 0:
            *best_posy = 0;
            *best_posx = 0;
            break;
        case 1:
            *best_posy = 0;
            *best_posx = 2;
            break;
        case 2:
            *best_posy = 2;
            *best_posx = 0;
            break;
        case 3:
            *best_posy = 2;
            *best_posx = 2;
            break;
        }
        return 10;
    }

    int move_status = 0;
    int score = 0;
    int temp_posy = 0, temp_posx = 0;
    int best_score = player == COMPUTER ? -1000 : 1000;

    int i = 0, j;
    for (i = 0; i < BOARD_HEIGHT; i++) {
        for (j = 0; j < BOARD_WIDTH; j++) {
            if (board->ttt_board[i][j] != BLANK)
                continue;

            move_status = do_move(board, i, j, player);
            if (move_status == WINNER_HUMAN) {
                score = depth - 10;
            } else if (move_status == WINNER_COMP) {
                score = 10 - depth;
            } else if (move_status == TIE) {
                score =  0;
            } else if (move_status == GAME_IN_PROGRESS) {
                score = find_minmax(board, depth+1, player * -1, best_posy, best_posx);
            } else {
                return -10000;
            }

            if (undo_move(board, i, j) != SUCCESS) {
                return -10000;
            }

            if (player == COMPUTER) {
                if (best_score < score) {
                    best_score = score;
                    temp_posy = i;
                    temp_posx = j;
                }
            } else if (player == HUMAN) {
                if (best_score > score) {
                    best_score = score;
                    temp_posy = i;
                    temp_posx = j;
                }
            }
        }
    }

    *best_posy = temp_posy;
    *best_posx = temp_posx;
    return best_score;
}

int computer_move(board_t *board)
{
    int best_posx = -1;
    int best_posy = -1;

    find_minmax(board, 0, COMPUTER, &best_posy, &best_posx);
    return do_move(board, best_posy, best_posx, COMPUTER);
}

int player_move(board_t *board)
{
    int max_input = 256;
    int posx = 0;
    int posy = 0;
    char *input = malloc(max_input);
    printf("Enter move [y,x]: ");
    if (freaduntil(input, max_input, ',', stdin) == -1)
        goto error;
    posy = strtol(input, NULL, 10);
    if (freaduntil(input, max_input, '\n', stdin) == -1)
        goto error;
    posx = strtol(input, NULL, 10);

    free(input);
    return do_move(board, posy, posx, HUMAN);
error:
    free(input);
    return BAD_MOVE;
}
