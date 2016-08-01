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


#ifndef DECK_H
#define DECK_H 1

#include "card.h"

struct deck {
	uint8_t count;
	uint8_t unk1; // push size to mult of 4 bytes
	uint8_t unk2; // push size to mult of 4 bytes
	uint8_t unk3; // push size to mult of 4 bytes
	struct card *cards[52];
};

/**
 * Create a deck of all 52 cards in order of increasing suit and rank.
 *
 * @return VA of new deck
 */
extern struct deck *create_deck();

/**
 * Shuffle the deck.
 *
 * This shuffling algorithm is an abomination of the Richard Durstenfeld
 *  shuffle. This algorithm is unique, because it starts in a random index
 *  and all cards are available in the choice for the random swap idx.
 *
 * @param d Deck to shuffle
 * @param seed Seed to use in random generator in shuffle
 * @return SUCCESS or ERR_UNINITIALIZED_DECK on error
 */
extern int shuffle_deck(struct deck *d, uint8_t seed);

/**
 * Get a new deck that is shuffled.
 *
 * @param seed Seed to use in random generator in shuffle
 * @return VA of new deck.
 */
extern struct deck *get_shuffled_deck(uint8_t seed);

/**
 * Pop the top card off of the deck.
 *
 * @param d The Deck
 * @return VA of card if there is at least one card in the deck.
 *  NULL if deck is empty or uninitialized.
 */
extern struct card *pop(struct deck *d);

/**
 * Check to see if the deck is empty
 *
 * @return TRUE if yes, FALSE if no or ERR_UNINITIALIZED_DECK on error
 */
extern int is_deck_empty(struct deck *d);


#endif