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
#include "cgc_stdint.h"
#include "cgc_string.h"
#include "cgc_io.h"

static uint8_t ikey = 0xAA;
static uint8_t okey = 0x55;

int cgc_read_bytes(void *_buf, cgc_size_t n)
{
    cgc_size_t bytes, i;
    char *buf = _buf;

    while (n != 0)
    {
        if (cgc_receive(STDIN, buf, n, &bytes) != 0 || bytes == 0)
            return 0;
        for (i = 0; i < bytes; i++)
        {
            buf[i] ^= ikey;
            ikey += buf[i];
        }
        n -= bytes;
        buf += bytes;
    }
    return 1;
}

int cgc_read_until(char *buf, cgc_size_t n, char el)
{
    cgc_size_t i;
    for (i = 0; i < n; i++)
    {
        if (cgc_read_bytes(&buf[i], 1) == 0)
            return 0;
        if (buf[i] == el)
            break;
    }

    if (i < n)
        buf[i] = 0;
    else
        buf[n-1] = 0;

    return 1;
}

void cgc_write_bytes(void *_buf, cgc_size_t n)
{
    cgc_size_t bytes, i;
    char *buf = _buf;

    for (i = 0; i < n; i++)
    {
        char val = buf[i];
        buf[i] ^= okey;
        okey += val;
    }

    while (n != 0)
    {
        if (cgc_transmit(STDOUT, buf, n, &bytes) != 0 || bytes == 0)
            return;
        n -= bytes;
        buf += bytes;
    }
}

void cgc_write_string(char *buf)
{
    cgc_write_bytes(buf, cgc_strlen(buf));
}
