/*

Author: Steve Wood <swood@cromulence.com>

Copyright (c) 2016 Cromulence LLC

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
#include "malloc.h"
#include "stdlib.h"
#include "service.h"


void makeAirportCode( unsigned char *readPtr, char apCode[4]);
char *findAirportCodebyNumber(airportInfoType *airports, int connectionNum);

int loadDB(airportInfoType **airports) {


unsigned char *readPtr;
unsigned char airportCount;
unsigned int offset;
unsigned int i;
char airportCode[4];
char *code;

airportInfoType *tmpPtr;
struct connectionList *tmpConnectionPtr;
int connectionCount;
int connectionNum;


	// this should only be called on an empty database
	if (*airports != 0)
		return -1;

	readPtr = (unsigned char *)INITIALIZATION_DATA;
	offset = 1;

	airportCount = *readPtr % 16 + 5;


	*airports = malloc(sizeof(airportInfoType));

	if (*airports == 0)
		return -1;

	tmpPtr = *airports;

	for (i=0; i < airportCount; ++i) {

		while (1) {

			makeAirportCode(readPtr+offset, airportCode);
			offset+=3;

			if (check4Code(*airports, airportCode)== -1) {

				continue;
			}
			else {
		
				break;
			}

		} // while(1)	
		
		strcpy(tmpPtr->code, airportCode);

		// if this isn't the last one, malloc memory for the next
		if (i < airportCount -1 ) {

			tmpPtr->next = malloc(sizeof(airportInfoType));

			if (tmpPtr->next == 0)
				return -1;

			tmpPtr = tmpPtr->next;
		}
		// otherewise just terminate the linked list
		else
			tmpPtr->next = 0;

	}

	// now create the connections to other airports.
	tmpPtr = *airports;

	while (tmpPtr != 0) {

		connectionCount = *(readPtr + offset) % (airportCount/2) + 1;
		offset++;

		tmpPtr->connections = malloc(sizeof(connectionListType));

		if (tmpPtr->connections == 0)
			return -1;

		tmpConnectionPtr = (struct connectionList *)tmpPtr->connections;

		i = 0;
		do {

			connectionNum = *(readPtr + offset) % airportCount;
			offset++;


			code = findAirportCodebyNumber(*airports, connectionNum);


			if (check4ConnectionCode(tmpPtr->connections, code) == -1) {


				strcpy(tmpConnectionPtr->destCode, code);

				tmpConnectionPtr->cost = *(unsigned char *)(readPtr+offset);
				++offset;

				tmpConnectionPtr->time = *(unsigned char *)(readPtr+offset);
				++offset;

				++i;

				if (i < connectionCount) {

					tmpConnectionPtr->next = malloc(sizeof(connectionListType));

					if (tmpConnectionPtr->next == 0)
						return -1;

					tmpConnectionPtr = tmpConnectionPtr->next;
				}

			}


		} while (i < connectionCount);

		tmpPtr = tmpPtr->next;

	} // while (tmpPtr != 0)

	return 0;
}

// map the random bytes from the magic page into the uppercase alphabet to make an airport code
void makeAirportCode(unsigned char *readPtr, char apCode[4]) {

unsigned char tmpchar;
int i;


	for (i=0; i< 3; ++i) {

		tmpchar = *(char *)(readPtr+i);
		tmpchar = (tmpchar % 26) + 'A';

		apCode[i] = tmpchar;
	}

	apCode[i] = 0;

}

// returns 0 if its not found in the list, -1 if it is.
int check4Code(airportInfoType *airports, char apCode[4]) {


	// if the airport list is empty, this is a fine code obviously
	if (airports == 0)
		return 0;

	while (airports != 0) {

		if (apCode[0] == airports->code[0] && 
				apCode[1] == airports->code[1] &&
				apCode[2] == airports->code[2] ) 
			return -1;
		else
			airports = airports->next;

	}

	return 0;

}

// returns -1 if the code is not found, or its position in the list otherwise
int check4ConnectionCode(connectionListType *connections, char apCode[4]) {

int count;

	count = 0;

	while(connections != 0) {


		if (connections->destCode[0] == apCode[0] &&
			connections->destCode[1] == apCode[1] &&
			connections->destCode[2] == apCode[2] )

			return count;

		count++;
		connections = connections->next;

	} // while

	return -1;

}


char *findAirportCodebyNumber(airportInfoType *airports, int connectionNum) {

int i;

	i = 0;

	while(i < connectionNum && airports != 0) {


		airports = airports->next;

		++i;

	}

	return(airports->code);

}






