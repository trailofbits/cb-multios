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

#define RECV(v,s) if(s != cgc_recv_all((char *)v, s)) {cgc__terminate(ERR_RECV_FAILED);}
#define SENDSI(v) cgc_send((char *)&v, sizeof(int32_t));
#define SENDUI(v) send((char *)&v, sizeof(uint32_t));
#define SENDD(v) send((char *)&v, sizeof(double));
#define SENDLL(v) cgc_send((char *)&v, sizeof(long long));

enum {
	ERR_INVALID_MODE = -80,
	ERR_INVALID_COMMAND = -81,
	ERR_INVALID_NONCE = -82,
	ERR_RAND_FAILED = -83,
	ERR_RECV_FAILED = -84,
};

extern int cgc_do_build();
extern int cgc_do_examine();
extern int cgc_do_nonce();

#endif