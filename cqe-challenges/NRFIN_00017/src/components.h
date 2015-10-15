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

#ifndef COMPONENTS_H
#define COMPONENTS_H 1

typedef enum {
	INCANDESCENT_M5_100BULB = 5,
	LED_C6_150BULB = 6,
	INCANDESCENT_C7_25BULB = 7,
	INCANDESCENT_C9_25BULB = 9,
} LIGHT_STRING_MODELS_T;

typedef enum {
	THREE_WAY = 3,
	SIX_WAY = 6,
	EIGHT_WAY = 8,
} SPLITTER_MODELS_T;

typedef enum {
	FIFTEEN_AMP = 15,
	TWENTY_AMP = 20,
} CIRCUIT_MODELS_T;

typedef enum {
	ONE_HUNDRED_AMP_EIGHT_SPACE = 10008,
	ONE_HUNDRED_AMP_SIXTEEN_SPACE = 10016,
	ONE_HUNDRED_AMP_TWENTY_SPACE = 10020,
	ONE_HUNDRED_FIFTY_AMP_TWENTY_SPACE = 15020,
	ONE_HUNDRED_FIFTY_AMP_TWENTY_FOUR_SPACE = 15024,
	ONE_HUNDRED_FIFTY_AMP_THIRTY_SPACE = 15030,
	TWO_HUNDRED_AMP_TWENTY_SPACE = 20020,
	TWO_HUNDRED_AMP_THIRTY_SPACE = 20030,
	TWO_HUNDRED_AMP_FOURTY_SPACE = 20040,
	TWO_HUNDRED_AMP_FOURTY_TWO_SPACE = 20042,
	FOUR_HUNDRED_AMP_TWENTY_SPACE = 40020,
	FOUR_HUNDRED_AMP_THIRTY_SPACE = 40030,
	FOUR_HUNDRED_AMP_FOURTY_SPACE = 40040,
	FOUR_HUNDRED_AMP_FOURTY_TWO_SPACE = 40042,
} LOAD_CENTER_MODELS_T;

// would prefer NO_LOAD to be 0, but had to change order to
// to help trigger vuln code path due to array out of bounds reads
// reading a 0 for LOAD_TYPE.
typedef enum {
	SPLITTER = 0,
	LIGHT_STRING = 1,
	NO_LOAD = 2,
} LOAD_TYPE_T;

typedef struct receptacle_t {
	uint32_t id;			// >= 1
	LOAD_TYPE_T load_type;
	void *load;				// ptr to a load (n_way_splitter_t or light_string_t)
	uint8_t amp_rating;
} receptacle_t;

typedef struct outlet_t {
	uint32_t id;
	receptacle_t r1;
	receptacle_t r2;
	uint8_t amp_rating;
} outlet_t;

typedef struct n_way_splitter_t {
	uint32_t id;
	uint8_t total_amp_rating;
	uint8_t receptacle_amp_rating;
	uint8_t receptacle_count;
	receptacle_t receptacles[8];
} n_way_splitter_t;

typedef struct light_string_t {
	uint32_t id;
	LIGHT_STRING_MODELS_T model_id; // refer to description of light string
	float	total_wattage;
	receptacle_t receptacle;
} light_string_t;

typedef struct breaker_t {
	uint32_t id;			// 0 <= id < breakers_installed_cnt
	uint8_t amp_rating;
	list_t *outlets;		// ptr to a list of outlets
} breaker_t;

typedef struct load_center_t {
	uint8_t breaker_spaces;
	uint8_t breakers_installed_cnt;
	uint32_t amp_rating;
	breaker_t breakers[0];	// var len array: breakers[breaker_spaces]
} load_center_t;

float get_max_amps_of_light_string();
load_center_t *get_new_load_center_by_model_id(LOAD_CENTER_MODELS_T model_id);
int8_t get_new_breaker_by_model_id(CIRCUIT_MODELS_T model_id, breaker_t *breaker_space, uint8_t breaker_space_idx);
outlet_t *get_new_outlet_by_model_id(CIRCUIT_MODELS_T model_id);
n_way_splitter_t *get_new_n_way_splitter_by_model_id(SPLITTER_MODELS_T model_id);
light_string_t *get_new_light_string_by_model_id(LIGHT_STRING_MODELS_T model_id);


#endif /* MODELS_H */