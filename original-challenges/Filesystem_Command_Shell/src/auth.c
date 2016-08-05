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
#include "service.h"
#include "filesystem.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

#define INITIALIZATION_DATA 0x4347C000

// authenticates from the magic page.  Returns a security ID on success, or 0 on failure
securityIdType authenticate(char *name, unsigned int token) {

int i;
int x;
int offset;
unsigned char tmpchar;
char userID[8];
unsigned int tmp_token;
securityIdType security_ID;
unsigned char *readPtr;
unsigned int maxEntries;


	readPtr = (unsigned char *)INITIALIZATION_DATA;
	maxEntries = 4096/32;

	for (i = 0; i < maxEntries; ++i) {

		offset = i * 32;

		for (x = 0; x < 7; ++x) {

			tmpchar = *(readPtr+offset+x);
			tmpchar = (tmpchar % 26) + 'a';
			userID[x] = tmpchar;
		}

		userID[7] = 0;

		if (strncmp(name, userID, 7) == 0) {
			
			tmp_token = 0;

			for (x = 14; x < 28; ++x ) {

				tmp_token += *(unsigned char *)(readPtr+offset+x);
			}

			if (tmp_token == token) {

				security_ID = *(unsigned int *)(readPtr+offset+28);

				// make sure none are negative
				security_ID = security_ID & 0x7fffffff;

				return security_ID;

			}
		}
	}

	if (strcmp(name, "GUEST") == 0) {

		if ( token > 1 & token < 8 && token % 2 == 0 ) {
		
			return token;

		}
	}

	return 0;

}

int lookupName( char *name, securityIdType ID ) {

int i;
int x;
int offset;
unsigned char tmpchar;
char userID[8];
securityIdType security_ID;
unsigned char *readPtr;
unsigned int maxEntries;

	if (name == 0) {

		return -1;

	}

	readPtr = (unsigned char *)INITIALIZATION_DATA;
	maxEntries = 4096/32;

	for (i = 0; i < maxEntries; ++i) {

		offset = i * 32;

		security_ID = *(unsigned int *)(readPtr+offset+28);

		// make sure its not negative
		security_ID = security_ID & 0x7fffffff;

		if ( ID == security_ID ) {

			for (x = 0; x < 7; ++x) {

				tmpchar = *(readPtr+offset+x);
				tmpchar = (tmpchar % 26) + 'a';
				userID[x] = tmpchar;
			}

			userID[7] = 0;

			strcpy(name, userID);

			return 0;

		} // if ( ID == security_ID )


	} // for

	if (ID > 2 && ID < 8 ) {

		strcpy(name, "GUEST");
		name[5] = ID + '0';
		name[6] = 0;

		return 0;
	}

	// if we get here, the ID wasn't found
	return -1;
}
