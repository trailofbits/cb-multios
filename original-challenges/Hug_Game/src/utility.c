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
#include "utility.h"

unsigned int getBet(gamestate *state) {
	char got[16];
	unsigned int wager;

	put("How much would you like to wager? ");
	bzero(got, 16);
	recvUntil(0, got, 15, '\n');
	wager = atoi(got);
	if(wager > 0 && wager <= state->hugcount) {
		if(wager > 1000)
			put("HIGH ROLLER COMING THROUGH!\n");
		return wager;
	} else {
		put("You can't bet that many hugs. Sorry. :(\n");
		return -1;
	}
}

void hugsrand(gamestate* state, unsigned int seed) {
    state->gamerand = seed;
}

unsigned int hugsnextrand(gamestate *state) {
	unsigned int bits;

	bits = ((state->gamerand >> 0) ^ (state->gamerand >> 2) ^ (state->gamerand >> 3) ^ (state->gamerand >> 5)) & 1;
	state->gamerand = (state->gamerand >> 1) | (bits << 31);
    return state->gamerand;
}

void handleOutcome(gamestate *state, char outcome, unsigned int wagered) {
	if(outcome == 1) {
		put("YOU WIN!\nAdding ");
		put(itoa(wagered));
		put(" to your hug balance.\n\n");
		state->hugcount+=wagered;
	} else {
		put("YOU LOSE!\nDebiting ");
		put(itoa(wagered));
		put(" from your hug balance.\n\n");
		state->hugcount-=wagered;
	}
}
