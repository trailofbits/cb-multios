
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


#include "service.h"
#include "stdio.h"
#include "stdlib.h"
#include "input.h"

int add_player(playerInfoType *playerList) {

int i;
char buffer[MAX_NAME_LEN];
int method;

	i = 0;

	while (playerList[i].player_name[0] != 0 && i < MAX_PLAYERS) 
		++i;

	if (i == MAX_PLAYERS) {

		printf("Too many players\n");
		return -1;
	}

	printf("Enter player name\n");
	if(receive_until( buffer, '\n', sizeof(buffer) ) == 0)
		return -1;

	strcpy(playerList[i].player_name, buffer);

	playerList[i].funds = 500;
	playerList[i].computerPlayer = 0;
	playerList[i].wins = 0;
	playerList[i].losses = 0;
	playerList[i].useHints = 0;

	printf("Computer player? (y/n)\n");

	if(receive_until( buffer, '\n', sizeof(buffer) ) == 0)
		return -1;

	if (buffer[0] == 'y' || buffer[0] == 'Y') {

		playerList[i].computerPlayer = 1;

		printf("Method 1-4:\n");

		if(receive_until( buffer, '\n', sizeof(buffer) ) == 0)
			return -1;

		method = atoi(buffer);

		playerList[i].computerMethod = method;

		switch (method) {


			case 1:

				playerList[i].whackJackAlgorithm = matchDealer;
				break;

			case 2:

				playerList[i].whackJackAlgorithm = basicAlgo;
				break;			

			case 3:

				playerList[i].whackJackAlgorithm = simpleAlgo;
				break;

			case 4:

				playerList[i].whackJackAlgorithm = neverBustAlgo;
				break;

			case 5:

				playerList[i].whackJackAlgorithm = superDuperAlgo;
				break;			
		}

	}
	else {

		printf("Would you like to enable hints?\n");


		if(receive_until( buffer, '\n', sizeof(buffer) ) == 0)
		return -1;

		if (buffer[0] == 'y' || buffer[0] == 'Y') {

			playerList[i].useHints = 1;

			printf("Method 1-4:\n");

			if(receive_until( buffer, '\n', sizeof(buffer) ) == 0)
				return -1;

			method = atoi(buffer);

			playerList[i].hintsMethod = method;

			switch (method) {


				case 1:

					playerList[i].whackJackAlgorithm = matchDealer;
					break;

				case 2:

					playerList[i].whackJackAlgorithm = basicAlgo;
					break;			

				case 3:

					playerList[i].whackJackAlgorithm = simpleAlgo;
					break;

				case 4:

					playerList[i].whackJackAlgorithm = neverBustAlgo;
					break;			
			}
		}
	}

	return 0;

} // add_player


int show_players(playerInfoType *playerList) {

int i;


	i = 0;

	while (i < MAX_PLAYERS) {

		if (playerList[i].player_name[0] != 0 ) {

			printf("Player name: $s\n", playerList[i].player_name);
			printf("       Wins: $d\n", playerList[i].wins);
			printf("     Losses: $d\n", playerList[i].losses);
			printf("      Funds: $d\n", playerList[i].funds);
		}

		++i;
	}

	return 0;

} // show_players

int delete_player(playerInfoType *playerList) {

int i;
int x;
int delete_num;

char buffer[20];

		i = 0;
		x = 1;

	while (i < MAX_PLAYERS) {

		if (playerList[i].player_name[0] != 0 ) {

			printf("$d) $s\n", x, playerList[i].player_name);
			x++;
		}

		++i;
	}

	if (x == 1) {

		printf("No players\n");
		return -1;
	}

	printf("Player to delete (1-$d):\n", x-1);

	if(receive_until( buffer, '\n', sizeof(buffer) ) == 0)
		return -1;

	delete_num = atoi(buffer);


	if ( delete_num >= x)
		return -1;

	x = 0;

	for (i=0; i < MAX_PLAYERS; ++i) {

		if (playerList[i].player_name[0] != 0 ) {
			x++;

			if (x==delete_num) {
				playerList[i].player_name[0] = 0;
				playerList[i].wins = 0;
				playerList[i].losses = 0;
				playerList[i].funds = 500;

				break;
			}
		}

	}
	return 0;

}


