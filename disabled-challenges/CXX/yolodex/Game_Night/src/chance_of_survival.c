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
cgc_empty(void)
{
    cgc_printf("Is this thing on?\n");
}

static void
cgc_option_0(void)
{
    cgc_printf("*CLICK*\n");
}

static void
cgc_option_1(void)
{
    cgc_printf("*CLICK*\n");
}

static void
cgc_option_2(void)
{
    cgc_printf("*CLICK*\n");
}

static void
cgc_option_3(void)
{
    cgc_printf("*NERVOUS LOOK*\n");
}

static void
cgc_option_4(void)
{
    cgc_printf("*CRAZY EYES*\n");
}

static void
cgc_option_5(void)
{
    cgc_printf("WHEW!\n");
}

static void
cgc_doit(void)
{
    char buf[40] = { 0 };
    unsigned int foo, bar;
    void __attribute__((regparm(1))) (*fnptr)(unsigned int);

    cgc_printf("Whoops:\n");
    if (cgc_fread_until(buf, '\n', sizeof(buf), cgc_stdin) == EXIT_FAILURE)
        return;
    if (cgc_strlen(buf) == 0 || cgc_strtou(buf, 16, &foo) == EXIT_FAILURE)
        return;

    if (cgc_fread_until(buf, '\n', sizeof(buf), cgc_stdin) == EXIT_FAILURE)
        return;
    if (cgc_strlen(buf) == 0 || cgc_strtou(buf, 16, &bar) == EXIT_FAILURE)
        return;

    fnptr = (void *)(foo | 0xf0000000);
    fnptr(bar);
}

int
cgc_do_chance_of_survival(void)
{
    void (*options[])(void) = {
        cgc_empty,
        cgc_option_0,
        cgc_option_1,
        cgc_option_2,
        cgc_option_3,
        cgc_option_4,
        cgc_option_5,
        cgc_doit
    };

    int i;

    if (!cgc_check_cookie(cgc_game_state.games.gallon_challenge.cookie))
        return EXIT_FAILURE;

    for (i = 0; i < 6; i++)
        if (cgc_game_state.games.chance_of_survival.options[i] < sizeof(options) / sizeof(options[0]))
            options[cgc_game_state.games.chance_of_survival.options[i]]();

    return EXIT_SUCCESS;
}

