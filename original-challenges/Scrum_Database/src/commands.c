/*

Author: Steve Wood <swood@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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
#include "stdio.h"
#include "string.h"

#define COMMAND_PREFIX 0x12345678

int receive_commands( productDefType **database ) {

commandMessageType command;
int read_length;
int retval;

	while(1) {


		read_length = sizeof(command.prefix) + sizeof(command.command_length) + sizeof(command.command_type);

		if (receive_bytes((unsigned char *)&command, read_length) == -1)
			_terminate(-1);

		if (command.prefix != COMMAND_PREFIX) {

			_terminate(-1);

		}

		// check to see if the incoming data is larger than the buffer
		if (command.command_length > COMMAND_MAX_LEN) {

			_terminate(-1);
		}

		if (receive_bytes((unsigned char *)&command.command, command.command_length) == -1)
			_terminate(-1);

		switch (command.command_type) {

				case TERMINATE:

					return 0;
					break;

				case CREATE_PRODUCT:

					retval=create_product(database, command.command);
					break;

				case DELETE_PRODUCT:

					retval=delete_product(database, (messageIDType *)command.command);
					break;

				case LIST_PRODUCTS:

					retval=list_product(*database, (messageIDType *)command.command);
					break;

				case CREATE_PBI:

					retval=create_pbi( *database, (newPBIMessageType *)command.command);
					break;

				case DELETE_PBI:

					retval=delete_pbi( *database, (deletePBIMessageType *)command.command);
					break;

				case CREATE_SPRINT:

					retval=create_sprint( *database, (newSprintMessageType *)command.command);
					break;

				case DELETE_SPRINT:

					retval=delete_sprint( *database, (deleteSprintMessageType *)command.command);
					break;

				case MOVE_PBI_TO_SPRINT:

					// move an item from the product backlog to a defined sprint
					retval=move_pbi_to_sprint( *database, (movePBIMessageType *)command.command);
					break;

				case MOVE_SBI_TO_PBI:

					// move an item from the Sprint back to the product backlog
					retval=move_sbi_to_pbl( *database, (moveToPBIMessageType *)command.command);
					break;

				case UPDATE_SBI_STATUS:

					retval=update_sbi_status( *database, (updateSBIMessageType *)command.command );
					break;

				case UPDATE_SBI_POINTS:

					retval=update_sbi_points( *database, (updateSBIMessageType *)command.command );
					break;

				case UPDATE_SBI_DESCR:

					retval=update_sbi_description( *database, (updateSBIDescMessageType *)command.command );
					break;

				case LIST_ALL_PRODUCTS:

					retval = list_all_products( *database );
					break;

		} // switch

	} // while (1)


} // receive_commands



int send_response(int response_code) {

commandResponseType message;

	message.prefix = 0x87654321;
	message.command_response = response_code;

	write( STDOUT, (void *)&message, sizeof(message) );

	return 0;
	
}


