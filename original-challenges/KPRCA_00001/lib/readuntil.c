/*
 * Author: Andrew Wesie <andrew.wesie@kapricasecurity.com>
 * 
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
#include <stdlib.h>

int readuntil(int fd, char *buf, size_t n, char delim)
{
    char *bufend = buf + n - 1;
    int ret;
    while (buf != bufend)
    {
        size_t rx;
        if (receive(fd, buf, 1, &rx) != 0 || rx == 0)
            break;
        if (*buf == delim)
            break;
        buf++;
    }
    if (buf == bufend || *buf != delim)
        return 1;
    buf[1] = '\0';
    return 0;
}

int writeall(int fd, const char *buf, size_t n)
{
    const char *wptr = buf;
    const char *bufend = buf + n;
    while (wptr != bufend)
    {
        size_t tx;
        if (transmit(fd, buf, bufend - wptr, &tx) != 0 || tx == 0)
            break;
        wptr += tx;
    }
    return wptr - buf;
}
