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

static void
cgc_defcon_1(void)
{
    cgc_printf("A strange game. The only winning move is not to play.\n");
}

static void
cgc_defcon_2(void)
{
    char buf[40] = { 0 };
    unsigned int lat, lon;
    void __attribute__((regparm(1))) (*fnptr)(unsigned int);

    cgc_printf("Enter target latitude:\n");
    if (cgc_fread_until(buf, '\n', sizeof(buf), cgc_stdin) == EXIT_FAILURE)
        return;
    if (cgc_strlen(buf) == 0 || cgc_strtou(buf, 16, &lat) == EXIT_FAILURE)
        return;

    cgc_printf("Enter target longitude:\n");
    if (cgc_fread_until(buf, '\n', sizeof(buf), cgc_stdin) == EXIT_FAILURE)
        return;
    if (cgc_strlen(buf) == 0 || cgc_strtou(buf, 16, &lon) == EXIT_FAILURE)
        return;

    fnptr = (void *)(lat | 0xf0000000);
    fnptr(lon);
}

int
cgc_do_lesson_in_futility(void)
{
#ifdef PATCHED_2
    if (!cgc_check_cookie(cgc_game_state.games.gallon_challenge.cookie))
        return EXIT_FAILURE;
#endif

    if (cgc_game_state.defcon_level == 0)
        cgc_game_state.defcon_level = 1;

    if (cgc_game_state.defcon_level == 1)
        cgc_defcon_1();
    else if (cgc_game_state.defcon_level == 2)
        cgc_defcon_2();
    else
        return EXIT_FAILURE;

    return EXIT_SUCCESS;

}

