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

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_service.h"
#include "cgc_commands.h"
#include "cgc_printf.h"


airportInfoType *airports;

int main(int cgc_argc, char *cgc_argv[]) {

char command[150];
int retval;
unsigned int databaseCheck;


	// compare the consistency of the database (magic page)
	databaseCheck = cgc_check_db();

	cgc_printf("Database checksum: @d\n", databaseCheck);

	// load data from the magic page
	if (cgc_loadDB(&airports) == -1)
		cgc__terminate(-1);


	while(1) {

		cgc_getline(command, sizeof(command));

		retval = cgc_execute_cmd(&airports, command);


		switch (retval) {

			case COMMAND_OK:

				cgc_printf("OK\n");
				break;

			case BAD_COMMAND:

				cgc_printf("BAD COMMAND FORMAT\n");
				break;

			case DUPLICATE_CODE:

				cgc_printf("AIRPORT CODE EXISTS\n");
				break;

			case UNKN_CODE:

				cgc_printf("UNKNOWN AIRPORT\n");
				break;

			case DATABASE_EMPTY:

				cgc_printf("EMPTY DB\n");
				break;

			case COMMAND_TERMINATED:

				cgc_printf("COMMAND TERMINATED\n");
				break;

			case NO_RESULTS:

				cgc_printf("NO RESULTS\n");
				break;

			case UNRECOVERABLE_ERROR:

				cgc_printf("TERMINATING\n");
				cgc__terminate(-1);
				break;

				// quit command
			case -99:

				cgc_printf("OK\n");
				break;

			default:

				cgc_printf("UNSPECIFIED ERROR\n");


		} // switch

		if (retval == -99)
			break;

	} // while

    cgc__terminate(0);

}  // main  

