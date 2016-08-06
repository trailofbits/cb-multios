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
#include "components.h"
#include "assemble.h"
#include "examine.h"

/*
 * Check the load center to see if it has too much amp load.
 *
 * Too much amp load (total amp load > 100% amp rating).
 *
 * Returns:
 *  Too much amp load: TRUE
 *  Not too much amp load: FALSE
 */
static uint8_t is_too_much_amp_load_on_load_center() {
	if (get_total_amp_load_on_load_center() > get_amp_rating_of_load_center()) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * Check the breaker to see if it has too much amp load.
 *
 * Too much amp load (total amp load > 80% amp rating).
 *
 * Returns:
 *  Too much amp load: TRUE
 *  Not too much amp load: FALSE
 */
static uint8_t is_too_much_amp_load_on_breaker(uint32_t breaker_id) {
	if (get_total_amp_load_on_breaker_by_breaker_id(breaker_id) > (0.8 * (float)get_amp_rating_of_breaker(breaker_id))) {
		return TRUE;
	} else {
		return FALSE;
	}
} 

/*
 * Check the breaker to see if it has too many outlets on its circuit.
 *
 *  Too many outlets on its circuit (>8 on 15 amp, >10 on 20 amp).
 *
 * Returns:
 *  Too many outlets: TRUE
 *  Not to many outlets: FALSE
 */
static uint8_t is_too_many_outlets_on_breaker(uint32_t breaker_id) {
	uint32_t outlet_count = get_count_outlets_on_breaker(breaker_id);
	uint8_t res = FALSE;
	switch(get_amp_rating_of_breaker(breaker_id)) {
		case FIFTEEN_AMP:
			if (outlet_count > 8)
				res = TRUE;
			break;
		case TWENTY_AMP:
			if (outlet_count > 10)
				res = TRUE;
			break;
		default:
			res = FALSE;
	}
	return res;
}

/*
 * Check the outlet to see if it has too much amp load.
 *
 * Too much amp load (total outlet amp load > 80% amp rating).
 *
 * Returns:
 *  Too much amp load: TRUE
 *  Not too much amp load: FALSE
 */
static uint8_t is_too_much_amp_load_on_outlet(outlet_id) {
	if (get_total_amp_load_on_outlet_by_outlet_id(outlet_id) > (0.8 * (float)get_amp_rating_of_outlet(outlet_id))) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * Check the outlet to see if it has too much amp load on either receptacle.
 *
 * Too much amp load (max receptacle amp load > 80% amp rating).
 *
 * Returns:
 *  Too much amp load: TRUE
 *  Not too much amp load: FALSE
 */
static uint8_t is_too_much_amp_load_on_one_outlet_receptacle(outlet_id) {
	if (get_max_receptacle_amp_load_on_outlet_by_outlet_id(outlet_id) > (0.8 * (float)get_amp_rating_of_outlet(outlet_id))) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * Check the splitter to see if it has too much amp load.
 *
 * Too much amp load (total splitter amp load > 80% amp rating).
 *
 * Returns:
 *  Too much amp load: TRUE
 *  Not too much amp load: FALSE
 */
static uint8_t is_too_much_amp_load_on_splitter(splitter_id) {
	if (get_total_amp_load_on_splitter_by_splitter_id(splitter_id) > (0.8 * (float)get_amp_rating_of_splitter(splitter_id))) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * Check the splitter to see if it has too much amp load on any one receptacle.
 *
 * Too much amp load (max receptacle amp load > 80% amp rating).
 *
 * Returns:
 *  Too much amp load: TRUE
 *  Not too much amp load: FALSE
 */
 static uint8_t is_too_much_amp_load_on_one_splitter_receptacle(splitter_id) {
	if (get_max_receptacle_amp_load_on_splitter_by_splitter_id(splitter_id) > (0.8 * (float)get_amp_rating_of_splitter(splitter_id))) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * Check the light string to see if it has too much amp load.
 *
 * Too much amp load (>(210W/120V) on that string + all downstream loads).
 *
 * Returns:
 *  Too much amp load: TRUE
 *  Not too much amp load: FALSE
 */
static uint8_t is_too_much_amp_load_on_light_string(light_string_id) {
	if (get_total_amp_load_on_light_string_by_light_string_id(light_string_id) > get_amp_rating_of_light_string(light_string_id)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * Check the receptacle to see if it has too much amp load.
 *
 * Too much amp load (amp load > 80% amp rating).
 *
 * Returns:
 *  Too much amp load: TRUE
 *  Not too much amp load: FALSE
 */
static uint8_t is_too_much_amp_load_on_receptacle(receptacle_id) {
	if (get_total_amp_load_on_receptacle_by_receptacle_id(receptacle_id) > (float)get_amp_rating_of_receptacle(receptacle_id)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * Check the electrical panel to see if it is overloaded.
 *
 * Overloaded means:
 *   1. Too much amp load (total amp load > 100% amp rating).
 *
 * Returns:
 *  Overloaded: TRUE
 *  Not overloaded: FALSE
 */
uint8_t is_electrical_panel_overloaded() {
	return is_too_much_amp_load_on_load_center();
}

/*
 * Check the breaker to see if it is overloaded.
 *
 * Overloaded means
 *  1. Too many outlets on its circuit (>8 on 15 amp, >10 on 20 amp).
 *  2. Too much amp load (total amp load > 80% amp rating).
 *
 * Returns:
 *  Overloaded: TRUE
 *  Not overloaded: FALSE
 */
uint8_t is_breaker_overloaded(uint32_t breaker_id) {
	if ((TRUE == is_too_many_outlets_on_breaker(breaker_id)) || 
		(TRUE == is_too_much_amp_load_on_breaker(breaker_id))) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * Check the outlet to see if it is overloaded.
 *
 * Overloaded means
 *  1. Too much total load (>80% amp rating)
 *  2. Too much load on one receptacle (>80% amp rating)
 *
 * Returns:
 *  Overloaded: TRUE
 *  Not overloaded: FALSE
 */
uint8_t is_outlet_overloaded(uint32_t outlet_id) {
	if ((TRUE == is_too_much_amp_load_on_outlet(outlet_id)) ||
		(TRUE == is_too_much_amp_load_on_one_outlet_receptacle(outlet_id))) {
		return TRUE;
	} else {
		return FALSE;
	}
} 

/*
 * Check the splitter to see if it is overloaded.
 *
 * Overloaded means
 *  1. Too much total load (>80% amp rating)
 *  2. Too much load on one receptacle (>80% amp rating)
 *
 * Returns:
 *  Overloaded: TRUE
 *  Not overloaded: FALSE
 */
uint8_t is_splitter_overloaded(uint32_t splitter_id) {
	if ((TRUE == is_too_much_amp_load_on_splitter(splitter_id)) ||
		(TRUE == is_too_much_amp_load_on_one_splitter_receptacle(splitter_id))) {
		return TRUE;
	} else {
		return FALSE;
	}
} 

/*
 * Check the light string to see if it is overloaded.
 *
 * Overloaded means
 *  1. Too much total load (>210W on that string + all downstream loads)
 *
 * Returns:
 *  Overloaded: TRUE
 *  Not overloaded: FALSE
 */
uint8_t is_light_string_overloaded(uint32_t light_string_id) {
	if (TRUE == is_too_much_amp_load_on_light_string(light_string_id)) {
		return TRUE;
	} else {
		return FALSE;
	}
} 

/*
 * Check the receptacle to see if it is overloaded.
 *
 * Overloaded means
 *  1. Too much total load (>80% amp rating)
 *
 * Returns:
 *  Overloaded: TRUE
 *  Not overloaded: FALSE
 */
uint8_t is_receptacle_overloaded(uint32_t receptacle_id) {
	if (TRUE == is_too_much_amp_load_on_receptacle(receptacle_id)) {
		return TRUE;
	} else {
		return FALSE;
	}
} 

