/*

Author: Steve Wood <swood@cromulence.co>

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
#include "service.h"
#include "stdlib.h"


int remove_dives(logbook_type *Info)  {

	char buf[1024];
	int rcv_cnt;

	dive_log_type *next_dive, *prev_dive, *temp_dive;
	struct dive_data *temp_ptr, *next_ptr;

	next_dive = Info->dives;

	int dive_count = 1;

	int dive_number_to_delete = 0;

	if (next_dive == 0) {

		printf("\n");
		printf("Dive Log is empty\n");
		return 0;
	}

	// show all the dives
	list_dives(Info);

	printf("\n");
	printf("Enter Dive # to delete or blank to abort: ");

	rcv_cnt=getline(buf, sizeof(buf));
		
	if (rcv_cnt==0)
		return 0;

	dive_number_to_delete=atoi(buf);

	next_dive = Info->dives;

	// if its the dive at the head of the list take care of it a bit differently
	if (dive_number_to_delete == 1) {

		temp_dive=next_dive->next;

		// if there are downloaded dive log samples, first delete them before the dive log entry
		if (next_dive->data != 0) {

			temp_ptr=next_dive->data;

			while (temp_ptr!= 0) {

				next_ptr=temp_ptr->next;

				free(temp_ptr);

				temp_ptr=next_ptr;
			}

		}
		// now free the dive log entry
		free(next_dive);

		Info->dives = temp_dive;
		return 0;
	}


	// it wasn't at the head, so work through the list until its found
	dive_count = 1;

	while (dive_count < dive_number_to_delete && next_dive!= 0) {

		++dive_count;

		prev_dive=next_dive;
		next_dive=next_dive->next;

	}

	// make sure we didn't hit the end of the list
	if (dive_count == dive_number_to_delete && next_dive != 0) {

		// join the prior and next nodes in the linked list
		prev_dive->next = next_dive->next;

		// if there are downloaded dive log samples, first delete them before the dive log entry
		if (next_dive->data != 0) {

			temp_ptr=next_dive->data;

			while (temp_ptr!= 0) {

				next_ptr=temp_ptr->next;

				free(temp_ptr);

				temp_ptr=next_ptr;
			}
		
		}

		// now free the dive log entry
		free (next_dive);
	}
	else {

		printf("Invalid dive number entered\n");
	}

	return 0;
}

