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

#ifndef PEOPLE_H
#define PEOPLE_H 1

#include <libcgc.h>


typedef struct person Person;
typedef struct relation Relation;
typedef struct search Search;

typedef enum {  RT_NONE = 0, 
				RT_SELF = 1, 
				RT_MOTHER = 2,
				RT_FATHER = 4,
				RT_ADOPTING_PARENT = 8,
				RT_ADOPTED_CHILD = 16,
				RT_BIO_CHILD = 32,
				RT_PARTNER = 64,
				RT_FORMER = 128,
			} R_TYPES;

#define PERSON_UNKNOWN  0x00000000
#define RELATED 		0x10000001
#define NOT_RELATED 	0x14000041

struct relation {
	uint32_t person_id;		// 0x00000000 (Unknown)
	Person *person;			// NULL when id is Unknown
};

struct search {
	Person   *p;		// The person being processed
	uint32_t  visited;	// bit map of relations in this person which have been processed (bitmap of R_TYPES)
};


typedef void __attribute__((regparm(2))) (*shift_relation_fn)(Person *p, uint32_t id);

struct person {
	uint32_t id;
	struct {
		uint16_t birth_year;
		uint16_t death_year; 	// 0 means still alive
	} lifecycle;
	struct {
		uint8_t fname[10];
		uint8_t mname[10];
		uint8_t lname[10];
	} name;
	struct {
		Relation adopted[10];
		Relation biological[10];
	} children;
	struct {
		Relation biological_mother;
		Relation biological_father;
		Relation adopting[2];
	} parents;
	struct {
		Relation current;		// we'll ignore polygomy
		Relation former[2];
	} partners;
	shift_relation_fn shift;
	Person *next;
};

// qty of input data required to create a person (id, birth_year, fname, mname, lname)
#define PERSON_IN_SZ (sizeof(uint32_t) + sizeof(uint16_t) + 3*10*sizeof(uint8_t))

Person *new_person(char *input);
void add_person_to_list(Person **p_list, Person *p);
Person *get_person_by_id(Person *p_list, uint32_t id);
uint32_t count_people(Person *p_list);


#endif
