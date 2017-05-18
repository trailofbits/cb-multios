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
#include "cgc_L2.h"

extern char pname[10];

// kill all downstream processes
void cgc_KillAll(void) {
	char die[] = "diedie!";
	cgc_transmit(FD_ROUTER, die, 7, NULL);
	cgc_transmit(FD_CB3, die, 7, NULL);
}

uint8_t cgc_ReceiveBytes(int fd, cgc_size_t NumBytes, unsigned char *buf) {
	cgc_size_t TotalBytes = 0;
	cgc_size_t rx_bytes;
	
	if (!buf) {
		return(0);
	}

	while (TotalBytes < NumBytes) {
		if (cgc_receive(fd, buf+TotalBytes, NumBytes-TotalBytes, &rx_bytes) != 0) {
			#ifdef SWITCH
			KillAll();
			#endif
			cgc__terminate(0);
		}
		if (rx_bytes == 0) {
			#ifdef SWITCH
			KillAll();
			#endif
			cgc__terminate(0);
		}
		TotalBytes += rx_bytes;	
	}

	return(TotalBytes);
}

uint8_t cgc_SendBytes(int fd, cgc_size_t NumBytes, unsigned char *buf) {
	cgc_size_t TotalBytes = 0;
	cgc_size_t tx_bytes;

	if (!buf) {
		return(0);
	}

	while (TotalBytes < NumBytes) {
		if (cgc_transmit(fd, buf, NumBytes-TotalBytes, &tx_bytes) != 0) {
			return(TotalBytes);
		}
		if (tx_bytes == 0) {
			return(TotalBytes);
		}
		TotalBytes += tx_bytes;
	}

	return(TotalBytes);
}
