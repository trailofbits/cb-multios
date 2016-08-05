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
#include <libcgc.h>
#include "errno.h"
#include "send_bytes.h"

int send_bytes(int fd, const char *buf, unsigned int size) {

	if ((NULL == buf) || (0 == size)) {
		return ERRNO_SEND;
	}

	size_t bytes_sent_iter = 0;
	unsigned int bytes_sent_total = 0;
	const char *p_buf = buf;

	while (bytes_sent_total < size) {
        if (0 != (transmit(fd, p_buf, size - bytes_sent_total, &bytes_sent_iter))) {
        	return ERRNO_SEND;
        }

        if (0 == bytes_sent_iter) {
        	break;
        }

        bytes_sent_total += bytes_sent_iter;
        p_buf += bytes_sent_iter;
	}

	return bytes_sent_total;
}
