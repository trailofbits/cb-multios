 /*

Author: Debbie Nuttall <debbie@cromulence.com>

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
#include "stdio.h"
#include "ctype.h"
#include "libc.h"
#include "crackaddr.h"



char *crackaddr(char *addr, char *output) {
	char *outp = output;
	char *endp = output + MAX_NAME - 5;
	char c;

	if (addr == NULL) {
		return NULL;
	}

	// strip whitespace
	while (*addr && isspace(*addr))
		addr++;
	
	// Setup state
	int inA, inC;
	inA = inC = 0;
	int Blevel, Blevelout;
	Blevel = Blevelout = 0;
	int full;
	int Dmode = 0;
	int outputLevel = 0;

	while (*addr != '\0') {
		c = *addr++;
		full = outp >= endp;

		if ((!full) && (outputLevel > 0)){
			*outp++ = c;
		}

		if (c == 'A') {
		 	outputLevel = 0;
		 	if (!inA) {
				inA = TRUE;
				endp--;
			}
		}
		if (c == 'a') {
			outputLevel++;
			if (outputLevel <= 1) {
				 *outp++ = c;
			}
			if (inA) {
				inA = FALSE;
				endp++;
			}
		}

		// Equivalent to parents from original crackaddr
		// Bb can be embedded in other Bb
		if (c == 'B') {
			Blevel++;
			if (!full) {
				Blevelout++;
				endp--;
				outputLevel++;
			}
		}
		if ((c == 'b') && (Blevel > 0)) {
			Blevel--;
			outputLevel--;
			if (!full) {
				Blevelout--;
				endp++;
			}
			continue;
		} else if (c == 'b') {
			// Syntax error unmatched 'b'
			if ((!full) && (outputLevel > 0)){
				outp--;
			}
		}

		// Equivalent to angle brackets from original crackaddr
		if ((c == 'C') && (!inC)) {
			inC = TRUE;
#ifdef PATCHED_1
			endp--;
#endif
		}
		if ((c == 'c') && (inC)) {
			inC = FALSE;
			endp++;
		}

		if (c == 'D') {
			Dmode = !Dmode;
		}


		// Escapes next char
		if ((c == 'F') && (!full)) {
			if (*addr != '\0') { 
				*outp++ = *addr++;
			}
			continue;
		}

		// Skips next char
		if (c == 'G') {
			if (*addr != '\0') { 
				addr++;
			}
			continue;
		}

	}

	if (inA) {
		*outp++ = 'a';
	}
	while((Blevelout-- > 0)&&(outp < endp - 2)) {
		*outp++ = 'b';
	}
	
	if (inC) {
		*outp++ = 'c';
	}

	if (Dmode) {
		*outp++ = 'D';
	}

	*outp++ = '\0';

	return output;

	}	


