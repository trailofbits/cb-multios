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
#ifndef L2_H
#define L2_H

#include <libcgc.h>
#include "stdint.h"

#define FD_CRS (1)
#define FD_ROUTER (4)
#define FD_CB3 (6)

// flag to enable Echo packet to cb3 on router startup
#define ROUTER

#define L3_HEADER_TYPE (0x01)
#define L2_ADJACENCY_DISCOVERY_TYPE (0x02)
#define L2_ADJACENCY_RESPONSE_TYPE (0x03)
typedef struct __attribute__((__packed__)) _L2Hdr {
	uint16_t Dst;
	uint16_t Src;
	uint8_t Len; // num bytes after L2Hdr including checksum footer
	uint8_t NxtHdr;
	uint8_t Vlan;
} L2Hdr, *pL2Hdr;

typedef struct __attribute__((__packed__)) _L2Ftr {
	uint32_t Chksum;
} L2Ftr, *pL2Ftr;

#define MAX_L2_CAM_ENTRIES (255)
typedef struct _L2CAM {
	uint16_t L2Addr;
	uint8_t Vlan;
	uint8_t L2Port;
} L2CAM, *pL2CAM;

void L2_InitCAM(void);
uint8_t L2_PopulateCAM(uint16_t Addr, int fd, uint8_t Vlan);
pL2CAM L2_LookupCAM(uint16_t Addr, uint8_t Vlan);
uint32_t L2_CalculateChecksum(unsigned char *Frame);
uint8_t L2_VerifyChecksum(unsigned char *Frame);
uint8_t L2_RxFrame(int fd, unsigned char *Frame);
uint8_t L2_ForwardFrame(unsigned char *Frame);

#endif
