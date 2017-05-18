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

// #define DEBUG 1

// We avoid including all of stdlib because then it would be easier to bisect 
// which functions are stdlib across CBs.
#include "libcgc.h"
// #include "cgc_stdint.h"
#include "cgc_memset.h"
#include "cgc_memcpy.h"
// #include "cgc_recv_until_delim_n.h"
#include "cgc_send_bytes.h"
#include "cgc_recv_bytes.h"
// #include "cgc_char.h"
// #include "cgc_streq.h"
// #include "cgc_strlen.h"
// #include "cgc_list.h"
// #include "cgc_malloc.h"

typedef unsigned char uint8_t;
typedef uint8_t byte_t;
typedef unsigned short uint16_t; 
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef uint8_t bool;
#define FALSE 0
#define TRUE 1

#define INT_MAX 0x7FFFFFFF

#define SUCCESS 0
#define SZ_PAGE 0x1000


#ifdef DEBUG
#include "cgc_debug.h"
#define dbg(args...) fprintf(stderr, "[D] %s:%d @ %s | ", __FILE__, __LINE__, __func__);fprintf(stderr, args);
#define err(args...) \
	fprintf(stderr, "[E] %s:%d @ %s | ", __FILE__, __LINE__, __func__);\
	fprintf(stderr, args);\
	if(SUCCESS == ret) { ret = -1; }\
	goto bail;
#else
#define dbg(args...) do { } while (0);
#define err(args...) goto bail;
#endif


#define CHK_SUCCESS(code, args...) if (SUCCESS != (ret = code)) { err(args); }

#endif
