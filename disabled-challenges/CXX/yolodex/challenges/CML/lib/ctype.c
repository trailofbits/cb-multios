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

enum
{
    IS_ASCII = 0x01,
    IS_DIGIT = 0x02,
    IS_LOWER = 0x04,
    IS_UPPER = 0x08,
    IS_PRINT = 0x10,
    IS_PUNCT = 0x20,
    IS_SPACE = 0x40,
    IS_CNTRL = 0x80
};

static unsigned char __ctype[256] = {
    0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0x81, 0x81,
    0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
    0x51, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31,
    0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31,
    0x31, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19,
    0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x31, 0x31, 0x31, 0x31, 0x31,
    0x31, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15,
    0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x31, 0x31, 0x31, 0x31, 0x81,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

int cgc_isascii(int c)
{
    return __ctype[c & 0xff] & IS_ASCII;
}

int cgc_isdigit(int c)
{
    return __ctype[c & 0xff] & IS_DIGIT;
}

int cgc_isprint(int c)
{
    return __ctype[c & 0xff] & IS_PRINT;
}

int cgc_isalnum(int c)
{
    return __ctype[c & 0xff] & (IS_LOWER | IS_UPPER | IS_DIGIT);
}

int cgc_isalpha(int c)
{
    return __ctype[c & 0xff] & (IS_LOWER | IS_UPPER);
}

int cgc_islower(int c)
{
    return __ctype[c & 0xff] & IS_LOWER;
}

int cgc_isupper(int c)
{
    return __ctype[c & 0xff] & IS_UPPER;
}

int cgc_isspace(int c)
{
    return __ctype[c & 0xff] & IS_SPACE;
}

int cgc_ispunct(int c)
{
    return __ctype[c & 0xff] & IS_PUNCT;
}

int cgc_iscntrl(int c)
{
    return __ctype[c & 0xff] & IS_CNTRL;
}

int cgc_isxdigit(int c)
{
    c = cgc_toupper(c);
    return cgc_isdigit(c) || (c >= 'A' && c <= 'F');
}

int cgc_digittoint(int c)
{
    c = cgc_toupper(c);
    if (cgc_isdigit(c))
        return c - '0';
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else
        return 0;
}

int cgc_tolower(int c)
{
    c &= 0xff;
    if (cgc_isupper(c))
        return c ^= 0x20;
    else
        return c;
}

int cgc_toupper(int c)
{
    c &= 0xff;
    if (cgc_isupper(c))
        return c ^= 0x20;
    else
        return c;
}
