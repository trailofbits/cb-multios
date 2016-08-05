
/*

Author: Steve Wood <swood@cromulence.com>

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

#ifndef SERVICE_H
#define SERVICE_H

#define RANDOM_CARD_DATA 0x4347C000
#define CARD_DATA_LEN 2048


#define MAX_PLAYERS 8
#define MAX_NAME_LEN 12
#define MAX_CARDS 10
#define COMPUTER_PLAYER_BET 5

typedef struct playerInfo {

	char player_name[MAX_NAME_LEN];
	char (* whackJackAlgorithm)(unsigned char, unsigned char *);
	unsigned int funds;
	unsigned char cards[MAX_CARDS];
	unsigned char computerPlayer; // 0 human, 1 computer
	unsigned char computerMethod;
	unsigned char useHints;
	unsigned char hintsMethod;
	unsigned int wins;
	unsigned int losses;
	unsigned int bet;


} playerInfoType;


int add_player( playerInfoType *playerList );
int delete_player( playerInfoType *playerList );
int show_players( playerInfoType *playerList );
int play_round( playerInfoType *playerList, unsigned short *next_card );

int score_cards( unsigned char *cards );

char matchDealer( unsigned char dealer_show_card, unsigned char *player_cards );
char basicAlgo( unsigned char dealer_show_card, unsigned char *player_cards );

char neverBustAlgo( unsigned char dealer_show_card, unsigned char *player_cards );
char simpleAlgo( unsigned char dealer_show_card, unsigned char *player_cards );

char superDuperAlgo( unsigned char dealer_show_card, unsigned char *player_cards );

#endif


