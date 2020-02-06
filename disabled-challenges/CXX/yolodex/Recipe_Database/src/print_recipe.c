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

void cgc_print_recipe(Recipe_Type *book) {

char **temp;
Ingredient_Type *ingredient;

	cgc_printf("\n");

#ifdef PATCHED
	if ( book == NULL ) {
		return;
	}

	if ( book->Title == NULL ) {
		return;
	}
#endif

	cgc_printf("\t\t@s\n\n", book->Title);

	ingredient = book->Ingredient_List;

	cgc_printf("Ingredients\n");
	cgc_printf("-----------\n");

	while (ingredient) {

		if (ingredient->measurement[0])
			cgc_printf("@s @s\n", ingredient->measurement, ingredient->item);
		else
			cgc_printf("@s\n", ingredient->item);

		ingredient=ingredient->next;
	}

	cgc_printf("\n");
	cgc_printf("Instructions\n");
	cgc_printf("------------\n");

	temp = book->Instructions;


	if (temp) {

		while(temp[0]) {

			cgc_printf("@s\n", temp[0]);
			++temp;
		}
	}
	cgc_printf("\n\n");

}


void cgc_print_all_tagged(Recipe_Type *book) {

char **temp;
Ingredient_Type *ingredient;

	cgc_printf("\n");

	while(book) {


		if (book->Tagged != 1 ) {

			book = book->next;
			continue;

		}
		
		cgc_printf("\t\t@s\n\n", book->Title);

		ingredient = book->Ingredient_List;

		cgc_printf("Ingredients\n");
		cgc_printf("-----------\n");

		while (ingredient) {

			if (ingredient->measurement[0])
				cgc_printf("@s @s\n", ingredient->measurement, ingredient->item);
			else
				cgc_printf("@s\n", ingredient->item);

			ingredient=ingredient->next;
		}

		cgc_printf("\n");
		cgc_printf("Instructions\n");
		cgc_printf("------------\n");

		temp = book->Instructions;

#ifdef PATCHED

		if (temp==0) {

			cgc_printf("\n\n");
			continue;
		}
#endif

		while(temp[0]) {

			cgc_printf("@s\n", temp[0]);
			++temp;
		}
		cgc_printf("\n\n");

		book = book->next;

	}



}

