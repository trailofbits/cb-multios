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

int
cgc_do_gallon_challenge(void)
{
    char buf[40] = { 0 };
    unsigned int countdown;
    int i;

    if (cgc_game_state.games.gallon_challenge.tank_size == 0)
        cgc_game_state.games.gallon_challenge.tank_size = 100;

    cgc_printf("Give me a countdown!\n");
    if (cgc_fread_until(buf, '\n', sizeof(buf), cgc_stdin) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (cgc_strlen(buf) == 0 || cgc_strtou(buf, 16, &countdown) == EXIT_FAILURE)
        return EXIT_FAILURE;

    for (i = 0; i < cgc_game_state.games.gallon_challenge.tank_size; i++) {
        if (i < 100)
            cgc_printf("CHUG! ");

        *(unsigned int *)&cgc_game_state.spew[i & ~(sizeof(unsigned int) - 1)] = countdown;
    }
    cgc_printf("\n");

    if (!cgc_check_cookie(cgc_game_state.games.gallon_challenge.cookie))
        cgc_printf("Woah... bleh.\n");
    else
        cgc_printf("Nice!\n");

    return EXIT_SUCCESS;
}

