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
#ifndef TRAIL_H
#define TRAIL_H 1
#include <stdint.h>
#include "rider.h"

typedef struct trail Trail;

typedef void (*trail_embark_fn)(Trail *, Rider *);
typedef void (*trail_step_fn)(Trail *);
typedef uint32_t (*trail_disembark_fn)(Trail *);

struct trail {
	uint32_t id;
	uint32_t difficulty;			// difficulty of this trail (amt of energy used to ride it)
	uint32_t length;				// length of this trail
	uint32_t rider_total;			// number of riders that have embarked on this trail
	Rider *riders;					// list of riders on this trail
	uint32_t start_decider;			// decider at start of this trail
	uint32_t end_decider;			// decider at end of this trail
	trail_embark_fn embark;			// move rider from start decider's rider queue to riders
	trail_step_fn step; 			// move rider one step on the trail
	trail_disembark_fn disembark;	// move rider from riders to end decider's rider queue
};

#define TRAIL_IO_ELEMENTS	5
#define TRAIL_IO_SZ 	(TRAIL_IO_ELEMENTS * sizeof(uint32_t))

int32_t trail_new(Trail **t, uint32_t settings[5]);
void trail_reset(Trail *t, Rider **riders);
void trail_destroy(Trail **t, Rider **riders);

#endif