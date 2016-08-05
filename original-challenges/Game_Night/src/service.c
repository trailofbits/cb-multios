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

#include <libcgc.h>

#include "conv.h"
#include "stdio.h"
#include "string.h"

#include "games.h"

int
main(void)
{
    char buf[40] = { 0 };
    unsigned int game;

    init_cookie();

    while (1) {
        printf("Shall we play a game?\n\n"
                "1. Hugman\n"
                "2. Chess\n"
                "3. Sudoku\n"
                "4. Gallon Challenge\n"
                "5. Safari Zone\n"
                "6. Chance of Survival\n"
                "7. Lesson in Futility\n"
                "8. Quit\n\n");

        if (fread_until(buf, '\n', sizeof(buf), stdin) == EXIT_FAILURE)
            break;
        if (strlen(buf) == 0 || strtou(buf, 10, &game) == EXIT_FAILURE)
            continue;

        if (game == 1) {
            if (do_hugman() != EXIT_SUCCESS)
                break;
        } else if (game == 2) {
            if (do_chess() != EXIT_SUCCESS)
                break;
        } else if (game == 3) {
            if (do_sudoku() != EXIT_SUCCESS)
                break;
        } else if (game == 4) {
            if (do_gallon_challenge() != EXIT_SUCCESS)
                break;
        } else if (game == 5) {
            if (do_safari_zone() != EXIT_SUCCESS)
                break;
        } else if (game == 6) {
            if (do_chance_of_survival() != EXIT_SUCCESS)
                break;
        } else if (game == 7) {
            printf("Wouldn't you prefer a nice game of chess?\n");
            if (do_lesson_in_futility() != EXIT_SUCCESS)
                break;
        } else if (game == 8) {
            break;
        }
    }

    return 0;
}

