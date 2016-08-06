/*

Author: Steve Wood <swood@cromulence.co>

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

#include "stdlib.h"

// search for a string in a target string, including the * and ? wildcards
int match_str(char *search, char *target) {
	
char *after_wildcard=0;

	while (*target != 0 && *search != 0) {


		if (*search == '*') {

			// if we are at the end of the search string with a wildcard, success!
			if (*(search+1) == 0)
				return 1;

			// move past the '*'
			++search;

			// save this point because we might have to come back here
			after_wildcard=search;

			// now wildcard through the target until the next match of the search string
			while (*search != *target && *target != 0)
				++target;

			// if we hit the end of the target w/o finding the next char, they don't match
			if (*target == 0)
				return 0;

			// must have found a match, increment to next chars and start at the top
			++search;
			++target;

			// we hit the end of the search string
			if (*search==0 ) {

				// but there's more target string, and there was a wildcard specified in the search
				// restart the search from after the '*'
				if ( *target!=0 && after_wildcard!=0) {
					search=after_wildcard;
					continue;
				}
				else
					break;
			}
		} 
		// match any single character.  we already know we aren't at the end of the string, so increment and move on
		else if (*search == '?') {

			++search;
			++target;

		}
		// the chars don't match, but if there was a wildcard earlier...
		else if (*search != *target) {

			// there was an '*' so restart the search string from that point
			if (after_wildcard!=0) {

				if (search!=after_wildcard) {
					search=after_wildcard;
					continue;
				}
				// this is a special case where resetting the search string would cause us to get in a loop
				// increment the target string to get out of that loop
				else
					++target;	
			}
			else
				return 0;

		}
		// they must match, so move to the next chars
		else {

			++search;
			++target;

			// if we've exhausted the search string
			if (*search==0 ) {

				// but there is still more target and the wildcard was specified, restart at the wildcard.
				if ( *target!=0 && after_wildcard!=0) {
					search=after_wildcard;
					continue;
				}
				else
					break;
			}


		} //else

	} //while


	// if we hit the end of both strings at the same time, success!
	if (*target==0) {

		// allow for a trailing '*' at the end of the search
		if (*search == 0 || (*search=='*' && *(search+1)==0))
			return 1;
		else
			return 0;
	}
	else
		return 0;


}  //match_str()


// a simple scan for wildcard chars
int contains_wildcards(char *str) {

	while (*str != 0) {

		if (*str == '*' || *str == '?')
			return 1;
		else
			++str;

	}

	return 0;

} // contains_wildcards()