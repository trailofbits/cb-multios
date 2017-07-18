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
#include "cgc_common.h"

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
int cgc_get_request_type(byte_t *operation);

 /**
 * Issue a REQUEST to the server for some computation.  
 * Call appropriate op_? function pointer to anticipate result.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int cgc_do_request(cgc_size_t x, cgc_size_t y, cgc_size_t *expected_answer);

 /**
 * Recv the RESPONSE to our REQUEST from the server.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int cgc_do_response(cgc_size_t expected_answer);

 /**
 * Ask the server to conduct an addition on our behalf.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int cgc_op_add(cgc_size_t x, cgc_size_t y, cgc_size_t *expected_answer);

 /**
 * Ask the server to conduct a subtraction on our behalf.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int cgc_op_sub(cgc_size_t x, cgc_size_t y, cgc_size_t *expected_answer);

 /**
 * Ask the server to conduct a multiplication on our behalf.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int cgc_op_mul(cgc_size_t x, cgc_size_t y, cgc_size_t *expected_answer);

 /**
 * Ask the server to conduct a division on our behalf.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int cgc_op_div(cgc_size_t x, cgc_size_t y, cgc_size_t *expected_answer);

 /**
 * Negotiate enckey_idx and auth_token_idx with the other CB.  The CLIENT 
 * determines the former; the SERVER the latter.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int cgc_negotiate(void);

 /**
 * Terminate the process.  Called upon receipt of a DST_EXIT message.
 *
 * @return void
 */
void cgc_do_exit(void);

 /**
 * The main loop.  Responsible for maintaining the simple state machine and 
 * dispatching to other functions.  Should not return during normal execution.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int main(int cgc_argc, char *cgc_argv[]);

#define NUM_OPS 256
int (*operations[NUM_OPS]) (cgc_size_t x, cgc_size_t y, cgc_size_t *expected_answer) = {
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 8
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 16
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 24
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 32
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 40
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 48
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 56
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 64
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 72
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 80
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 88
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 96
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 104
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 112
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 120
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 128

	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 8
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 16
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 24
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 32
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 40
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 48
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 56
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 64
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 72
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 80
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 88
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 96
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 104
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 112
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 120
	cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, cgc_op_add, cgc_op_sub, cgc_op_mul, cgc_op_div, // 128
};
