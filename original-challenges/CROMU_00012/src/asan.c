/*

Author: Dustin Fraze (df@cromulence.co)

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

#include <libcgc.h>

#include "asan.h"
#include "stdlib.h"
#include "string.h"

int validatePtr(void *ptr) {
	int validated = 0;
	if((unsigned int)ptr > STACKBASE && (unsigned int)ptr < STACKBASE + STACKSIZE)
		validated = 1;
	if((unsigned int)ptr > PROGRAMBASE && (unsigned int)ptr < PROGRAMBASE+PROGRAMSIZE)
		validated = 1;
	if(validated == 0) {
		puts("Invalid pointer detected!");
		_terminate(-1);
	}
	return validated;
}

void validateRet() {
	int* retAddr = 0;

	retAddr = __builtin_return_address(1);

	if((unsigned int)retAddr < PROGRAMBASE || (unsigned int)retAddr > PROGRAMBASE+PROGRAMSIZE) {
		//only allowed to ret to an address within the main module.
		puts("***** STACK SMASHING DETECTED! *****");
		_terminate(-1);
	}

	retAddr=(int*)((char *)retAddr-5);
	//check to see if the previous instruction was a call.
	if((*retAddr & 0xff) != 0xe8) {
		puts("***** STACK SMASHING DETECTED! *****");
		_terminate(-1);
	}
}