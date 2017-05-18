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

#include "cgc_libc.h"
#include "cgc_gamestate.h"
#include "cgc_utility.h"

extern gamestate *state;

void cgc_dicegame() {
	char howmany[16];
	unsigned int rolls[16];
	cgc_bzero((char *)rolls, sizeof(rolls));
	int rollnum = 0;
	int wager = 0;
	int maxrolls;

	cgc_bzero(howmany, 16);

	wager = cgc_getBet(state);
	if(wager == -1)
		return;

	cgc_put("How many rolls do you want? ");
	cgc_recvUntil(0, howmany, 15, '\n');
	maxrolls = cgc_atoi(howmany);

	while(rollnum < maxrolls) {
		cgc_put("Rolling a 31337 sided dice. 31337 wins jackpot. If you guess within 100, you win.\n");
		cgc_put("What is your guess for the dice? ");
		#ifdef PATCHED_1
		rolls[rollnum%16] = cgc_hugsnextrand(state);
		if(rolls[rollnum%16] % 31338 == 31337)
		#else
		rolls[rollnum] = cgc_hugsnextrand(state);
		if(rolls[rollnum] % 31338 == 31337)
		#endif
		{
			cgc_put("!!!JACKPOT!!!");
			wager*=1000;
			cgc_handleOutcome(state, 1, wager);
		} else {
			cgc_bzero(howmany, 16);
			cgc_recvUntil(0, howmany, 15, '\n');
			#ifdef PATCHED_1
			if((((rolls[rollnum%16]%31338) < 100) || (cgc_atoi(howmany) > (rolls[rollnum%16]%31338)-100)) && (cgc_atoi(howmany) < (rolls[rollnum%16]%31338)+100))
			#else
			if((((rolls[rollnum]%31338) < 100) || (cgc_atoi(howmany) > (rolls[rollnum]%31338)-100)) && (cgc_atoi(howmany) < (rolls[rollnum]%31338)+100))
			#endif
			{
	
				cgc_put("Yes! ");
				cgc_put(howmany);
				cgc_put(" is ");
				#ifdef PATCHED_1
				if((signed int)((rolls[rollnum%16]%31338)-cgc_atoi(howmany)) < 0) {
					cgc_put(cgc_itoa(cgc_atoi(howmany)-(rolls[rollnum%16]%31338)));
				} else {
					cgc_put(cgc_itoa((rolls[rollnum%16]%31338)-cgc_atoi(howmany)));
				}
				#else
				if((signed int)((rolls[rollnum]%31338)-cgc_atoi(howmany)) < 0) {
					cgc_put(cgc_itoa(cgc_atoi(howmany)-(rolls[rollnum]%31338)));
				} else {
					cgc_put(cgc_itoa((rolls[rollnum]%31338)-cgc_atoi(howmany)));
				}
				#endif
				cgc_put(" away from ");
				#ifdef PATCHED_1
				cgc_put(cgc_itoa((rolls[rollnum%16]%31338)));
				#else
				cgc_put(cgc_itoa((rolls[rollnum]%31338)));
				#endif
				cgc_put("\n");
				cgc_handleOutcome(state, 1, wager);
			} else {
				cgc_handleOutcome(state, 0, wager);
			}
		}
		rollnum++;
	}

	return;
}
