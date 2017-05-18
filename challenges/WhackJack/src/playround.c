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


#include "cgc_service.h"
#include "cgc_stdio.h"
#include "cgc_stdlib.h"
#include "cgc_input.h"

char *cardType[] = { "", "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

int cgc_score_cards(unsigned char *cards) {

int score1 = 0;
int ace = 0;
int i;

	for (i=0; i < MAX_CARDS;++i) {

		if (cards[i] > 1 && cards[i] < 10) {

			score1 += cards[i];

		}
		else if (cards[i] >= 10) {

			score1 += 10;
		}
		else if (cards[i] == 1) {

			ace += 1;
			score1 += 11;

		}

	}

	while (score1 > 21 && ace > 0) {
		score1 -= 10;
		ace--;
	}

	return score1;
}



void cgc_show_cards(unsigned char *dealer_cards, playerInfoType *playerList) {

int i;
int x;

	
	cgc_printf("Dealer:");

	for (i=0; i< MAX_CARDS && dealer_cards[i]!= 0; ++i)
		cgc_printf(" $s", cardType[dealer_cards[i]]);

	cgc_printf(" ($d)\n", cgc_score_cards(dealer_cards));

	for (i = 0; i < MAX_PLAYERS; ++i) {

		if (playerList[i].player_name[0] != 0) {

			cgc_printf("$s:", playerList[i].player_name);

			for (x=0; x < MAX_CARDS && playerList[i].cards[x] != 0; ++x)
				cgc_printf(" $s", cardType[playerList[i].cards[x]]);

			cgc_printf(" ($d)\n", cgc_score_cards(playerList[i].cards));
		}

	}	


}


int cgc_play_round(playerInfoType *playerList, unsigned short *next_card) {

unsigned short *deck;
int i;
int x;
unsigned char dealer_cards[MAX_CARDS];
char buffer[5];
int score;
int finished;
int dealer_score;
int player_count;
int bet;

	for (i=0; i < MAX_CARDS; ++i)
		dealer_cards[i] = 0;

	player_count = 0;

	for (i=0; i < MAX_PLAYERS; ++i) {
	
		if (playerList[i].player_name[0] != 0)
			++player_count;

		for (x = 0; x < MAX_CARDS; ++x)
			playerList[i].cards[x] = 0;

	}

	if (player_count == 0) {

		cgc_printf("No players\n");
		return -1;
	}

 	// Now each player gets to play in turn
	for (i = 0; i < MAX_PLAYERS; ++i) {

		if (playerList[i].player_name[0] == 0)
			continue;

		finished = 0;
		cgc_printf("Player: $s\n", playerList[i].player_name);

		cgc_printf("Place your bet (1-$d)\n", playerList[i].funds);

		if (playerList[i].computerPlayer==1) {

			playerList[i].bet = COMPUTER_PLAYER_BET;

		}
		else {

			if(cgc_receive_until( buffer, '\n', sizeof(buffer) ) == 0)
				return -1;

			bet = cgc_atoi(buffer);

			playerList[i].bet = bet;
		}
	}

	// first deal out the initial cards
	deck = (unsigned short *)RANDOM_CARD_DATA;

	// dealer gets a card
	dealer_cards[0] = (deck[*next_card] % 13) +1;
	*next_card = (*next_card < CARD_DATA_LEN - 1) ? (*next_card + 1) : 0;

	// now around the table each player gets a card
	for (i = 0; i < MAX_PLAYERS; ++i) {

		if (playerList[i].player_name[0] != 0) {

			playerList[i].cards[0] = (deck[*next_card] % 13) +1;
			*next_card = (*next_card < CARD_DATA_LEN - 1) ? (*next_card + 1) : 0;

		}

	}

	// dealers second card
	dealer_cards[1] = (deck[*next_card] % 13) +1;
	*next_card = (*next_card < CARD_DATA_LEN - 1) ? (*next_card + 1) : 0;

	// around the table once more
	for (i = 0; i < MAX_PLAYERS; ++i) {

		if (playerList[i].player_name[0] != 0) {

			playerList[i].cards[1] = (deck[*next_card] % 13) +1;
			*next_card = (*next_card < CARD_DATA_LEN - 1) ? (*next_card + 1) : 0;


		}

	}

 	cgc_show_cards(dealer_cards, playerList);
	//cgc_printf("Dealer shows: $d $d\n", dealer_cards[0], dealer_cards[1]);


 	// Now each player gets to play in turn
	for (i = 0; i < MAX_PLAYERS; ++i) {

		if (playerList[i].player_name[0] == 0)
			continue;

		finished = 0;
		cgc_printf("Player: $s\n", playerList[i].player_name);

		while (!finished) {

			for (x=0; x < MAX_CARDS && playerList[i].cards[x] != 0; ++x)
				cgc_printf("$s ", cardType[playerList[i].cards[x]]);		

			cgc_printf("($d)\n", cgc_score_cards(playerList[i].cards));	

			if (playerList[i].useHints == 1) {

				cgc_printf("Do you want a hint?\n");

				if(cgc_receive_until( buffer, '\n', sizeof(buffer) ) == 0)
					return -1;

				if (buffer[0] == 'y' || buffer[0] == 'Y') {

					buffer[0] = playerList[i].whackJackAlgorithm(dealer_cards[1], playerList[i].cards);


					switch (buffer[0]) {

						case 'S':

							cgc_printf("You should Stand\n");
							break;

						case 'H':

							cgc_printf("You should Hit\n");
							break;

						default:
							cgc_printf("Uh.... it didn't say\n");

					} //switch


				} // if  yes to hints

			} // if useHints

			cgc_printf("Do you wish to H)it or S)tand\n");

			if (playerList[i].computerPlayer==1) {

				buffer[0] = playerList[i].whackJackAlgorithm(dealer_cards[1], playerList[i].cards);


			}
			else {
				if(cgc_receive_until( buffer, '\n', sizeof(buffer) ) == 0)
					return -1;
			}
			if (buffer[0] == 'S')
				finished = 1;
			else if (buffer[0] == 'H') {

				playerList[i].cards[x] = (deck[*next_card] % 13) +1;
				*next_card = (*next_card < CARD_DATA_LEN - 1) ? (*next_card + 1) : 0;

				cgc_printf("$s draws $s\n", playerList[i].player_name, cardType[playerList[i].cards[x]]);
				score = cgc_score_cards(playerList[i].cards);

				if (score > 21)
					finished = 1;
			}

		} // while

	} // for (i)


	finished = 0;
	x = 0;

	while(dealer_cards[x] != 0)
		++x;

	while (!finished) {

		dealer_score = cgc_score_cards(dealer_cards);

		if ( dealer_score > 16 )
			break;

		dealer_cards[x] = (deck[*next_card] % 13) +1;
		cgc_printf("Dealer draws $s\n", cardType[dealer_cards[x]]);

		*next_card = (*next_card < CARD_DATA_LEN - 1) ? (*next_card + 1) : 0;
		++x;

	}


	for (i = 0; i < MAX_PLAYERS; ++i) {

		if (playerList[i].player_name[0] == 0)
			continue;

		cgc_printf("$s: ", playerList[i].player_name);

		score = cgc_score_cards(playerList[i].cards);

		if (dealer_score > 21 && score < 22) {
			cgc_printf("wins!\n");
			playerList[i].funds += playerList[i].bet;
			playerList[i].wins++;
		}
		else if ( score < 22 && score > dealer_score) {
			cgc_printf("wins!\n");
			playerList[i].wins++;
			playerList[i].funds += playerList[i].bet;
		}
		else if ( score == dealer_score)
			cgc_printf("pushes\n");
		else  {
			cgc_printf("loses\n");
			playerList[i].funds -= playerList[i].bet;
			playerList[i].losses++;

			if (playerList[i].funds == 0) {

				playerList[i].player_name[0] = 0;
				playerList[i].wins = 0;
				playerList[i].losses = 0;
				playerList[i].computerPlayer = 0;

			}
		}


	} // for (i)

	return 0;
}


