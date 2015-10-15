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
#ifndef STACK_H
#define STACK_H

#define TOO_MANY_ELEM_STR "Too many elements!\n"
#define NOT_ENOUGH_ELEM_STR "Not enough elements!\n"
#define MAX_STACK_SIZE 2000000

typedef struct {
	int top;
	int elementSize;
	int numElements;
	void *elements;
} Stack;

void initStack(Stack *stack, int numElements, int elementSize);
void destroyStack(Stack *stack);

int isStackFull(Stack *stack);
int isStackEmpty(Stack *stack);

void pushElement(Stack *stack, void* element);
void* popElement(Stack *stack);

#endif /* STACK_H */