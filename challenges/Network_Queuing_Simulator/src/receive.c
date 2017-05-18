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
#include "cgc_generator.h"
#include "cgc_input.h"

// Pkt struct used by generator() calls to hold the next packet
extern pkt cgc_NextPkt;

extern interface cgc_iface;
extern double cgc_wall_clock;
extern double cgc_max_wall_clock;

// generator function pointer
int (*generator)(void);

int cgc_InitReceive(void) {
	char buf[10];
	unsigned int gen_type = 0;
	int len;

	cgc_puts("The following packet generators are available:");
	cgc_puts("  1 - Random");
	cgc_puts("  2 - Poisson");
	cgc_puts("  3 - Manual");

	// see what packet generator the user wants to employ
	while (gen_type < 1 || gen_type > 3) {
		cgc_printf("Which generator would you like to use? (1-3): ");
#ifdef PATCHED
		if ((len = cgc_readUntil(buf, 9, '\n')) == -1) {
#else
		if ((len = cgc_readUntil(buf, 29, '\n')) == -1) {
#endif
			return(-1);
		}
		gen_type = (unsigned char)cgc_atoi(buf);
	}

	// set the generator function pointer appropriately
	if (gen_type == 1) {
		if (cgc_InitRandom()) {
			return(-1);
		}
		generator = &cgc_RandomGenerator;
	} else if (gen_type == 2) {
		if (cgc_InitPoisson()) {
			return(-1);
		}
		generator = &cgc_PoissonGenerator;
	} else if (gen_type == 3) {
		if (cgc_InitManual()) {
			return(-1);
		}
		generator = &cgc_ManualGenerator;
	} else {
		cgc_puts("Invalid Generator");
		return(-1);
	}

	// see how long we need to run the simulation
	cgc_max_wall_clock = -1.0;
	while (cgc_max_wall_clock < 0) {
		cgc_printf("For how long would you like the simulation to run? (1 - 10s): ");
		if ((len = cgc_readUntil(buf, 9, '\n')) == -1) {
			return(-1);
		}
		cgc_max_wall_clock = cgc_atof(buf);
#ifdef PATCHED
		if (cgc_max_wall_clock > 10.0) {
			cgc_printf("Using max runtime of 10.0 seconds\n");
			cgc_max_wall_clock = 10.0;
		}
#endif
	}

	// init the cgc_NextPkt struct
	cgc_bzero(&cgc_NextPkt, sizeof(pkt));
	
	return(0);

}

int cgc_RX(void) {
	int i;
	queue *q;

	// keep calling the packet generator function to get the next packet
	// as long as there are packets which have arrived at time < cgc_wall_clock
	while (generator()) {
		// see if a packet was generated
		if (cgc_NextPkt.bytes == 0) {
			// nope, done with this RX() call
			break;
		}

		// see if the generated packet has actually arrived yet
		if (cgc_NextPkt.timestamp > cgc_wall_clock) {
			// nope
			break;
		}

		// see which queue should be used for the packet
		for (i = 0; i < cgc_iface.num_queues; i++) {
			q = cgc_iface.ifqueue[i];
			if (q->min_priority <= cgc_NextPkt.priority && q->max_priority >= cgc_NextPkt.priority) {
				// found the queue
				break;
			}
		}
		if (i == cgc_iface.num_queues) {
			// this shouldn't happen if we set up the queues properly
			cgc_printf("Unable to find target queue for packet with priority @d\n", cgc_NextPkt.priority);
			return(-1);
		}

		// add it to the queue
		if (q->curr_depth == 0) {
			q->head->timestamp = cgc_NextPkt.timestamp;
			q->head->bytes     = cgc_NextPkt.bytes;
			q->head->priority  = cgc_NextPkt.priority;
			q->free = q->head->next;
			q->curr_depth++;
		} else if (q->curr_depth < q->max_depth) {
			q->free->timestamp = cgc_NextPkt.timestamp;
			q->free->bytes     = cgc_NextPkt.bytes;
			q->free->priority  = cgc_NextPkt.priority;
			q->free = q->free->next;
			q->curr_depth++;
		} else {
			q->dropped_pkts++;
		}

		// mark the cgc_NextPkt as processed
		cgc_NextPkt.bytes = 0;

	}

	return(0);

}
