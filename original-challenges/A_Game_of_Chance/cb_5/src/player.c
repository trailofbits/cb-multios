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
#include "malloc.h"
#include "memcmp.h"

#include "card.h"
#include "player.h"

/* Commands to send to players */
const char START_ROUND[6] 		= {'\x08','\x88','\x88','\x88','\x88','\x08'};
const char END_ROUND[6] 		= {'\x80','\x88','\x88','\x88','\x88','\x80'};
const char GIVE_PLAYER_CARD[6] 	= {'\x1C','\xCC','\xCC','\xCC','\xCC','\x1C'};
const char SHOW_DEALT_CARDS[6] 	= {'\xCF','\xCC','\xCC','\xCC','\xCC','\xCF'};
const char GET_WAGER[6] 		= {'\xF1','\xAA','\xAA','\xAA','\xAA','\xF1'};
const char SHOW_ALL_WAGERS[6] 	= {'\xFF','\xAA','\xAA','\xAA','\xAA','\xFF'};
const char SHOW_RESULTS[6] 		= {'\xFF','\xFF','\x99','\xFF','\x99','\xFF'};
const char PAY_PLAYER[6] 		= {'\xCC','\xAA','\x55','\x44','\xEE','\xEE'};
const char PLAYER_QUIT[6] 		= {'\x22','\x22','\xEE','\x22','\xE7','\x77'};

/* Results */
enum {
	WIN = 1,
	LOSS = 7,
};

ssize_t wallet = INITIAL_CASH;
unsigned char players = 0;
unsigned int round_active = FALSE;
unsigned int bogus = 10;
size_t my_wager = 0;
const char *fp = (const char *)FLAG_PAGE;
size_t fp_idx = 0;

Card deal[2] = {0};

/**
 * Determine how much money to wager.
 */
size_t do_wager_ai(void) {
	size_t wager = 0;
	if ((2 == deal[0].value) || (3 == deal[0].value)) {
		return wager;
	}
	wager = (size_t)(unsigned char)fp[fp_idx];
	return wager;
}

/**
 * Update fp_idx and ensure it stays in the range 0-4095
 *
 * @param shift 	Amount to shift fp_idx
 */
void update_fp_idx(int shift) {
	int fp_idx_tmp = 0;
#ifdef PATCHED_1
	fp_idx_tmp = shift;
#else
	fp_idx_tmp = fp_idx + shift;
#endif
	DBG("fp_idx: %U, fp_idx_tmp: %I\n", fp_idx, fp_idx_tmp);
	// fp_idx = fp[fp_idx] + shift;
	if (4096 <= fp_idx_tmp) {
		fp_idx = (unsigned int)((int)fp_idx_tmp - (int)4096);
	} else if (0 > fp_idx_tmp) {
		fp_idx = (unsigned int)((int)4096 + (int)fp_idx_tmp);
	} else {
		fp_idx = (unsigned int)fp_idx_tmp;
	}
	DBG("fp_idx: %U\n", fp_idx);
}

/**
 * Mark start of round and receive the number of players
 */
void start_round(void) {
	char ack = bogus;

	RECV(READ_FD, (char *)&players, sizeof(players));
	deal[0].value = 0;
	deal[1].value = 0;

	round_active = TRUE;
	SEND(WRITE_FD, &ack, sizeof(char));
	DBG("Round started with %U players\n", players);
}

/**
 * Receive one dealt card
 */	
void get_card(void) {
	Card c;
	char c_num;

	RECV(READ_FD, (char *)&c, sizeof(Card));
	RECV(READ_FD, &c_num, sizeof(char));

	deal[c_num - 1].value = c.value;
	DBG("Got card with value %U\n", c.value);
}

/**
 * View all dealt cards
 */
void view_dealt_cards(void) {
	Card cards[10] = {0};
	DBG("Viewing dealt cards\n");
	RECV(READ_FD, (char *)cards, sizeof(Card) * (players + 1));

	for (unsigned int pid = 1; pid <= players; pid++) {
		if (0 == cards[pid].value) {
			bogus++;
		}
	}
}

/**
 * Give wager
 */
void give_wager(void) {
	my_wager = do_wager_ai();

	SEND(WRITE_FD, (char *)&my_wager, sizeof(size_t));
	DBG("My wager: $%U\n", my_wager);
}

/**
 * View all wagers on table
 */
void view_wagers(void) {
	size_t wagers[10] = {0};

	DBG("Viewing wagers\n");
	RECV(READ_FD, (char *)wagers, sizeof(size_t) * (players + 1));

	for (unsigned int pid = 1; pid <= players; pid++) {
		if (0 == wagers[pid]) {
			bogus++;
		}

		if ((MY_ID == pid) && (my_wager != wagers[pid])) {
			DBG("Oddly, my wager given %U doesn't match what the dealer claims %U\n", my_wager, wagers[pid]);
			bogus++;
		}
	}
}

/**
 * View final results
 */
void view_results(void) {
	size_t results[10] = {0};

	DBG("Viewing Results\n");
	RECV(READ_FD, (char *)results, sizeof(size_t) * (players + 1));

	for (unsigned int pid = 1; pid <= players; pid++) {
		if (0 == results[pid]) {
			bogus++;
		}
		if (MY_ID == pid) {
			if (WIN == results[pid]) {
				update_fp_idx(WIN_SHIFT);
				DBG("I win. New fp_idx %U\n", fp_idx);
			} else {
				update_fp_idx(LOSS_SHIFT);
				DBG("I lost. New fp_idx %U\n", fp_idx);
			}
		}
	}
}

/**
 * Pay or collect money from dealer
 */
void exchange_money(void) {
	ssize_t amount = 0;
	RECV(READ_FD, (char *)&amount, sizeof(amount));
	wallet += amount;
	DBG("Exchanged $%I, New wallet balance: $%I\n", amount, wallet);
}

/**
 * End current round
 */
void end_round(void) {
	char ack = bogus;

	round_active = FALSE;
	players = 0;

	SEND(WRITE_FD, &ack, sizeof(char));
	DBG("Ended round\n");
}

/**
 * Tell player to quit
 *
 * @param pid 		Player ID to contact
 */
void i_quit(void) {
	char ack = bogus;

	SEND(WRITE_FD, &ack, sizeof(char));
	DBG("I quit\n");
}

/**
 * Process a command from the CRS
 *
 * @return SUCCESS on success, else val < 0 on error or quit.
 */
ssize_t process(void) {
	int ret = SUCCESS;

	char cmd[7] = {0};

    RECV(READ_FD, cmd, sizeof(cmd) - 1);
    DBG("recv'd cmd: %S.\n", cmd);

    if (0 == memcmp((char *)START_ROUND, cmd, sizeof(START_ROUND))) {
    	start_round();
    } else if (0 == memcmp((char *)END_ROUND, cmd, sizeof(END_ROUND))) {
    	end_round();
    } else if (0 == memcmp((char *)GIVE_PLAYER_CARD, cmd, sizeof(GIVE_PLAYER_CARD))) {
    	get_card();
    } else if (0 == memcmp((char *)SHOW_DEALT_CARDS, cmd, sizeof(SHOW_DEALT_CARDS))) {
    	view_dealt_cards();
    } else if (0 == memcmp((char *)GET_WAGER, cmd, sizeof(GET_WAGER))) {
    	give_wager();
    } else if (0 == memcmp((char *)SHOW_ALL_WAGERS, cmd, sizeof(SHOW_ALL_WAGERS))) {
    	view_wagers();
    } else if (0 == memcmp((char *)SHOW_RESULTS, cmd, sizeof(SHOW_RESULTS))) {
    	view_results();
    } else if (0 == memcmp((char *)PAY_PLAYER, cmd, sizeof(PAY_PLAYER))) {
    	exchange_money();
    } else if (0 == memcmp((char *)PLAYER_QUIT, cmd, sizeof(PLAYER_QUIT))) {
    	i_quit();
    	ret = -2;
    }

	return ret;
}