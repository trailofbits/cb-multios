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


int showAirports(airportInfoType *airports, char *command) {

connectionListType *connection;
char apCode[4];
int i;
int results;

	results = 0;

	if (airports == 0)
		return DATABASE_EMPTY;

	apCode[0] = 0;

	for (i=0; i < strlen(command); ++i) {

		if (command[i] == '/') {

			if (strlen(command+i+1) != 3)
				return BAD_COMMAND;	

			strcpy(apCode, command+i+1);

			break;
		}
	}

	while (airports != 0) {

		if (apCode[0] != 0) {

			if (strcmp(apCode, airports->code) != 0) {

				airports = airports->next;
				continue;
			}

		}

		results = 1;
		printf("Airport: @s\n", airports->code);

		printf("Connections: ");

		connection = airports->connections;

		if (connection == 0) {
			printf("\n\n");
			airports = airports->next;
			continue;
		}

		printf("@s (@d, @d)", connection->destCode, connection->cost, connection->time);

		connection = connection->next;

		while (connection!= 0) {

			printf(", @s (@d, @d)", connection->destCode, connection->cost, connection->time);

			connection = connection->next;
		}

		printf("\n\n");

		airports = airports->next;

	}

	if (results)
		return COMMAND_OK;
	else
		return NO_RESULTS;

}


int addAirport(airportInfoType **airports, char *command) {

char newCode[4];
char newConn[4];
char buffer[20];
int i;
int x;
airportInfoType *tmpAirport;
airportInfoType *apPtr;
connectionListType *tmpConnection;
int duplicateCode;
int delimiter_count;
int ccount;
connectionListType connections2add[MAX_CONNECTIONS];

	delimiter_count = 0;

	for (i=0; i < strlen(command); ++i) {

		if (command[i] == '/')
			++delimiter_count;
	}

	if (delimiter_count) {


		// make sure at least one connection is specified by having 4 delimiters
		// and if there are enough parameters (3 per connecting airport plus the initial new airport code
		if (delimiter_count < 4 || (delimiter_count % 3 != 1)) {

			return BAD_COMMAND;
		}

		i = 0;

		while(command[i] != '/')
			++i;

		++i;

		strncpy(newCode, command+i, 3);
		newCode[3] = 0;

		i+=3;

			// validate that it does not already exist
		if (check4Code(*airports, newCode) != 0) {

			return DUPLICATE_CODE;
		}

		ccount = 0;


		while (1) {

#ifdef PATCHED_1
			if (ccount >= MAX_CONNECTIONS -1) {

				return BAD_COMMAND;
			}
#endif

			if (command[i] != '/')
				return BAD_COMMAND;

			++i;

			strncpy(connections2add[ccount].destCode, command+i, 3);

			connections2add[ccount].destCode[3] = 0;


			if (check4Code(*airports, connections2add[ccount].destCode) == 0) {

				return UNKN_CODE;
			}

			for (x=0; x < ccount; ++x) {

				if (strcmp(connections2add[ccount].destCode, connections2add[x].destCode)== 0)
					return DUPLICATE_CODE;
			}

			i+=3;

			if (command[i] != '/')
				return BAD_COMMAND;

			++i;

			connections2add[ccount].cost = atoi(command+i);


			while(command[i] != '/')
				++i;

			++i;

			connections2add[ccount].time = atoi(command+i);

			while (command[i] != '/' && command[i] != 0)
				++i;

			ccount++;

			if (command[i] == 0)
				break;

		} // while (1)


	} // if delimiter_count
	else {

		// get airport code
		getline(newCode, sizeof(newCode));

		// validate that it does not already exist
		if (check4Code(*airports, newCode) != 0) {

			printf("Duplicate code detected\n");
			return DUPLICATE_CODE;
		}

		// add connections

		ccount = 0;

		while (1) {

			// get airport code for connection
			printf("Enter airport code for connection:\n");
			getline(newConn, sizeof(newConn));

			// if its blank then terminate adding new connections
			if (newConn[0] == 0)
				break;
			
			if (strcmp(newCode, newConn) == 0) {

				printf("Illegal connection value\n");
				continue;
			}
			// validate connections exist and are not duplicates of existing connections
			if (check4Code(*airports, newConn) == 0) {

				printf("Connecting airport not found\n");
				continue;
			}

			duplicateCode = 0;
			for (x=0; x < ccount; ++x) {

				if (strcmp(newConn, connections2add[x].destCode)== 0) {
					duplicateCode = 1;
					printf("Duplicate connection\n");
					break;
				}
			}

			// if that was a duplicate code, go back to the top and try again
			if (duplicateCode)
				continue;

			// now tmpConnection points to the newly allocated memory
			strncpy(connections2add[ccount].destCode, newConn, 4);

			printf("Connection cost:\n");
			getline(buffer, sizeof(buffer));

			connections2add[ccount].cost = atoi(buffer);

			printf("Connection duration:\n");
			getline(buffer, sizeof(buffer));

			connections2add[ccount].time = atoi(buffer);

			++ccount;

		} // while(1)

	} // else


	// create the entry at the end
	tmpAirport = malloc(sizeof(airportInfoType));

	// memory allocation failed
	if (tmpAirport == 0) 
		return UNRECOVERABLE_ERROR;

	strcpy(tmpAirport->code, newCode);
	tmpAirport->next = 0;
	tmpAirport->connections = 0;

	if (*airports == 0) {

		*airports = tmpAirport;
	}
	else {

		apPtr = *airports;

		while(apPtr->next != 0)
			apPtr = apPtr->next;

		apPtr->next = tmpAirport;

	}

	for (i = 0; i < ccount; ++i) {

		if (tmpAirport->connections == 0) {

			tmpAirport->connections = malloc(sizeof(connectionListType));

			if (tmpAirport->connections == 0)
				return UNRECOVERABLE_ERROR;

			tmpConnection = tmpAirport->connections;

			tmpConnection->next = 0;
		}
		else {

			tmpConnection->next = malloc(sizeof(connectionListType));

			if (tmpConnection->next == 0)
				return UNRECOVERABLE_ERROR;

			tmpConnection = tmpConnection->next;

			tmpConnection->next = 0;
		}

		strncpy(tmpConnection->destCode, connections2add[i].destCode, 4);
		tmpConnection->cost = connections2add[i].cost;
		tmpConnection->time = connections2add[i].time;

	}

	return COMMAND_OK;

} //addAirport


// remove an airport, and remove it from any airports listing it as a connection
int deleteAirport(airportInfoType **airports, char *command) {

char apCode[4];
airportInfoType *tmpAirport;
airportInfoType *apPtr;
connectionListType *tmpConnection;
connectionListType *prevConnection;
int found;
int i;


	// if the airport database is empty, just return because there's nothing to delete
	if (*airports == 0)
		return DATABASE_EMPTY;

	apCode[0] = 0;

	for (i=0; i < strlen(command); ++i) {

		if (command[i] == '/') {

#ifdef PATCHED_2
			strncpy(apCode, command+i+1, 3);
			apCode[3] = 0;
#else
			strcpy(apCode, command+i+1);
#endif
			if (strlen(apCode) != 3)
				return BAD_COMMAND;

			break;
		}
	} // for

	if (apCode[0] == 0) {
		// get airport code for connection
		printf("Enter airport code for deletion:\n");
		getline(apCode, sizeof(apCode));

		// if its blank then terminate adding new connections
		if (apCode[0] == 0)
			return COMMAND_TERMINATED;
	}

	// see if the matching airport is in the head node
	if (strcmp((*airports)->code, apCode) == 0) {

		tmpAirport = *airports;

		tmpConnection = tmpAirport->connections;

		while(tmpConnection != 0) {

			tmpAirport->connections = tmpConnection->next;

			free(tmpConnection);

			tmpConnection = tmpAirport->connections;
		}

		*airports = (*airports)->next;

		free(tmpAirport);

	}
	else {
		tmpAirport = (*airports)->next;
		apPtr = *airports;

		found = 0;

		while(tmpAirport != 0) {

			if (strcmp(tmpAirport->code, apCode) == 0) {

				found = 1;
				break;
			}
			else {
				apPtr = tmpAirport;
				tmpAirport = tmpAirport->next;
			}

		}

		if (found) {

			apPtr->next = tmpAirport->next;
			free(tmpAirport);

		}
		else
			return UNKN_CODE;

	} //else


	// now go find all references as a connection and remove them
	apPtr = *airports;

	while (apPtr != 0) {


		if (apPtr->connections == 0) {

			apPtr = apPtr->next;
			continue;
		}

		if (strcmp(apPtr->connections->destCode, apCode)== 0) {

			tmpConnection = apPtr->connections;

			apPtr->connections = apPtr->connections->next;

			free(tmpConnection);
			
			apPtr = apPtr->next;
			continue;

		}

		prevConnection = apPtr->connections;
		tmpConnection = prevConnection->next;

		while(tmpConnection!= 0) {


			if (strcmp(tmpConnection->destCode, apCode) == 0) {


				prevConnection->next = tmpConnection->next;

				free(tmpConnection);
				break;
			}

			prevConnection = tmpConnection;
			tmpConnection = prevConnection->next;

		} // while(tmpConnection)

		apPtr = apPtr->next;

	} // while (apPtr != 0)

	return COMMAND_OK;

} // deleteAirport



