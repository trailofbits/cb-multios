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

const char *CB_NAME = "SERVER";

#define PIPE_SEND_TAP PIPE_TAP_A
#define PIPE_SEND_NO_TAP PIPE_CB1_A
#define PIPE_RECV PIPE_CB2_B

 /**
 * Provided an X and a Y, add: X + Y.  Return the RESPONSE to the CLIENT.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
__attribute__ ((regparm (3))) int op_add(uint32_t x, uint32_t y, uint8_t nmb);

 /**
 * Provided an X and a Y, subtract: X - Y. Return the RESPONSE to the CLIENT.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
__attribute__ ((regparm (3))) int op_sub(uint32_t x, uint32_t y, uint8_t nmb);

 /**
 * Provided an X and a Y, multiply: X * Y. Return the RESPONSE to the CLIENT.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
__attribute__ ((regparm (3))) int op_mul(uint32_t x, uint32_t y, uint8_t nmb);

 /**
 * Provided an X and a Y, divide: X / Y.  If Y is 0, result is 0. 
 * Return the RESPONSE to the CLIENT.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
__attribute__ ((regparm (3))) int op_div(uint32_t x, uint32_t y, uint8_t nmb);

 /**
 * An authenticated function; used to reconfigure the behavior of an operation 
 * (by redirecting its function pointer).  In the UNPATCHED version, so sanity 
 * checking is applied to the redirection.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
__attribute__ ((regparm (3))) int op_mod(uint32_t x, uint32_t y, uint8_t nmb);

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


// op_mod is 61 (0x3d)
#define NUM_OPS 256
__attribute__ ((regparm (3))) int (*operations[NUM_OPS]) (uint32_t x, uint32_t y, uint8_t nmb) = {
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 8
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 16
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 24
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 32
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 40
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 48
	op_add, op_sub, op_mul, op_div, op_add, op_sub, op_mul, op_div, // 56
	op_add, op_sub, op_mul, op_div, op_add, op_mod, op_mul, op_div, // 64
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

