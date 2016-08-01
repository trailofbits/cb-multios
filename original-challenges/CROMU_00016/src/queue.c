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
#include "input.h"
#include "queue.h"

interface iface; 

// handle setting up the queues
int InitQueues(void) {
	int len;
	char buf[10];
	unsigned char num_queues = 0;
	unsigned char curr_queue;
	int min_pri;
	int max_pri;
	unsigned int queue_depth;
	unsigned int num_pkts;
	char priority_queue = 0;
	unsigned char weight;
	unsigned char total_weight = 0;
	queue *q;
	unsigned char lowest_weight = 255;
	unsigned int total_tokens;
	int i;
	unsigned char priority_vals;

	// determine how many queues are needed
	while (num_queues < MIN_QUEUES || num_queues > MAX_QUEUES) {
		printf("How many queues (1-8)?: ");
		if ((len = readUntil(buf, 9, '\n')) == -1) {
			return(-1);
		}
		num_queues = (unsigned char)atoi(buf);
	}
	iface.num_queues = num_queues;
	iface.priority_queue_enabled = 0;

	// allocate space to hold the interface queue pointers
	if (allocate(num_queues * sizeof(queue *), 0, (void **)&(iface.ifqueue))) {
		puts("Failed to allocate interface queue pointers");
		return(-1);
	}
	bzero(iface.ifqueue, num_queues * sizeof(queue *));

	// for each queue
	curr_queue = 0;
	while (curr_queue < num_queues) {
		printf("Queue @d:\n", curr_queue);
		
		// Is queue 0 a priority queue (serviced before all others)?
		if (curr_queue == 0) {
			bzero(buf, 10);
			while (buf[0] != 'y' & buf[0] != 'n') {
				printf("  Is queue #@d a priority queue(y,n): ", curr_queue);
				if ((len = readUntil(buf, 2, '\n')) == -1) {
					return(-1);
				}
				if (buf[0] == 'y') {
					iface.priority_queue_enabled = 1;
					break;
				} 
			}
		}

		// what priority values should be placed in this queue?
		min_pri = -1;
		while (min_pri < MIN_PRIORITY || min_pri > MAX_PRIORITY) {
			printf("  What's the minimum priority packet to place in queue #@d (@d-@d): ", curr_queue, MIN_PRIORITY, MAX_PRIORITY);
			if ((len = readUntil(buf, 9, '\n')) == -1) {
				return(-1);
			} else if (len == 0) {
				continue;
			}
			min_pri = (unsigned int)atoi(buf);

			// make sure that priority isn't already assigned to another queue
			for (i = 0; i < curr_queue; i++) {
				if (iface.ifqueue[i]->min_priority <= min_pri && min_pri <= iface.ifqueue[i]->max_priority) {
					printf("  That priority value is already assigned to queue @d\n", i);
					min_pri = -1;
					break;
				}
			}
		}
		max_pri = -1;
		while (max_pri < MIN_PRIORITY || max_pri > MAX_PRIORITY) {
			printf("  What's the maximum priority packet to place in queue #@d (@d-@d): ", curr_queue, MIN_PRIORITY, MAX_PRIORITY);
			if ((len = readUntil(buf, 9, '\n')) == -1) {
				return(-1);
			} else if (len == 0) {
				continue;
			}
			max_pri = (unsigned int)atoi(buf);

			// make sure max >= min
			if (max_pri < min_pri) {
				puts("  Maximum priority must be greater or equal to minimum priority");
				max_pri = -1;
				continue;
			}

			// make sure it isn't already assigned to some other queue
			for (i = 0; i < curr_queue; i++) {
				if (iface.ifqueue[i]->min_priority <= max_pri && max_pri <= iface.ifqueue[i]->max_priority) {
					printf("  That priority value is already assigned to queue @d\n", i);
					max_pri = -1;
					break;
				}
			}
		}

		// how deep should the queue be?
		queue_depth = 0;
		while (queue_depth < MIN_DEPTH || queue_depth > MAX_DEPTH) {
			printf("  What is the depth of queue #@d (@d - @d packets): ", curr_queue, MIN_DEPTH, MAX_DEPTH);
			if ((len = readUntil(buf, 9, '\n')) == -1) {
				return(-1);
			}
			queue_depth = (unsigned int)atoi(buf);
		}

		// what weight should be given to this queue (if it's not a priority queue)?
		weight = 0;
		if (!iface.priority_queue_enabled || curr_queue != 0) {
			while (weight < MIN_WEIGHT || weight > MAX_WEIGHT) {
				printf("  What is the weight of queue #@d (@d - @d percent): ", curr_queue, MIN_WEIGHT, MAX_WEIGHT);
				if ((len = readUntil(buf, 9, '\n')) == -1) {
					return(-1);
				}
				weight = (unsigned char)atoi(buf);
	
				// make sure the requested weight doesn't add up to more 
				// than the available weight for all queues
				if (total_weight + weight > 100) {
					puts("  Total weight of all queues can not exceed 100%");
					weight = 0;
				} else if ((curr_queue == num_queues-1) && (total_weight + weight != 100)) {
					puts("  Total weight of all queues must total up to 100%");
					weight = 0;
				}
			}
			if (weight < lowest_weight) {
				lowest_weight = weight;
			}
			total_weight += weight;
		}

		// allocate a new queue
		if (allocate(sizeof(queue), 0, (void **)&(iface.ifqueue[curr_queue]))) {
			printf("  Failed to allocate queue #@d\n", curr_queue);
			return(-1);
		}
		bzero(iface.ifqueue[curr_queue], sizeof(queue));
		q = iface.ifqueue[curr_queue];
		q->max_depth = queue_depth;
		q->min_priority = min_pri;
		q->max_priority = max_pri;
		q->weight = weight;

		// set the initial bucket level
		q->bucket = q->max_tokens;

		// allocate a pkt array to handle the required queue depth
		if (InitRingBuffer(queue_depth, &(q->ring_buffer))) {
			puts("  Failed to allocate pkt ring buffer");
			return(-1);
		}
		q->head = q->ring_buffer;
		q->free = q->ring_buffer;

		// move on to the next requested queue
		curr_queue++;
	}

	// make sure all priority values are covered by the queues
	priority_vals = 64;
	for (i = 0; i < num_queues; i++) {
		priority_vals -= (iface.ifqueue[i]->max_priority - iface.ifqueue[i]->min_priority + 1);
	}
	if (priority_vals != 0) {
		printf("Not all priority values from @d to @d are accounted for in the queue definitions.\n",
			MIN_PRIORITY, MAX_PRIORITY);
		return(-1);
	}
	
	// calculate the total tokens to distribute across all queues
	// such that the lowest weight queue gets 1500 tokens...
	// enough to send at least one packet
	total_tokens = 1500*100/lowest_weight;

	// set each queue's max_tokens based on the total_tokens	
	for (i = 0; i < num_queues; i++) {
		if (iface.priority_queue_enabled && i == 0)
			continue;

		q = iface.ifqueue[i];
		q->max_tokens = total_tokens * (q->weight / 100.0);
	}

	return(0);

}

// function to set up a new ring buffer
int InitRingBuffer(unsigned int num_pkts, pkt **ring_buffer) {
	unsigned int num_pages;
	unsigned int pkts_per_page;
	unsigned int page;
	pkt *p;
	pkt *prev_p;
	int i;
	unsigned int count;

	// see how many PAGE_SIZE byte allocations we'll need
	pkts_per_page = PAGE_SIZE/sizeof(pkt);
	num_pages = num_pkts/pkts_per_page + 1;

	page = 0;
	prev_p = NULL;
	count = 0;
	while (page < num_pages) {
		if (allocate(PAGE_SIZE, 0, (void *)&(p))) {
			puts("Failed to allocate pkt page");
			return(-1);
		}
		bzero(p, PAGE_SIZE);

		// if this is the first page, set the ring buffer
		// to point at its first packet (aka the page start)
		if (page == 0) {
			*ring_buffer = p;
		}

		// if we've allocated a page previously, then
		// point that page's last pkt struct at the new
		// page's first pkt struct
		if (prev_p) {
			prev_p->next = &(p[0]);
		}

		// run through the pkt structs on this page
		// pointing each at the next
		for (i = 0; i < pkts_per_page-1 && count < num_pkts-1; i++, count++) {
			p[i].next = &(p[i+1]);
		}

		// save a pointer to the last packet struct for the
		// next page (if there is one)
		prev_p = &(p[i]);

		page++;
	}

	// complete the ring
	prev_p->next = *ring_buffer;

	return(0);
}

// destroy a previously created ring buffer
int DestroyRingBuffer(unsigned char queue) {
	unsigned int pkts_per_page;
	unsigned int num_pages;
	unsigned int page;
	pkt *p;
	pkt *page_top;

	// just in case
	if (queue > iface.num_queues-1) {
		return(-1);
	}

	// see how many PAGE_SIZE byte allocations we created
	pkts_per_page = PAGE_SIZE/sizeof(pkt);
	num_pages = iface.ifqueue[queue]->max_depth/pkts_per_page + 1;

	page = 0;
	page_top = iface.ifqueue[queue]->ring_buffer;
	p = page_top;
	while (page < num_pages) {
		// find the last pkt on the page
		do {
			p = p->next;
			// end immediately if p points to the top of the ring buffer
			if (p == iface.ifqueue[queue]->ring_buffer) {
				break;
			}
		} while ((((unsigned int)p & 0xFFFFF000) == ((unsigned int)p->next & 0xFFFFF000)) && p != page_top);

		// get pointer to next page if it's not the top of the ring
		// buffer which has already been free'd
		if (p != iface.ifqueue[queue]->ring_buffer) {
			p = p->next;
		}

		deallocate(page_top, PAGE_SIZE);
		page_top = p;
		page++;
	}

	return(0);
}

// destroy the queues that were created
int DestroyQueues(void) {
	unsigned char i;

	// for each queue
	for (i = 0; i < iface.num_queues; i++) {
		// destroy the ring buffer
		if (DestroyRingBuffer(i)) {
			return(-1);
		}

		// free the queue
		deallocate(iface.ifqueue[i], sizeof(queue));
	}

	// free the interface queue pointers
	deallocate(iface.ifqueue, iface.num_queues * sizeof(queue *));

	return(0);
}
