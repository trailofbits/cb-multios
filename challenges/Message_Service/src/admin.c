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

char ADMIN_PASSWD[] = "GIMMIE";
int cgc_ADMIN_ACCESS;

void cgc_PrintAdminMenu(void) {

        cgc_print("1) Send Broadcast Message\n");
        cgc_print("2) Leave Admin Mode\n");
        cgc_print("3) Exit\n");
        cgc_print(": ");

	return;
}

void cgc_AdminLogin(void) {
	char buf[100];

	cgc_zero(buf, 100);
	cgc_print("Admin Password: ");
	if (cgc_read_until(buf, '\n', 100) == -1) {
		cgc__terminate(-1);
	}

	if (cgc_strmatch(ADMIN_PASSWD, buf)) {
		cgc_ADMIN_ACCESS = 1;
		cgc_print("[-] Admin access granted\n");
		return;
	}

	cgc_print("[-] Admin access denied\n");
	cgc_ADMIN_ACCESS = 0;

	return;
}

// send a message to all users
void cgc_SendBroadcastMessage(void) {
	int i, j;
#ifdef PATCHED
	char message[MAX_MESSAGE_LEN];

	// cgc_read in the Message:
	cgc_zero(message, MAX_MESSAGE_LEN);
	cgc_print("Message: ");
	if (cgc_read_until(message, '\n', MAX_MESSAGE_LEN) == -1) {
#else
	char message[1024];

	// cgc_read in the Message:
	cgc_zero(message, 1024);
	cgc_print("Message: ");
	if (cgc_read_until(message, '\n', 1024) == -1) {
#endif
		cgc__terminate(-1);
	}
	if (cgc_strlen(message) == 0) {
		return;
	}

	// for all valid users
	for (i = 0; i < cgc_NUM_USERS; i++) {
		if (cgc_USERS[i].name[0] == '\0') {
			continue;
		}

		if (cgc_USERS[i].top_message == MAX_MESSAGES) {
			cgc_print("[*] Unable to send message to ");
			cgc_print(cgc_USERS[i].name);
			cgc_print(". Their mailbox is full.\n");
			continue;
		}

		// store the message
		j = cgc_USERS[i].top_message+1;
		cgc_strcopy(cgc_USERS[i].messages[j], message);
		cgc_USERS[i].msg_read[j] = 0;
		cgc_USERS[i].top_message = j;

	}

	return;
}
