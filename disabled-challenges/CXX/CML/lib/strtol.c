/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, cgc_free of charge, to any person obtaining a copy
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
#include "cgc_ctype.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"

#ifdef STRTOUL
unsigned long cgc_strtoul(const char *str, char **endptr, int base)
#else
long cgc_strtol(const char *str, char **endptr, int base)
#endif
{
    const char *orig = str;
    int sign = 1, empty = 1, overflow = 0;
#ifdef STRTOUL
    unsigned long long val = 0;
#else
    unsigned long val = 0;
#endif

    /* 1. initial sequence of white-space characters */
    while (cgc_isspace(*str))
    {
        if (*str == 0)
            goto error;
        str++;
    }

    /* 2. subject sequence interpreted as an integer */
    /* preceding sign */
    if (*str == '+')
    {
        sign = 1;
        str++;
    }
    else if (*str == '-')
    {
        sign = -1;
        str++;
    }
    /* prefix */
    if (base == 16)
    {
        if (str[0] == '0' && cgc_tolower(str[1]) == 'x')
            str += 2;
    }
    else if (base == 0)
    {
        if (str[0] == '0' && str[1] >= '0' && str[1] <= '7')
        {
            str++;
            base = 8;
        }
        else if (str[0] == '0' && cgc_tolower(str[1]) == 'x')
        {
            str += 2;
            base = 16;
        }
        else if (cgc_isdigit(*str))
            base = 10;
        else
            goto error;
    }
    /* value */
    while (*str)
    {
        int x;
        if (cgc_isdigit(*str))
            x = *str - '0';
        else if (cgc_islower(*str))
            x = *str - 'a' + 10;
        else if (cgc_isupper(*str))
            x = *str - 'A' + 10;
        else
            goto error;

        if (x >= base)
            goto error;

        empty = 0;
        val = val * base + x;
#ifdef STRTOUL
        if (val > ULONG_MAX)
#else
        if (val > LONG_MAX)
#endif
            overflow = 1;
        str++;
    }

error:
    if (endptr != NULL)
        *endptr = (char *) (empty ? orig : str);
#ifdef STRTOUL
    if (sign < 0)
    {
        if (val > LONG_MAX && val != (unsigned long)LONG_MIN)
            overflow = 1;
        val = -val;
    }
    return overflow ? ULONG_MAX : val;
#else
    if (sign < 0)
        return overflow ? LONG_MIN : -val;
    else
        return overflow ? LONG_MAX : val;
#endif
}
