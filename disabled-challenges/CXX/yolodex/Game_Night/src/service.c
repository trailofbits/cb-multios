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

#include "libcgc.h"

#include "cgc_conv.h"
#include "cgc_stdio.h"
#include "cgc_string.h"

#include "cgc_games.h"

int
main(int cgc_argc, char *cgc_argv[])
{
    char buf[40] = { 0 };
    unsigned int game;

    cgc_init_cookie();

    while (1) {
        cgc_printf("Shall we play a game?\n\n"
                "1. Hugman\n"
                "2. Chess\n"
                "3. Sudoku\n"
                "4. Gallon Challenge\n"
                "5. Safari Zone\n"
                "6. Chance of Survival\n"
                "7. Lesson in Futility\n"
                "8. Quit\n\n");

        if (cgc_fread_until(buf, '\n', sizeof(buf), cgc_stdin) == EXIT_FAILURE)
            break;
        if (cgc_strlen(buf) == 0 || cgc_strtou(buf, 10, &game) == EXIT_FAILURE)
            continue;

        if (game == 1) {
            if (cgc_do_hugman() != EXIT_SUCCESS)
                break;
        } else if (game == 2) {
            if (cgc_do_chess() != EXIT_SUCCESS)
                break;
        } else if (game == 3) {
            if (cgc_do_sudoku() != EXIT_SUCCESS)
                break;
        } else if (game == 4) {
            if (cgc_do_gallon_challenge() != EXIT_SUCCESS)
                break;
        } else if (game == 5) {
            if (cgc_do_safari_zone() != EXIT_SUCCESS)
                break;
        } else if (game == 6) {
            if (cgc_do_chance_of_survival() != EXIT_SUCCESS)
                break;
        } else if (game == 7) {
            cgc_printf("Wouldn't you prefer a nice game of chess?\n");
            if (cgc_do_lesson_in_futility() != EXIT_SUCCESS)
                break;
        } else if (game == 8) {
            break;
        }
    }

    return 0;
}

