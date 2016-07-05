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
#include <libcgc.h>
#include "libc.h"
#include "stack.h"

void initStack(Stack *stack, int numElements, int elementSize) {

	int ret;

	if(numElements > MAX_STACK_SIZE/elementSize) {
		stack->elements = NULL;
		return;
	}

	ret = allocate(elementSize * numElements, 0, (void**) &stack->elements);
	if (ret != 0)
		_terminate(16);

	stack->numElements = numElements;
	stack->elementSize = elementSize;
	stack->top = -1;
}

void destroyStack(Stack *stack) {
	
	int ret;

	ret = deallocate(stack->elements, stack->numElements*stack->elementSize);
	if (ret != 0)
		_terminate(17);

	stack->elements = NULL;
	stack->numElements = 0;
	stack->elementSize = 0;
	stack->top = -1;
}

int isStackFull(Stack *stack) {
#ifdef PATCHED
	return stack->top >= stack->numElements - 1;
#else
	return stack->top >= stack->numElements;
#endif
}

int isStackEmpty(Stack *stack) {
	return stack->top < 0;
}

void pushElement(Stack *stack, void* element) {
	int ret;

	if(isStackFull(stack)) {
		ret = transmit_all(STDOUT, TOO_MANY_ELEM_STR, sizeof(TOO_MANY_ELEM_STR));
    	if (ret != 0)
        	_terminate(18);
        _terminate(19);
	}
	stack->top++;
	memcpy(&stack->elements[stack->elementSize*stack->top], element, stack->elementSize);
}

void* popElement(Stack *stack) {
	int ret;

	if(isStackEmpty(stack)) {
		ret = transmit_all(STDOUT, NOT_ENOUGH_ELEM_STR, sizeof(NOT_ENOUGH_ELEM_STR));
    	if (ret != 0)
        	_terminate(20);
        _terminate(21);
	}

	return &stack->elements[stack->elementSize*stack->top--];
}
