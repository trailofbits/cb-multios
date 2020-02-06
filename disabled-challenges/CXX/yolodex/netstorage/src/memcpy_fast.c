/*
 * Author: Andrew Wesie <andrew.wesie@kapricasecurity.com>
 *
 * Copyright (c) 2014 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include "cgc_stdlib.h"
#include "cgc_string.h"

typedef unsigned int intptr_t;
typedef unsigned int uint128_t __attribute__((__vector_size__(16)));

void *cgc_memcpy_fast(void *dst, void *src, cgc_size_t length)
{
    if ((length % 16) || ((intptr_t)dst % 16) || ((intptr_t)src % 16))
        return cgc_memcpy(dst, src, length);

#if PATCHED
    if (length == 0)
        return dst;
#endif

    cgc_size_t i = 0;
    do
    {
        ((uint128_t*)dst)[i] = ((uint128_t*)src)[i];
    }
    while (++i < (length / 16));
    return dst;
}
