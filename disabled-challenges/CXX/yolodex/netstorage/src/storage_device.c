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
#include "cgc_stdint.h"
#include "cgc_stdlib.h"

#include "cgc_usb.h"

static usb_t usb;

static cgc_size_t cgc__send(const void *buf, cgc_size_t length)
{
    cgc_size_t bytes;
    cgc_ssize_t ret = cgc_transmit(STDOUT, buf, length, &bytes);
    if (ret != 0 || bytes != length) return 0;
    return ret;
}

static cgc_size_t cgc__recv(void *buf, cgc_size_t length)
{
    cgc_size_t bytes, count;
    for (count = 0; count != length;)
    {
        cgc_size_t to_read = length - count;
        cgc_ssize_t ret = cgc_receive(STDIN, buf, to_read, &bytes);
        if (ret != 0 || bytes == 0) break;
        count += bytes;
    }
    return count;
}

int main(int cgc_argc, char *cgc_argv[])
{
    cgc_usb_init(&usb);
    usb.send = cgc__send;
    usb.recv = cgc__recv;
    do {
        if (!cgc_usb_handle_packet(&usb))
            break;
    } while (1);
    return 0;
}
