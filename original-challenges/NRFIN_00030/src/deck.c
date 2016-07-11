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
#include "deck.h"



struct deck *create_deck() {

	struct deck *d = NULL;
	d = calloc(sizeof(struct deck));

	uint8_t idx = 0;
	for (uint8_t s = 1; s < 5; s++) {
		for (uint8_t r = 1; r < 14; r++) {
			d->cards[idx] = create_card(s, r);
			d->count++;
			idx++;
		}
	}

	return d;
}

int shuffle_deck(struct deck *d, uint8_t seed) {
	if (NULL == d) {
		return ERR_UNINITIALIZED_DECK;
	}

	uint8_t idx = 0; 	// loop index walks through the deck
	uint8_t rand_idx = 0; 	// index of card to swap with card at the loop index
	struct card *temp_card = NULL;

	idx = seed % 52; // index in deck where algorithm will start

	for (int i = 0; i < 52; i++) {
		idx = (idx + i) % 52;
		rand_idx = (rand_idx + prng_get_next()) % 52;

		// swap card at rand_idx with card at idx
		if (idx != rand_idx) {
			temp_card = d->cards[idx];
			d->cards[idx] = d->cards[rand_idx];
			d->cards[rand_idx] = temp_card;
		}
	}
	return SUCCESS;
}

struct deck *get_shuffled_deck(uint8_t seed) {
    struct deck *d;
    d = create_deck();
    shuffle_deck(d, seed);
    return d;
}

struct card *pop(struct deck *d) {
	if (NULL == d) {
		return NULL;
	}
	if (0 == d->count) {
		return NULL;
	}

	struct card *c = NULL;
	d->count--;
	c = d->cards[d->count];
	d->cards[d->count] = NULL;
	return c;
}

int is_deck_empty(struct deck *d) {
	if (NULL == d) {
		return ERR_UNINITIALIZED_DECK;
	}
	if (0 == d->count) {
		return TRUE;
	} else {
		return FALSE;
	}
}

