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
#include "cgc_libc.h"

#define RECV(v,s) if(s != cgc_recv_all((char *)v, s)) {cgc__terminate(-10);}
#define SENDSI(v) cgc_send((char *)&v, sizeof(int32_t));
#define SENDUI(v) cgc_send((char *)&v, sizeof(uint32_t));
#define SENDD(v) cgc_send((char *)&v, sizeof(double));
#define SENDLL(v) cgc_send((char *)&v, sizeof(long long));
#define ALLOC(sz,ptr) if(SUCCESS != cgc_allocate(sz, 0, (void **)ptr)) {cgc__terminate(ERRNO_ALLOC);}

#define MAX_LIST_LEN 1000
 
typedef struct int32_data {
	int32_t val;
} int32_data_t;

typedef struct dbl64_data {
	double val;
} dbl64_data_t;

int cgc_int32_node_compare(node_t * nd1, node_t * nd2);
int cgc_dbl64_node_compare(node_t * nd1, node_t * nd2);
int cgc_do_create();
int cgc_do_eval();
int cgc_do_nonce();

#endif