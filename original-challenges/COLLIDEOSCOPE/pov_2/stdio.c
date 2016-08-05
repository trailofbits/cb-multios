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

#include "conv.h"
#include "limits.h"
#include "stdlib.h"
#include "string.h"

#include "stdio.h"

struct FILE {
    int fd;
    enum mode mode;
    unsigned char *buf;
    size_t bufsize;
    size_t bufpos;
};

#define BUFSIZE 256
static unsigned char stdbuf[3][BUFSIZE];

static FILE stdfiles[3] = {
    { STDIN, READ, stdbuf[0], BUFSIZE, 0 },
    { STDOUT, WRITE, stdbuf[1], BUFSIZE, 0 },
    { STDERR, WRITE, stdbuf[2], BUFSIZE, 0 }
};

FILE *stdin = &stdfiles[0];
FILE *stdout = &stdfiles[1];
FILE *stderr = &stdfiles[2];

ssize_t
read_all(int fd, void *ptr, size_t size)
{
    ssize_t ret = 0;
    size_t bytes_rx;

    if (size > SSIZE_MAX)
        return EXIT_FAILURE;

    while (size) {
        if (receive(fd, (unsigned char *)ptr + ret, size, &bytes_rx) != 0
                || bytes_rx == 0)
            return EXIT_FAILURE;

        size -= bytes_rx;
        ret += bytes_rx;
    }

    return ret;
}

ssize_t
read_until(int fd, void *ptr, unsigned char delim, size_t size)
{
    ssize_t ret = 0;
    size_t bytes_rx;

    if (size > SSIZE_MAX)
        return EXIT_FAILURE;

    while (ret < (ssize_t)size - 1) {
        if (receive(fd, (unsigned char *)ptr + ret, 1, &bytes_rx) != 0
                || bytes_rx == 0)
            return EXIT_FAILURE;

        if (*((unsigned char *)ptr + ret) == delim)
            break;

        ret += bytes_rx;
    }

    *((unsigned char *)ptr + ret) = '\0';
    return ret;
}

ssize_t
write_all(int fd, const void *ptr, size_t size)
{
    ssize_t ret = 0;
    size_t bytes_tx;

    if (size > SSIZE_MAX)
        return EXIT_FAILURE;

    while (size) {
        if (transmit(fd, (const unsigned char *)ptr + ret, size, &bytes_tx) != 0 ||
                bytes_tx == 0)
            return EXIT_FAILURE;

        size -= bytes_tx;
        ret += bytes_tx;
    }

    return ret;
}

int
fflush(FILE *stream)
{
    ssize_t written;

    if (!stream || !stream->mode == WRITE)
        return EXIT_FAILURE;

    if (!stream->buf || stream->bufpos == 0)
        return EXIT_SUCCESS;

    written = write_all(stream->fd, stream->buf, stream->bufpos);
    if (written < 0)
        return written;

    stream->bufpos -= written;
    return EXIT_SUCCESS;
}

ssize_t
fread(void *ptr, size_t size, FILE *stream)
{
    //TEMP
    return read_all(stream->fd, ptr, size);
}

ssize_t
fread_until(void *ptr, unsigned char delim, size_t size, FILE *stream)
{
    //TEMP
    return read_until(stream->fd, ptr, delim, size);
}

ssize_t
fwrite(const void *ptr, size_t size, FILE *stream)
{
    //TEMP
    return write_all(stream->fd, ptr, size);
}

int
fgetc(FILE *stream)
{
    char c;
    ssize_t read;

    read = fread(&c, 1, stream);
    if (read < 0)
        return read;

    return c;
}

int
fputc(int character, FILE *stream)
{
    return fwrite(&character, 1, stream);
}

static int
printf_core(const char *format, void (*printfn)(char c, void *data),
        void *data, va_list args)
{
    int ret = 0;
    char c, f, buf[32];
    size_t buflen;
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
                if (dtostr(va_arg(args, double), buf, sizeof(buf)) != EXIT_SUCCESS)
                    return EXIT_FAILURE;
                s = buf;
                break;
            case 'd':
                if (itostr(va_arg(args, int), 10, 0, buf, sizeof(buf)) != EXIT_SUCCESS)
                    return EXIT_FAILURE;
                s = buf;
                break;
            case 'u':
                if (utostr(va_arg(args, unsigned int), 10, 0, buf, sizeof(buf)) != EXIT_SUCCESS)
                    return EXIT_FAILURE;
                s = buf;
                break;
            case 'x':
            case 'X':
                if (utostr(va_arg(args, unsigned int), 16, isupper(f), buf, sizeof(buf)) != EXIT_SUCCESS)
                    return EXIT_FAILURE;

                // Pad out with 8 zeros
                if ((buflen = strlen(buf)) < 2 * sizeof(unsigned int)) {
                    memmove(buf + (2 * sizeof(unsigned int) - buflen), buf, buflen + 1);
                    memset(buf, '0', 2 * sizeof(unsigned int) - buflen);
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
file_printer(char c, void *data)
{
    fputc(c, data);
}

struct string_printer_ctx {
    char *s;
    size_t num;
};

static void
string_printer(char c, void *data)
{
    struct string_printer_ctx *ctx = data;
    if (ctx->num--)
        *ctx->s++ = c;
}

int
vfprintf(FILE *stream, const char *format, va_list args)
{
    return printf_core(format, file_printer, stream, args);
}

int
vprintf(const char *format, va_list args) 
{
    return vfprintf(stdout, format, args);
}

int
vsnprintf(char *s, size_t num, const char *format, va_list args)
{
    struct string_printer_ctx ctx = { s, num };
    return printf_core(format, string_printer, &ctx, args);
}

int
vsprintf(char *s, const char *format, va_list args)
{
    return vsnprintf(s, (size_t)SIZE_MAX, format, args);
}

int
fprintf(FILE *stream, const char *format, ...)
{
    int ret;
    va_list args;
    va_start(args, format);
    ret = vfprintf(stream, format, args);
    va_end(args);
    return ret;
}

int
printf(const char *format, ...)
{
    int ret;
    va_list args;
    va_start(args, format);
    ret = vprintf(format, args);
    va_end(args);
    return ret;
}

int
snprintf(char *s, size_t num, const char *format, ...)
{
    int ret;
    va_list args;
    va_start(args, format);
    ret = vsnprintf(s, num, format, args);
    va_end(args);
    return ret;
}

int
sprintf(char *s, const char *format, ...)
{
    int ret;
    va_list args;
    va_start(args, format);
    ret = vsprintf(s, format, args);
    va_end(args);
    return ret;
}

