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
#ifndef LIBC_H
#define LIBC_H 1

#include <libcgc.h>
#include <errno.h>
#include <stdint.h>
#include "memset.h"
#include "conv.h"
#include "memcpy.h"
#include "recv_until_delim_n.h"
#include "send_bytes.h"
#include "recv_bytes.h"
#include "rand.h"
#include "streq.h"
#include "strlen.h"
#include "list.h"
#include "malloc.h"
#include "hash_table.h"
#include "xxprintf.h"

#define DEBUG 1

#define FLAG_PAGE 0x4347C000

#define READ_FD STDIN

#define SEND(f,b,s) if(s != send_bytes(f,b,s)) _terminate(ERRNO_SEND)

#define RECV_DELIM(f,t,b,s)	if(0 > recv_until_delim_n(f,t,b,s)) _terminate(ERRNO_RECV)

// trim delimiter from resultant string
#define RECV_DELIM_TRIM(f,t,b,s)	\
 			do { \
 				int r_u_d_n = 0; \
 				r_u_d_n = recv_until_delim_n(f,t,b,s); \
				if (0 >= r_u_d_n) _terminate(ERRNO_RECV); \
				if (t == b[r_u_d_n - 1]) b[r_u_d_n - 1] = '\0'; \
			} while (0);

#define RECV(f,b,s) if(0 > recv_bytes(f,b,s)) _terminate(ERRNO_RECV)

#define FAIL_BAIL_RET(e) if (SUCCESS != (ret = e)) return ret;
#define NEG_BAIL_RET(e) if (0 > (ret = e)) return ret
#define MALLOC_OK(p) if (NULL == p) _terminate(ERRNO_ALLOC)

#endif
