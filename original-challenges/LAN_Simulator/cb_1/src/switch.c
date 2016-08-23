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
#include "L2.h"

int main(void) {
	unsigned char Frame[MAX_FRAME_LEN];
        fd_set readfds;
	int fd;

	L2_InitCAM();
	L2_PopulateCAM(0x0001, FD_ROUTER, 1);
	L2_PopulateCAM(0x0002, FD_ROUTER, 2);

	while (1) {
		FD_ZERO(&readfds);
		FD_SET(FD_CRS, &readfds);
		FD_SET(FD_ROUTER, &readfds);
		FD_SET(FD_CB3, &readfds);
		if (fdwait(FD_CB3+1, &readfds, NULL, NULL, NULL) != 0) {
			continue;
		}
		if (FD_ISSET(FD_CRS, &readfds)) {
			fd = FD_CRS;
		} else if (FD_ISSET(FD_ROUTER, &readfds)) {
			fd = FD_ROUTER;
		} else if (FD_ISSET(FD_CB3, &readfds)) {
			fd = FD_CB3;
		} else {
			continue;
		}
		if (L2_RxFrame(fd, Frame)) {
			L2_ForwardFrame(Frame);
		}
	}

	return(0);
}
