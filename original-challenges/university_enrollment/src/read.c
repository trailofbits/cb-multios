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
#include "read.h"

int readline(char *buf, size_t buf_size)
{
    if (!buf || buf_size < 2)
        return -1;

    size_t rx, i = 0;
#ifdef PATCHED
    while (i < buf_size && receive(STDIN, &buf[i], 1, &rx) == 0 && rx == 1) {
#else
    while (receive(STDIN, &buf[i], 1, &rx) == 0 && rx == 1 && i < buf_size) {
#endif
        if(buf[i] == '\n') {
            buf[i] = '\0';
            break;
        }

        i++;
    }

    if (i == 0)
        return -1;
    else if (i == buf_size)
        return -2;
    return 0;
}

int readnum(char *buf, size_t buf_size)
{
    if (readline(buf, buf_size))
        return -1;

    return strtol(&buf[0], NULL, 10);
}

