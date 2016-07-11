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
#include "message.h"
#include "stdlib.h"
#include "stdint.h"
#include "user.h"


int msg_count_login;

// dirty grouping of global variables
typedef struct
{
	Message listOfMessages[MAX_USERS][MAX_MESSAGES];
	void (*printer)();
} GLOBALS;

GLOBALS globs;

void print_message(int user_offset, int msg_offset)
{
	if (!strcmp(globs.listOfMessages[user_offset][msg_offset].to, ""))
		return;
	printf("******************\n");
	printf("To: @s\nFrom: @s \nMsg: @s\n", globs.listOfMessages[user_offset][msg_offset].to, globs.listOfMessages[user_offset][msg_offset].from, globs.listOfMessages[user_offset][msg_offset].msg);		
}

// if draft == 1, this is a draft message
int add_message(char *dest, char *src, char *msg, char draft)
{
	globs.printer = print_message; // easy init

	char found = -1; // this will have the user's index if it is found

	// does the dest exist?
	for (int j = 0; j < user_count; j++)
	{
		if (!strcmp(dest, listOfUsers[j]->name))
		{
			found = j;
			break;
		}
	}
	if (found == -1)
	{
		printf("User does not exist.\n");
		return 0;
	}

	int target = -1;
	int index = -1;
	if (draft == 1)
		index = get_user_index(src);
	else
		index = get_user_index(dest);

	if (current_user->first_login == 1)
	{
		current_user->first_login = 0;

		// setting the target to the current msg_count allows a write past the end of the MAX_MESSAGES for this user
		// if this is the last user, it allows an overwrite of the function pointer 'printer'
		#ifndef PATCHED
		if (current_user->msg_count >= MAX_MESSAGES)
		{
			target = current_user->msg_count; // a naive person might assume this is zero...that's the problem
			goto label;
		}
		#endif
	}
	
	// add messages into blank spots
	#ifdef PATCHED
	for (int i = 0; i < MAX_MESSAGES; i++) 
	#else
	for (int i = 0; i < MAX_MESSAGES+1; i++) 
	#endif
	{
		if (globs.listOfMessages[index][i].match != 0xbeef)
		{
			// this message is not valid, replace it
			target = i;
			goto label;
		}
	}
label:
	{
		// without this check, users can write past the end of of their message queue
		// very simple buffer overrun
		if (target == -1)
		{
			//printf("target is neg 1 name: @s @d", current_user->name, current_user->msg_count);
			return 0;
		}

		Message *cur = &(globs.listOfMessages[index][target]);

		cur->match = 0xbeef;
		strcpy(cur->from, src);
		strcpy(cur->to, dest);
		strcpy(cur->msg, msg);
		cur->is_draft = draft;

		msg_count_login++;
		current_user->msg_count++;
		return 1;
	}
	return 0;
}

void list_drafts(char *name)
{
	int index = get_user_index(name);
	int found = 0;
	for (int i = 0; i < MAX_MESSAGES; i++)
	{
		if (globs.listOfMessages[index][i].match != 0xbeef) 
		{
			continue;
		}
		if (!strcmp(name, globs.listOfMessages[index][i].from) && (globs.listOfMessages[index][i].is_draft == 1))
		{
			found = 1;
			globs.printer(index, i);
		}
	}
	if (found == 0)
		printf("No drafts for this user.\n");
}

void list_inbox(char *name)
{
	// print all messages to the current user
	int index = get_user_index(name);
	int found = 0;
	for (int i = 0; i < MAX_MESSAGES; i++)
	{
		if (globs.listOfMessages[index][i].match != 0xbeef) 
		{
			continue;
		}
		if (!strcmp(name, globs.listOfMessages[index][i].to) && (globs.listOfMessages[index][i].is_draft == 0))
		{
			found = 1;
			globs.printer(index, i);
		}
	}
	if (found == 0)
		printf("No messages for this user.\n");
}

void list_all_messages()
{
	// print all messages
	int found = 0;
	for (int j = 0; j < user_count; j++)
	{
		for (int i = 0; i < MAX_MESSAGES; i++)
		{
			found = 1;
			globs.printer(j, i);
		}
	}
	if (found == 0)
		printf("No messages.\n");
}

int get_draft_count(char *name)
{
	int index = get_user_index(name);
	int count = 0;
	for (int i = 0; i < MAX_MESSAGES; i++)
	{
		if ((!strcmp(name, globs.listOfMessages[index][i].from)) && (globs.listOfMessages[index][i].is_draft == 1))
		{
			count += 1;
		}
	}
	return count;
}

int get_inbox_count(char *name)
{
	int count = 0;
	// print all messages to the current user
	int index = get_user_index(name);
	for (int i = 0; i < MAX_MESSAGES; i++)
	{
		if ((!strcmp(name, globs.listOfMessages[index][i].to)) && (globs.listOfMessages[index][i].is_draft == 0))
		{
			count++;
		}
	}
	return count;
}

int get_total_count()
{
	int count = 0;
	for (int j = 0; j < user_count; j++)
	{
		for (int i = 0; i < listOfUsers[j]->msg_count; i++)
		{
			count++;
		}
	}
	return count;
}

void print_draft_for_send(char *name)
{
	int my_index = get_user_index(name);
	int i = 0;
	for (i = 0; i < MAX_MESSAGES; i++)
	{
		if (globs.listOfMessages[my_index][i].match == 0xbeef)
		{
			// list all of this user's drafts
			if (!strcmp(name, globs.listOfMessages[my_index][i].from) && (globs.listOfMessages[my_index][i].is_draft == 1))
			{
				printf("@d: To: @s Msg: @s\n", i, globs.listOfMessages[my_index][i].to, globs.listOfMessages[my_index][i].msg);
			}
		}
	}

	char buf[4] = {0};
	size_t l = 0;
	while (l < 1)
		l = receive_until( buf, '\n', 3);

	int choice = atoi(&buf[0]);
	if (choice >= MAX_MESSAGES || choice < 0)
	{
		printf("Out of range.\n");
		return;
	}

	if (strcmp(name, globs.listOfMessages[my_index][choice].from) || (globs.listOfMessages[my_index][choice].is_draft != 1))
	{
		printf("Not a valid selection.\n");
		return;
	}

	// pointer to the current draft message
	Message *cur = &(globs.listOfMessages[my_index][choice]);

	// get the dest user's index
	int dst_index = get_user_index(globs.listOfMessages[my_index][choice].to);

	int target = -1;
	for (int i = 0; i < MAX_MESSAGES; i++)
	{
		if (globs.listOfMessages[dst_index][i].match != 0xbeef)
		{
			// this message is not valid, replace it
			target = i;
			break;
		}
	}
	if (target == -1)
	{
		printf("No space left for this user.\n");
		return;
	}
	// pointer to destination message 
	Message *dst_msg = &(globs.listOfMessages[dst_index][target]);

	strcpy(dst_msg->from, cur->from);
	strcpy(dst_msg->to, cur->to);
	strcpy(dst_msg->msg, cur->msg);
	dst_msg->is_draft = 0;
	dst_msg->match = 0xbeef;

	// remove from sender's array
	bzero(cur->to, MAX_NAME_LEN);
	bzero(cur->from, MAX_NAME_LEN);
	bzero(cur->msg, MAX_MSG_LEN);
	cur->match = 0;
}

void print_draft_for_del(char *name)
{
	int index = get_user_index(name);
	int i = 0;
	for (i = 0; i < MAX_MESSAGES; i++)
	{
		// for each message that is FROM this user, list it with a number
		if (!strcmp(name, globs.listOfMessages[index][i].from) && (globs.listOfMessages[index][i].is_draft == 1))
		{
			printf("@d: To: @s Msg: @s\n", i, globs.listOfMessages[index][i].to, globs.listOfMessages[index][i].msg);
		}
	}

	char buf[3] = {0};
	size_t l = 0;
	while (l < 1)
		l = receive_until( buf, '\n', 2);

	int choice = atoi(&buf[0]);
	if (choice >= MAX_MESSAGES || choice < 0)
	{
		printf("Out of range.\n");
		return;
	}

	if (strcmp(name, globs.listOfMessages[index][choice].from) || (globs.listOfMessages[index][choice].is_draft != 1))
	{
		printf("Not a valid selection.\n");
		return;
	}

	bzero(globs.listOfMessages[index][choice].to, MAX_NAME_LEN);
	bzero(globs.listOfMessages[index][choice].from, MAX_NAME_LEN);
	bzero(globs.listOfMessages[index][choice].msg, MAX_MSG_LEN);
	globs.listOfMessages[index][choice].match = 0;
	current_user->msg_count--;
}

