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

#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_games.h"

struct cgc_game_state cgc_game_state;

void
cgc_init_cookie(void)
{
    unsigned char flag_byte;
    unsigned int gold = 0;
    int i;

    for (i = 0; i < sizeof(unsigned int); i++) {
        flag_byte = cgc_get_flag_byte(1021 + i);
        gold |= (cgc_memchr("\n\0", flag_byte, 2) == NULL ? flag_byte : 1) << ((3 - i) * 8);
    }

    cgc_game_state.games.hugman.cookie = gold;
}

int
cgc_check_cookie(unsigned int cookie)
{
    unsigned char flag_byte;
    unsigned int gold = 0;
    int i;

    for (i = 0; i < sizeof(unsigned int); i++) {
        flag_byte = cgc_get_flag_byte(1021 + i);
        gold |= (cgc_memchr("\n\0", flag_byte, 2) == NULL ? flag_byte : 1) << ((3 - i) * 8);
    }

    return cookie == gold;
}

