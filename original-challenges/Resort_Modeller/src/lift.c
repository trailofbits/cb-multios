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
#include "rider.h"
#include "decider.h"
#include "resort.h"


/**
 * Add one rider to the chair
 *
 * @param c 	Chair
 * @param r 	Rider
 */
void chair_embark_rider(Chair *c, Rider *r) {
	rider_append(&c->riders, r);
	c->empty_seats--;
}

/**
 * Remove one rider from the chair
 *
 * @param c 	Chair
 * @return pointer to Rider or NULL if chair is empty
 */
Rider *chair_disembark_rider(Chair *c) {
	Rider *r = NULL;
	r = rider_pop(&c->riders);
	if (NULL != r) {
		c->empty_seats++;
	}
	return r;
}

/**
 * Create and initialize a chair using the given settings
 *
 * @param c 		Pointer to assign new chair
 * @param id		ID for this chair
 * @param seatas 	Number of seats on this chair
 * @return SUCCESS on success, else -1
 */
int32_t chair_new(Chair **c, uint32_t id, uint32_t seats) {
	if (0 == seats) return -1;

	Chair *new = calloc(sizeof(Chair));
	MALLOC_OK(new);

	new->id = id;
	new->seats = seats;
	new->empty_seats = seats;
	new->embark = chair_embark_rider;
	new->disembark = chair_disembark_rider;
	*c = new;

	return SUCCESS;
}

/**
 * Reset chair to initial state.
 *
 * @param c 		Chair to reset
 * @param riders 	List of riders to store riders removed from chair
 */
void chair_reset(Chair *c, Rider **riders) {
	Rider *r = NULL;
	while (NULL != (r = c->disembark(c))) {
		rider_append(riders, r);
	}
}

/**
 * Reset all chair in a list.
 *
 * @param chairs 	List of chairs
 * @param riders 	List of riders to store riders removed from chair list
 */
void chair_reset_list(Chair *chairs, Rider **riders) {
	Chair *c = chairs;
	while (NULL != c) {
		chair_reset(c, riders);
		c = c->next;
	}
}

/**
 * Add new chair to list of chairs.
 *
 * @param chairs 	List of chairs
 * @param new 		New chair
 * @return pointer to new chair.
 */
Chair *chair_append_new(Chair **chairs, Chair *new) {
	Chair *prev = *chairs;
	if (NULL == prev) { // this is the first chair
		*chairs = new;
	} else { // other chairs exist
		while (NULL != prev->next) { // find last chair
			prev = prev->next;
		}
		prev->next = new;
	}

	return new;
}

/**
 * Remove chair from a list of chairs
 *
 * @param chairs 	List of chairs
 * @return pointer to chair or NULL if list is empty
 */
Chair *chair_pop(Chair **chairs) {
	if (NULL == *chairs) {
		return NULL;
	}
	Chair *c = *chairs;
	*chairs = c->next;
	c->next = NULL;
	return c;
}

/**
 * Destroy one chair
 *
 * @param c 	Chair
 */
void chair_destroy_single(Chair **c, Rider **riders) {
	chair_reset(*c, riders);
	free(*c);
	*c = NULL;
}

/**
 * Destroy all chairs in a list
 *
 * @param chairs 	List of chairs
 */
void chair_destroy_list(Chair **chairs, Rider **riders) {
	Chair *c = NULL;
	while (NULL != *chairs) {
		c = chair_pop(chairs);
		chair_destroy_single(&c, riders);
	}
}

/**
 * Add riders to the lift queue
 *
 * @param l 		Lift
 * @param riders 	List of riders
 */
void lift_enqueue_riders(Lift *l, Rider **riders) {
	Rider *r = NULL;
	while (NULL != (r = rider_pop(riders))) {
		rider_append(&l->queue, r);
	}
}

/**
 * Remove riders from the lift queue and embark onto the next chair.
 * 	If enough riders in queue, fill the chair to capacity.
 *
 * @param l 	Lift
 * @return Number of riders that were embarked.
 */
uint32_t lift_embark_riders(Lift *l) {
	uint32_t count = 0;
	Rider *r = NULL;
	Chair *c = l->c_embark;
	while (0 != c->empty_seats) {
		r = rider_pop(&l->queue);
		if (NULL == r) {
			break;
		}
		c->embark(c, r);
		l->rider_total++;
		count++;
	}

	if (NULL == c->next) { // last chair in list
		l->c_embark = l->chairs;
	} else {
		l->c_embark = c->next;
	}
	return count;
}

/**
 * Move all riders one step further through the lift
 *
 * @param l 	Lift
 */
void lift_one_step(Lift *l) {
	// unload c_disembark chair and increment to the next chair
	l->disembark(l);

	// load c_embark char and increment to the next chair
	l->embark(l);
}

/**
 * Disembark riders from the chair and add to the lift's end decider queue.
 *  All riders on chair are disembarked.
 *
 * @param l 	Lift
 * @return Number of riders that were disembarked.
 */
uint32_t lift_disembark_riders(Lift *l) {
	uint32_t count = 0;

	Decider *d = get_decider_by_id(l->end_decider);
	if (NULL == d) {
		return count;
	}
	Rider *r = NULL;
	Chair *c = l->c_disembark;
	while (c->empty_seats < c->seats) {
		r = c->disembark(c);
		if (NULL == r) {
			break;
		}
		d->embark(d, r);
		count++;
	}

	if (NULL == c->next) { // last chair in list
		l->c_disembark = l->chairs;
	} else {
		l->c_disembark = c->next;
	}

	return count;
}

/**
 * Create and initialize a new lift
 *
 * @param l 		Pointer to store lift
 * @param settings 	Array of lift settings
 * @return lift's ID on success, else -1
 */
int32_t lift_new(Lift **l, uint32_t settings[5]) {

	Lift *new = calloc(sizeof(Lift));
	MALLOC_OK(new);

	new->id = settings[0];
	new->start_decider = settings[1];
	new->end_decider = settings[2];
	new->chair_count = settings[3];
	new->chair_capacity = settings[4];
	new->embark = lift_embark_riders;
	new->step = lift_one_step;
	new->disembark = lift_disembark_riders;

	if ((new->chair_count == 0) ||										// at least 1 chair
		(new->start_decider == new->end_decider) || 					// different start/end
		((new->chair_capacity != 2) && (new->chair_capacity != 4))) { 	// valid chair size/qty
		free(new);
		return -1;
	}

	Chair *c_new;
	// gen chairs
	// set embark and disembark chairs
	for (uint32_t i = 0; i < new->chair_count; i++) {
		chair_new(&c_new, i, new->chair_capacity);
		chair_append_new(&new->chairs, c_new);
		if (0 == i) { // first chair
			new->c_embark = c_new;
		}
		if (new->chair_count/2 == i) { // middle chair
			new->c_disembark = c_new;
		}
	}

	*l = new;
	return new->id;
}

/**
 * Reset lift to initial state (no riders on chairs or in queue).
 *
 * @param l 		Lift
 * @param riders 	List of riders to store riders removed from lift.
 */
void lift_reset(Lift *l, Rider **riders) {

	// empty all chairs
	chair_reset_list(l->chairs, riders);

	// remove riders from queue
	rider_append(riders, l->queue);
	l->queue = NULL;

	l->rider_total = 0;
	l->c_embark = l->chairs;
	l->c_disembark = l->chairs;
	for (uint32_t i = 0; i < l->chair_count; i++) {
		if (l->chair_count/2 == i) { // middle chair
			break;
		}
		l->c_disembark = l->c_disembark->next;
	}
}

/**
 * Destroy a lift and remove all riders from it
 *
 * @param l 		Lift
 * @param riders 	List to store riders into
 */
void lift_destroy(Lift **l, Rider **riders) {
	Lift *this = *l;
	// destroy all chairs and get the riders from them
	chair_destroy_list(&this->chairs, riders);
	// return all riders in queue
	rider_append(riders, this->queue);
	free(*l);
	*l = NULL;
}

