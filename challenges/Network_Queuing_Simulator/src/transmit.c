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
#include "cgc_input.h"
#include "cgc_receive.h"
#include "cgc_mt.h"

extern interface cgc_iface;
double cgc_wall_clock;
double cgc_max_wall_clock;
extern double delta_sum;

// get the interface bit rate, init the PRNG, and init some state variables
int cgc_InitInterface(void) {
	unsigned int speed = 0;
	int len;
	char buf[12];

	// what speed is the interface
	while (speed == 0 || speed > MAX_SPEED) {
		cgc_printf("What's the interface speed (in bps up to @d bps): ", MAX_SPEED);
		if ((len = cgc_readUntil(buf, 11, '\n')) == -1) {
			return(-1);
		}
		speed = (unsigned int)cgc_atoi(buf);
        }
	cgc_iface.speed = speed;

	// init the PRNG with this speed
	cgc_init_mt(speed);

	// set the inter-frame gap time
	cgc_iface.ifg = 96.0 / (double)speed;

	// init wall clock time...because it needs to be done somewhere
	cgc_wall_clock = 0.0;

	// init the interface packet counter
	cgc_iface.total_pkts = 0;
	cgc_iface.total_bytes = 0;

	return(0);
}

// transmit a packet from the designated queue
int cgc_TransmitPktFromQueue(unsigned char queue) {
	pkt *p;

	// make sure the queue number is valid
	if (queue >= cgc_iface.num_queues) {
		cgc_puts("Invalid queue number");
		return(-1);
	}

	// get a pointer to the packet we're transmitting
	p = cgc_iface.ifqueue[queue]->head;

	// see how long it waited in the queue
	cgc_iface.ifqueue[queue]->cumulative_latency += (cgc_wall_clock - p->timestamp);

	// update wall clock time
	cgc_wall_clock += ((p->bytes * 8.0) / (double)cgc_iface.speed) + cgc_iface.ifg;

	// decrement the queue depth
	cgc_iface.ifqueue[queue]->curr_depth--;

	// decrement the token bucket (if this isn't the priority queue)
	if (!cgc_iface.priority_queue_enabled || queue != 0) {
		cgc_iface.ifqueue[queue]->bucket -= p->bytes;
	}

	// keep some stats
	cgc_iface.ifqueue[queue]->total_pkts++;
	cgc_iface.ifqueue[queue]->total_bytes += p->bytes;
	cgc_iface.total_pkts++;
	cgc_iface.total_bytes += p->bytes;

	// mark the ring buffer packet slot as available
	p->bytes = 0;
	p->priority = 0;
	p->timestamp = 0;

	// update the queue head pointer
	cgc_iface.ifqueue[queue]->head = p->next;

	return(0);

}

// put back the max_tokens into each queue's token bucket
void cgc_ReplinishTokens(void) {
	queue *q;
	int i;

	// set all queues back to their max_tokens
	for (i = 0; i < cgc_iface.num_queues; i++) {
		q = cgc_iface.ifqueue[i];
		q->bucket = q->max_tokens;
	}
}

// convert unsigned int to string
void cgc_uint_to_str(unsigned int val, char *buf) {
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
void cgc_print_uint(char *buf, unsigned int val) {
	struct local_vars l;
	l.p = l.outbuf;

	cgc_strncpy(l.outbuf, buf, 31);
	cgc_uint_to_str(val, l.outbuf+cgc_strlen(l.outbuf));
	cgc_printf("@s\n", l.p);
}

// dump out queue stats
void cgc_PrintStats(void) {
	int i;
	int j;
	unsigned int bytes;
	pkt *p;

	cgc_printf("cgc_wall_clock: @f (s)\n", cgc_wall_clock);
	for (i = 0; i < cgc_iface.num_queues; i++) {
		cgc_printf("Queue @d\n", i);
		cgc_printf("  Pkts Transmitted:       @d\n", cgc_iface.ifqueue[i]->total_pkts);
		cgc_printf("  Pkts Dropped:           @d\n", cgc_iface.ifqueue[i]->dropped_pkts);
		if (cgc_iface.ifqueue[i]->total_pkts == 0) {
			cgc_printf("  Average Latency (s):    @f\n", 0.0);
		} else {
			cgc_printf("  Average Latency (s):    @f\n", cgc_iface.ifqueue[i]->cumulative_latency/cgc_iface.ifqueue[i]->total_pkts);
		}
		cgc_printf("  Enqueued Pkts:          @d\n", cgc_iface.ifqueue[i]->curr_depth);
		bytes = 0;
		p = cgc_iface.ifqueue[i]->head;
		for (j = 0; j < cgc_iface.ifqueue[i]->curr_depth; j++) {
			bytes += p->bytes;
			p = p->next;
		}
		cgc_printf("  Queue Depth (bytes):    @d\n", bytes);
	}
	cgc_printf("Interface Stats\n");
	cgc_print_uint("  Pkts Transmitted:       ", cgc_iface.total_pkts);
}

// service the priority (if defined) and other queues
int cgc_TX(void) {
	queue *q;
	int i;

	// replinish tokens at the beginning of the queue run
	cgc_ReplinishTokens();

	// see if there are packets waiting in the priority queue
	if (cgc_iface.priority_queue_enabled) {
		while (cgc_iface.ifqueue[0]->curr_depth) {
			// transmit the packet at the head of the queue
			if (cgc_TransmitPktFromQueue(0)) {
				cgc_puts("Packet transmission failed");
				return(-1);
			}

			if (cgc_wall_clock > cgc_max_wall_clock) {
				return(0);
			}

			// receive any new packets
			cgc_RX();
		}
	}

	// For each remaining queue
	for (i = 0; i < cgc_iface.num_queues; i++) {
		// don't service the priority queue...it has already been done
		if (cgc_iface.priority_queue_enabled && i == 0)
			continue;

		// are there packets ready to be transmitted in the queue?
		q = cgc_iface.ifqueue[i];
		while (q->curr_depth) {
			// are there tokens available to transmit the packet?
			if (q->head->bytes <= q->bucket) {
				// transmit the packet
				if (cgc_TransmitPktFromQueue(i)) {
					cgc_puts("Packet transmission failed");
					return(-1);
				}

				if (cgc_wall_clock > cgc_max_wall_clock) {
					return(0);
				}

				// receive any new packets
				cgc_RX();
			} else {
				break;
			}
		}
	}

	return(0);

}
