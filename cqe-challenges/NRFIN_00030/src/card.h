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


#ifndef CARD_H
#define CARD_H 1

struct card {
	uint8_t suit; // 1: Diamonds, 2: Clubs, 3: Hearts, 4: Spades
	uint8_t rank; // 1: Ace, 2-10: Face Value, 11: Jack, 12: Queen, 13: King
	uint8_t unk1; // push size to mult of 4 bytes
	uint8_t unk2; // push size to mult of 4 bytes
};

/*
 * Create a new card with the given suit and rank.
 *
 * @param suit Suit of the card
 * @param rank Rank of the card
 * @return VA of new card. NULL if error
 */
extern struct card *create_card(uint8_t suit, uint8_t rank);

/*
 * Examine a card to see if it has the given rank.
 *
 * @param c Card to examine
 * @param rank Rank to use for matching
 * @return TRUE if rank matches, else FALSE or ERR_UNINITIALIZED_CARD on error
 */
extern int is_rank(struct card *c, uint8_t rank);

/*
 * Deallocate a card.
 *
 * @param c Card to deallocate
 */
extern void destroy_card(struct card *c);

/**
 * Check to see if the suit is valid.
 *
 * @param suit Suit to test.
 * @return TRUE if valid, else FALSE
 */
extern int is_valid_suit(uint8_t suit);

/**
 * Check to see if the rank is valid.
 *
 * @param rank Rank to test.
 * @return TRUE if valid, else FALSE
 */
extern int is_valid_rank(uint8_t rank);

/**
 * Compare 2 cards to see if they are equal rank and suit.
 *
 * @param c1 Card 1
 * @param c2 Card 2
 * @return TRUE if equal, else FALSE
 */
extern int is_equal(struct card *c1, struct card *c2);

/**
 * Test if arrays cards1 and cards2 contain the same number of cards and 
 * the same set of cards.
 *
 * Note: This function expects cards1 and cards2 to have at least
 * allocated space for one (1) struct card *.
 * Also expects cards1 and cards2 to have at least qty allocated spaces for 
 * struct card * when qty > 0.
 *
 * @param cards1 Array of cards
 * @param cards2 Array of cards
 * @param qty Number of cards expected in both arrays
 * @return TRUE if cards1 and cards2 have the same cards, FALSE if not.
 */
extern int is_set_equal(struct card *cards1[], struct card *cards2[], uint8_t qty);

#endif