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

typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;

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

#define L4_HEADER_TYPE (0x01)
typedef struct __attribute__((__packed__)) _L3Hdr {
	uint32_t Dst;
	uint32_t Src;
	uint8_t Len; // number of bytes after L3Hdr
	uint8_t NxtHdr;
} L3Hdr, *pL3Hdr;

typedef struct __attribute__((__packed__)) _L4Hdr {
	unsigned char Dst;
	unsigned char Src;
	uint8_t Len;
} L4Hdr, *pL4Hdr;

typedef struct __attribute__((__packed__)) _L2Adjacency {
	uint32_t L3Addr;
	uint16_t L2Addr;
	uint8_t Age;
	uint8_t Vlan;
} L2Adjacency, *pL2Adjacency;
