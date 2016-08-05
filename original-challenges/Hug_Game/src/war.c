/*

Author: Dustin Fraze (df@cromulence.com)

Copyright (c) 2014 Cromulence LLC

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
#include "libc.h"
#include "utility.h"

extern gamestate *state;

char *cardName(int cardNum) {
	switch(cardNum+1) {
		case 1:
			return "two";
		case 2:
			return "three";
		case 3:
			return "four";
		case 4:
			return "five";
		case 5:
			return "six";
		case 6:
			return "seven";
		case 7:
			return "eight";
		case 8:
			return "nine";
		case 9:
			return "ten";
		case 10:
			return "jack";
		case 11:
			return "queen";
		case 12:
			return "king";
		case 13:
			return "ace";
	}
	return "?";
}

char *cardSuite(int cardNum) {
	switch(cardNum) {
		case 0:
			return "spades";
		case 1:
			return "hearts";
		case 2:
			return "clubs";
		case 3:
			return "diamonds";
	}
	return "?";
}

void war() {
	int wager;
	unsigned int playerCard;
	unsigned int dealerCard;

	wager = getBet(state);
	if(wager < 0)
		return;

	playerCard = hugsnextrand(state);
	dealerCard = hugsnextrand(state);
	top:
	if(dealerCard % 13 > playerCard % 13) {
		put("Dealer's ");
		put(cardName(dealerCard % 13));
		put(" of ");
		put(cardSuite(dealerCard % 4));
		put(" beats player's ");
		put(cardName(playerCard % 13));
		put(" of ");
		put(cardSuite(playerCard % 4));
		put("\n");
		handleOutcome(state, 0, wager);
	} else if (dealerCard % 13 < playerCard % 13) {
		put("Player's ");
		put(cardName(playerCard % 13));
		put(" of ");
		put(cardSuite(playerCard % 4));
		put(" beats dealer's ");
		put(cardName(dealerCard % 13));
		put(" of ");
		put(cardSuite(dealerCard % 4));
		put("\n");
		handleOutcome(state, 1, wager);
	} else {
		put("Both players drew a ");
		put(cardName(playerCard % 13));
		put("\nTHIS MEANS WAR\n");
		wager *= 2;
		hugsnextrand(state);
		hugsnextrand(state);
		hugsnextrand(state);
		playerCard = hugsnextrand(state);
		hugsnextrand(state);
		hugsnextrand(state);
		hugsnextrand(state);
		dealerCard = hugsnextrand(state);
		goto top;
	}
}
