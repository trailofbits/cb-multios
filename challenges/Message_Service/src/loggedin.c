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
#include "libcgc.h"
#include "cgc_service.h"
#include "cgc_jlib.h"

extern int cgc_CURRENT_USER;
//extern users_t cgc_USERS[MAX_USERS];
extern users_t *cgc_USERS;
extern int cgc_NUM_USERS;

void cgc_SendMessage(void) {
	char user[MAX_USER_NAME_LEN+1];
	char message[MAX_MESSAGE_LEN];
	int i, j;

	// cgc_read in the To:
	cgc_zero(user, MAX_USER_NAME_LEN+1);
	cgc_print("To: ");
	if (cgc_read_until(user, '\n', MAX_USER_NAME_LEN+1) == -1) {
		cgc__terminate(-1);
	}

	if (cgc_strlen(user) == 0) {
		return;
	}

	// cgc_read in the Message:
	cgc_zero(message, MAX_MESSAGE_LEN);
	cgc_print("Message: ");
	if (cgc_read_until(message, '\n', MAX_MESSAGE_LEN) == -1) {
		cgc__terminate(-1);
	}
	if (cgc_strlen(message) == 0) {
		return;
	}

	// find the recipient
	for (i = 0; i < cgc_NUM_USERS; i++) {
		if (cgc_strmatch(user, cgc_USERS[i].name)) {
			break;
		}
	}
	if (i == cgc_NUM_USERS) {
		return;
	}

	if (cgc_USERS[i].top_message == MAX_MESSAGES) {
		// recipient's mailbox is full
		cgc_print("[-] Recipient's mailbox is full\n");
		return;
	}
	
	// store the message
	j = cgc_USERS[i].top_message+1;
	cgc_strcopy(cgc_USERS[i].messages[j], message);
	cgc_USERS[i].msg_read[j] = 0;
	cgc_USERS[i].top_message = j;

	return;

}

void cgc_ReadMessage(void) {
	char id[4];
	int id_val;

	// cgc_read in the ID:
	cgc_zero(id, 4);
	cgc_print("ID: ");
	if (cgc_read_until(id, '\n', 4) == -1) {
		cgc__terminate(-1);
	}
	if (cgc_strlen(id) == 0) {
		return;
	}

	if (!cgc_isdigits(id)) {
		return;
	}
	id_val = cgc_atoi(id);

	if (id_val > cgc_USERS[cgc_CURRENT_USER].top_message) {
		cgc_print("[-] Message ID out of range\n");
		return;
	}

	if (cgc_USERS[cgc_CURRENT_USER].messages[id_val][0] == '\0') {
		cgc_print("[-] Message ID not found\n");
		return;
	}

	// print the message
	cgc_print("***********************************\n");
	cgc_print(id);
	cgc_print(":  ");
	cgc_print(cgc_USERS[cgc_CURRENT_USER].messages[id_val]);
	cgc_print("\n");
	cgc_print("***********************************\n");
	cgc_USERS[cgc_CURRENT_USER].msg_read[id_val] = 1;

	return;
}

void cgc_ListMessages(void) {
	unsigned int i;

	for (i = 1; i <= cgc_USERS[cgc_CURRENT_USER].top_message; i++) {
		if (cgc_USERS[cgc_CURRENT_USER].messages[i][0] == '\0') {
			continue;
		}

		cgc_print("***********************************\n");
		cgc_print_uint(i);
		cgc_print(":  ");
		cgc_print(cgc_USERS[cgc_CURRENT_USER].messages[i]);
		cgc_print("\n");
		cgc_print("***********************************\n");
		
	}

	return;
}

void cgc_DeleteMessage(void) {
	char id[4];
	int id_val;

	// cgc_read in the ID:
	cgc_zero(id, 4);
	cgc_print("ID: ");
	if (cgc_read_until(id, '\n', 4) == -1) {
		cgc__terminate(-1);
	}
	if (cgc_strlen(id) == 0) {
		return;
	}

	if (!cgc_isdigits(id)) {
		return;
	}
	id_val = cgc_atoi(id);

	if (id_val > cgc_USERS[cgc_CURRENT_USER].top_message) {
		cgc_print("[-] Message ID out of range\n");
		return;
	}

	cgc_zero(cgc_USERS[cgc_CURRENT_USER].messages[id_val], MAX_MESSAGE_LEN);
	
	return;

}

void cgc_PrintNewMessages(void) {
	unsigned int i;
	int first = 1;

	for (i = 1; i < MAX_MESSAGES; i++) {
		if (cgc_USERS[cgc_CURRENT_USER].messages[i][0] == '\0') {
			continue;
		}
		if (cgc_USERS[cgc_CURRENT_USER].msg_read[i] == 1) {
			continue;
		}

		if (first) {
			cgc_print("Unread messages:\n");
			first = 0;
		}
		cgc_print("***********************************\n");
		cgc_print_uint(i);
		cgc_print(":  ");
		cgc_print(cgc_USERS[cgc_CURRENT_USER].messages[i]);
		cgc_print("\n");
		cgc_print("***********************************\n");

		cgc_USERS[cgc_CURRENT_USER].msg_read[i] = 1;
	}

	return;
}
