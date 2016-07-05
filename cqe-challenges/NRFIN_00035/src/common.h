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

#ifndef COMMON_H
#define COMMON_H 1

/* Number of seconds to sleep between each round */
#define SLEEP_INT_SEC 0
#define SLEEP_INT_USEC 577

/* Units of H2O added to each tank in each round */
#define FILL_RATE 12

/* Quantity of tanks */
#define TANK_QTY 10

/* Tank capacity (units of H2O) */
#define TANK_CAP 255

/* Tank initial volume (units of H2O) */
#define INIT_LEVEL 90

/* Tank volume (units of H2O) marking low level */
#define LOW_LEVEL 25

/* Tank volume (units of H2O) marking critically low level */
#define CRIT_LEVEL 5

enum {
	ERR_END_OF_FILE = -14,
	ERR_UNINITIALIZED_TANK = -15,
	ERR_INVALID_QTY = -16,
	ERR_INVALID_VALVE_POS = -17,
	ERR_TANK_EMPTY = -18,
	ERR_END_OF_LIFE = -19,
	ERR_TANK_FULL = -20,
};

#endif