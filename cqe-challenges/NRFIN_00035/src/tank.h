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


#ifndef TANK_H
#define TANK_H 1

#include <stdint.h>
#include "h2o.h"

enum {
	/* Valve positions */
	CLOSED = 0,
	OPEN = 1,
	/* Status values */
	IN_SERVICE = 2,
	OUT_OF_SERVICE = 6,
};

struct tank {
	uint8_t id;				// ID number of tank
	uint8_t fill_rate; 		// amt of h2o added per round
	uint8_t drain_rate; 	// amt of h2o drained per round
	uint8_t valve_position; // position of valve
	uint8_t capacity; 		// qty of h2o tank can hold
	uint8_t level; 			// qty of h2o in tank
	uint8_t status; 		// status of tank
	uint8_t eol; 			// make struct into even mult of 4 bytes
	struct h2o *contents[];	// array of h2o ptrs
};

/**
 * Create a new tank of the given capacity.
 *
 * @param id Tank ID number
 * @param capacity Tank capacity
 * @return VA tank
 */
extern struct tank *create_tank(uint8_t id, uint8_t capacity);

/**
 * Set the fill rate for the tank.
 *
 * @param t Tank
 * @param fr Fill rate
 * @return SUCCESS or ERR_UNINITIALIZED_TANK, ERR_END_OF_LIFE on error
 */
extern int set_fill_rate(struct tank *t, uint8_t fr);

/**
 * Set the drain rate for the tank.
 *
 * @param t Tank
 * @param dr Drain rate
 * @return SUCCESS or ERR_UNINITIALIZED_TANK, ERR_END_OF_LIFE on error
 */
extern int set_drain_rate(struct tank *t, uint8_t dr);

/**
 * Set the input valve state to open
 *
 * @param t Tank
 * @return SUCCESS or ERR_UNINITIALIZED_TANK, ERR_END_OF_LIFE on error
 */
extern int open_valve(struct tank *t);

/**
 * Set the input valve state to closed
 *
 * @param t Tank
 * @return SUCCESS or ERR_UNINITIALIZED_TANK, ERR_END_OF_LIFE on error
 */
extern int close_valve(struct tank *t);

/**
 * Set the status of the tank.
 *
 * @param t Tank
 * @param s Status IN_SERVICE or OUT_OF_SERVICE
 * @return SUCCESS or ERR_UNINITIALIZED_TANK on error
 */
extern int set_status(struct tank *t, uint8_t s);

/**
 * Set the tank to be in-service. Allow input and output.
 *
 * @param t Tank
 * @return SUCCESS or ERR_UNINITIALIZED_TANK, ERR_END_OF_LIFE on error
 */
extern int set_in_service(struct tank *t);

/**
 * Set the tank to be out-of-service. Close and disallow input and output.
 *
 * @param t Tank
 * @return SUCCESS or ERR_UNINITIALIZED_TANK, ERR_END_OF_LIFE on error
 */
extern int set_out_of_service(struct tank *t);

/**
 * Check the in-service status.
 *
 * @param t Tank
 * @return TRUE if in-service, FALSE if not or ERR_UNINITIALIZED_TANK,
 *	ERR_END_OF_LIFE on error
 */
extern int is_in_service(struct tank *t);

/**
 * Set the tank to as having reached end-of-life. Close and disallow input and output.
 * It cannot be undone.
 *
 * @param t Tank
 * @return SUCCESS or ERR_UNINITIALIZED_TANK, ERR_END_OF_LIFE on error
 */
extern int set_end_of_life(struct tank *t);

/**
 * Check the end-of-life status.
 *
 * @param t Tank
 * @return TRUE if at end-of-life, FALSE if not or ERR_UNINITIALIZED_TANK,
 *	ERR_END_OF_LIFE on error
 */
extern int is_end_of_life(struct tank *t);

/**
 * Add units of water to the tank.
 *
 * @param t Tank
 * @param qty Quantity of water units
 * @return SUCCESS or ERR_UNINITIALIZED_TANK on error
 */
extern int add_water(struct tank *t, uint8_t qty);

/**
 * Remove units of water from tank.
 *
 * @param t Tank
 * @param qty Quantity of water units
 * @return SUCCESS or ERR_UNINITIALIZED_TANK on error
 */
extern int rm_water(struct tank *t, uint8_t qty);

/**
 * Fill tank with units of water defined by fill rate.
 *
 * @param t Tank
 * @return SUCCESS or ERR_UNINITIALIZED_TANK, ERR_END_OF_LIFE on error
 */
extern int do_fill(struct tank *t);

/**
 * Drain tank of units of water defined by drain rate.
 *
 * @param t Tank
 * @return SUCCESS or ERR_UNINITIALIZED_TANK, ERR_END_OF_LIFE on error
 */
extern int do_drain(struct tank *t);

/**
 * Check tank level to against low level marker.
 *
 * @param t Tank
 * @return TRUE if at or below low level, FALSE if 
 *	above low level or ERR_UNINITIALIZED_TANK, ERR_END_OF_LIFE on error.
 */
extern int is_level_low(struct tank *t);

/**
 * Check tank level to against critically low level marker.
 *
 * @param t Tank
 * @return TRUE if at or below critical low level, FALSE if 
 *	above critical low level or ERR_UNINITIALIZED_TANK, ERR_END_OF_LIFE on error.
 */
extern int is_level_crit_low(struct tank *t);

#endif
