/*
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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_convert.h"

char *cgc_itoa(int value, char *str, cgc_size_t size)
{
    int base = 10;
    if (size <= 1 )
        return NULL;

    cgc_size_t i = 0;
    int is_negative = 0;

    if (value < 0)
        is_negative = 1;

    do {
        if (is_negative)
            str[i++] = '0' - value % base;
        else
            str[i++] = '0' + value % base;

        value /= base;
    } while (i < size - 1 && value != 0);

    if (value != 0 || (i == size - 1  && is_negative))
        return NULL;

    if (is_negative)
        str[i++] = '-';
    str[i--] = '\0';

    int j = 0;
    while (i > j) {
        char c = str[j];
        str[j++] = str[i];
        str[i--] = c;
    }

    return str;
}
