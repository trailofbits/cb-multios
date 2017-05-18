/*

Author: Steve Wood <swood@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_commands.h"
#include "cgc_output_strings.h"
#include "cgc_malloc.h"

char *cgc_obf_strings(char *input_string);

int cgc_create_product( productDefType **database, void *command_data ) {

newProductMessageType *msg;
productDefType *newProduct;

	msg = (newProductMessageType *)command_data;

	// special case if this is the first product
	if (*database == 0) {

		*database = cgc_calloc(sizeof(productDefType));

		if (*database == 0)
			cgc__terminate(-1);

		newProduct = *database;

	}
	else {

		newProduct = *database;

		// add this new product to the end of the list
		while(newProduct->ID != msg->ID && newProduct->next != 0)
			newProduct = newProduct->next;

		// if this ID is already in the database, fail 
		if (newProduct->ID == msg->ID)
			return(-1);

		// otherwise add this new product to the end of the list
		newProduct->next = (productDefType *)cgc_calloc(sizeof(productDefType));

		if (newProduct->next == 0)
			cgc__terminate(-1);


		newProduct = newProduct->next;
	}

	newProduct->next = 0;
	newProduct->ID = msg->ID;
	newProduct->productBacklog = 0;
	newProduct->sprintList = 0;

	// allocate memory for the title
	newProduct->title = cgc_calloc(cgc_strlen((char *)&msg->title)+1);

	if (newProduct->title == 0)
		cgc__terminate(-1);


	cgc_strncpy(newProduct->title, (char *)&msg->title, cgc_strlen(&msg->title));

	return 0;
}



int cgc_delete_product( productDefType **database, messageIDType *message ) {


productDefType *lastProduct, *tmpProduct;
sprintEntryType *sprintPtr, *tmpSprintPtr;
backlogItemType *PBIPtr, *tmpPBIPtr;


	// nothing to delete here, move along
	if (*database == 0)  {

		return(-1);
	}

	// is the matching entry the head of the linked list?
	if ((*database)->ID == message->ID) {

		tmpProduct = *database;
		*database = (*database)->next;

		// if there's a title, free that memory
		if (tmpProduct->title)
			cgc_free(tmpProduct->title);

		// now free the Sprint list
		sprintPtr = tmpProduct->sprintList;

		while (sprintPtr!= 0) {

			PBIPtr = sprintPtr->sprintBacklogList;

			// first free the backlog items tied to this Sprint
			while (PBIPtr != 0) {

				if (PBIPtr->description != 0)
					cgc_free(PBIPtr->description);

				tmpPBIPtr = PBIPtr;
				PBIPtr = PBIPtr->next;

				cgc_free(tmpPBIPtr);
			}

			// free the memory for the sprint title
			if (sprintPtr->title != 0)
				cgc_free(sprintPtr->title);


			// now free the sprint memory itself
			tmpSprintPtr = sprintPtr;

			sprintPtr = sprintPtr->next;

			cgc_free(tmpSprintPtr);

		}

		// now free the PBI list
		PBIPtr = tmpProduct->productBacklog;

		while (PBIPtr != 0) {


			if (PBIPtr->description != 0)
				cgc_free(PBIPtr->description);

			tmpPBIPtr = PBIPtr;
			PBIPtr = PBIPtr->next;

			cgc_free(tmpPBIPtr);

		}

		// now free the final object
		cgc_free(tmpProduct);

		return(0);

	}

	// the entry to delete wasn't the head, so find it in the list
	lastProduct = *database;
	tmpProduct = (*database)->next;


	while (tmpProduct != 0 && tmpProduct->ID != message->ID  ) {

		lastProduct = tmpProduct;
		tmpProduct = tmpProduct->next;
	}

	// it wasn't found by the end of the list was reached
	if (tmpProduct == 0 ) {

		return(-1);
	}

	// link around the entry to be deleted
	lastProduct->next = tmpProduct->next;

	// free the title memory
	if (tmpProduct->title)
		cgc_free(tmpProduct->title);


	// now free the PBI
	PBIPtr = tmpProduct->productBacklog;

	while (PBIPtr != 0) {

		tmpPBIPtr = PBIPtr;

		if (PBIPtr->description != 0)
			cgc_free(PBIPtr->description);

		PBIPtr = PBIPtr->next;

		cgc_free(tmpPBIPtr);

	}

	// now free the Sprints
	sprintPtr = tmpProduct->sprintList;

	while (sprintPtr!= 0) {

		PBIPtr = sprintPtr->sprintBacklogList;

		// first free the backlog items tied to this Sprint
		while (PBIPtr != 0) {

			if (PBIPtr->description != 0)
				cgc_free(PBIPtr->description);

			tmpPBIPtr = PBIPtr;
			PBIPtr = PBIPtr->next;

			cgc_free(tmpPBIPtr);
		}

		// free the memory for the sprint title
		if (sprintPtr->title != 0)
			cgc_free(sprintPtr->title);


		// now free the sprint memory itself
		tmpSprintPtr = sprintPtr;

		sprintPtr = sprintPtr->next;

		cgc_free(tmpSprintPtr);

	}

	cgc_free(tmpProduct);

	return 0;
}

int cgc_list_all_products( productDefType *database) {


	if (database == 0)
		return (-1);

	while (database != 0 ) {


		cgc_printf(cgc_obf_strings(cgc_List_Products), database->title);

		database = database->next;

	}
	cgc_printf("\n");

	return 0;

}


int cgc_list_product( productDefType *database, messageIDType *message) {

sprintEntryType *sprintPtr;
backlogItemType *PBIPtr;


	if (message->ID == 0) {

		cgc_list_all_products(database);
		return 0;

	}

	while(database != 0 && database->ID != message->ID )
		database = database->next;

	if (database == 0) {

		return(-1);
	}

	cgc_printf("\n");
	cgc_printf(cgc_obf_strings(cgc_Prod_Title), database->title);
	cgc_printf(cgc_obf_strings(cgc_Prod_ID), database->ID);
	cgc_printf("\n");

	PBIPtr = database->productBacklog;

	cgc_printf(cgc_obf_strings(cgc_Prod_Backlog));
	cgc_printf(cgc_obf_strings(cgc_Prod_Backlog2));
	
	while (PBIPtr != 0) {

		// cgc_printf(obf_strings(Prod_Backlog3), PBIPtr->ID, PBIPtr->story_points, PBIPtr->description);
		cgc_printf(cgc_obf_strings(cgc_Prod_Backlog3), PBIPtr->ID, PBIPtr->story_points);
		PBIPtr = PBIPtr->next;
	}

	cgc_printf("\n");

	sprintPtr = database->sprintList;
	cgc_printf(cgc_obf_strings(cgc_Sprints_Title));

	while (sprintPtr != 0) {

		cgc_printf(cgc_obf_strings(cgc_Sprint_Entry), sprintPtr->ID, sprintPtr->title);

		PBIPtr = sprintPtr->sprintBacklogList;

		while (PBIPtr != 0) {
			// cgc_printf(obf_strings(SBI_Entry), PBIPtr->ID, PBIPtr->story_points, PBIPtr->status, PBIPtr->description);
			cgc_printf(cgc_obf_strings(cgc_SBI_Entry), PBIPtr->ID, PBIPtr->story_points, PBIPtr->status);

			PBIPtr = PBIPtr->next;
		}

		cgc_printf("\n");
		sprintPtr = sprintPtr->next;

	}

	cgc_printf("\n");
	return(0);

}




