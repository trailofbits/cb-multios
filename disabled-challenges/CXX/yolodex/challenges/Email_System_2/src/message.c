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
#include "cgc_message.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_user.h"


int cgc_msg_count_login;

// dirty grouping of global variables
typedef struct
{
	Message listOfMessages[MAX_USERS][MAX_MESSAGES];
	void (*printer)();
} GLOBALS;

GLOBALS globs;

void cgc_print_message(int user_offset, int msg_offset)
{
	if (!cgc_strcmp(globs.listOfMessages[user_offset][msg_offset].to, ""))
		return;
	cgc_printf("******************\n");
	cgc_printf("To: @s\nFrom: @s \nMsg: @s\n", globs.listOfMessages[user_offset][msg_offset].to, globs.listOfMessages[user_offset][msg_offset].from, globs.listOfMessages[user_offset][msg_offset].msg);		
}

// if draft == 1, this is a draft message
int cgc_add_message(char *dest, char *src, char *msg, char draft)
{
	globs.printer = cgc_print_message; // easy init

	char found = -1; // this will have the user's index if it is found

	// does the dest exist?
	for (int j = 0; j < cgc_user_count; j++)
	{
		if (!cgc_strcmp(dest, cgc_listOfUsers[j]->name))
		{
			found = j;
			break;
		}
	}
	if (found == -1)
	{
		cgc_printf("User does not exist.\n");
		return 0;
	}

	int target = -1;
	int index = -1;
	if (draft == 1)
		index = cgc_get_user_index(src);
	else
		index = cgc_get_user_index(dest);

	if (cgc_current_user->first_login == 1)
	{
		cgc_current_user->first_login = 0;

		// setting the target to the current msg_count allows a cgc_write past the end of the MAX_MESSAGES for this user
		// if this is the last user, it allows an overwrite of the function pointer 'printer'
		#ifndef PATCHED
		if (cgc_current_user->msg_count >= MAX_MESSAGES)
		{
			target = cgc_current_user->msg_count; // a naive person might assume this is zero...that's the problem
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
		// without this check, users can cgc_write past the end of of their message queue
		// very simple buffer overrun
		if (target == -1)
		{
			//cgc_printf("target is neg 1 name: @s @d", cgc_current_user->name, cgc_current_user->msg_count);
			return 0;
		}

		Message *cur = &(globs.listOfMessages[index][target]);

		cur->match = 0xbeef;
		cgc_strcpy(cur->from, src);
		cgc_strcpy(cur->to, dest);
		cgc_strcpy(cur->msg, msg);
		cur->is_draft = draft;

		cgc_msg_count_login++;
		cgc_current_user->msg_count++;
		return 1;
	}
	return 0;
}

void cgc_list_drafts(char *name)
{
	int index = cgc_get_user_index(name);
	int found = 0;
	for (int i = 0; i < MAX_MESSAGES; i++)
	{
		if (globs.listOfMessages[index][i].match != 0xbeef) 
		{
			continue;
		}
		if (!cgc_strcmp(name, globs.listOfMessages[index][i].from) && (globs.listOfMessages[index][i].is_draft == 1))
		{
			found = 1;
			globs.printer(index, i);
		}
	}
	if (found == 0)
		cgc_printf("No drafts for this user.\n");
}

void cgc_list_inbox(char *name)
{
	// print all messages to the current user
	int index = cgc_get_user_index(name);
	int found = 0;
	for (int i = 0; i < MAX_MESSAGES; i++)
	{
		if (globs.listOfMessages[index][i].match != 0xbeef) 
		{
			continue;
		}
		if (!cgc_strcmp(name, globs.listOfMessages[index][i].to) && (globs.listOfMessages[index][i].is_draft == 0))
		{
			found = 1;
			globs.printer(index, i);
		}
	}
	if (found == 0)
		cgc_printf("No messages for this user.\n");
}

void cgc_list_all_messages()
{
	// print all messages
	int found = 0;
	for (int j = 0; j < cgc_user_count; j++)
	{
		for (int i = 0; i < MAX_MESSAGES; i++)
		{
			found = 1;
			globs.printer(j, i);
		}
	}
	if (found == 0)
		cgc_printf("No messages.\n");
}

int cgc_get_draft_count(char *name)
{
	int index = cgc_get_user_index(name);
	int count = 0;
	for (int i = 0; i < MAX_MESSAGES; i++)
	{
		if ((!cgc_strcmp(name, globs.listOfMessages[index][i].from)) && (globs.listOfMessages[index][i].is_draft == 1))
		{
			count += 1;
		}
	}
	return count;
}

int cgc_get_inbox_count(char *name)
{
	int count = 0;
	// print all messages to the current user
	int index = cgc_get_user_index(name);
	for (int i = 0; i < MAX_MESSAGES; i++)
	{
		if ((!cgc_strcmp(name, globs.listOfMessages[index][i].to)) && (globs.listOfMessages[index][i].is_draft == 0))
		{
			count++;
		}
	}
	return count;
}

int cgc_get_total_count()
{
	int count = 0;
	for (int j = 0; j < cgc_user_count; j++)
	{
		for (int i = 0; i < cgc_listOfUsers[j]->msg_count; i++)
		{
			count++;
		}
	}
	return count;
}

void cgc_print_draft_for_send(char *name)
{
	int my_index = cgc_get_user_index(name);
	int i = 0;
	for (i = 0; i < MAX_MESSAGES; i++)
	{
		if (globs.listOfMessages[my_index][i].match == 0xbeef)
		{
			// list all of this user's drafts
			if (!cgc_strcmp(name, globs.listOfMessages[my_index][i].from) && (globs.listOfMessages[my_index][i].is_draft == 1))
			{
				cgc_printf("@d: To: @s Msg: @s\n", i, globs.listOfMessages[my_index][i].to, globs.listOfMessages[my_index][i].msg);
			}
		}
	}

	char buf[4] = {0};
	cgc_size_t l = 0;
	while (l < 1)
		l = cgc_receive_until( buf, '\n', 3);

	int choice = cgc_atoi(&buf[0]);
	if (choice >= MAX_MESSAGES || choice < 0)
	{
		cgc_printf("Out of range.\n");
		return;
	}

	if (cgc_strcmp(name, globs.listOfMessages[my_index][choice].from) || (globs.listOfMessages[my_index][choice].is_draft != 1))
	{
		cgc_printf("Not a valid selection.\n");
		return;
	}

	// pointer to the current draft message
	Message *cur = &(globs.listOfMessages[my_index][choice]);

	// get the dest user's index
	int dst_index = cgc_get_user_index(globs.listOfMessages[my_index][choice].to);

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
		cgc_printf("No space left for this user.\n");
		return;
	}
	// pointer to destination message 
	Message *dst_msg = &(globs.listOfMessages[dst_index][target]);

	cgc_strcpy(dst_msg->from, cur->from);
	cgc_strcpy(dst_msg->to, cur->to);
	cgc_strcpy(dst_msg->msg, cur->msg);
	dst_msg->is_draft = 0;
	dst_msg->match = 0xbeef;

	// remove from sender's array
	cgc_bzero(cur->to, MAX_NAME_LEN);
	cgc_bzero(cur->from, MAX_NAME_LEN);
	cgc_bzero(cur->msg, MAX_MSG_LEN);
	cur->match = 0;
}

void cgc_print_draft_for_del(char *name)
{
	int index = cgc_get_user_index(name);
	int i = 0;
	for (i = 0; i < MAX_MESSAGES; i++)
	{
		// for each message that is FROM this user, list it with a number
		if (!cgc_strcmp(name, globs.listOfMessages[index][i].from) && (globs.listOfMessages[index][i].is_draft == 1))
		{
			cgc_printf("@d: To: @s Msg: @s\n", i, globs.listOfMessages[index][i].to, globs.listOfMessages[index][i].msg);
		}
	}

	char buf[3] = {0};
	cgc_size_t l = 0;
	while (l < 1)
		l = cgc_receive_until( buf, '\n', 2);

	int choice = cgc_atoi(&buf[0]);
	if (choice >= MAX_MESSAGES || choice < 0)
	{
		cgc_printf("Out of range.\n");
		return;
	}

	if (cgc_strcmp(name, globs.listOfMessages[index][choice].from) || (globs.listOfMessages[index][choice].is_draft != 1))
	{
		cgc_printf("Not a valid selection.\n");
		return;
	}

	cgc_bzero(globs.listOfMessages[index][choice].to, MAX_NAME_LEN);
	cgc_bzero(globs.listOfMessages[index][choice].from, MAX_NAME_LEN);
	cgc_bzero(globs.listOfMessages[index][choice].msg, MAX_MSG_LEN);
	globs.listOfMessages[index][choice].match = 0;
	cgc_current_user->msg_count--;
}

