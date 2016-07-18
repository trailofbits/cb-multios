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
#ifndef RIDER_H
#define RIDER_H 1
#include <stdint.h>

typedef enum {SKIER, BOARDER} rider_t;

typedef struct rider Rider;

typedef void __attribute__((regparm(2))) (*rider_health_ins_fn)(Rider *, uint32_t);

struct rider {
	uint32_t id;
	rider_t r_type;					// SKIER or BOARDER
	uint32_t energy_level;			// remaining energy
	uint32_t initial_energy_level; 	// initial energy level
	uint32_t trail_count;			// number of trails completed
	uint32_t trail_distance;		// distance travelled on current trail
	uint32_t health_code;
	rider_health_ins_fn health_check;
	Rider *next;
};

#define RIDER_IO_ELEMENTS	4
#define RIDER_IO_SZ 	(RIDER_IO_ELEMENTS * sizeof(uint32_t))


int32_t rider_new(Rider **rider, uint32_t settings[3]);
void rider_destroy(Rider **rider);
void rider_destroy_list(Rider **riders);
void rider_append(Rider **riders, Rider *rider);
Rider *rider_pop(Rider **riders);
void rider_reset(Rider *rider);

#endif