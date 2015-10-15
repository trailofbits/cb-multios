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


#ifndef PAGESIZE
#define PAGESIZE 4096
#endif

#ifndef map_h
#define map_h



#include "llist.h"

typedef struct intersection_s {
	char FLAG[32];
	pdListNode self;
	struct road_s *other_road;
	struct intersection_s *prevIntersection;
	double distance_to_prev;
	struct intersection_s *nextIntersection;
	double distance_to_next;
} intersection, *pintersection;

typedef struct road_s {
	char FLAG[16];
	pdListNode self;
	char name[32];
	pdList addressList;
	pdList intersectionList; 
	double length;
}road, *proad;

typedef struct map_s {
	char name[32];
	pdList roadList;
}map, *pmap;


typedef struct address_s {
	char FLAG[8];
	pdListNode self;
	int number;
	char resident[32];
	proad thisRoad;
	pintersection prevIntersection;
	double distance_to_prev;
	pintersection nextIntersection;
	double distance_to_next;
}address, *paddress;

typedef struct routeList_s {
	proad thisRoad;//pointer to the newly discovered unique road
	struct routeList_s *parent;//parent is the road that was being explored when this is pushed on the list.
	char filler[120];//data[4088],  501 fits 8(503+8)=4088..9 to crash,247 fits 16(247+8)=4080..18 to crash ,119 fits 32(119+8)=4064..121 to crash 
} routeList, *prouteList;

pmap init_map(char mapName[32]);
proad add_road(pmap thisMap, char roadName[32], double roadLength);
void print_roads(pmap thisMap);
paddress add_address ( int number, char resident[32], proad thisRoad, pintersection prevIntersection,
 						double distance_to_prev, pintersection nextIntersection, double distance_to_next );
void print_addresses(proad thisRoad);
pintersection add_intersection ( proad thisRoad, proad other_road, pintersection prevIntersection, double distance_to_prev, double distance_to_next );
void print_intersections(proad thisRoad);
pintersection delete_intersection(proad thisRoad, pintersection deletedIntersection);
//new
psList init_turnList();
psList get_route(pmap thisMap, psList turnList, proad targetRoad, proad startRoad);


#endif 