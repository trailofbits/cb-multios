/*

Author: Joe Rogers <joe@cromulence.co>

Copyright (c) 2014 Cromulence LLC

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
#include "cgc_queue.h"
#include "cgc_transmit.h"
#include "cgc_receive.h"
#include "cgc_input.h"

extern double cgc_wall_clock;
extern double cgc_max_wall_clock;

int main(int cgc_argc, char *cgc_argv[]) {

	cgc_puts("Welcome to the network queuing simulator");

	if (cgc_InitInterface()) {
		cgc_puts("Unable to init interface\n");
		cgc__terminate(-1);
	}

	if (cgc_InitReceive()) {
		cgc_puts("Unable to init packet generator\n");
		cgc__terminate(-1);
	}

	if (cgc_InitQueues()) {
		cgc_puts("Failed to initialize queues\n");
		cgc__terminate(-1);
	}

	while (1)  {
		cgc_RX();
		cgc_TX();
		// increment cgc_wall_clock time since we don't have
		// any packets to TX or RX
		cgc_wall_clock += 0.00001;
		if (cgc_wall_clock > cgc_max_wall_clock) {
			break;
		}
	}

	cgc_PrintStats();

	cgc_DestroyQueues();

	cgc__terminate(0);
}
