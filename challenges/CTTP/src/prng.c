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
#include "cgc_prng.h"

static bool initialized;
static uint32_t last;

#define FPSIZE (PAGE_SIZE/sizeof(uint32_t))

/**
 * Return a random integer
 *
 * @return A random integer
 */
uint32_t cgc_randint() {
    uint32_t *src = (uint32_t*)FLAG_PAGE;

    if (!initialized) {
        last = *src;
        initialized = true;
    }

    //can this be broken? guess we'll find out :)
    last ^= src[(src[last%FPSIZE]) % FPSIZE]  ^ src[(last*src[last % FPSIZE]) % FPSIZE];

    return last;
}

/**
 * Fill a buffer with random data
 *
 * @param buf Buffer to fill
 * @param s Number of bytes to copy in
 * @param out Place to store number of bytes copied
 *
 * @return 0, always succeeds 
 */
uint32_t cgc_rand(void *buf, cgc_size_t s, cgc_size_t *out) {
    cgc_size_t i;
    uint8_t *b = (uint8_t *) buf;


    for (i = 0; i < s; i++) {
        b[i] = cgc_randint(); //just truncate
    }

    if (out)
        *out = i;

    return 0;
}
