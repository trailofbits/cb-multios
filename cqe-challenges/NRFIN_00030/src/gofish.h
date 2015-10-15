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


#ifndef GOFISH_H
#define GOFISH_H 1

#include "deck.h"
#include "player.h"

struct game_state {
	uint8_t whos_turn;
	uint8_t unk1; // push size to mult of 4 bytes
	uint8_t unk2; // push size to mult of 4 bytes
	uint8_t unk3; // push size to mult of 4 bytes
	struct deck *pool;
	struct player *p_remote;
	struct player *p_bot;
};

/**
 * Create a new game.
 *
 * @param player_name Name of remote player
 * @return Pointer to the game state.
 */
extern struct game_state *create_game(char *player_name);

/**
 * Deal the initial hand to each player.
 *
 * @param game Pointer to the game state.
 * @return SUCCESS or ERR_UNINITIALIZED_HAND, ERR_NULL_CARD, ERR_HAND_FULL,
 *	ERR_UNINITIALIZED_PLAYER, ERR_UNINITIALIZED_DECK, ERR_UNINITIALIZED_GAME
 *  on error 
 */
extern int deal(struct game_state *game);

/**
 * Get number of cards in initial hand.
 *
 * @return Number of cards in initial hand.
 */
extern int get_hand_size();

/**
 * The player has finished their turn, so update whos_turn
 *  to be the next player.
 *
 * @param game Pointer to the game state.
 * @return SUCCESS or ERR_UNINITIALIZED_GAME on error
 */
extern int turn_complete(struct game_state *game);

/**
 * Check to see if this turn is the player's turn.
 *
 * @param game Pointer to the game state.
 * @return TRUE if yes, FALSE if no or ERR_UNINITIALIZED_GAME on error
 */
extern int is_player_turn(struct game_state *game);

/**
 * Check to see if the game is over.
 *
 * @param game Pointer to the game state.
 * @return TRUE if yes, FALSE if no or ERR_UNINITIALIZED_GAME on error
 */
extern int is_game_over(struct game_state *game);


#endif
