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

#include "math.h"

#define SIGNMASK (1ull << 63)
#define EXPMASK (0x7ffull << 52)
#define MANTMASK (~(1ull << 52))

unsigned long long
sign(double d)
{
    return *(unsigned long long *)(&d) & SIGNMASK;
}

unsigned long long
exponent(double d)
{
    return *(unsigned long long *)(&d) & EXPMASK;
}

unsigned long long
mantissa(double d)
{
    return *(unsigned long long *)(&d) & MANTMASK;
}

int
isnan(double d)
{
    return exponent(d) == EXPMASK && mantissa(d) != 0;
}

int
isinf(double d)
{
    if (exponent(d) == EXPMASK && mantissa(d) == 0)
        return sign(d) ? -1 : 1;
    return 0;
}

double
abs(double d)
{
    unsigned long long ret = *(unsigned long long *)(&d) & ~SIGNMASK;
    return *(double *)(&ret);
}

double
clamp(double d)
{
    if (d < 0.0)
        return 0.0;
    else if (d > 1.0)
        return 1.0;
    else
        return d;
}

