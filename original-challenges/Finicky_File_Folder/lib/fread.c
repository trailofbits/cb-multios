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
#include <string.h>
#include "stdio_private.h"

static int _refill(FILE *stream)
{
    size_t rx;

    if (stream->idx == stream->length)
        stream->idx = stream->length = 0;

    if (receive(stream->fd, &stream->buffer[stream->length], sizeof(stream->buffer) - stream->length, &rx) != 0 ||
        rx == 0)
    {
        return -1;
    }

    stream->length = rx;
    xlat(stream->xlat_map_inv, stream->buffer, stream->length);

    return rx;
}

ssize_t fread(void *ptr, size_t size, FILE *stream)
{
    char *buf = ptr;
    size_t idx = 0, rx;

    if (stream->idx == stream->length)
        _refill(stream);

    /* copy from the buffered input first */
    if (stream->idx != INVALID_IDX)
    {
        rx = stream->length - stream->idx;
        if (rx > size)
            rx = size;

        memcpy(buf, stream->buffer + stream->idx, rx);
        idx += rx;
        stream->idx += rx;

        if (stream->idx == stream->length)
            stream->idx = stream->length = 0;
    }

    /* read in the remaining bytes as quickly as possible */
    for (; idx < size; idx += rx)
    {
        if (receive(stream->fd, buf + idx, size - idx, &rx) != 0 || rx == 0)
            return -1;
        xlat(stream->xlat_map_inv, buf + idx, rx);
    }

    return idx;
}

static int _getc(FILE *stream)
{
    char ch;
    size_t rx;

    if (stream->idx == INVALID_IDX)
    {
        /* unbuffered read */
        if (receive(stream->fd, &ch, 1, &rx) != 0 || rx == 0)
            return -1;
        xlat(stream->xlat_map_inv, &ch, 1);
        return (int)(unsigned char)ch;
    }
    else
    {
        /* buffered read */
        if (stream->idx == stream->length)
        {
            if (_refill(stream) < 0)
                return -1;
        }

        return (int)(unsigned char)stream->buffer[stream->idx++];
    }
}

ssize_t freaduntil(char *str, size_t size, char term, FILE *stream)
{
    size_t idx;

    for (idx = 0; idx < size - 1; idx++)
    {
        int ch = _getc(stream);
        if (ch == -1)
            return -1;
        else if (ch == term)
            break;
        else
            str[idx] = ch;
    }

    if (idx == size - 1)
    {
        int ch;
        do {
            ch = _getc(stream);
            if (ch == -1)
                return -1;
        } while (ch != term);
    }

    str[idx] = 0;
    return idx;
}
