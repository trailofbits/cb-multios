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

#include "cgc_conv.h"
#include "cgc_limits.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_stdio.h"

struct FILE {
    int fd;
    enum mode mode;
    unsigned char *buf;
    cgc_size_t bufsize;
    cgc_size_t bufpos;
};

#define BUFSIZE 256
static unsigned char stdbuf[3][BUFSIZE];

static FILE stdfiles[3] = {
    { STDIN, READ, stdbuf[0], BUFSIZE, 0 },
    { STDOUT, WRITE, stdbuf[1], BUFSIZE, 0 },
    { STDERR, WRITE, stdbuf[2], BUFSIZE, 0 }
};

FILE *cgc_stdin = &stdfiles[0];
FILE *cgc_stdout = &stdfiles[1];
FILE *cgc_stderr = &stdfiles[2];

cgc_ssize_t
cgc_read_all(int fd, void *ptr, cgc_size_t size)
{
    cgc_ssize_t ret = 0;
    cgc_size_t bytes_rx;

    if (size > SSIZE_MAX)
        return EXIT_FAILURE;

    while (size) {
        if (cgc_receive(fd, (unsigned char *)ptr + ret, size, &bytes_rx) != 0
                || bytes_rx == 0)
            return EXIT_FAILURE;

        size -= bytes_rx;
        ret += bytes_rx;
    }

    return ret;
}

cgc_ssize_t
cgc_read_until(int fd, void *ptr, unsigned char delim, cgc_size_t size)
{
    cgc_ssize_t ret = 0;
    cgc_size_t bytes_rx;

    if (size > SSIZE_MAX)
        return EXIT_FAILURE;

    while (ret < (cgc_ssize_t)size - 1) {
        if (cgc_receive(fd, (unsigned char *)ptr + ret, 1, &bytes_rx) != 0
                || bytes_rx == 0)
            return EXIT_FAILURE;

        if (*((unsigned char *)ptr + ret) == delim)
            break;

        ret += bytes_rx;
    }

    *((unsigned char *)ptr + ret) = '\0';
    return ret;
}

cgc_ssize_t
cgc_write_all(int fd, const void *ptr, cgc_size_t size)
{
    cgc_ssize_t ret = 0;
    cgc_size_t bytes_tx;

    if (size > SSIZE_MAX)
        return EXIT_FAILURE;

    while (size) {
        if (cgc_transmit(fd, (const unsigned char *)ptr + ret, size, &bytes_tx) != 0 ||
                bytes_tx == 0)
            return EXIT_FAILURE;

        size -= bytes_tx;
        ret += bytes_tx;
    }

    return ret;
}

int
cgc_fflush(FILE *stream)
{
    cgc_ssize_t written;

    if (!stream || !stream->mode == WRITE)
        return EXIT_FAILURE;

    if (!stream->buf || stream->bufpos == 0)
        return EXIT_SUCCESS;

    written = cgc_write_all(stream->fd, stream->buf, stream->bufpos);
    if (written < 0)
        return written;

    stream->bufpos -= written;
    return EXIT_SUCCESS;
}

cgc_ssize_t
cgc_fread(void *ptr, cgc_size_t size, FILE *stream)
{
    //TEMP
    return cgc_read_all(stream->fd, ptr, size);
}

cgc_ssize_t
cgc_fread_until(void *ptr, unsigned char delim, cgc_size_t size, FILE *stream)
{
    //TEMP
    return cgc_read_until(stream->fd, ptr, delim, size);
}

cgc_ssize_t
cgc_fwrite(const void *ptr, cgc_size_t size, FILE *stream)
{
    //TEMP
    return cgc_write_all(stream->fd, ptr, size);
}

int
cgc_fgetc(FILE *stream)
{
    char c;
    cgc_ssize_t cgc_read;

    cgc_read = cgc_fread(&c, 1, stream);
    if (cgc_read < 0)
        return cgc_read;

    return c;
}

int
cgc_fputc(int character, FILE *stream)
{
    return cgc_fwrite(&character, 1, stream);
}

static int
cgc_printf_core(const char *format, void (*printfn)(char c, void *data),
        void *data, va_list args)
{
    int ret = 0;
    char c, f, buf[32];
    cgc_size_t buflen;
    const char *s = NULL;

    while ((f = *format++)) {
        if (f != '%') {
            printfn(f, data);
            ret++;
        } else {
            switch ((f = *format++)) {
            case '%':
                printfn(f, data);
                ret++;
                break;
            case 'c':
                c = va_arg(args, int);
                printfn(c, data);
                ret++;
                break;
            case 's':
                s = va_arg(args, char *);
                break;
            case 'f':
                if (cgc_dtostr(va_arg(args, double), buf, sizeof(buf)) != EXIT_SUCCESS)
                    return EXIT_FAILURE;
                s = buf;
                break;
            case 'd':
                if (cgc_itostr(va_arg(args, int), 10, 0, buf, sizeof(buf)) != EXIT_SUCCESS)
                    return EXIT_FAILURE;
                s = buf;
                break;
            case 'u':
                if (cgc_utostr(va_arg(args, unsigned int), 10, 0, buf, sizeof(buf)) != EXIT_SUCCESS)
                    return EXIT_FAILURE;
                s = buf;
                break;
            case 'x':
            case 'X':
                if (cgc_utostr(va_arg(args, unsigned int), 16, cgc_isupper(f), buf, sizeof(buf)) != EXIT_SUCCESS)
                    return EXIT_FAILURE;

                // Pad out with 8 zeros
                if ((buflen = cgc_strlen(buf)) < 2 * sizeof(unsigned int)) {
                    cgc_memmove(buf + (2 * sizeof(unsigned int) - buflen), buf, buflen + 1);
                    cgc_memset(buf, '0', 2 * sizeof(unsigned int) - buflen);
                }

                s = buf;
                break;
            default:
                return EXIT_FAILURE;
            }

            while (s && *s) {
                printfn(*s++, data);
                ret++;
            }

            s = NULL;
        }
    }

    return ret;
}

static void
cgc_file_printer(char c, void *data)
{
    cgc_fputc(c, data);
}

struct string_printer_ctx {
    char *s;
    cgc_size_t num;
};

static void
cgc_string_printer(char c, void *data)
{
    struct string_printer_ctx *ctx = data;
    if (ctx->num--)
        *ctx->s++ = c;
}

int
cgc_vfprintf(FILE *stream, const char *format, va_list args)
{
    return cgc_printf_core(format, cgc_file_printer, stream, args);
}

int
cgc_vprintf(const char *format, va_list args) 
{
    return cgc_vfprintf(cgc_stdout, format, args);
}

int
cgc_vsnprintf(char *s, cgc_size_t num, const char *format, va_list args)
{
    struct string_printer_ctx ctx = { s, num };
    return cgc_printf_core(format, cgc_string_printer, &ctx, args);
}

int
cgc_vsprintf(char *s, const char *format, va_list args)
{
    return cgc_vsnprintf(s, (cgc_size_t)SIZE_MAX, format, args);
}

int
cgc_fprintf(FILE *stream, const char *format, ...)
{
    int ret;
    va_list args;
    va_start(args, format);
    ret = cgc_vfprintf(stream, format, args);
    va_end(args);
    return ret;
}

int
cgc_printf(const char *format, ...)
{
    int ret;
    va_list args;
    va_start(args, format);
    ret = cgc_vprintf(format, args);
    va_end(args);
    return ret;
}

int
cgc_snprintf(char *s, cgc_size_t num, const char *format, ...)
{
    int ret;
    va_list args;
    va_start(args, format);
    ret = cgc_vsnprintf(s, num, format, args);
    va_end(args);
    return ret;
}

int
cgc_sprintf(char *s, const char *format, ...)
{
    int ret;
    va_list args;
    va_start(args, format);
    ret = cgc_vsprintf(s, format, args);
    va_end(args);
    return ret;
}

