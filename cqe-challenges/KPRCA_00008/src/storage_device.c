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
#include <stdint.h>
#include <stdlib.h>

#include "usb.h"

static usb_t usb;

static size_t _send(const void *buf, size_t length)
{
    size_t bytes;
    ssize_t ret = transmit(STDOUT, buf, length, &bytes);
    if (ret != 0 || bytes != length) return 0;
    return ret;
}

static size_t _recv(void *buf, size_t length)
{
    size_t bytes, count;
    for (count = 0; count != length;)
    {
        size_t to_read = length - count;
        ssize_t ret = receive(STDIN, buf, to_read, &bytes);
        if (ret != 0 || bytes == 0) break;
        count += bytes;
    }
    return count;
}

int main()
{
    usb_init(&usb);
    usb.send = _send;
    usb.recv = _recv;
    do {
        if (!usb_handle_packet(&usb))
            break;
    } while (1);
    return 0;
}
