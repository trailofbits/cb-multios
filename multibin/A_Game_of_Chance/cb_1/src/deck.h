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

typedef struct {
	unsigned int count; 	// number of cards remaining in deck
	Card cards[];			// array of Cards
} Deck;


/*
 * Define a new deck or replace deck with a new one.
 *
 * This copies the values out of the values param, but does not free the values param.
 * The caller should do that.
 *
 * @param count 	Number of cards
 * @param values 	Array of card values
 * @return SUCCESS if success, else -1 if error (invalid value)
 */
int replace_deck(unsigned int count, unsigned char *values);

/*
 * Get the next available card.
 *
 * @return VA of card or NULL if none left
 */
Card *get_next_card();

/*
 * Get the number of cards in the deck.
 *
 * @return Number of cards remaining in deck. If no deck defined, will return 0.
 */
unsigned int get_deck_size();


#endif
