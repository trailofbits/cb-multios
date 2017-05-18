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
#include "cgc_gofish.h"
#include "cgc_operation.h"
#include "cgc_rxtx.h"

struct game_state *game = NULL;

/**
 * If the remote player has an empty hand, process
 * the player's request to draw a new hand.
 *
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_HAND_FULL,
 *	ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_DECK, ERR_INVALID_QTY,
 *	ERR_INVALID_XML, ERRNO_RECV on error 
 */
static int cgc_process_remote_player_empty_hand() {
	int ret = SUCCESS;
	if (TRUE == cgc_is_player_hand_empty(game->p_remote)) {
		if (SUCCESS != (ret = cgc_recv_draw_request())) {return ret;}
		ret = cgc_draw_new_hand(game->p_remote, game->pool, cgc_get_hand_size());
		// when pool doesn't have enough cards, get ERR_NULL_CARD, which is ok
		if ((0 > ret) && (ERR_NULL_CARD != ret)) {
			return ret;
		} else {
			ret = SUCCESS;
		}
		cgc_send_hand(game->p_remote->h);
	}
	return ret;
}

/**
 * If the bot player has an empty hand, process drawing a new hand.
 *
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_HAND_FULL,
 *	ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_DECK, ERR_INVALID_QTY on error 
 */
static int cgc_process_bot_player_empty_hand() {
	int ret = SUCCESS;
	if (TRUE == cgc_is_player_hand_empty(game->p_bot)) {
		ret = cgc_draw_new_hand(game->p_bot, game->pool, cgc_get_hand_size());
		if ((0 <= ret) || (ERR_NULL_CARD == ret)) {ret = SUCCESS;}
	}
	return ret;
}

/**
 * When remote player has to go fish, process their notification
 * and subsequent fishing action.
 *
 * @return SUCCESS or ERR_INVALID_CARD, ERR_INVALID_XML, ERRNO_RECV, 
 *	ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_HAND_FULL,
 *	ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_DECK, 
 *	ERR_UNINITIALIZED_ARRAY on error
 */
static int cgc_process_remote_player_fishing(uint8_t rank) {
	int ret = 0;
	struct card *c[1] = {0};

	if (SUCCESS != (ret = cgc_recv_fish_request())) {return ret;}

	if (0 == game->pool->count) { // pool is out of cards
		cgc_send_cards(c, 0);
	} else {
		if (SUCCESS != (ret = cgc_take_top_card(game->p_remote, game->pool))) {return ret;}
		if (SUCCESS != (ret = cgc_get_players_newest_card(game->p_remote, c))) {return ret;}
		cgc_send_cards(c, 1);
		if (rank == c[0]->rank) {
			ret = cgc_recv_and_match_cards(c, 1);
		} else {
			c[0] = NULL;
			ret = cgc_recv_and_match_cards(c, 0);
		}
		if (FALSE == ret) {
			ret = ERR_INVALID_CARD;
		} else {
			ret = SUCCESS;
		}

	}

	return ret;
}

/**
 * Process bot player going fishing
 *
 * @return SUCCESS or ERR_INVALID_CARD, ERR_INVALID_XML, ERRNO_RECV, 
 *	ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_HAND_FULL,
 *	ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_DECK, 
 *	ERR_UNINITIALIZED_ARRAY on error
 */
static int cgc_process_bot_player_fishing(uint8_t rank) {
	int ret = 0;
	struct card *c[1] = {0};

	if (0 != game->pool->count) { // only fish if there are cards in the pool
		if (SUCCESS != (ret = cgc_take_top_card(game->p_bot, game->pool))) {return ret;}
		if (SUCCESS != (ret = cgc_get_players_newest_card(game->p_bot, c))) {return ret;}
		if (rank == c[0]->rank) {
			cgc_send_cards(c, 1);
		} else {
			cgc_send_cards(c, 0);
		}
	}
	return SUCCESS;
}

/**
 * Process bot player giving cards to remote player.
 *
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, 
 * 	ERR_INVALID_QTY, ERR_HAND_FULL on error
 */
static int cgc_process_remote_player_accept_cards(struct card *cards[], uint8_t qty) {
	int ret = 0;

	cgc_send_cards(cards, qty);

	return cgc_accept_cards(game->p_remote, cards, qty);
}

/**
 * Process remote player giving cards to bot player.
 *
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, 
 * 	ERR_INVALID_QTY, ERR_HAND_FULL, ERR_INVALID_CARD on error
 */
static int cgc_process_bot_player_accept_cards(struct card *cards[], uint8_t qty) {
	int ret = 0;
	if (TRUE != (ret = cgc_recv_and_match_cards(cards, qty))) {
		if (FALSE == ret) {
			ret = ERR_INVALID_CARD;
		}
		goto bail;
	}

	ret = cgc_accept_cards(game->p_bot, cards, qty);
bail:

	return ret;
}

/**
 * Process remote player asking bot player for cards of rank.
 *
 * @return SUCCESS or ERR_INVALID_XML, ERR_INVALID_RANK,
 *	ERRNO_RECV, ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, 
 * 	ERR_INVALID_QTY, ERR_HAND_FULL, ERR_INVALID_CARD, 
 *	ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_DECK, 
 *	ERR_UNINITIALIZED_ARRAY on error
 */
static int cgc_process_remote_player_ask() {
	int rank = 0;
	int qty = 0;
	int ret = 0;
	struct card *cards[4] = {0};

	rank = cgc_recv_ask_and_get_rank();
	// when hand is empty, a rank of 0 is used for the ask, which is
	// an invalid rank. so expect ERR_INVALID_RANK in that case
	if (0 > rank) {
		if (FALSE == ((ERR_INVALID_RANK == rank) && (TRUE == cgc_is_hand_empty(game->p_remote->h)))) {
			return rank;
		}
	}
	qty = cgc_have_cards_of_rank(game->p_bot, rank, cards);

	if (0 <= qty) {
		cgc_send_go_fish_notice(qty);
	}

	if (0 == qty) { // go fish
		ret = cgc_process_remote_player_fishing(rank);
	} else if ((1 == qty) || (2 == qty) || (3 == qty)) { // take cards
		ret = cgc_process_remote_player_accept_cards(cards, qty);
	} else { // error
		ret = qty;
	}

	cgc_turn_complete(game);

	return ret;
}

/**
 * Process bot player asking remote player for cards of rank.
 *
 * @return SUCCESS or ERR_UNINITIALIZED_PLAYER, ERR_HAND_EMPTY,
 *	ERR_UNINITIALIZED_HAND, ERR_INVALID_CARD, ERR_INVALID_XML, ERRNO_RECV, 
 *	ERR_NULL_CARD, ERR_HAND_FULL, ERR_UNINITIALIZED_DECK, 
 *	ERR_UNINITIALIZED_ARRAY, ERR_INVALID_QTY on error
 */
static int cgc_process_bot_player_ask() {
	int rank = 0;
	int qty = 0;
	int ret = 0;
	struct card *cards[4] = {0};

	rank = cgc_select_random_card(game->p_bot);
	// when hand is empty rank will be ERR_HAND_EMPTY
	if ((0 > rank) && (ERR_HAND_EMPTY != rank)) {return rank;}

	if (ERR_HAND_EMPTY == rank) {
		rank = 0;
	}
	cgc_send_ask(rank);

	qty = cgc_have_cards_of_rank(game->p_remote, rank, cards);

	if (qty != (ret = cgc_recv_go_fish_notice())) {
		if (0 <= ret) {
			return ERR_INVALID_QTY;
		} else {
			return ret;
		}
	}

	if (0 == qty) { // go fish
		ret = cgc_process_bot_player_fishing(rank);
	} else if ((1 == qty) || (2 == qty) || (3 == qty)) { // take cards
		ret = cgc_process_bot_player_accept_cards(cards, qty);
	}

	cgc_turn_complete(game);

	return ret;
}

/**
 * Process remote player playing books.
 *
 * @return SUCCESS or ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_HAND, 
 *	ERR_NULL_CARD, ERR_INVALID_CARD, ERR_INVALID_QTY on error
 */
static int cgc_process_remote_player_books() {
	int ret = 0;

	if (0 > (ret = cgc_play_books(game->p_remote))) {return ret;}

	if (TRUE != (ret = cgc_recv_and_match_count_books_played((uint8_t)ret))) {
		if (FALSE == ret) {
			ret = ERR_INVALID_QTY;
		}
	} else {
		ret = SUCCESS;
	}

	return ret;
}

/**
 * Process bot player playing books.
 *
 * @return SUCCESS or ERR_UNINITIALIZED_PLAYER,
 *  ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_INVALID_CARD on error
 */
static int cgc_process_bot_player_books() {
	int ret = 0;

	if (0 > (ret = cgc_play_books(game->p_bot))) {return ret;}

	cgc_send_count_books_played((uint8_t)ret);

	return SUCCESS;
}

/**
 * Process a bot player turn.
 *
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_HAND_FULL,
 *	ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_DECK, ERR_INVALID_QTY, 
 *	ERR_HAND_EMPTY, ERR_INVALID_CARD, ERR_INVALID_XML, ERRNO_RECV,
 *	ERR_UNINITIALIZED_ARRAY on error
 */
static int cgc_do_bot_turn() {
	int ret = 0;
	cgc_send_turn_notice(1);

	if (SUCCESS != (ret = cgc_process_bot_player_empty_hand())) {return ret;}

	if (SUCCESS != (ret = cgc_process_bot_player_ask())) {return ret;}

	if (SUCCESS != (ret = cgc_process_bot_player_books())) {return ret;}

	return SUCCESS;
}

/**
 * Process a remote player turn.
 *
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_HAND_FULL,
 *	ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_DECK, ERR_INVALID_QTY,
 *	ERR_INVALID_XML, ERRNO_RECV, ERR_INVALID_RANK, ERR_INVALID_CARD, 
 *	ERR_UNINITIALIZED_ARRAY on error 
 */
static int cgc_do_player_turn() {
	int ret = 0;
	cgc_send_turn_notice(0);

	if (SUCCESS != (ret = cgc_process_remote_player_empty_hand())) {return ret;}

	if (SUCCESS != (ret = cgc_process_remote_player_ask())) {return ret;}

	if (SUCCESS != (ret = cgc_process_remote_player_books())) {return ret;}

	return SUCCESS;
}

/**
 * Process a player turn.
 *
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_HAND_FULL,
 *	ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_DECK, ERR_INVALID_QTY,
 *	ERR_INVALID_XML, ERRNO_RECV, ERR_INVALID_RANK, ERR_INVALID_CARD, 
 *	ERR_UNINITIALIZED_ARRAY, ERR_HAND_EMPTY on error
 */
static int cgc_do_turn() {
	int ret = SUCCESS;
	if (TRUE == cgc_is_player_turn(game)) {
		ret = cgc_do_player_turn();
	} else {
		ret = cgc_do_bot_turn();
	}
	return ret;
}


int cgc_play_game() {
	int ret = 0;
	char *player_name = NULL;

	if (SUCCESS != (ret = cgc_recv_player_name(&player_name))) {return ret;}

	game = cgc_create_game(player_name);

	if (SUCCESS != (ret = cgc_deal(game))) {return ret;}

	if (SUCCESS != (ret = cgc_send_initial_hand_to_player(game))) {return ret;}

	while (FALSE == cgc_is_game_over(game)) {
		if (SUCCESS != (ret = cgc_do_turn())) {
			return ret;
		}
	}

	cgc_send_final_results(game);

	return ret;
}
