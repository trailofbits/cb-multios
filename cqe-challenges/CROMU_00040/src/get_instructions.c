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

#include <libcgc.h>
#include "stdlib.h"
#include "service.h"


void get_instructions(Recipe_Type *recipe) {

size_t size;
char buffer[1024];
char *temp_step;
char **step_list;
	
int step_count = 0;


	printf("Enter the step by step instructions.  A blank line to end.\n\n");
	printf("Step 1: ");

	size=getline(buffer, sizeof(buffer));

	if (size <=1) 
		return;
	else {

	
	// the dynamic array is null terminated so allocate memory for the null too
#ifdef PATCHED
		recipe->Instructions = malloc(sizeof(char *) * 4);
#else
		recipe->Instructions = malloc(sizeof(char *) * 2);
#endif

		if (recipe->Instructions == 0) {

			printf("unable to malloc memory\n");
			_terminate(-1);

		}

#ifdef PATCHED
		memset(recipe->Instructions, 0, sizeof(char *)*4);
#else
		memset(recipe->Instructions, 0, sizeof(char *)*2);
#endif


#ifdef PATCHED
		temp_step=malloc(strlen(buffer)+1);
#else
		temp_step=malloc(strlen(buffer));
#endif

		if (temp_step == 0) {

			printf("unable to malloc memory\n");
			_terminate(-1);

		}

#ifdef PATCHED
		memset( temp_step, 0, strlen(buffer) + 1 );
#endif

		strcpy(temp_step, buffer);

		recipe->Instructions[0] = temp_step;

		step_count++;

	}

	printf("Step 2: ");

	size=getline(buffer, sizeof(buffer));

	while(size > 1) {

#ifdef PATCHED
			step_list = malloc(sizeof(char *)*(step_count+4));
#else
			step_list = malloc(sizeof(char *)*(step_count+2));
#endif

			if (step_list == 0) {

				printf("unable to malloc\n");
				_terminate(-1);
			}

#ifdef PATCHED
			memset(step_list, 0, sizeof(char *)*(step_count+4));
#else
			memset(step_list, 0, sizeof(char *)*(step_count+2));
#endif

			memcpy(step_list, recipe->Instructions, sizeof(char *)*(step_count+1));

#ifdef PATCHED
			temp_step=malloc(strlen(buffer)+1);
#else
			temp_step=malloc(strlen(buffer));
#endif

			if (temp_step == 0) {

				printf("unable to malloc memory\n");
				_terminate(-1);

			}

#ifdef PATCHED
			memset( temp_step, 0, strlen(buffer)+ 1);
#endif
			strcpy(temp_step, buffer);

			step_list[step_count] = temp_step;

			free(recipe->Instructions);

			recipe->Instructions = step_list;

			++step_count;

			printf("Step @d: ", step_count+1);

			size=getline(buffer, sizeof(buffer));

	}  // while


}  // get_instructions()
