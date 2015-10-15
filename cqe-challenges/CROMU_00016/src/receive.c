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
#include <libcgc.h>
#include "stdlib.h"
#include "queue.h"
#include "generator.h"
#include "input.h"

// Pkt struct used by generator() calls to hold the next packet
extern pkt NextPkt;

extern interface iface;
extern double wall_clock;
extern double max_wall_clock;

// generator function pointer
int (*generator)(void);

int InitReceive(void) {
	char buf[10];
	unsigned int gen_type = 0;
	int len;

	puts("The following packet generators are available:");
	puts("  1 - Random");
	puts("  2 - Poisson");
	puts("  3 - Manual");

	// see what packet generator the user wants to employ
	while (gen_type < 1 || gen_type > 3) {
		printf("Which generator would you like to use? (1-3): ");
#ifdef PATCHED
		if ((len = readUntil(buf, 9, '\n')) == -1) {
#else
		if ((len = readUntil(buf, 29, '\n')) == -1) {
#endif
			return(-1);
		}
		gen_type = (unsigned char)atoi(buf);
	}

	// set the generator function pointer appropriately
	if (gen_type == 1) {
		if (InitRandom()) {
			return(-1);
		}
		generator = &RandomGenerator;
	} else if (gen_type == 2) {
		if (InitPoisson()) {
			return(-1);
		}
		generator = &PoissonGenerator;
	} else if (gen_type == 3) {
		if (InitManual()) {
			return(-1);
		}
		generator = &ManualGenerator;
	} else {
		puts("Invalid Generator");
		return(-1);
	}

	// see how long we need to run the simulation
	max_wall_clock = -1.0;
	while (max_wall_clock < 0) {
		printf("For how long would you like the simulation to run? (1 - 10s): ");
		if ((len = readUntil(buf, 9, '\n')) == -1) {
			return(-1);
		}
		max_wall_clock = atof(buf);
#ifdef PATCHED
		if (max_wall_clock > 10.0) {
			printf("Using max runtime of 10.0 seconds\n");
			max_wall_clock = 10.0;
		}
#endif
	}

	// init the NextPkt struct
	bzero(&NextPkt, sizeof(pkt));
	
	return(0);

}

int RX(void) {
	int i;
	queue *q;

	// keep calling the packet generator function to get the next packet
	// as long as there are packets which have arrived at time < wall_clock
	while (generator()) {
		// see if a packet was generated
		if (NextPkt.bytes == 0) {
			// nope, done with this RX() call
			break;
		}

		// see if the generated packet has actually arrived yet
		if (NextPkt.timestamp > wall_clock) {
			// nope
			break;
		}

		// see which queue should be used for the packet
		for (i = 0; i < iface.num_queues; i++) {
			q = iface.ifqueue[i];
			if (q->min_priority <= NextPkt.priority && q->max_priority >= NextPkt.priority) {
				// found the queue
				break;
			}
		}
		if (i == iface.num_queues) {
			// this shouldn't happen if we set up the queues properly
			printf("Unable to find target queue for packet with priority @d\n", NextPkt.priority);
			return(-1);
		}

		// add it to the queue
		if (q->curr_depth == 0) {
			q->head->timestamp = NextPkt.timestamp;
			q->head->bytes     = NextPkt.bytes;
			q->head->priority  = NextPkt.priority;
			q->free = q->head->next;
			q->curr_depth++;
		} else if (q->curr_depth < q->max_depth) {
			q->free->timestamp = NextPkt.timestamp;
			q->free->bytes     = NextPkt.bytes;
			q->free->priority  = NextPkt.priority;
			q->free = q->free->next;
			q->curr_depth++;
		} else {
			q->dropped_pkts++;
		}

		// mark the NextPkt as processed
		NextPkt.bytes = 0;

	}

	return(0);

}
