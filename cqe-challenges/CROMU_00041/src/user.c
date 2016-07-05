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
#include "stdlib.h"
#include "stdint.h"


User *current_user;

User *listOfUsers[MAX_USERS];
int user_count;

// successful login: 1, currentUser is correct
// bad login: 0
int login(char *name, char *passwd)
{
	// compare username and password with users
	for (int i = 0; i < user_count; i++)
	{
		if ((strcmp(name, listOfUsers[i]->name) == 0) && (!strcmp(passwd, listOfUsers[i]->password)))
		{
			current_user = listOfUsers[i];
			return 1;
		}
	}
	return 0;
}

int logout()
{
	current_user->first_login = 0;
	return 1;
}

int get_user_index(char *name)
{
	for (int i = 0; i < user_count; i++)
	{
		if (strcmp(name, listOfUsers[i]->name) == 0)
		{
			return i;
		}
	}
	return -1;
}

void create_user(int tries)
{	
	char buf[MAX_NAME_LEN];
	char buf2[MAX_PASS_LEN];
	printf("Username: \n");
	size_t len = receive_until( buf, '\n', MAX_NAME_LEN - 1);
	buf[len++] = 0;

	int found = -1;
	// does this user already exist?
	if (strlen(buf) < 1) 
	{
		return;
	}
	for (int j = 0; j < user_count; j++)
	{
		if (!strcmp(buf, listOfUsers[j]->name))
		{
			found = j;
			break;
		}
	}

	// user tried a bad password 3x, reset password
	if (tries > 0)
	{
		if (found == -1) 
		{
			// Failed login, but username not found. Do nothing
			return;
		}
		
		// this user already found, put this user on top of the last one
		// replace password
		// first login

		listOfUsers[found]->first_login = 1;
		printf("Password: \n");
		len = receive_until( buf2, '\n', MAX_PASS_LEN - 1);
		buf2[len++] = 0;
		bzero(listOfUsers[found]->password, MAX_PASS_LEN);
		strncpy(listOfUsers[found]->password, buf2, len);
		return;
	}

	if (found == -1)
	{
		// this user doesn't exist, are we full already?
		if (user_count >= MAX_USERS)
		{
			printf("Maximum number of users reached.\n");
			return;
		}
		else
		{
			listOfUsers[user_count] = (User*)malloc(sizeof(User));
			strncpy(listOfUsers[user_count]->name, buf, len);

			listOfUsers[user_count]->index = user_count;
			listOfUsers[user_count]->first_login = 1;
			listOfUsers[user_count]->msg_count = 0;
			
			printf("Password: \n");
			len = receive_until( buf2, '\n', MAX_PASS_LEN - 1);
			buf2[len++] = 0;
			strncpy(listOfUsers[user_count++]->password, buf2, len);
		}
	}
}

void list_users()
{
	for (int i = 0; i < user_count; i++)
	{
		printf("@s -- @s\n", listOfUsers[i]->name, listOfUsers[i]->password);
	}
}
