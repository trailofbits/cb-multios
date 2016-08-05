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

#include "conv.h"
#include "stdio.h"
#include "string.h"

#include "games.h"

static int
read_board(char *board)
{
    int i;

    if (fread(board, 10 * 9, stdin) != 10 * 9)
        return EXIT_FAILURE;

    for (i = 0; i < 10 * 9; i++) {
        if ((i + 1) % 10 == 0) {
            if (board[i] != '\n')
                return EXIT_FAILURE;
        } else {
            if (strchr("123456789 ", board[i]) == NULL)
                return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

static char
get_square(char *board, int x, int y)
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
get_super_square(char *board, char *set, int x, int y)
{
    int i, j;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            set[j * 3 + i] = get_square(board, x + i, y + j);
}

static int
count_duplicates(char *set)
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
validate_board(char *board)
{
    int ret;
    char set[9];
    int i, j;

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++)
            set[j] = get_square(board, j, i);

        if ((ret = count_duplicates(set)) != 0)
            return -ret + 1;
    }

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++)
            set[j] = get_square(board, i, j);

        if ((ret = count_duplicates(set)) != 0)
            return -ret;
    }

    for (i = 0; i < 9; i += 3) {
        for (j = 0; j < 9; j += 3) {
            get_super_square(board, set, i, j);

            if ((ret = count_duplicates(set)) != 0)
                return -ret;
        }
    }

    return EXIT_SUCCESS;
}

static int solve_board(char *board, char *square)
{
    char num, *next_square;

    if ((next_square = strchr(square, ' ')) == NULL)
        return EXIT_SUCCESS;

    for (num = '1'; num <= '9'; num++) {
        *next_square = num;
        if (validate_board(board) == EXIT_SUCCESS) {
            if (solve_board(board, next_square + 1) == EXIT_SUCCESS)
                return EXIT_SUCCESS;
        }
    }

    *next_square = ' ';
    return EXIT_FAILURE;
}

int
do_sudoku()
{
    // 9 rows of 9 chars + newlines for each row
    char board[10 * 9];

    printf("Let me help you cheat at sudoku, enter your board n00b:\n");

    if (read_board(board) != EXIT_SUCCESS) {
        printf("Invalid board\n");
        return EXIT_SUCCESS;
    }

    game_state.games.sudoku.fitness = validate_board(board);
    if (solve_board(board, board) != EXIT_SUCCESS)
        printf("Nice try\n");
    else
        printf("Solved!\n%s\n", board);

    return EXIT_SUCCESS;
}

