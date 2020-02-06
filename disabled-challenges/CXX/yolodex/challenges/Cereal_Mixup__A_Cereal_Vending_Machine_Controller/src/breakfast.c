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

#include "libcgc.h"
#include "cgc_stdint.h"
#include "cgc_libc.h"
#include "cgc_send.h"

#include "cgc_breakfast.h"
#include "cgc_actuators.h"
#include "cgc_breakfast_objects.h"


const char cgc_PLACE_BOWL_MSG[4] 		= {'\x11', '\xd1', '\xe0', '\xa4'};
const char cgc_ADD_CEREAL_MSG[4] 		= {'\xec', '\xdf', '\x01', '\xbb'};
const char cgc_ADD_LIQUID_MSG[4] 		= {'\xba', '\xfd', '\xff', '\x03'};
const char cgc_ADD_TOPPING_MSG[4] 		= {'\xca', '\x0d', '\xcc', '\xf1'};
const char cgc_BREAKFAST_READY_MSG[4] 	= {'\x3a', '\xcc', '\x00', '\xe8'};

// need room for one of each subtype per category
//  index into these arrays using the enum value
Liquids *cgc_liquids_ptrs[L_STI_COUNT] 		= {0};
Cereals *cgc_cereals_ptrs[C_STI_COUNT] 		= {0};
Toppings *cgc_toppings_ptrs[T_STI_COUNT] 	= {0};

/**
 * Reset the object pointer buffers and delete the objects
 */
void cgc_reset_buffers(void) {
	for (l_sti_t idx = 0; idx < L_STI_COUNT; idx++) {
		if (cgc_liquids_ptrs[idx] != NULL) {
			cgc_liquids_ptrs[idx]->destroy(cgc_liquids_ptrs[idx]);
			cgc_liquids_ptrs[idx] = NULL;
		}
	}
	for (c_sti_t idx = 0; idx < C_STI_COUNT; idx++) {
		if (cgc_cereals_ptrs[idx] != NULL) {
			cgc_cereals_ptrs[idx]->destroy(cgc_cereals_ptrs[idx]);
			cgc_cereals_ptrs[idx] = NULL;
		}
	}
	for (t_sti_t idx = 0; idx < T_STI_COUNT; idx++) {
		if (cgc_toppings_ptrs[idx] != NULL) {
			cgc_toppings_ptrs[idx]->destroy(cgc_toppings_ptrs[idx]);
			cgc_toppings_ptrs[idx] = NULL;
		}
	}
}

/**
 * Determine the number of units of liquids that were requested
 *
 * @return Number of units of liquids
 */
unsigned int cgc_units_of_liquids(void) {
	unsigned int cnt = 0;
	for (int i = 0; i < L_STI_COUNT; i++) {
		if (NULL != cgc_liquids_ptrs[i])
			cnt++;
	}
	return cnt;
}

/**
 * Determine the number of units of cereals that were requested
 *
 * @return Number of units of cereals
 */
unsigned int cgc_units_of_cereals(void) {
	unsigned int cnt = 0;
	for (int i = 0; i < C_STI_COUNT; i++) {
		if (NULL != cgc_cereals_ptrs[i])
			cnt++;
	}
	return cnt;
}

/**
 * Determine the number of units of toppings that were requested
 *
 * @return Number of units of toppings
 */
unsigned int cgc_units_of_toppings(void) {
	unsigned int cnt = 0;
	for (int i = 0; i < T_STI_COUNT; i++) {
		if (NULL != cgc_toppings_ptrs[i])
			cnt++;
	}
	return cnt;
}

/**
 * Dispense a liquid into the bowl
 *
 * @param subTypeID 	ID of liquid to dispense
 */
void cgc_dispense_liquid(l_sti_t subTypeID) {
	switch(subTypeID) {
		case DAIRY_MILK:
			cgc_dispense_dairy_milk();
			break;
		case DAIRY_CREAM:
			cgc_dispense_dairy_cream();
			break;
		case WATER:
			cgc_dispense_water();
			break;
		case SOY_MILK:
			cgc_dispense_soy_milk();
			break;
		case ALMOND_MILK:
			cgc_dispense_almond_milk();
			break;
		default:
			return;
	}
}

/**
 * Dispense a cereal into the bowl
 *
 * @param subTypeID 	ID of cereal to dispense
 */
void cgc_dispense_cereal(c_sti_t subTypeID) {
	switch(subTypeID) {
		case SUGAR_LOOPS:
			cgc_dispense_sugar_loops();
			break;
		case MAIZE_FLAKES:
			cgc_dispense_maize_flakes();
			break;
		case MARSHMALLOW_FIGURINES:
			cgc_dispense_marshmallow_figuringes();
			break;
		case CHOCOLATE_RICE_PELLETS:
			cgc_dispense_chocolate_rice_pellets();
			break;
		case OHHS_OF_OATS:
			cgc_dispense_oohs_of_oats();
			break;
		case CRUNCHY_PUFFS:
			cgc_dispense_crunchy_puffs();
			break;
		case FRUITZ_N_NUTZ:
			cgc_dispense_frutiz_n_nuts();
			break;
		default:
			return;
	}
}

/**
 * Dispense a topping into the bowl
 *
 * @param subTypeID 	ID of topping to dispense
 */
void cgc_dispense_toppings(t_sti_t subTypeID) {
	switch(subTypeID) {
		case CHOCOLATE_DROPS:
			cgc_dispense_chocolate_drops();
			break;
		case BLUEBERRIES:
			cgc_dispense_blueberries();
			break;
		case BERRY_MEDLEY:
			cgc_dispense_berry_medley();
			break;
		case SUGAR_CUBE:
			cgc_dispense_sugar_cube();
			break;
		case STRAWBERRIES:
			cgc_dispense_strawberries();
			break;
		default:
			return;
	}
}

/**
 * Manage operation of the breakfast dispensing machine
 */
void cgc_dispense_breakfast() {

	cgc_init_dispenser();
    cgc_send(cgc_PLACE_BOWL_MSG, sizeof(cgc_PLACE_BOWL_MSG));
	// dispense a bowl
    cgc_dispense_bowl();

	if (0 != cgc_units_of_cereals()) {
		cgc_send(cgc_ADD_CEREAL_MSG, sizeof(cgc_ADD_CEREAL_MSG));
		// dispense cereals
		for (c_sti_t i = 0; i < C_STI_COUNT; i++) {
			if (NULL != cgc_cereals_ptrs[i])
				cgc_dispense_cereal(i);
		}
	}

	if (0 != cgc_units_of_liquids()) {
		cgc_send(cgc_ADD_LIQUID_MSG, sizeof(cgc_ADD_LIQUID_MSG));
		// dispense liquids
		for (l_sti_t i = 0; i < L_STI_COUNT; i++) {
			if (NULL != cgc_liquids_ptrs[i])
				cgc_dispense_liquid(i);
		}
	}

	if (0 != cgc_units_of_toppings()) {
		cgc_send(cgc_ADD_TOPPING_MSG, sizeof(cgc_ADD_TOPPING_MSG));
		// dispense toppings
		for (t_sti_t i = 0; i < T_STI_COUNT; i++) {
			if (NULL != cgc_toppings_ptrs[i])
				cgc_dispense_toppings(i);
		}
	}

	cgc_send(cgc_BREAKFAST_READY_MSG, sizeof(cgc_BREAKFAST_READY_MSG));
	cgc_completion_buzzer();
}

cgc_ssize_t cgc_process_plain_input(Stream *input_stream) {
// Plain content, send SVU as UINT32 and STI as UCHAR

	// scan through Stream->content and extract the data
	char *cur = input_stream->content;
	char *end = cur + input_stream->size;
	unsigned char subTypeID = 0;
	svu_t svu;

	Liquids *p_liquids;
	Cereals *p_cereals;
	Toppings *p_toppings;

	int ret = 0;
	cgc_reset_buffers();

	while (cur < end) {
		svu = *(svu_t *)cur;
		cur += sizeof(unsigned int);
		switch (svu) {
			// set the TYPE_ptrs[x] to anything not NULL.
			case LIQUID:
				subTypeID = *(unsigned char *)cur;
				cur += sizeof(unsigned char);

				if (subTypeID >= L_STI_COUNT) return -1;
				if (NULL != cgc_liquids_ptrs[subTypeID]) return -1;

				p_liquids = cgc_constructor_liquids();
				ret = p_liquids->set_data(p_liquids, svu, subTypeID);
				if (0 > ret) {
					p_liquids->destroy(p_liquids);
					p_liquids = NULL;
				}
				cgc_liquids_ptrs[subTypeID] = p_liquids;
				break;
			case CEREAL:
				subTypeID = *(unsigned char *)cur;
				cur += sizeof(unsigned char);

				if (subTypeID >= C_STI_COUNT) return -1;
				if (NULL != cgc_cereals_ptrs[subTypeID]) return -1;

				p_cereals = cgc_constructor_cereals();
				ret = p_cereals->set_data(p_cereals, svu, subTypeID);
				if (0 > ret) {
					p_cereals->destroy(p_cereals);
					p_cereals = NULL;
				}
				cgc_cereals_ptrs[subTypeID] = p_cereals;
				break;
			case TOPPINGS:
				subTypeID = *(unsigned char *)cur;
				cur += sizeof(unsigned char);

				if (subTypeID >= T_STI_COUNT) return -1;
				if (NULL != cgc_toppings_ptrs[subTypeID]) return -1;

				p_toppings = cgc_constructor_toppings();
				ret = p_toppings->set_data(p_toppings, svu, subTypeID);
				if (0 > ret) {
					p_toppings->destroy(p_toppings);
					p_toppings = NULL;
				}
				cgc_toppings_ptrs[subTypeID] = p_toppings;
				break;
			default:
				return -1;
		}
	}

	cgc_dispense_breakfast();
	return 0;
}

cgc_ssize_t cgc_process_serialized_input(Stream *input_stream) {
	cgc_ssize_t ret;
	char *cur = input_stream->content;
	char *end = cur + input_stream->size;
	svu_t svu;

	Liquids *p_liquids;
	Cereals *p_cereals;
	Toppings *p_toppings;

	cgc_reset_buffers();

	while (cur < end) {
		svu = *(svu_t *)cur;
		switch (svu) {
			case LIQUID:
				p_liquids = cgc_deserialize_liquids(&cur);
				if (NULL == p_liquids) return -1;
				if (NULL != cgc_liquids_ptrs[p_liquids->subTypeID]) {
					p_liquids->destroy(p_liquids); // no dups
					return -1;
				}

				cgc_liquids_ptrs[p_liquids->subTypeID] = p_liquids;
				break;
			case CEREAL:
				p_cereals = cgc_deserialize_cereals(&cur);
				if (NULL == p_cereals) return -1;
				if (NULL != cgc_cereals_ptrs[p_cereals->subTypeID]) {
					p_cereals->destroy(p_cereals); // no dups
					return -1;
				}

				cgc_cereals_ptrs[p_cereals->subTypeID] = p_cereals;
				break;
			case TOPPINGS:
				p_toppings = cgc_deserialize_toppings(&cur);
				if (NULL == p_toppings) return -1;
				if (NULL != cgc_toppings_ptrs[p_toppings->subTypeID]) {
					p_toppings->destroy(p_toppings); // no dups
					return -1;
				}

				cgc_toppings_ptrs[p_toppings->subTypeID] = p_toppings;
				break;
			/* 
				This CB is simulating a language that has default
				object types available via the inherited libs.

				In that type of language, objects are 
				constructed/initalized/deserialised on demand.
			   	And if they are not assigned to anything, 
			   	they are trashed by garbage collector, if one exists,
			   	or they cause memory leaks.

			   	But, bad things can still happen during that little bit of time ;)
			*/
			default:
#ifndef PATCHED_1
				ret = cgc_check_inherited_types(svu, &cur);
				if (-1 == ret) return -1; // unknown type
#else
				return -1;
#endif
		}
	}

	cgc_dispense_breakfast();
	return 0;
}



