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
#include <stdint.h>
#include "libc.h"
#include "memcpy.h"

#include "people.h"


/**
 * When a person has a relationship change, this function
 * will check each Relation buffer for empty slots and perform
 * a left shift on the remaining entries if an empty slot
 * if found.
 *
 * @param p 	Pointer to Person
 * @param id 	ID of Person
 */
void  __attribute__((regparm(2))) shift_relation(Person *p, uint32_t id) {
	size_t count = 0;
	int prev_idx = 0;
	int idx = 0;
	// algorithm for left shift to fill empty spaces:
	// check idx
	// if FULL and prev_idx < i, move i -> prev_idx, clear i, set i and prev_idx to prev_idx +1
	// if FULL and prev_idx == i, inc i and prev_idx
	// else EMPTY, inc i

	// children.adopted
	count = sizeof(p->children.adopted) / sizeof(p->children.adopted[0]);
	prev_idx = 0;
	idx = 0;
	while (idx < count) {
		if ((PERSON_UNKNOWN != p->children.adopted[idx].person_id) &&
			(prev_idx < idx)) {

			p->children.adopted[prev_idx].person_id = p->children.adopted[idx].person_id;
			p->children.adopted[idx].person_id = PERSON_UNKNOWN;
			p->children.adopted[prev_idx].person = p->children.adopted[idx].person;
			p->children.adopted[idx].person = NULL;

			idx = prev_idx + 1;
			prev_idx = idx;
		} else if ((PERSON_UNKNOWN != p->children.adopted[idx].person_id) &&
				   (prev_idx == idx)) {
			idx++;
			prev_idx++;
		} else {
			idx++;
		}
	}

	// children.biological
	count = sizeof(p->children.biological) / sizeof(p->children.biological[0]);
	prev_idx = 0;
	idx = 0;
	while (idx < count) {
		if ((PERSON_UNKNOWN != p->children.biological[idx].person_id) &&
			(prev_idx < idx)) {

			p->children.biological[prev_idx].person_id = p->children.biological[idx].person_id;
			p->children.biological[idx].person_id = PERSON_UNKNOWN;
			p->children.biological[prev_idx].person = p->children.biological[idx].person;
			p->children.biological[idx].person = NULL;

			idx = prev_idx + 1;
			prev_idx = idx;
		} else if ((PERSON_UNKNOWN != p->children.biological[idx].person_id) &&
				   (prev_idx == idx)) {
			idx++;
			prev_idx++;
		} else {
			idx++;
		}
	}

	// parents.adopting
	count = sizeof(p->parents.adopting) / sizeof(p->parents.adopting[0]);
	prev_idx = 0;
	idx = 0;
	while (idx < count) {
		if ((PERSON_UNKNOWN != p->parents.adopting[idx].person_id) &&
			(prev_idx < idx)) {

			p->parents.adopting[prev_idx].person_id = p->parents.adopting[idx].person_id;
			p->parents.adopting[idx].person_id = PERSON_UNKNOWN;
			p->parents.adopting[prev_idx].person = p->parents.adopting[idx].person;
			p->parents.adopting[idx].person = NULL;

			idx = prev_idx + 1;
			prev_idx = idx;
		} else if ((PERSON_UNKNOWN != p->parents.adopting[idx].person_id) &&
				   (prev_idx == idx)) {
			idx++;
			prev_idx++;
		} else {
			idx++;
		}
	}

	// partners.former
	count = sizeof(p->partners.former) / sizeof(p->partners.former[0]);
	prev_idx = 0;
	idx = 0;
	while (idx < count) {
		if ((PERSON_UNKNOWN != p->partners.former[idx].person_id) &&
			(prev_idx < idx)) {

			p->partners.former[prev_idx].person_id = p->partners.former[idx].person_id;
			p->partners.former[idx].person_id = PERSON_UNKNOWN;
			p->partners.former[prev_idx].person = p->partners.former[idx].person;
			p->partners.former[idx].person = NULL;

			idx = prev_idx + 1;
			prev_idx = idx;
		} else if ((PERSON_UNKNOWN != p->partners.former[idx].person_id) &&
				   (prev_idx == idx)) {
			idx++;
			prev_idx++;
		} else {
			idx++;
		}
	}
}

/**
 * Read byes from input to create a new Person.
 *
 * @param input 	Pointer to Buffer of input data
 * @return Pointer to Person or NULL if error.
 */
Person *new_person(char *input) {
	Person *p = NULL;
	char *idx = input;
	size_t shift = 0;

	if (NULL == input) return p;

	p = calloc(sizeof(Person));
	MALLOC_OK(p);

	p->id = *(uint32_t *)idx;
	idx += sizeof(uint32_t);

	p->lifecycle.birth_year = *(uint16_t *)idx;
	idx += sizeof(uint16_t);

	shift = 10*sizeof(uint8_t);
	memcpy(&p->name.fname, idx, shift);
	idx += shift;

	memcpy(&p->name.mname, idx, shift);
	idx += shift;

	memcpy(&p->name.lname, idx, shift);
	idx += shift;

	p->shift = shift_relation;

	return p;
}

/**
 * Search the Person list for the Person having the given ID.
 *
 * @param p_list 	Pointer to start of List of Persons
 * @param id 		ID of Person to find
 * @return Pointer to Person having ID or NULL if not found or is unknown.
 */
Person *get_person_by_id(Person *p_list, uint32_t id) {
	if ((NULL == p_list) || (PERSON_UNKNOWN == id)) {
		return NULL;
	}

	Person *ptr = p_list;
	while ((NULL != ptr) && (id != ptr->id)) {
		ptr = ptr->next;
	}

	return ptr;
}

/**
 * Append a Person to the Person List.
 *
 * @param p_list 	Pointer to Pointer to List of Persons
 * @param p 		Pointer to Person to add
 */
void add_person_to_list(Person **p_list, Person *p) {
	Person *this = *p_list;
	Person *prev = *p_list;

	if (NULL == this) { // was empty list, add as first
		*p_list = p;
	} else {  // find end of list then append
		while (NULL != this) {
			prev = this;
			this = this->next;
		}
		prev->next = p;
	}
}

/**
 * Simply count the number of people in the family tree
 *
 * @param p_list 	Pointer to List of Persons
 * @return Number of people in the list
 */
uint32_t count_people(Person *p_list) {
	uint32_t count = 0;
	while (NULL != p_list) {
		count++;
		p_list = p_list->next;
	}
	return count;
}


