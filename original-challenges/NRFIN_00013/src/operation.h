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

#ifndef OPERATION_H
#define OPERATION_H
#include "libc.h"

#define RECV(v,s) if(s != recv_all((char *)v, s)) {_terminate(-10);}
#define SENDSI(v) send((char *)&v, sizeof(int32_t));
#define SENDUI(v) send((char *)&v, sizeof(uint32_t));
#define SENDD(v) send((char *)&v, sizeof(double));
#define SENDLL(v) send((char *)&v, sizeof(long long));
#define ALLOC(sz,ptr) if(SUCCESS != allocate(sz, 0, (void **)ptr)) {_terminate(ERRNO_ALLOC);}

#define MAX_LIST_LEN 1000
 
typedef struct int32_data {
	int32_t val;
} int32_data_t;

typedef struct dbl64_data {
	double val;
} dbl64_data_t;

int int32_node_compare(node_t * nd1, node_t * nd2);
int dbl64_node_compare(node_t * nd1, node_t * nd2);
int do_create();
int do_eval();
int do_nonce();

#endif