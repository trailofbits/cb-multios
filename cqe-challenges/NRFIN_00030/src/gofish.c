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
#include <libcgc.h>
#include "libc.h"
#include "common.h"
#include "gofish.h"


struct game_state *create_game(char *player_name) {
	struct game_state *game = NULL;
	game = calloc(sizeof(struct game_state));

	game->whos_turn =  0; // remote player goes first
	uint8_t seed = 0;
	// would be a good vuln, but too easy for fuzzer to hit.
	if ('\0' != player_name[0]) {
		seed = player_name[0];
	}
	game->pool = get_shuffled_deck(seed); // seed: first byte of player_name
	game->p_remote = create_player(0, player_name);
	char *bot = NULL;
	bot = calloc(4);
	strncpy(bot, "Bot", 3);

	game->p_bot = create_player(1, bot);

	return game;
}

int deal(struct game_state *game) {
	if (NULL == game) {
		return ERR_UNINITIALIZED_GAME;
	}

	int ret = 0;

	for (uint8_t card_cnt = 0; card_cnt < get_hand_size(); card_cnt++) {
		ret = take_top_card(game->p_remote, game->pool);
		if (0 > ret) {
			return ret;
		}
		ret = take_top_card(game->p_bot, game->pool);
		if (0 > ret) {
			return ret;
		}
	}

	return SUCCESS;
}

int get_hand_size() {
	return 7;
}

int turn_complete(struct game_state *game) {
	if (NULL == game) {
		return ERR_UNINITIALIZED_GAME;
	}

	game->whos_turn = (game->whos_turn + 1) % 2;
	return SUCCESS;
}

int is_player_turn(struct game_state *game) {
	if (NULL == game) {
		return ERR_UNINITIALIZED_GAME;
	}

	// remote player is always player 0
	if (0 == game->whos_turn) {
		return TRUE;
	} else {
		return FALSE;
	}
}

int is_game_over(struct game_state *game) {
	if (NULL == game) {
		return ERR_UNINITIALIZED_GAME;
	}

	if ((TRUE == is_deck_empty(game->pool)) &&
		(TRUE == is_player_hand_empty(game->p_remote)) &&
		(TRUE == is_player_hand_empty(game->p_bot))) {
		return TRUE;
	} else {
		return FALSE;
	}
}
