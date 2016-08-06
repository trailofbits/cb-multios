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
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

typedef int (*consumer_t) (void *arg, const char *buf, size_t n);

static char *_print_base(char *outend, int *n, unsigned int val, unsigned int base, int uppercase)
{
    *n = 0;
    if (base < 2 || base > 16)
        return outend;

    if (val == 0)
    {
        *n = 1;
        *(--outend) = '0';
        return outend;
    }

    const char *str;
    if (uppercase)
        str = "0123456789ABCDEF";
    else
        str = "0123456789abcdef";

    while (val > 0)
    {
        (*n)++;
        *(--outend) = str[val % base];
        val /= base;
    }

    return outend;
}

static char *_print_signed(char *outbuf, int *n, int val)
{
    int neg = 0;
    if (val < 0)
    {
        neg = 1;
        val = -val;
    }
    char *s = _print_base(outbuf, n, (unsigned int)val, 10, 0);
    if (neg)
    {
        *(--s) = '-';
        (*n)++;
    }
    return s;
}

static int _printf(consumer_t consumer, void *arg, const char *fmt, va_list ap)
{
    char tmpbuf[32]; /* must be at least 32 bytes for _print_base */
    const char *fmtstr = NULL;
    char modifier = 0;
    int n, total = 0;

#define CONSUME(b, c) \
    do { \
        size_t tmp = (size_t)(c); \
        if (tmp == 0) break; \
        total += (n = consumer(arg, (b), tmp)); \
        if (n < 0) goto error; \
        if (n < tmp) goto done; \
    } while (0)

#define FLUSH() \
    do { \
        if (fmtstr) { \
            CONSUME(fmtstr, fmt-fmtstr); \
            fmtstr = NULL; \
        } \
    } while (0)

    while (*fmt)
    {
        int flags = 0;
#define FLAG_ZERO_PADDING 0x01
        unsigned int field_width = 0;

        if (*fmt != '%')
        {
            if (fmtstr == NULL)
                fmtstr = fmt;
            fmt++;
            continue;
        }

        FLUSH();

        fmt++;
        if (*fmt == '%')
        {
            CONSUME(fmt, 1);
            fmt++;
            continue;
        }

        /* process flags */
        while (1)
        {
            switch (*fmt)
            {
            case '0':
                flags |= FLAG_ZERO_PADDING;
                fmt++;
                break;
            default:
                goto flags_done;
            }
        }

flags_done:
        /* process field width */
        field_width = strtoul(fmt, (char **)&fmt, 10);

        /* process modifiers */
        switch (*fmt)
        {
        case 'H':
        case 'h':
        case 'l':
            modifier = *fmt;
            fmt++;
            break;
        }

        /* process conversion */
        char *tmpstr;
        int base, outlen, sv;
        unsigned int uv;
        void *pv;
        switch(*fmt)
        {
        case 'd':
        case 'i':
            sv = va_arg(ap, int);
            if (modifier == 'h') sv = (short)(sv & 0xffff);
            else if (modifier == 'H') sv = (signed char)(sv & 0xff);
            tmpstr = _print_signed(tmpbuf + 32, &outlen, sv);
            while (field_width > outlen)
            {
                CONSUME((flags & FLAG_ZERO_PADDING) ? "0" : " ", 1);
                field_width--;
            }
            CONSUME(tmpstr, outlen);
            fmt++;
            break;
        case 'u':
        case 'o':
        case 'x':
        case 'X':
            if (*fmt == 'u') base = 10;
            else if(*fmt == 'o') base = 8;
            else base = 16;
            uv = va_arg(ap, unsigned int);
            if (modifier == 'h') uv &= 0xffff;
            else if (modifier == 'H') uv &= 0xff;
            tmpstr = _print_base(tmpbuf + 32, &outlen, uv, base, *fmt == 'X');
            while (field_width > outlen)
            {
                CONSUME((flags & FLAG_ZERO_PADDING) ? "0" : " ", 1);
                field_width--;
            }
            CONSUME(tmpstr, outlen);
            fmt++;
            break;
        case 'n':
            pv = va_arg(ap, void *);
            if (modifier == 'h') *(short int *)pv = total;
            else if (modifier == 'H') *(signed char *)pv = total;
            else *(int *)pv = total;
            fmt++;
            break;
        case 's':
            pv = va_arg(ap, void *);
            CONSUME((char *)pv, strlen((char *)pv));
            fmt++;
            break;
        }
    }
    FLUSH();

done:
    return total;
error:
    return -1;
}

static int _consumer_fd(void *arg, const char *buf, size_t n)
{
    return writeall((int)arg, buf, n);
}

static int _consumer_string(void *arg, const char *buf, size_t n)
{
    char **s = (char **)arg;
    memcpy(*s, buf, n);
    (*s) += n;
    **s = '\0';
    return (int)n;
}

typedef struct {
    char *buf;
    size_t bytes_remaining;
} string_info_t;

static int _consumer_string_checked(void *arg, const char *buf, size_t n)
{
    string_info_t *sinfo = arg;
    if (n > sinfo->bytes_remaining)
        n = sinfo->bytes_remaining;
    if (n == 0)
        return 0;
    memcpy(sinfo->buf, buf, n);
    sinfo->buf += n;
    sinfo->buf[0] = '\0';
    sinfo->bytes_remaining -= n;
    return (int)n;
}

int fdprintf(int fd, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int ret = _printf(_consumer_fd, (void *)fd, fmt, ap);
    va_end(ap);
    return ret;
}

int sprintf(char *s, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int ret = _printf(_consumer_string, (void *)&s, fmt, ap);
    va_end(ap);
    return ret;
}

int vsnprintf(char *s, size_t size, const char *fmt, va_list ap)
{
    if (size == 0)
        return 0;

    string_info_t sinfo;
    sinfo.buf = s;
    sinfo.bytes_remaining = size - 1; /* room for NULL byte */
    return _printf(_consumer_string_checked, (void *)&sinfo, fmt, ap);
}

int snprintf(char *s, size_t size, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int ret = vsnprintf(s, size, fmt, ap);
    va_end(ap);
    return ret;
}

