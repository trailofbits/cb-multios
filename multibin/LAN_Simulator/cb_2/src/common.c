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
#include "stdint.h"
#include "string.h"
#include "L2.h"

extern char pname[10];

// kill all downstream processes
void KillAll(void) {
	char die[] = "diedie!";
	transmit(FD_ROUTER, die, 7, NULL);
	transmit(FD_CB3, die, 7, NULL);
}

uint8_t ReceiveBytes(int fd, size_t NumBytes, unsigned char *buf) {
	size_t TotalBytes = 0;
	size_t rx_bytes;
	
	if (!buf) {
		return(0);
	}

	while (TotalBytes < NumBytes) {
		if (receive(fd, buf+TotalBytes, NumBytes-TotalBytes, &rx_bytes) != 0) {
			#ifdef SWITCH
			KillAll();
			#endif
			_terminate(0);
		}
		if (rx_bytes == 0) {
			#ifdef SWITCH
			KillAll();
			#endif
			_terminate(0);
		}
		TotalBytes += rx_bytes;	
	}

	return(TotalBytes);
}

uint8_t SendBytes(int fd, size_t NumBytes, unsigned char *buf) {
	size_t TotalBytes = 0;
	size_t tx_bytes;

	if (!buf) {
		return(0);
	}

	while (TotalBytes < NumBytes) {
		if (transmit(fd, buf, NumBytes-TotalBytes, &tx_bytes) != 0) {
			return(TotalBytes);
		}
		if (tx_bytes == 0) {
			return(TotalBytes);
		}
		TotalBytes += tx_bytes;
	}

	return(TotalBytes);
}
