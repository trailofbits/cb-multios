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


#ifndef OPERATION_H
#define OPERATION_H 1

#include "tank.h"

enum {
	OPEN_VALVE = 12,
	CLOSE_VALVE = 13,
	NO_CHANGE = 14,
	SET_IN_SERVICE = 15,
	SET_OUT_OF_SERVICE = 16,
	SET_END_OF_LIFE = 17,
};

struct tankset {
	uint8_t count;
	uint8_t unk;
	uint8_t unk1;
	uint8_t unk2;
	struct tank *tanks[]; 
};

/**
 * Init a tank set with qty tanks.
 *
 * @param t Tank set to initialize
 * @param qty Quantity of tanks to create in the tank set
 * @return SUCCESS or ERR_INVALID_QTY on error.
 */
extern int create_tanks(struct tankset **t, uint8_t qty);

/**
 * Generate and update the drain factor for each tank in the tankset.
 *
 * @param t Tank set to initialize
 * @return SUCCESS or ERR_UNINITIALIZED_TANK on error.
 */
extern int update_drain_factors(struct tankset *t);

/**
 * Process the drain and fill rates to update the water level
 *	for each tank in the tankset.
 *
 * @param t Tank set
 * @return SUCCESS or ERR_UNINITIALIZED_TANK on error
 */
extern int update_water_levels(struct tankset *t);

/**
 * Check the level of each tank in the tank set for a
 *	low or critically low level.
 *
 * @param t Tank set
 * @return SUCCESS or ERR_UNINITIALIZED_TANK on error.
 */
extern int check_levels(struct tankset *t);

/**
 * For each tank in the tank set, send the status and recv
 *	the next valve position.
 *
 * @param t Tank set
 * @return SUCCESS or ERR_UNINITIALIZED_TANK, ERR_INVALID_VALVE_POS,
 *	ERR_END_OF_FILE, ERR_END_OF_LIFE on error.
 */
extern int rxtx(struct tankset *t);

#endif
 