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

void SendMessage(void) {
	char user[MAX_USER_NAME_LEN+1];
	char message[MAX_MESSAGE_LEN];
	int i, j;

	// read in the To:
	zero(user, MAX_USER_NAME_LEN+1);
	print("To: ");
	if (read_until(user, '\n', MAX_USER_NAME_LEN+1) == -1) {
		_terminate(-1);
	}

	if (strlen(user) == 0) {
		return;
	}

	// read in the Message:
	zero(message, MAX_MESSAGE_LEN);
	print("Message: ");
	if (read_until(message, '\n', MAX_MESSAGE_LEN) == -1) {
		_terminate(-1);
	}
	if (strlen(message) == 0) {
		return;
	}

	// find the recipient
	for (i = 0; i < NUM_USERS; i++) {
		if (strmatch(user, USERS[i].name)) {
			break;
		}
	}
	if (i == NUM_USERS) {
		return;
	}

	if (USERS[i].top_message == MAX_MESSAGES) {
		// recipient's mailbox is full
		print("[-] Recipient's mailbox is full\n");
		return;
	}
	
	// store the message
	j = USERS[i].top_message+1;
	strcopy(USERS[i].messages[j], message);
	USERS[i].msg_read[j] = 0;
	USERS[i].top_message = j;

	return;

}

void ReadMessage(void) {
	char id[4];
	int id_val;

	// read in the ID:
	zero(id, 4);
	print("ID: ");
	if (read_until(id, '\n', 4) == -1) {
		_terminate(-1);
	}
	if (strlen(id) == 0) {
		return;
	}

	if (!isdigits(id)) {
		return;
	}
	id_val = atoi(id);

	if (id_val > USERS[CURRENT_USER].top_message) {
		print("[-] Message ID out of range\n");
		return;
	}

	if (USERS[CURRENT_USER].messages[id_val][0] == '\0') {
		print("[-] Message ID not found\n");
		return;
	}

	// print the message
	print("***********************************\n");
	print(id);
	print(":  ");
	print(USERS[CURRENT_USER].messages[id_val]);
	print("\n");
	print("***********************************\n");
	USERS[CURRENT_USER].msg_read[id_val] = 1;

	return;
}

void ListMessages(void) {
	unsigned int i;

	for (i = 1; i <= USERS[CURRENT_USER].top_message; i++) {
		if (USERS[CURRENT_USER].messages[i][0] == '\0') {
			continue;
		}

		print("***********************************\n");
		print_uint(i);
		print(":  ");
		print(USERS[CURRENT_USER].messages[i]);
		print("\n");
		print("***********************************\n");
		
	}

	return;
}

void DeleteMessage(void) {
	char id[4];
	int id_val;

	// read in the ID:
	zero(id, 4);
	print("ID: ");
	if (read_until(id, '\n', 4) == -1) {
		_terminate(-1);
	}
	if (strlen(id) == 0) {
		return;
	}

	if (!isdigits(id)) {
		return;
	}
	id_val = atoi(id);

	if (id_val > USERS[CURRENT_USER].top_message) {
		print("[-] Message ID out of range\n");
		return;
	}

	zero(USERS[CURRENT_USER].messages[id_val], MAX_MESSAGE_LEN);
	
	return;

}

void PrintNewMessages(void) {
	unsigned int i;
	int first = 1;

	for (i = 1; i < MAX_MESSAGES; i++) {
		if (USERS[CURRENT_USER].messages[i][0] == '\0') {
			continue;
		}
		if (USERS[CURRENT_USER].msg_read[i] == 1) {
			continue;
		}

		if (first) {
			print("Unread messages:\n");
			first = 0;
		}
		print("***********************************\n");
		print_uint(i);
		print(":  ");
		print(USERS[CURRENT_USER].messages[i]);
		print("\n");
		print("***********************************\n");

		USERS[CURRENT_USER].msg_read[i] = 1;
	}

	return;
}
