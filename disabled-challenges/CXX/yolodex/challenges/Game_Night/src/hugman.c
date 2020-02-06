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

#include "cgc_stdio.h"
#include "cgc_string.h"

#include "cgc_games.h"
#include "cgc_words.h"

static const char *new_board =
    "                     --------\n\0"
    "                     |      |\n\0"
    "                            |\n\0"
    "                            |\n\0"
    "                            |\n\0"
    "                            |\n\0"
    "                            |\n\0"
    "                     _______|\n\0"
    "                             \n\0"
    "                             \n\0"
    "        _ _ _ _ _ _ _ _      \n\0";

int
cgc_do_hugman(void)
{
    cgc_size_t round = cgc_game_state.games.hugman.round % 4;
#ifdef PATCHED_1
    cgc_size_t index = round * 256 + cgc_get_flag_byte(cgc_game_state.games.hugman.round);
#else
    cgc_size_t index = round * 256 + cgc_get_flag_byte_unsafe(cgc_game_state.games.hugman.round);
#endif
    const char *word = dict[index];
    int i, j, c_, success, win;
    char c;

    char board[11][31];
    cgc_memcpy(board, new_board, sizeof(board));

    char graveyard[53] = { 0 };

    const char limbs[] = {
        'O', '|', '\\', '/', '|', '/', '\\'
    };

    struct {
        cgc_size_t x, y;
    } limb_coordinates[] = {
        { 2, 21 },
        { 3, 21 },
        { 3, 20 },
        { 3, 22 },
        { 4, 21 },
        { 5, 20 },
        { 5, 22 }
    }, letter_coordinates[] = {
        { 10, 8 },
        { 10, 10 },
        { 10, 12 },
        { 10, 14 },
        { 10, 16 },
        { 10, 18 },
        { 10, 20 },
        { 10, 22 }
    };

    if (!cgc_check_cookie(cgc_game_state.games.gallon_challenge.cookie))
        return EXIT_FAILURE;

    for (i = 0; i < sizeof(limbs) / sizeof(limbs[0]);) {
        success = 0;
        win = 1;

        for (j = 0; j < sizeof(board) / sizeof(board[0]); j++)
            cgc_printf("%s", board[j]);
        cgc_printf("Incorrect: %s\n", graveyard);

        do {
            if ((c_ = getc()) < 0)
                return EXIT_FAILURE;
            c = c_;
        } while (c == '\n');

        for (j = 0; j < 8; j++) {
            if (word[j] == c) {
                board[letter_coordinates[j].x][letter_coordinates[j].y] = c;
                success = 1;
            }

            if (board[letter_coordinates[j].x][letter_coordinates[j].y] == '_')
                win = 0;
        }

        if (win)
            break;

        if (!success) {
            board[limb_coordinates[i].x][limb_coordinates[i].y] = limbs[i];
            i++;

            if (cgc_strchr(graveyard, c) == NULL)
                cgc_strncat(graveyard, &c, 1);
        }
    }

    for (j = 0; j < sizeof(board) / sizeof(board[0]); j++)
        cgc_printf("%s", board[j]);

    cgc_game_state.games.hugman.round++;
    // Avoid giving away a free Missigno/Mewthree!
    if (cgc_game_state.games.hugman.round == 6 ||
            cgc_game_state.games.hugman.round == 0xffffffff)
        cgc_game_state.games.hugman.round++;

    if (win)
        cgc_printf("CONGRATULATIONS!\n");
    else
        cgc_printf("Sorry, the word was %s!\n", word);

    return EXIT_SUCCESS;
}
