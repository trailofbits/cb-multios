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
#include "cgc_service.h"


void cgc_get_instructions(Recipe_Type *recipe) {

cgc_size_t size;
char buffer[1024];
char *temp_step;
char **step_list;
	
int step_count = 0;


	cgc_printf("Enter the step by step instructions.  A blank line to end.\n\n");
	cgc_printf("Step 1: ");

	size=cgc_getline(buffer, sizeof(buffer));

	if (size <=1) 
		return;
	else {

	
	// the dynamic array is null terminated so allocate memory for the null too
#ifdef PATCHED
		recipe->Instructions = cgc_malloc(sizeof(char *) * 4);
#else
		recipe->Instructions = cgc_malloc(sizeof(char *) * 2);
#endif

		if (recipe->Instructions == 0) {

			cgc_printf("unable to malloc memory\n");
			cgc__terminate(-1);

		}

#ifdef PATCHED
		cgc_memset(recipe->Instructions, 0, sizeof(char *)*4);
#else
		cgc_memset(recipe->Instructions, 0, sizeof(char *)*2);
#endif


#ifdef PATCHED
		temp_step=cgc_malloc(cgc_strlen(buffer)+1);
#else
		temp_step=cgc_malloc(cgc_strlen(buffer));
#endif

		if (temp_step == 0) {

			cgc_printf("unable to malloc memory\n");
			cgc__terminate(-1);

		}

#ifdef PATCHED
		cgc_memset( temp_step, 0, cgc_strlen(buffer) + 1 );
#endif

		cgc_strcpy(temp_step, buffer);

		recipe->Instructions[0] = temp_step;

		step_count++;

	}

	cgc_printf("Step 2: ");

	size=cgc_getline(buffer, sizeof(buffer));

	while(size > 1) {

#ifdef PATCHED
			step_list = cgc_malloc(sizeof(char *)*(step_count+4));
#else
			step_list = cgc_malloc(sizeof(char *)*(step_count+2));
#endif

			if (step_list == 0) {

				cgc_printf("unable to malloc\n");
				cgc__terminate(-1);
			}

#ifdef PATCHED
			cgc_memset(step_list, 0, sizeof(char *)*(step_count+4));
#else
			cgc_memset(step_list, 0, sizeof(char *)*(step_count+2));
#endif

			cgc_memcpy(step_list, recipe->Instructions, sizeof(char *)*(step_count+1));

#ifdef PATCHED
			temp_step=cgc_malloc(cgc_strlen(buffer)+1);
#else
			temp_step=cgc_malloc(cgc_strlen(buffer));
#endif

			if (temp_step == 0) {

				cgc_printf("unable to malloc memory\n");
				cgc__terminate(-1);

			}

#ifdef PATCHED
			cgc_memset( temp_step, 0, cgc_strlen(buffer)+ 1);
#endif
			cgc_strcpy(temp_step, buffer);

			step_list[step_count] = temp_step;

			cgc_free(recipe->Instructions);

			recipe->Instructions = step_list;

			++step_count;

			cgc_printf("Step @d: ", step_count+1);

			size=cgc_getline(buffer, sizeof(buffer));

	}  // while


}  // get_instructions()
