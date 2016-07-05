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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "convert.h"

double atof(char *str, size_t size, int *bad_conversion)
{
    if (str == NULL || strlen(str) >= size || strlen(str) == 0)
        goto error;

    double val = 0.0, exp = 0.0, dec_multiplier = 1.0;
    int has_period = 0, has_exp = 0;
    int negative = 1;
    int num_dec = 0;

    if (*str == '-') {
        str++;
        if (*str == '\0')
            goto error;
        negative = -1;
    }

    while (*str != '\0') {
        if (*str >= '0' && *str <= '9') {
            if (has_exp) {
                exp = (exp * 10) + (*str - '0');
            } else if (!has_period) {
                val = (val * 10) + (*str - '0');
            } else {
                dec_multiplier *= 10;
                num_dec++;
                val += ((*str - '0') / dec_multiplier);
            }
        } else if (*str == '.') {
            has_period++;
        } else if (tolower(*str) == 'e') {
            has_exp++;
        } else {
            goto error;
        }

        if (has_period > 1 || has_exp > 1)
            goto error;

        if (num_dec >= MAX_DEC)
            goto done;

        str++;
    }
    goto done;

error:
    *bad_conversion = 1;
    return 0.0;

done:
    if (has_exp)
        val *= pow(10, exp);

    return val * negative;
}

