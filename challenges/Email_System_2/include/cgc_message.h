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
#include "cgc_common.h"


typedef struct 
{
	int match;
	char to[MAX_NAME_LEN];
	char from[MAX_NAME_LEN];
	char msg[MAX_MSG_LEN];
	char is_draft;
} Message;

extern int cgc_msg_count_login;

int cgc_add_message(char *, char *, char *, char);
void cgc_list_inbox(char *);
void cgc_list_drafts(char *);
void cgc_list_all_messages();
int cgc_get_total_count();
int cgc_get_draft_count(char *);
int cgc_get_inbox_count(char *);
void cgc_print_draft_for_send(char *);
void cgc_print_draft_for_del(char *);