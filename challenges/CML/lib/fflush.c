/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, cgc_free of charge, to any person obtaining a copy
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
#include "cgc_stdio_private.h"

int cgc_fflush(FILE *stream)
{
    if (stream->idx == INVALID_IDX)
        return 0;

    if (stream->rw == F_READ)
    {
        /* drop the contents of the cgc_read buffer */
        stream->idx = stream->length = 0;
        return 0;
    }
    else
    {
        int ret = 0;

        /* flush to fd */
        xlat(stream->xlat_map, stream->buffer + stream->idx, stream->length - stream->idx);
        if (transmit_all(stream->fd, stream->buffer + stream->idx, stream->length - stream->idx) != 0)
            ret = -1;

        stream->idx = stream->length = 0;
        return ret;
    }
}

void cgc_fbuffered(FILE *stream, int enabled)
{
    if (stream->idx != INVALID_IDX)
        cgc_fflush(stream);

    if (enabled)
    {
        stream->idx = 0;
        stream->length = 0;
    }
    else
    {
        stream->idx = -1;
        stream->length = 0;
    }
}
