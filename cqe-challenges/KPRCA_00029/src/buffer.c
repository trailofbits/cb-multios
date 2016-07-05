/*
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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

static void increment_read(buffer_t *buf, size_t n)
{
    buf->read_idx += n;
    if (buf->read_idx == buf->length * 8)
        buf->read_idx = 0;//-= buf->length * 8;
    else if (buf->read_idx > buf->length * 8)
        exit(1);
}

static void increment_write(buffer_t *buf, size_t n)
{
    buf->write_idx += n;
    if (buf->write_idx >= buf->length * 8)
        buf->write_idx -= buf->length * 8;
}

// read functions
int buffer_read_bit(buffer_t *buf)
{
    if (buf->read_idx == buf->write_idx)
        return -1;

    uint8_t byte = buf->buffer[buf->read_idx / 8];
    uint8_t bit = (byte >> (7 - (buf->read_idx % 8))) & 1;
    increment_read(buf, 1);
    return bit;
}

unsigned int buffer_read_bits(buffer_t *buf, unsigned int count)
{
    unsigned int value = 0;
    size_t i;
    for (i = 0; i < count && buf->read_idx != buf->write_idx; i++)
        value = (value << 1) | buffer_read_bit(buf);
    return value;
}

void buffer_read_bytes(buffer_t *buf, uint8_t *output, size_t n)
{
    size_t i;
    if ((buf->read_idx % 8) == 0 && buffer_read_remaining(buf)/8 >= n)
    {
        // fast path
        for (i = 0; i < n; i++)
        {
            output[i] = buf->buffer[buf->read_idx / 8];
            increment_read(buf, 8);
        }
    }
    else
    {
        // slow path
        for (i = 0; i < n; i++)
            output[i] = buffer_read_bits(buf, 8);
    }
}

// write functions
void buffer_write_bit(buffer_t *buf, int value)
{
    uint8_t byte = buf->buffer[buf->write_idx / 8];
    uint8_t pos = 7 - (buf->write_idx % 8);
    if (pos == 7)
        byte = 0;
    buf->buffer[buf->write_idx / 8] = byte | (value << pos);
    increment_write(buf, 1);
}

void buffer_write_bits(buffer_t *buf, unsigned int value, unsigned int count)
{
    int i;
    for (i = count-1; i >= 0; i--)
        buffer_write_bit(buf, (value >> i) & 1);
}

void buffer_write_bytes(buffer_t *buf, uint8_t *input, size_t n)
{
    size_t i;
    if ((buf->write_idx % 8) == 0)
    {
        // fast path
        for (i = 0; i < n; i++)
        {
            buf->buffer[buf->write_idx / 8] = input[i];
            increment_write(buf, 8);
        }
    }
    else
    {
        // slow path
        for (i = 0; i < n; i++)
            buffer_write_bits(buf, input[i], 8);
    }
}

// misc functions
uint64_t buffer_read_remaining(buffer_t *buf)
{
    int64_t diff = buf->write_idx - buf->read_idx;
    if (diff < 0)
        return (buf->length * 8) + diff;
    return diff;
}

uint64_t buffer_read_tell(buffer_t *buf)
{
    return buf->read_idx;
}

void buffer_read_seek(buffer_t *buf, uint64_t pos)
{
    buf->read_idx = pos;
}

uint64_t buffer_write_tell(buffer_t *buf)
{
    return buf->write_idx;
}

void buffer_write_seek(buffer_t *buf, uint64_t pos)
{
    buf->write_idx = pos;
}

void buffer_init(buffer_t *buf, uint8_t *data, size_t data_size)
{
    memset(buf, 0, sizeof(buffer_t));
    buf->buffer = data;
    buf->length = data_size;
}
