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

#include "cgc_stdlib.h"

static unsigned long long rand_seed = 0xdeadbeefull;

void
cgc_srand(unsigned int seed)
{
    rand_seed = seed;
}

unsigned int
cgc_rand(void)
{
    // Constants from Knuth
    rand_seed = 6364136223846793005 * rand_seed + 1442695040888963407;
    return (unsigned int)(rand_seed >> 32);
}

unsigned char
cgc_get_flag_byte(cgc_size_t index)
{
    unsigned char *flag_page = FLAG_PAGE;
    return flag_page[(index % (PAGE_SIZE / 4)) * 4];
}

unsigned char
cgc_get_flag_byte_unsafe(cgc_size_t index)
{
    unsigned char *flag_page = FLAG_PAGE;
    return flag_page[index % PAGE_SIZE];
}

