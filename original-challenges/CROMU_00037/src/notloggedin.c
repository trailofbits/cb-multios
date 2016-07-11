/*

Author: Joe Rogers <joe@cromulence.co>

Copyright (c) 2014-2015 Cromulence LLC

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
#include "service.h"
#include "jlib.h"

extern int CURRENT_USER;
//extern users_t USERS[MAX_USERS];
extern users_t *USERS;
extern int NUM_USERS;

void CreateUser(void) {
	char buf[MAX_USER_NAME_LEN+1];
	int i;
	int available_slot = -1;

	// prompt for a username
	zero(buf, MAX_USER_NAME_LEN+1);
	print("username: ");
	if (read_until(buf, '\n', MAX_USER_NAME_LEN+1) == -1) {
		_terminate(-1);
	}

	// did we get one?
	if (strlen(buf) == 0) {
		// nope
		return;
	}

	// see if that user already exists
	for (i = 0; i < NUM_USERS; i++) {
		// keep track of any available user slots in case we need to create a new one
		if (USERS[i].name[0] == '\0') {
			available_slot = i;
		}
		if (strmatch(buf, USERS[i].name)) {
			print("[-] Error user exists\n");
			return;
		}
	}

	// nope, create it
	if (available_slot != -1) {
		zero((char *)(&(USERS[available_slot])), sizeof(users_t));
		strcopy(USERS[available_slot].name, buf);
	} else {
		if (NUM_USERS < MAX_USERS) {
			zero((char *)(&(USERS[NUM_USERS])), sizeof(users_t));
			strcopy(USERS[NUM_USERS].name, buf);
			NUM_USERS++;
		} else {
			print("[-] Max users already created\n");
		}
	}

	return;
}

void Login(void) {
	char buf[MAX_USER_NAME_LEN+1];
	int i;

	// prompt for a username
	zero(buf, MAX_USER_NAME_LEN+1);
	print("username: ");
	if (read_until(buf, '\n', MAX_USER_NAME_LEN+1) == -1) {
		_terminate(-1);
	}

	// did we get one?
	if (strlen(buf) == 0) {
		// nope
		return;
	}

	// see if that user is in the list
	for (i = 0; i < NUM_USERS; i++) {
		if (strmatch(buf, USERS[i].name)) {
			break;
		}
	}
	if (i == NUM_USERS) {
		// nope
		print("Login Failed\n");
		return;
	}

	// yep, log them in
	CURRENT_USER = i;
	print("Login Success\n");

	return;
}
