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

int
do_gallon_challenge(void)
{
    char buf[40] = { 0 };
    unsigned int countdown;
    int i;

    if (game_state.games.gallon_challenge.tank_size == 0)
        game_state.games.gallon_challenge.tank_size = 100;

    printf("Give me a countdown!\n");
    if (fread_until(buf, '\n', sizeof(buf), stdin) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (strlen(buf) == 0 || strtou(buf, 16, &countdown) == EXIT_FAILURE)
        return EXIT_FAILURE;

    for (i = 0; i < game_state.games.gallon_challenge.tank_size; i++) {
        if (i < 100)
            printf("CHUG! ");

        *(unsigned int *)&game_state.spew[i & ~(sizeof(unsigned int) - 1)] = countdown;
    }
    printf("\n");

    if (!check_cookie(game_state.games.gallon_challenge.cookie))
        printf("Woah... bleh.\n");
    else
        printf("Nice!\n");

    return EXIT_SUCCESS;
}

