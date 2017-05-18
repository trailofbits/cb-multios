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
cgc_read_board(char *board)
{
    int i;

    if (cgc_fread(board, 8 * 9, cgc_stdin) != 8 * 9)
        return EXIT_FAILURE;

    for (i = 0; i < 8 * 9; i++) {
        if ((i + 1) % 9 == 0) {
            if (board[i] != '\n')
                return EXIT_FAILURE;
        } else {
            if (cgc_strchr("prnbqk ", board[i]) == NULL)
                return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

static char
cgc_get_piece(char *board, int x, int y)
{
    if (x < 0 || y < 0 || x >= 8 || y >= 8)
        return '\0';

    return board[y * 9 + x];
}

static void
cgc_get_coords(char *board, char *piece, int *x, int *y)
{
    *x = (piece - board) % 9;
    *y = (piece - board) / 9;
}

static void
cgc_set_move(int x0, int y0, int x1, int y1)
{
    cgc_game_state.games.chess.move[0] = x0 + 'a';
    cgc_game_state.games.chess.move[1] = y0 + '1';
    cgc_game_state.games.chess.move[2] = x1 + 'a';
    cgc_game_state.games.chess.move[3] = y1 + '1';
}

/* We don't bother modeling all the nuances of the game's rules in these functions */
static void
cgc_move_pawn(char *board, int x, int y)
{
    if (cgc_isupper(cgc_get_piece(board, x - 1, y)))
        cgc_set_move(x, y, x - 1, y);
    else if (cgc_isupper(cgc_get_piece(board, x + 1, y)))
        cgc_set_move(x, y, x + 1, y);
    else if (cgc_get_piece(board, x, y + 2) == ' ')
        cgc_set_move(x, y, x, y + 2);
    else if (cgc_get_piece(board, x, y + 1) == ' ')
        cgc_set_move(x, y, x, y + 1);
}

static void
cgc_move_rook(char *board, int x, int y)
{
    if (cgc_isupper(cgc_get_piece(board, x, y + 1)) || cgc_get_piece(board, x, y + 1) == ' ')
        cgc_set_move(x, y, x, y + 1);
    else if (cgc_isupper(cgc_get_piece(board, x - 1, y)) || cgc_get_piece(board, x - 1, y) == ' ')
        cgc_set_move(x, y, x - 1, y);
    else if (cgc_isupper(cgc_get_piece(board, x + 1, y)) || cgc_get_piece(board, x + 1, y) == ' ')
        cgc_set_move(x, y, x + 1, y);
    else if (cgc_isupper(cgc_get_piece(board, x, y - 1)) || cgc_get_piece(board, x, y - 1) == ' ')
        cgc_set_move(x, y, x, y - 1);
}

static void
cgc_move_knight(char *board, int x, int y)
{
    if (cgc_isupper(cgc_get_piece(board, x + 1, y + 2)) || cgc_get_piece(board, x + 1, y + 2) == ' ')
        cgc_set_move(x, y, x + 1, y + 2);
    else if (cgc_isupper(cgc_get_piece(board, x + 2, y + 1)) || cgc_get_piece(board, x + 2, y + 1) == ' ')
        cgc_set_move(x, y, x + 2, y + 1);
    else if (cgc_isupper(cgc_get_piece(board, x + 2, y - 1)) || cgc_get_piece(board, x + 2, y - 1) == ' ')
        cgc_set_move(x, y, x + 2, y - 1);
    else if (cgc_isupper(cgc_get_piece(board, x + 1, y - 2)) || cgc_get_piece(board, x + 1, y - 2) == ' ')
        cgc_set_move(x, y, x + 1, y - 2);
    else if (cgc_isupper(cgc_get_piece(board, x - 1, y + 2)) || cgc_get_piece(board, x - 1, y + 2) == ' ')
        cgc_set_move(x, y, x - 1, y + 2);
    else if (cgc_isupper(cgc_get_piece(board, x - 2, y + 1)) || cgc_get_piece(board, x - 2, y + 1) == ' ')
        cgc_set_move(x, y, x - 2, y + 1);
    else if (cgc_isupper(cgc_get_piece(board, x - 2, y - 1)) || cgc_get_piece(board, x - 2, y - 1) == ' ')
        cgc_set_move(x, y, x - 2, y - 1);
    else if (cgc_isupper(cgc_get_piece(board, x - 1, y - 2)) || cgc_get_piece(board, x - 1, y - 2) == ' ')
        cgc_set_move(x, y, x - 1, y - 2);
}

static void
cgc_move_bishop(char *board, int x, int y)
{
    if (cgc_isupper(cgc_get_piece(board, x - 1, y + 1)) || cgc_get_piece(board, x - 1, y + 1) == ' ')
        cgc_set_move(x, y, x - 1, y + 1);
    else if (cgc_isupper(cgc_get_piece(board, x + 1, y + 1)) || cgc_get_piece(board, x + 1, y + 1) == ' ')
        cgc_set_move(x, y, x + 1, y + 1);
    else if (cgc_isupper(cgc_get_piece(board, x - 1, y - 1)) || cgc_get_piece(board, x - 1, y - 1) == ' ')
        cgc_set_move(x, y, x - 1, y - 1);
    else if (cgc_isupper(cgc_get_piece(board, x + 1, y - 1)) || cgc_get_piece(board, x + 1, y - 1) == ' ')
        cgc_set_move(x, y, x + 1, y - 1);
}

static void
cgc_move_queen(char *board, int x, int y)
{
    if (cgc_isupper(cgc_get_piece(board, x, y + 1)) || cgc_get_piece(board, x, y + 1) == ' ')
        cgc_set_move(x, y, x, y + 1);
    else if (cgc_isupper(cgc_get_piece(board, x - 1, y)) || cgc_get_piece(board, x - 1, y) == ' ')
        cgc_set_move(x, y, x - 1, y);
    else if (cgc_isupper(cgc_get_piece(board, x + 1, y)) || cgc_get_piece(board, x + 1, y) == ' ')
        cgc_set_move(x, y, x + 1, y);
    else if (cgc_isupper(cgc_get_piece(board, x, y - 1)) || cgc_get_piece(board, x, y - 1) == ' ')
        cgc_set_move(x, y, x, y - 1);
    else if (cgc_isupper(cgc_get_piece(board, x - 1, y + 1)) || cgc_get_piece(board, x - 1, y + 1) == ' ')
        cgc_set_move(x, y, x - 1, y + 1);
    else if (cgc_isupper(cgc_get_piece(board, x + 1, y + 1)) || cgc_get_piece(board, x + 1, y + 1) == ' ')
        cgc_set_move(x, y, x + 1, y + 1);
    else if (cgc_isupper(cgc_get_piece(board, x - 1, y - 1)) || cgc_get_piece(board, x - 1, y - 1) == ' ')
        cgc_set_move(x, y, x - 1, y - 1);
    else if (cgc_isupper(cgc_get_piece(board, x + 1, y - 1)) || cgc_get_piece(board, x + 1, y - 1) == ' ')
        cgc_set_move(x, y, x + 1, y - 1);
}

static void
cgc_move_king(char *board, int x, int y)
{
    cgc_move_queen(board, x, y);
}

static int
cgc_find_move(char *board)
{
    char *piece;
    int x, y;

    if ((piece = cgc_strpbrk(board, "prnbqk")) == NULL)
        return EXIT_FAILURE;

    cgc_get_coords(board, piece, &x, &y);

    switch(*piece) {
    case 'p':
        cgc_move_pawn(board, x, y);
        break;
    case 'r':
        cgc_move_rook(board, x, y);
        break;
    case 'n':
        cgc_move_knight(board, x, y);
        break;
    case 'b':
        cgc_move_bishop(board, x, y);
        break;
    case 'q':
        cgc_move_queen(board, x, y);
        break;
    case 'k':
        cgc_move_king(board, x, y);
        break;
    default:
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int
cgc_do_chess()
{
    // 8 rows of 8 chars + newlines for each row
    char board[9 * 8];

    cgc_printf("Welcome to chessmaster 0x8000, enter your board:\n");

    if (cgc_read_board(board) != EXIT_SUCCESS) {
        cgc_printf("Invalid board\n");
        return EXIT_SUCCESS;
    }

    cgc_find_move(board);
    cgc_printf("Muahhaha, I move to %c%c%c%c\n",
            cgc_game_state.games.chess.move[0],
            cgc_game_state.games.chess.move[1],
            cgc_game_state.games.chess.move[2],
            cgc_game_state.games.chess.move[3]);

    return EXIT_SUCCESS;
}

