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
#include "input.h"
#include "receive.h"
#include "mt.h"

extern interface iface;
double wall_clock;
double max_wall_clock;
extern double delta_sum;

// get the interface bit rate, init the PRNG, and init some state variables
int InitInterface(void) {
	unsigned int speed = 0;
	int len;
	char buf[12];

	// what speed is the interface
	while (speed == 0 || speed > MAX_SPEED) {
		printf("What's the interface speed (in bps up to @d bps): ", MAX_SPEED);
		if ((len = readUntil(buf, 11, '\n')) == -1) {
			return(-1);
		}
		speed = (unsigned int)atoi(buf);
        }
	iface.speed = speed;

	// init the PRNG with this speed
	init_mt(speed);

	// set the inter-frame gap time
	iface.ifg = 96.0 / (double)speed;

	// init wall clock time...because it needs to be done somewhere
	wall_clock = 0.0;

	// init the interface packet counter
	iface.total_pkts = 0;
	iface.total_bytes = 0;

	return(0);
}

// transmit a packet from the designated queue
int TransmitPktFromQueue(unsigned char queue) {
	pkt *p;

	// make sure the queue number is valid
	if (queue >= iface.num_queues) {
		puts("Invalid queue number");
		return(-1);
	}

	// get a pointer to the packet we're transmitting
	p = iface.ifqueue[queue]->head;

	// see how long it waited in the queue
	iface.ifqueue[queue]->cumulative_latency += (wall_clock - p->timestamp);

	// update wall clock time
	wall_clock += ((p->bytes * 8.0) / (double)iface.speed) + iface.ifg;

	// decrement the queue depth
	iface.ifqueue[queue]->curr_depth--;

	// decrement the token bucket (if this isn't the priority queue)
	if (!iface.priority_queue_enabled || queue != 0) {
		iface.ifqueue[queue]->bucket -= p->bytes;
	}

	// keep some stats
	iface.ifqueue[queue]->total_pkts++;
	iface.ifqueue[queue]->total_bytes += p->bytes;
	iface.total_pkts++;
	iface.total_bytes += p->bytes;

	// mark the ring buffer packet slot as available
	p->bytes = 0;
	p->priority = 0;
	p->timestamp = 0;

	// update the queue head pointer
	iface.ifqueue[queue]->head = p->next;

	return(0);

}

// put back the max_tokens into each queue's token bucket
void ReplinishTokens(void) {
	queue *q;
	int i;

	// set all queues back to their max_tokens
	for (i = 0; i < iface.num_queues; i++) {
		q = iface.ifqueue[i];
		q->bucket = q->max_tokens;
	}
}

// convert unsigned int to string
void uint_to_str(unsigned int val, char *buf) {
	char temp_buf[32];
	char *c = temp_buf;
	int count = 0;

	if (buf == NULL) {
		return;
	}

	do {
		*c = (val % 10) + '0';
		val /= 10;
		c++;
		count++;
	} while (val != 0);

	while (count-- > 0) {
		c--;
		*buf = *c;
		buf++;
	}

	*buf = '\0';

}

// badly protected function which will easily
// overflow outbuf unless CB is patched to limit
// size of val by limiting the runtime of the 
// simulation
struct local_vars {
	char outbuf[32];
	char *p;
};
void print_uint(char *buf, unsigned int val) {
	struct local_vars l;
	l.p = l.outbuf;

	strncpy(l.outbuf, buf, 31);
	uint_to_str(val, l.outbuf+strlen(l.outbuf));
	printf("@s\n", l.p);
}

// dump out queue stats
void PrintStats(void) {
	int i;
	int j;
	unsigned int bytes;
	pkt *p;

	printf("wall_clock: @f (s)\n", wall_clock);
	for (i = 0; i < iface.num_queues; i++) {
		printf("Queue @d\n", i);
		printf("  Pkts Transmitted:       @d\n", iface.ifqueue[i]->total_pkts);
		printf("  Pkts Dropped:           @d\n", iface.ifqueue[i]->dropped_pkts);
		if (iface.ifqueue[i]->total_pkts == 0) {
			printf("  Average Latency (s):    @f\n", 0.0);
		} else {
			printf("  Average Latency (s):    @f\n", iface.ifqueue[i]->cumulative_latency/iface.ifqueue[i]->total_pkts);
		}
		printf("  Enqueued Pkts:          @d\n", iface.ifqueue[i]->curr_depth);
		bytes = 0;
		p = iface.ifqueue[i]->head;
		for (j = 0; j < iface.ifqueue[i]->curr_depth; j++) {
			bytes += p->bytes;
			p = p->next;
		}
		printf("  Queue Depth (bytes):    @d\n", bytes);
	}
	printf("Interface Stats\n");
	print_uint("  Pkts Transmitted:       ", iface.total_pkts);
}

// service the priority (if defined) and other queues
int TX(void) {
	queue *q;
	int i;

	// replinish tokens at the beginning of the queue run
	ReplinishTokens();

	// see if there are packets waiting in the priority queue
	if (iface.priority_queue_enabled) {
		while (iface.ifqueue[0]->curr_depth) {
			// transmit the packet at the head of the queue
			if (TransmitPktFromQueue(0)) {
				puts("Packet transmission failed");
				return(-1);
			}

			if (wall_clock > max_wall_clock) {
				return(0);
			}

			// receive any new packets
			RX();
		}
	}

	// For each remaining queue
	for (i = 0; i < iface.num_queues; i++) {
		// don't service the priority queue...it has already been done
		if (iface.priority_queue_enabled && i == 0)
			continue;

		// are there packets ready to be transmitted in the queue?
		q = iface.ifqueue[i];
		while (q->curr_depth) {
			// are there tokens available to transmit the packet?
			if (q->head->bytes <= q->bucket) {
				// transmit the packet
				if (TransmitPktFromQueue(i)) {
					puts("Packet transmission failed");
					return(-1);
				}

				if (wall_clock > max_wall_clock) {
					return(0);
				}

				// receive any new packets
				RX();
			} else {
				break;
			}
		}
	}

	return(0);

}
