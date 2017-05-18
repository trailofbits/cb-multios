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
#include "cgc_libc.h"
#include "cgc_recv_until_delim_n.h"

#define EOF 					-1
#define FILE_BUF_SZ 			1024

typedef struct {
	cgc_size_t 	fd;
	cgc_size_t 	idx;					// current idx in buf
	cgc_size_t 	count;					// number of usable bytes in buf
	unsigned char buf[FILE_BUF_SZ]; // buffer of received bytes
} FILE;

// list of FILE's in use by this CB for RECEIVING data (not used for sending)
// In an IPC CB, will need to modify this with the correct FDs
// By default READ_FD is defined in libc.h
#define RECV_FILE_COUNT 		1	// number of FILEs in recv_files
#define RECV_FILE_FROM_FD(fd)		\
 	switch(fd) {					\
 		case READ_FD: 				\
 			f = &recv_files[0];		\
 			break;					\
 		default: return ERRNO_RECV;	\
 	}

static FILE recv_files[RECV_FILE_COUNT] = { {.fd = READ_FD} };

/**
 *	Receive one char from the FILE
 *
 * @param f 	file descriptor to process
 * @param error Value to store error condition.
 * @return next available char if found, EOF if no more chars or an error
 */
static cgc_ssize_t cgc_recv_char(int fd, int *error) {
	char ch = 0;
	FILE *f = NULL;
	RECV_FILE_FROM_FD(fd);

	*error = 0;

	// check for an available char
	if ((0 != f->count) && ((f->count - 1) >= f->idx)) {
		goto havechar;
	}

	// no available char, so need to receive()
	f->idx = 0;
	f->count = 0;

    if (0 != (cgc_receive(f->fd, f->buf, FILE_BUF_SZ, &f->count))) {
    	*error = ERRNO_RECV;
    	return EOF;
    }
    if (0 == f->count) {
    	*error = EOF;
    	return EOF;
    }

havechar:
	ch = f->buf[f->idx];
	f->idx++;
	return ch;
}

cgc_ssize_t cgc_recv_until_delim_n(int fd, char delim, char *buf, unsigned int size) {
	if ((NULL == buf) || (0 == size)) {
		return ERRNO_RECV;
	}

	cgc_size_t bytes_read_total = 0;
	char ch = 0;
	int error = 0;

	for (cgc_size_t i = 0; i < size; i++) {
		ch = cgc_recv_char(fd, &error);

		if (EOF == ch) {
			if (ERRNO_RECV == error) {
				return ERRNO_RECV;
			}
			if (EOF == error) {
				break;
			}
		}

        buf[bytes_read_total++] = ch;
        if (delim == ch) {
        	break;
        }
	}

	if (delim != buf[bytes_read_total-1]) {
		return ERRNO_RECV;
	}

	return bytes_read_total;
}

