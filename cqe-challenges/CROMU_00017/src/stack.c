/*

Author: James Nuttall (james@cromulence.co)

Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "math_lib.h"
#include "stack.h"
#include "stdlib.h"
#include "prng.h"

// Globals
Stack_i num_stack;
int curr_num_stack;
Stack_c op_stack;
int curr_op_stack;


int push_num(int num)
{
	debug_print("PUSH_NUM: @d\n", num);
	if (curr_num_stack >= MAX_NUM_COUNT)
		return FAIL;
	num_stack.stak[++curr_num_stack] = num;
	return SUCCESS;
}

// returns SUCCESS or FAIL
// pass in number which will contain the requested number
// removes number from num_stack
int pop_num(int *num)
{
	debug_print("POP_NUM: @d\n", num_stack.stak[curr_num_stack]);
	if (curr_num_stack <= -1)
	{
		// error, empty
		debug_print("POP_NUM failed\n", 0);
		_terminate(0);
		return FAIL;

	}
	*num = num_stack.stak[curr_num_stack--];
	return SUCCESS;
}

// returns SUCCESS or FAIL
// pass in char pointer which will contain the requested operator
// does NOT remove operator from op_stack
int peek_op(char *op)
{
	if (curr_op_stack <= -1)
	{
		// error, empty
		return FAIL;
	}
	*op = op_stack.stak[curr_op_stack];
	return SUCCESS;
}

// returns SUCCESS or FAIL
// pushes op onto the op_stack
int push_op(char op)
{
	debug_print("PUSH_OP: @c\n", op);
	if (curr_op_stack >= MAX_NUM_COUNT)
		return FAIL;
	op_stack.stak[++curr_op_stack] = op;
	return SUCCESS;
}

// returns SUCCESS or FAIL
// pass in char pointer which will contain the requested operator
// removes operator from op_stack
int pop_op(char *op)
{
	debug_print("POP_OP: @c\n", op_stack.stak[curr_op_stack]);
	if (curr_op_stack <= -1)
	{
		// error, empty
		debug_print("POP_OP failed\n", 0);
		_terminate(0);
		return FAIL;
	}
	*op = op_stack.stak[curr_op_stack--];
	return SUCCESS;
}