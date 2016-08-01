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
#include "hand.h"

struct hand *create_hand() {
	struct hand *h = NULL;
	h = calloc(sizeof(struct hand));

	return h;
}

void consolidate_hand(struct hand *h) {
	uint8_t qty_in_place = 0; // number of cards that are verified consolidated
	uint8_t r_idx = 0; // idx where card is read from
	uint8_t w_idx = 0; // idx where card is written to

	while ((r_idx < 52) && (qty_in_place < h->count)) {
		if (NULL == h->cards[r_idx]) {
			r_idx++;
		} else if ((NULL != h->cards[r_idx]) && (NULL == h->cards[w_idx])) {
			h->cards[w_idx] = h->cards[r_idx];
			h->cards[r_idx] = NULL;
			w_idx++;
			// r_idx = w_idx;
			qty_in_place++;
		} else {
			r_idx++;
			w_idx++;
			qty_in_place++;
		}
	}
}

int add_card_to_hand(struct hand *h, struct card *c) {
	if (NULL == h) {
		return ERR_UNINITIALIZED_HAND;
	}
	if (NULL == c) {
		return ERR_NULL_CARD;
	}

	if (52 <= h->count) {
		return ERR_HAND_FULL;
	}

	// assumes hand has been consolidated

 	h->cards[h->count] = c;
 	h->count++;

 	return SUCCESS;
}

int add_cards_to_hand(struct hand *h, struct card *cards[], uint8_t qty) {
	int ret = SUCCESS;
	if (NULL == h) {
		return ERR_UNINITIALIZED_HAND;
	}
	if (52 < (qty + h->count)) {
		return ERR_INVALID_QTY;
	}

	if (NULL == cards) {
		return ERR_NULL_CARD;
	}
	for (uint8_t idx_ = 0; idx_ < qty; idx_++) {
		if (NULL == cards[idx_]) {
			return ERR_NULL_CARD;
		}
	}

	for (uint8_t idx = 0; idx < qty; idx++) {
		ret = add_card_to_hand(h, cards[idx]);
		if (SUCCESS != ret) {
			return ret;
		}
		cards[idx] = NULL;
	}
	return ret;
}

int rm_card_from_hand(struct hand *h, uint8_t idx, struct card **c) {

	if (NULL == h) {
		return ERR_UNINITIALIZED_HAND;
	}
	if (h->count <= idx) {
		return ERR_INVALID_CARD;
	}

	*c = h->cards[idx];

	if (NULL == *c) {
		return ERR_NULL_CARD;
	}

	h->cards[idx] = NULL;
	h->count--;

	consolidate_hand(h);

	return SUCCESS;
}

int qty_of_rank_in_hand(struct hand *h, uint8_t rank) {

	if (NULL == h) {
		return ERR_UNINITIALIZED_HAND;
	}

	int qty = 0;
	for (int idx = 0; idx < h->count; idx++) {
		if (TRUE == is_rank(h->cards[idx], rank)) {
			qty++;
		}
	}

	return qty;
}

int get_all_of_rank_from_hand(struct hand *h, uint8_t rank, struct card *cards[]) {

	if (NULL == h) {
		return ERR_UNINITIALIZED_HAND;
	}

	if (NULL == cards) {
		return ERR_NULL_CARD;
	}

	if (0 == rank) {
		return 0;
	}
	// rm_card_from_hand() runs consolidate, so need to use cnt
	// instead of idx to index into the hand and allow the idx variable
	// to just count through the original number of cards. also need to
	// use hand_size for the upper bound because h->count will change
	// when consolidate is run.
	int cnt = 0;
	int hand_size = h->count;
	uint8_t qty = 0;
	int ret = 0;
	for (int idx = 0; idx < hand_size; idx++) {
		if (TRUE == is_rank(h->cards[cnt], rank)) {
			ret = rm_card_from_hand(h, cnt, &cards[qty]);
			if (0 > ret) {
				return ret;
			}
			qty++;
		} else {
			cnt++;
		}
	}

	return qty;
}

int get_count_cards_in_hand(struct hand *h) {
	if (NULL == h) {
		return ERR_UNINITIALIZED_HAND;
	}
	return h->count;
}

int get_rank_of_random_card_in_hand(struct hand *h) {
	if (NULL == h) {
		return ERR_UNINITIALIZED_HAND;
	}

	int count = get_count_cards_in_hand(h);
	if (0 > count) {
		return count;
	}
	if (0 == count) {
		return ERR_HAND_EMPTY;		
	}
	uint8_t rand_idx = 0;
	if (1 < count) {
		uint8_t p = prng_get_next();
		rand_idx = p % count;
	}

	return h->cards[rand_idx]->rank;
}

int is_hand_empty(struct hand *h) {
	if (NULL == h) {
		return ERR_UNINITIALIZED_HAND;
	}

	if (0 == get_count_cards_in_hand(h)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int get_latest_card(struct hand *h, struct card **c) {
	if (NULL == h) {
		return ERR_UNINITIALIZED_HAND;
	}

	if (TRUE == is_hand_empty(h)) {
		return ERR_HAND_EMPTY;
	}

	*c = h->cards[h->count - 1];
	return SUCCESS;
}
