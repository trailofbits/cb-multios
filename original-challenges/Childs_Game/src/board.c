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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "board.h"

board_t *create_board()
{
    board_t *board = malloc(sizeof(board_t));
    clear_board(board);
    return board;
}

void clear_board(board_t *board)
{
    memset(board->ttt_board, BLANK, BOARD_WIDTH * BOARD_HEIGHT * sizeof(char));
    board->num_moves = 0;
    board->winner = 0;
}

int check_winning_board(board_t *board)
{
    int temp_pos;
    if ((temp_pos = board->ttt_board[0][0]) != BLANK) {
        if (board->ttt_board[0][1] == temp_pos && board->ttt_board[0][2] == temp_pos)
            goto winner;
        if (board->ttt_board[1][1] == temp_pos && board->ttt_board[2][2] == temp_pos)
            goto winner;
        if (board->ttt_board[1][0] == temp_pos && board->ttt_board[2][0] == temp_pos)
            goto winner;
    }

    if ((temp_pos = board->ttt_board[0][1]) != BLANK) {
        if (board->ttt_board[1][1] == temp_pos && board->ttt_board[2][1] == temp_pos)
            goto winner;
    }

    if ((temp_pos = board->ttt_board[0][2]) != BLANK) {
        if (board->ttt_board[1][2] == temp_pos && board->ttt_board[2][2] == temp_pos)
            goto winner;
        if (board->ttt_board[1][1] == temp_pos && board->ttt_board[2][0] == temp_pos)
            goto winner;
    }

    if ((temp_pos = board->ttt_board[1][0]) != BLANK) {
        if (board->ttt_board[1][1] == temp_pos && board->ttt_board[1][2] == temp_pos)
            goto winner;
    }

    if ((temp_pos = board->ttt_board[2][0]) != BLANK) {
        if (board->ttt_board[2][1] == temp_pos && board->ttt_board[2][2] == temp_pos)
            goto winner;
    }

//non_winner:
    if (board->num_moves == 9) {
        board->winner = TIE;
        return board->winner;
    } else {
        return GAME_IN_PROGRESS;
    }

winner:
    board->winner = temp_pos == HUMAN ? WINNER_HUMAN : WINNER_COMP;
    return board->winner;
}

int do_move(board_t *board, int posy, int posx, int player)
{
    if (board->num_moves >= 9)
        return GAME_OVER;

    if (posx < 0 || posy < 0 || posx > 2 || posy > 2)
        return BAD_MOVE;

    if (board->ttt_board[posy][posx] != BLANK)
        return BAD_MOVE;

    board->ttt_board[posy][posx] = player;
    board->num_moves++;

    return check_winning_board(board);
}

int undo_move(board_t *board, int posy, int posx)
{
    if (posx < 0 || posy < 0 || posx >3 || posy > 3)
        return BAD_MOVE;

    if (board->ttt_board[posy][posx] == BLANK)
        return BAD_MOVE;

    board->ttt_board[posy][posx] = BLANK;
    board->num_moves--;
    board->winner = 0;

    return SUCCESS;
}

void print_board(board_t *board)
{
    int i, j;
    char *c;
    for (i = 0; i < BOARD_HEIGHT; i++) {
        printf("|");
        for (j = 0; j < BOARD_WIDTH; j++) {
            switch(board->ttt_board[i][j]) {
            case HUMAN:
                c = "H";
                break;
            case COMPUTER:
                c = "C";
                break;
            case BLANK:
                c = "-";
                break;
            default:
                c = "%";
            }
            printf("%s|", c);
        }
        printf("\n");
    }
}
