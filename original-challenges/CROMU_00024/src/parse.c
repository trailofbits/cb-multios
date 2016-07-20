/*

Author: Steve Wood <swood@cromulence.co>

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

#include "stdlib.h"


int parse_command(char *buffer, char separator, char ***args) {
	
	int arg_count;
	char *tmp;
	int i;

	
	if (*buffer != 0) {

		// there is at least 1 because this function was called with a string
		arg_count = 1;
		tmp=buffer;
	}
	else
		return -1;

	// count how many fields are on the command so memory can be allocated for the pointers
	while(*tmp++ != 0) {

		if (*tmp==separator)
			++arg_count;
	} // while

	// allocate one char pointer for each field in the command
	*args=calloc(arg_count, sizeof(char *));

	// failed to allocate the memory
	if (*args==0) {
		return -1;
	}

	// start back from the beginning of the buffer
	tmp=buffer;

	// for each field, store a pointer to the first char
	for (i=0;i< arg_count; ++i) {

		(*args)[i]=tmp;

		while (*tmp!= separator && *tmp != 0)
			++tmp;

		// if we found the separator, overwrite it with a null so our args will be properly terminated
		if (*tmp !=0) {

			*tmp=0;
			++tmp;
		}


	} //for 

	return (arg_count);

}