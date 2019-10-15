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

void cgc_write_bytes(const void *buf, cgc_size_t count)
{
    cgc_size_t bytes;
    if (cgc_transmit(STDOUT, buf, count, &bytes) != 0 || bytes != count)
        cgc_exit(1);
}

void cgc_read_bytes(void *buf, cgc_size_t count)
{
    cgc_size_t bytes;
    if (cgc_receive(STDIN, buf, count, &bytes) != 0 || bytes != count)
        cgc_exit(1);
}

void cgc_write_byte(uint8_t b)
{
    cgc_write_bytes(&b, 1);
}

uint8_t cgc_read_byte()
{
    uint8_t result;
    cgc_read_bytes(&result, 1);
    return result;
}

void cgc_write_int(int val)
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
        cgc_write_byte(b);

        tmp = (absval >> (7 * (bytes-1))) & 0x7f;
    } while (bytes-- > 0);
}

int cgc_read_int()
{
    uint8_t b;
    int result, neg;

    b = cgc_read_byte();
    neg = b & 0x40;
    result = b & 0x3f;

    while (b & 0x80)
    {
        b = cgc_read_byte();
        result = (result << 7) | (b & 0x7f);
    }

    return neg ? -result : result;
}

void cgc_write_string(const char *str)
{
    unsigned int length = cgc_strlen(str);
    cgc_write_int(length);
    cgc_write_bytes(str, length);
}

char *cgc_read_string()
{
    cgc_size_t size = (cgc_size_t) cgc_read_int();
    char *result;

    if (size == SIZE_MAX)
        return NULL;
    
    result = cgc_malloc(size+1);
    if (result == NULL)
        return NULL;

    cgc_read_bytes(result, size);
    result[size] = 0;
    return result;
}

