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
#include "cgc_stdint.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_stdio_private.h"

/*
 * This library can be customized using preprocessor defines:
 *  PRINTF_CHAR specifies the character to use instead of %
 *  PRINTF_N_CHAR specifies the character to use for %n, otherwise disabled
 */

#ifndef PRINTF_CHAR
#define PRINTF_CHAR '%'
#endif

static void _convert_unsigned(char *buf, unsigned x, int base, int upper)
{
    const char *numbers;
    char *tmp = buf + 20;

    if (upper)
        numbers = "0123456789ABCDEF";
    else
        numbers = "0123456789abcdef";

    /* NUL terminate */
    *(--tmp) = 0;

    if (x == 0)
        *(--tmp) = numbers[0];
    else
    {
        while (x)
        {
            *(--tmp) = numbers[x % base];
            x = x / base;
        }
    }

    /* move to beginning of buf */
    cgc_memmove(buf, tmp, 20 - (buf - tmp));
}

static void _convert_signed(char *buf, int x, int base, int upper)
{
    if (x < 0)
    {
        *buf++ = '-';
        x = -x;
    }

    _convert_unsigned(buf, x, base, upper);
}

static int cgc__vsfprintf(const char *fmt, va_list ap, FILE *stream, char *buf, cgc_size_t buf_size)
{
    char ch;
    unsigned int num_size, field_size;
    cgc_size_t count = 0;
    char numbuf[64];
    cgc_size_t numbuflen;

#define OUTPUT_CHAR(_ch) \
    do { \
        if (count >= buf_size) { \
            if (count++ == SIZE_MAX) cgc__terminate(1); \
            break; \
        } \
        char __ch = _ch; \
        if (stream) cgc_fwrite(&__ch, 1, stream); \
        if (buf) buf[count] = __ch; \
        count++; \
    } while (0)

#define OUTPUT_STRING(str, _sz) \
    do { \
        cgc_size_t sz = _sz; \
        if (count >= buf_size) { \
            if ((cgc_size_t)(count + sz) < (count)) cgc__terminate(1); \
            count += sz; break; \
        } \
        cgc_size_t cnt = buf_size - count; \
        if (cnt > sz) cnt = sz; \
        if (stream) cgc_fwrite(str, cnt, stream); \
        if (buf) cgc_memcpy(buf + count, str, cnt); \
        if ((cgc_size_t)(count + sz) < (count)) cgc__terminate(1); \
        count += sz; \
    } while (0)

    while ((ch = *fmt++))
    {
        char pad_char = ' ';
        const char *tmp, *strarg;
        unsigned int uintarg;
        int intarg;

        /* output non-format characters */
        while (ch != PRINTF_CHAR)
        {
            OUTPUT_CHAR(ch);
            if (!(ch = *fmt++))
                goto done;
        }

        tmp = fmt;
        num_size = 4;
        field_size = 0;

        /* field flags */
        switch ((ch = *fmt++))
        {
        case 0: /* NUL */
            goto done;
        case ' ':
            pad_char = ' ';
            break;
        case '0':
            pad_char = '0';
            break;
        default:
            fmt--;
            break;
        }

        /* field width */
        if (*fmt >= '0' && *fmt <= '9')
            field_size = cgc_strtoul(fmt, (char **)&fmt, 10);

        /* modifiers */
        switch ((ch = *fmt++))
        {
        case 0: /* NUL */
            goto done;
        case 'h':
            if (*fmt == 'h')
            {
                fmt++;
                num_size = 1;
            }
            else
            {
                num_size = 2;
            }
            break;
        case 'l':
            if (*fmt == 'l')
            {
                fmt++;
                num_size = 8;
                /* BUG: long long NOT supported */
            }
            else
            {
                num_size = 4;
            }
            break;
        default:
            fmt--;
            break;
        }

        /* conversion */
        switch ((ch = *fmt++))
        {
        case 0: /* NUL */
            OUTPUT_STRING(tmp, fmt - tmp);
            goto done;
        default: /* unrecognized format character */
            OUTPUT_STRING(tmp, fmt - tmp);
            break;
        case 'd':
        case 'u':
        case 'x':
        case 'X':
            if (ch == 'd')
            {
                if (num_size <= 4)
                    intarg = va_arg(ap, int);
                else goto done;

                _convert_signed(numbuf, intarg, 10, 0);
            }
            else
            {
                if (num_size <= 4)
                    uintarg = va_arg(ap, unsigned int);
                else goto done;

                _convert_unsigned(numbuf, uintarg, ch == 'u' ? 10 : 16, ch == 'X');
            }

            numbuflen = cgc_strlen(numbuf);
            if (numbuflen < field_size)
            {
                field_size -= numbuflen;
                do {
                    OUTPUT_CHAR(pad_char);
                    field_size--;
                } while (field_size > 0);
            }
            OUTPUT_STRING(numbuf, numbuflen);
            break;
        case 'c':
            ch = va_arg(ap, int);
            OUTPUT_CHAR(ch);
            break;
        case 's':
            strarg = va_arg(ap, const char *);
            OUTPUT_STRING(strarg, cgc_strlen(strarg));
            break;
#ifdef PRINTF_N_CHAR
        case PRINTF_N_CHAR:
            if (num_size == 1)
                *va_arg(ap, unsigned char *) = count;
            else if (num_size == 2)
                *va_arg(ap, unsigned short *) = count;
            else if (num_size == 4)
                *va_arg(ap, unsigned int *) = count;
            else goto done;
#endif
        }
    }

done:
    /* append NUL byte to buf, but not to the stream */
    stream = NULL;
    OUTPUT_CHAR('\0');

    return (int)count - 1; // - 1 since we don't count NULL
}

int cgc_printf(const char *fmt, ...)
{
    int ret;
    va_list ap;

    va_start(ap, fmt);
    ret = cgc_vprintf(fmt, ap);
    va_end(ap);

    return ret;
}

int cgc_fprintf(FILE *stream, const char *fmt, ...)
{
    int ret;
    va_list ap;

    va_start(ap, fmt);
    ret = cgc_vfprintf(stream, fmt, ap);
    va_end(ap);

    return ret;
}

int cgc_sprintf(char *str, const char *fmt, ...)
{
    int ret;
    va_list ap;

    va_start(ap, fmt);
    ret = cgc_vsprintf(str, fmt, ap);
    va_end(ap);

    return ret;
}

int cgc_vprintf(const char *fmt, va_list ap)
{
    return cgc_vfprintf(cgc_stdout, fmt, ap);
}

int cgc_vfprintf(FILE *stream, const char *fmt, va_list ap)
{
    int retval, buffered = 1;
    // switch to buffered mode temporarily
    if (stream->idx == -1)
    {
        buffered = 0;
        stream->idx = 0;
    }
    retval = cgc__vsfprintf(fmt, ap, stream, NULL, INT_MAX);
    if (!buffered)
    {
        cgc_fflush(stream);
        stream->idx = -1;
    }
    return retval;
}

int cgc_vsprintf(char *str, const char *fmt, va_list ap)
{
    return cgc__vsfprintf(fmt, ap, NULL, str, INT_MAX);
}
