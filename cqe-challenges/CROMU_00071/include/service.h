
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

#ifndef SERVICE_H
#define SERVICE_H

#define INITIALIZATION_DATA 0x4347C000
#define INIT_DATA_LEN 4096

#define MAX_CONNECTIONS 10

typedef struct connectionList {

	char destCode[4];
	unsigned int cost;
	unsigned int time;

	struct connectionList *next;

} connectionListType;


typedef struct airportInfo {

	char code[4];
	unsigned short delayFactor;

	connectionListType *connections;

	struct airportInfo *next;

} airportInfoType;


int loadDB( airportInfoType **airports );
int showAirports( airportInfoType *airports, char *command );
int addAirport( airportInfoType **airports, char *command );
int deleteAirport( airportInfoType **airports, char *command );
int findRoutes( airportInfoType *airports, char *command );
int check4Code( airportInfoType *airports, char apCode[4]);
int check4ConnectionCode( connectionListType *connections, char apCode[4] );
int execute_cmd(airportInfoType **airports, char *buffer);
unsigned int check_db();

#endif


