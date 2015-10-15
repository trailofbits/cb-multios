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

#ifndef STACK_H_DEFINED
#define STACK_H_DEFINED


#define MAX_NUM_COUNT 64
#define MAX_OP_COUNT 64

typedef struct
{
	int stak[MAX_NUM_COUNT+1];
	int count;
} Stack_i; // int stack


typedef struct
{
	char stak[MAX_NUM_COUNT+1];
	int count;
} Stack_c; // char stack

// tracks numbers
extern Stack_i num_stack;
extern int curr_num_stack;

// tracks symbols (+,-)
extern Stack_c op_stack;
extern int curr_op_stack;


int push_num(int num);
int pop_num(int *num);
int peek_op(char *op);
int push_op(char op);
int pop_op(char *op);

#endif