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


#ifndef PLAYER_H
#define PLAYER_H 1

struct player {
	uint8_t id;
	uint8_t book_count;
	uint8_t unk1; // push size to mult of 4 bytes
	uint8_t unk2; // push size to mult of 4 bytes
	char *name;
	struct hand *h;
};

/**
 * Create a new player.
 *
 * @param id Player ID
 * @param name Player Name
 * @return VA of new player
 */
extern struct player *create_player(uint8_t id, char *name);

/**
 * Player takes top card from deck (dealing) or pool (fishing) to his hand.
 *
 * @param p Player which will add card to her hand.
 * @param d Deck from which the card will be drawn.
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_HAND_FULL,
 *	ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_DECK on error 
 */
extern int take_top_card(struct player *p, struct deck *d);

/**
 * Player is asked for cards of a given rank and gives them up if they have them.
 *
 * @param p Player
 * @param rank Card rank for player to search her hand for
 * @param cards Array to return cards (pointers to cards) in
 * @return Number of cards player has of given rank (0/1/2/3) or 
 *	ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, 
 *	ERR_INVALID_CARD on error
 */
extern int have_cards_of_rank(struct player *p, uint8_t rank, struct card *cards[]);

/**
 * Player searches their hand for books. If found, plays the books.
 *
 * @param p Player
 * @return Number of books played or ERR_UNINITIALIZED_PLAYER,
 *  ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_INVALID_CARD on error
 */
extern int play_books(struct player *p);

/**
 * Checks to see if the player has no cards left in their hand.
 *
 * @param p Player
 * @return TRUE if yes, FALSE if no, or ERR_UNINITIALIZED_PLAYER,
 *  ERR_UNINITIALIZED_HAND on error
 */
extern int is_player_hand_empty(struct player *p);

/**
 * Player takes qty cards from the pool (fishing) to his hand.
 *
 * @param p Player which will add card to her hand.
 * @param d Deck from which the card will be drawn.
 * @return Number of cards drawn or ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_HAND_FULL,
 *	ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_DECK, ERR_INVALID_QTY on error 
 */
extern int draw_new_hand(struct player *p, struct deck *d, uint8_t qty);

/**
 * Get the rank of a random card in players hand.
 *
 * @param p Player
 * @return Rank of card or ERR_UNINITIALIZED_PLAYER, ERR_HAND_EMPTY,
 *	ERR_UNINITIALIZED_HAND on error
 */
extern int select_random_card(struct player *p);

/**
 * Insert given cards into players hand.
 *
 * @param p Player receiving cards
 * @param cards Cards given to player
 * @param qty Number of cards given to player
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, 
 * 	ERR_INVALID_QTY, ERR_HAND_FULL on error
 */
extern int accept_cards(struct player *p, struct card *cards[], uint8_t qty);

/**
 * Get card player drew most recently.
 *
 * @param p Player
 * @param card An array to hold the card.
 * @return SUCCESS or ERR_UNINITIALIZED_ARRAY, ERR_UNINITIALIZED_PLAYER
 *  on error
 */
extern int get_players_newest_card(struct player *p, struct card *card[]);

#endif


