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

    if (fread(board, 8 * 9, stdin) != 8 * 9)
        return EXIT_FAILURE;

    for (i = 0; i < 8 * 9; i++) {
        if ((i + 1) % 9 == 0) {
            if (board[i] != '\n')
                return EXIT_FAILURE;
        } else {
            if (strchr("prnbqk ", board[i]) == NULL)
                return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

static char
get_piece(char *board, int x, int y)
{
    if (x < 0 || y < 0 || x >= 8 || y >= 8)
        return '\0';

    return board[y * 9 + x];
}

static void
get_coords(char *board, char *piece, int *x, int *y)
{
    *x = (piece - board) % 9;
    *y = (piece - board) / 9;
}

static void
set_move(int x0, int y0, int x1, int y1)
{
    game_state.games.chess.move[0] = x0 + 'a';
    game_state.games.chess.move[1] = y0 + '1';
    game_state.games.chess.move[2] = x1 + 'a';
    game_state.games.chess.move[3] = y1 + '1';
}

/* We don't bother modeling all the nuances of the game's rules in these functions */
static void
move_pawn(char *board, int x, int y)
{
    if (isupper(get_piece(board, x - 1, y)))
        set_move(x, y, x - 1, y);
    else if (isupper(get_piece(board, x + 1, y)))
        set_move(x, y, x + 1, y);
    else if (get_piece(board, x, y + 2) == ' ')
        set_move(x, y, x, y + 2);
    else if (get_piece(board, x, y + 1) == ' ')
        set_move(x, y, x, y + 1);
}

static void
move_rook(char *board, int x, int y)
{
    if (isupper(get_piece(board, x, y + 1)) || get_piece(board, x, y + 1) == ' ')
        set_move(x, y, x, y + 1);
    else if (isupper(get_piece(board, x - 1, y)) || get_piece(board, x - 1, y) == ' ')
        set_move(x, y, x - 1, y);
    else if (isupper(get_piece(board, x + 1, y)) || get_piece(board, x + 1, y) == ' ')
        set_move(x, y, x + 1, y);
    else if (isupper(get_piece(board, x, y - 1)) || get_piece(board, x, y - 1) == ' ')
        set_move(x, y, x, y - 1);
}

static void
move_knight(char *board, int x, int y)
{
    if (isupper(get_piece(board, x + 1, y + 2)) || get_piece(board, x + 1, y + 2) == ' ')
        set_move(x, y, x + 1, y + 2);
    else if (isupper(get_piece(board, x + 2, y + 1)) || get_piece(board, x + 2, y + 1) == ' ')
        set_move(x, y, x + 2, y + 1);
    else if (isupper(get_piece(board, x + 2, y - 1)) || get_piece(board, x + 2, y - 1) == ' ')
        set_move(x, y, x + 2, y - 1);
    else if (isupper(get_piece(board, x + 1, y - 2)) || get_piece(board, x + 1, y - 2) == ' ')
        set_move(x, y, x + 1, y - 2);
    else if (isupper(get_piece(board, x - 1, y + 2)) || get_piece(board, x - 1, y + 2) == ' ')
        set_move(x, y, x - 1, y + 2);
    else if (isupper(get_piece(board, x - 2, y + 1)) || get_piece(board, x - 2, y + 1) == ' ')
        set_move(x, y, x - 2, y + 1);
    else if (isupper(get_piece(board, x - 2, y - 1)) || get_piece(board, x - 2, y - 1) == ' ')
        set_move(x, y, x - 2, y - 1);
    else if (isupper(get_piece(board, x - 1, y - 2)) || get_piece(board, x - 1, y - 2) == ' ')
        set_move(x, y, x - 1, y - 2);
}

static void
move_bishop(char *board, int x, int y)
{
    if (isupper(get_piece(board, x - 1, y + 1)) || get_piece(board, x - 1, y + 1) == ' ')
        set_move(x, y, x - 1, y + 1);
    else if (isupper(get_piece(board, x + 1, y + 1)) || get_piece(board, x + 1, y + 1) == ' ')
        set_move(x, y, x + 1, y + 1);
    else if (isupper(get_piece(board, x - 1, y - 1)) || get_piece(board, x - 1, y - 1) == ' ')
        set_move(x, y, x - 1, y - 1);
    else if (isupper(get_piece(board, x + 1, y - 1)) || get_piece(board, x + 1, y - 1) == ' ')
        set_move(x, y, x + 1, y - 1);
}

static void
move_queen(char *board, int x, int y)
{
    if (isupper(get_piece(board, x, y + 1)) || get_piece(board, x, y + 1) == ' ')
        set_move(x, y, x, y + 1);
    else if (isupper(get_piece(board, x - 1, y)) || get_piece(board, x - 1, y) == ' ')
        set_move(x, y, x - 1, y);
    else if (isupper(get_piece(board, x + 1, y)) || get_piece(board, x + 1, y) == ' ')
        set_move(x, y, x + 1, y);
    else if (isupper(get_piece(board, x, y - 1)) || get_piece(board, x, y - 1) == ' ')
        set_move(x, y, x, y - 1);
    else if (isupper(get_piece(board, x - 1, y + 1)) || get_piece(board, x - 1, y + 1) == ' ')
        set_move(x, y, x - 1, y + 1);
    else if (isupper(get_piece(board, x + 1, y + 1)) || get_piece(board, x + 1, y + 1) == ' ')
        set_move(x, y, x + 1, y + 1);
    else if (isupper(get_piece(board, x - 1, y - 1)) || get_piece(board, x - 1, y - 1) == ' ')
        set_move(x, y, x - 1, y - 1);
    else if (isupper(get_piece(board, x + 1, y - 1)) || get_piece(board, x + 1, y - 1) == ' ')
        set_move(x, y, x + 1, y - 1);
}

static void
move_king(char *board, int x, int y)
{
    move_queen(board, x, y);
}

static int
find_move(char *board)
{
    char *piece;
    int x, y;

    if ((piece = strpbrk(board, "prnbqk")) == NULL)
        return EXIT_FAILURE;

    get_coords(board, piece, &x, &y);

    switch(*piece) {
    case 'p':
        move_pawn(board, x, y);
        break;
    case 'r':
        move_rook(board, x, y);
        break;
    case 'n':
        move_knight(board, x, y);
        break;
    case 'b':
        move_bishop(board, x, y);
        break;
    case 'q':
        move_queen(board, x, y);
        break;
    case 'k':
        move_king(board, x, y);
        break;
    default:
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int
do_chess()
{
    // 8 rows of 8 chars + newlines for each row
    char board[9 * 8];

    printf("Welcome to chessmaster 0x8000, enter your board:\n");

    if (read_board(board) != EXIT_SUCCESS) {
        printf("Invalid board\n");
        return EXIT_SUCCESS;
    }

    find_move(board);
    printf("Muahhaha, I move to %c%c%c%c\n",
            game_state.games.chess.move[0],
            game_state.games.chess.move[1],
            game_state.games.chess.move[2],
            game_state.games.chess.move[3]);

    return EXIT_SUCCESS;
}

