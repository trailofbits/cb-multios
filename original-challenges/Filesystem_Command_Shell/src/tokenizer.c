/*

Author: Steve Wood <swood@cromulence.com>

Copyright (c) 2016 Cromulence LLC

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
#include "stdlib.h"
#include "service.h"
#include "filesystem.h"
#include "string.h"
#include "ctype.h"
#include "stdio.h"
#include "malloc.h"


// returns the number of tokens, and an array of pointers to the items in the original string argument
int tokenize(char *string, char delimiter, char **args[]) {
int i;
int count;

	if (strlen(string) == 0) {

		return 0;
	}

	i = 0;
	count = 0;

	// pass one is to just determine how many tokens there are so memory can be allocated
	while(*(string+i) != 0) {
		
		while ( isspace(*(string+i)) && *(string+i) != 0)
			++i;

		if (*(string+i) == 0)
			break;

		++count;

		while ( !isspace(*(string+i)) && *(string+i) != 0)
			++i;

		if (*(string+i) == 0 )
			break;
	}


	*args = malloc(count * sizeof(char *));


	if (*args == 0 )
		return -1;

	i = 0;
	count = 0;

	while(*(string+i) != 0) {
		
		while ( isspace(*(string+i)) && *(string+i) != 0)
			++i;

		if (*(string+i) == 0)
			break;

		(*args)[count] = (string+i);
		++count;

		while ( !isspace(*(string+i)) && *(string+i) != 0)
			++i;


		if (*(string+i) == 0 )
			break;
		else {

			*(string+i) = 0;
			++i;
		}
	}

	return count;

}

