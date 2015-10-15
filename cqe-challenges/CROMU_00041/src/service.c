/*

Author: James Nuttall (james@cromulence.co)

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

#include <libcgc.h>
#include "user.h"
#include "message.h"
#include "stdlib.h"

int bad_login_count;

void print_A()
{
	printf("******************\n");
	printf("1. Create User\n");
	printf("2. Login\n");
	printf("3. Exit\n");
	printf(": \n");
}


int handle_A_input()
{
	char buf[3] = {0};
	// same for all users
	// handle create user
	// handle login
	// handle exit
	size_t l = 0;
	while (l < 1)
		l = receive_until( buf, '\n', 2);

	if (buf[0] == '1')
	{
		// CREATE USER
		create_user(0);
	}
	else if (buf[0] == '2')
	{
		// LOGIN

		list_users();

		char name[MAX_NAME_LEN];
		char pswd[MAX_PASS_LEN];

		printf("Username: \n");
		size_t len = receive_until( name, '\n', MAX_NAME_LEN - 1);
		name[len++] = 0;
		printf("Password: \n");
		len = receive_until( pswd, '\n', MAX_PASS_LEN - 1);
		pswd[len++] = 0;

		msg_count_login = 0;

		if (login(name, pswd) == 1)
		{
			// successful login
			
			return 2;
		}
		else
		{
			printf("Bad login.\n");
			bad_login_count++;
			if (bad_login_count >= 3)
			{
				create_user(bad_login_count); // this allows a user to be re-created
				bad_login_count = 0;
			}
		}
	}
	else if (buf[0] == '3')
	{
		// EXIT
		printf("The end.\n");
		_terminate(0);
	}
	else
		printf("unknown input: @c @c\n", buf[0], buf[1]);
	return 0;
}

void print_B()
{
	printf("********@s********\n", current_user->name);
	printf("1. Create Message\n");
	printf("2. Send Message\n");
	printf("3. List All [@d]\n", get_total_count());
	printf("4. List Drafts [@d]\n", get_draft_count(current_user->name));
	printf("5. List Inbox [@d]\n", get_inbox_count(current_user->name));
	printf("6. Delete Draft\n");
	printf("7. Logout\n");
	printf("8. Exit\n");
	printf(": \n");
}

int handle_B_input()
{
	char buf[3] = {0};
	size_t l = 0;
	while (l < 1)
		l = receive_until( buf, '\n', 2);

	if (buf[0] == '7')
	{
		// LOGOUT
		printf("Logging out of user @s\n", current_user->name);
		logout();
		return 2;
	}
	else if (buf[0] == '8')
	{
		// EXIT
		printf("The end.\n");
		_terminate(0);
	}
	else if (buf[0] == '2')
	{
		// SEND MESSAGE from drafts list
		if (get_draft_count(current_user->name) == 0)
		{
			printf("Must create draft first.\n");
			return 0;
		}

		// list all drafts with number in front
		// user enters valid number
		// that message is changed from drafts 1->0
		print_draft_for_send(current_user->name);
	}
	else if (buf[0] == '1')
	{
		// ADD A MESSAGE TO DRAFTS
		if (msg_count_login >= MAX_MESSAGES_LOGIN)
		{
			printf("Reached maximum messages for this session.\n");
			return 0;
		}

		printf("To:\n");

		char dest[MAX_NAME_LEN];
		size_t len = receive_until( dest, '\n', MAX_NAME_LEN - 1);
		dest[len++] = 0;

		printf("Message:\n");
		char msg_buf[MAX_MSG_LEN];
		len = receive_until( msg_buf, '\n', MAX_MSG_LEN - 1);
		msg_buf[len++] = 0;

		if (add_message(dest, current_user->name, msg_buf, 1) != 1)
			printf("add_message failed\n");
	}
	else if (buf[0] == '3')
	{
		// LIST MESSAGES
		// list all messages in summary
		if (get_total_count() == 0)
		{
			printf("No messages.\n");
			return 0;
		}

		list_all_messages();
	}
	else if (buf[0] == '4')
	{
		// LIST DRAFTS
		list_drafts(current_user->name);
	}
	else if (buf[0] == '5')
	{
		// LIST INCOMING MSGS
		list_inbox(current_user->name);
	}
	else if (buf[0] == '6')
	{
		// DELETE MESSAGE from drafts list
		if (get_draft_count(current_user->name) == 0)
		{
			printf("Must create draft first.\n");
			return 0;
		}
		print_draft_for_del(current_user->name);
	}
	else
		printf("unknown input: @c @c", buf[0], buf[1]);
	return 0;
}

int main()
{
	msg_count_login = 0;
	user_count = 0;
	bad_login_count = 0;

A_menu:
	while (1)
	{
		print_A();
		if (handle_A_input() == 2)
			goto B_menu;
	}

B_menu:
	while (1)
	{
		print_B();
		if (handle_B_input() == 2)
			goto A_menu;
	}
	
	return 0;
}
