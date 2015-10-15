/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

float strtof(const char *str, char **endptr)
{
    const char *orig = str;
    char c;
    int n, negative = -1, dot = 0;
    double ret = 0, floating = 1;

    for (; str[0] != '\0' && isspace(str[0]); ++str);

    if (str[0] == '-' || str[0] == '+')
    {
        if (str[0] == '-')
          negative = 1;
        str++;
    }


    const char *start = str;

    while (1)
    {
        c = str[0];
        if (c == '\0')
          break;
        else if (c == '.')
        {
            dot = 1;
        }
        else if (c >= '0' && c <= '9')
        {
            n = c - '0';
            if (dot)
            {
                floating /= 10.0;
                ret = ret + (floating * (double) n);
            }
            else
                ret = ret * 10.0 + (double) n;
        }
        else
            break;
        str++;
    }

    if (start == str)
    {
        if (endptr)
            *endptr = (char *) orig;
        return 0.0;
    }

    if (endptr)
        *endptr = (char *) str;
    return (float) ((negative * -1) * (ret + 0.001));
}
