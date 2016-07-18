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
#include "lift.h"
#include "trail.h"
#include "rider.h"
#include "decider.h"

static uint8_t *fp = (uint8_t *)FLAG_PAGE;
static uint16_t fp_idx = 0;

/**
 * Create and initialize a new transport option
 *
 * @param to 		Pointer to store new transport option
 * @param o_type 	Type of transport option
 * @param transport Transport
 */
void option_new(TOption **to, toption_t o_type, void *transport) {
	TOption *new = calloc(sizeof(TOption));
	MALLOC_OK(new);

	new->o_type = o_type;
	new->transport = transport;
	new->next = NULL;
	*to = new;
}

/**
 * Add new option to list of options.
 *
 * @param options 	List of options
 * @param new 		New option
 */
void option_append_new(TOption **options, TOption *new) {
	TOption *prev = *options;
	if (NULL == prev) { // this is the first one
		*options = new;
	} else { // other chairs exist
		while (NULL != prev->next) { // find last one
			prev = prev->next;
		}
		prev->next = new;
	}
}

/**
 * Remove first transport option from the list
 *
 * @param options 	List of transport options
 * @return pointer to transport option or NULL if none
 */
TOption *option_pop(TOption **options) {
	if (NULL == *options) {
		return NULL;
	}
	TOption *to = *options;
	*options = to->next;
	to->next = NULL;
	return to;
}

/**
 * Destroy a single transport option
 *
 * @param to 	Transport option
 */
void option_destroy_single(TOption **to) {

	// Do not destroy the transport itself, would cause use-after-free issues
	// Destroy them from the lift and trail master lists in the Resort.

	// switch(to->o_type) {
	// 	case LIFT:
	// 		lift_destroy((Lift **)&to->transport);
	// 		break;
	// 	case TRAIL:
	// 		trail_destroy((Trail **)&to->transport);
	// 		break;
	// 	default:
	// 		break;
	// }

	free(*to);
	*to = NULL;
}

/**
 * Destroy a list of transport options
 *
 * @param options 	List of transport options
 */
void option_destroy_list(TOption **options) {
	TOption *to = NULL;
	while (NULL != *options) {
		to = option_pop(options);
		option_destroy_single(&to);
	}
}

/**
 * Get flag page idx and update it
 *
 * @return fp idx
 */
uint16_t get_next_fp_idx(void) {
	uint16_t idx = fp_idx;
	fp_idx = (fp_idx + 1) % 4096;
	return idx;
}

/**
 * Get a random transport option
 *
 * @param d 	Decider
 * @return pointer to option or NULL if none
 */
TOption *decider_select_option(Decider *d) {
	uint8_t selection_idx = fp[get_next_fp_idx()] % d->option_count;
	TOption *to = d->t_options;
	for (uint8_t i = 0; i < selection_idx; i++) {
		to = to->next;
	}
	return to;
}

/**
 * Add a transport option to the decider
 *
 * @param d 		Decider
 * @param o_type 	Transport option type
 * @param transport Transport
 */
void decider_add_option(Decider *d, toption_t o_type, void *transport) {
	TOption *to = NULL;
	option_new(&to, o_type, transport);
	option_append_new(&d->t_options, to);
	d->option_count++;

}

/**
 * Add rider to the queue
 *
 * @param d 	Decider
 * @param r 	Rider
 */
void decider_embark(Decider *d, Rider *r) {
	rider_append(&d->queue, r);
}

/**
 * Move all riders from queue to a transport option
 *
 * @param d 	Decider
 * @return Number of riders disembarked
 */
uint32_t decider_disembark(Decider *d) {
	Rider *r = NULL;
	Trail *t = NULL;
	TOption *to = NULL;
	uint32_t count = 0;

	if (0 == d->option_count) {
		return count;
	}

	while (NULL != (r = rider_pop(&d->queue))) {
		to = decider_select_option(d);
		if (NULL == to) {
			rider_append(&d->queue, r);
			break;
		}
		switch(to->o_type) {
			case LIFT:
				if (0 == r->energy_level) {
					r->health_check(r, r->id);
					rider_append(&d->quitters, r);
				} else {
					lift_enqueue_riders((Lift *)to->transport, &r);
				}
				count++;
				break;
			case TRAIL:
				t = (Trail *)to->transport;
				if (t->difficulty > r->energy_level) {
					r->health_check(r, r->id);
					rider_append(&d->quitters, r);					
				} else {
					t->embark(t, r);
				}
				count++;
				break;
			default:
				rider_append(&d->queue, r);
				break;
		}
	}
	return count;
}

/**
 * Create and initialize a new Decider
 *
 * @param d 		Pointer to store new decider
 * @param settings 	Settings for new decider
 * @return ID of decider else -1 on error
 */
int32_t decider_new(Decider **d, uint32_t settings[2]) {

	Decider *new = calloc(sizeof(Decider));
	MALLOC_OK(new);

	new->id = settings[0];
	new->altitude = settings[1];
	new->embark = decider_embark;
	new->disembark = decider_disembark;

	if (0 == new->altitude) {
		free(new);
		return -1;
	}

	*d = new;
	return new->id;
}

/**
 * Reset the decider to the initial state
 *
 * @param d 		Decider
 * @param riders 	List to store riders into
 */
void decider_reset(Decider *d, Rider **riders) {

	// get riders out of queue
	rider_append(riders, d->queue);
	d->queue = NULL;
	// get riders out of quitters
	rider_append(riders, d->quitters);
	d->quitters = NULL;

	// The caller should reset transport options separately via the Resort lists
}

/**
 * Destroy the decider. The caller must destroy any lifts/trails assigned to this decider.
 *
 * @param d 	Decider
 */
void decider_destroy(Decider **d, Rider **riders) {
	Decider *this = *d;
	// return riders in queue
	if (NULL != this->queue) {
		rider_append(riders, this->queue);
	}
	// return riders in quitters
	if (NULL != this->quitters) {
		rider_append(riders, this->quitters);
	}

	// destroy transport options
	TOption *to = this->t_options;
	option_destroy_list(&to);

	free(*d);
	*d = NULL;
}

