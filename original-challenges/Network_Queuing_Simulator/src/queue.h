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

#define PAGE_SIZE 4096

#define MIN_PKT_SIZE 64
#define MAX_PKT_SIZE 1500
typedef struct _pkt {
	double timestamp;
	unsigned int bytes;
	unsigned int priority;
	struct _pkt *next;
} pkt;

#define MIN_PRIORITY 0
#define MAX_PRIORITY 63
#define MIN_WEIGHT 1
#define MAX_WEIGHT 100
#define MIN_DEPTH 1
#define MAX_DEPTH 1024
#define MIN_QUEUES 1
#define MAX_QUEUES 8
typedef struct _queue {
	unsigned int max_depth;
	unsigned int curr_depth;
	unsigned int bucket;
	unsigned int max_tokens;
	unsigned int total_pkts;
	unsigned int total_bytes;
	unsigned int dropped_pkts;
	double cumulative_latency;
	unsigned char min_priority;
	unsigned char max_priority;
	unsigned char weight;
	pkt *head;
	pkt *free;
	pkt *ring_buffer;
} queue;

typedef struct _interface {
	unsigned int speed;
	unsigned int total_pkts;
	unsigned int total_bytes;
	unsigned char num_queues;
	double ifg;
	char priority_queue_enabled;
	queue **ifqueue;
} interface;

int InitQueues(void);
int InitRingBuffer(unsigned int, pkt **);
int DestroyRingBuffer(unsigned char);
int DestroyQueues(void);
