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
#include "libcgc.h"
#include "cgc_stdlib.h"

#define BUFF_SIZE 100

int cgc_split_ingredient(char *input, char *measure, int measure_size, char *ingredient, int ingredient_size) {


char *tmp;
char buffer[BUFF_SIZE];
int i;

	measure[0] = 0;
	tmp = input;
	i = 0;

	cgc_bzero(buffer, BUFF_SIZE);

	while (tmp[i] != ' ' && i < BUFF_SIZE-1 && i < cgc_strlen(tmp)) {

		buffer[i] = tmp[i];
		++i;
	}

	buffer[i] = 0;

	tmp = input+i+1;

	// first validate that the first term is a measurement value
	for (i=0; i < cgc_strlen(buffer); ++i) {

		if (!cgc_isdigit(buffer[i]) && buffer[i]!='.' && buffer[i]!='/') {

			cgc_strcpy(ingredient, input);
			measure[0] = 0;

			return 0;
		}

	}

	cgc_strcpy(measure, buffer);

	cgc_bzero(buffer, BUFF_SIZE);
	i = 0;

	while (tmp[i] != ' ' && i < BUFF_SIZE-1 && i < cgc_strlen(tmp)) {

		buffer[i] = tmp[i];
		++i;
	}

	buffer[i]=0;

	if (cgc_strcmp(buffer, "tsp") == 0 || cgc_strcmp(buffer, "tbsp") == 0 || cgc_strcmp(buffer, "cup") == 0 
		|| cgc_strcmp(buffer, "cups") ==0 || cgc_strcmp(buffer, "oz")== 0 ) {

		cgc_strcat(measure, " ");
		cgc_strcat(measure, buffer);

		tmp = tmp + i + 1;
	}

	cgc_strcpy(ingredient, tmp);

	return 0;

}