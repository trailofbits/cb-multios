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

#include <libcgc.h>
#include <stdint.h>
#include "libc.h"
#include "rider.h"

/**
 * Function to check the health of a rider when they run out of energy
 *
 * @param r 	Rider
 * @param id 	Rider ID
 */
void __attribute__((regparm(2))) rider_health_check(Rider *r, uint32_t r_id) {

	uint32_t *results = &r->health_code;
#ifdef PATCHED_1
	if (0 == r->energy_level) {
		*results = r->health_code;
	}
#else
	if (0 == r->energy_level) {
		*results++ = r->health_code;
	}
	*results = r->health_code;
#endif
}

/**
 * Create and initialize a new rider
 *
 * @param riders	Pointer to store rider
 * @param settings 	Array of rider settings
 * @return SUCCESS on success, else -1
 */
int32_t rider_new(Rider **rider, uint32_t settings[4]) {

	Rider *new = calloc(sizeof(Rider));
	MALLOC_OK(new);

	new->id = settings[0];
	new->r_type = settings[1];
	new->energy_level = settings[2];
	new->initial_energy_level = new->energy_level;
	new->health_code = settings[3];
	new->health_check = rider_health_check;

	if ((new->energy_level == 0) ||
		((new->r_type != SKIER) && (new->r_type != BOARDER))) {
		free(new);
		return -1;
	}	

	*rider = new;
	return SUCCESS;
}

/**
 * Destroy one rider
 *
 * @param rider 	Rider
 */
void rider_destroy(Rider **rider) {
	free(*rider);
	*rider = NULL;
}

/**
 * Destroy all riders in a list
 *
 * @param riders 	List of Riders
 */
void rider_destroy_list(Rider **riders) {
	Rider *this = *riders;
	while (NULL != this) {
		this = rider_pop(riders);
		rider_destroy(&this);
		this = *riders;
	}
	*riders = NULL;
}

/**
 * Append on or more riders to the list of riders
 *
 * @param riders 	List of riders that will be appended to
 * @param rider 	A single rider or a list of riders to append 
 */
void rider_append(Rider **riders, Rider *rider) {
	Rider *this = *riders;
	Rider *prev = *riders;

	if (NULL == this) { // was empty list, to rider is first
		*riders = rider;
	} else {  // find end of riders then append
		while (NULL != this) {
			prev = this;
			this = this->next;
		}
		prev->next = rider;
	}
}

/**
 * Remove first rider from list
 *
 * @param riders 	List of riders
 * @return pointer to first rider or NULL if empty list
 */
Rider *rider_pop(Rider **riders) {
	Rider *this = *riders;
	if (NULL != this) {
		*riders = this->next;
		this->next = NULL;
	}
	return this;
}

void rider_reset(Rider *rider) {
	rider->energy_level = rider->initial_energy_level;
	rider->trail_count = 0;
	rider->trail_distance = 0;
}
