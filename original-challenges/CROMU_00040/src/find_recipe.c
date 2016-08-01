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


void find_recipe(Recipe_Type *book) {

char **temp;
Ingredient_Type *ingredient;
char buffer[1024];
char answer[5];
size_t size;


	printf("Enter search term: ");

	size=getline(buffer, sizeof(buffer));

	if (size <=1 ) 
		return;


	printf("\n");

	while(book) {


		if (match_str(buffer, book->Title)) {

			print_recipe(book);

			printf("Would you like to tag this recipe? ");

			size=getline(answer, sizeof(answer));

			if (size <1 )  {
				book=book->next;
				continue;
			}

			if (answer[0] == 'y' || answer[0] == 'Y') {

				book->Tagged = 1;
			}

			book=book->next;
			continue;

		}

		ingredient = book->Ingredient_List;

		while (ingredient) {

			if (match_str(buffer, ingredient->item)) {

				print_recipe(book);

#ifdef PATCHED
			if ( book == NULL ) {
				return;
			}
#endif

				printf("Would you like to tag this recipe? ");

				size=getline(answer, sizeof(answer));

				if (size <1 )  {
					book=book->next;
					continue;
				}

				if (answer[0] == 'y' || answer[0] == 'Y') {

					book->Tagged = 1;
				}
				break;

			}

			ingredient=ingredient->next;
		}

		book = book->next;

	}


}
