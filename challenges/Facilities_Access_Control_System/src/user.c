/*

Author: Joe Rogers <joe@cromulence.com>

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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_stdint.h"
#include "cgc_string.h"
#include "cgc_user.h"
#include "cgc_io.h"
#include "cgc_device.h"

User cgc_Users[MAX_USERS];
uint8_t cgc_NumUsers = 0;

uint8_t cgc_FindUsername(char *Username) {
	uint8_t i;

	for (i = 0; i < MAX_USERS; i++) {
		if (!cgc_strcmp(cgc_Users[i].Username, Username)) {
			break;
		}
	}

	return(i);
}

uint8_t cgc_FindCode(char *code) {
	uint8_t i;

	for (i = 0; i < MAX_USERS; i++) {
		if (!cgc_strcmp(cgc_Users[i].Pin, code)) {
			return(1);
		}
		if (!cgc_strcmp(cgc_Users[i].AccessCode, code)) {
			return(1);
		}
	}

	return(0);
}

int8_t cgc_FindAvailableUser(void) {
	uint8_t i;

	for (i = 0; i < MAX_USERS; i++) {
		if (!cgc_Users[i].Username[0]) {
			break;
		}
	}
	if (i == MAX_USERS) {
		return(-1);
	} else {
		return(i);
	}
}

uint8_t cgc_AddUser(void) {
	int8_t TargetUser;
	User NewUser;

	// Read in the user info
	if (!cgc_ReadBytes((unsigned char *)&NewUser, sizeof(User))) {
		return(0);
	}

	// Make sure there's room for a new user
#ifdef PATCHED_1
	if (cgc_NumUsers >= MAX_USERS) {
#else
	if (cgc_NumUsers > MAX_USERS) {
#endif
		return(0);
	}

	// Find an available user entry
	TargetUser = cgc_FindAvailableUser();

	// Make sure the user doesn't already exist
	if (cgc_FindUsername(NewUser.Username) != MAX_USERS) {
		return(0);
	}

	// Make sure the selected pin and access code are of the correct lengths
	if (cgc_strlen(NewUser.Pin) != PIN_LEN) {
		return(0);
	}
	if (cgc_strlen(NewUser.AccessCode) != ACCESS_CODE_LEN) {
		return(0);
	}

	// Make sure the selected passcode doesn't already exist
	if (cgc_FindCode(NewUser.Pin) || cgc_FindCode(NewUser.AccessCode)) {
		return(0);
	}

	// Add the user to the list
	cgc_memcpy(&cgc_Users[TargetUser], &NewUser, sizeof(User));

	cgc_NumUsers++;

	return(1);
}

uint8_t cgc_DelUser(void) {
	char Username[32];
	uint8_t UserIndex;

	// Read in the username
	cgc_bzero(Username, 32);
	if (!cgc_ReadBytes((unsigned char *)Username, 32)) {
		return(0);
	}
	Username[31] = '\0';

	// Find the user in the table
	if ((UserIndex = cgc_FindUsername(Username)) == MAX_USERS) {
		return(0);
	}

	// Remove the user from any devices to which it's associated
	cgc_RevokeAccess(UserIndex);

	// Zero that entry
	cgc_bzero(&cgc_Users[UserIndex], sizeof(User));
	cgc_NumUsers--;

	return(1);
}
