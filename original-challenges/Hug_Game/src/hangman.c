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
#include "words.h"
#include "libc.h"
#include "utility.h"
#include "gamestate.h"

extern gamestate *state;

char *renderBoard(gamestate *state);
char *pickaword(gamestate *state);

char *pickaword(gamestate *state) {
	return words[hugsnextrand(state) % (sizeof(words) / 4)];
}

void hangman() {
	char *toguess;
	int i;
	char correct[128];
	char guess[4];
	unsigned int len = 0;
	int right;
	int correctcount = 0;
	unsigned int wagered = 0;

	bzero(correct, 128);
	toguess = pickaword(state);
	len = strlen(toguess);
	state->hangmanguess = 0;

	wagered = getBet(state);
	if(wagered == -1)
		return;

	while(state->hangmanguess < 5)
	{
		right = 0;
		bzero(guess, 4);
		put(renderBoard(state));
		for(i=0;i<len;i++)
		{
			if(correct[i] == 0)
				put("_");
			else {
				put(&correct[i]);
				i+= strlen(&correct[i])-1;
			}
		}

		put("\n");
		put("Please enter a guess: ");
		recvUntil(0, guess, 3, '\n');
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
		if(strlen(correct) == strlen(toguess))
		{
			handleOutcome(state, 1, wagered);
			return;
		}
	}
	handleOutcome(state, 0, wagered);
}

char * renderBoard(gamestate *state) {
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
