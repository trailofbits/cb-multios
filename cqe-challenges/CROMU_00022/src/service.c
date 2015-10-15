/*

Author: James Connor (jymbo@cromulence.co)

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
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <mymath.h>
#include <malloc.h>
#include "service.h"
#include "ui.h"


pDiverInfo init_data(){
	pDiverInfo workingData = NULL;
	workingData = malloc( sizeof( sDiverInfo ) );
	if ( workingData == NULL ){ _terminate( -2 );}
	return workingData;
}

void destroy_data( pDiverInfo workingData ){
	free( workingData );
}

//dive is linked list
//cases first entry in list, last entry in list (always add at the end)
//returns pointer to diveentrynew
pDiveEntry AddDive( pDiverInfo DiverInfo ){
	pDiveEntryListNode DiveEntryListCur = NULL ;
	pDiveEntryListNode DiveEntryListTemp;
	//linked list node
	pDiveEntryListNode DiveEntryListNew = malloc( sizeof( sDiveEntryListNode ) );
	//data element
	pDiveEntry DiveEntryNew = malloc( sizeof( sDiveEntry ) );
	//if malloc fails, exit
	if (  ( DiveEntryNew == NULL ) || ( DiveEntryListNew == NULL )  ) { _terminate( -2 );}

	//add data element to linked list node
	DiveEntryListNew->DiveEntry = DiveEntryNew;
	DiveEntryListNew->next = NULL;

	DiveEntryListTemp = DiverInfo->DiveEntryList;
	DiveEntryListCur = DiveEntryListTemp;
	//if first in list
	if ( DiveEntryListTemp == NULL ) {
		DiverInfo->DiveEntryList = DiveEntryListNew;
		DiveEntryListNew->prev = NULL;
		DiverInfo->DiveEntryCount = 1;
		//diveentry 
	}else { //not first in list, add to end of list
		while ( DiveEntryListTemp != NULL ){
			DiveEntryListCur = DiveEntryListTemp;
			DiveEntryListTemp = DiveEntryListTemp->next;
		}
		//temp is null, Cur is last
		DiveEntryListCur->next = DiveEntryListNew;
		DiveEntryListNew->prev = DiveEntryListCur;
		DiverInfo->DiveEntryCount += 1;

	}
	return DiveEntryNew;
}

//deletes and frees diveentry and diveentrylistnode
//returns pointer to prev listnode or null if head is deleted
//to delete all dives, delete last, and keep deleting until returns null
//five cases: 
//	pointer is invalid/not in list, 
//	pointer is only node, free and set diveentrylist to null
//	pointer is first but not only, free and set diveentrylist to next, next->prev to null
//	pointer is middle, free and set prev->next to next, next->prev to prev
//	pointer is last but not only. free set prev->next to next (which is null)
//reduces to if exists, only, not first, and not last (4 cases)
pDiveEntryListNode DeleteDive( pDiverInfo DiverInfo, pDiveEntryListNode DiveEntryListNodeToDelete ){
	pDiveEntryListNode DiveEntryListPrev = NULL;
	pDiveEntryListNode DiveEntryListTemp = NULL;
	pDiveEntryListNode DiveEntryListCur  = NULL;
	DiveEntryListTemp = DiverInfo->DiveEntryList;
	while (  ( DiveEntryListTemp != NULL )&&( DiveEntryListTemp != DiveEntryListNodeToDelete )  ){
		DiveEntryListTemp = DiveEntryListTemp->next;
	}
	
	if ( DiveEntryListTemp == NULL ){
		return NULL;
	}
	//there is a prev entry (not first)
	if ( DiveEntryListNodeToDelete->prev != NULL ){
		DiveEntryListNodeToDelete->prev->next = DiveEntryListNodeToDelete->next;
		DiveEntryListPrev = DiveEntryListNodeToDelete->prev;
	}
	//there is a next entry (not last)
	if ( DiveEntryListNodeToDelete->next != NULL ){
		DiveEntryListNodeToDelete->next->prev = DiveEntryListNodeToDelete->prev;
	}
	if ( DiveEntryListNodeToDelete == DiverInfo->DiveEntryList ){
		DiverInfo->DiveEntryList = DiverInfo->DiveEntryList->next;
	}
	free(DiveEntryListNodeToDelete->DiveEntry);
	free(DiveEntryListNodeToDelete);	
	return DiveEntryListPrev;
}

int main(){
	pDiverInfo workingData = init_data();
	MainMenu( workingData );
	destroy_data( workingData );
	return 1;
}
