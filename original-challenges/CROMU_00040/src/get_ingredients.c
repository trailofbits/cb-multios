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



int get_ingredients(Recipe_Type *recipe) {
int ingredients_count;
size_t size;
char buffer[1024];
char item[1024];
char measurement[1024];

Ingredient_Type *ingredient;

	ingredients_count=0;
	ingredient = 0;


	printf("Enter the measurement and ingredients, one per line.  A blank line ends.\n\n");

	size=getline(buffer, sizeof(buffer));

	if (size <= 1) {

		return 0;
	}
	else {

		 ingredient = malloc(sizeof(Ingredient_Type));

		if (ingredient == 0) {

			printf("unable to malloc memory\n");
			_terminate(-1);
		}
	}

	recipe->Ingredient_List=ingredient;

	while(size > 1) {

		// validate ingredient entry

		bzero(measurement, 1024);
		bzero(item,1024);

		split_ingredient(buffer, measurement, 1024,  item, 1024);

		ingredient->next = 0;

		memcpy( ingredient->item, item, 99);
		memcpy( ingredient->measurement, measurement, 19);

		// store ingredient
		++ingredients_count;


		// get next input line
		size=getline(buffer, sizeof(buffer));

		if (size > 1 ) {

			ingredient->next = malloc(sizeof(Ingredient_Type));

			if (ingredient->next == 0) {

				printf("unable to malloc\n");
				_terminate(-1);

			}

			ingredient = ingredient->next;
		}

	}

	return (ingredients_count);

}