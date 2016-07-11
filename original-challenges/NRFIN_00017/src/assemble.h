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

#ifndef ASSEMBLE_H
#define ASSEMBLE_H 1

/*
 * When an object is created that has receptacles, this struct is used to
 * store the object's id and the id's for the receptacles in that object.
 * A light string has 1 receptacle, an outlet has 2, and a n-way splitter
 * can have 3, 6, or 8 receptacles.
 */
typedef struct assemble_result_t {
	uint32_t object_id;
	uint32_t receptacle_id[8];
	uint8_t  receptacle_ids_assigned_cnt;
} assemble_result_t;

enum {
	ERR_E_MODEL_EXISTS = -41,
	ERR_E_MODEL_NOT_EXISTS = -42,
	ERR_BREAKER_SPACES_FULL = -43,
	ERR_INVALID_MODEL_ID = -44,
	ERR_INVALID_BREAKER_ID = -45,
	ERR_INVALID_RECEPTACLE_ID = -46,
	ERR_INVALID_OUTLET_ID = -47,
	ERR_INVALID_SPLITTER_ID = -48,
	ERR_INVALID_LIGHT_STRING_ID = -49,
	ERR_RECEPTACLE_FULL = -50,
	ERR_OUTLET_AMPS_EXCEED_BREAKER_AMPS = -51,
};

// Examine
int32_t get_count_outlets_on_breaker(uint32_t breaker_id);
int8_t get_amp_rating_of_breaker(uint32_t breaker_id);
float get_total_amp_load_on_breaker_by_breaker_id(uint32_t breaker_id);

int8_t get_amp_rating_of_outlet(uint32_t outlet_id);
float get_total_amp_load_on_outlet_by_outlet_id(uint32_t outlet_id);
float get_max_receptacle_amp_load_on_outlet_by_outlet_id(uint32_t outlet_id);

int8_t get_amp_rating_of_splitter(uint32_t splitter_id);
float get_total_amp_load_on_splitter_by_splitter_id(uint32_t splitter_id);
float get_max_receptacle_amp_load_on_splitter_by_splitter_id(uint32_t splitter_id);

float get_amp_rating_of_light_string(uint32_t light_string_id);
float get_total_amp_load_on_light_string_by_light_string_id(uint32_t light_string_id);

int8_t get_amp_rating_of_receptacle(uint32_t receptacle_id);
float get_total_amp_load_on_receptacle_by_receptacle_id(uint32_t receptacle_id);

int8_t get_number_of_breakers_installed_in_load_center();
int8_t get_total_breaker_space_count();
int32_t get_amp_rating_of_load_center();
float get_total_amp_load_on_load_center();


// Assembly
int8_t init_electric_model(LOAD_CENTER_MODELS_T model_id);
int8_t add_breaker_to_load_center(CIRCUIT_MODELS_T model_id, assemble_result_t *result);
int8_t add_outlet_to_breaker(CIRCUIT_MODELS_T outlet_model_id, uint32_t breaker_id, assemble_result_t *result);
int8_t add_n_way_splitter_to_receptacle(SPLITTER_MODELS_T splitter_model_id, uint32_t receptacle_id, assemble_result_t *result);
int8_t add_light_string_to_receptacle(LIGHT_STRING_MODELS_T light_string_model_id, uint32_t receptacle_id, assemble_result_t *result);

#endif