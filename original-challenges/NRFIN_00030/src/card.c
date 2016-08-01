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
#include "card.h"


struct card *create_card(uint8_t suit, uint8_t rank) {

	if ((FALSE == is_valid_suit(suit)) || 
		(FALSE == is_valid_rank(rank))) {
		return NULL;
	}

	struct card *c = NULL;
	c = calloc(sizeof(struct card));
	c->suit = suit;
	c->rank = rank;

	return c;
}

int is_rank(struct card *c, uint8_t rank) {
	if (NULL == c) {
		return ERR_UNINITIALIZED_CARD;
	}
	if (c->rank == rank) {
		return TRUE;
	} else {
		return FALSE;
	}
}

void destroy_card(struct card *c) {
	free(c);
}

int is_valid_suit(uint8_t suit) {
	if ((1 <= suit) && (4 >= suit)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int is_valid_rank(uint8_t rank) {
	if ((1 <= rank) && (13 >= rank)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int is_equal(struct card *c1, struct card *c2) {
	if ((NULL == c1) && (NULL == c2)) {
		return TRUE;
	}
	if ((NULL == c1) || (NULL == c2)) {
		return FALSE;
	}

	if ((c1->rank == c2->rank) && (c1->suit == c2->suit)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int is_set_equal(struct card *cards1[], struct card *cards2[], uint8_t qty) {
	if (0 == qty) {
		return is_equal(cards1[0], cards2[0]);
	}

	unsigned int count = 0;
	unsigned int found = 0;
	for (int idx = 0; idx < qty; idx++) {
		for (int idx2 = 0; idx2 < qty; idx2++) {
			if (TRUE == is_equal(cards1[idx], cards2[idx2])) {
				found++;
				count++;
			}
		}
		if (1 < found) {
			return FALSE;
		}
		found = 0;
	}

	if (qty != count) {
		return FALSE;
	} else {
		return TRUE;
	}
}

