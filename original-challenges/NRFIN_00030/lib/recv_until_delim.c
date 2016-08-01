/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "recv_until_delim.h"
#include <errno.h>

// mod from recvline to make delimiter generic
// does not NULL terminate buf
int recv_until_delim(int fd, char *buf, size_t size, char delim) {
    size_t bytes_read = 0;
    size_t total_read = 0;

    if(!size)
        return ERRNO_RECV;

    if (!buf)
        return ERRNO_RECV;

    while (size) {
        if (receive(fd, buf++, 1, &bytes_read))
            return ERRNO_RECV;

        total_read++;
        size--;
        
        if(*(buf-1) == delim)
            break;
    }

    if (*(buf-1) != delim)
        return ERRNO_RECV;

    return total_read;
}
