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
#include "service.h"
#include <libcgc.h>
#include "comms.h"
#include "cbstring.h"
#include "cbstdio.h"
#include "map.h"

unsigned int flag_idx=0;
unsigned char random_buffer[1024];

/**
 * Get a random number between min and max
 * @param  min Minimum of random number
 * @param  max Maximum of random number
 * @return     the random number 
 */
int getRandomNumber(int min, int max) {
	int random_int;
	unsigned char random_char;
	int diff;
	const char *flag = (const char*) FLAG_PAGE;

	diff = max - min + 1;
	random_char = flag[flag_idx++];
	if(flag_idx == 200)
		flag_idx = 0;

	random_int = random_char % diff;
	random_int = random_int + min;

	return random_int;

}

/**
 * Initialize buffer with random data
 */
void initRandomBuffer() {

	if(random(random_buffer, 1024, NULL))
		_terminate(99);

}

/**
 * Place criminal at starting position in the harbor
 * @param location Position of criminal
 */
void initHarborChase(Position* location) {
	char x=0, y=0;

	x = getRandomNumber(-9, 9);

	switch(x) {
		case -9:
			y = getRandomNumber(-9, -8);
			break;
		case -8: 
			x = -9;
			y = getRandomNumber(-9, -8);
			break;
		case -7:
			y = getRandomNumber(-7, -5);
			break;
		case -6:
			y = getRandomNumber(-10, -5);
			break;
		case -5:
			y = getRandomNumber(-10, -3);
			break;
		case -4:
			y = getRandomNumber(-8, -3);
			break;
		case -3:
			y = getRandomNumber(-10, -2);
			break;
		case -2:
			y = getRandomNumber(-10, 0);
			break;
		case -1:
			y = getRandomNumber(-9, 0);
 			if(y == -1)
 				y = -2;
 			if(y == 0)
 				y = -2;
			break;
		case 0:
			y = getRandomNumber(-9, 0);
 			if(y < 0 && y > -2)
 				y = -2;
 			if(y >= 0 && y < 2)
 				y = -2;
 			break;
		case 1:
			y = getRandomNumber(-9, 0);
 			if(y == 0)
 				y = -3;
 			if(y == 1)
 				y = -3;
			break;
		case 2:
			y = getRandomNumber(-9, 4);
			break;
		case 3:
			y = getRandomNumber(-8, 4);
			break;
		case 4:
			y = getRandomNumber(-7, 5);
			break;
		case 5:
			y = getRandomNumber(-5, 6);
			break;
		case 6:
			y = getRandomNumber(-4, 6);
			break;
		case 7:
			y = getRandomNumber(-5, 6);
			break;
		case 8:
			y = getRandomNumber(0, 1);
			break;	
		case 9:
			y = getRandomNumber(0, 1);
			break;		
		default:
			_terminate(SWITCH_ERROR);
	}

	location->x = x;
	location->y = y;

}

/**
 * Place criminal at starting location in city
 * @param location Position of criminal
 */
void initCarChase(Position* location) {
	char x=0,y=0;

	x = getRandomNumber(-2, 7);

 	switch(x) {
 		case -2: 
 			y = -1;
 			break;
 		case -1:
 			y = getRandomNumber(-3,3);
 			if(y < 0 && y > -2)
 				y = -2;
 			if(y > 0 && y < 2)
 				y = 2;
			break;
		case 0:
 			y = getRandomNumber(-5,5);
 			if(y < 0 && y > -2)
 				y = -2;
 			if(y >= 0 && y < 2)
 				y = 2;
			break;			 
		case 1:
 			y = getRandomNumber(-5,7);
 			if(y < 0 && y > -2)
 				y = -2;
 			if(y > 0 && y < 2)
 				y = 2;
			break;
		case 2:
 			y = getRandomNumber(-4,7);
			break;
		case 3:
 			y = getRandomNumber(-4,5);
			break;
		case 4:
 			y = getRandomNumber(-3,3);
			break;
		case 5:
 			y = getRandomNumber(-3,1);
			break;
		case 6:
 			y = getRandomNumber(-2,-1);
			break;
		case 7:
 			y = getRandomNumber(-2,-1);
			break;
		default:
			_terminate(SWITCH_ERROR);			
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
unsigned int getsAway(Position criminal, Map* map) {

	if(getCoordinate(map, criminal.x, criminal.y) == -1)
		return TRUE;

	return FALSE;
}

/**
 * Determine if criminal has been caught
 * @param  criminal Position of criminal
 * @param  map      Map of territory
 * @return          TRUE if caught, FALSE if not
 */
unsigned int isCaught(Position criminal, Map* map) {

	if(getCoordinate(map, criminal.x, criminal.y) == 0)
		return TRUE;
	
	return FALSE;
}

/**
 * Move criminal in boat to most beneficial position
 * @param criminal Position of criminal
 * @param map      Map of harbor
 */
void moveCriminalInBoat(Position* criminal, Map* map) {
	int value=0;
	int bestX;
	int bestY;
	unsigned int tmp;

	tmp = getCoordinate(map, criminal->x, criminal->y);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x;
		bestY = criminal->y;
	}

	tmp = getCoordinate(map, criminal->x+1, criminal->y);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x+1;
		bestY = criminal->y;
	}

	tmp = getCoordinate(map, criminal->x, criminal->y+1);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x;
		bestY = criminal->y+1;
	}

	tmp = getCoordinate(map, criminal->x-1, criminal->y);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x-1;
		bestY = criminal->y;
	}

	tmp = getCoordinate(map, criminal->x, criminal->y-1);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x;
		bestY = criminal->y-1;
	}

	tmp = getCoordinate(map, criminal->x+1, criminal->y+1);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x+1;
		bestY = criminal->y+1;
	}

	tmp = getCoordinate(map, criminal->x-1, criminal->y-1);
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
	if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
		_terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move criminal in car to most beneficial position
 * @param criminal Position of criminal
 * @param map      Map of city
 */
void moveCriminalInCar(Position* criminal, Map* map) {
	int value=0;
	int bestX;
	int bestY;
	unsigned int tmp;
	
	tmp = getCoordinate(map, criminal->x, criminal->y);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x;
		bestY = criminal->y;
	}

	tmp = getCoordinate(map, criminal->x+1, criminal->y);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x+1;
		bestY = criminal->y;
	}

	tmp = getCoordinate(map, criminal->x, criminal->y+1);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x;
		bestY = criminal->y+1;
	}

	tmp = getCoordinate(map, criminal->x-1, criminal->y);
	if(tmp > value) {
		value = tmp;
		bestX = criminal->x-1;
		bestY = criminal->y;
	}

	tmp = getCoordinate(map, criminal->x, criminal->y-1);
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
	if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
		_terminate(TRANSMIT_ERROR);
#endif

}

/**
 * Move left in boat
 * @param criminal Position of criminal
 */
void moveLeftInBoat(Position* criminal) {
	int newX, newY;
	newX = criminal->y;
	newY = criminal->y - criminal->x;
	criminal->x = newX - 2;
	criminal->y = newY - 2;

#ifdef DEBUG
	char send_buffer[1024];
	bzero(send_buffer, 1024);
	sprintf(send_buffer, "Move Left. Criminal at (!I, !I)\n", criminal->x, criminal->y);
	if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
		_terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move forward in boat
 * @param criminal Position of criminal
 */
void moveForwardInBoat(Position* criminal) {
	criminal->x = criminal->x - 2;
	criminal->y = criminal->y - 2;

#ifdef DEBUG
	char send_buffer[1024];
	bzero(send_buffer, 1024);
	sprintf(send_buffer, "Move Forward. Criminal at (!I, !I)\n", criminal->x, criminal->y);
	if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
		_terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move right in boat
 * @param criminal Position of criminal
 */
void moveRightInBoat(Position* criminal) {
	int newX, newY;
	newX = criminal->x - criminal->y;
	newY = criminal->x;
	criminal->x = newX - 2;
	criminal->y = newY - 2;


#ifdef DEBUG
	char send_buffer[1024];
	bzero(send_buffer, 1024);
	sprintf(send_buffer, "Move Right. Criminal at (!I, !I)\n", criminal->x, criminal->y);
	if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
		_terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move forward in car
 * @param criminal Position of criminal
 */
void moveForwardInCar(Position* criminal) {
	criminal->y = criminal->y - 2;

#ifdef DEBUG
	char send_buffer[1024];
	bzero(send_buffer, 1024);
	sprintf(send_buffer, "Move Forward. Criminal at (!I, !I)\n", criminal->x, criminal->y);
	if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
		_terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Move right in car
 * @param criminal Position of criminal
 */
void moveRightInCar(Position* criminal) {
	int newX, newY;
	newX = criminal->y * -1;
	newY = criminal->x - 2;
	criminal->x = newX;
	criminal->y = newY;

#ifdef DEBUG
	char send_buffer[1024];
	bzero(send_buffer, 1024);
	sprintf(send_buffer, "Move Right. Criminal at (!I, !I)\n", criminal->x, criminal->y);
	if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
		_terminate(TRANSMIT_ERROR);
#endif
}

/**
 * Get the next move from user and make move
 * @param criminal Current position of criminal in harbor
 */
void getMoveInBoat(Position* criminal) {
	char buffer[2];
	size_t bytes;

	if(read_until_delim_or_n(STDIN, buffer, '#', sizeof(buffer), &bytes))
		_terminate(READ_ERROR);

	if(buffer[0] == 'R')
		moveRightInBoat(criminal);
	else if (buffer[0] == 'F')
		moveForwardInBoat(criminal);
	else if (buffer[0] == 'L')
		moveLeftInBoat(criminal);

}

/**
 * Get the next move from user and make move
 * @param criminal Current position of criminal in city
 */
void getMoveInCar(Position* criminal) {
	char buffer[2];
	size_t bytes;

	if(read_until_delim_or_n(STDIN, buffer, '#', sizeof(buffer), &bytes))
		_terminate(READ_ERROR);

	if(buffer[0] == 'R')
		moveRightInCar(criminal);
	else if (buffer[0] == 'F')
		moveForwardInCar(criminal);

}

/**
 * Initialize coordinate values for harbor map
 * @param map_ptr pointer to Map pointer for storing new map
 */
void initHarborMap(Map **map_ptr) {
	int V;
	int newCoordinate=0;

	V = 0;
	setCoordinate(map_ptr, -1, 0, V);
	setCoordinate(map_ptr, 0, 0, V);
	setCoordinate(map_ptr, 1, 0, V);
	setCoordinate(map_ptr, 0, -1, V);
	setCoordinate(map_ptr, 0, 1, V);
	setCoordinate(map_ptr, 1, 1, V);
	setCoordinate(map_ptr, -1, -1, V);


	V = 1;
	setCoordinate(map_ptr, -1, 1, V);
	setCoordinate(map_ptr, -1, 2, V);
	setCoordinate(map_ptr, 0, 2, V);
	setCoordinate(map_ptr, 0, 3, V);
	setCoordinate(map_ptr, 1, 2, V);
	setCoordinate(map_ptr, 1, 3, V);
	setCoordinate(map_ptr, 1, -1, V);
	setCoordinate(map_ptr, 2, -1, V);
	setCoordinate(map_ptr, 2, 0, V);
	setCoordinate(map_ptr, 2, 1, V);
	setCoordinate(map_ptr, 2, 2, V);
	setCoordinate(map_ptr, 2, 3, V);
	setCoordinate(map_ptr, 3, 0, V);
	setCoordinate(map_ptr, 3, 1, V);
	setCoordinate(map_ptr, 3, 2, V);
	setCoordinate(map_ptr, 3, 3, V);	

	V = 2;
	setCoordinate(map_ptr, 2, 4, V);
	setCoordinate(map_ptr, 2, -2, V);
	setCoordinate(map_ptr, 3, 4, V);
	setCoordinate(map_ptr, 3, -1, V);
	setCoordinate(map_ptr, 4, 0, V);
	setCoordinate(map_ptr, 4, 1, V);
	setCoordinate(map_ptr, 4, 2, V);
	setCoordinate(map_ptr, 4, 3, V);
	setCoordinate(map_ptr, 4, 4, V);

	V=3;
	setCoordinate(map_ptr, 4, 5, V);
	setCoordinate(map_ptr, 2, -3, V);
	setCoordinate(map_ptr, 3, -2, V);
	setCoordinate(map_ptr, 4, -1, V);
	setCoordinate(map_ptr, 5, 0, V);
	setCoordinate(map_ptr, 5, 1, V);
	setCoordinate(map_ptr, 5, 2, V);
	setCoordinate(map_ptr, 5, 3, V);
	setCoordinate(map_ptr, 5, 4, V);
	setCoordinate(map_ptr, 5, 5, V);


	V=4;
	setCoordinate(map_ptr, 1, -4, V);
	setCoordinate(map_ptr, 2, -4, V);
	setCoordinate(map_ptr, 3, -3, V);
	setCoordinate(map_ptr, 4, -2, V);
	setCoordinate(map_ptr, 5, -1, V);
	setCoordinate(map_ptr, 6, 0, V);
	setCoordinate(map_ptr, 6, 1, V);
	setCoordinate(map_ptr, 6, 2, V);
	setCoordinate(map_ptr, 6, 3, V);
	setCoordinate(map_ptr, 6, 4, V);
	setCoordinate(map_ptr, 6, 5, V);
	setCoordinate(map_ptr, 6, 6, V);
	setCoordinate(map_ptr, 5, 6, V);



	V=5;
	setCoordinate(map_ptr, 0, -5, V);
	setCoordinate(map_ptr, 1, -5, V);
	setCoordinate(map_ptr, 2, -5, V);
	setCoordinate(map_ptr, 3, -4, V);
	setCoordinate(map_ptr, 4, -3, V);
	setCoordinate(map_ptr, 5, -2, V);
	setCoordinate(map_ptr, 6, -1, V);
	setCoordinate(map_ptr, 7, 0, V);
	setCoordinate(map_ptr, 7, 1, V);
	setCoordinate(map_ptr, 7, 2, V);
	setCoordinate(map_ptr, 7, 3, V);
	setCoordinate(map_ptr, 7, 4, V);
	setCoordinate(map_ptr, 7, 5, V);
	setCoordinate(map_ptr, 7, 6, V);
	setCoordinate(map_ptr, 7, 7, V);
	setCoordinate(map_ptr, 7, 8, V);
	setCoordinate(map_ptr, 5, 7, V);
	setCoordinate(map_ptr, 6, 7, V);

	V=6;
	setCoordinate(map_ptr, -2, -6, V);
	setCoordinate(map_ptr, -1, -6, V);
	setCoordinate(map_ptr, 0, -6, V);
	setCoordinate(map_ptr, 1, -6, V);
	setCoordinate(map_ptr, 2, -6, V);
	setCoordinate(map_ptr, 3, -5, V);
	setCoordinate(map_ptr, 4, -4, V);
	setCoordinate(map_ptr, 5, -3, V);
	setCoordinate(map_ptr, 6, -2, V);
	setCoordinate(map_ptr, 7, -1, V);
	setCoordinate(map_ptr, 8, 0, V);
	setCoordinate(map_ptr, 8, 1, V);
	setCoordinate(map_ptr, 8, 2, V);
	setCoordinate(map_ptr, 8, 3, V);
	setCoordinate(map_ptr, 8, 4, V);
	setCoordinate(map_ptr, 8, 5, V);
	setCoordinate(map_ptr, 8, 6, V);
	setCoordinate(map_ptr, 8, 7, V);
	setCoordinate(map_ptr, 8, 8, V);
	setCoordinate(map_ptr, 8, 9, V);
	setCoordinate(map_ptr, 9, 3, V);


	V=7;
	setCoordinate(map_ptr, -3, -6, V);
	setCoordinate(map_ptr, -3, -7, V);
	setCoordinate(map_ptr, -2, -7, V);
	setCoordinate(map_ptr, -1, -7, V);
	setCoordinate(map_ptr, 0, -7, V);
	setCoordinate(map_ptr, 1, -7, V);
	setCoordinate(map_ptr, 2, -7, V);
	setCoordinate(map_ptr, 3, -6, V);
	setCoordinate(map_ptr, 4, -5, V);
	setCoordinate(map_ptr, 5, -4, V);
	setCoordinate(map_ptr, 6, -3, V);
	setCoordinate(map_ptr, 7, -2, V);
	setCoordinate(map_ptr, 9, 0, V);
	setCoordinate(map_ptr, 8, -1, V);
	setCoordinate(map_ptr, 10, 3, V);
	setCoordinate(map_ptr, 9, 2, V);
	setCoordinate(map_ptr, 6, 8, V);
	setCoordinate(map_ptr, 7, 9, V);
	setCoordinate(map_ptr, 9, 5, V);
	setCoordinate(map_ptr, 9, 6, V);
	setCoordinate(map_ptr, 9, 7, V);
	setCoordinate(map_ptr, 9, 8, V);
	setCoordinate(map_ptr, 9, 9, V);
	

	V=8;
	setCoordinate(map_ptr, -4, -6, V);
	setCoordinate(map_ptr, -4, -7, V);
	setCoordinate(map_ptr, -4, -8, V);
	setCoordinate(map_ptr, -3, -8, V);
	setCoordinate(map_ptr, -2, -8, V);
	setCoordinate(map_ptr, -1, -8, V);
	setCoordinate(map_ptr, 0, -8, V);
	setCoordinate(map_ptr, 1, -8, V);
	setCoordinate(map_ptr, 2, -8, V);
	setCoordinate(map_ptr, 3, -7, V);
	setCoordinate(map_ptr, 4, -6, V);
	setCoordinate(map_ptr, 5, -5, V);
	setCoordinate(map_ptr, 6, -4, V);
	setCoordinate(map_ptr, 7, -3, V);
	setCoordinate(map_ptr, 8, -2, V);
	setCoordinate(map_ptr, 9, 1, V);
	setCoordinate(map_ptr, 9, -1, V);
	setCoordinate(map_ptr, 9, 4, V);
	setCoordinate(map_ptr, 10, -1, V);
	setCoordinate(map_ptr, 10, 0, V);
	setCoordinate(map_ptr, 10, 2, V);
	setCoordinate(map_ptr, 10, 5, V);
	setCoordinate(map_ptr, 10, 7, V);
	setCoordinate(map_ptr, 11, 5, V);
	setCoordinate(map_ptr, 3, -9, V);
	

	V=9;
	setCoordinate(map_ptr, -5, -4, V);
	setCoordinate(map_ptr, -7, -5, V);
	setCoordinate(map_ptr, -5, -5, V);
	setCoordinate(map_ptr, -4, -5, V);
	setCoordinate(map_ptr, -5, -6, V);
	setCoordinate(map_ptr, -5, -7, V);
	setCoordinate(map_ptr, -5, -8, V);
	setCoordinate(map_ptr, -5, -9, V);
	setCoordinate(map_ptr, -4, -9, V);
	setCoordinate(map_ptr, -3, -9, V);
	setCoordinate(map_ptr, -2, -9, V);
	setCoordinate(map_ptr, -1, -9, V);
	setCoordinate(map_ptr, 0, -9, V);
	setCoordinate(map_ptr, 1, -9, V);
	setCoordinate(map_ptr, 2, -9, V);
	setCoordinate(map_ptr, 3, -8, V);
	setCoordinate(map_ptr, 4, -7, V);
	setCoordinate(map_ptr, 7, -4, V);
	setCoordinate(map_ptr, -1, -5, V);
	setCoordinate(map_ptr, 9, -2, V);
	setCoordinate(map_ptr, 9, -3, V);
	setCoordinate(map_ptr, 10, 1, V);
	setCoordinate(map_ptr, 10, 4, V);
	setCoordinate(map_ptr, 10, 6, V);
	setCoordinate(map_ptr, 10, 9, V);
	setCoordinate(map_ptr, -4, -2, V);
	setCoordinate(map_ptr, 4, -8, V);
	setCoordinate(map_ptr, 5, -7, V);
	setCoordinate(map_ptr, -4, -11, V);
	setCoordinate(map_ptr, 11, 1, V);
	setCoordinate(map_ptr, 11, 2, V);
	setCoordinate(map_ptr, 11, 4, V);	
	setCoordinate(map_ptr, 11, 6, V);
	setCoordinate(map_ptr, 11, 7, V);		
	setCoordinate(map_ptr, 12, 2, V);
	setCoordinate(map_ptr, 6, -6, V);

	V=10;
	setCoordinate(map_ptr, -5, -3, V);
	setCoordinate(map_ptr, -3, -5, V);
	setCoordinate(map_ptr, -2, -5, V);	
	setCoordinate(map_ptr, -7, -6, V);
	setCoordinate(map_ptr, -6, -6, V);
	setCoordinate(map_ptr, -6, -7, V);
	setCoordinate(map_ptr, -6, -8, V);
	setCoordinate(map_ptr, -6, -9, V);
	setCoordinate(map_ptr, -6, -10, V);
	setCoordinate(map_ptr, -5, -10, V);
	setCoordinate(map_ptr, -4, -10, V);
	setCoordinate(map_ptr, -3, -10, V);
	setCoordinate(map_ptr, -2, -10, V);
	setCoordinate(map_ptr, 0, -10, V);
	setCoordinate(map_ptr, 7, -5, V);
	setCoordinate(map_ptr, 5, -6, V);
	setCoordinate(map_ptr, 6, -5, V);
	setCoordinate(map_ptr, 8, -3, V);
	setCoordinate(map_ptr, -3, -12, V);
	setCoordinate(map_ptr, 4, -9, V);
	setCoordinate(map_ptr, -5, -12, V);
	setCoordinate(map_ptr, 12, 1, V);



	V=11;
	setCoordinate(map_ptr, -4, -3, V);
	setCoordinate(map_ptr, -4, -4, V);
	setCoordinate(map_ptr, -3, -4, V);
	setCoordinate(map_ptr, -2, -4, V);
	setCoordinate(map_ptr, -1, -4, V);
	setCoordinate(map_ptr, 0, -4, V);
	setCoordinate(map_ptr, -8, -7, V);
	setCoordinate(map_ptr, -7, -7, V);
	setCoordinate(map_ptr, -7, -8, V);
	setCoordinate(map_ptr, -7, -9, V);
	setCoordinate(map_ptr, 7, -6, V);
	setCoordinate(map_ptr, -1, -10, V);
	setCoordinate(map_ptr, -2, -11, V);
	setCoordinate(map_ptr, -2, -12, V);
	setCoordinate(map_ptr, 8, -4, V);
	setCoordinate(map_ptr, -5, -11, V);
	setCoordinate(map_ptr, -6, -11, V);
	setCoordinate(map_ptr, -6, -12, V); 
	setCoordinate(map_ptr, -7, -11, V);
	setCoordinate(map_ptr, 10, 10, V);
	setCoordinate(map_ptr, 3, -10, V);


	V=12;
	setCoordinate(map_ptr, -3, -2, V);
	setCoordinate(map_ptr, -3, -3, V);
	setCoordinate(map_ptr, -2, -3, V);
	setCoordinate(map_ptr, -1, -3, V);
	setCoordinate(map_ptr, 0, -3, V);
	setCoordinate(map_ptr, -9, -8, V);
	setCoordinate(map_ptr, -8, -8, V);
	setCoordinate(map_ptr, -8, -9, V);
	setCoordinate(map_ptr, -8, -10, V);
	setCoordinate(map_ptr, 7, -7, V);  
	setCoordinate(map_ptr, -1, -11, V);
	setCoordinate(map_ptr, -3, -11, V);
	setCoordinate(map_ptr, -4, -12, V);
	setCoordinate(map_ptr, 2, -10, V);
	setCoordinate(map_ptr, 9, 10, V);



	V=13;
	setCoordinate(map_ptr, -2, -1, V);
	setCoordinate(map_ptr, -2, -2, V);
	setCoordinate(map_ptr, -1, -2, V);
	setCoordinate(map_ptr, 0, -2, V);
	setCoordinate(map_ptr, 1, -2, V);
	setCoordinate(map_ptr, 1, -3, V);
	setCoordinate(map_ptr, -9, -9, V);
	setCoordinate(map_ptr, 11, 0, V);
	setCoordinate(map_ptr, -7, -12, V);
	setCoordinate(map_ptr, 9, 11, V);
	setCoordinate(map_ptr, 8, 10, V);
	setCoordinate(map_ptr, 10, 11, V);

}

/**
 * Initialize coordinate values for city map
 * @param map_ptr pointer to Map pointer for storing new map
 */
void initCityMap(Map **map_ptr) {
	int V;
	int newCoordinate=0;

	V = 0;
	for(int x=-1; x<=1; x++) {
		for(int y=-1; y<=1; y++) {
			setCoordinate(map_ptr, x, y, V);
		}
	}

	V = 1;
	for (int x = V; x <= V+2; x++) {
		for(int y=-1; y<=1; y++) {
			if(getCoordinate(*map_ptr, x, y) == -1)
				setCoordinate(map_ptr, x, y, V);
		}	
	}
	for (int x = -1; x <= 1; x++) {
		for(int y=V; y<=V+2; y++) {
			if(getCoordinate(*map_ptr, x, y) == -1)
				setCoordinate(map_ptr, x, y, V);
		}	
	}

	V = 2;
	setCoordinate(map_ptr, 0, 4, V);
	setCoordinate(map_ptr, 2, 2, V);
	setCoordinate(map_ptr, 4, 0, V);
	setCoordinate(map_ptr, 2, -2, V);

	V=3;
	setCoordinate(map_ptr, 0, 5, V);
	setCoordinate(map_ptr, 1, 4, V);
	setCoordinate(map_ptr, 2, 3, V);
	setCoordinate(map_ptr, 3, 2, V);
	setCoordinate(map_ptr, 5, 0, V);
	setCoordinate(map_ptr, 4, -1, V);
	setCoordinate(map_ptr, 3, -2, V);
	setCoordinate(map_ptr, 2, -3, V);	
	setCoordinate(map_ptr, 1, -2, V);	

	V=4;
	setCoordinate(map_ptr, 1, 5, V);
	setCoordinate(map_ptr, 2, 4, V);
	setCoordinate(map_ptr, 5, -1, V);
	setCoordinate(map_ptr, 4, -2, V);
	setCoordinate(map_ptr, 1, -3, V);	
	setCoordinate(map_ptr, 0, -2, V);

	V=5;
	setCoordinate(map_ptr, 1, 6, V);
	setCoordinate(map_ptr, 4, 1, V);
	setCoordinate(map_ptr, 6, -1, V);	
	setCoordinate(map_ptr, 1, -4, V);

	V=6;
	setCoordinate(map_ptr, 3, 3, V);
	setCoordinate(map_ptr, 4, 2, V);
	setCoordinate(map_ptr, 3, -3, V);	
	setCoordinate(map_ptr, 2, -4, V);

	V=7;
	setCoordinate(map_ptr, 2, 5, V);
	setCoordinate(map_ptr, 3, 4, V);
	setCoordinate(map_ptr, 5, -2, V);
	setCoordinate(map_ptr, 4, -3, V);
	setCoordinate(map_ptr, 0, -3, V);	
	setCoordinate(map_ptr, -1, -2, V);

	V=8;
	setCoordinate(map_ptr, 1, 7, V);
	setCoordinate(map_ptr, 2, 6, V);
	setCoordinate(map_ptr, 5, 1, V);
	setCoordinate(map_ptr, 6, -2, V);	
	setCoordinate(map_ptr, 7, -1, V);
	setCoordinate(map_ptr, 1, -5, V);
	setCoordinate(map_ptr, 0, -4, V);

	V=9;
	setCoordinate(map_ptr, 4, 3, V);
	setCoordinate(map_ptr, 3, -4, V);
	setCoordinate(map_ptr, -2, -1, V);

	V=10;
	setCoordinate(map_ptr, 3, 5, V);
	setCoordinate(map_ptr, 5, -3, V);
	setCoordinate(map_ptr, -1, -3, V);

	V=11;
	setCoordinate(map_ptr, 2, 7, V);
	setCoordinate(map_ptr, 7, -2, V);
	setCoordinate(map_ptr, 0, -5, V);
}

int main(void) {
	Position criminal;
	Map *cityMap=NULL;
	Map *harborMap=NULL;
	unsigned int result=0;
	char flag_buf[40];
	char send_buffer[SEND_SZ];
	char x;
	size_t index=0;
	unsigned int moves=0;
	unsigned int caught=0;
	unsigned int gotAway=0;
	const char *flag = (const char*) FLAG_PAGE;

	for (unsigned int i = 0; i < 10; i++) {
		sprintf(&flag_buf[i*4], "!H", (unsigned char) *flag++);
	}

	initCityMap(&cityMap);

	for(int t=0; t<100; t++) {	
		initCarChase(&criminal);
		bzero(send_buffer, SEND_SZ);
		sprintf(send_buffer, "Criminal at (!I, !I)\n", criminal.x, criminal.y);
		if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
			_terminate(TRANSMIT_ERROR);

		do {
			//makeMoveInCar(&criminal);
			getMoveInCar(&criminal);
			moves++;

			if(isCaught(criminal, cityMap)) {

				bzero(send_buffer, SEND_SZ);
				sprintf(send_buffer, "Criminal caught in !U moves\n", moves);
				if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
					_terminate(TRANSMIT_ERROR);	
				moves = 0;
				break;

			} else {
				moveCriminalInCar(&criminal, cityMap);

				if(getsAway(criminal, cityMap)) {
					if(transmit_all(STDOUT, "Got away\n", strlen("Got away\n")))
						_terminate(TRANSMIT_ERROR);
					initCarChase(&criminal);
					bzero(send_buffer, SEND_SZ);
					sprintf(send_buffer, "Criminal at (!I, !I)\n", criminal.x, criminal.y);
					if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
						_terminate(TRANSMIT_ERROR);
				}			
			}
		} while(1);

	}
	freeMap(&cityMap);
	initHarborMap(&harborMap);
	
	for(int t=0; t<100; t++) {

		initHarborChase(&criminal);
		bzero(send_buffer, SEND_SZ);
		sprintf(send_buffer, "Criminal at (!I, !I)\n", criminal.x, criminal.y);
		if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
			_terminate(TRANSMIT_ERROR);

		do {
			//makeMoveInBoat(&criminal, harborMap);
			getMoveInBoat(&criminal);
			moves++;

			if(isCaught(criminal, harborMap)) {
				caught++;
				bzero(send_buffer, SEND_SZ);
				sprintf(send_buffer, "Criminal caught in !U moves\n", moves);
				if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
					_terminate(TRANSMIT_ERROR);	
				moves = 0;
				break;

			} else {
				moveCriminalInBoat(&criminal, harborMap);

				
				if(getsAway(criminal, harborMap)) {
					gotAway++;
					if(transmit_all(STDOUT, "Got away\n", strlen("Got away\n")))
						_terminate(TRANSMIT_ERROR);
					initHarborChase(&criminal);
					bzero(send_buffer, SEND_SZ);
					sprintf(send_buffer, "Criminal at (!I, !I)\n", criminal.x, criminal.y);
					if(transmit_all(STDOUT, send_buffer, strlen(send_buffer)))
						_terminate(TRANSMIT_ERROR);
				}
				
			}
		} while(1);
	}
	freeMap(&harborMap);
}
