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



Shopping_List_Type *cgc_build_shopping_list(Recipe_Type *book) {

Shopping_List_Type *list, *previous;
Shopping_List_Type *list_head;
Ingredient_Type *ingredient;

	list_head = 0;
	list = 0;
	previous = 0;

	while(book) {


		if (book->Tagged != 1 ) {

			book = book->next;
			continue;

		}

		if (list_head==0) {

			list_head = cgc_malloc(sizeof(Shopping_List_Type));

			if (list_head == 0) {

				cgc_printf("unable to malloc memory\n");
				cgc__terminate(-1);
			}

			list = list_head;
			list->next = 0;

		}
		
		ingredient = book->Ingredient_List;

		while (ingredient) {

			list->item = ingredient->item;
			ingredient=ingredient->next;

			list->next = cgc_malloc(sizeof(Shopping_List_Type));

			if (list->next == 0) {

				cgc_printf("unable to malloc memory\n");
				cgc__terminate(-1);

			}

			previous = list;
			list = list->next;
			list->next = 0;
		}

		book = book->next;

	}

	if (list) {
		cgc_free(list);
		list = previous;
		list->next = 0;
	}

	return(list_head);

}


void cgc_print_shopping_list(Recipe_Type *book) {

Shopping_List_Type *my_list;
Shopping_List_Type *tmp_list;

	// first build a linked list of items from tagged recipes
	my_list = cgc_build_shopping_list(book);

	cgc_printf("\n");
	cgc_printf("Shopping List\n");
	cgc_printf("-------------\n");

	if (my_list != 0) {

		cgc_sort_shopping_list(my_list);
		tmp_list = my_list;

		while (tmp_list) {

			cgc_printf("@s\n", tmp_list->item);

			tmp_list= tmp_list->next;
		}

		// now free the linked list to hold the shopping list
		tmp_list = my_list->next;

		while( my_list) {

			cgc_free(my_list);

			my_list = tmp_list;

			if (tmp_list != 0)
				tmp_list = tmp_list->next;

		}

	}

	cgc_printf("\n");
}