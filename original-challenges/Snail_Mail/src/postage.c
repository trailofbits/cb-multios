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
#include "malloc.h"
#include "memcmp.h"
#include "list.h"
#include "memcpy.h"
#include "rand.h"

#include "postage.h"

#define SEED_MAX (4096 - 3)
static const char BAD_STAMP[3] 			= {'\xbb','\xaa','\xdd'};

const char *seed = (const char *)FLAG_PAGE;
unsigned short seed_idx = 0;

struct list stamp_roll;

/**
 * Predicate compare function for stamp_roll list searching
 *
 * @param s1 	Pointer to data element of node 1 (stamp1)
 * @param s2	Pointer to data element of node 2 (stamp2)
 * @return TRUE if s1->serial == s2->serial, else FALSE
 */
static unsigned char stamp_cmp(const void *s1, void *s2) {
	stamp_t *stamp1 = (stamp_t *)s1;
	stamp_t *stamp2 = (stamp_t *)s2;

	return (0 == memcmp(stamp1->serial, stamp2->serial, STAMP_SIZE));
}

void init_stamp_roll(void) {
	list_init(&stamp_roll, free);
}

stamp_t *get_new_stamp(void) {
	// create a stamp
	stamp_t *s = malloc(sizeof(stamp_t));
	MALLOC_OK(s);

	// make sure no valid stamp has the serial of BAD_STAMP
	do {
#ifndef PATCHED_1
		if (sizeof(stamp_t) != memcpy(s->serial, &seed[seed_idx], sizeof(stamp_t)))
			return NULL;
		seed_idx = (seed_idx + 3) % SEED_MAX;
#else
		for (int i = 0; i < sizeof(stamp_t); i++) {
			rand((char *)&seed_idx, 2);
			s->serial[i] = seed[seed_idx % SEED_MAX];
		}
#endif
	} while (0 == memcmp(s->serial, (void *)BAD_STAMP, sizeof(BAD_STAMP)));

	// add to stamp roll
	list_insert_at_end(&stamp_roll, s);

	return s;
}

int use_stamp(stamp_t *s) {
	// determine if stamp is valid
	struct node *s_on_roll = list_find_node_with_data(&stamp_roll, stamp_cmp, s);
	if (NULL == s_on_roll) return -1;

	// remove stamp from stamp_roll
	list_remove_node(&stamp_roll, s_on_roll);

	// destroy used stamp
	list_destroy_node(&stamp_roll, &s_on_roll);

	return SUCCESS;
}

