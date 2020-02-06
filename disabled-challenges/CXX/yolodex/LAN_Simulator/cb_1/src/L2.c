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
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_stdint.h"
#include "cgc_string.h"
#include "cgc_common.h"
#include "cgc_L2.h"

L2CAM CAM[MAX_L2_CAM_ENTRIES];

#ifdef CB3
extern uint8_t cgc_Pwdgen_Offset;
#endif

// Init the L2 CAM
void cgc_L2_InitCAM(void) {
	cgc_bzero(CAM, sizeof(CAM));
}

// Populate L2 CAM
uint8_t cgc_L2_PopulateCAM(uint16_t Addr, int fd, uint8_t Vlan) {
	uint32_t i;
	uint32_t FreeEntry = MAX_L2_CAM_ENTRIES;

	if (!Addr) {
		return(0);
	}

	// does the Addr already exist in the CAM?
	for (i = 0; i < MAX_L2_CAM_ENTRIES; i++) {
		if (Addr == CAM[i].L2Addr && CAM[i].Vlan == Vlan) {
			// yep, update it
			CAM[i].L2Port = fd;
			CAM[i].Vlan = Vlan;
			return(1);
		}
		if (FreeEntry == MAX_L2_CAM_ENTRIES) {
			if (CAM[i].L2Addr == 0x0000) {
				FreeEntry = i;
			}
		}
	}

	// nope, create an entry
	if (FreeEntry == MAX_L2_CAM_ENTRIES) {
		// no free space
		return(0);
	}
	
	CAM[FreeEntry].L2Addr = Addr;
	CAM[FreeEntry].L2Port = fd;
	CAM[FreeEntry].Vlan = Vlan;

	return(1);
}

// Lookup L2 CAM entry
pL2CAM cgc_L2_LookupCAM(uint16_t Addr, uint8_t Vlan) {
	uint32_t i;

	for (i = 0; i < MAX_L2_CAM_ENTRIES; i++) {
		if (Addr == CAM[i].L2Addr && CAM[i].Vlan == Vlan) {
			return(&(CAM[i]));
		}
	}
	return(NULL);
}

// Calculate L2 Checksum
uint32_t cgc_L2_CalculateChecksum(unsigned char *Frame) {
	pL2Hdr pL2 = (pL2Hdr)Frame;
	uint32_t sum = 0;
	uint8_t i;

	if (!Frame) {
		return(0);
	}

	for (i = 0; i < sizeof(L2Hdr)+(pL2->Len)-4; i++) {
		sum += Frame[i];
	}

	return(sum);
}

// Verify L2 Checksum
uint8_t cgc_L2_VerifyChecksum(unsigned char *Frame) {
	pL2Hdr pL2 = (pL2Hdr)Frame;
	uint32_t sum = 0;
	uint8_t i;
	uint32_t FrameChksum;

	if (!Frame) {
		return(0);
	}

	sum = cgc_L2_CalculateChecksum(Frame);

	cgc_memcpy(&FrameChksum, Frame+sizeof(L2Hdr)+((pL2->Len)-4), 4);
	if (sum == FrameChksum) {
		return(1);
	}

	return(0);
}

// Receive L2 Frame
uint8_t cgc_L2_RxFrame(int fd, unsigned char *Frame) {
	cgc_size_t TotalBytes = 0;
	cgc_size_t rx_bytes;
	uint32_t FrameChksum;
	pL2Hdr pL2;

	if (!Frame) {
		return(0);
	}

	// receive the L2 header first
	if (cgc_ReceiveBytes(fd, sizeof(L2Hdr), Frame) != sizeof(L2Hdr)) {
		return(0);
	}

	// we were told to terminate
	if (!cgc_strcmp((char *)Frame, "diedie!")) {
		cgc__terminate(0);
	}

	// receive the rest of the frame based on the Len in the header
	pL2 = (pL2Hdr)Frame;
	#ifdef CB3
	cgc_Pwdgen_Offset = (pL2->Src & 0x3)+4;
	#endif
	if (cgc_ReceiveBytes(fd, pL2->Len, Frame+sizeof(L2Hdr)) != pL2->Len) {
		return(0);
	}

	// Make sure it's valid
	if (!cgc_L2_VerifyChecksum(Frame)) {
		return(0);
	}

	// make sure the VLAN tags are valid
	// based on which fd they arrived from
	if (fd == FD_CRS) {
		// only a tag of '0' is valid
		#ifdef PATCHED_1
		if (pL2->Vlan != 0) {
			cgc_KillAll();
			cgc__terminate(0);
		}

		// set the tag in the packet
		pL2->Vlan = 1;
		#else
		if (pL2->Vlan == 0) {
			pL2->Vlan = 1;
		}
		#endif
	} else if (fd == FD_ROUTER) {
		// only frames tagged with VLANs 1 or 2 are valid
		if (pL2->Vlan != 1 && pL2->Vlan != 2) {
			cgc_KillAll();
			cgc__terminate(0);
		}
	} else if (fd == FD_CB3) {
		// only a tag of '0' is valid
		if (pL2->Vlan != 0) {
			cgc_KillAll();
			cgc__terminate(0);
		}
		
		// set the tag in the packet
		#ifndef CB3
		pL2->Vlan = 2;
		#endif
	}

	// Update the checksum since we changed the Vlan tag
	FrameChksum = cgc_L2_CalculateChecksum(Frame);
	cgc_memcpy(Frame+sizeof(L2Hdr)+pL2->Len-4, &FrameChksum, 4);
	
	// populate the CAM
	cgc_L2_PopulateCAM(pL2->Src, fd, pL2->Vlan);

	return(1);
}

// Forward L2 Frame
uint8_t cgc_L2_ForwardFrame(unsigned char *Frame) {
	pL2CAM Dst_CAM;
	pL2CAM Src_CAM;
	pL2Hdr pL2 = (pL2Hdr)Frame;
	uint8_t Len;
	uint32_t FrameChksum;

	if (!Frame) {
		return(0);
	}
	
	// calc the length of the overall frame
	Len = sizeof(L2Hdr)+(pL2->Len);
	
	// look up the dst L2 addr in the CAM
	if ((Dst_CAM = cgc_L2_LookupCAM(pL2->Dst, pL2->Vlan)) == NULL) {
		// is it a broadcast addr?
		if (pL2->Dst != 0xffff) {
			// no
			return(0);
		}

		// forward the broadcast to all ports in this LAN
		if ((Src_CAM = cgc_L2_LookupCAM(pL2->Src, pL2->Vlan)) == NULL) {
			// shouldn't happen
			return(0);
		}
		if (Src_CAM->L2Port == FD_CRS || 
		    Src_CAM->L2Port == FD_CB3) {
			// send the packet to the router
			if (cgc_SendBytes(FD_ROUTER, Len, Frame) != Len) {
				return(0);
			}
		}
		if (Src_CAM->L2Port == FD_ROUTER && Src_CAM->Vlan == 1) {
			// send the packet to the CRS
			// remove the VLAN tag
			pL2->Vlan = 0;
			FrameChksum = cgc_L2_CalculateChecksum(Frame);
			cgc_memcpy(Frame+sizeof(L2Hdr)+pL2->Len-4, &FrameChksum, 4);

			if (cgc_SendBytes(FD_CRS+1, Len, Frame) != Len) {
				return(0);
			}
		}
		if (Src_CAM->L2Port == FD_ROUTER && Src_CAM->Vlan == 2) {
			// send the packet to CB3
			// remove the VLAN tag
			pL2->Vlan = 0;
			FrameChksum = cgc_L2_CalculateChecksum(Frame);
			cgc_memcpy(Frame+sizeof(L2Hdr)+pL2->Len-4, &FrameChksum, 4);
			
			if (cgc_SendBytes(FD_CB3, Len, Frame) != Len) {
				return(0);
			}
		}

		return(1);
	}
	
	// forward it to the specified port
	// Remove the VLAN tag if destined to CRS or CB3
	if (Dst_CAM->L2Port == FD_CRS) {
		pL2->Vlan = 0;
		FrameChksum = cgc_L2_CalculateChecksum(Frame);
		cgc_memcpy(Frame+sizeof(L2Hdr)+pL2->Len-4, &FrameChksum, 4);

		// also handle the difference in which FD we use for the CRS
		// versus the rest of the CB's
		if (cgc_SendBytes(Dst_CAM->L2Port+1, Len, Frame) != Len) {
			return(0);
		}
		return(1);

	} else if (Dst_CAM->L2Port == FD_CB3) {
		pL2->Vlan = 0;
		FrameChksum = cgc_L2_CalculateChecksum(Frame);
		cgc_memcpy(Frame+sizeof(L2Hdr)+pL2->Len-4, &FrameChksum, 4);
	}

	if (cgc_SendBytes(Dst_CAM->L2Port, Len, Frame) != Len) {
		return(0);
	}

	return(1);
}
