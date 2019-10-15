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
#pragma once
#include "libcgc.h"
#include "cgc_errno.h"
#include "cgc_stdint.h"
#include "cgc_recv_bytes.h"
#include "cgc_send_bytes.h"
#include "cgc_xxprintf.h"
#include "cgc_ipc.h"

#define MY_ID 4
#define MY_NAME "p4"

#define READ_FD 			IPC_READ_FD(MY_ID)
#define WRITE_FD 			IPC_WRITE_FD(0)


// #define DEBUG 1

#define FLAG_PAGE 0x4347C000

#define SEND(f,b,s) if(s != send_bytes(f,b,s)) cgc__terminate(ERRNO_SEND)
// #define RECV_DELIM(f,t,b,s)	if(0 > recv_until_delim_n(f,t,b,s)) cgc__terminate(ERRNO_RECV)
#define RECV(f,b,s) if(0 > recv_bytes(f,b,s)) cgc__terminate(ERRNO_RECV)

#define FAIL_BAIL_RET(e) if (SUCCESS != (ret = e)) return ret;
#define NEG_BAIL_RET(e) if (0 > (ret = e)) return ret
#define MALLOC_OK(p) if (NULL == p) cgc__terminate(ERRNO_ALLOC)

#ifdef DEBUG
#define DBG(args...) \
 	do { \
	 	fdprintf(STDERR, '%', '\0', "[%S] %S:%U @ %S | ", MY_NAME, __FILE__, __LINE__, __func__); \
	 	fdprintf(STDERR, '%', '\0', args); \
	 } while (0);
// #define err(args...) \
// 	fprintf(stderr, "[E] %s:%d @ %s | ", __FILE__, __LINE__, __func__);\
// 	fprintf(stderr, args);\
// 	if(SUCCESS == ret) { ret = -1; }\
// 	goto bail;
#else
#define DBG(args...) do { } while (0);
// #define err(args...) goto bail;
#endif

 