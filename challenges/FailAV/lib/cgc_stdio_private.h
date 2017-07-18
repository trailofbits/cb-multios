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
#ifndef STDIO_PRIVATE_H_
#define STDIO_PRIVATE_H_

#include "cgc_stdio.h"
#include "cgc_string.h"

#define INVALID_IDX -1
#define F_READ 1
#define F_WRITE 2

struct FILE {
    int fd;
    int rw;
    int idx;
    int length;
    unsigned char *xlat_map;
    unsigned char *xlat_map_inv;
    char buffer[1024];
};

static inline void cgc_xlat(const unsigned char *map, void *buf, cgc_size_t count)
{
    unsigned char *cbuf = (unsigned char *)buf;
    cgc_size_t i;

    if (map == NULL)
        return;

    for (i = 0; i < count; i++)
        cbuf[i] = map[cbuf[i]];
}

static inline int cgc_transmit_all(int fd, const void *buf, cgc_size_t count)
{
    const char *cbuf = (const char *)buf;
    cgc_size_t i;

    for (i = 0; i < count; )
    {
        cgc_size_t bytes;
        if (cgc_transmit(fd, cbuf + i, count - i, &bytes) != 0)
            return -1;
        i += bytes;
    }

    return 0;
}

static inline int transmit_xlat(int fd,  const unsigned char *map, const void *buf, cgc_size_t count)
{
    const char *cbuf = (const char *)buf;
    char tmp[1024];
    cgc_size_t i;

    for (i = 0; i < count; )
    {
        cgc_size_t cnt = count - i;
        if (cnt > sizeof(tmp)) cnt = sizeof(tmp);

        cgc_memcpy(tmp, cbuf + i, cnt);
        cgc_xlat(map, tmp, cnt);
        if (cgc_transmit_all(fd, tmp, cnt) != 0)
            return -1;
        i += cnt;
    }
    
    return 0;
}

#endif
