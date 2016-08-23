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
#include "string.h"
#include "common.h"
#include "L2.h"
#include "L3.h"

L3Int L3Interfaces[2];
struct _config {
	L2Adjacency L2Adjacencies[MAX_L2_ADJACENCIES];
	Queue SendQueue[MAX_QUEUE_DEPTH];
};
struct _config Config;

uint8_t MaxInterfaces;

void InitSendQueue(void) {
	uint8_t i;

	for (i = 0; i < MAX_QUEUE_DEPTH; i++) {
		Config.SendQueue[i].Valid = 0;
	}
}

// Define L3 interfaces
void L3_InitInterfaces(void) {

	#ifdef CB3
		MaxInterfaces = 1;
	
		// Set up the int for this CB
		L3Interfaces[0].Addr = 0x0a010202;
		L3Interfaces[0].Mask = 0xffffff00;
		L3Interfaces[0].Gateway = 0x0a010201;
		L3Interfaces[0].Rx_FD = FD_CB3;
		L3Interfaces[0].Tx_FD = FD_CB3;
		L3Interfaces[0].Vlan = 0;
	
		// build their L2 adjacencies
		Config.L2Adjacencies[0].L3Addr = L3Interfaces[0].Addr;
		Config.L2Adjacencies[0].L2Addr = 0xaaaa;
		Config.L2Adjacencies[0].Age = 0;
		Config.L2Adjacencies[0].Vlan = 1;
	#else   // cb_router
		MaxInterfaces = 2;

		// Set up the two ints for this CB
		L3Interfaces[0].Addr = 0x0a010101;
		L3Interfaces[0].Mask = 0xffffff00;
		L3Interfaces[0].Rx_FD = FD_ROUTER;
		L3Interfaces[0].Tx_FD = FD_ROUTER;
		L3Interfaces[0].Vlan = 1;
		L3Interfaces[1].Addr = 0x0a010201;
		L3Interfaces[1].Mask = 0xffffff00;
		L3Interfaces[1].Rx_FD = FD_ROUTER;
		L3Interfaces[1].Tx_FD = FD_ROUTER;
		L3Interfaces[1].Vlan = 2;

		// build their L2 adjacencies
		Config.L2Adjacencies[0].L3Addr = L3Interfaces[0].Addr;
		Config.L2Adjacencies[0].L2Addr = 0x0001;
		Config.L2Adjacencies[0].Age = 0;
		Config.L2Adjacencies[0].Vlan = 1;
		Config.L2Adjacencies[1].L3Addr = L3Interfaces[1].Addr;
		Config.L2Adjacencies[1].L2Addr = 0x0002;
		Config.L2Adjacencies[1].Age = 0;
		Config.L2Adjacencies[1].Vlan = 2;
	#endif 

	return;
}

// Learn a new L2 adjacency
uint8_t LearnL2Adjacency(uint32_t L3Addr, uint16_t L2Addr, uint8_t Vlan) {
	uint8_t i;
	uint8_t FreeL2Adj = MAX_L2_ADJACENCIES;
	uint8_t MaxAdjAge = 0;
	uint8_t OldL2Adj = MaxInterfaces; // never replace physical interfaces

	// skip the first MaxInterfaces number of adjacenciees
	// because those are permanent for the physical interfaces
	// of the device
	for (i = MaxInterfaces; i < MAX_L2_ADJACENCIES; i++) {
		if (Config.L2Adjacencies[i].L3Addr == 0 && FreeL2Adj == MAX_L2_ADJACENCIES) {
			// found a free L2 Adjacency entry
			FreeL2Adj = i;
		} else if (Config.L2Adjacencies[i].L3Addr != 0 && Config.L2Adjacencies[i].Age > MaxAdjAge) {
				// found an old L2 Adjacency entry
				MaxAdjAge = Config.L2Adjacencies[i].Age;
				OldL2Adj = i;
		}
		if (Config.L2Adjacencies[i].L3Addr == L3Addr) {
			// found a matching L2 Adjacency entry, so update it
			Config.L2Adjacencies[i].L2Addr = L2Addr;
			Config.L2Adjacencies[i].Age = 0;
			Config.L2Adjacencies[i].Vlan = Vlan;
			break;
		}
	}
	if (i >= MAX_L2_ADJACENCIES) {
		// didn't find a matching L2 Adjacency entry, so use
		// an empty slot or the oldest slot we found
		#ifdef PATCHED_2
		if (FreeL2Adj < MAX_L2_ADJACENCIES) {
		#else
		if (FreeL2Adj <= MAX_L2_ADJACENCIES) {
		#endif
			Config.L2Adjacencies[FreeL2Adj].L3Addr = L3Addr;
			Config.L2Adjacencies[FreeL2Adj].L2Addr = L2Addr;
			Config.L2Adjacencies[FreeL2Adj].Age = 0;
			Config.L2Adjacencies[FreeL2Adj].Vlan = Vlan;
		} else {
			Config.L2Adjacencies[OldL2Adj].L3Addr = L3Addr;
			Config.L2Adjacencies[OldL2Adj].L2Addr = L2Addr;
			Config.L2Adjacencies[OldL2Adj].Age = 0;
			Config.L2Adjacencies[OldL2Adj].Vlan = Vlan;
		}
	}

	return(1);

}
// Lookup L2 Adjacency
uint16_t LookupL2Adjacency(uint32_t TargetAddr) {
	uint8_t i;
	uint8_t Found = MAX_L2_ADJACENCIES;

	for (i = 0; i < MAX_L2_ADJACENCIES; i++) {
		if (Config.L2Adjacencies[i].L3Addr == TargetAddr) {
			// age out old entries
			if (i > MaxInterfaces) {
				Config.L2Adjacencies[i].Age++;
			}
			if (Config.L2Adjacencies[i].Age >= MAX_L2_ADJACENCY_AGE) {
				Config.L2Adjacencies[i].L3Addr = 0;
				continue;
			}
			Found = i;
			break;
		}
	}

	if (Found != MAX_L2_ADJACENCIES) {
		return(Config.L2Adjacencies[Found].L2Addr);
	}

	return(0);
}

// Resolve L2 Adjacency
uint16_t ResolveL2Adjacency(uint32_t TargetAddr, uint8_t InterfaceId) {
	uint8_t i;
	uint16_t L2Addr;
	unsigned char Frame[MAX_FRAME_LEN];
	pL2Hdr pL2 = (pL2Hdr)Frame;
	pL2Adjacency pL2Adj = (pL2Adjacency)(Frame+sizeof(L2Hdr));
	pL2Ftr pL2Footer = (pL2Ftr)(Frame+sizeof(L2Hdr)+sizeof(L2Adjacency));
	uint8_t FrameLen;

	bzero(Frame, MAX_FRAME_LEN);

	if (InterfaceId > MaxInterfaces) {
		return(0);
	}

	// form up a L2 Adjacency Discovery Packet
	pL2->Dst = 0xffff;
	pL2->Src = LookupL2Adjacency(L3Interfaces[InterfaceId].Addr);
	pL2->Len = sizeof(L2Adjacency)+sizeof(L2Ftr);
	pL2->NxtHdr = L2_ADJACENCY_DISCOVERY_TYPE;
	pL2->Vlan = L3Interfaces[InterfaceId].Vlan;
	pL2Adj->L3Addr = TargetAddr;
	pL2Adj->L2Addr = 0x0000;
	pL2Footer->Chksum = L2_CalculateChecksum(Frame);
	FrameLen = sizeof(L2Hdr)+pL2->Len;
	
	// send the L2 ADP
	if (SendBytes(L3Interfaces[InterfaceId].Tx_FD, FrameLen, Frame) != FrameLen) {
		return(0);
	}
	
	return(1);
}

// Handle L2 Adjacency Discovery Packet
uint8_t HandleL2AdjacencyDiscoveryPacket(unsigned char *Frame) {
	unsigned char ResponseFrame[MAX_FRAME_LEN];
	pL2Hdr pL2 = (pL2Hdr)ResponseFrame;
	pL2Adjacency pL2AdjResp = (pL2Adjacency)(ResponseFrame+sizeof(L2Hdr));
	uint8_t Id;
	pL2Hdr pL2Disc = (pL2Hdr)Frame;
	pL2Adjacency pL2Adj = (pL2Adjacency)(Frame+sizeof(L2Hdr));
	uint8_t FrameLen;

	if (!Frame) {
		return(0);
	}

	// see if the Addr is one of ours
	for (Id = 0; Id < MaxInterfaces; Id++) {
		if (L3Interfaces[Id].Addr == pL2Adj->L3Addr &&
		    L3Interfaces[Id].Vlan == pL2Disc->Vlan) {
			break;
		}
	}
	
	// nope, nothing to do
	if (Id == MaxInterfaces) {
		return(1);
	}

	// yep, form up a response
	pL2->Dst = pL2Disc->Src;
	if ((pL2->Src = LookupL2Adjacency(L3Interfaces[Id].Addr)) == 0) {
		// shouldn't get here
		return(0);
	}
	pL2->Len = sizeof(L2Adjacency)+sizeof(L2Ftr);
	#ifdef CB3
	pL2->Vlan = 0;
	#else
	pL2->Vlan = L3Interfaces[Id].Vlan;
	#endif
	pL2->NxtHdr = L2_ADJACENCY_RESPONSE_TYPE;
	pL2AdjResp->L3Addr = L3Interfaces[Id].Addr;
	pL2AdjResp->L2Addr = pL2->Src;
	pL2AdjResp->Age = 0;
	pL2AdjResp->Vlan = 0;
	*(uint32_t *)(ResponseFrame+sizeof(L2Hdr)+sizeof(L2Adjacency)) = L2_CalculateChecksum(ResponseFrame);

	// send the frame
	FrameLen = sizeof(L2Hdr)+pL2->Len;
	if (SendBytes(L3Interfaces[Id].Tx_FD, FrameLen, ResponseFrame) != FrameLen) {
		return(0);
	}

	return(1);

}

// Handle L2 Adjacency Response Packet
uint8_t HandleL2AdjacencyResponsePacket(unsigned char *Frame) {
	uint8_t Id;
	pL2Hdr pL2 = (pL2Hdr)Frame;
	pL2Adjacency pL2Adj = (pL2Adjacency)(Frame+sizeof(L2Hdr));
	uint8_t FrameLen;
	uint32_t DstSubnet;
	uint32_t InterfaceSubnet;

	if (!Frame) {
		return(0);
	}

	// see if the Addr on one of our subnets
	for (Id = 0; Id < MaxInterfaces; Id++) {
		InterfaceSubnet = L3Interfaces[Id].Addr & L3Interfaces[Id].Mask;
		DstSubnet = pL2Adj->L3Addr & L3Interfaces[Id].Mask;
		if (InterfaceSubnet == DstSubnet && L3Interfaces[Id].Vlan == pL2->Vlan) {
			break;
		}
	}

	// nope, nothing to do
	if (Id == MaxInterfaces) {
		return(1);
	}
	
	// yep, copy the adjacency response into the cache
	LearnL2Adjacency(pL2Adj->L3Addr, pL2Adj->L2Addr, pL2->Vlan);

	return(1);

}

// Receive L3 Packet
uint8_t L3_RxPacket(int fd, unsigned char *Packet) {
	size_t TotalBytes = 0;
	size_t rx_bytes;
	pL2Hdr pL2;
	pL3Hdr pL3;
	unsigned char Frame[MAX_FRAME_LEN];
	uint8_t Id;
	uint32_t SrcSubnet;
	uint32_t InterfaceSubnet;

	if (!Packet) {
		return(0);
	}

	bzero(Frame, MAX_FRAME_LEN);

	// Receive the L2 frame
	if (!L2_RxFrame(fd, Frame)) {
		return(0);
	}

	// Make sure the frame is of sufficient length
	pL2 = (pL2Hdr)Frame;
	if (pL2->NxtHdr == L3_HEADER_TYPE) {
		if (pL2->Len < sizeof(L3Hdr)+sizeof(L2Ftr)) {
			return(0);
		}
		pL3 = (pL3Hdr)(Frame+sizeof(L2Hdr));
		if (pL2->Len != sizeof(L3Hdr)+pL3->Len+sizeof(L2Ftr)) {
			return(0);
		}
	} else if (pL2->NxtHdr == L2_ADJACENCY_DISCOVERY_TYPE ||
		   pL2->NxtHdr == L2_ADJACENCY_RESPONSE_TYPE) {
		if (pL2->Len < sizeof(L2Adjacency)+sizeof(L2Ftr)) {
			return(0);
		}
	}
	
	// See if it's a L2 Adjacency Discovery Packet
	if (pL2->NxtHdr == L2_ADJACENCY_DISCOVERY_TYPE) {
		// yep
		HandleL2AdjacencyDiscoveryPacket(Frame);
		return(0);
	}

	// See if it's a L2 Adjacency Response Packet
	if (pL2->NxtHdr == L2_ADJACENCY_RESPONSE_TYPE) {
		// yep
		HandleL2AdjacencyResponsePacket(Frame);
		return(0);
	}

	// Otherwise, it should be a standard L3 packet
	if (pL2->NxtHdr != L3_HEADER_TYPE) {
		return(0);
	}

	// if we're the router, see if it's spoofed
	#ifndef CB3
	for (Id = 0; Id < MaxInterfaces; Id++) {
		InterfaceSubnet = L3Interfaces[Id].Addr & L3Interfaces[Id].Mask;
		SrcSubnet = pL3->Src & L3Interfaces[Id].Mask;
		if (InterfaceSubnet == SrcSubnet && L3Interfaces[Id].Vlan == pL2->Vlan) {
			break;
		}
	}
	if (Id == MaxInterfaces) {
		// didn't find a match, so it's spoofed
		return(0);
	}
	#endif

	// Copy the L3 packet bytes into the output buffer
	memcpy(Packet, Frame+sizeof(L2Hdr), pL2->Len-sizeof(L2Ftr));

	return(1);
}

uint8_t Enqueue(unsigned char *Frame, uint32_t L3Addr, uint8_t Id) {
	uint8_t i;
	uint8_t Added = 0;

	if (!Frame) {
		return(0);
	}

	// run through the queue
	for (i = 0; i < MAX_QUEUE_DEPTH; i++) {
		if (Config.SendQueue[i].Valid == 0 && !Added) {
			// add this Frame to the queue
			memcpy(Config.SendQueue[i].Frame, Frame, MAX_FRAME_LEN);
			Config.SendQueue[i].Age = 0;
			Config.SendQueue[i].Id = Id;
			Config.SendQueue[i].Valid = 1;
			Config.SendQueue[i].L3Addr = L3Addr;
			Added = 1;
			continue;
		}
		if (Config.SendQueue[i].Age < MAX_QUEUE_AGE) {
			Config.SendQueue[i].Age++;
		}
	}

	return(1);
}

uint8_t L3_ServiceSendQueue(void) {
	uint8_t i;
	uint8_t Id;
	pL2Hdr pL2;
	pL3Hdr pL3;

	// for each packet in the send queue
	for (i = 0; i < MAX_QUEUE_DEPTH; i++) {
		if (Config.SendQueue[i].Valid == 0) {
			continue;
		}
		
		pL2 = (pL2Hdr)(Config.SendQueue[i].Frame);
		pL3 = (pL3Hdr)(Config.SendQueue[i].Frame+sizeof(L2Hdr));
		Id = Config.SendQueue[i].Id;
		
		// look up the destination L2 Adjacency
		// if there's still no L2 adjacency, increment the frame age and move on
		if ((pL2->Dst = LookupL2Adjacency(Config.SendQueue[i].L3Addr)) == 0) {
			if (Config.SendQueue[i].Age < MAX_QUEUE_AGE) {
				Config.SendQueue[i].Age++;
			} else {
				// too old, drop it
				Config.SendQueue[i].Valid = 0;
			}
			continue;
		}

		pL2->Vlan = L3Interfaces[Config.SendQueue[i].Id].Vlan;

		// calculate the checksum
		*(uint32_t *)(Config.SendQueue[i].Frame+sizeof(L2Hdr)+sizeof(L3Hdr)+pL3->Len) = L2_CalculateChecksum(Config.SendQueue[i].Frame);

		// send the frame
		SendBytes(L3Interfaces[Id].Tx_FD, pL2->Len+sizeof(L2Hdr), Config.SendQueue[i].Frame);
		Config.SendQueue[i].Valid = 0;
	}

	return(1);
}

// Forward L3 Packet
uint8_t L3_ForwardPacket(unsigned char *Packet) {
	uint8_t Id;
	pL3Hdr pL3 = (pL3Hdr)Packet;
	uint32_t DstSubnet;
	uint32_t InterfaceSubnet;
	unsigned char Frame[MAX_FRAME_LEN];
	pL2Hdr pL2 = (pL2Hdr)Frame;
	uint8_t FrameLen;
	uint32_t NextHopL3Addr;

	if (!Packet) {
		return(0);
	}

	// Copy the L3 packet into the frame
	memcpy(Frame+sizeof(L2Hdr), Packet, sizeof(L3Hdr)+pL3->Len);

	// check the dst addr against our interfaces
	for (Id = 0; Id < MaxInterfaces; Id++) {
		// is the packet destined to the router itself?
		if (L3Interfaces[Id].Addr == pL3->Dst) {
			// yep, drop it
			return(0);
		}

		InterfaceSubnet = L3Interfaces[Id].Addr & L3Interfaces[Id].Mask;
		DstSubnet = pL3->Dst & L3Interfaces[Id].Mask;
		if (InterfaceSubnet == DstSubnet) {
			NextHopL3Addr = pL3->Dst;
			break;
		}
	}
	if (Id == MaxInterfaces) {
		#ifdef CB3
		// not destined to one of our networks, send it to the gateway
		Id = 0;
		NextHopL3Addr = L3Interfaces[Id].Gateway;
		#else
		return(0);
		#endif
	}

	// look up our own (src) L2 Adjacency
	if ((pL2->Src = LookupL2Adjacency(L3Interfaces[Id].Addr)) == 0) {
		// really shouldn't get here
		return(0);
	}

	// Set the L2 length
	pL2->Len = sizeof(L3Hdr) + pL3->Len + sizeof(L2Ftr);

	// Set the L2 Next Hdr
	pL2->NxtHdr = L3_HEADER_TYPE;

	// Set the VLAN
	pL2->Vlan = L3Interfaces[Id].Vlan;
	
	// look up the destination L2 Adjacency
	if ((pL2->Dst = LookupL2Adjacency(NextHopL3Addr)) == 0) {
		// send an Adjacency Discovery packet
		if (!ResolveL2Adjacency(NextHopL3Addr, Id)) {
			// failed to locate L2 host
			return(0);
		}

		// queue the frame for later delivery
		// once the L2Adjacency has been resolved
		if (!Enqueue(Frame, NextHopL3Addr, Id)) {
			return(0);
		}
		
		return(1);
	}

	// calculate the checksum
	*(uint32_t *)(Frame+sizeof(L2Hdr)+sizeof(L3Hdr)+pL3->Len) = L2_CalculateChecksum(Frame);

	// send the frame
	FrameLen = sizeof(L2Hdr)+pL2->Len;
	if (SendBytes(L3Interfaces[Id].Tx_FD, FrameLen, Frame) != FrameLen) {
		return(0);
	}

	return(1);
}

