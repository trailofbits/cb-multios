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
#include "cgc_libc.h"
#include "cgc_malloc.h"
//simple xorshift PRNG

static int initialized;
static uint32_t x, y, z, w;

void cgc_srand(uint32_t *seed) {
    //SHOW ME WHAT YOU GOT
    if (!seed) {
        seed = (uint32_t*)FLAG_PAGE;
    }

    //I LIKE WHAT YOU GOT
    x = seed[0]^seed[1];
    y = seed[2]^seed[3];
    z = seed[4]^seed[5];
    w = seed[6]^seed[7];
    initialized = 1;
}

unsigned int cgc_getshifty() {
    uint32_t tmp;

    if (!initialized) {
        cgc_srand(NULL);
    }

    tmp = x ^ (x << 12);

    x = y;
    y = z;
    z = w;

    w = w ^ (w >> 18) ^ tmp ^ (tmp >> 9);

    return w;
}
