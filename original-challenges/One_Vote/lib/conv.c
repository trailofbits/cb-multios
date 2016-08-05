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
#include <libcgc.h>
#include <errno.h>
#include <stdint.h>
#include "conv.h"


unsigned char is_non_printable(const unsigned char ch) {
    if (FALSE == is_printable(ch)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

unsigned char is_printable(const unsigned char ch) {
    if ((TRUE == is_digit(ch)) ||
        (TRUE == is_letter(ch)) ||
        (TRUE == is_symbol(ch))) {
        return TRUE;
    } else {
        return FALSE;
    }
}

unsigned char is_digit(const unsigned char ch) {
    if ((0x30 <= ch) && (0x39 >= ch)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

unsigned char is_hexdigit(const unsigned char ch) {
    if ((TRUE == is_digit(ch)) ||
        (('a' <= ch) && ('f' >= ch)) ||
        (('A' <= ch) && ('F' >= ch))) {
        return TRUE;
    } else {
        return FALSE;
    }
}

unsigned char is_letter(const unsigned char ch) {
    if ((TRUE == is_upper(ch)) ||
        (TRUE == is_lower(ch))) {
        return TRUE;
    } else {
        return FALSE;
    }
}

unsigned char is_upper(const unsigned char ch) {
    if ((0x41 <= ch) && (0x5A >= ch)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

unsigned char is_lower(const unsigned char ch) {
    if ((0x61 <= ch) && (0x7A >= ch)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

unsigned char is_symbol(const unsigned char ch) {
    if  (((0x21 <= ch) && (ch <= 0x2F)) || 
         ((0x3A <= ch) && (ch <= 0x40)) ||
         ((0x5B <= ch) && (ch <= 0x60)) ||
         ((0x7B <= ch) && (ch <= 0x7E))) {
        return TRUE;
    } else {
        return FALSE;
    }
}


int toupper(int c) {
    return is_lower(c) ? c - 'a' + 'A' : c;
}
 
int tolower(int c) {
    return is_upper(c) ? c - 'A' + 'a' : c;
}


char todigit(unsigned int value, unsigned int base) {
    if (base < 2 || base > 16 || value >= base)
        return '\0';

    if (value < 10)
        return value + '0';
    else
        return (value - 10) + 'a';
}

int fromdigit(char digit, unsigned int base) {
    int ret;

    if (base < 2 || base > 16)
        return ERRNO_CONV;

    digit = tolower(digit);
    if (is_digit(digit))
        ret = digit - '0';
    else
        ret = digit - 'a' + 10;

    return (ret >= 0 && ret < (int)base) ? ret : ERRNO_CONV;
}

int utostr(char* str, unsigned int n, unsigned int i, const char term) {

    int idx = 0;
    unsigned long tmp = i;
    int digit = 0;

    if (NULL == str) {
        return -1;
    }

    // at least fits 1 digit and term char
    if (n < 2) {
        return -1;
    }

    // increment index in str to where term char goes;
    //  following after rightmost digit
    do {
        tmp = tmp/10;
        idx++;
    } while (tmp != 0);

    // guarantee that this number will fit in the buffer
    if (idx >= n)
        return -1;

    // insert termination char
    str[idx--] = term;

    // move left through string, writing digits along the way
    do {
        digit = (i % 10);
        str[idx--] = '0' + digit;
        i /= 10;

    } while (i != 0);

    return 0;
}

int itostr(char* str, unsigned int n, int i, const char term) {

    int idx = 0;
    unsigned long tmp = 0;
    unsigned long i_pos = 0;
    int digit = 0;

    if (NULL == str) {
        return -1;
    }

    // at least fits 1 digit and term char
    if (n < 2) {
        return -1;
    }

    if (i < 0) {
        if (n < 3)
            return -1;
        str[idx++] = '-';
    }

    i_pos = i < 0 ? -i : i; // enure i_pos is always >= 0.
    tmp = i_pos;

    // increment index in str to where term char goes;
    //  following after rightmost digit
    do {
        tmp = tmp/10;
        idx++;
    } while (tmp != 0);

    // guarantee that this number will fit in the buffer
    if (idx >= n)
        return -1;

    // insert termination char
    str[idx--] = term;

    // move left through string, writing digits along the way
    do {
        digit = (i_pos % 10);
        str[idx--] = '0' + digit;
        i_pos /= 10;

    } while (i_pos != 0);

    return 0;
}

ssize_t strtou(const char *str, unsigned int base, unsigned int *result) {
    ssize_t ret = 0;
    unsigned long long acc = 0;
    int digit;

    if (base < 2 || base > 16)
        return ERRNO_CONV;

    while (*str && (digit = fromdigit(*str++, base)) != ERRNO_CONV) {
        if ((acc *= base) > UINT_MAX)
            return ERRNO_CONV;

        if ((unsigned long long)UINT_MAX - digit < acc)
            return ERRNO_CONV;

        acc += digit;
        ret++;
    }

    *result = acc;
    return ret;
}

ssize_t strtoi(const char *str, unsigned int base, int *result) {
    ssize_t ret;
    unsigned int u;
    int isnegative = 0;

    if (*str == '-')
        isnegative = 1;

    if ((ret = strtou(str + isnegative, base, &u)) == ERRNO_CONV)
        return ERRNO_CONV;

    if (u > ((unsigned int)INT_MAX + isnegative))
        return ERRNO_CONV;

    *result = isnegative ? -u : u;
    return ret + isnegative;
}

