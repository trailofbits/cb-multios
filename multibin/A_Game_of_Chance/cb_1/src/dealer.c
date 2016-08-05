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

#include "deck.h"
#include "dealer.h"


/* Trigger byte in command buffer sent by the CRS */
#define DECK_BYTE 		'\x21'
#define DEAL_BYTE 		'\x5f'
#define DATA_BYTE 		'\x3c'
#define BALANCE_BYTE 	'\x42'
#define COUNT_BYTE 		'\x63'
#define QUIT_BYTE 		'\x51'

/* Index in command buffer for each byte */
enum {
	DECK_IDX,
	DEAL_IDX,
	DATA_IDX,
	BALANCE_IDX,
	COUNT_IDX,
	QUIT_IDX,
	TOTAL,
};

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

/* Buffers indexed by player ID (1 to PLAYER_COUNT) */
size_t results[PLAYER_COUNT + 1] 		= {0};	// results from most recent round
size_t wagers[PLAYER_COUNT + 1] 		= {0};	// wagers from most recent round
ssize_t house_payout[PLAYER_COUNT + 1]	= {0}; 	// net $ amt each player as won/lost


/* Comms with the players */

/**
 * Inform player that the round will start and the number of players
 *
 * @param pid 		Player ID to inform
 */
void start_round(unsigned int pid) {
	unsigned char pc = PLAYER_COUNT;
	char ack;
	DBG("Starting round for player %U\n", pid);
	SEND(WRITE_FD(pid), START_ROUND, sizeof(START_ROUND));
	SEND(WRITE_FD(pid), (char *)&pc, sizeof(unsigned char));
	RECV(READ_FD, &ack, sizeof(unsigned char));
}

/**
 * Deal one card to player
 *
 * @param pid 		Player ID to deal a card to
 * @param card 		Card to deal to player
 * @param c_num 	Number of card for this round (1 or 2)
 */	
void deal_card_to_player(unsigned int pid, Card *card, unsigned char c_num) {

	DBG("Dealing card %U with value %U to player %U\n", c_num, card->value, pid);
	SEND(WRITE_FD(pid), GIVE_PLAYER_CARD, sizeof(GIVE_PLAYER_CARD));
	SEND(WRITE_FD(pid), (char *)card, sizeof(Card));
	SEND(WRITE_FD(pid), (char *)&c_num, sizeof(char));
}

/**
 * Show all dealt cards to player
 *
 * @param pid 		Player ID to show
 * @param cards 	Array of cards to show to player
 * @param count 	Number of cards
 */
void show_dealt_cards_to_player(unsigned int pid, Card cards[], size_t count) {

	DBG("Showing player %U the dealt cards\n", pid);
	SEND(WRITE_FD(pid), SHOW_DEALT_CARDS, sizeof(SHOW_DEALT_CARDS));
	SEND(WRITE_FD(pid), (char *)cards, sizeof(Card) * count);
}

/**
 * Ask player for wager
 *
 * @param pid 		Player ID to ask for wager
 */
void get_wager_from_player(unsigned int pid) {

	DBG("Getting wager from player %U\n", pid);
	SEND(WRITE_FD(pid), GET_WAGER, sizeof(GET_WAGER));
	RECV(READ_FD, (char *)&wagers[pid], sizeof(size_t));
}

/**
 * Show all wagers to player
 *
 * @param pid 		Player ID to show
 */
void show_wagers_to_player(unsigned int pid) {

	DBG("Showing wagers to player %U\n", pid);
	SEND(WRITE_FD(pid), SHOW_ALL_WAGERS, sizeof(SHOW_ALL_WAGERS));
	SEND(WRITE_FD(pid), (char *)wagers, sizeof(wagers));
}

/**
 * Calculate results for this round
 *
 * @param cards1 	Array of first cards
 * @param cards2 	Array of second cards
 * @param count 	Number of cards
 */
void calculate_results(Card card1[], Card card2[], unsigned char count) {
	unsigned short max = 0;
	unsigned short sums[10] = {0};

	FOR_EACH_PLAYER
		sums[pid] = (unsigned short)card1[pid].value + (unsigned short)card2[pid].value;
		if (max < sums[pid]) {
	  		max = sums[pid];
		}
	}

	FOR_EACH_PLAYER
		if (max != sums[pid]) {
			DBG("Player %U - LOSS\n", pid);
			results[pid] = LOSS;
		} else {
			DBG("Player %U - WIN\n", pid);
			results[pid] = WIN;
		}
	}
}

/**
 * Show final results to player
 *
 * @param pid 		Player ID to show
 * @param results 	Array of results
 * @param count 	Number of results in array
 */
void show_results_to_player(unsigned int pid) {
	DBG("Showing results to player %U\n", pid);
	SEND(WRITE_FD(pid), SHOW_RESULTS, sizeof(SHOW_RESULTS));
	SEND(WRITE_FD(pid), (char *)results, sizeof(results));
}

/**
 * Pay or collect money from player
 *
 * @param pid 		Player ID to transact with
 * @param amount 	Amount of money to pay or colect
 */
void pay_player(unsigned int pid, ssize_t amount) {
	DBG("Exchanging %I cash with player %U\n", amount, pid);
	SEND(WRITE_FD(pid), PAY_PLAYER, sizeof(PAY_PLAYER));
	SEND(WRITE_FD(pid), (char *)&amount, sizeof(amount));
}

/**
 * End current round
 *
 * @param pid 		Player ID to contact
 */
void end_round(unsigned int pid) {
	char ack;
	DBG("Telling player %U end of round\n", pid);
	SEND(WRITE_FD(pid), END_ROUND, sizeof(END_ROUND));
	RECV(READ_FD, &ack, sizeof(unsigned char));
}

/**
 * Tell player to quit
 *
 * @param pid 		Player ID to contact
 */
void player_quit(unsigned int pid) {
	char ack;
	DBG("Telling player %U to quit\n", pid);
	SEND(WRITE_FD(pid), PLAYER_QUIT, sizeof(PLAYER_QUIT));
	RECV(READ_FD, &ack, sizeof(unsigned char));
}

/* Comms with the CRS */

/**
 * This will create the first deck as well as replace an existing deck.
 *
 * @return SUCCESS on success, else -1 (invalid count or card value)
 */
int new_deck(void) {
	unsigned int count;
	unsigned char *values;
	int ret = SUCCESS;

	RECV(STDIN, (void*)&count, sizeof(count));
	DBG("Recv'd card count for new deck: %U.\n", count);

	values = malloc(count * sizeof(unsigned char));
	MALLOC_OK(values);

	RECV(STDIN, (char *)values, sizeof(char) * count);

	ret = replace_deck(count, values);
	DBG("New deck %S active\n", ret == 0 ? "is" : "is not");

	return ret;
}

/**
 * Deal one round to the players
 *
 * @return SUCCESS on success, else -1
 */
int deal_one_round(void) {
	int ret = SUCCESS;
	if ((PLAYER_COUNT << 1) > get_deck_size()) {
		DBG("Cannot deal round, to few cards\n");
		return -1;
	}
	DBG("Dealing new round\n");

	FOR_EACH_PLAYER
		start_round(pid);
	}

	Card card1[PLAYER_COUNT + 1] = {0};
	Card card2[PLAYER_COUNT + 1] = {0};

	// deal one card to each player
	FOR_EACH_PLAYER
		card1[pid].value = get_next_card()->value;
		deal_card_to_player(pid, &card1[pid], 1);
	}

	// inform players about set of dealt cards
	FOR_EACH_PLAYER
		show_dealt_cards_to_player(pid, card1, sizeof(card1));
	}

	// get wager from each player
	// update wagers
	FOR_EACH_PLAYER
		get_wager_from_player(pid);
	}

	// inform players about all wagers
	FOR_EACH_PLAYER
		show_wagers_to_player(pid);
	}

	// deal second card to each player
	FOR_EACH_PLAYER
		card2[pid].value = get_next_card()->value;
		deal_card_to_player(pid, &card2[pid], 2);
	}

	// inform players about set of dealt cards
	FOR_EACH_PLAYER
		show_dealt_cards_to_player(pid, card2, sizeof(card2));
	}

	// update results (each idx tagged with WIN or LOSS)
	calculate_results(card1, card2, PLAYER_COUNT);

	// inform players about results
	FOR_EACH_PLAYER
		show_results_to_player(pid);
	}

	// give/take money from each player (+/- wager)
	// update house_payout
	FOR_EACH_PLAYER
		if (WIN == results[pid]) {
			house_payout[pid] += wagers[pid];
			pay_player(pid, wagers[pid]);
		} else {
			house_payout[pid] -= wagers[pid];
			pay_player(pid, -wagers[pid]);
		}
	}

	FOR_EACH_PLAYER
		end_round(pid);
	}

	return ret;
}

/**
 * Send the data from the latest round to the CRS
 * (wagers and results)
 *
 * @return SUCCESS
 */
int get_round_data(void) {
	DBG("Getting round data\n");
	// send wagers
	SEND(STDOUT, (void *)&wagers, sizeof(wagers));
	// send results
	SEND(STDOUT, (void *)&results, sizeof(results));

	return SUCCESS;
}

/**
 * Send the house payout amounts to the CRS
 *
 * @return SUCCESS
 */
int get_balances(void) {
	DBG("Getting balances\n");
	SEND(STDOUT, (void *)&house_payout, sizeof(house_payout));

	return SUCCESS;
}

/**
 * Send the number of players to the CRS
 *
 * @return SUCCESS
 */
int get_player_count(void) {
	DBG("Getting player count\n");
	size_t pc = PLAYER_COUNT;

	SEND(STDOUT, (void *)&pc, sizeof(int));

	return SUCCESS;
}

/**
 * Send the quit command to each player and then exit
 *
 * @return SUCCESS on success, else -1 on error
 */
int quit(int ret) {
#ifdef DEBUG
	if (-1 == ret) {
		DBG("Time to quit\n");
	} else {
		DBG("Quitting due to invalid cmd\n");
	}
#endif
	FOR_EACH_PLAYER
		player_quit(pid);
	}

	return SUCCESS;
}

/**
 * Process a command from the CRS
 *
 * @return SUCCESS on success, else val < 0 on error or quit.
 */
ssize_t process(void) {
	int ret = -2;

	char cmd[7] = {0};

    RECV(STDIN, cmd, sizeof(cmd)-1);
    DBG("Recv'd cmd: %S.\n", cmd);
    if (DECK_BYTE == cmd[DECK_IDX]) {
    	ret = new_deck();
    } else if (DEAL_BYTE == cmd[DEAL_IDX]) {
    	ret = deal_one_round();
    } else if (DATA_BYTE == cmd[DATA_IDX]) {
    	ret = get_round_data();
    } else if (BALANCE_BYTE == cmd[BALANCE_IDX]) {
    	ret = get_balances();
    } else if (COUNT_BYTE == cmd[COUNT_IDX]) {
    	ret = get_player_count();
    } else if (QUIT_BYTE == cmd[QUIT_IDX]) {
    	ret = -1;
    }

    if (0 > ret) { // quit on error or quit cmd
    	quit(ret);
    }

	return ret;
}