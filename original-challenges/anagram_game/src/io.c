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

#include <stdlib.h>
#include <string.h>
#include "io.h"

void write_bytes(const void *buf, size_t count)
{
    size_t bytes;
    if (transmit(STDOUT, buf, count, &bytes) != 0 || bytes != count)
        exit(1);
}

void read_bytes(void *buf, size_t count)
{
    size_t bytes;
    if (receive(STDIN, buf, count, &bytes) != 0 || bytes != count)
        exit(1);
}

void write_byte(uint8_t b)
{
    write_bytes(&b, 1);
}

uint8_t read_byte()
{
    uint8_t result;
    read_bytes(&result, 1);
    return result;
}

void write_int(int val)
{
    int bytes, neg;
    unsigned int absval, tmp;
    uint8_t b;

    neg = val < 0;
    absval = neg ? -val : val;

    tmp = absval;
    for (bytes = 0; tmp > 0x3f; bytes++)
        tmp >>= 7;

    if (neg)
        tmp |= 0x40;

    do {
        b = tmp;
        b |= bytes > 0 ? 0x80 : 0;
        write_byte(b);

        tmp = (absval >> (7 * (bytes-1))) & 0x7f;
    } while (bytes-- > 0);
}

int read_int()
{
    uint8_t b;
    int result, neg;

    b = read_byte();
    neg = b & 0x40;
    result = b & 0x3f;

    while (b & 0x80)
    {
        b = read_byte();
        result = (result << 7) | (b & 0x7f);
    }

    return neg ? -result : result;
}

void write_string(const char *str)
{
    unsigned int length = strlen(str);
    write_int(length);
    write_bytes(str, length);
}

char *read_string()
{
    size_t size = (size_t) read_int();
    char *result;

    if (size == SIZE_MAX)
        return NULL;
    
    result = malloc(size+1);
    if (result == NULL)
        return NULL;

    read_bytes(result, size);
    result[size] = 0;
    return result;
}

