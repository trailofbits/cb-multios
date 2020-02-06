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

#include "cgc_conv.h"
#include "cgc_stdio.h"
#include "cgc_string.h"

#include "cgc_games.h"

static int
read_board(char *board)
{
    int i;

    if (cgc_fread(board, 10 * 9, cgc_stdin) != 10 * 9)
        return EXIT_FAILURE;

    for (i = 0; i < 10 * 9; i++) {
        if ((i + 1) % 10 == 0) {
            if (board[i] != '\n')
                return EXIT_FAILURE;
        } else {
            if (cgc_strchr("123456789 ", board[i]) == NULL)
                return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

static char
cgc_get_square(char *board, int x, int y)
{
    if (x < 0 || y < 0 || x >= 9 || y >= 9)
        return '\0';

    return board[y * 10 + x];
}

static void
set_square(char *board, char num, int x, int y)
{
    if (x < 0 || y < 0 || x >= 9 || y >= 9)
        return;

    if (num < '1' || num > '9')
        return;

    board[y * 10 + x] = num;
}

static void
cgc_get_super_square(char *board, char *set, int x, int y)
{
    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            set[j * 3 + i] = cgc_get_square(board, x + i, y + j);
}

static int
cgc_count_duplicates(char *set)
{
    int ret = 0;
    int i, j, count;

    for (i = '1'; i <= '9'; i++) {
        count = 0;
        for (j = 0; j < 9; j++)
            if (set[j] == i)
                count++;

        if (count > 1)
            ret += count;
    }

    return ret;
}

static int
cgc_validate_board(char *board)
{
    int ret;
    char set[9];
    int i, j;

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++)
            set[j] = cgc_get_square(board, j, i);

        if ((ret = cgc_count_duplicates(set)) != 0)
            return -ret + 1;
    }

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++)
            set[j] = cgc_get_square(board, i, j);

        if ((ret = cgc_count_duplicates(set)) != 0)
            return -ret;
    }

    for (i = 0; i < 9; i += 3) {
        for (j = 0; j < 9; j += 3) {
            cgc_get_super_square(board, set, i, j);

            if ((ret = cgc_count_duplicates(set)) != 0)
                return -ret;
        }
    }

    return EXIT_SUCCESS;
}

static int cgc_solve_board(char *board, char *square)
{
    char num, *next_square;

    if ((next_square = cgc_strchr(square, ' ')) == NULL)
        return EXIT_SUCCESS;

    for (num = '1'; num <= '9'; num++) {
        *next_square = num;
        if (cgc_validate_board(board) == EXIT_SUCCESS) {
            if (cgc_solve_board(board, next_square + 1) == EXIT_SUCCESS)
                return EXIT_SUCCESS;
        }
    }

    *next_square = ' ';
    return EXIT_FAILURE;
}

int
cgc_do_sudoku()
{
    // 9 rows of 9 chars + newlines for each row
    char board[10 * 9];

    cgc_printf("Let me help you cheat at sudoku, enter your board n00b:\n");

    if (read_board(board) != EXIT_SUCCESS) {
        cgc_printf("Invalid board\n");
        return EXIT_SUCCESS;
    }

    cgc_game_state.games.sudoku.fitness = cgc_validate_board(board);
    if (cgc_solve_board(board, board) != EXIT_SUCCESS)
        cgc_printf("Nice try\n");
    else
        cgc_printf("Solved!\n%s\n", board);

    return EXIT_SUCCESS;
}

