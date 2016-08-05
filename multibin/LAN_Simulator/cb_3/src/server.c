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
#include "stdlib.h"
#include "stdio.h"
#include "prng.h"
#include "common.h"
#include "L2.h"
#include "L3.h"
#include "L4.h"
#include "handlers.h"

extern Handlers Listeners[MAX_HANDLERS];

extern L3Int L3Interfaces[2];
L2Adjacency L2Adjacencies[MAX_L2_ADJACENCIES];
Queue SendQueue[MAX_QUEUE_DEPTH];

// Process the packet
uint8_t CB3_ProcessPacket(unsigned char *Packet) {
	uint8_t Id;
	uint32_t DstSubnet;
	uint32_t InterfaceSubnet;
	unsigned char Response[MAX_FRAME_LEN];
	uint8_t ResponseLen;
	uint8_t i;
	pL3Hdr pL3 = (pL3Hdr)Packet;
	pL4Hdr pL4 = (pL4Hdr)(Packet+sizeof(L3Hdr));
	pL3Hdr pL3Resp;
	pL4Hdr pL4Resp;

	if (!Packet) {
		return(0);
	}

	// check the dst addr against our interface
	if (L3Interfaces[0].Addr == pL3->Dst) {
		// make sure it's a L4 type we know how to handle
		if (pL3->NxtHdr != L4_HEADER_TYPE) {
			return(0);
		}

		// check the L4 length
		if (pL3->Len < sizeof(L4Hdr)) {
			return(0);
		}
		if (pL3->Len != sizeof(L4Hdr)+pL4->Len) {
			return(0);
		}

		// yep, forward it up the stack
		for (i = 0; i < MAX_HANDLERS; i++) {
			if (Listeners[i].L4Addr == pL4->Dst) {
				break;
			}
		}
		if (i == MAX_HANDLERS) {
			return(0);
		}

		if (Listeners[i].Handler(Packet+sizeof(L3Hdr)+sizeof(L4Hdr), pL4->Len, Response+sizeof(L3Hdr)+sizeof(L4Hdr), &ResponseLen) == 0) {
			return(0);
		}

		// form up the response packet
		pL3Resp = (pL3Hdr)Response;
		pL4Resp = (pL4Hdr)(Response+sizeof(L3Hdr));
		pL3Resp->Dst = pL3->Src;
		pL3Resp->Src = pL3->Dst;
		pL3Resp->NxtHdr = L4_HEADER_TYPE;
		pL3Resp->Len = sizeof(L4Hdr)+ResponseLen;
		pL4Resp->Dst = pL4->Src;
		pL4Resp->Src = pL4->Dst;
		pL4Resp->Len = ResponseLen;

		return(L3_ForwardPacket(Response));
		
	} else {
		return(0);
	}

	return(1);
}

int main(void) {
	unsigned char Frame[MAX_FRAME_LEN];
	unsigned char Packet[MAX_FRAME_LEN];

	seed_prng_array((uint32_t *)0x4347C000, 32);
	L2_InitCAM();
	L3_InitInterfaces();
	RegisterHandlers();

	while (1) {
		if (L3_RxPacket(FD_CB3, Packet)) {
			CB3_ProcessPacket(Packet);
		}
		L3_ServiceSendQueue();
	}
	
	return(0);
}
