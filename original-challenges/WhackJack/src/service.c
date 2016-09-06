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



int main(void) {

playerInfoType players[MAX_PLAYERS];	
char buffer[4];
int silentMenu;
int selection;
unsigned short card_ptr;

	selection = 99;
	silentMenu = 0;
	card_ptr = 0;


	while (selection != 0) {


		if (silentMenu == 0) {
			printf("\n");
			printf("1) Add Player\n");
			printf("2) Delete Player\n");
			printf("3) Play\n");
			printf("4) Statistics\n");

			printf("0) Exit\n");
		}

#ifdef PATCHED_1

		if(receive_until( buffer, '\n', 4 ) == 0)
			continue;

#else

		if(receive_until( buffer, '\n', 21 ) == 0)
			continue;

#endif
		selection = atoi(buffer);

		switch (selection) {

			case 1:

				add_player(players);

				break;

			case 2:

				delete_player(players); 
				break;

			case 3:

				play_round(players, &card_ptr);
				break;

			case 4:

				show_players(players);
				break;

			default:
				continue;


		} // switch


	} //while

	_terminate(0);

}  // main  

