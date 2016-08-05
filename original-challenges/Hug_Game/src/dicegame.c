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
#include "gamestate.h"
#include "utility.h"

extern gamestate *state;

void dicegame() {
	char howmany[16];
	unsigned int rolls[16];
	bzero((char *)rolls, sizeof(rolls));
	int rollnum = 0;
	int wager = 0;
	int maxrolls;

	bzero(howmany, 16);

	wager = getBet(state);
	if(wager == -1)
		return;

	put("How many rolls do you want? ");
	recvUntil(0, howmany, 15, '\n');
	maxrolls = atoi(howmany);

	while(rollnum < maxrolls) {
		put("Rolling a 31337 sided dice. 31337 wins jackpot. If you guess within 100, you win.\n");
		put("What is your guess for the dice? ");
		#ifdef PATCHED_1
		rolls[rollnum%16] = hugsnextrand(state);
		if(rolls[rollnum%16] % 31338 == 31337)
		#else
		rolls[rollnum] = hugsnextrand(state);
		if(rolls[rollnum] % 31338 == 31337)
		#endif
		{
			put("!!!JACKPOT!!!");
			wager*=1000;
			handleOutcome(state, 1, wager);
		} else {
			bzero(howmany, 16);
			recvUntil(0, howmany, 15, '\n');
			#ifdef PATCHED_1
			if((((rolls[rollnum%16]%31338) < 100) || (atoi(howmany) > (rolls[rollnum%16]%31338)-100)) && (atoi(howmany) < (rolls[rollnum%16]%31338)+100))
			#else
			if((((rolls[rollnum]%31338) < 100) || (atoi(howmany) > (rolls[rollnum]%31338)-100)) && (atoi(howmany) < (rolls[rollnum]%31338)+100))
			#endif
			{
	
				put("Yes! ");
				put(howmany);
				put(" is ");
				#ifdef PATCHED_1
				if((signed int)((rolls[rollnum%16]%31338)-atoi(howmany)) < 0) {
					put(itoa(atoi(howmany)-(rolls[rollnum%16]%31338)));
				} else {
					put(itoa((rolls[rollnum%16]%31338)-atoi(howmany)));
				}
				#else
				if((signed int)((rolls[rollnum]%31338)-atoi(howmany)) < 0) {
					put(itoa(atoi(howmany)-(rolls[rollnum]%31338)));
				} else {
					put(itoa((rolls[rollnum]%31338)-atoi(howmany)));
				}
				#endif
				put(" away from ");
				#ifdef PATCHED_1
				put(itoa((rolls[rollnum%16]%31338)));
				#else
				put(itoa((rolls[rollnum]%31338)));
				#endif
				put("\n");
				handleOutcome(state, 1, wager);
			} else {
				handleOutcome(state, 0, wager);
			}
		}
		rollnum++;
	}

	return;
}
