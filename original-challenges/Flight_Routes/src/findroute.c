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
#include "stdlib.h"
#include "service.h"
#include "commands.h"
#include "printf.h"

int findRoutes(airportInfoType *airports, char *command) {

char fromAirport[4];
char destAirport[4];
int offset;
int i;
int delimiter_count;
airportInfoType *srcAirport;
connectionListType *tmpConnectingAirport;
airportInfoType *connectionAirport;
connectionListType *nextHopAirport;

unsigned int cost;
unsigned int duration;
int results;



	if (airports == 0)
		return DATABASE_EMPTY;

	results = 0;

	// make sure the command line is semi formatted properly by having enough fields
	delimiter_count = 0;

	for (i=0; i < strlen(command); ++i) {

		if (command[i] == '/')
			++delimiter_count;
	}

	if (delimiter_count < 2)
		return BAD_COMMAND;
	
	//first parse the command to get the from/to airports
	offset = 0;

	while (command[offset] != '/')
		++offset;

	++offset;

	strncpy(fromAirport, command+offset, 3);

	fromAirport[3] = 0;

	if (check4Code(airports, fromAirport) == 0)
		return UNKN_CODE;

	offset+=3;

	if (command[offset] != '/')
		return BAD_COMMAND;

	++offset;

	strncpy(destAirport, command+offset, 3);

	destAirport[3] = 0;

	if (check4Code(airports, destAirport) == 0)
		return UNKN_CODE;

	srcAirport = airports;

	while(srcAirport!= 0) {

		if (strcmp(srcAirport->code, fromAirport) == 0)
			break;

		srcAirport = srcAirport->next;
	}

	// this shouldn't happen since we previously made sure the code existed
	if (srcAirport == 0)
		return UNKN_CODE;


	tmpConnectingAirport = srcAirport->connections;

	while(tmpConnectingAirport != 0) {

		cost = tmpConnectingAirport->cost;
		duration = tmpConnectingAirport->time;

		// first see if the connecting airport is actually the desired destination (direct flight)

		if (strcmp(tmpConnectingAirport->destCode, destAirport) == 0) {

			results = 1;

			printf("@s - @s: (@d, @d)\n", fromAirport, destAirport, cost, duration);

			tmpConnectingAirport = tmpConnectingAirport->next;
			continue;
		}

		// now check the connection's connections for a match with the destination

		connectionAirport = airports;

		while (connectionAirport !=0 ) {

			if (strcmp(tmpConnectingAirport->destCode, connectionAirport->code)==0)
				break;

			connectionAirport = connectionAirport->next;

		}

		if (connectionAirport == 0)
			return UNKN_CODE;


		nextHopAirport = connectionAirport->connections;

		while (nextHopAirport != 0) {

			if (strcmp(nextHopAirport->destCode, destAirport) == 0) {


				results = 1;

				printf("@s - @s - @s: (@d, @d)\n", fromAirport, tmpConnectingAirport->destCode, destAirport,
													cost+nextHopAirport->cost, duration+nextHopAirport->time);
				break;

			}

			nextHopAirport = nextHopAirport->next;

		} // while(nextHopAirport)


		tmpConnectingAirport = tmpConnectingAirport->next;

	}

	printf("\n");

	if (results)
		return COMMAND_OK;
	else
		return NO_RESULTS;
}































