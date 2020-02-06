/*
 * Copyright (c) 2016 Kaprica Security, Inc.
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

#ifndef PRINT_H_
#define PRINT_H_
#include "cgc_cstdio.h"
#include "cgc__defines.h"

#define PRINT_ARR_CHARS(_array, _size) \
    do { \
        unsigned char * __array = (unsigned char *)(_array); \
        for (int _i=0; _i < (_size); _i++) \
        { \
            cgc_printf(ESC "c", (__array)[_i]); \
        } \
    } while (0)

#define PRINT_ARR_HEX(_array, _size) \
    do { \
        unsigned char * __array = (unsigned char *)(_array); \
        for (int _i=0; _i < (_size); _i++) \
        { \
            cgc_printf("\\x" ESC "02x", (__array)[_i]); \
        } \
    } while (0)

#endif
