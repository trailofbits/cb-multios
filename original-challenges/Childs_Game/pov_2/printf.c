#include <libpov.h>
#include "stdarg.h"
#include "stdint.h"
#include "stdio_private.h"

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
    memmove(buf, tmp, 20 - (buf - tmp));
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

static int _vsfprintf(const char *fmt, va_list ap, FILE *stream, char *buf, size_t buf_size)
{
    char ch;
    unsigned int num_size, field_size;
    size_t count = 0;
    char numbuf[64];
    size_t numbuflen;

#define OUTPUT_CHAR(_ch) \
    do { \
        if (count >= buf_size) { \
            if (count++ == SIZE_MAX) _terminate(1); \
            break; \
        } \
        char __ch = _ch; \
        if (stream) fwrite(&__ch, 1, stream); \
        if (buf) buf[count] = __ch; \
        count++; \
    } while (0)

#define OUTPUT_STRING(str, _sz) \
    do { \
        size_t sz = _sz; \
        if (count >= buf_size) { \
            if ((size_t)(count + sz) < (count)) _terminate(1); \
            count += sz; break; \
        } \
        size_t cnt = buf_size - count; \
        if (cnt > sz) cnt = sz; \
        if (stream) fwrite(str, cnt, stream); \
        if (buf) memcpy(buf + count, str, cnt); \
        if ((size_t)(count + sz) < (count)) _terminate(1); \
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
            field_size = strtoul(fmt, (char **)&fmt, 10);

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

            numbuflen = strlen(numbuf);
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
            OUTPUT_STRING(strarg, strlen(strarg));
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

    return (int)count;
}

int printf(const char *fmt, ...)
{
    int ret;
    va_list ap;

    va_start(ap, fmt);
    ret = vprintf(fmt, ap);
    va_end(ap);

    return ret;
}

int fprintf(FILE *stream, const char *fmt, ...)
{
    int ret;
    va_list ap;

    va_start(ap, fmt);
    ret = vfprintf(stream, fmt, ap);
    va_end(ap);

    return ret;
}

int sprintf(char *str, const char *fmt, ...)
{
    int ret;
    va_list ap;

    va_start(ap, fmt);
    ret = vsprintf(str, fmt, ap);
    va_end(ap);

    return ret;
}

int vprintf(const char *fmt, va_list ap)
{
    return vfprintf(stdout, fmt, ap);
}

int vfprintf(FILE *stream, const char *fmt, va_list ap)
{
    return _vsfprintf(fmt, ap, stream, NULL, INT_MAX);
}

int vsprintf(char *str, const char *fmt, va_list ap)
{
    return _vsfprintf(fmt, ap, NULL, str, INT_MAX);
}
