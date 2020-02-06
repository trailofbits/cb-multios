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
#include "libcgc.h"
#include "cgc_errno.h"
#include "cgc_recv_until_delim_n.h"

int cgc_recv_until_delim_n(int fd, char delim, char *buf, unsigned int size) {

	if ((NULL == buf) || (0 == size)) {
		return ERRNO_RECV;
	}

	cgc_size_t bytes_read_iter = 0;
	unsigned int bytes_read_total = 0;

	unsigned int i = 0;
	for (i = 0; i < size; i++) {
        if (0 != (cgc_receive(fd, &buf[i], 1, &bytes_read_iter))) {
        	return ERRNO_RECV;
        }

        if (0 == bytes_read_iter) {
        	break;
        }

        bytes_read_total++;

        if (delim == buf[i]) {
        	break;
        }
	}

	if (delim != buf[bytes_read_total-1]) {
		return ERRNO_RECV;
	}

	return bytes_read_total;
}
