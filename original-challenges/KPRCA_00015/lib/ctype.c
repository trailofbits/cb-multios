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
#define CTYPE_LOWER 0x01
#define CTYPE_UPPER 0x02
#define CTYPE_DIGIT 0x04
#define CTYPE_PUNCT 0x08
#define CTYPE_SPACE 0x10
#define CTYPE_CNTRL 0x20

static const unsigned char _ctypes[128] = {
    /* 0x00 */
    CTYPE_CNTRL, CTYPE_CNTRL, CTYPE_CNTRL, CTYPE_CNTRL,
    CTYPE_CNTRL, CTYPE_CNTRL, CTYPE_CNTRL, CTYPE_CNTRL,
    /* 0x08 */
    CTYPE_CNTRL, CTYPE_CNTRL | CTYPE_SPACE, CTYPE_CNTRL | CTYPE_SPACE, CTYPE_CNTRL | CTYPE_SPACE,
    CTYPE_CNTRL | CTYPE_SPACE, CTYPE_CNTRL | CTYPE_SPACE, CTYPE_CNTRL, CTYPE_CNTRL,
    /* 0x10 */
    CTYPE_CNTRL, CTYPE_CNTRL, CTYPE_CNTRL, CTYPE_CNTRL,
    CTYPE_CNTRL, CTYPE_CNTRL, CTYPE_CNTRL, CTYPE_CNTRL,
    /* 0x18 */
    CTYPE_CNTRL, CTYPE_CNTRL, CTYPE_CNTRL, CTYPE_CNTRL,
    CTYPE_CNTRL, CTYPE_CNTRL, CTYPE_CNTRL, CTYPE_CNTRL,
    /* 0x20 */
    CTYPE_SPACE, CTYPE_PUNCT, CTYPE_PUNCT, CTYPE_PUNCT,
    CTYPE_PUNCT, CTYPE_PUNCT, CTYPE_PUNCT, CTYPE_PUNCT,
    /* 0x28 */
    CTYPE_PUNCT, CTYPE_PUNCT, CTYPE_PUNCT, CTYPE_PUNCT,
    CTYPE_PUNCT, CTYPE_PUNCT, CTYPE_PUNCT, CTYPE_PUNCT,
    /* 0x30 */
    CTYPE_DIGIT, CTYPE_DIGIT, CTYPE_DIGIT, CTYPE_DIGIT,
    CTYPE_DIGIT, CTYPE_DIGIT, CTYPE_DIGIT, CTYPE_DIGIT,
    /* 0x38 */
    CTYPE_DIGIT, CTYPE_DIGIT, CTYPE_PUNCT, CTYPE_PUNCT,
    CTYPE_PUNCT, CTYPE_PUNCT, CTYPE_PUNCT, CTYPE_PUNCT,
    /* 0x40 */
    CTYPE_PUNCT, CTYPE_UPPER, CTYPE_UPPER, CTYPE_UPPER,
    CTYPE_UPPER, CTYPE_UPPER, CTYPE_UPPER, CTYPE_UPPER,
    /* 0x48 */
    CTYPE_UPPER, CTYPE_UPPER, CTYPE_UPPER, CTYPE_UPPER,
    CTYPE_UPPER, CTYPE_UPPER, CTYPE_UPPER, CTYPE_UPPER,
    /* 0x50 */
    CTYPE_UPPER, CTYPE_UPPER, CTYPE_UPPER, CTYPE_UPPER,
    CTYPE_UPPER, CTYPE_UPPER, CTYPE_UPPER, CTYPE_UPPER,
    /* 0x58 */
    CTYPE_UPPER, CTYPE_UPPER, CTYPE_UPPER, CTYPE_PUNCT,
    CTYPE_PUNCT, CTYPE_PUNCT, CTYPE_PUNCT, CTYPE_PUNCT,
    /* 0x60 */
    CTYPE_PUNCT, CTYPE_LOWER, CTYPE_LOWER, CTYPE_LOWER,
    CTYPE_LOWER, CTYPE_LOWER, CTYPE_LOWER, CTYPE_LOWER,
    /* 0x68 */
    CTYPE_LOWER, CTYPE_LOWER, CTYPE_LOWER, CTYPE_LOWER,
    CTYPE_LOWER, CTYPE_LOWER, CTYPE_LOWER, CTYPE_LOWER,
    /* 0x70 */
    CTYPE_LOWER, CTYPE_LOWER, CTYPE_LOWER, CTYPE_LOWER,
    CTYPE_LOWER, CTYPE_LOWER, CTYPE_LOWER, CTYPE_LOWER,
    /* 0x78 */
    CTYPE_LOWER, CTYPE_LOWER, CTYPE_LOWER, CTYPE_PUNCT,
    CTYPE_PUNCT, CTYPE_PUNCT, CTYPE_PUNCT, CTYPE_CNTRL
};

int isascii(int c)
{
    return c >= 0 && c < 0x80;
}

int isprint(int c)
{
    return isascii(c) && (_ctypes[c] & CTYPE_CNTRL) == 0;
}

int isalnum(int c)
{
    return isascii(c) && (_ctypes[c] & (CTYPE_LOWER|CTYPE_UPPER|CTYPE_DIGIT));
}

int isalpha(int c)
{
    return isascii(c) && (_ctypes[c] & (CTYPE_LOWER|CTYPE_UPPER));
}

int islower(int c)
{
    return isascii(c) && (_ctypes[c] & CTYPE_LOWER);
}

int isupper(int c)
{
    return isascii(c) && (_ctypes[c] & CTYPE_UPPER);
}

int isspace(int c)
{
    return isascii(c) && (_ctypes[c] & CTYPE_SPACE);
}

int ispunct(int c)
{
    return isascii(c) && (_ctypes[c] & CTYPE_PUNCT);
}

int tolower(int c)
{
    if (isupper(c))
        return c + 0x20;
    else
        return c;
}

int toupper(int c)
{
    if (islower(c))
        return c - 0x20;
    else
        return c;
}
