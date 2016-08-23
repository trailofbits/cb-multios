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

#include "libc.h"
#include "malloc.h"

#include "card.h"
#include "deck.h"

static Deck *deck = NULL;

int replace_deck(unsigned int count, unsigned char *values) {
	if (NULL != deck) {
		free(deck);
	}
	if (0 == count) {
		return -1;
	}

	deck = malloc(sizeof(Deck) + count * sizeof(Card));
	MALLOC_OK(deck);

	deck->count = count;
	for (int i = 0; i < count; i++) {
		if (FALSE == is_valid_value(values[i])) {
			DBG("invaild card %H\n", values[i]);
			return -1;
		}
		deck->cards[i].value = values[i];
	}

	return SUCCESS;
}

Card *get_next_card() {
	Card *c = NULL;
	if ((NULL != deck) && (0 < deck->count)) {
		c = &deck->cards[--deck->count];
	}
	return c;
}

unsigned int get_deck_size() {
	if (NULL == deck) {
		return 0;
	}
	return deck->count;
}
