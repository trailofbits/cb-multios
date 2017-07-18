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
#include "cgc_words.h"
#include "cgc_libc.h"
#include "cgc_utility.h"
#include "cgc_gamestate.h"

extern gamestate *state;

char *cgc_renderBoard(gamestate *state);
char *cgc_pickaword(gamestate *state);

char *cgc_pickaword(gamestate *state) {
	return words[cgc_hugsnextrand(state) % (sizeof(words) / 4)];
}

void cgc_hangman() {
	char *toguess;
	int i;
	char correct[128];
	char guess[4];
	unsigned int len = 0;
	int right;
	int correctcount = 0;
	unsigned int wagered = 0;

	cgc_bzero(correct, 128);
	toguess = cgc_pickaword(state);
	len = cgc_strlen(toguess);
	state->hangmanguess = 0;

	wagered = cgc_getBet(state);
	if(wagered == -1)
		return;

	while(state->hangmanguess < 5)
	{
		right = 0;
		cgc_bzero(guess, 4);
		cgc_put(cgc_renderBoard(state));
		for(i=0;i<len;i++)
		{
			if(correct[i] == 0)
				cgc_put("_");
			else {
				cgc_put(&correct[i]);
				i+= cgc_strlen(&correct[i])-1;
			}
		}

		cgc_put("\n");
		cgc_put("Please enter a guess: ");
		cgc_recvUntil(0, guess, 3, '\n');
		for(i=0;i<len;i++)
		{
			if(guess[0] == toguess[i])
			{
				correct[i] = guess[0];
				right = 1;
				correctcount++;
			}
		}
		if(right == 0)
			state->hangmanguess++;
		if(cgc_strlen(correct) == cgc_strlen(toguess))
		{
			cgc_handleOutcome(state, 1, wagered);
			return;
		}
	}
	cgc_handleOutcome(state, 0, wagered);
}

char * cgc_renderBoard(gamestate *state) {
	switch(state->hangmanguess) {
		case 0:
		return "|---|\n\
|\n\
|\n\
|\n\
|\n\
______\n";
		case 1:
		return "|---|\n\
|   O\n\
|\n\
|\n\
|\n\
______\n";

		case 2:
		return "|---|\n\
|   O\n\
|   |\n\
|\n\
|\n\
______\n";
		case 3:
		return "|---|\n\
|   O\n\
|  -|-\n\
|\n\
|\n\
______\n";
		case 4:
		return "|---|\n\
|   O\n\
|  -|-\n\
|  / \\\n\
|\n\
______\n";
	}
	return "???\n";
}
