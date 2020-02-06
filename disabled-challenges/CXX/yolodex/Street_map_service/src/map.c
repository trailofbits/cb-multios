/*

Author: James Connor (jymbo@cromulence.co)

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
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_mymath.h"
#include "cgc_service.h"
#include "cgc_llist.h"

#include "cgc_map.h"


/*
graph traversal service that emulates a street map.  
provides routing from point to point 
map can be created/edited by adding streets, intersections, 
and addresses
*/


pmap cgc_init_map(char mapName[32]){
	pmap thisMap;
	if (  cgc_allocate( sizeof(map), 0, (void**)&thisMap ) != 0  ){
	cgc_puts("\n**Allocate returned an error.\n");
	cgc__terminate(1);
	}
	cgc_strcpy(thisMap->name, mapName);
	thisMap->name[31] = 0;
	thisMap->roadList = cgc_create_double_list();
	return thisMap;
}


proad cgc_add_road(pmap thisMap, char roadName[32], double roadLength){
	proad thisRoad = NULL;
	pdListNode thisNode = NULL;
	pdListNode lastRoadNode = cgc_get_last_element_d(thisMap->roadList);
	thisNode = cgc_insert_double_list_node(thisMap->roadList, lastRoadNode);
	thisRoad = (proad)thisNode->data;
	cgc_strcpy(thisRoad->name, roadName);
	thisRoad->name[cgc_strlen(roadName)] = 0;
	thisRoad->length = roadLength;
	thisRoad->addressList = cgc_create_double_list();
	thisRoad->intersectionList = cgc_create_double_list();
	thisRoad->self = thisNode;
	return thisRoad;

}

void cgc_print_roads(pmap thisMap){
	proad thisRoad;
	//check for empty map
	if (thisMap->roadList->listRoot != NULL){
		thisRoad = (proad)thisMap->roadList->listRoot->data;
	}else{
		thisRoad = NULL;
	}
	cgc_printf("The map @s contains @d roads.\n", thisMap->name, thisMap->roadList->count);
	int i = 1;
	while (thisRoad != NULL){
		cgc_printf("(@d) @s is @f units long\n", i, thisRoad->name, thisRoad->length);
		i++;
		if (thisRoad->self->next != NULL){
			thisRoad = (proad)thisRoad->self->next->data;
		}else{
			thisRoad = NULL;
		}
	}

	//print all road names and length for map
	return;
}
//returns null if not found

//insert address in list after last address in list with lower or equal number, if equal numbers new is inserted after last. 
paddress cgc_add_address ( int number, char resident[32], proad thisRoad, pintersection prevIntersection,
 						double distance_to_prev, pintersection nextIntersection, double distance_to_next ){
	address tempAddress;
	paddress thisAddress = &tempAddress;
	pdListNode thisNode = NULL;
	pdListNode prevNode = NULL;
	paddress nextAddress = NULL;
	paddress prevAddress = NULL;
	cgc_bzero(thisAddress, sizeof(address));
	//if empty addressList or first entry is higher number, insert at begining(prevAddress = NULL)
	if (thisRoad->addressList->listRoot != NULL){
		nextAddress = (paddress)thisRoad->addressList->listRoot->data;
	}
	//find where to insert new address in list
	while(nextAddress != NULL){
		//if next address number is higher, break, prevaddress will be set to NULL or prev.
		if (nextAddress->number > number){
			 nextAddress = NULL;
		//else set prevaddress to nextaddress and if there is a next loop, else break	 
		}else{
			prevAddress = nextAddress;
			if (nextAddress->self->next != NULL){
				nextAddress = (paddress)nextAddress->self->next->data;
			} else{nextAddress = NULL;}
		}
	}
	// at this point prevaddress is either NULL (insert at begining), or an address pointer
	if (prevAddress != NULL){
		prevNode = prevAddress->self;
	}

	thisNode = cgc_insert_double_list_node(thisRoad->addressList, prevNode);
	if (thisNode == NULL){
		cgc_puts("**insert_double_list_node failed");
		return NULL;
	}
	thisAddress->number = number;
	cgc_strcpy(thisAddress->resident, resident);
	thisAddress->resident[31] = 0;
	thisAddress->thisRoad = thisRoad;
	thisAddress->prevIntersection = prevIntersection;
	thisAddress->distance_to_prev = distance_to_prev;
	thisAddress->nextIntersection = nextIntersection;
	thisAddress->distance_to_next = distance_to_next;
	thisAddress->self = thisNode;
	cgc_memcpy( thisNode->data, thisAddress, sizeof(address) );
	return (paddress)thisNode->data;
}

void cgc_print_addresses(proad thisRoad){
	paddress thisAddress;
	//check for empty map
	if (thisRoad->addressList->listRoot != NULL){
		thisAddress = (paddress)thisRoad->addressList->listRoot->data;
	}else{
		thisAddress = NULL;
	}
	cgc_printf("The road @s contains @d addresses.\n", thisRoad->name, thisRoad->addressList->count);
	int i = 1;
	while (thisAddress != NULL){
		cgc_printf("(@d)\t@s\n\t@d @s\n", i, thisAddress->resident, thisAddress->number, thisRoad->name);
		i++;
		if (thisAddress->self->next != NULL){
			thisAddress = (paddress)thisAddress->self->next->data;
		}else{
			thisAddress = NULL;
		}
	}

	//print all road names and length for map
	return;
}

//on insert, have update prev and next for prevIntersection and nexIntersection, or you have a problem. data inside data is ugly
//if prevInterseciton is NULL, insert at begining, else insert at prevIntersection.
pintersection cgc_add_intersection ( proad thisRoad, proad other_road, pintersection prevIntersection, double distance_to_prev, double distance_to_next ){
	intersection tempIntersection;
	pintersection newIntersection = NULL;
	pdListNode newNode;
	pdListNode prevIntersectionNode = NULL;
	pintersection nextIntersection = NULL;
	if (prevIntersection != NULL){
		prevIntersectionNode = prevIntersection->self;
	}

	newNode = cgc_insert_double_list_node(thisRoad->intersectionList, prevIntersectionNode);
	if (newNode == NULL){
		cgc_puts("Failed to insert node");
		return NULL;
	} 
	newIntersection = (pintersection)newNode->data;

	if (prevIntersection != NULL){
		prevIntersection->nextIntersection = (pintersection)newNode->data;
	}
	if (newNode->next != NULL){
		nextIntersection = (pintersection)newNode->next->data;
		nextIntersection->prevIntersection = newIntersection;
	}

	newIntersection->prevIntersection = prevIntersection;
	newIntersection->nextIntersection = nextIntersection;
	newIntersection->self = newNode;
	newIntersection->other_road = other_road;
	newIntersection->distance_to_prev = distance_to_prev;
	newIntersection->distance_to_next = distance_to_next;
	return newIntersection;
}

void cgc_print_intersections(proad thisRoad){
	pintersection thisIntersection = NULL;
	if (thisRoad->intersectionList->listRoot != NULL){
		thisIntersection = (pintersection)thisRoad->intersectionList->listRoot->data;
	}
	cgc_printf("The road @s contains @d intersections.\n", thisRoad->name, thisRoad->intersectionList->count);
	int i = 1;
	while (thisIntersection != NULL){
		cgc_printf("(@d)\t@s intersects @s\n", i, thisRoad->name, thisIntersection->other_road->name );
		i++;
		if (thisIntersection->prevIntersection != NULL){
			cgc_printf("\t\t@f units after the intersection of @s\n",thisIntersection->distance_to_prev, 
					thisIntersection->prevIntersection->other_road->name);
		}
		if (thisIntersection->nextIntersection != NULL){
			cgc_printf("\t\t@f units before the intersection of @s\n", thisIntersection->distance_to_next, 
					thisIntersection->nextIntersection->other_road->name);
		}
		if (thisIntersection->self->next != NULL){
			thisIntersection = (pintersection)thisIntersection->self->next->data;
		}else {thisIntersection = NULL;}
	}
	return;
}

//returns pintersection which contains reference to searchpIntersection
//finding next for findall is (pintersection)pintersectionReturned->self->next->data
pintersection cgc_find_pintersection(proad thisRoad, pintersection searchpIntersection, pintersection startIntersection){
	pintersection tempIntersection = NULL;
	if (thisRoad->intersectionList->count == 0){
		cgc_puts("intersection list is empty");
		return (pintersection)NULL;
	}
	if (startIntersection == NULL){
		tempIntersection = (pintersection)thisRoad->intersectionList->listRoot->data;
	}else{
		tempIntersection = startIntersection;
	}
	while (tempIntersection != NULL){
		if ( (tempIntersection->prevIntersection == searchpIntersection) || 
			 (tempIntersection->nextIntersection == searchpIntersection) ){
			return tempIntersection;
		}
		if (tempIntersection->self->next != NULL){
			tempIntersection = (pintersection)tempIntersection->self->next->data;
		}else{
			tempIntersection = NULL;
		}
	}
	return NULL;
}

paddress cgc_find_pintersection_addresses(proad thisRoad, pintersection searchpIntersection, paddress startAddress){
	paddress tempAddress = NULL;
	if (startAddress == NULL){
		if(thisRoad->addressList->count == 0){
			cgc_puts("addresss list is empty");
			return (paddress)NULL;
		}
		tempAddress = (paddress) thisRoad->addressList->listRoot->data;
	}else{
		tempAddress = startAddress;
	}
	while (tempAddress != NULL){
		if ( (tempAddress->prevIntersection == searchpIntersection) ||
			(tempAddress->nextIntersection == searchpIntersection) ){
			return tempAddress;
		}
		if (tempAddress->self->next != NULL){
			tempAddress = (paddress)tempAddress->self->next->data;
		}else{
			tempAddress = NULL;
		}
	}

	return NULL;
}
//deletes intersection and set any reference to pintersection to prev or next or null
pintersection cgc_delete_intersection(proad thisRoad, pintersection deletedIntersection){
	pintersection tempIntersection =  NULL;
	pintersection thisIntersection = NULL;
	pdListNode thisNode = NULL;
	//check for pointers to the deleted intersection 
	pintersection refIntersection = cgc_find_pintersection(thisRoad, deletedIntersection, NULL);
	while (refIntersection != NULL){
		// if prevIntersection is the match, replace with deleted->prev or NULL
		if (refIntersection->prevIntersection == deletedIntersection){
			if (deletedIntersection->self->prev != NULL){
				refIntersection->prevIntersection = (pintersection)deletedIntersection->self->prev->data;
			}else{ 
				refIntersection->prevIntersection = NULL;
			}
		// if nextIntersection is the match, replace with deleted->next or NULL
		}else {
			if (deletedIntersection->self->next != NULL){
				refIntersection->nextIntersection = (pintersection)deletedIntersection->self->next->data;
			}else{ 
				refIntersection->nextIntersection = NULL;
			}
		}
		refIntersection = cgc_find_pintersection(thisRoad, deletedIntersection, refIntersection);
	}
	//check for pointers to deleted intersection in addresses
	paddress refAddress = cgc_find_pintersection_addresses(thisRoad, deletedIntersection, NULL);
	while (refAddress != NULL){
		//if prevIntersection is the match, replace with deleted->next or NULL
		if (refAddress->prevIntersection == deletedIntersection){
			if (deletedIntersection->self->prev != NULL){
				refAddress->prevIntersection = (pintersection)deletedIntersection->self->prev->data;
			}else{
				refAddress->prevIntersection = NULL;
			}
	// if nextIntersection is the match, replace with deleted->next or NULL			
		}else {
			if (deletedIntersection->self->next != NULL){
				refAddress->nextIntersection = (pintersection)deletedIntersection->self->next->data;
			}else{
				refAddress->nextIntersection = NULL;
			}
		}
		refAddress = cgc_find_pintersection_addresses(thisRoad,deletedIntersection, refAddress);
	}
	thisNode = cgc_delete_double_list_node(thisRoad->intersectionList, deletedIntersection->self);
	if (thisNode == NULL){
		return NULL;
	}
	return (pintersection)thisNode->data;
}


int cgc_is_in_turn_list(psList turnList, proad thisRoad){
	unsigned int i = 0;
	prouteList thisRouteList = NULL;
	if (turnList->listRoot == NULL){
		return 0;
	}
	thisRouteList = (prouteList)turnList->listRoot->data;
	while(thisRouteList->thisRoad != NULL){
		if (thisRouteList->thisRoad == thisRoad){
			return 1;
		}
		thisRouteList = (prouteList)(  (unsigned)turnList->listRoot->data + (unsigned int)( sizeof(routeList) * (i) )  );
		i++;
	}
	return 0;
}

psList cgc_init_turnList(){
	psList thisList = NULL;
	thisList = cgc_create_single_list();
	cgc_insert_single_list_node(thisList, NULL);
	return thisList;
}

prouteList cgc_push_to_turn_list(pmap thisMap, psList turnList, proad thisRoad, prouteList parent){
	prouteList thisRouteList = NULL;


#ifdef PATCHED
	//32
	if (  (turnList->listRoot->count) > ( 3800/(sizeof(routeList)) )  ){
		return NULL;
	}
#endif

#ifndef PATCHED
	//CWE-467 use of sizeof() on pointer type
	//1020
	if (  (turnList->listRoot->count) > ( 3800/(sizeof(prouteList)) )  ){
		return NULL;
	}
#endif	
	thisRouteList = (prouteList)(  (unsigned)turnList->listRoot->data + (unsigned int)( sizeof(routeList) * (unsigned int)(turnList->listRoot->count) )  );
	cgc_bzero(thisRouteList, sizeof(routeList));
	thisRouteList->thisRoad = thisRoad;
	thisRouteList->parent = parent;
	turnList->listRoot->count++;
	return thisRouteList;
}

psList cgc_get_route(pmap thisMap, psList turnList, proad targetRoad, proad startRoad){

	unsigned int curRouteListCount = 0;
//	turnList->count--;
//	turnList->count = 0;
	turnList->listRoot->count = 0;
	cgc_bzero(turnList->listRoot->data, 4080);
//
//	bzero(turnList->listRoot->count, sizeof(int));
//	
	prouteList curRouteList = cgc_push_to_turn_list(thisMap, turnList, startRoad, NULL);
	proad curRoad = NULL; 
	proad intersectionOtherRoad = NULL;
	pintersection thisIntersection = NULL;
	while (curRouteList->thisRoad != NULL){
		curRoad = curRouteList->thisRoad;
		if (curRoad->intersectionList->listRoot != NULL){
			thisIntersection = (pintersection)curRoad->intersectionList->listRoot->data;
		}else{thisIntersection = NULL;}
		while (thisIntersection != NULL){
			intersectionOtherRoad = thisIntersection->other_road;
			if ( !(cgc_is_in_turn_list(turnList, intersectionOtherRoad)) ){
				prouteList result = cgc_push_to_turn_list(thisMap, turnList, intersectionOtherRoad, curRouteList);
				if (result == NULL){
					return NULL; 
				}
				if (intersectionOtherRoad == targetRoad){
					return turnList;
				}
			}
			//move to next intersection if there is another
			if (thisIntersection->self->next != NULL){
				thisIntersection = (pintersection)thisIntersection->self->next->data;
			}else {thisIntersection = NULL;}
			//end while(curIntersection != NULL)
			}
		curRouteListCount++;
		curRouteList = (prouteList) (  (unsigned int)curRouteList  +  (unsigned int)(sizeof(routeList))  );
	}
	return NULL;
}


