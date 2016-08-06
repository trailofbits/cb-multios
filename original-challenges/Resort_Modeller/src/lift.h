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
#ifndef LIFT_H
#define LIFT_H 1

#include <stdint.h>
#include "rider.h"

typedef struct chair Chair;

typedef void (*chair_embark_fn)(Chair *, Rider *);
typedef Rider *(*chair_disembark_fn)(Chair *);

struct chair {
	uint32_t id;
	uint32_t seats;					// number of seats on chair
	uint32_t empty_seats;			// number of seats that are empty
	Rider *riders;					// list of riders on chair
	chair_embark_fn embark;			// add one rider to this chair
	chair_disembark_fn disembark;	// remove one rider from this chair
	Chair *next;
};

typedef struct lift Lift;

typedef uint32_t (*lift_embark_fn)(Lift *);
typedef uint32_t (*lift_disembark_fn)(Lift *);
typedef void (*lift_step_fn)(Lift *);

struct lift {
	uint32_t id;
	uint32_t chair_count;			// number of chairs on lift
	uint32_t chair_capacity;		// number of seats on chairs in this lift
	uint32_t rider_total;			// number of riders that have embarked on this lift
	Rider *queue;					// queue of riders ready to embark on this lift
	Chair *chairs;					// list of chairs on this lift
	Chair *c_embark;				// chair onto which riders will embark
	Chair *c_disembark;				// chair from which riders will disembark
	uint32_t start_decider;			// ID of decider at start of lift
	uint32_t end_decider;			// ID of decider at end of lift
	lift_embark_fn embark;			// move rider from queue to a chair
	lift_step_fn step; 				// move rider on step through the lift
	lift_disembark_fn disembark;	// move rider from a chair to the end decider rider queue
};

#define LIFT_IO_ELEMENTS	5
#define LIFT_IO_SZ 		(LIFT_IO_ELEMENTS * sizeof(uint32_t))

int32_t lift_new(Lift **l, uint32_t settings[5]);
void lift_reset(Lift *l, Rider **riders);
void lift_enqueue_riders(Lift *l, Rider **riders);
void lift_destroy(Lift **l, Rider **riders);

#endif