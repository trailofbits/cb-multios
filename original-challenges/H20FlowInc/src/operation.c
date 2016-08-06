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
#include "libc.h"
#include "common.h"
#include "operation.h"
#include "tank.h"

int create_tanks(struct tankset **t, uint8_t qty) {
	if (0 == qty) {
		return ERR_INVALID_QTY;
	}

	*t = calloc(sizeof(struct tankset) + qty * sizeof(struct tank *));

	for (int i = 0; i < qty; i++) {
		(*t)->tanks[i] = create_tank(i + 1, TANK_CAP);
		(*t)->count++;
	}

	return SUCCESS;
}

int update_drain_factors(struct tankset *t) {
	uint8_t factor = 0;
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}
	int ret = 0;
	for (int idx = 0; idx < t->count; idx++) {
		if ((FALSE == is_end_of_life(t->tanks[idx])) && (TRUE == is_in_service(t->tanks[idx]))) {
			factor = prng_get_next();
			if (0 == factor % 2) {
				FAILBAIL(set_drain_rate(t->tanks[idx], 2 * factor));
			} else {
				FAILBAIL(set_drain_rate(t->tanks[idx], factor));
			}
		}
	}
	return SUCCESS;
}

int update_water_levels(struct tankset *t) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}

	int ret = 0;
	for (int idx = 0; idx < t->count; idx++) {
		if (FALSE == is_end_of_life(t->tanks[idx])) {
			FAILBAIL(do_drain(t->tanks[idx]));
			FAILBAIL(do_fill(t->tanks[idx]));
		}
	}
	return SUCCESS;
}

int check_levels(struct tankset *t) {
	if (NULL == t) {
		return ERR_UNINITIALIZED_TANK;
	}

	int ret = 0;
	for (int idx = 0; idx < t->count; idx++) {
		if (FALSE == is_end_of_life(t->tanks[idx])) {

			// check critical low level, if so, send alert msg
			if (TRUE == is_level_crit_low(t->tanks[idx])) {
#if PATCHED
				syslog(LOG_ERROR, "Tank ~n level below critical level", t->tanks[idx]->id);
#else
				// VULN: null ptr de-ref
				syslog(LOG_ERROR, "Tank ~n level below critical level", t->tanks[TANK_QTY]->id);
#endif
			}

			// check low level, if so, fill above low level marker
			if (TRUE == is_level_low(t->tanks[idx])) {
				FAILBAIL(add_water(t->tanks[idx], 1 + LOW_LEVEL - t->tanks[idx]->level));
			}
		}
	}

	return SUCCESS;
}

int rxtx(struct tankset *t) {
	uint8_t valve_pos = 0;
	int ret = 0;
	for (int idx = 0; idx < t->count; idx++) {
		FAILBAIL(send((char *)t->tanks[idx], 8));

		if (1 != (ret = recv_all((char *)&valve_pos, 1))) {
			if (0 == ret) {
				return ERR_END_OF_FILE;
			} else {
				return ret;
			}
		}

		switch(valve_pos) {
			case OPEN_VALVE:
				FAILBAIL(open_valve(t->tanks[idx]));
				break;
			case CLOSE_VALVE:
				FAILBAIL(close_valve(t->tanks[idx]));
				break;
			case NO_CHANGE:
				break;
			case SET_IN_SERVICE:
				FAILBAIL(set_in_service(t->tanks[idx]));
				break;
			case SET_OUT_OF_SERVICE:
				FAILBAIL(set_out_of_service(t->tanks[idx]));
				break;
			case SET_END_OF_LIFE:
				FAILBAIL(set_end_of_life(t->tanks[idx]));
				break;
			default:
				return ERR_INVALID_VALVE_POS;
		}
	}

	return SUCCESS;
}
