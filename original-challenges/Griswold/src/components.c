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
#define ALLOC(sz,p) if (SUCCESS != allocate(sz, 0, (void **)p)) {_terminate(ERRNO_ALLOC);}

#define FIRST_RECEPTACLE_ID 1
#define FIRST_LIGHT_STRING_ID 1
#define FIRST_N_WAY_SPLITTER_ID 1
#define FIRST_OUTLET_ID 1
#define MAX_RESIDENTIAL_LIGHT_STRING_WIRE_WATTAGE 210.0
#define RESIDENTIAL_LINE_VOLTAGE 120.0

static uint32_t next_receptacle_id = FIRST_RECEPTACLE_ID;
static uint32_t next_light_string_id = FIRST_LIGHT_STRING_ID;
static uint32_t next_n_way_splitter_id = FIRST_N_WAY_SPLITTER_ID;
static uint32_t next_outlet_id = FIRST_OUTLET_ID;

/*
 * Allocate space for a new load center struct and its breaker spaces.
 * Assign initial values.
 *
 * Returns:
 *  Success: VA of new load_center_t
 *  Failure: terminate with code ERRNO_ALLOC
 */
static load_center_t *create_load_center(uint32_t amp_rating, uint8_t breaker_spaces) {
	load_center_t *load_center = NULL;
	ALLOC(sizeof(load_center_t) + breaker_spaces * sizeof(breaker_t), &load_center);
	load_center->breaker_spaces = breaker_spaces;
	load_center->breakers_installed_cnt = 0;
	load_center->amp_rating = amp_rating;
	return load_center;
}

/*
 * Initialize a breaker in a breaker space.
 */
static void create_breaker(uint8_t amp_rating, breaker_t *breaker_space, uint8_t breaker_space_idx) {
	breaker_space->id = breaker_space_idx;
	breaker_space->amp_rating = amp_rating;
	breaker_space->outlets = list_create_dup();
	if (breaker_space->outlets == NULL) {_terminate(ERRNO_ALLOC);}
}

/*
 * Assign initial values for a receptacle.
 */
static void create_receptacle(uint8_t amp_rating, receptacle_t *receptacle) {
	receptacle->id = next_receptacle_id++;
	receptacle->load_type = NO_LOAD;
	receptacle->load = (void *)NULL;
	receptacle->amp_rating = amp_rating;
}

/*
 * Allocate space for a new outlet struct and initialize the receptacles.
 * Assign initial values.
 *
 * Returns:
 *  Success: VA of new outlet_t
 *  Failure: terminate with code ERRNO_ALLOC
 */
static outlet_t *create_outlet(uint8_t amp_rating) {
	outlet_t *outlet = NULL;
	ALLOC(sizeof(outlet_t), &outlet);
	outlet->id = next_outlet_id++;
	create_receptacle(amp_rating, &(outlet->r1));
	create_receptacle(amp_rating, &(outlet->r2));
	outlet->amp_rating = amp_rating;
	return outlet;
}

/*
 * Allocate space for a new n-way splitter struct and initialize the receptacles.
 * Assign initial values.
 *
 * Returns:
 *  Success: VA of new n_way_splitter_t
 *  Failure: terminate with code ERRNO_ALLOC
 */
static n_way_splitter_t *create_n_way_splitter(uint8_t receptacle_count) {
	n_way_splitter_t *splitter = NULL;
	ALLOC(sizeof(n_way_splitter_t), &splitter);
	splitter->id = next_n_way_splitter_id++;
	splitter->total_amp_rating = 15;
	splitter->receptacle_amp_rating = 15;
	splitter->receptacle_count = receptacle_count;
	for (int r_idx = 0; r_idx < receptacle_count; r_idx++) {
		create_receptacle(15, &(splitter->receptacles[r_idx]));
	}
	return splitter;
}

/*
 * Allocate space for a new light string struct and initialize its receptacle.
 * Assign initial values.
 *
 * Returns:
 *  Success: VA of new light_string_t
 *  Failure: terminate with code ERRNO_ALLOC
 */
static light_string_t *create_light_string(LIGHT_STRING_MODELS_T model_id, float watts) {
	light_string_t *l_string = NULL;
	ALLOC(sizeof(light_string_t), &l_string);
	l_string->id = next_light_string_id++;
	l_string->model_id = model_id;
	l_string->total_wattage = watts;
	create_receptacle(15, &(l_string->receptacle));
	return l_string;
}

/*
 * Calculate how many amps a light string can safely handle.
 *
 * Returns:
 *  Number of amps.
 */
float get_max_amps_of_light_string() {
	return (float)MAX_RESIDENTIAL_LIGHT_STRING_WIRE_WATTAGE / (float)RESIDENTIAL_LINE_VOLTAGE;
}

/*
 * Return a newly allocated and initialized load center matching model_id.
 *
 * Returns:
 *  Success: VA of new load_center_t
 *  Failure: NULL
 */
load_center_t *get_new_load_center_by_model_id(LOAD_CENTER_MODELS_T model_id) {
	load_center_t *load_center = NULL;
	switch(model_id) {
		case ONE_HUNDRED_AMP_EIGHT_SPACE:
			load_center = create_load_center(100, 8);
			break;
		case ONE_HUNDRED_AMP_SIXTEEN_SPACE:
			load_center = create_load_center(100, 16);
			break;
		case ONE_HUNDRED_AMP_TWENTY_SPACE:
			load_center = create_load_center(100, 20);
			break;
		case ONE_HUNDRED_FIFTY_AMP_TWENTY_SPACE:
			load_center = create_load_center(150, 20);
			break;
		case ONE_HUNDRED_FIFTY_AMP_TWENTY_FOUR_SPACE:
			load_center = create_load_center(150, 24);
			break;
		case ONE_HUNDRED_FIFTY_AMP_THIRTY_SPACE:
			load_center = create_load_center(150, 30);
			break;
		case TWO_HUNDRED_AMP_TWENTY_SPACE:
			load_center = create_load_center(200, 20);
			break;
		case TWO_HUNDRED_AMP_THIRTY_SPACE:
			load_center = create_load_center(200, 30);
			break;
		case TWO_HUNDRED_AMP_FOURTY_SPACE:
			load_center = create_load_center(200, 40);
			break;
		case TWO_HUNDRED_AMP_FOURTY_TWO_SPACE:
			load_center = create_load_center(200, 42);
			break;
		case FOUR_HUNDRED_AMP_TWENTY_SPACE:
			load_center = create_load_center(400, 20);
			break;
		case FOUR_HUNDRED_AMP_THIRTY_SPACE:
			load_center = create_load_center(400, 30);
			break;
		case FOUR_HUNDRED_AMP_FOURTY_SPACE:
			load_center = create_load_center(400, 40);
			break;
		case FOUR_HUNDRED_AMP_FOURTY_TWO_SPACE:
			load_center = create_load_center(400, 42);
			break;
		default:
			// invalid model_id
			return NULL;
	}
	return load_center;
}

/*
 * Initialize a breaker matching model_id in the breaker_space.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: -1
 */
int8_t get_new_breaker_by_model_id(CIRCUIT_MODELS_T model_id, breaker_t *breaker_space, uint8_t breaker_space_idx) {
	int8_t res = SUCCESS;
	switch(model_id) {
		case FIFTEEN_AMP:
			create_breaker(15, breaker_space, breaker_space_idx);
			break;
		case TWENTY_AMP:
			create_breaker(20, breaker_space, breaker_space_idx);
			break;
		default:
			// invalid model_id
			res = -1;
	}
	return res;
}

/*
 * Return a newly allocated and initialized outlet matching model_id.
 *
 * Returns:
 *  Success: VA of new outlet_t
 *  Failure: NULL
 */
outlet_t *get_new_outlet_by_model_id(CIRCUIT_MODELS_T model_id) {
	outlet_t *outlet = NULL;
	switch(model_id) {
		case FIFTEEN_AMP:
			outlet = create_outlet(15);
			break;
		case TWENTY_AMP:
			outlet = create_outlet(20);
			break;
		default:
			// invalid model_id
			return NULL;
	}
	return outlet;
}

/*
 * Return a newly allocated and initialized n-way splitter matching model_id.
 *
 * Returns:
 *  Success: VA of new n_way_splitter_t
 *  Failure: NULL
 */
n_way_splitter_t *get_new_n_way_splitter_by_model_id(SPLITTER_MODELS_T model_id) {
	n_way_splitter_t *splitter = NULL;
	switch(model_id) {
		case THREE_WAY:
			splitter = create_n_way_splitter(3);
			break;
		case SIX_WAY:
			splitter = create_n_way_splitter(6);
			break;
		case EIGHT_WAY:
			splitter = create_n_way_splitter(8);
			break;
		default:
			// invalid model_id
			return NULL;
	}
	return splitter;
}

/*
 * Return a newly allocated and initialized light string matching model_id.
 *
 * Returns:
 *  Success: VA of new light_string_t
 *  Failure: NULL
 */
light_string_t *get_new_light_string_by_model_id(LIGHT_STRING_MODELS_T model_id) {
	light_string_t *light_string = NULL;
	switch(model_id) {
		case INCANDESCENT_M5_100BULB:
			light_string = create_light_string(model_id, 40.8);
			break;
		case LED_C6_150BULB:
			light_string = create_light_string(model_id, 12.0);
			break;
		case INCANDESCENT_C7_25BULB:
			light_string = create_light_string(model_id, 165.6);
			break;
		case INCANDESCENT_C9_25BULB:
			light_string = create_light_string(model_id, 120.0);
			break;
		default:
			// invalid model_id
			return NULL;
	}
	return light_string;
}
