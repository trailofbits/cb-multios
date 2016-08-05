/*

Author: Steve Wood <swood@cromulence.com>

Copyright (c) 2016 Cromulence LLC

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

#include <libcgc.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "service.h"
#include "input.h"

// algo 1
char matchDealer(unsigned char dealer_show_card, unsigned char *player_cards) {

int player_score;


	player_score = score_cards(player_cards);

	if (player_score > 16)
		return('S');
	else
		return('H');


}

// algo 4
char neverBustAlgo( unsigned char dealer_show_card, unsigned char *player_cards ) {

int player_score;

	player_score = score_cards(player_cards);

 	if (player_score > 11 )
 		return 'S';
 	else
 		return 'H';

}

// algo 2
char basicAlgo( unsigned char dealer_show_card, unsigned char *player_cards ) {


int i;
int hard;
int player_score;
char answer;

	hard = 1;

	for (i = 0; i < MAX_CARDS && player_cards[i] != 0; ++i) {

		if (player_cards[i] == 1) {

			hard = 0;
		}
	}

	player_score = score_cards(player_cards);

	switch (hard) {



		case 1:

			if (player_score < 12)
				answer = 'H';

			else if (player_score > 16)
				answer = 'S';

			else if (player_score > 11 && player_score < 17 && dealer_show_card > 6)
				answer = 'H';

			else if (player_score == 12 && dealer_show_card < 4)
				answer = 'H';

			else
				answer = 'S';

			break;

		case 0:

			if (player_score < 18)
				answer = 'H';

			else if (player_score == 18 && dealer_show_card > 8 && dealer_show_card < 11)
				answer = 'H';

			else
				answer = 'S';

			break;
	}

	return answer;
}


// algo 3
char simpleAlgo( unsigned char dealer_show_card, unsigned char *player_cards ) {

int i;
int hard;
int player_score;


	for (i = 0; i < MAX_CARDS && player_cards[i] != 0; ++i) {

		if (player_cards[i] == 1) {

			hard = 0;
		}
	}

	player_score = score_cards(player_cards);

	if (hard) {


		if (player_score < 12)
			return 'H';

		else if (player_score > 16)
			return 'S';

		else if (dealer_show_card < 7)
			return 'S';

		else
			return 'H';

	}
	else {

		if (player_score < 18 )
			return 'H';

		else if (player_score == 18 && dealer_show_card < 7)
			return 'S';

		else if (player_score == 18 && dealer_show_card > 7)
			return 'H';

		else 
			return 'S';

	}

}

// algo 5
char superDuperAlgo( unsigned char dealer_show_card, unsigned char *player_cards ) {

int i;
int hard;
int player_score;

char decision_table_hard[14][21] = { 	'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'H','S', 'S', 'S' };

char decision_table_soft[14][21] = { 	'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S',
										'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H', 'H', 'H','H', 'H', 'S','S', 'S', 'S' };

	hard = 1;

	for (i = 0; i < MAX_CARDS && player_cards[i] != 0; ++i) {

		if (player_cards[i] == 1) {

			hard = 0;
		}

	}

	player_score = score_cards(player_cards);

	if (hard) {

		return decision_table_hard[dealer_show_card][player_score];
	}
	else {

		return decision_table_soft[dealer_show_card][player_score];
	}



}



