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
#include "cgc_stdlib.h"
#include "cgc_stdarg.h"
#include "cgc_string.h"

#define OUTPUT_BYTE(x) do { \
    cgc_size_t bytes; \
    char _c = x; \
    cgc_transmit(STDOUT, &_c, sizeof(_c), &bytes); \
} while (0);

#define NUM_TO_LOWER(x) (((x) < 10 ? (x)+'0' : (x)-10+'a'))
#define NUM_TO_UPPER(x) (((x) < 10 ? (x)+'0' : (x)-10+'A'))

#define FLAG_PAD_ZERO 0x1
#define FLAG_UPPERCASE 0x2
int cgc_output_number(unsigned int x, int base, int min, unsigned int flags)
{
    int n = 0;
    if (x >= base)
    {
        n = cgc_output_number(x / base, base, min-1, flags);
        x %= base;
    }
    if (n == 0 && min > 0)
    {
        while (--min)
            if (flags & FLAG_PAD_ZERO)
                OUTPUT_BYTE('0')
            else
                OUTPUT_BYTE(' ')
    }

    if (flags & FLAG_UPPERCASE)
        OUTPUT_BYTE(NUM_TO_UPPER(x))
    else
        OUTPUT_BYTE(NUM_TO_LOWER(x))
    return n + 1;
}

int cgc_send_n_bytes(int fd, cgc_size_t n, char *buf)
{
    if (!n || !buf)
        return -1;

    cgc_size_t tx = 0, total_sent = 0;

    while (total_sent < n) {
        if (cgc_transmit(fd, buf + total_sent, n - total_sent, &tx) != 0) {
            return -1;
        } else {
            total_sent += tx;
        }
    }

    return total_sent;
}

int cgc_printf(const char *fmt, ...)
{
    char *astring;
    int aint, i, n = 0, flags = 0, min = 0;
    unsigned int auint;
    va_list ap;
    va_start(ap, fmt);

    while (*fmt != '\0')
    {
        char c = *fmt++;
        if (c == '%')
        {
            while (1)
            {
                c = *fmt++;
                switch (c)
                {
                case '0':
                    flags |= FLAG_PAD_ZERO;
                    continue;
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    min = cgc_strtol(fmt-1, (char**)&fmt, 10);
                    continue;
                }
                break;
            }
            switch (c)
            {
            case '%':
                OUTPUT_BYTE('%')
                break;
            case 's':
                astring = va_arg(ap, char *);
//                for (i = 0; i < cgc_strlen(astring); i++)
//                    OUTPUT_BYTE(astring[i]);
                cgc_send_n_bytes(STDOUT, astring, cgc_strlen(astring));
                break;
            case 'd':
                aint = va_arg(ap, int);
                if (aint < 0)
                {
                    OUTPUT_BYTE('-')
                    aint = -aint;
                }
                cgc_output_number(aint, 10, min, flags);
                break;
            case 'X':
                flags |= FLAG_UPPERCASE;
            case 'x':
                auint = va_arg(ap, unsigned int);
                cgc_output_number(auint, 16, min, flags);
                break;
            default:
                OUTPUT_BYTE(c)
                break;
            }
            min = 0;
            flags = 0;
        }
        else
        {
            OUTPUT_BYTE(c)
        }
    }

    va_end(ap);
    return n;
}

#undef OUTPUT_BYTE
