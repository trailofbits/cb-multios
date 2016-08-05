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
#include "stdint.h"
#include "common.h"

#define L4_HEADER_TYPE (0x01)
#define L3FLAG_MOREFRAG (0x80)
typedef struct __attribute__((__packed__)) _L3Hdr {
	uint32_t Dst;
	uint32_t Src;
	uint8_t Len; // number of bytes after L3Hdr
	uint8_t NxtHdr;
} L3Hdr, *pL3Hdr;

typedef struct _L3RIB {
	uint32_t L3Addr;
	uint8_t Interface;
} L3RIB, *pL3RIB;

// router's L3 interfaces
typedef struct _L3Int {
	uint32_t Addr;
	uint32_t Mask;
	uint32_t Gateway;
	int Rx_FD;
	int Tx_FD;
	uint8_t Vlan;
} L3Int, *pL3Int;

// L2 adjacency table (ARP table)
#define MAX_L2_ADJACENCIES (16)
#define MAX_L2_ADJACENCY_AGE (8)
typedef struct __attribute__((__packed__)) _L2Adjacency {
	uint32_t L3Addr;
	uint16_t L2Addr;
	uint8_t Age;
	uint8_t Vlan;
} L2Adjacency, *pL2Adjacency;

// Send Queue
#define MAX_QUEUE_DEPTH (10)
#define MAX_QUEUE_AGE (10)
typedef struct _queue {
	uint32_t L3Addr;
	uint8_t Valid;
	uint8_t Age;
	uint8_t Id;
	unsigned char Frame[MAX_FRAME_LEN];
} Queue, *pQueue;

void L3_InitInterfaces(void);
uint8_t L3_RxPacket(int fd, unsigned char *Packet);
uint8_t CB3_ProcessPacket(unsigned char *Packet);
uint8_t L3_ForwardPacket(unsigned char *Packet);
uint8_t L3_ServiceSendQueue(void);
