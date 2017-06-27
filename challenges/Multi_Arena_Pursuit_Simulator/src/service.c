/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "cgc_service.h"
#include "libcgc.h"
#include "cgc_comms.h"
#include "cgc_cbstring.h"
#include "cgc_cbstdio.h"
#include "cgc_map.h"

unsigned int cgc_flag_idx=0;
unsigned char random_buffer[1024];

/**
 * Get a random number between min and max
 * @param  min Minimum of random number
 * @param  max Maximum of random number
 * @return     the random number 
 */
int cgc_getRandomNumber(int min, int max) {
	int random_int;
	unsigned char random_char;
	int diff;
	const char *flag = (const char*) FLAG_PAGE;

	diff = max - min + 1;
	random_char = flag[cgc_flag_idx++];
	if(cgc_flag_idx == 200)
		cgc_flag_idx = 0;

	random_int = random_char % diff;
	random_int = random_int + min;

	return random_int;

}

/**
 * Initialize buffer with random data
 */
void cgc_initRandomBuffer() {

	if(cgc_random(random_buffer, 1024, NULL))
		cgc__terminate(99);

}

/**
 * Place criminal at starting position in the harbor
 * @param location Position of criminal
 */
void cgc_initHarborChase(Position* location) {
	char x=0, y=0;

	x = cgc_getRandomNumber(-9, 9);

	switch(x) {
		case -9:
			y = cgc_getRandomNumber(-9, -8);
			break;
		case -8: 
			x = -9;
			y = cgc_getRandomNumber(-9, -8);
			break;
		case -7:
			y = cgc_getRandomNumber(-7, -5);
			break;
		case -6:
			y = cgc_getRandomNumber(-10, -5);
			break;
		case -5:
			y = cgc_getRandomNumber(-10, -3);
			break;
		case -4:
			y = cgc_getRandomNumber(-8, -3);
			break;
		case -3:
			y = cgc_getRandomNumber(-10, -2);
			break;
		case -2:
			y = cgc_getRandomNumber(-10, 0);
			break;
		case -1:
			y = cgc_getRandomNumber(-9, 0);
 			if(y == -1)
 				y = -2;
 			if(y == 0)
 				y = -2;
			break;
		case 0:
			y = cgc_getRandomNumber(-9, 0);
 			if(y < 0 && y > -2)
 				y = -2;
 			if(y >= 0 && y < 2)
 				y = -2;
 			break;
		case 1:
			y = cgc_getRandomNumber(-9, 0);
 			if(y == 0)
 				y = -3;
 			if(y == 1)
 				y = -3;
			break;
		case 2:
			y = cgc_getRandomNumber(-9, 4);
			break;
		case 3:
			y = cgc_getRandomNumber(-8, 4);
			break;
		case 4:
			y = cgc_getRandomNumber(-7, 5);
			break;
		case 5:
			y = cgc_getRandomNumber(-5, 6);
			break;
		case 6:
			y = cgc_getRandomNumber(-4, 6);
			break;
		case 7:
			y = cgc_getRandomNumber(-5, 6);
			break;
		case 8:
			y = cgc_getRandomNumber(0, 1);
			break;	
		case 9:
			y = cgc_getRandomNumber(0, 1);
			break;		
		default:
			cgc__terminate(SWITCH_ERROR);
	}

	location->x = x;
	location->y = y;

}

/**
 * Place criminal at starting location in city
 * @param location Position of criminal
 */
void cgc_initCarChase(Position* location) {
	char x=0,y=0;

	x = cgc_getRandomNumber(-2, 7);

 	switch(x) {
 		case -2: 
 			y = -1;
 			break;
 		case -1:
 			y = cgc_getRandomNumber(-3,3);
 			if(y < 0 && y > -2)
 				y = -2;
 			if(y > 0 && y < 2)
 				y = 2;
			break;
		case 0:
 			y = cgc_getRandomNumber(-5,5);
 			if(y < 0 && y > -2)
 				y = -2;
 			if(y >= 0 && y < 2)
 				y = 2;
			break;			 
		case 1:
 			y = cgc_getRandomNumber(-5,7);
 			if(y < 0 && y > -2)
 				y = -2;
 			if(y > 0 && y < 2)
 				y = 2;
			break;
		case 2:
 			y = cgc_getRandomNumber(-4,7);
			break;
		case 3:
 			y = cgc_getRandomNumber(-4,5);
			break;
		case 4:
 			y = cgc_getRandomNumber(-3,3);
			break;
		case 5:
 			y = cgc_getRandomNumber(-3,1);
			break;
		case 6:
 			y = cgc_getRandomNumber(-2,-1);
			break;
		case 7:
 			y = cgc_getRandomNumber(-2,-1);
			break;
		default:
			cgc__terminate(SWITCH_ERROR);			
 	}

 	location->x = x;
 	location->y = y;

}

/**
 * Determine if criminal has avoided capture
 * @param  criminal Position of criminal
 * @param  map      Map of territory
 * @return          TRUE if criminal has escaped, FALSE if criminal has not
 */
unsigned int cgc_getsAway(Position criminal, Map* map) {

	if(cgc_getCoordinate(map, criminal.x, criminal.y) == -1)
		return TRUE;

	return FALSE;
}

/**
 * Determine if criminal has been caught
 * @param  criminal Position of criminal
 * @param  map      Map of territory
 * @return          TRUE if caught, FALSE if not
 */
unsigned int cgc_isCaught(Position criminal, Map* map) {

	if(cgc_getCoordinate(map, criminal.x, criminal.y) == 0)
		return TRUE;
	
	return FALSE;
}

/**
 * Move criminal in boat to most beneficial position
 * @param criminal Position of criminal
 * @param map      Map of harbor
 */
void cgc_moveCriminalInBoat(Position* criminal, Map* map) {
	int value=0;
	int bestX;
	int bestY;
	unsigned int tmp;

	tmp = cgc_getCoordinate(map, criminal->x, criminal->y);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x;
		bestY = criminal->y;
	}

	tmp = cgc_getCoordinate(map, criminal->x+1, criminal->y);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x+1;
		bestY = criminal->y;
	}

	tmp = cgc_getCoordinate(map, criminal->x, criminal->y+1);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x;
		bestY = criminal->y+1;
	}

	tmp = cgc_getCoordinate(map, criminal->x-1, criminal->y);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x-1;
		bestY = criminal->y;
	}

	tmp = cgc_getCoordinate(map, criminal->x, criminal->y-1);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x;
		bestY = criminal->y-1;
	}

	tmp = cgc_getCoordinate(map, criminal->x+1, criminal->y+1);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x+1;
		bestY = criminal->y+1;
	}

	tmp = cgc_getCoordinate(map, criminal->x-1, criminal->y-1);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x-1;
		bestY = criminal->y-1;
	}

	criminal->x = bestX;
	criminal->y = bestY;

#ifdef DEBUG
	char send_buffer[1024];
	bzero(send_buffer, 1024);
	sprintf(send_buffer, "Criminal moves. Criminal at (!I, !I)\n", criminal->x, criminal->y);
	if(transmit_all(STDOUT, send_buffer, cgc_strlen(send_buffer)))
		cgc__terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move criminal in car to most beneficial position
 * @param criminal Position of criminal
 * @param map      Map of city
 */
void cgc_moveCriminalInCar(Position* criminal, Map* map) {
	int value=0;
	int bestX;
	int bestY;
	unsigned int tmp;
	
	tmp = cgc_getCoordinate(map, criminal->x, criminal->y);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x;
		bestY = criminal->y;
	}

	tmp = cgc_getCoordinate(map, criminal->x+1, criminal->y);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x+1;
		bestY = criminal->y;
	}

	tmp = cgc_getCoordinate(map, criminal->x, criminal->y+1);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x;
		bestY = criminal->y+1;
	}

	tmp = cgc_getCoordinate(map, criminal->x-1, criminal->y);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x-1;
		bestY = criminal->y;
	}

	tmp = cgc_getCoordinate(map, criminal->x, criminal->y-1);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x;
		bestY = criminal->y-1;
	}

	criminal->x = bestX;
	criminal->y = bestY;

#ifdef DEBUG
	char send_buffer[1024];
	bzero(send_buffer, 1024);
	sprintf(send_buffer, "Criminal moves. Criminal at (!I, !I)\n", criminal->x, criminal->y);
	if(transmit_all(STDOUT, send_buffer, cgc_strlen(send_buffer)))
		cgc__terminate(TRANSMIT_ERROR);
#endif

}

/**
 * Move left in boat
 * @param criminal Position of criminal
 */
void cgc_moveLeftInBoat(Position* criminal) {
	int newX, newY;
	newX = criminal->y;
	newY = criminal->y - criminal->x;
	criminal->x = newX - 2;
	criminal->y = newY - 2;

#ifdef DEBUG
	char send_buffer[1024];
	bzero(send_buffer, 1024);
	sprintf(send_buffer, "Move Left. Criminal at (!I, !I)\n", criminal->x, criminal->y);
	if(transmit_all(STDOUT, send_buffer, cgc_strlen(send_buffer)))
		cgc__terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move forward in boat
 * @param criminal Position of criminal
 */
void cgc_moveForwardInBoat(Position* criminal) {
	criminal->x = criminal->x - 2;
	criminal->y = criminal->y - 2;

#ifdef DEBUG
	char send_buffer[1024];
	bzero(send_buffer, 1024);
	sprintf(send_buffer, "Move Forward. Criminal at (!I, !I)\n", criminal->x, criminal->y);
	if(transmit_all(STDOUT, send_buffer, cgc_strlen(send_buffer)))
		cgc__terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move right in boat
 * @param criminal Position of criminal
 */
void cgc_moveRightInBoat(Position* criminal) {
	int newX, newY;
	newX = criminal->x - criminal->y;
	newY = criminal->x;
	criminal->x = newX - 2;
	criminal->y = newY - 2;


#ifdef DEBUG
	char send_buffer[1024];
	bzero(send_buffer, 1024);
	sprintf(send_buffer, "Move Right. Criminal at (!I, !I)\n", criminal->x, criminal->y);
	if(transmit_all(STDOUT, send_buffer, cgc_strlen(send_buffer)))
		cgc__terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move forward in car
 * @param criminal Position of criminal
 */
void cgc_moveForwardInCar(Position* criminal) {
	criminal->y = criminal->y - 2;

#ifdef DEBUG
	char send_buffer[1024];
	bzero(send_buffer, 1024);
	sprintf(send_buffer, "Move Forward. Criminal at (!I, !I)\n", criminal->x, criminal->y);
	if(transmit_all(STDOUT, send_buffer, cgc_strlen(send_buffer)))
		cgc__terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move right in car
 * @param criminal Position of criminal
 */
void cgc_moveRightInCar(Position* criminal) {
	int newX, newY;
	newX = criminal->y * -1;
	newY = criminal->x - 2;
	criminal->x = newX;
	criminal->y = newY;

#ifdef DEBUG
	char send_buffer[1024];
	bzero(send_buffer, 1024);
	sprintf(send_buffer, "Move Right. Criminal at (!I, !I)\n", criminal->x, criminal->y);
	if(transmit_all(STDOUT, send_buffer, cgc_strlen(send_buffer)))
		cgc__terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Get the next move from user and make move
 * @param criminal Current position of criminal in harbor
 */
void cgc_getMoveInBoat(Position* criminal) {
	char buffer[2];
	cgc_size_t bytes;

	if(cgc_read_until_delim_or_n(STDIN, buffer, '#', sizeof(buffer), &bytes))
		cgc__terminate(READ_ERROR);

	if(buffer[0] == 'R')
		cgc_moveRightInBoat(criminal);
	else if (buffer[0] == 'F')
		cgc_moveForwardInBoat(criminal);
	else if (buffer[0] == 'L')
		cgc_moveLeftInBoat(criminal);

}

/**
 * Get the next move from user and make move
 * @param criminal Current position of criminal in city
 */
void cgc_getMoveInCar(Position* criminal) {
	char buffer[2];
	cgc_size_t bytes;

	if(cgc_read_until_delim_or_n(STDIN, buffer, '#', sizeof(buffer), &bytes))
		cgc__terminate(READ_ERROR);

	if(buffer[0] == 'R')
		cgc_moveRightInCar(criminal);
	else if (buffer[0] == 'F')
		cgc_moveForwardInCar(criminal);

}

/**
 * Initialize coordinate values for harbor map
 * @param map_ptr pointer to Map pointer for storing new map
 */
void cgc_initHarborMap(Map **map_ptr) {
	int V;
	int newCoordinate=0;

	V = 0;
	cgc_setCoordinate(map_ptr, -1, 0, V);
	cgc_setCoordinate(map_ptr, 0, 0, V);
	cgc_setCoordinate(map_ptr, 1, 0, V);
	cgc_setCoordinate(map_ptr, 0, -1, V);
	cgc_setCoordinate(map_ptr, 0, 1, V);
	cgc_setCoordinate(map_ptr, 1, 1, V);
	cgc_setCoordinate(map_ptr, -1, -1, V);


	V = 1;
	cgc_setCoordinate(map_ptr, -1, 1, V);
	cgc_setCoordinate(map_ptr, -1, 2, V);
	cgc_setCoordinate(map_ptr, 0, 2, V);
	cgc_setCoordinate(map_ptr, 0, 3, V);
	cgc_setCoordinate(map_ptr, 1, 2, V);
	cgc_setCoordinate(map_ptr, 1, 3, V);
	cgc_setCoordinate(map_ptr, 1, -1, V);
	cgc_setCoordinate(map_ptr, 2, -1, V);
	cgc_setCoordinate(map_ptr, 2, 0, V);
	cgc_setCoordinate(map_ptr, 2, 1, V);
	cgc_setCoordinate(map_ptr, 2, 2, V);
	cgc_setCoordinate(map_ptr, 2, 3, V);
	cgc_setCoordinate(map_ptr, 3, 0, V);
	cgc_setCoordinate(map_ptr, 3, 1, V);
	cgc_setCoordinate(map_ptr, 3, 2, V);
	cgc_setCoordinate(map_ptr, 3, 3, V);	

	V = 2;
	cgc_setCoordinate(map_ptr, 2, 4, V);
	cgc_setCoordinate(map_ptr, 2, -2, V);
	cgc_setCoordinate(map_ptr, 3, 4, V);
	cgc_setCoordinate(map_ptr, 3, -1, V);
	cgc_setCoordinate(map_ptr, 4, 0, V);
	cgc_setCoordinate(map_ptr, 4, 1, V);
	cgc_setCoordinate(map_ptr, 4, 2, V);
	cgc_setCoordinate(map_ptr, 4, 3, V);
	cgc_setCoordinate(map_ptr, 4, 4, V);

	V=3;
	cgc_setCoordinate(map_ptr, 4, 5, V);
	cgc_setCoordinate(map_ptr, 2, -3, V);
	cgc_setCoordinate(map_ptr, 3, -2, V);
	cgc_setCoordinate(map_ptr, 4, -1, V);
	cgc_setCoordinate(map_ptr, 5, 0, V);
	cgc_setCoordinate(map_ptr, 5, 1, V);
	cgc_setCoordinate(map_ptr, 5, 2, V);
	cgc_setCoordinate(map_ptr, 5, 3, V);
	cgc_setCoordinate(map_ptr, 5, 4, V);
	cgc_setCoordinate(map_ptr, 5, 5, V);


	V=4;
	cgc_setCoordinate(map_ptr, 1, -4, V);
	cgc_setCoordinate(map_ptr, 2, -4, V);
	cgc_setCoordinate(map_ptr, 3, -3, V);
	cgc_setCoordinate(map_ptr, 4, -2, V);
	cgc_setCoordinate(map_ptr, 5, -1, V);
	cgc_setCoordinate(map_ptr, 6, 0, V);
	cgc_setCoordinate(map_ptr, 6, 1, V);
	cgc_setCoordinate(map_ptr, 6, 2, V);
	cgc_setCoordinate(map_ptr, 6, 3, V);
	cgc_setCoordinate(map_ptr, 6, 4, V);
	cgc_setCoordinate(map_ptr, 6, 5, V);
	cgc_setCoordinate(map_ptr, 6, 6, V);
	cgc_setCoordinate(map_ptr, 5, 6, V);



	V=5;
	cgc_setCoordinate(map_ptr, 0, -5, V);
	cgc_setCoordinate(map_ptr, 1, -5, V);
	cgc_setCoordinate(map_ptr, 2, -5, V);
	cgc_setCoordinate(map_ptr, 3, -4, V);
	cgc_setCoordinate(map_ptr, 4, -3, V);
	cgc_setCoordinate(map_ptr, 5, -2, V);
	cgc_setCoordinate(map_ptr, 6, -1, V);
	cgc_setCoordinate(map_ptr, 7, 0, V);
	cgc_setCoordinate(map_ptr, 7, 1, V);
	cgc_setCoordinate(map_ptr, 7, 2, V);
	cgc_setCoordinate(map_ptr, 7, 3, V);
	cgc_setCoordinate(map_ptr, 7, 4, V);
	cgc_setCoordinate(map_ptr, 7, 5, V);
	cgc_setCoordinate(map_ptr, 7, 6, V);
	cgc_setCoordinate(map_ptr, 7, 7, V);
	cgc_setCoordinate(map_ptr, 7, 8, V);
	cgc_setCoordinate(map_ptr, 5, 7, V);
	cgc_setCoordinate(map_ptr, 6, 7, V);

	V=6;
	cgc_setCoordinate(map_ptr, -2, -6, V);
	cgc_setCoordinate(map_ptr, -1, -6, V);
	cgc_setCoordinate(map_ptr, 0, -6, V);
	cgc_setCoordinate(map_ptr, 1, -6, V);
	cgc_setCoordinate(map_ptr, 2, -6, V);
	cgc_setCoordinate(map_ptr, 3, -5, V);
	cgc_setCoordinate(map_ptr, 4, -4, V);
	cgc_setCoordinate(map_ptr, 5, -3, V);
	cgc_setCoordinate(map_ptr, 6, -2, V);
	cgc_setCoordinate(map_ptr, 7, -1, V);
	cgc_setCoordinate(map_ptr, 8, 0, V);
	cgc_setCoordinate(map_ptr, 8, 1, V);
	cgc_setCoordinate(map_ptr, 8, 2, V);
	cgc_setCoordinate(map_ptr, 8, 3, V);
	cgc_setCoordinate(map_ptr, 8, 4, V);
	cgc_setCoordinate(map_ptr, 8, 5, V);
	cgc_setCoordinate(map_ptr, 8, 6, V);
	cgc_setCoordinate(map_ptr, 8, 7, V);
	cgc_setCoordinate(map_ptr, 8, 8, V);
	cgc_setCoordinate(map_ptr, 8, 9, V);
	cgc_setCoordinate(map_ptr, 9, 3, V);


	V=7;
	cgc_setCoordinate(map_ptr, -3, -6, V);
	cgc_setCoordinate(map_ptr, -3, -7, V);
	cgc_setCoordinate(map_ptr, -2, -7, V);
	cgc_setCoordinate(map_ptr, -1, -7, V);
	cgc_setCoordinate(map_ptr, 0, -7, V);
	cgc_setCoordinate(map_ptr, 1, -7, V);
	cgc_setCoordinate(map_ptr, 2, -7, V);
	cgc_setCoordinate(map_ptr, 3, -6, V);
	cgc_setCoordinate(map_ptr, 4, -5, V);
	cgc_setCoordinate(map_ptr, 5, -4, V);
	cgc_setCoordinate(map_ptr, 6, -3, V);
	cgc_setCoordinate(map_ptr, 7, -2, V);
	cgc_setCoordinate(map_ptr, 9, 0, V);
	cgc_setCoordinate(map_ptr, 8, -1, V);
	cgc_setCoordinate(map_ptr, 10, 3, V);
	cgc_setCoordinate(map_ptr, 9, 2, V);
	cgc_setCoordinate(map_ptr, 6, 8, V);
	cgc_setCoordinate(map_ptr, 7, 9, V);
	cgc_setCoordinate(map_ptr, 9, 5, V);
	cgc_setCoordinate(map_ptr, 9, 6, V);
	cgc_setCoordinate(map_ptr, 9, 7, V);
	cgc_setCoordinate(map_ptr, 9, 8, V);
	cgc_setCoordinate(map_ptr, 9, 9, V);
	

	V=8;
	cgc_setCoordinate(map_ptr, -4, -6, V);
	cgc_setCoordinate(map_ptr, -4, -7, V);
	cgc_setCoordinate(map_ptr, -4, -8, V);
	cgc_setCoordinate(map_ptr, -3, -8, V);
	cgc_setCoordinate(map_ptr, -2, -8, V);
	cgc_setCoordinate(map_ptr, -1, -8, V);
	cgc_setCoordinate(map_ptr, 0, -8, V);
	cgc_setCoordinate(map_ptr, 1, -8, V);
	cgc_setCoordinate(map_ptr, 2, -8, V);
	cgc_setCoordinate(map_ptr, 3, -7, V);
	cgc_setCoordinate(map_ptr, 4, -6, V);
	cgc_setCoordinate(map_ptr, 5, -5, V);
	cgc_setCoordinate(map_ptr, 6, -4, V);
	cgc_setCoordinate(map_ptr, 7, -3, V);
	cgc_setCoordinate(map_ptr, 8, -2, V);
	cgc_setCoordinate(map_ptr, 9, 1, V);
	cgc_setCoordinate(map_ptr, 9, -1, V);
	cgc_setCoordinate(map_ptr, 9, 4, V);
	cgc_setCoordinate(map_ptr, 10, -1, V);
	cgc_setCoordinate(map_ptr, 10, 0, V);
	cgc_setCoordinate(map_ptr, 10, 2, V);
	cgc_setCoordinate(map_ptr, 10, 5, V);
	cgc_setCoordinate(map_ptr, 10, 7, V);
	cgc_setCoordinate(map_ptr, 11, 5, V);
	cgc_setCoordinate(map_ptr, 3, -9, V);
	

	V=9;
	cgc_setCoordinate(map_ptr, -5, -4, V);
	cgc_setCoordinate(map_ptr, -7, -5, V);
	cgc_setCoordinate(map_ptr, -5, -5, V);
	cgc_setCoordinate(map_ptr, -4, -5, V);
	cgc_setCoordinate(map_ptr, -5, -6, V);
	cgc_setCoordinate(map_ptr, -5, -7, V);
	cgc_setCoordinate(map_ptr, -5, -8, V);
	cgc_setCoordinate(map_ptr, -5, -9, V);
	cgc_setCoordinate(map_ptr, -4, -9, V);
	cgc_setCoordinate(map_ptr, -3, -9, V);
	cgc_setCoordinate(map_ptr, -2, -9, V);
	cgc_setCoordinate(map_ptr, -1, -9, V);
	cgc_setCoordinate(map_ptr, 0, -9, V);
	cgc_setCoordinate(map_ptr, 1, -9, V);
	cgc_setCoordinate(map_ptr, 2, -9, V);
	cgc_setCoordinate(map_ptr, 3, -8, V);
	cgc_setCoordinate(map_ptr, 4, -7, V);
	cgc_setCoordinate(map_ptr, 7, -4, V);
	cgc_setCoordinate(map_ptr, -1, -5, V);
	cgc_setCoordinate(map_ptr, 9, -2, V);
	cgc_setCoordinate(map_ptr, 9, -3, V);
	cgc_setCoordinate(map_ptr, 10, 1, V);
	cgc_setCoordinate(map_ptr, 10, 4, V);
	cgc_setCoordinate(map_ptr, 10, 6, V);
	cgc_setCoordinate(map_ptr, 10, 9, V);
	cgc_setCoordinate(map_ptr, -4, -2, V);
	cgc_setCoordinate(map_ptr, 4, -8, V);
	cgc_setCoordinate(map_ptr, 5, -7, V);
	cgc_setCoordinate(map_ptr, -4, -11, V);
	cgc_setCoordinate(map_ptr, 11, 1, V);
	cgc_setCoordinate(map_ptr, 11, 2, V);
	cgc_setCoordinate(map_ptr, 11, 4, V);	
	cgc_setCoordinate(map_ptr, 11, 6, V);
	cgc_setCoordinate(map_ptr, 11, 7, V);		
	cgc_setCoordinate(map_ptr, 12, 2, V);
	cgc_setCoordinate(map_ptr, 6, -6, V);

	V=10;
	cgc_setCoordinate(map_ptr, -5, -3, V);
	cgc_setCoordinate(map_ptr, -3, -5, V);
	cgc_setCoordinate(map_ptr, -2, -5, V);	
	cgc_setCoordinate(map_ptr, -7, -6, V);
	cgc_setCoordinate(map_ptr, -6, -6, V);
	cgc_setCoordinate(map_ptr, -6, -7, V);
	cgc_setCoordinate(map_ptr, -6, -8, V);
	cgc_setCoordinate(map_ptr, -6, -9, V);
	cgc_setCoordinate(map_ptr, -6, -10, V);
	cgc_setCoordinate(map_ptr, -5, -10, V);
	cgc_setCoordinate(map_ptr, -4, -10, V);
	cgc_setCoordinate(map_ptr, -3, -10, V);
	cgc_setCoordinate(map_ptr, -2, -10, V);
	cgc_setCoordinate(map_ptr, 0, -10, V);
	cgc_setCoordinate(map_ptr, 7, -5, V);
	cgc_setCoordinate(map_ptr, 5, -6, V);
	cgc_setCoordinate(map_ptr, 6, -5, V);
	cgc_setCoordinate(map_ptr, 8, -3, V);
	cgc_setCoordinate(map_ptr, -3, -12, V);
	cgc_setCoordinate(map_ptr, 4, -9, V);
	cgc_setCoordinate(map_ptr, -5, -12, V);
	cgc_setCoordinate(map_ptr, 12, 1, V);



	V=11;
	cgc_setCoordinate(map_ptr, -4, -3, V);
	cgc_setCoordinate(map_ptr, -4, -4, V);
	cgc_setCoordinate(map_ptr, -3, -4, V);
	cgc_setCoordinate(map_ptr, -2, -4, V);
	cgc_setCoordinate(map_ptr, -1, -4, V);
	cgc_setCoordinate(map_ptr, 0, -4, V);
	cgc_setCoordinate(map_ptr, -8, -7, V);
	cgc_setCoordinate(map_ptr, -7, -7, V);
	cgc_setCoordinate(map_ptr, -7, -8, V);
	cgc_setCoordinate(map_ptr, -7, -9, V);
	cgc_setCoordinate(map_ptr, 7, -6, V);
	cgc_setCoordinate(map_ptr, -1, -10, V);
	cgc_setCoordinate(map_ptr, -2, -11, V);
	cgc_setCoordinate(map_ptr, -2, -12, V);
	cgc_setCoordinate(map_ptr, 8, -4, V);
	cgc_setCoordinate(map_ptr, -5, -11, V);
	cgc_setCoordinate(map_ptr, -6, -11, V);
	cgc_setCoordinate(map_ptr, -6, -12, V); 
	cgc_setCoordinate(map_ptr, -7, -11, V);
	cgc_setCoordinate(map_ptr, 10, 10, V);
	cgc_setCoordinate(map_ptr, 3, -10, V);


	V=12;
	cgc_setCoordinate(map_ptr, -3, -2, V);
	cgc_setCoordinate(map_ptr, -3, -3, V);
	cgc_setCoordinate(map_ptr, -2, -3, V);
	cgc_setCoordinate(map_ptr, -1, -3, V);
	cgc_setCoordinate(map_ptr, 0, -3, V);
	cgc_setCoordinate(map_ptr, -9, -8, V);
	cgc_setCoordinate(map_ptr, -8, -8, V);
	cgc_setCoordinate(map_ptr, -8, -9, V);
	cgc_setCoordinate(map_ptr, -8, -10, V);
	cgc_setCoordinate(map_ptr, 7, -7, V);  
	cgc_setCoordinate(map_ptr, -1, -11, V);
	cgc_setCoordinate(map_ptr, -3, -11, V);
	cgc_setCoordinate(map_ptr, -4, -12, V);
	cgc_setCoordinate(map_ptr, 2, -10, V);
	cgc_setCoordinate(map_ptr, 9, 10, V);



	V=13;
	cgc_setCoordinate(map_ptr, -2, -1, V);
	cgc_setCoordinate(map_ptr, -2, -2, V);
	cgc_setCoordinate(map_ptr, -1, -2, V);
	cgc_setCoordinate(map_ptr, 0, -2, V);
	cgc_setCoordinate(map_ptr, 1, -2, V);
	cgc_setCoordinate(map_ptr, 1, -3, V);
	cgc_setCoordinate(map_ptr, -9, -9, V);
	cgc_setCoordinate(map_ptr, 11, 0, V);
	cgc_setCoordinate(map_ptr, -7, -12, V);
	cgc_setCoordinate(map_ptr, 9, 11, V);
	cgc_setCoordinate(map_ptr, 8, 10, V);
	cgc_setCoordinate(map_ptr, 10, 11, V);

}

/**
 * Initialize coordinate values for city map
 * @param map_ptr pointer to Map pointer for storing new map
 */
void cgc_initCityMap(Map **map_ptr) {
	int V;
	int newCoordinate=0;

	V = 0;
	for(int x=-1; x<=1; x++) {
		for(int y=-1; y<=1; y++) {
			cgc_setCoordinate(map_ptr, x, y, V);
		}
	}

	V = 1;
	for (int x = V; x <= V+2; x++) {
		for(int y=-1; y<=1; y++) {
			if(cgc_getCoordinate(*map_ptr, x, y) == -1)
				cgc_setCoordinate(map_ptr, x, y, V);
		}	
	}
	for (int x = -1; x <= 1; x++) {
		for(int y=V; y<=V+2; y++) {
			if(cgc_getCoordinate(*map_ptr, x, y) == -1)
				cgc_setCoordinate(map_ptr, x, y, V);
		}	
	}

	V = 2;
	cgc_setCoordinate(map_ptr, 0, 4, V);
	cgc_setCoordinate(map_ptr, 2, 2, V);
	cgc_setCoordinate(map_ptr, 4, 0, V);
	cgc_setCoordinate(map_ptr, 2, -2, V);

	V=3;
	cgc_setCoordinate(map_ptr, 0, 5, V);
	cgc_setCoordinate(map_ptr, 1, 4, V);
	cgc_setCoordinate(map_ptr, 2, 3, V);
	cgc_setCoordinate(map_ptr, 3, 2, V);
	cgc_setCoordinate(map_ptr, 5, 0, V);
	cgc_setCoordinate(map_ptr, 4, -1, V);
	cgc_setCoordinate(map_ptr, 3, -2, V);
	cgc_setCoordinate(map_ptr, 2, -3, V);	
	cgc_setCoordinate(map_ptr, 1, -2, V);	

	V=4;
	cgc_setCoordinate(map_ptr, 1, 5, V);
	cgc_setCoordinate(map_ptr, 2, 4, V);
	cgc_setCoordinate(map_ptr, 5, -1, V);
	cgc_setCoordinate(map_ptr, 4, -2, V);
	cgc_setCoordinate(map_ptr, 1, -3, V);	
	cgc_setCoordinate(map_ptr, 0, -2, V);

	V=5;
	cgc_setCoordinate(map_ptr, 1, 6, V);
	cgc_setCoordinate(map_ptr, 4, 1, V);
	cgc_setCoordinate(map_ptr, 6, -1, V);	
	cgc_setCoordinate(map_ptr, 1, -4, V);

	V=6;
	cgc_setCoordinate(map_ptr, 3, 3, V);
	cgc_setCoordinate(map_ptr, 4, 2, V);
	cgc_setCoordinate(map_ptr, 3, -3, V);	
	cgc_setCoordinate(map_ptr, 2, -4, V);

	V=7;
	cgc_setCoordinate(map_ptr, 2, 5, V);
	cgc_setCoordinate(map_ptr, 3, 4, V);
	cgc_setCoordinate(map_ptr, 5, -2, V);
	cgc_setCoordinate(map_ptr, 4, -3, V);
	cgc_setCoordinate(map_ptr, 0, -3, V);	
	cgc_setCoordinate(map_ptr, -1, -2, V);

	V=8;
	cgc_setCoordinate(map_ptr, 1, 7, V);
	cgc_setCoordinate(map_ptr, 2, 6, V);
	cgc_setCoordinate(map_ptr, 5, 1, V);
	cgc_setCoordinate(map_ptr, 6, -2, V);	
	cgc_setCoordinate(map_ptr, 7, -1, V);
	cgc_setCoordinate(map_ptr, 1, -5, V);
	cgc_setCoordinate(map_ptr, 0, -4, V);

	V=9;
	cgc_setCoordinate(map_ptr, 4, 3, V);
	cgc_setCoordinate(map_ptr, 3, -4, V);
	cgc_setCoordinate(map_ptr, -2, -1, V);

	V=10;
	cgc_setCoordinate(map_ptr, 3, 5, V);
	cgc_setCoordinate(map_ptr, 5, -3, V);
	cgc_setCoordinate(map_ptr, -1, -3, V);

	V=11;
	cgc_setCoordinate(map_ptr, 2, 7, V);
	cgc_setCoordinate(map_ptr, 7, -2, V);
	cgc_setCoordinate(map_ptr, 0, -5, V);
}

int main(int cgc_argc, char *cgc_argv[]) {
	Position criminal;
	Map *cityMap=NULL;
	Map *harborMap=NULL;
	unsigned int result=0;
	char flag_buf[40];
	char send_buffer[SEND_SZ];
	char x;
	cgc_size_t index=0;
	unsigned int moves=0;
	unsigned int caught=0;
	unsigned int gotAway=0;
	const char *flag = (const char*) FLAG_PAGE;

	for (unsigned int i = 0; i < 10; i++) {
		cgc_sprintf(&flag_buf[i*4], "!H", (unsigned char) *flag++);
	}

	cgc_initCityMap(&cityMap);

	for(int t=0; t<100; t++) {	
		cgc_initCarChase(&criminal);
		cgc_bzero(send_buffer, SEND_SZ);
		cgc_sprintf(send_buffer, "Criminal at (!I, !I)\n", criminal.x, criminal.y);
		if(cgc_transmit_all(STDOUT, send_buffer, cgc_strlen(send_buffer)))
			cgc__terminate(TRANSMIT_ERROR);

		do {
			//makeMoveInCar(&criminal);
			cgc_getMoveInCar(&criminal);
			moves++;

			if(cgc_isCaught(criminal, cityMap)) {

				cgc_bzero(send_buffer, SEND_SZ);
				cgc_sprintf(send_buffer, "Criminal caught in !U moves\n", moves);
				if(cgc_transmit_all(STDOUT, send_buffer, cgc_strlen(send_buffer)))
					cgc__terminate(TRANSMIT_ERROR);	
				moves = 0;
				break;

			} else {
				cgc_moveCriminalInCar(&criminal, cityMap);

				if(cgc_getsAway(criminal, cityMap)) {
					if(cgc_transmit_all(STDOUT, "Got away\n", cgc_strlen("Got away\n")))
						cgc__terminate(TRANSMIT_ERROR);
					cgc_initCarChase(&criminal);
					cgc_bzero(send_buffer, SEND_SZ);
					cgc_sprintf(send_buffer, "Criminal at (!I, !I)\n", criminal.x, criminal.y);
					if(cgc_transmit_all(STDOUT, send_buffer, cgc_strlen(send_buffer)))
						cgc__terminate(TRANSMIT_ERROR);
				}			
			}
		} while(1);

	}
	cgc_freeMap(&cityMap);
	cgc_initHarborMap(&harborMap);
	
	for(int t=0; t<100; t++) {

		cgc_initHarborChase(&criminal);
		cgc_bzero(send_buffer, SEND_SZ);
		cgc_sprintf(send_buffer, "Criminal at (!I, !I)\n", criminal.x, criminal.y);
		if(cgc_transmit_all(STDOUT, send_buffer, cgc_strlen(send_buffer)))
			cgc__terminate(TRANSMIT_ERROR);

		do {
			//makeMoveInBoat(&criminal, harborMap);
			cgc_getMoveInBoat(&criminal);
			moves++;

			if(cgc_isCaught(criminal, harborMap)) {
				caught++;
				cgc_bzero(send_buffer, SEND_SZ);
				cgc_sprintf(send_buffer, "Criminal caught in !U moves\n", moves);
				if(cgc_transmit_all(STDOUT, send_buffer, cgc_strlen(send_buffer)))
					cgc__terminate(TRANSMIT_ERROR);	
				moves = 0;
				break;

			} else {
				cgc_moveCriminalInBoat(&criminal, harborMap);

				
				if(cgc_getsAway(criminal, harborMap)) {
					gotAway++;
					if(cgc_transmit_all(STDOUT, "Got away\n", cgc_strlen("Got away\n")))
						cgc__terminate(TRANSMIT_ERROR);
					cgc_initHarborChase(&criminal);
					cgc_bzero(send_buffer, SEND_SZ);
					cgc_sprintf(send_buffer, "Criminal at (!I, !I)\n", criminal.x, criminal.y);
					if(cgc_transmit_all(STDOUT, send_buffer, cgc_strlen(send_buffer)))
						cgc__terminate(TRANSMIT_ERROR);
				}
				
			}
		} while(1);
	}
	cgc_freeMap(&harborMap);
}
