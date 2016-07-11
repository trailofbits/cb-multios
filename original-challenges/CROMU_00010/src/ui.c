/*

Author: James Connor <jymbo@cromulence.com>

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
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <mymath.h>
#include "service.h"
#include "llist.h"
#include "map.h"

#define NAME_MAP 0x41 			//A
#define ADDROAD 0x42 			//B
#define ADDADDRESS 0x43			//C
#define ADDINTERSECTION 0x44	//D
#define PRINTMAP 0x45			//E
#define FINDROUTE 0x49			//I

#define NUMBER 0x4E				//N
#define LIST 0x4C				//L
#define NOTDEFINED 0x4F			//O
#define EXIT 0x30				//0
#define DELIM 0x0A				//\n


void name_map(pmap map){
	char mapName[32];
	printf("Name:\n");
	int result = receive_until(mapName, DELIM, 31);
	if (result > 0){
		mapName[result] = 0;
		printf("Map @s is now named @s.\n",map->name, mapName);
		strcpy(map->name,mapName);
	}else{
		puts("Name not set.");
	}
	return;
}

double get_positive_float(){
	double fnum = 0.0;
	char cnum[11];
	int result = receive_until(cnum, DELIM, 10);
	cnum[result] = 0;
	fnum = atof(cnum);
	if (fnum > 0.0){
		return fnum;
	}
	return 0.0;

}

int get_positive_int(){
	char cnum[9];
	int retVal = 0;
	int result = receive_until(cnum, DELIM, 8);
	cnum[result] = 0;
	retVal = atoi(cnum);
	if (retVal > 0){
		return retVal;
	}
	return 0;
}

void get_char32(char *char32){
	char retChar[32];
	memset(retChar, 0, 32);
	int result = receive_until(retChar, DELIM, 31);
	retChar[result] = 0;
	memset(char32, 0, 32);
	if (strlen(retChar)>0){
		strcpy (char32, retChar);
	}
	return;
} 

void print_map_info(pmap map){
	puts("Map Info");
	printf("Map Name: @s Number of Roads: @d\n", map->name, map->roadList->count);
	puts("Road List:");
	if (map->roadList->listRoot == NULL){
		puts("End of road list");
		return;
	}
	proad thisRoad = (proad)map->roadList->listRoot->data;
	while (thisRoad !=NULL){
		printf("@s is @f units long\n",thisRoad->name, thisRoad->length);
		puts("IntersectionList:");
		print_intersections(thisRoad);
		puts("AddressList:");
		print_addresses(thisRoad);
		if (thisRoad->self->next == NULL){
			thisRoad = NULL;
		}else{
			thisRoad = (proad)thisRoad->self->next->data;
		}

	}
	puts("End of road list");
	return;
}

void add_new_road(pmap map){
	char name[32];
	double flength = 0;
	proad thisRoad = NULL;
	if (map->roadList->count >= 50){
		puts("No more roads allowed.(Limit)");
		return;
	}
	printf("Road Name:\n");
	int result = receive_until(name, DELIM, 31);
	name[result] = 0;
	printf("Road Length:\n");
	flength = get_positive_float();
	if ( (flength > 0.0)&&(strlen(name)!=0) ){
		thisRoad = add_road(map, name, flength);
	}else {
		puts("Invalid Road.");
	}
	return;
}

proad select_road(pmap thisMap){
	proad thisRoad = NULL;
	char choice[3];
	int loop = 1;
	if (thisMap->roadList->count == 1){
		puts("Only road selected.");
		thisRoad = (proad)thisMap->roadList->listRoot->data;
		return thisRoad;
	}
	if (thisMap->roadList->count == 0){
		return NULL;
	}
	while (loop){
		memset (choice, 0, 3);
		puts("Select Road by (N)umber, or (L)ist or (0)Exit.");
		printf("choice:\n");
		int result = receive_until(choice, DELIM, 2);
		switch (choice[0]){
			case LIST:
				print_roads(thisMap);
				break;
			case NUMBER:
				printf("1-@d:\n",thisMap->roadList->count);
				int number = get_positive_int();
				if ( number == 0 ){
					puts("Invalid number. (0)");
					break;
				}
				if (thisMap->roadList->count >= number){
					thisRoad = (proad) thisMap->roadList->listRoot->data;
					int i = 1;
					while (i<number){
						thisRoad = (proad) thisRoad->self->next->data;
						i++;
					}
					loop = 0;
				}else{
					puts("Invalid number. (out of range)");
				}
				//select by number
				break;
			case EXIT:
				loop = 0;
				thisRoad = NULL;
				break;
			default:
				break;
		}
	}
	return thisRoad;
}

paddress select_address(proad thisRoad){
	paddress thisAddress = NULL;
	char choice[3];
	int loop = 1;
	if (thisRoad->addressList->count == 1){
		puts("Only address on road was selected");
		thisAddress = (paddress) thisRoad->addressList->listRoot->data;
		return thisAddress;
	}
	if (thisRoad->addressList->count == 0){
		return NULL;
	}
	while (loop){
		memset(choice, 0, 3);
		puts("Select address (N)umber (L)ist or (0)Exit: ");
		int result = receive_until(choice, DELIM, 2);
		switch (choice[0]){
			case LIST:
				print_addresses(thisRoad);
				break;
			case NUMBER:
				printf("1-@d:\n",thisRoad->addressList->count);
				int number = get_positive_int();
				if ( number == 0 ){
					puts("Invalid number. (0)");
					return NULL;
				}
				if (thisRoad->addressList->count >= number){
					thisAddress = (paddress) thisRoad->addressList->listRoot->data;
					int i = 1;
					while (i<number){
						thisAddress = (paddress) thisAddress->self->next->data;
						i++;
					}
					return thisAddress;
				}else{
					puts("Invalid number. (out of range)");
					return NULL;
				}
				//select by number
				break;
			case EXIT:
				return NULL;
			default:
				break;
		}
	}
	return thisAddress;
}

pintersection select_intersection(proad thisRoad){
	char choice[3];
	int loop = 1;
	pintersection thisIntersection = NULL;
	if ( thisRoad->intersectionList->count == 0 ){
		puts("This road has no intersections to choose.");
		return NULL;
	}
	while (loop){
		memset (choice, 0, 3);
		puts("Select intersection by (N)umber, (L)ist, or set to N(O)TDEFINED.");
		printf("choice:\n");
		int result = receive_until(choice, DELIM, 2);
		switch (choice[0]){
			case LIST:
				print_intersections(thisRoad);
				break;
			case NUMBER:
				printf("1-@d:\n",thisRoad->intersectionList->count);
				int number = get_positive_int();
				if ( number ==0 ){
					puts("Invalid number.");
					return NULL;
				}
				if (thisRoad->intersectionList->count >= number){
					thisIntersection = (pintersection) thisRoad->intersectionList->listRoot->data;
					int i = 1;
					while (i<number){
						thisIntersection = (pintersection)thisIntersection->self->next->data;
						i++;
					}
					loop = 0;
				}else{
					puts("Invalid number.");
					return NULL;
				}
				//select by number
				break;
			case NOTDEFINED:
				loop = 0;
				thisIntersection = NULL;
				break;
			default:
				break;
		}
	}
	return thisIntersection;
}

void add_new_address(pmap map){
	paddress thisAddress = NULL;
	int inumber = 0;
	char resident[32];
	proad thisRoad = NULL;
	pintersection prevIntersection = NULL;
	double ddistance_to_next = 0.0;
	pintersection nextIntersection = NULL;
	double ddistance_to_prev = 0.0;
	printf("Street Number: \n");
	inumber = get_positive_int();
	if (inumber == 0){
		puts("Invalid number.");
		return;
	}
	printf("Resident: \n");
	get_char32(resident);
	if (strlen(resident) == 0) {
		puts("Invalid resident.");
		return;
	}
	thisRoad = select_road(map);
	//check thisRoad for NULL
	if (thisRoad == NULL){
		puts("Invalid road.");
		return;
	}
	if (thisRoad->addressList->count >= 50){
		puts("Invalid road.(Limit)");
		return;
	}
	prevIntersection = select_intersection(thisRoad);
	if (prevIntersection != NULL){
		puts("Distance to intersection: ");
		ddistance_to_prev = get_positive_float();
		if (ddistance_to_prev == 0.0){
			puts("Invalid distance");
			return;
		}
	}
	nextIntersection = select_intersection(thisRoad);
	if(nextIntersection != NULL){
		puts("Distance to intersection: ");
		ddistance_to_next = get_positive_float();
		if (ddistance_to_next == 0.0){
			puts("Invalid distance");
			return;
		}
	}
	thisAddress = add_address ( inumber, resident, thisRoad, prevIntersection,
 						 		ddistance_to_prev, nextIntersection, ddistance_to_next );
	if (thisAddress == NULL) {
		puts("Address not Added");
	}
	return;
}
void add_new_intersection(pmap thisMap){
	proad thisRoad = select_road(thisMap);
	proad otherRoad = select_road(thisMap);
	double distance_to_prev = 0;
	double distance_to_next = 0;
	double distance_to_prev2 = 0;
	double distance_to_next2 = 0;
	if ( (thisRoad == NULL) || (otherRoad == NULL) || (thisRoad == otherRoad) ) {
		puts("Invalid intersection.");
		return;
	}
	if ( (thisRoad->intersectionList->count >= 50) || (otherRoad->intersectionList->count >= 50) ) {
		puts("Invalid intersection. (Limit)");
		return;
	}
	puts("Prev intersection on road 1.");
	pintersection prevIntersection = select_intersection(thisRoad);
	if (prevIntersection != NULL){
		puts("Distance to prev");
		distance_to_prev = get_positive_float();
		if (prevIntersection->self->next != NULL){
			puts("Distance to next");
			distance_to_next = get_positive_float();
		}
	//if no prev, we are inserting at the beginging of the list
	}else{
		if (thisRoad->intersectionList->listRoot != NULL){
			puts("Distance to next");
			distance_to_next = get_positive_float();
		}
	} 

	pintersection thisIntersection = add_intersection ( thisRoad, otherRoad, prevIntersection, distance_to_prev, distance_to_next );
	//add corresponding intersection on other road (makes routing make sense)
	if (thisIntersection == NULL){
		puts("Intersection not added.");
		return;	
	}
	puts("Prev intersection on road 2.");
	pintersection prevIntersection2 = select_intersection(otherRoad);
	if (prevIntersection2 != NULL){
		puts("Distance to prev");
		distance_to_prev2 = get_positive_float();
		if (prevIntersection2->self->next != NULL){
			puts("Distance to next");
			distance_to_next2 = get_positive_float();
		}
	//if no prev, we are inserting at the beginging of the list
	}else{
		if (otherRoad->intersectionList->listRoot != NULL){
			puts("Distance to next");
			distance_to_next2 = get_positive_float();
		}
	} 

	pintersection thisIntersection2 = add_intersection ( otherRoad, thisRoad, prevIntersection2, distance_to_prev2, distance_to_next2 );
	if (thisIntersection2 == NULL){
		puts("Intersection not added.");
		delete_intersection(thisRoad, thisIntersection);
		return;	
	}
	return;
}

void show_route(pmap thisMap, psList turnList){
	puts("from address ");
	proad thisRoad = select_road(thisMap);
	if (thisRoad == NULL){return;}
	//address selection
	paddress thisAddress = select_address(thisRoad);
	if (thisAddress == NULL){return;}
	puts("to address ");
	proad nextRoad = select_road(thisMap);
	if (nextRoad == NULL){return;}
	//address selection
	paddress nextAddress = select_address(nextRoad);
	if (nextAddress == NULL){return;}
	if ( thisRoad == nextRoad){
		puts("Address is on the same road.");
		return;
	}
	psList thisList = get_route(thisMap, turnList, thisRoad, nextRoad);
	if (thisList == NULL){
		puts("No valid route.\nCan't get there from here");
		puts("#############################");

		return;
	}
	if (thisList->listRoot->count < 1){
		puts("**bad route");
		return;
	}
	prouteList thisRouteList =   (prouteList)(  (unsigned int)thisList->listRoot->data + (unsigned int) (thisList->listRoot->count-1) * sizeof(routeList)  );
	prouteList nextRouteList = thisRouteList->parent;
	printf("Starting on @s.\n",thisRouteList->thisRoad->name);
	while (nextRouteList != NULL){
		printf("head towards @s then turn on to @s\n",nextRouteList->thisRoad->name,nextRouteList->thisRoad->name);
		thisRouteList = nextRouteList;
		nextRouteList = nextRouteList->parent;
	}
	puts("You have arrived at your destination.");
	puts("#############################");

	return;
}

void prompt_loop(pmap thisMap, psList turnList){
	char choice[3];
	int loop = 1;
	while(loop){
		memset (choice, 0, 3);
		printf("choice:\n");
		int result = receive_until(choice, DELIM, 2);
		switch (choice[0]){
			case NAME_MAP:
				name_map(thisMap);
				break;
			case ADDROAD:
				add_new_road(thisMap);
				break;
			case ADDADDRESS:
				add_new_address(thisMap);
				break;
			case ADDINTERSECTION:
				add_new_intersection(thisMap);
				break;

			case FINDROUTE:
				show_route(thisMap, turnList);
				break;
			case PRINTMAP:
				print_map_info(thisMap);
				break;
			case EXIT:
				loop = 0;
				puts("Exiting.");
				break;
			default:
				puts("Invalid choice.");
				break;
		}
	}
}