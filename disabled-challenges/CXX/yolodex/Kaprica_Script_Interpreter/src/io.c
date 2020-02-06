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
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_io.h"

#define BUFFER_SIZE (8192)
#define IS_MUTABLE(x) ((x)->fd >= 0)

void cgc_io_init_fd(io_t *io, int fd)
{
    io->fd = fd;
    io->buf = cgc_malloc(BUFFER_SIZE);
    io->pos = 0;
    io->length = 0;
    io->mark = -1;
}

void cgc_io_init_bytes(io_t *io, const char *str, unsigned int length)
{
    io->fd = -1;
    io->buf = (char *)str;
    io->length = length;
    io->pos = 0;
    io->mark = -1;
}

void cgc_io_init_string(io_t *io, const char *str)
{
    cgc_io_init_bytes(io, str, cgc_strlen(str));
}

void cgc_io_mark(io_t *io)
{
    if (IS_MUTABLE(io) && io->pos > 0)
    {
        cgc_memmove(io->buf, io->buf + io->pos, io->length - io->pos);
        io->length -= io->pos;
        io->pos = 0;
    }
    io->mark = io->pos;
}

int cgc_io_rewind(io_t *io)
{
    if (io->mark == -1)
        return 0;

    io->pos = io->mark;
    return 1;
}

/* returns position relative to last mark */
int cgc_io_tell(io_t *io)
{
    return io->pos - io->mark;
}

/* seeks to a position relative to last mark */
int cgc_io_seek(io_t *io, int pos)
{
    int new_pos = io->mark + pos;
    if (new_pos > io->length)
        return 0;
    
    io->pos = new_pos;
    return 1;
}

int cgc_io_getc(io_t *io)
{
    if (io->pos == io->length)
    {
        if (IS_MUTABLE(io))
        {
            cgc_size_t bytes;
            if (io->length == BUFFER_SIZE)
                return -1;
            if (cgc_receive(io->fd, &io->buf[io->length], 1, &bytes) != 0 || bytes != 1)
                return -1;
            io->length++;
        }
        else
        {
            return -1;
        }
    }

    return io->buf[io->pos++];
}

int cgc_io_ungetc(io_t *io)
{
    return cgc_io_seek(io, cgc_io_tell(io) - 1);
}

int cgc_io_peek(io_t *io)
{
    int c = cgc_io_getc(io);
    if (c >= 0)
        cgc_io_ungetc(io);
    return c;
}

int cgc_io_read(io_t *io, char *buf, unsigned int cnt)
{
    return -1;
}
