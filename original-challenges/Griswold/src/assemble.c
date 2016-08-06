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

static receptacle_t *search_receptacle_for_receptacle_id(receptacle_t *receptacle, uint32_t receptacle_id);
static receptacle_t *search_light_string_for_receptacle_id(light_string_t *light_string, uint32_t receptacle_id);
static receptacle_t *search_outlet_for_receptacle_id(outlet_t *outlet, uint32_t receptacle_id);
static receptacle_t *search_splitter_for_receptacle_id(n_way_splitter_t *splitter, uint32_t receptacle_id);
static n_way_splitter_t *search_receptacle_for_splitter_id(receptacle_t *r, uint32_t splitter_id);
static n_way_splitter_t *search_light_string_for_splitter_id(light_string_t *ls, uint32_t splitter_id);
static n_way_splitter_t *search_outlet_for_splitter_id(outlet_t *o, uint32_t splitter_id);
static n_way_splitter_t *search_splitter_for_splitter_id(n_way_splitter_t *splitter, uint32_t splitter_id);
static light_string_t *search_receptacle_for_light_string_id(receptacle_t *r, uint32_t light_string_id);
static light_string_t *search_light_string_for_light_string_id(light_string_t *light_string, uint32_t light_string_id);
static light_string_t *search_outlet_for_light_string_id(outlet_t *o, uint32_t light_string_id);
static light_string_t *search_splitter_for_light_string_id(n_way_splitter_t *s, uint32_t light_string_id);
static list_t * get_outlet_list_on_breaker(uint32_t breaker_id);
static float get_total_amp_load_on_light_string_by_light_string_va(light_string_t *light_string);
static float get_total_amp_load_on_splitter_by_splitter_va(n_way_splitter_t *splitter);
static float get_total_amp_load_on_receptacle_by_receptacle_va(receptacle_t *receptacle);
static float get_total_amp_load_on_outlet_by_outlet_va(outlet_t *outlet);



// root of the electrical model is the load center
static load_center_t *e_model = NULL;

/*
 * Calculate the number of amps, given volts and watts.
 *
 * Returns:
 *  amps >= 0.0
 */
static float convert_watts_to_amps(float watts) {
	return (watts / 120.0);
}

/*
 * Check if load center has been created.
 *
 * Returns:
 *  Yes: TRUE
 *  No : FALSE
 */
static uint8_t load_center_is_created() {
	if (NULL == e_model) return FALSE;
	else return TRUE;
}

/*
 * Check if load center breaker spaces are all full (occupied).
 *
 * Returns:
 *  Full: TRUE
 *  Not full: FALSE
 */
static int8_t load_center_breaker_spaces_are_full() {
	if ((TRUE == load_center_is_created()) && 
		(e_model->breaker_spaces == e_model->breakers_installed_cnt)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/*
 * Get type of load on receptacle.
 *
 * Returns:
 *  If not loaded: NO_LOAD
 *  If has splitter: SPLITTER
 *  If has light string: LIGHT_STRING
 */
static LOAD_TYPE_T get_receptacle_load_type(receptacle_t *receptacle) {
	return receptacle->load_type;
}

/*
 * Check if receptacle already has a load in it
 *
 * Returns:
 *  Loaded: TRUE
 *  No loaded: FALSE
 */
static int8_t receptacle_is_loaded(receptacle_t *receptacle) {
	if (NO_LOAD > get_receptacle_load_type(receptacle)) {
		return TRUE;
	} else {
		return FALSE;
	}
}



/*
 * Search recurisvely through the receptacle circuit for receptacle having
 * id of receptacle_id.
 *
 * Returns:
 *  Success: VA of receptacle_t
 *  Failure: NULL
 */
static receptacle_t *search_receptacle_for_receptacle_id(receptacle_t *receptacle, uint32_t receptacle_id) {

	receptacle_t *r = NULL;
	if (receptacle_id == receptacle->id) {
		r = receptacle;
	} else if (SPLITTER == get_receptacle_load_type(receptacle)) {
		r = search_splitter_for_receptacle_id((n_way_splitter_t *)receptacle->load, receptacle_id);
	} else if (LIGHT_STRING == get_receptacle_load_type(receptacle)) {
		r = search_light_string_for_receptacle_id((light_string_t *)receptacle->load, receptacle_id);
	}
	return r;
}

/*
 * Search recursively through the outlet circuit for receptacle having
 * id of receptacle_id.
 *
 * Returns:
 *  Success: VA of receptacle_t
 *  Failure: NULL
 */
static receptacle_t *search_outlet_for_receptacle_id(outlet_t *outlet, uint32_t receptacle_id) {

	receptacle_t *r = NULL;
	r = search_receptacle_for_receptacle_id(&(outlet->r1), receptacle_id);
	if (NULL == r) {
		r = search_receptacle_for_receptacle_id(&(outlet->r2), receptacle_id);
	}
	return r;
}

/*
 * Search recursively through the splitters circuit for receptacle
 * having id of receptacle_id.
 *
 * Returns:
 *  Success: VA of receptacle_t
 *  Failure: NULL
 */
static receptacle_t *search_splitter_for_receptacle_id(n_way_splitter_t *splitter, uint32_t receptacle_id) {

	receptacle_t *r = NULL;
#ifdef PATCHED
	for (uint32_t idx = 0; idx < splitter->receptacle_count; idx++) {
#else
	for (uint32_t idx = 0; idx <= splitter->receptacle_count; idx++) {
#endif
		r = search_receptacle_for_receptacle_id(&(splitter->receptacles[idx]), receptacle_id);
		if (NULL != r) break;
	}
	return r;
}

/*
 * Search recursively through the light string circuit for receptacle
 * having id of receptacle_id.
 *
 * Returns:
 *  Success: VA of receptacle_id
 *  Failure: NULL
 */
static receptacle_t *search_light_string_for_receptacle_id(light_string_t *light_string, uint32_t receptacle_id) {
	return search_receptacle_for_receptacle_id(&(light_string->receptacle), receptacle_id);
}



/*
 * Search recursively through the receptacle circuit for splitter
 * having id of splitter_id.
 *
 * Returns:
 *  Success: VA of n_way_splitter_t
 *  Failure: NULL
 */
static n_way_splitter_t *search_receptacle_for_splitter_id(receptacle_t *r, uint32_t splitter_id) {
	n_way_splitter_t *s = NULL;

	if (SPLITTER == get_receptacle_load_type(r)) {
		s = search_splitter_for_splitter_id((n_way_splitter_t *)r->load, splitter_id);
	} else if (LIGHT_STRING == get_receptacle_load_type(r)) {
		s = search_light_string_for_splitter_id((light_string_t *)r->load, splitter_id);
	}

	return s;
}

/*
 * Search recursively through the light string circuit for splitter
 * having id of splitter_id.
 *
 * Returns:
 *  Success: VA of n_way_splitter_t
 *  Failure: NULL
 */
static n_way_splitter_t *search_light_string_for_splitter_id(light_string_t *ls, uint32_t splitter_id) {
	return search_receptacle_for_splitter_id(&(ls->receptacle), splitter_id);
}

/*
 * Search recursively through the outlet circuit for splitter
 * having id of splitter_id.
 *
 * Returns:
 *  Success: VA of n_way_splitter_t
 *  Failure: NULL
 */
static n_way_splitter_t *search_outlet_for_splitter_id(outlet_t *o, uint32_t splitter_id) {
	n_way_splitter_t *s = NULL;
	s = search_receptacle_for_splitter_id(&(o->r1), splitter_id);
	if (NULL == s) {
		s = search_receptacle_for_splitter_id(&(o->r2), splitter_id);
	}

	return s;
}

/*
 * Search recursively through the splitter circuit for splitter
 * having id of splitter_id.
 *
 * Returns:
 *  Success: VA of n_way_splitter_t
 *  Failure: NULL
 */
static n_way_splitter_t *search_splitter_for_splitter_id(n_way_splitter_t *splitter, uint32_t splitter_id) {
	n_way_splitter_t *s = NULL;

	if (splitter_id == splitter->id) {
		s = splitter;
	} else {
		for (uint8_t idx = 0; idx < splitter->receptacle_count; idx++) {
			s = search_receptacle_for_splitter_id(&(splitter->receptacles[idx]), splitter_id);
			if (NULL != s) break;
		}
	}
	return s;
}



/*
 * Search recursively through the receptacle circuit for light string
 * having id of light_string_id.
 *
 * Returns:
 *  Success: VA of light_string_t
 *  Failure: NULL
 */
static light_string_t *search_receptacle_for_light_string_id(receptacle_t *r, uint32_t light_string_id) {
	light_string_t *ls = NULL;

	if (SPLITTER == get_receptacle_load_type(r)) {
		ls = search_splitter_for_light_string_id((n_way_splitter_t *)r->load, light_string_id);
	} else if (LIGHT_STRING == get_receptacle_load_type(r)) {
		ls = search_light_string_for_light_string_id((light_string_t *)r->load, light_string_id);
	}

	return ls;
}

/*
 * Search recursively through the light string circuit for light string
 * having id of light_string_id.
 *
 * Returns:
 *  Success: VA of light_string_t
 *  Failure: NULL
 */
static light_string_t *search_light_string_for_light_string_id(light_string_t *light_string, uint32_t light_string_id) {
	light_string_t *ls = NULL;

	if (light_string_id == light_string->id) {
		ls = light_string;
	} else {
		ls = search_receptacle_for_light_string_id(&(light_string->receptacle), light_string_id);
	}
	return ls;
}

/*
 * Search recursively through the outlet circuit for light string
 * having id of light_string_id.
 *
 * Returns:
 *  Success: VA of light_string_t
 *  Failure: NULL
 */
static light_string_t *search_outlet_for_light_string_id(outlet_t *o, uint32_t light_string_id) {
	light_string_t *ls = NULL;
	ls = search_receptacle_for_light_string_id(&(o->r1), light_string_id);
	if (NULL == ls) {
		ls = search_receptacle_for_light_string_id(&(o->r2), light_string_id);
	}

	return ls;
}

/*
 * Search recursively through the splitter circuit for light string
 * having id of light_string_id.
 *
 * Returns:
 *  Success: VA of light_string_t
 *  Failure: NULL
 */
static light_string_t *search_splitter_for_light_string_id(n_way_splitter_t *s, uint32_t light_string_id) {
	light_string_t *ls = NULL;
	for (uint8_t idx = 0; idx < s->receptacle_count; idx++) {
		ls = search_receptacle_for_light_string_id(&(s->receptacles[idx]), light_string_id);
		if (NULL != ls) break;
	}

	return ls;
}



/*
 * Search the outlets of a breaker for the receptacles having id of receptacle_id.
 *
 * Returns:
 *  Not Found: NULL
 *  Found: VA receptacle_t
 */
static receptacle_t *get_receptacle_by_id_from_breaker_id(uint32_t breaker_id, uint32_t receptacle_id) {
	receptacle_t *r = NULL;
	list_t *outlet_list = get_outlet_list_on_breaker(breaker_id);
	node_t *outlet_node_ptr = get_first_node(outlet_list);
	while (get_list_tail(outlet_list) != outlet_node_ptr) {
		r = search_outlet_for_receptacle_id((outlet_t *)outlet_node_ptr->data, receptacle_id);
		if (NULL != r) break;
		outlet_node_ptr = outlet_node_ptr->next;
	}	

	return r;
}

/*
 * Search the e_model for the receptacle having id of receptacle id.
 *
 * Returns:
 *  Not Found: NULL
 *  Found: VA receptacle_t
 */
static receptacle_t *get_receptacle_by_id(uint32_t receptacle_id) {
	receptacle_t *r = NULL;
	// for each breaker, check each outlet
	if (TRUE == load_center_is_created()) {
		for (uint32_t breaker_idx = 0; breaker_idx < e_model->breakers_installed_cnt; breaker_idx++) {
			// for each outlet on the breaker's circuit, check its loads
			r = get_receptacle_by_id_from_breaker_id(breaker_idx, receptacle_id);
			if (NULL != r) break;
		}
	}

	return r;
}

/*
 * Search the e_model for the breaker having id of breaker_id.
 *
 * Returns:
 *  Not Found: NULL
 *  Found: VA breaker_t
 */
static breaker_t *get_breaker_by_id(uint32_t breaker_id) {
#ifdef PATCHED
	if ((FALSE == load_center_is_created()) || 
		(0 == e_model->breakers_installed_cnt) ||
		(breaker_id >= e_model->breakers_installed_cnt)) {
#else
	if ((FALSE == load_center_is_created()) || (0 == e_model->breakers_installed_cnt)) {
#endif
		return NULL;
	}

	return &(e_model->breakers[breaker_id]);
}

/*
 * Search the e_model for the outlet having id of outlet_id.
 *
 * Returns:
 *  Not Found: NULL
 *  Found: VA outlet_t
 */
static outlet_t *get_outlet_by_id(uint32_t outlet_id) {
	outlet_t *o = NULL;
	int8_t breakers_installed_cnt = get_number_of_breakers_installed_in_load_center();
	if (0 > breakers_installed_cnt) {
		return NULL;
	}
	for (uint32_t breaker_id = 0; breaker_id < breakers_installed_cnt; breaker_id++) {

		list_t *outlet_list = get_outlet_list_on_breaker(breaker_id);
		node_t *outlet_node_ptr = get_first_node(outlet_list);
		while (get_list_tail(outlet_list) != outlet_node_ptr) {
			o = (outlet_t *)outlet_node_ptr->data;
			if (outlet_id == o->id) {
				break;
			} else {
				o = NULL;
			}
			outlet_node_ptr = outlet_node_ptr->next;
		}
	}
	return o;
}

/*
 * Search the e_model for splitter having id of splitter_id.
 *
 * Returns:
 *  Not Found: NULL
 *  Found: VA n_way_splitter_t
 */
static n_way_splitter_t *get_splitter_by_id(uint32_t splitter_id) {
	n_way_splitter_t *s = NULL;

	int8_t breakers_installed_cnt = get_number_of_breakers_installed_in_load_center();
	if (0 > breakers_installed_cnt) {
		return NULL;
	}
	for (uint32_t breaker_id = 0; breaker_id < breakers_installed_cnt; breaker_id++) {

		list_t *outlet_list = get_outlet_list_on_breaker(breaker_id);
		node_t *outlet_node_ptr = get_first_node(outlet_list);
		while (get_list_tail(outlet_list) != outlet_node_ptr) {
			outlet_t *o = (outlet_t *)outlet_node_ptr->data;
			s = search_outlet_for_splitter_id(o, splitter_id);
			if (NULL != s) {
				break;
			}
			outlet_node_ptr = outlet_node_ptr->next;
		}
	}
	return s;
}

/*
 * Search the e_model for light string having id of light_string_id.
 *
 * Returns:
 *  Not Found: NULL
 *  Found: VA light_string_t
 */
static light_string_t *get_light_string_by_id(uint32_t light_string_id) {
	light_string_t *ls = NULL;

	int8_t breakers_installed_cnt = get_number_of_breakers_installed_in_load_center();
	if (0 > breakers_installed_cnt) {
		return NULL;
	}
	for (uint32_t breaker_id = 0; breaker_id < breakers_installed_cnt; breaker_id++) {

		list_t *outlet_list = get_outlet_list_on_breaker(breaker_id);
		node_t *outlet_node_ptr = get_first_node(outlet_list);
		while (get_list_tail(outlet_list) != outlet_node_ptr) {
			outlet_t *o = (outlet_t *)outlet_node_ptr->data;
			ls = search_outlet_for_light_string_id(o, light_string_id);
			if (NULL != ls) {
				break;
			}
			outlet_node_ptr = outlet_node_ptr->next;
		}
	}
	return ls;	
}

/*
 * Check if the breaker with breaker_id is installed.
 *
 * Returns:
 *  Not installed: FALSE
 *  Is installed: TRUE
 */
static uint8_t breaker_id_is_installed(uint32_t breaker_id) {
	if (NULL == get_breaker_by_id(breaker_id)) {
		return FALSE;
	} else {
		return TRUE;
	}
}

/*
 * Get the list of outlets installed on breaker.
 *
 * Returns:
 *  Success: VA of list
 *  Failure: NULL
 */
static list_t * get_outlet_list_on_breaker(uint32_t breaker_id) {
	if (FALSE == breaker_id_is_installed(breaker_id)) {
		return NULL;
	}

	breaker_t * b = get_breaker_by_id(breaker_id);
	return b->outlets;
}

/*
 * Count the number of outlets on this breaker's circuit.
 *
 * Returns:
 *  Success: outlets->count >= 0
 *  Failure: ERR_INVALID_BREAKER_ID
 */
int32_t get_count_outlets_on_breaker(uint32_t breaker_id) {
	if (FALSE == breaker_id_is_installed(breaker_id)) {
		return ERR_INVALID_BREAKER_ID;
	}

	breaker_t * b = get_breaker_by_id(breaker_id);
	return b->outlets->count;
}

/*
 * Get the amp rating of a breaker.
 *
 * Returns:
 *  Success: amp rating 15 or 20
 *  Failure: ERR_INVALID_BREAKER_ID
 */
int8_t get_amp_rating_of_breaker(uint32_t breaker_id) {
	if (FALSE == breaker_id_is_installed(breaker_id)) {
		return ERR_INVALID_BREAKER_ID;
	}

	breaker_t * b = get_breaker_by_id(breaker_id);
	return b->amp_rating;
}

/*
 * Get the amp rating of an outlet.
 *
 * Returns:
 *  Success: amp rating 15 or 20
 *  Failure: ERR_INVALID_OUTLET_ID
 */
int8_t get_amp_rating_of_outlet(uint32_t outlet_id) {
	outlet_t *o = get_outlet_by_id(outlet_id);
	if (NULL == o) {
		return ERR_INVALID_OUTLET_ID;
	} else {
		return o->amp_rating;
	}
}

/*
 * Get the amp rating of a splitter.
 *
 * Returns:
 *  Success: amp rating 15 or 20
 *  Failure: ERR_INVALID_SPLITTER_ID
 */
int8_t get_amp_rating_of_splitter(uint32_t splitter_id) {
	n_way_splitter_t *s = get_splitter_by_id(splitter_id);
	if (NULL == s) {
		return ERR_INVALID_SPLITTER_ID;
	} else {
		return s->total_amp_rating;
	}
}

/*
 * Get the amp rating of a light string.
 *
 * Returns:
 *  Success: amp rating > 0.0
 *  Failure: ERR_INVALID_LIGHT_STRING_ID
 */
float get_amp_rating_of_light_string(uint32_t light_string_id) {
	light_string_t *s = get_light_string_by_id(light_string_id);
	if (NULL == s) {
		return (float)ERR_INVALID_LIGHT_STRING_ID;
	} else {
		return get_max_amps_of_light_string();
	}
}


/*
 * Get the amp rating of a receptacle.
 *
 * Returns:
 *  Success: amp rating 15 or 20
 *  Failure: ERR_INVALID_RECEPTACLE_ID
 */
int8_t get_amp_rating_of_receptacle(uint32_t receptacle_id) {
	receptacle_t *r = get_receptacle_by_id(receptacle_id);
	if (NULL == r) {
		return ERR_INVALID_RECEPTACLE_ID;
	} else {
		return r->amp_rating;
	}
}

/*
 * Count the number of breakers installed in the load center (e_model)
 *
 * Returns:
 *  Success: breaker count >= 0
 *  Failure: ERR_E_MODEL_NOT_EXISTS
 */
int8_t get_number_of_breakers_installed_in_load_center() {
	if (FALSE == load_center_is_created()) {
		return ERR_E_MODEL_NOT_EXISTS;
	}

	return e_model->breakers_installed_cnt;
}

/*
 * Get the number of breaker spaces in the load center.
 *
 * Returns:
 *  Success: breaker_spaces > 0
 *  Failure: ERR_E_MODEL_NOT_EXISTS
 */
int8_t get_total_breaker_space_count() {
	if (FALSE == load_center_is_created()) {
		return ERR_E_MODEL_NOT_EXISTS;
	}

	return e_model->breaker_spaces;
}

/*
 * Get the amp rating of the load center.
 *
 * Returns:
 * 	Success: amp rating > 0
 *  Failure: ERR_E_MODEL_NOT_EXISTS
 */
int32_t get_amp_rating_of_load_center() {
	if (FALSE == load_center_is_created()) {
		return ERR_E_MODEL_NOT_EXISTS;
	}

	return e_model->amp_rating;
}




/*
 * Calculate the total amp load on the load center.
 *
 * Returns:
 *	Success: amp load >= 0.0
 *  Failure: ERR_E_MODEL_NOT_EXISTS
 */
float get_total_amp_load_on_load_center() {
	if (FALSE == load_center_is_created()) {
		return ERR_E_MODEL_NOT_EXISTS;
	}

	// sum amp loads of installed breakers
	float total_amp_load = 0.0;
	int32_t breakers_installed_cnt = get_number_of_breakers_installed_in_load_center();
	if (0 > breakers_installed_cnt) {
		return breakers_installed_cnt;
	}
	for (uint8_t idx = 0; idx < breakers_installed_cnt; idx++) {
		total_amp_load += get_total_amp_load_on_breaker_by_breaker_id(idx);
	}

	return total_amp_load;
}

/*
 * Calculate the total amp load on a breaker having id of breaker_id.
 *
 * Returns:
 *  Success: amp_load >= 0.0
 *  Failure: ERR_INVALID_BREAKER_ID
 */
float get_total_amp_load_on_breaker_by_breaker_id(uint32_t breaker_id) {
	if (FALSE == breaker_id_is_installed(breaker_id)) {
		return ERR_INVALID_BREAKER_ID;
	}

	// sum amp loads of installed breakers
	float total_amp_load = 0.0;
	list_t *outlet_list =  get_outlet_list_on_breaker(breaker_id);
	node_t * outlet_node_ptr = get_first_node(outlet_list);
	while (get_list_tail(outlet_list) != outlet_node_ptr) {
		total_amp_load += get_total_amp_load_on_outlet_by_outlet_va((outlet_t *)outlet_node_ptr->data);
		outlet_node_ptr = outlet_node_ptr->next;
	}

	return total_amp_load;
}

/*
 * Calculate the total amp load on an outlet.
 *
 * Returns:
 *  Success: amp_load >= 0.0
 */
static float get_total_amp_load_on_outlet_by_outlet_va(outlet_t *outlet) {
	float total_amp_load = 0.0;
	total_amp_load += get_total_amp_load_on_receptacle_by_receptacle_va(&(outlet->r1));
	total_amp_load += get_total_amp_load_on_receptacle_by_receptacle_va(&(outlet->r2));
	return total_amp_load;
}

/*
 * Calculate the total amp load on an outlet having outlet id of outlet_id.
 *
 * Returns:
 *  Success: amp_load >= 0.0;
 *  Failure: ERR_INVALID_OUTLET_ID
 */
float get_total_amp_load_on_outlet_by_outlet_id(uint32_t outlet_id) {
	outlet_t *o = get_outlet_by_id(outlet_id);
	if (NULL == o) {
		return ERR_INVALID_OUTLET_ID;
	} else {
		return get_total_amp_load_on_outlet_by_outlet_va(o);
	}
}

/*
 * Calculate the total amp load on a receptacle.
 *
 * Returns:
 *  Success: amp_load >= 0.0
 */
static float get_total_amp_load_on_receptacle_by_receptacle_va(receptacle_t *receptacle) {
	float total_amp_load = 0.0;
	if (SPLITTER == get_receptacle_load_type(receptacle)) {
		total_amp_load = get_total_amp_load_on_splitter_by_splitter_va((n_way_splitter_t *)receptacle->load);
	} else if (LIGHT_STRING == get_receptacle_load_type(receptacle)) {
		total_amp_load = get_total_amp_load_on_light_string_by_light_string_va((light_string_t *)receptacle->load);
	}
	// NO_LOAD has no load, so go with default of 0.0

	return total_amp_load;
}

/*
 * Calculate the total amp load on a receptacle having id of receptacle_id.
 *
 * Returns:
 *  Success: amp_load >= 0.0
 *  Failure: ERR_INVALID_RECEPTACLE_ID
 */
float get_total_amp_load_on_receptacle_by_receptacle_id(uint32_t receptacle_id) {
	receptacle_t *r = get_receptacle_by_id(receptacle_id);
	if (NULL == r) {
		return ERR_INVALID_RECEPTACLE_ID;
	} else {
		return get_total_amp_load_on_receptacle_by_receptacle_va(r);
	}
}

/*
 * Calculate the total amp load on a splitter.
 *
 * Returns:
 *  Success: amp_load >= 0.0
 */
static float get_total_amp_load_on_splitter_by_splitter_va(n_way_splitter_t *splitter) {
	float total_amp_load = 0.0;
	for (int idx = 0; idx < splitter->receptacle_count; idx++) {
		total_amp_load += get_total_amp_load_on_receptacle_by_receptacle_va(&(splitter->receptacles[idx]));
	}
	return total_amp_load;
}

/*
 * Calculate the total amp load on a splitter having id of splitter_id.
 *
 * Returns:
 *  Success: amp_load >= 0.0
 *  Failure: ERR_INVALID_SPLITTER_ID
 */
float get_total_amp_load_on_splitter_by_splitter_id(uint32_t splitter_id) {
	n_way_splitter_t *s = get_splitter_by_id(splitter_id);
	if (NULL == s) {
		return ERR_INVALID_SPLITTER_ID;
	} else {
		return get_total_amp_load_on_splitter_by_splitter_va(s);
	}
}

/*
 * Calculate the total amp load on a light string.
 *
 * Returns:
 *  Success: amp_load >= 0.0
 */
static float get_total_amp_load_on_light_string_by_light_string_va(light_string_t *light_string) {
	float total_amp_load = 0.0;
	total_amp_load += convert_watts_to_amps(light_string->total_wattage);
	total_amp_load += get_total_amp_load_on_receptacle_by_receptacle_va(&(light_string->receptacle));
	return total_amp_load;
}

/*
 * Calculate the total amp load on a light string having id of light_string_id.
 *
 * Returns:
 *  Success: amp_load >= 0.0
 *  Failure: ERR_INVALID_LIGHT_STRING_ID
 */
float get_total_amp_load_on_light_string_by_light_string_id(uint32_t light_string_id) {
	light_string_t *ls = get_light_string_by_id(light_string_id);
	if (NULL == ls) {
		return ERR_INVALID_LIGHT_STRING_ID;
	} else {
		return get_total_amp_load_on_light_string_by_light_string_va(ls);
	}
}



/*
 * Calculate the max receptacle amp load on an outlet.
 *
 * Outlet has 2 receptacles, find the max of their loads.
 *
 * Returns:
 *  Success: max_amp_load >= 0.0
 */
static float get_max_receptacle_amp_load_on_outlet_by_outlet_va(outlet_t *outlet) {
	float r1_load = get_total_amp_load_on_receptacle_by_receptacle_va(&(outlet->r1));
	float r2_load = get_total_amp_load_on_receptacle_by_receptacle_va(&(outlet->r2));

	if (r1_load > r2_load) {
		return r1_load;
	} else {
		return r2_load;
	}
}

/*
 * Calculate the max receptacle amp load on an outlet having outlet id of outlet_id.
 *
 * Returns:
 *  Success: amp_load >= 0.0;
 *  Failure: ERR_INVALID_OUTLET_ID
 */
float get_max_receptacle_amp_load_on_outlet_by_outlet_id(uint32_t outlet_id) {
	outlet_t *o = get_outlet_by_id(outlet_id);
	if (NULL == o) {
		return ERR_INVALID_OUTLET_ID;
	} else {
		return get_max_receptacle_amp_load_on_outlet_by_outlet_va(o);
	}
}

/*
 * Calculate the max receptacle amp load on a splitter.
 *
 * Splitter has n receptacles, find the max of their loads.
 *
 * Returns:
 *  Success: amp_load >= 0.0
 */
static float get_max_receptacle_amp_load_on_splitter_by_splitter_va(n_way_splitter_t *splitter) {
	float max_amp_load = 0.0;
	float tmp_amp_load = 0.0;
	for (int idx = 0; idx < splitter->receptacle_count; idx++) {
		tmp_amp_load = get_total_amp_load_on_receptacle_by_receptacle_va(&(splitter->receptacles[idx]));
		if (tmp_amp_load > max_amp_load) {
			max_amp_load = tmp_amp_load;
		}
	}
	return max_amp_load;
}

/*
 * Calculate the max receptacle amp load on a splitter having id of splitter_id.
 *
 * Returns:
 *  Success: amp_load >= 0.0
 *  Failure: ERR_INVALID_SPLITTER_ID
 */
float get_max_receptacle_amp_load_on_splitter_by_splitter_id(uint32_t splitter_id) {
	n_way_splitter_t *s = get_splitter_by_id(splitter_id);
	if (NULL == s) {
		return ERR_INVALID_SPLITTER_ID;
	} else {
		return get_max_receptacle_amp_load_on_splitter_by_splitter_va(s);
	}
}





/*
 * Start the electric model using the given load center model.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_E_MODEL_EXISTS, ERR_INVALID_MODEL_ID
 */
int8_t init_electric_model(LOAD_CENTER_MODELS_T model_id) {
	if (TRUE == load_center_is_created()) {
		return ERR_E_MODEL_EXISTS;
	}

	e_model = get_new_load_center_by_model_id(model_id);
	if (NULL == e_model) {
		return ERR_INVALID_MODEL_ID;
	} else {
		return SUCCESS;
	}
}

/*
 * Add breaker to load center, given breaker model id.
 *
 * result will store the breaker_id.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_INVALID_MODEL_ID, ERR_BREAKER_SPACES_FULL, ERR_E_MODEL_NOT_EXISTS
 */
int8_t add_breaker_to_load_center(CIRCUIT_MODELS_T model_id, assemble_result_t *result) {

	if (FALSE == load_center_is_created()) {
		return ERR_E_MODEL_NOT_EXISTS;
	}

	if (TRUE == load_center_breaker_spaces_are_full()) {
		return ERR_BREAKER_SPACES_FULL;
	}

	breaker_t *breaker_space = &(e_model->breakers[e_model->breakers_installed_cnt]);
	if (-1 == get_new_breaker_by_model_id(model_id, breaker_space, e_model->breakers_installed_cnt)) {
		return ERR_INVALID_MODEL_ID;
	}

	result->object_id = e_model->breakers_installed_cnt++;

	return SUCCESS;
}

/*
 * Add outlet to breaker, given outlet model id and breaker id.
 *
 * result will store the outlet_id and 2 receptacle id's.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_E_MODEL_NOT_EXISTS, ERR_INVALID_BREAKER_ID, ERR_INVALID_MODEL_ID, ERR_OUTLET_AMPS_EXCEED_BREAKER_AMPS
 */
int8_t add_outlet_to_breaker(CIRCUIT_MODELS_T outlet_model_id, uint32_t breaker_id, assemble_result_t *result) {

	if (FALSE == load_center_is_created()) {
		return ERR_E_MODEL_NOT_EXISTS;
	}

	breaker_t *breaker = get_breaker_by_id(breaker_id);
	if (NULL == breaker) {
		return ERR_INVALID_BREAKER_ID;
	}
	outlet_t *o = get_new_outlet_by_model_id(outlet_model_id);
	if (NULL == o) {
		return ERR_INVALID_MODEL_ID;
	}

	// don't want a 20amp outlet on a 15amp breaker
	if (o->amp_rating > breaker->amp_rating) {
		deallocate((void *)o, sizeof(outlet_t));
		return ERR_OUTLET_AMPS_EXCEED_BREAKER_AMPS;
	}

	result->object_id = o->id;
	result->receptacle_id[0] = o->r1.id;
	result->receptacle_id[1] = o->r2.id;
	result->receptacle_ids_assigned_cnt = 2;
	return list_append(breaker->outlets, node_create((void *)o));
}

/*
 * Add n-way splitter to receptacle, given splitter model id and receptacle id.
 *
 * result will store the splitter id, the number of receptacles, and all receptacle ids.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_E_MODEL_NOT_EXISTS, ERR_INVALID_RECEPTACLE_ID, ERR_INVALID_MODEL_ID
 */
int8_t add_n_way_splitter_to_receptacle(SPLITTER_MODELS_T splitter_model_id, uint32_t receptacle_id, assemble_result_t *result) {

	if (FALSE == load_center_is_created()) {
		return ERR_E_MODEL_NOT_EXISTS;
	}

	receptacle_t *r = get_receptacle_by_id(receptacle_id);
	if (NULL == r) {
		return ERR_INVALID_RECEPTACLE_ID;
	}

	if (TRUE == receptacle_is_loaded(r)) {
		return ERR_RECEPTACLE_FULL;
	}

	n_way_splitter_t *s = get_new_n_way_splitter_by_model_id(splitter_model_id);
	if (NULL == s) {
		return ERR_INVALID_MODEL_ID;
	}

	// connect splitter to receptacle
	r->load_type = SPLITTER;
	r->load = (void *)s;
	r->amp_rating = s->total_amp_rating;

	// populate result
	result->object_id = s->id;
	result->receptacle_ids_assigned_cnt = s->receptacle_count;
	for (int i = 0; i < s->receptacle_count; i++) {
		result->receptacle_id[i] = s->receptacles[i].id;
	}

	return SUCCESS;
}

/*
 * Add light string to receptacle, given light string model id and receptacle id.
 *
 * result will store the light string id, 1 as the number of receptacles, and one receptacle id.
 *
 * Returns:
 *  Success: SUCCESS
 *  Failure: ERR_E_MODEL_NOT_EXISTS, ERR_INVALID_RECEPTACLE_ID, ERR_INVALID_MODEL_ID
 */
int8_t add_light_string_to_receptacle(LIGHT_STRING_MODELS_T light_string_model_id, uint32_t receptacle_id, assemble_result_t *result) {

	if (FALSE == load_center_is_created()) {
		return ERR_E_MODEL_NOT_EXISTS;
	}

	receptacle_t *r = get_receptacle_by_id(receptacle_id);
	if (NULL == r) {
		return ERR_INVALID_RECEPTACLE_ID;
	}

	if (TRUE == receptacle_is_loaded(r)) {
		return ERR_RECEPTACLE_FULL;
	}

	light_string_t *ls = get_new_light_string_by_model_id(light_string_model_id);
	if (NULL == ls) {
		return ERR_INVALID_MODEL_ID;
	}

	// connect light string to receptacle
	r->load_type = LIGHT_STRING;
	r->load = (void *)ls;

	// populate result
	result->object_id = ls->id;
	result->receptacle_ids_assigned_cnt = 1;
	result->receptacle_id[0] = ls->receptacle.id;

	return SUCCESS;
}
