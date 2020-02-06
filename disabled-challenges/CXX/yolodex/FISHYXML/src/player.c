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
#include "cgc_libc.h"
#include "cgc_common.h"
#include "cgc_deck.h"
#include "cgc_hand.h"
#include "cgc_player.h"

struct player *cgc_create_player(uint8_t id, char *name) {

	struct player *p = NULL;
	p = cgc_calloc(sizeof(struct player));

	p->name = name;
	p->id = id;
	p->book_count = 0;
	p->h = cgc_create_hand();
	return p;
}

int cgc_take_top_card(struct player *p, struct deck *d) {
	if (NULL == p) {
		return ERR_UNINITIALIZED_PLAYER;
	}
	if (NULL == d) {
		return ERR_UNINITIALIZED_DECK;
	}

 	return cgc_add_card_to_hand(p->h, cgc_pop(d));
}

int cgc_have_cards_of_rank(struct player *p, uint8_t rank, struct card *cards[]) {
	if (NULL == p) {
		return ERR_UNINITIALIZED_PLAYER;
	}

	return cgc_get_all_of_rank_from_hand(p->h, rank, cards);
}

int cgc_play_books(struct player *p) {
	if (NULL == p) {
		return ERR_UNINITIALIZED_PLAYER;
	}

	if (4 > cgc_get_count_cards_in_hand(p->h)) {
		return 0;
	}

	int qty = 0;
	int ret = 0;
	int book_count = 0;
	struct card *cards[4] = {0};

	for (int rank = 1; rank < 14; rank++) {
		if (0 > (qty = cgc_qty_of_rank_in_hand(p->h, rank))) {return qty;}

		if (4 == qty) {
			if (0 > (ret = cgc_get_all_of_rank_from_hand(p->h, rank, cards))) {return ret;}

			cgc_destroy_card(cards[3]);
			cgc_destroy_card(cards[2]);
			cgc_destroy_card(cards[1]);
			cgc_destroy_card(cards[0]);

			p->book_count++;
			book_count++;
		}
	}

	return book_count;
}

int cgc_is_player_hand_empty(struct player *p) {
	if (NULL == p) {
		return ERR_UNINITIALIZED_PLAYER;
	}

	if (TRUE == cgc_is_hand_empty(p->h)) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int cgc_draw_new_hand(struct player *p, struct deck *d, uint8_t qty) {
	if (NULL == p) {
		return ERR_UNINITIALIZED_PLAYER;
	}
	if (NULL == d) {
		return ERR_UNINITIALIZED_DECK;
	}
	if ((0 == qty) || (7 < qty)) {
		return ERR_INVALID_QTY;
	}

	int ret = 0;
	int cnt = 0;
	for (; cnt < qty; cnt++) {
		ret = cgc_take_top_card(p, d);
		if (0 > ret) {
			return ret; // ERR_NULL_CARD when no more cards in pool (deck)
		}
	}

	return cnt;
}

int cgc_select_random_card(struct player *p) {
	if (NULL == p) {
		return ERR_UNINITIALIZED_PLAYER;
	}

	if (0 == cgc_get_count_cards_in_hand(p->h)) {
		return ERR_HAND_EMPTY;
	}

	return cgc_get_rank_of_random_card_in_hand(p->h);
}

int cgc_accept_cards(struct player *p, struct card *cards[], uint8_t qty) {
	if (NULL == p) {
		return ERR_UNINITIALIZED_PLAYER;
	}
	if (NULL == cards) {
		return ERR_UNINITIALIZED_ARRAY;
	}

	return cgc_add_cards_to_hand(p->h, cards, qty);
}

int cgc_get_players_newest_card(struct player *p, struct card **card) {
	if (NULL == p) {
		return ERR_UNINITIALIZED_PLAYER;
	}
	if (NULL == card) {
		return ERR_UNINITIALIZED_ARRAY;
	}

	return cgc_get_latest_card(p->h, card);
}

