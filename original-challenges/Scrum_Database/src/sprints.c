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


#include <libcgc.h>
#include "stdlib.h"
#include "service.h"
#include "stdio.h"
#include "string.h"
#include "commands.h"
#include "malloc.h"

int create_sprint( productDefType *database, newSprintMessageType *message) {

sprintEntryType *newSprint;
sprintEntryType *sprintPtr;


	// first find the product ID 
	while(database != 0 && database->ID != message->productID )
		database = database->next;

	// it wasn't found
	if (database == 0) {

		return(-1);
	}


	// allocate memory for the new sprint
	newSprint = (sprintEntryType *)calloc(sizeof(sprintEntryType));

	if (newSprint == 0)
		_terminate(-1);

	newSprint->ID = message->sprintID;

	// add an extra byte since strlen doesn't count the null terminator
	newSprint->title = calloc(strlen((char *)&message->title)+1);

	if (newSprint->title == 0)
		_terminate(-1);


	strncpy(newSprint->title, &message->title, strlen(&message->title));

	// set the default values, all 0 in this case
	newSprint->duration = 0;
	newSprint->total_points = 0;
	newSprint->velocity_required = 0;
	newSprint->sprintBacklogList = 0;
	newSprint->next = 0;


	// if this is the first sprint, it changes the head pointer so its a special case
	if (database->sprintList == 0) {
		database->sprintList = newSprint;
		return 0;
	}

	sprintPtr = database->sprintList;

	// otherwise find the end of the linked list
	while(sprintPtr->next != 0)
		sprintPtr = sprintPtr->next;

	// now add the new sprint to the end
	sprintPtr->next = newSprint;

return 0;

}


int delete_sprint( productDefType *database, deleteSprintMessageType *message) {


sprintEntryType *sprintPtr;
sprintEntryType *prevPtr;


	// find the product id 
	while(database != 0 && database->ID != message->productID )
		database = database->next;

	// it wasn't found
	if (database == 0) {

		return(-1);
	}

	// if the sprint list is empty, there's nothing to delete
	if (database->sprintList == 0) {

		return (-1);
	}

	// if its the head of the linked list, special case to delete
	if (database->sprintList->ID == message->sprintID) {

		// don't delete a sprint that still has backlog items assigned to it
		if (database->sprintList->sprintBacklogList != 0)
			return(-1);

		sprintPtr = database->sprintList;
		database->sprintList = sprintPtr->next;

		// does it have a title?  Free that memory first
		if (sprintPtr->title)
			free(sprintPtr->title);

		free(sprintPtr);
		return 0;

	}
	// otherwise, just link around the entry to be deleted
	else {

		prevPtr = database->sprintList;
		sprintPtr = prevPtr->next;

		while(sprintPtr != 0 && sprintPtr->ID != message->sprintID) {
			prevPtr = sprintPtr;
			sprintPtr = sprintPtr->next;
		}
	}

	// it wasn't found if we hit the end of the list
	if (sprintPtr == 0) {

		return(-1);
	}
	else {

			// don't delete a sprint that still has backlog items assigned to it
		if (sprintPtr->sprintBacklogList != 0)
			return(-1);
		
		prevPtr->next = sprintPtr->next;

	}

	// does it have a title?  Free that memory first
	if (sprintPtr->title)
		free(sprintPtr->title);
		
	// now delete the sprint's memory
	free(sprintPtr);


	return 0;

}


