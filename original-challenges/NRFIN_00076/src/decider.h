/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef DECIDER_H
#define DECIDER_H 1
#include <stdint.h>
#include "rider.h"
#include "lift.h"
#include "trail.h"


typedef enum {LIFT, TRAIL} toption_t;

typedef struct transport_option TOption;
struct transport_option {
	toption_t o_type;				// type of transport option
	void *transport;				// pointer to transport option
	TOption *next;
};

typedef struct decider Decider;

typedef void (*decider_embark_fn)(Decider *, Rider *);
typedef uint32_t (*decider_disembark_fn)(Decider *);

struct decider {
	uint32_t id;
	uint32_t altitude; 				// altitude of this decider
	Rider *queue;					// queue of riders on this decider ready to embark on lift or trail
	Rider *quitters;				// list of riders that are too tired to continue (0 energy level)
	uint32_t option_count;			// number of transport options
	TOption *t_options;				// list of transport options for riders (LIFT or TRAIL)
	decider_embark_fn embark;		// move rider from transport option to queue
	decider_disembark_fn disembark;	// move rider from queue to transport option
};

#define DECIDER_IO_ELEMENTS 	2
#define DECIDER_IO_SZ 	(DECIDER_IO_ELEMENTS * sizeof(uint32_t))


int32_t decider_new(Decider **d, uint32_t settings[2]);
void decider_reset(Decider *d, Rider **riders);
void decider_destroy(Decider **d, Rider **riders);
void decider_add_option(Decider *d, toption_t o_type, void *transport);


#endif