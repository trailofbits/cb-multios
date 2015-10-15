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

#ifndef RXTX_H
#define RXTX_H 1

#include "card.h"
#include "hand.h"
#include "gofish.h"

/**
 * Recieve name of remote player
 *
 * @param player_name Pointer to null terminated char buf holding name of remote player
 * @return SUCCESS or ERRNO_RECV, ERR_INVALID_XML on error
 */
extern int recv_player_name(char **player_name);

/**
 * Send 0 or more cards to remote player.
 * 
 * If qty is 0, the xml for a card is omitted, but the encapsulating xml is sent.
 *
 * @param cards An array of cards.
 * @param qty Quantity of cards to send.
 * @return SUCCESS or ERR_INVALID_XML on error
 */
extern int send_cards(struct card *cards[], uint8_t qty);

/**
 * Receive 0 or more cards from remote user.
 *
 * @param cards An array to hold cards
 * @param qty Number of cards to receive
 * @return Number of cards received or ERR_INVALID_XML,
 *	ERR_INVALID_CARD on error
 */
extern int recv_cards(struct card *cards[], uint8_t qty);

/**
 * Receive draw request from remote player.
 *
 * @return SUCCESS or ERR_INVALID_XML, ERRNO_RECV on error.
 */
extern int recv_draw_request();

/**
 * Send full hand to remote player.
 *
 * @param h A hand
 * @return SUCCESS or ERR_INVALID_XML on error
 */
extern int send_hand(struct hand *h);

/**
 * Send notice to tell remote player to go fish.
 *
 * @param qty Number of cards being sent; 0 for "Go Fish"
 */
extern void send_go_fish_notice(uint8_t qty);

/**
 * Receive go fish notice from remote player telling bot player to go fish.
 *
 * @return Number of cards being given (0 for "Go Fish") or
 *	ERR_INVALID_XML, ERRNO_RECV on error.
 */
extern int recv_go_fish_notice();

/**
 * Receive request from remote player to fish for a card in the pool.
 *
 * @return SUCCESS or ERR_INVALID_XML, ERRNO_RECV on error.
 */
extern int recv_fish_request();

/**
 * Receive cards from remote player and match with expected cards.
 *
 * @param cards Array of expected cards.
 * @param qty Quantity of cards to receive.
 * @return TRUE if received cards match cards, else FALSE
 */
extern int recv_and_match_cards(struct card *cards[], uint8_t qty);

/**
 * Receive remote players shown card and compare it with the expected
 * card c.
 *
 * @param cards Cards array having one card to use for comparison.
 * @return TRUE if received cards match cards, else FALSE
 */
// extern int recv_and_match_shown_card(struct card *cards[]);

/**
 * Send shown card to remote player.
 *
 * Note: When no card is to be shown, c is NULL.
 *
 * @param cards Cards array holding a card to send to remote player or 
 *	NULL if no card is to be shown.
 * @return SUCCESS or ERR_INVALID_XML on error
 */
// extern int send_show_card(struct card *cards[]);

/**
 * Receive remote players ask.
 *
 * Note: When no card is to be shown, c is NULL, send card with rank/suit of 0.
 *
 * @return Card rank or ERR_INVALID_XML, ERR_INVALID_RANK,
 *	ERRNO_RECV on error
 */
extern int recv_ask_and_get_rank();

/**
 * Send bot ask to remote player.
 *
 * @param rank Rank of card(s) bot player is asking for
 */
extern void send_ask(uint8_t rank);

/**
 * Receive count of books played by remote player on this turn.
 *
 * @param count Expected number of books
 * @return TRUE if player count matches expected count, else FALSE, or 
 *	ERR_INVALID_XML, ERRNO_RECV on error
 */
extern int recv_and_match_count_books_played(uint8_t count);

/**
 * Send count of books played by bot player on this turn.
 *
 * @param count Number of books played
 */
extern void send_count_books_played(uint8_t count);

/**
 * Send notice to remote player that it is their turn.
 *
 * @param p_id Player ID of player whose turn it is
 */
extern void send_turn_notice(uint8_t p_id);

/**
 * Send initial hand to remote player.
 *
 * @param game Game state
 * @return SUCCESS or ERR_INVALID_XML on error
 */
extern int send_initial_hand_to_player(struct game_state *game);

/**
 * Send final results to remote player.
 *
 * @param game Game state
 */
extern void send_final_results(struct game_state *game);

/**
 * Send error message to remote player.
 *
 * @param err_code Error code
 */
extern void send_error(int8_t err_code);

#endif