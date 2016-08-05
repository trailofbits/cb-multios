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
#include "common.h"
#include "string.h"
#include "L2.h"
#include "L3.h"
#include "L4.h"

// Send an echo packet to cb3 on startup to init L2Adjacencies
void SendEchoRequest(void) {
	unsigned char Packet[MAX_FRAME_LEN];
	pL3Hdr pL3 = (pL3Hdr)Packet;
	pL4Hdr pL4 = (pL4Hdr)(Packet+sizeof(L3Hdr));

	bzero(Packet, MAX_FRAME_LEN);

	// build up the L4 header
	pL4->Dst = 7; // echo port
	pL4->Src = 1; // src port, don't care
	pL4->Len = 4;
	memcpy(Packet+sizeof(L3Hdr)+sizeof(L4Hdr), (void *)0x4347C000, 4);

	// build up the L3 header
	pL3->Dst = 0x0a010202;
	pL3->Src = 0x0a010201;
	pL3->Len = sizeof(L4Hdr)+pL4->Len;
	pL3->NxtHdr = 0x1;

	// Forward the Packet
	L3_ForwardPacket(Packet);

}

int main(void) {
	unsigned char Frame[MAX_FRAME_LEN];
	unsigned char Packet[MAX_FRAME_LEN];

	L2_InitCAM();
	L3_InitInterfaces();

	SendEchoRequest();

	while (1) {
		bzero(Packet, MAX_FRAME_LEN);
		if (L3_RxPacket(FD_ROUTER, Packet)) {
			L3_ForwardPacket(Packet);
		}
		L3_ServiceSendQueue();
	}
	
	return(0);
}
