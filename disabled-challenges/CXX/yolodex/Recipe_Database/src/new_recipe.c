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

#define BUFF_SIZE 200

int cgc_new_recipe(Recipe_Type **book) {

Recipe_Type *recipe;
Recipe_Type *previous;

char buffer[BUFF_SIZE];
cgc_size_t size;

	previous = 0;

	if (*book == 0) {

		*book = cgc_malloc(sizeof(Recipe_Type));

		if (*book==0) {

			cgc_printf("Failed to allocate memory\n");
			cgc__terminate(-1);

		}

		recipe = *book;
	}
	else {

		recipe = *book;

		while(recipe->next != 0) 
			recipe = recipe->next;

		recipe->next = cgc_malloc(sizeof(Recipe_Type));

		if (recipe->next == 0) {

			cgc_printf("Failed to allocate memory\n");
			cgc__terminate(-1);

		}

		previous = recipe;
		recipe = recipe->next;
	}

	recipe->Tagged = 0;
	recipe->next = 0;

	cgc_printf("Enter Title: ");

	size=cgc_getline(buffer, sizeof(buffer));

	if (size <=1) {

		if (recipe == *book) {

			*book = 0;
		}

		cgc_free(recipe);

		if (previous)
			previous->next = 0;

		return (-1);
	}
	else {

		cgc_strncpy(recipe->Title, buffer, BUFF_SIZE);

	}

	if (cgc_get_ingredients(recipe) == 0) {

		if (*book == recipe) {

			*book = 0;
		}

		cgc_free(recipe);

		if (previous) 
			previous->next = 0;

		return (-1);

	}

	// instructions can be left blank as some recipes are just ingredients
	cgc_get_instructions(recipe);


	return(0);


}


