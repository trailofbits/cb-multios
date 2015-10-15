/*

Author: Debbie Nuttall <debbie@cromulence.co>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef CASINO_H
#define CASINO_H

#define BREAK_THE_BANK 5000

#define PLAYER_NAME_LENGTH 32

typedef struct player_info_s{
	int number;
	char name[PLAYER_NAME_LENGTH];
	int blackjack_score;
	int poker_score;
	int slots_score;
	int wallet;
	struct player_info_s *next;
} player_info;


enum payout_names {
	SLOTS_COLUMN_MATCH,
	SLOTS_ROW_MATCH,
	POKER_ROYAL_FLUSH,
	POKER_STRAIGHT_FLUSH,
	POKER_FLUSH,
	POKER_FOUR_OF_A_KIND,
	POKER_FULL_HOUSE,
	POKER_TWO_PAIR,
	POKER_THREE_OF_A_KIND,
	POKER_JACKS_OR_BETTER,
	POKER_STRAIGHT,
	BLACKJACK_PUSH,
	BLACKJACK_BLACKJACK,
	BLACKJACK_WIN,
	NUMBER_OF_PAYOUTS };

extern int payouts[NUMBER_OF_PAYOUTS];

#endif // CASINO_H
