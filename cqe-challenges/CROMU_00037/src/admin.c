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

char ADMIN_PASSWD[] = "GIMMIE";
int ADMIN_ACCESS;

void PrintAdminMenu(void) {

        print("1) Send Broadcast Message\n");
        print("2) Leave Admin Mode\n");
        print("3) Exit\n");
        print(": ");

	return;
}

void AdminLogin(void) {
	char buf[100];

	zero(buf, 100);
	print("Admin Password: ");
	if (read_until(buf, '\n', 100) == -1) {
		_terminate(-1);
	}

	if (strmatch(ADMIN_PASSWD, buf)) {
		ADMIN_ACCESS = 1;
		print("[-] Admin access granted\n");
		return;
	}

	print("[-] Admin access denied\n");
	ADMIN_ACCESS = 0;

	return;
}

// send a message to all users
void SendBroadcastMessage(void) {
	int i, j;
#ifdef PATCHED
	char message[MAX_MESSAGE_LEN];

	// read in the Message:
	zero(message, MAX_MESSAGE_LEN);
	print("Message: ");
	if (read_until(message, '\n', MAX_MESSAGE_LEN) == -1) {
#else
	char message[1024];

	// read in the Message:
	zero(message, 1024);
	print("Message: ");
	if (read_until(message, '\n', 1024) == -1) {
#endif
		_terminate(-1);
	}
	if (strlen(message) == 0) {
		return;
	}

	// for all valid users
	for (i = 0; i < NUM_USERS; i++) {
		if (USERS[i].name[0] == '\0') {
			continue;
		}

		if (USERS[i].top_message == MAX_MESSAGES) {
			print("[*] Unable to send message to ");
			print(USERS[i].name);
			print(". Their mailbox is full.\n");
			continue;
		}

		// store the message
		j = USERS[i].top_message+1;
		strcopy(USERS[i].messages[j], message);
		USERS[i].msg_read[j] = 0;
		USERS[i].top_message = j;

	}

	return;
}
