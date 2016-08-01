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
#include "notloggedin.h"
#include "loggedin.h"
#include "sort.h"
#include "admin.h"

int CURRENT_USER;
users_t *USERS;
int NUM_USERS;
extern int ADMIN_ACCESS;

void PrintLoggedOutMenu(void) {
	print("1) Create User\n");
	print("2) Login\n");
	print("3) Exit\n");
	print(": ");
}

void PrintLoggedInMenu(void) {

	print("1) Send Message\n");
	print("2) Read Message\n");
	print("3) List Messages\n");
	print("4) Delete Message\n");
	print("5) Logout\n");
	print("6) Exit\n");
	print(": ");

}

void BusyWork(void) {
	char array[4096];
	int addr = (int)(&PrintLoggedOutMenu) & 0xfffff000;
	int i = 20;

	while (i--) {
		memcopy(array, (char *)addr, 4096);
		sort_n_sum(array, 4096);
	}

}

int main(void) {
	users_t users[MAX_USERS];
	char buf[100];
	int done = 0;

//	BusyWork();

	// set a global pointer for easier function access
	USERS = users;

	// init some vars
	ADMIN_ACCESS = 0;
	CURRENT_USER = -1;
	NUM_USERS = 0;
	zero((char *)USERS, sizeof(users_t)*MAX_USERS);

	while (!done) {
		if (ADMIN_ACCESS) {
			zero(buf, 100);
			PrintAdminMenu();
			if (read_until(buf, '\n', 100) == -1) {
				_terminate(-1);
			}
			if (strlen(buf) > 1) {
				print("[-] Invalid choice\n");
				continue;
			}
			switch (buf[0]) {
				case '1':
					SendBroadcastMessage();
					break;

				case '2':
					ADMIN_ACCESS = 0;
					break;

				case '3':
					print("Exiting...\n");
					done = 1;
					break;

				default:
					continue;
			}
		} else if (CURRENT_USER == -1) {
			zero(buf, 100);
			PrintLoggedOutMenu();
			if (read_until(buf, '\n', 100) == -1) {
				_terminate(-1);
			}
			if (strlen(buf) > 1) {
				print("[-] Invalid choice\n");
				continue;
			}
			switch (buf[0]) {
				case '1':
					CreateUser();
					break;
				case '2':
					Login();
					break;
				case '3':
					print("Exiting...\n");
					_terminate(0);
					break;
				default:
					print("[-] Invalid choice\n");
					continue;
			}
		} else {
			zero(buf, 100);
			PrintNewMessages();
			PrintLoggedInMenu();
			if (read_until(buf, '\n', 100) == -1) {
				_terminate(-1);
			}
			if (strlen(buf) > 1) {
				print("[-] Invalid choice\n");
				continue;
			}
			switch (buf[0]) {
				case '1':
					SendMessage();
					break;
				case '2':
					ReadMessage();
					break;
				case '3':
					ListMessages();
					break;
				case '4':
					DeleteMessage();
					break;
				case '5':
					CURRENT_USER = -1;
					print("Logging out...\n");
					break;
				case '6':
					print("Exiting...\n");
					_terminate(0);
					break;
				case 'a':
					AdminLogin();
					break;
				default:
					print("[-] Invalid choice\n");
					continue;
			}
		}
	}

	return(0);
}
