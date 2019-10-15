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

#include "libcgc.h"

#include "cgc_limits.h"
#include "cgc_math.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_conv.h"

int
cgc_isdigit(int c)
{
    return c >= '0' && c <= '9';
}

int
cgc_ishexdigit(int c)
{
    return cgc_isdigit(c) ||
        (c >= 'a' && c <= 'f') ||
        (c >= 'A' && c <= 'F');
}

int
cgc_isalpha(int c)
{
    return cgc_isupper(c) || cgc_islower(c);
}

int
cgc_islower(int c)
{
    return c >= 'a' && c <= 'z';
}

int
cgc_isupper(int c)
{
    return c >= 'A' && c <= 'Z';
}

int
cgc_toupper(int c)
{
    return cgc_islower(c) ? c - 'a' + 'A' : c;
}
 
int
cgc_tolower(int c)
{
    return cgc_isupper(c) ? c - 'A' + 'a' : c;
}

char
cgc_todigit(unsigned int value, unsigned int base)
{
    if (base < 2 || base > 16 || value >= base)
        return '\0';

    if (value < 10)
        return value + '0';
    else
        return (value - 10) + 'a';
}

int
cgc_fromdigit(char digit, unsigned int base)
{
    int ret;

    if (base < 2 || base > 16)
        return EXIT_FAILURE;

    digit = cgc_tolower(digit);
    if (cgc_isdigit(digit))
        ret = digit - '0';
    else
        ret = digit - 'a' + 10;

    return (ret >= 0 && ret < (int)base) ? ret : EXIT_FAILURE;
}

int
cgc_utostr(unsigned int value, unsigned int base, int uppercase, char *str, cgc_size_t num)
{
    unsigned int i, tmp;
    cgc_size_t len = 1;

    if (base < 2 || base > 16 || num < 1)
        return EXIT_FAILURE;

    tmp = value;
    while (tmp /= base)
        len++;

    if (len >= num)
        return EXIT_FAILURE;

    for (i = 0; i < len; i++) {
        str[len - i - 1] = cgc_todigit(value % base, base);
        value /= base;

        if (uppercase)
            str[len - i - 1] = cgc_toupper(str[len - i - 1]);
    }

    str[len] = '\0';
    return EXIT_SUCCESS;
}

int
cgc_itostr(int value, unsigned int base, int uppercase, char *str, cgc_size_t num)
{
    if (num < (value < 0 ? 2 : 1))
        return EXIT_FAILURE;

    if (value < 0) {
        *str++ = '-';
        num--;
    }

    return cgc_utostr(value < 0 ? -value : value, base, uppercase, str, num);
}

int
cgc_dtostr(double value, char *str, cgc_size_t num)
{
    unsigned int i, fractional_len;
    char fractional_buf[DTOSTR_PRECISION + 1];
    unsigned int whole_part, fractional_part;

    if (cgc_isnan(value)) {
        if (num < 4)
            return EXIT_FAILURE;

        cgc_strncpy(str, "nan", 4);
        return EXIT_SUCCESS;
    }

    if (cgc_sign(value)) {
        if (num < 2)
            return EXIT_FAILURE;

        *str++ = '-';
        num--;
        value = cgc_abs(value);
    }

    if (cgc_isinf(value)) {
        if (num < 4)
            return EXIT_FAILURE;

        cgc_strncpy(str, "inf", 4);
        return EXIT_SUCCESS;
    }

    // Space for decimal point and null terminator
    if (value >= UINT_MAX + 1.0 || num < 2 + DTOSTR_PRECISION)
        return EXIT_FAILURE;

    whole_part = value;
    fractional_part = (value - whole_part) * cgc_pow(10.0, DTOSTR_PRECISION);

    if (cgc_utostr(fractional_part, 10, 0, fractional_buf, sizeof(fractional_buf)) != 0)
        return EXIT_FAILURE;

    if (cgc_utostr(whole_part, 10, 0, str, num - DTOSTR_PRECISION - 1) != 0)
        return EXIT_FAILURE;

    str += cgc_strlen(str);
    *str++ = '.';

    fractional_len = cgc_strlen(fractional_buf);
    for (i = 0; i < DTOSTR_PRECISION - fractional_len; i++)
        *str++ = '0';

    cgc_strcpy(str, fractional_buf);
    return EXIT_SUCCESS;
}

cgc_ssize_t
cgc_strtou(char *str, unsigned int base, unsigned int *result)
{
    cgc_ssize_t ret = 0;
    unsigned long long acc = 0;
    int digit;

    if (base < 2 || base > 16)
        return EXIT_FAILURE;

    while (*str && (digit = cgc_fromdigit(*str++, base)) != EXIT_FAILURE) {
        if ((acc *= base) > UINT_MAX)
            return EXIT_FAILURE;

        if ((unsigned long long)UINT_MAX - digit < acc)
            return EXIT_FAILURE;

        acc += digit;
        ret++;
    }

    *result = acc;
    return ret;
}

cgc_ssize_t
cgc_strtoi(char *str, unsigned int base, int *result)
{
    cgc_ssize_t ret;
    unsigned int u;
    int isnegative = 0;

    if (*str == '-')
        isnegative = 1;

    if ((ret = cgc_strtou(str + isnegative, base, &u)) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (u > ((unsigned int)INT_MAX + isnegative))
        return EXIT_FAILURE;

    *result = isnegative ? -u : u;
    return ret + isnegative;
}


cgc_ssize_t
cgc_strtod(char *str, double *result)
{
    cgc_ssize_t ret, frac_size = 0;
    int whole_part;
    unsigned int frac_part = 0;
    char *frac_str;

    if ((frac_str = cgc_strrchr(str, '.')) != NULL)
        *frac_str++ = '\0';

    if ((ret = cgc_strtoi(str, 10, &whole_part)) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (frac_str && (frac_size = cgc_strtou(frac_str, 10, &frac_part)) == EXIT_FAILURE)
        return EXIT_FAILURE;

    *result = whole_part < 0 ? -(double)frac_part : (double)frac_part;
    *result /= cgc_pow(10.0, frac_size);
    *result += (double)whole_part;

    return ret + (frac_str ? 1 + frac_size : 0);
}

