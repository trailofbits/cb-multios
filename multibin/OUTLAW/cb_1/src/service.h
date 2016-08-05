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

#include <libcgc.h>
#include "common.h"

const char *CB_NAME = "CLIENT";

#define PIPE_SEND_TAP PIPE_TAP_A
#define PIPE_SEND_NO_TAP PIPE_CB2_A
#define PIPE_RECV PIPE_CB1_B

#define STATE_REQUEST 54
#define STATE_RESPONSE 45

 /**
 * Grab a byte from the PRNG and interpret it as in index into the operations 
 * table.  Return the next pseudo-random operation.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int get_request_type(byte_t *operation);

 /**
 * Issue a REQUEST to the server for some computation.  
 * Call appropriate op_? function pointer to anticipate result.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int do_request(size_t x, size_t y, size_t *expected_answer);

 /**
 * Recv the RESPONSE to our REQUEST from the server.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int do_response(size_t expected_answer);

 /**
 * Ask the server to conduct an addition on our behalf.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int op_add(size_t x, size_t y, size_t *expected_answer);

 /**
 * Ask the server to conduct a subtraction on our behalf.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int op_sub(size_t x, size_t y, size_t *expected_answer);

 /**
 * Ask the server to conduct a multiplication on our behalf.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int op_mul(size_t x, size_t y, size_t *expected_answer);

 /**
 * Ask the server to conduct a division on our behalf.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int op_div(size_t x, size_t y, size_t *expected_answer);

 /**
 * Negotiate enckey_idx and auth_token_idx with the other CB.  The CLIENT 
 * determines the former; the SERVER the latter.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int negotiate(void);

 /**
 * Terminate the process.  Called upon receipt of a DST_EXIT message.
 *
 * @return void
 */
void do_exit(void);

 /**
 * The main loop.  Responsible for maintaining the simple state machine and 
 * dispatching to other functions.  Should not return during normal execution.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int main(void);

#define NUM_OPS 256
int (*operations[NUM_OPS]) (size_t x, size_t y, size_t *expected_answer) = {
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 8
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 16
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 24
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 32
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 40
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 48
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 56
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 64
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 72
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 80
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 88
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 96
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 104
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 112
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 120
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 128

	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 8
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 16
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 24
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 32
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 40
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 48
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 56
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 64
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 72
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 80
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 88
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 96
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 104
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 112
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 120
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 128
};
