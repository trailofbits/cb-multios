/*
 * Copyright (c) 2014-2015 Kaprica Security, Inc.
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
#include "interp.h"

#define OUTPUT_BYTE(x) do { \
    size_t bytes; \
    char _c = x; \
    transmit(fd, &_c, sizeof(_c), &bytes); \
} while (0);

#define NUM_TO_LOWER(x) (((x) < 10 ? (x)+'0' : (x)-10+'a'))
#define NUM_TO_UPPER(x) (((x) < 10 ? (x)+'0' : (x)-10+'A'))

#define FLAG_PAD_ZERO 0x1
#define FLAG_UPPERCASE 0x2
static int output_number_printf(int fd, unsigned int x, int base, int min, unsigned int flags)
{
    int n = 0;
    if (x >= base)
    {
        n = output_number_printf(fd, x / base, base, min-1, flags);
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

int eprintf(int fd, const char *fmt, var_t *args, unsigned int cnt)
{
    const char *astring;
    char achar;
    int aint, i, n = 0, flags = 0, min = 0;
    unsigned int auint, narg = 0;

#define NEXT_ARG(name, ctype, vtype) do { \
        var_t *v; \
        if (narg >= cnt) \
            return -1; \
        v = &args[narg++]; \
        if (vtype == VAR_STRING && v->type == VAR_NULL) \
            (name) = (ctype) ""; \
        else if (vtype == VAR_NUMBER && v->type == VAR_NULL) \
            (name) = (ctype) 0; \
        else if (vtype == VAR_NUMBER) \
            (name) = (ctype) v->v_number.value; \
        else if (vtype == VAR_STRING) \
            (name) = (ctype) v->v_string.value; \
        else \
            return -1; \
    } while (0)

    while (*fmt != '\0')
    {
        char c = *fmt++;
        if (c == '#')
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
                    min = strtol(fmt-1, (char**)&fmt, 10);
                    continue;
                }
                break;
            }
            switch (c)
            {
            case '#':
                OUTPUT_BYTE('#')
                break;
            case 's':
                NEXT_ARG(astring, const char *, VAR_STRING);
#if PATCHED
                if (args[narg-1].type == VAR_NUMBER)
                    return -1;
#endif
                for (i = 0; i < strlen(astring); i++)
                    OUTPUT_BYTE(astring[i]);
                break;
            case 'd':
                NEXT_ARG(aint, int, VAR_NUMBER);
                if (aint < 0)
                {
                    OUTPUT_BYTE('-')
                    aint = -aint;
                }
                output_number_printf(fd, aint, 10, min, flags);
                break;
            case 'u':
                NEXT_ARG(auint, unsigned int, VAR_NUMBER);
                output_number_printf(fd, auint, 10, min, flags);
                break;
            case 'X':
                flags |= FLAG_UPPERCASE;
            case 'x':
                NEXT_ARG(auint, unsigned int, VAR_NUMBER);
                output_number_printf(fd, auint, 16, min, flags);
                break;
            case 'c':
                NEXT_ARG(achar, int, VAR_NUMBER);
                OUTPUT_BYTE(achar);
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

    return n;
}

#undef OUTPUT_BYTE
