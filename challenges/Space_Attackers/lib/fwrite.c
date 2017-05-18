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
#include "cgc_string.h"
#include "cgc_stdio_private.h"

cgc_ssize_t cgc_fwrite(const void *ptr, cgc_size_t size, FILE *stream)
{
    const char *buf = ptr;
    cgc_size_t idx = 0, tx;

    if (stream->idx == INVALID_IDX)
    {
unbuffered:
        if (cgc_transmit_all(stream->fd, ptr, size) != 0)
            return -1;
        return size;
    }
    else
    {
        if (size >= sizeof(stream->buffer))
        {
            cgc_fflush(stream);
            goto unbuffered;
        }

        if (stream->length + size >= sizeof(stream->buffer))
        {
            tx = sizeof(stream->buffer) - stream->length;
            cgc_memcpy(stream->buffer + stream->length, buf, tx);
            stream->length += tx;
            idx += tx;

            cgc_fflush(stream);
        }

        if (idx < size)
        {
            tx = size - idx;
            cgc_memcpy(stream->buffer + stream->length, buf + idx, tx);
            stream->length += tx;
            idx += tx;
        }

        return idx;
    }
}
