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
#include <libcgc.h>
#include <ctype.h>
#include <string.h>

long strtol(const char *str, char **endptr, int base)
{
    int c, neg = 0;
    const char *alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
    long val = 0;

    if (base != 0 && (base < 2 || base > 36)) return 0;

    /* skip whitespace */
    while (*str && isspace(*str))
        str++;

    /* parse potential -/+ (default to positive) */
    if (*str == '-')
    {
        neg = 1;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }

    /* parse prefix (0x, 0) */
    if (base == 0 || base == 16)
    {
        if (str[0] == '0' && str[1] == 'x')
        {
            base = 16;
            str += 2;
        }
    }
    if (base == 0)
    {
        if (str[0] == '0')
            base = 8;
    }
    if (base == 0)
        base = 10;

    /* parse number */
    while ((c = *str))
    {
        /* search for c */
        const char *idx = memchr(alphabet, tolower(c), base);
        if (idx == NULL)
            break;
        /* XXX clamp to LONG_MAX / LONG_MIN */
        val = val * base + (idx - alphabet);
        str++;
    }

    if (endptr)
        *endptr = (char *)str;
    if (neg)
        return -val;
    else
        return val;
}

unsigned long strtoul(const char *str, char **endptr, int base)
{
    return (unsigned long)strtol(str, endptr, base);
}
