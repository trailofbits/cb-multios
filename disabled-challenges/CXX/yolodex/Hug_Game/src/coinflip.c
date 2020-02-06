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

#include "cgc_gamestate.h"
#include "cgc_libc.h"
#include "cgc_utility.h"

extern gamestate *state;

void cgc_coinflip() {
	char got[4];
	char choice;
	unsigned int wager = 0;

	cgc_bzero(got, 4);

	wager = cgc_getBet(state);
	if(wager == -1)
		return;

	cgc_put("Flipping a coin. Do you think it's going to be (h)eads or (t)ails?\n");
	cgc_recvUntil(0, got, 3, '\n');

	switch(got[0]) {
		case 'h':
		case 't':
			break;
		default:
			cgc_put("Invalid choice. Pay the hug tax.");
			state->hugcount-=wager;
			return;
	}

	choice = (got[0] == 'h' ?  1 :  0);

	if(choice == (cgc_hugsnextrand(state) % 2))
		cgc_handleOutcome(state, 1, wager);
	else
		cgc_handleOutcome(state, 0, wager);
}
