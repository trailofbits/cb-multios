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

#include "libcgc.h"
#include "cgc_user.h"
#include "cgc_message.h"
#include "cgc_stdlib.h"

int bad_login_count;

void cgc_print_A()
{
	cgc_printf("******************\n");
	cgc_printf("1. Create User\n");
	cgc_printf("2. Login\n");
	cgc_printf("3. Exit\n");
	cgc_printf(": \n");
}


int cgc_handle_A_input()
{
	char buf[3] = {0};
	// same for all users
	// handle create user
	// handle login
	// handle cgc_exit
	cgc_size_t l = 0;
	while (l < 1)
		l = cgc_receive_until( buf, '\n', 2);

	if (buf[0] == '1')
	{
		// CREATE USER
		cgc_create_user(0);
	}
	else if (buf[0] == '2')
	{
		// LOGIN

		cgc_list_users();

		char name[MAX_NAME_LEN];
		char pswd[MAX_PASS_LEN];

		cgc_printf("Username: \n");
		cgc_size_t len = cgc_receive_until( name, '\n', MAX_NAME_LEN - 1);
		name[len++] = 0;
		cgc_printf("Password: \n");
		len = cgc_receive_until( pswd, '\n', MAX_PASS_LEN - 1);
		pswd[len++] = 0;

		cgc_msg_count_login = 0;

		if (cgc_login(name, pswd) == 1)
		{
			// successful login
			
			return 2;
		}
		else
		{
			cgc_printf("Bad login.\n");
			bad_login_count++;
			if (bad_login_count >= 3)
			{
				cgc_create_user(bad_login_count); // this allows a user to be re-created
				bad_login_count = 0;
			}
		}
	}
	else if (buf[0] == '3')
	{
		// EXIT
		cgc_printf("The end.\n");
		cgc__terminate(0);
	}
	else
		cgc_printf("unknown input: @c @c\n", buf[0], buf[1]);
	return 0;
}

void cgc_print_B()
{
	cgc_printf("********@s********\n", cgc_current_user->name);
	cgc_printf("1. Create Message\n");
	cgc_printf("2. Send Message\n");
	cgc_printf("3. List All [@d]\n", cgc_get_total_count());
	cgc_printf("4. List Drafts [@d]\n", cgc_get_draft_count(cgc_current_user->name));
	cgc_printf("5. List Inbox [@d]\n", cgc_get_inbox_count(cgc_current_user->name));
	cgc_printf("6. Delete Draft\n");
	cgc_printf("7. Logout\n");
	cgc_printf("8. Exit\n");
	cgc_printf(": \n");
}

int cgc_handle_B_input()
{
	char buf[3] = {0};
	cgc_size_t l = 0;
	while (l < 1)
		l = cgc_receive_until( buf, '\n', 2);

	if (buf[0] == '7')
	{
		// LOGOUT
		cgc_printf("Logging out of user @s\n", cgc_current_user->name);
		cgc_logout();
		return 2;
	}
	else if (buf[0] == '8')
	{
		// EXIT
		cgc_printf("The end.\n");
		cgc__terminate(0);
	}
	else if (buf[0] == '2')
	{
		// SEND MESSAGE from drafts list
		if (cgc_get_draft_count(cgc_current_user->name) == 0)
		{
			cgc_printf("Must create draft first.\n");
			return 0;
		}

		// list all drafts with number in front
		// user enters valid number
		// that message is changed from drafts 1->0
		cgc_print_draft_for_send(cgc_current_user->name);
	}
	else if (buf[0] == '1')
	{
		// ADD A MESSAGE TO DRAFTS
		if (cgc_msg_count_login >= MAX_MESSAGES_LOGIN)
		{
			cgc_printf("Reached maximum messages for this session.\n");
			return 0;
		}

		cgc_printf("To:\n");

		char dest[MAX_NAME_LEN];
		cgc_size_t len = cgc_receive_until( dest, '\n', MAX_NAME_LEN - 1);
		dest[len++] = 0;

		cgc_printf("Message:\n");
		char msg_buf[MAX_MSG_LEN];
		len = cgc_receive_until( msg_buf, '\n', MAX_MSG_LEN - 1);
		msg_buf[len++] = 0;

		if (cgc_add_message(dest, cgc_current_user->name, msg_buf, 1) != 1)
			cgc_printf("add_message failed\n");
	}
	else if (buf[0] == '3')
	{
		// LIST MESSAGES
		// list all messages in summary
		if (cgc_get_total_count() == 0)
		{
			cgc_printf("No messages.\n");
			return 0;
		}

		cgc_list_all_messages();
	}
	else if (buf[0] == '4')
	{
		// LIST DRAFTS
		cgc_list_drafts(cgc_current_user->name);
	}
	else if (buf[0] == '5')
	{
		// LIST INCOMING MSGS
		cgc_list_inbox(cgc_current_user->name);
	}
	else if (buf[0] == '6')
	{
		// DELETE MESSAGE from drafts list
		if (cgc_get_draft_count(cgc_current_user->name) == 0)
		{
			cgc_printf("Must create draft first.\n");
			return 0;
		}
		cgc_print_draft_for_del(cgc_current_user->name);
	}
	else
		cgc_printf("unknown input: @c @c", buf[0], buf[1]);
	return 0;
}

int main(int cgc_argc, char *cgc_argv[])
{
	cgc_msg_count_login = 0;
	cgc_user_count = 0;
	bad_login_count = 0;

A_menu:
	while (1)
	{
		cgc_print_A();
		if (cgc_handle_A_input() == 2)
			goto B_menu;
	}

B_menu:
	while (1)
	{
		cgc_print_B();
		if (cgc_handle_B_input() == 2)
			goto A_menu;
	}
	
	return 0;
}
