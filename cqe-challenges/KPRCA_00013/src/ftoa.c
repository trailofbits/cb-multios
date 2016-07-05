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
#include <libcgc.h>
#include <stdlib.h>
#include <string.h>

#include "convert.h"

char *ftoa(double value, char *str, size_t size) {
    if (size <= 1)
        return NULL;

    if (isinf(value) || isnan(value))
        return NULL;

    size_t i = 0;
    int negative = 0;

    if (value < 0) {
        negative = 1;
        str[i++] = '-';
        value *= -1;
    }

    if (i == size)
        return NULL;

    // apply rounding
    double rem = remainder(value, 0.001) * pow(10, 4);
    if (rem > 5 || (rem < 0 && rem > -5))
        if (!negative)
            value += 0.0005;
    else
        if (negative)
            value += 0.0005;
    int magnitude = value == 0 ? 0 : log10(value);
    if (magnitude < 0)
        magnitude = 0;
    for (; magnitude > -4; magnitude--)
    {
        if (i == size)
            break;

        if (magnitude == -1)
        {
            str[i++] = '.';
            if (i == size)
                break;
        }

        double e = pow(10, magnitude);
        int digit = value / e;
        value -= digit * e;
        str[i++] = digit + '0';
    }

    if (i == size)
        return NULL;
    else
        str[i] = '\0';

    return str;
}
