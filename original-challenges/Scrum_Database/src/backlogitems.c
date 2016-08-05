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


int create_pbi( productDefType *database, newPBIMessageType *message ) {

backlogItemType *newPBI;
backlogItemType *PBIPtr;


	while(database != 0 && database->ID != message->productID )
		database = database->next;

	if (database == 0) {

		return(-1);
	}


	newPBI = (backlogItemType *)calloc(sizeof(backlogItemType));

	if (newPBI == 0) 
		_terminate(-1);


	newPBI->ID = message->pbItemID;
	newPBI->status = 0;
	newPBI->story_points = message->user_story_points;
	newPBI->next = 0;

	newPBI->description = calloc(strlen(&message->title)+1);

	if (newPBI->description == 0)
		_terminate(-1);


	strcpy(newPBI->description, &message->title);


	if (database->productBacklog == 0) {

		database->productBacklog = newPBI;
		return 0;
	}

	PBIPtr = database->productBacklog;

	while (PBIPtr->next != 0)
		PBIPtr = PBIPtr->next;

	PBIPtr->next = newPBI;


	return 0;
}


int delete_pbi( productDefType *database, deletePBIMessageType *message ) {

backlogItemType *prevPBI;
backlogItemType *PBIPtr;


	while(database != 0 && database->ID != message->productID )
		database = database->next;

	if (database == 0) {

		return(-1);
	}

	// now find the PBI entry

	PBIPtr = database->productBacklog;

	if (PBIPtr->ID == message->pbItemID) {

		database->productBacklog = PBIPtr->next;

	}
	else {
		prevPBI = PBIPtr;

		while (PBIPtr != 0 && PBIPtr->ID != message->pbItemID) {
			prevPBI = PBIPtr;
			PBIPtr = PBIPtr->next;
		}

		if (PBIPtr == 0) {

			return -1;

		}

		prevPBI->next = PBIPtr->next;
	}

	if (PBIPtr->description != 0) 
		free(PBIPtr->description);

	free(PBIPtr);

	return 0;

}



int move_pbi_to_sprint( productDefType *database, movePBIMessageType *message ) {

sprintEntryType *sprintPtr;
backlogItemType *PBIPtr;
backlogItemType *prevPtr;
backlogItemType *sprintBIPtr;


	// first find the product ID in the database
	while( database != 0 && database->ID != message->productID )
		database = database->next;

	if (database == 0) {

		return(-1);
	}


	// now find the target Sprint ID to ensure it exists
	sprintPtr = database->sprintList;

	while(sprintPtr != 0 && sprintPtr->ID != message->sprintID)
		sprintPtr = sprintPtr->next;

	if (sprintPtr == 0) {

		return(-1);

	}

	// now find the PBI entry

	PBIPtr = database->productBacklog;

	if (PBIPtr->ID == message->pbItemID) {

		database->productBacklog = PBIPtr->next;

	}
	else {
		prevPtr = PBIPtr;

		while (PBIPtr != 0 && PBIPtr->ID != message->pbItemID) {
			prevPtr = PBIPtr;
			PBIPtr = PBIPtr->next;
		}

		if (PBIPtr == 0) {

			return -1;

		}

		prevPtr->next = PBIPtr->next;
	}


	if (sprintPtr->sprintBacklogList == 0) {

		sprintPtr->sprintBacklogList = PBIPtr;
		PBIPtr->next = 0;
		return 0;
	}

	sprintBIPtr = sprintPtr->sprintBacklogList;

	while(sprintBIPtr->next != 0)
		sprintBIPtr = sprintBIPtr->next;

	sprintBIPtr->next = PBIPtr;

	PBIPtr->next = 0;

	// update the total number of points assigned to this sprint
	sprintPtr->total_points += PBIPtr->story_points;

	return 0;

}



int update_sbi_status( productDefType *database, updateSBIMessageType *message ) {

sprintEntryType *sprintPtr;
backlogItemType *SBIPtr;
backlogItemType *sprintBIPtr;


	// first find the product ID in the database
	while( database != 0 && database->ID != message->productID )
		database = database->next;

	if (database == 0) {

		return(-1);
	}


	// now find the target Sprint ID to ensure it exists
	sprintPtr = database->sprintList;

	while(sprintPtr != 0 && sprintPtr->ID != message->sprintID)
		sprintPtr = sprintPtr->next;

	if (sprintPtr == 0) {

		return(-1);

	}

	// now find the PBI entry

	SBIPtr = sprintPtr->sprintBacklogList;

	while (SBIPtr != 0 && SBIPtr->ID != message->pbItemID) {
		
		SBIPtr = SBIPtr->next;
	}

	if (SBIPtr == 0) {

		return -1;

	}

	SBIPtr->status = message->status;

	return 0;

}



int update_sbi_points( productDefType *database, updateSBIMessageType *message ) {

sprintEntryType *sprintPtr;
backlogItemType *SBIPtr;
backlogItemType *sprintBIPtr;


	// first find the product ID in the database
	while( database != 0 && database->ID != message->productID )
		database = database->next;

	if (database == 0) {

		return(-1);
	}


	// now find the target Sprint ID to ensure it exists
	sprintPtr = database->sprintList;

	while(sprintPtr != 0 && sprintPtr->ID != message->sprintID)
		sprintPtr = sprintPtr->next;

	if (sprintPtr == 0) {

		return(-1);

	}

	// now find the PBI entry

	SBIPtr = sprintPtr->sprintBacklogList;

	while (SBIPtr != 0 && SBIPtr->ID != message->pbItemID) {
		
		SBIPtr = SBIPtr->next;
	}

	if (SBIPtr == 0) {

		return -1;

	}

	// update the total story points with the change
	sprintPtr->total_points -= SBIPtr->story_points;
	sprintPtr->total_points += message->status;

	SBIPtr->story_points = message->status;

	return 0;

}


int update_sbi_description( productDefType *database, updateSBIDescMessageType *message ) {

sprintEntryType *sprintPtr;
backlogItemType *SBIPtr;
backlogItemType *sprintBIPtr;


	// first find the product ID in the database
	while( database != 0 && database->ID != message->productID )
		database = database->next;

	if (database == 0) {

		return(-1);
	}


	// now find the target Sprint ID to ensure it exists
	sprintPtr = database->sprintList;

	while(sprintPtr != 0 && sprintPtr->ID != message->sprintID)
		sprintPtr = sprintPtr->next;

	if (sprintPtr == 0) {

		return(-1);

	}

	// now find the BI entry

	SBIPtr = sprintPtr->sprintBacklogList;

	while (SBIPtr != 0 && SBIPtr->ID != message->pbItemID) {
		
		SBIPtr = SBIPtr->next;
	}

	if (SBIPtr == 0) {

		return -1;

	}

#ifdef PATCHED_1

	free(SBIPtr->description);

	SBIPtr->description = malloc(strlen(&message->desc)+1);

	if (SBIPtr->description == 0)
		_terminate(-1);

#endif

	strcpy(SBIPtr->description, &message->desc);

	return 0;

}


int move_sbi_to_pbl( productDefType *database, moveToPBIMessageType *message ) {

sprintEntryType *sprintPtr;
backlogItemType *PBIPtr;
backlogItemType *prevPtr;
backlogItemType *SBIPtr;

	// first find the product ID in the database
	while( database != 0 && database->ID != message->productID )
		database = database->next;

	if (database == 0) {

		return(-1);
	}


	sprintPtr = database->sprintList;
	PBIPtr = database->productBacklog;

	// now find the target Sprint ID to ensure it exists
	while(sprintPtr != 0 && sprintPtr->ID != message->sprintID)
		sprintPtr = sprintPtr->next;

	if (sprintPtr == 0) {

		return(-1);

	}

	// now find the BI entry

	SBIPtr = sprintPtr->sprintBacklogList;
	prevPtr = SBIPtr;

	while (SBIPtr != 0 && SBIPtr->ID != message->pbItemID) {
		
		prevPtr = SBIPtr;
		SBIPtr = SBIPtr->next;
	}

	if (SBIPtr == 0) {

		return -1;

	}

	if (SBIPtr == sprintPtr->sprintBacklogList) {

		sprintPtr->sprintBacklogList = sprintPtr->sprintBacklogList->next;
	}
	else {

		prevPtr->next = SBIPtr->next;
	}

	SBIPtr->next = 0;

	if (PBIPtr == 0) {

		database->productBacklog = SBIPtr;
	}
	else {

		while(PBIPtr->next != 0)	
			PBIPtr = PBIPtr->next;	

		PBIPtr->next = SBIPtr;
	}

	// update the sprint's total points 
	sprintPtr->total_points -= SBIPtr->story_points;

	return 0;

}


