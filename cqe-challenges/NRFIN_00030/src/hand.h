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


#ifndef HAND_H
#define HAND_H 1

struct hand {
	uint8_t count;
	uint8_t unk1; // push size to mult of 4 bytes
	uint8_t unk2; // push size to mult of 4 bytes
	uint8_t unk3; // push size to mult of 4 bytes
	struct card *cards[52];
};

/**
 * Create a new empty hand.
 *
 * @return VA of new hand.
 */
extern struct hand *create_hand();

/**
 * Consolidate hand to reomve empty spaces between cards in card array.
 *
 * @param h A hand
 */
extern void consolidate_hand(struct hand *h);

/**
 * Add card to hand.
 *
 * @param h A hand
 * @param c A card
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_HAND_FULL on error
 */
extern int add_card_to_hand(struct hand *h, struct card *c);

/**
 * Add multiple cards to hand.
 *
 * @param h A hand
 * @param cards[] Array of card pointers
 * @param qty Number of cards in cards array
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, 
 * 	ERR_INVALID_QTY, ERR_HAND_FULL on error
 */
extern int add_cards_to_hand(struct hand *h, struct card *cards[], uint8_t qty);

/**
 * Remove card from hand.
 *
 * @param h A hand
 * @param idx Index of card to remove from hand (0-51)
 * @param c Pointer to a card pointer to return the removed card.
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_INVALID_CARD,
 	ERR_NULL_CARD on error
 */
extern int rm_card_from_hand(struct hand *h, uint8_t idx, struct card **c);

/**
 * Count how many cards in hand have the given rank.
 *
 * @param h A hand
 * @param rank Rank of cards to search for in hand
 * @return Number of cards matching rank (0/1/2/3/4), or
 *	ERR_UNINITIALIZED_HAND on error
 */
extern int qty_of_rank_in_hand(struct hand *h, uint8_t rank);

/**
 * Get all cards of rank from hand.
 *
 *  Return 0 to 4 struct card pointers via the cards array.
 *  And the number of cards via the return value.
 *
 * @param h A hand
 * @param rank Rank of cards to serach for in hand
 * @param cards[] Array to store card pointers.
 * @return Number of cards matching rank (0/1/2/3/4) or 
 *	ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_INVALID_CARD on error
 */
extern int get_all_of_rank_from_hand(struct hand *h, uint8_t rank, struct card *cards[]);

/**
 * Get the number of cards in the hand.
 *
 * @param h A hand
 * @return Number of cards in the hand (0 - 45) or ERR_UNINITIALIZED_HAND on error
 */
extern int get_count_cards_in_hand(struct hand *h);

/**
 * Select a random card in hand and return its rank.
 *
 * @param h A hand
 * @return Rank of card or ERR_UNINITIALIZED_HAND, ERR_HAND_EMPTY on error
 */
extern int get_rank_of_random_card_in_hand(struct hand *h);

/**
 * Check if the hand has zero cards.
 *
 * @param h A hand
 * @return TRUE if empty, FALSE if not or ERR_UNINITIALIZED_HAND on error
 */
extern int is_hand_empty(struct hand *h);

/**
 * Get the card most recently added to the hand.
 *
 * @param h A hand
 * @param c A pointer to a card pointer to store result
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_HAND_EMPTY on error
 */
extern int get_latest_card(struct hand *h, struct card **c);

#endif