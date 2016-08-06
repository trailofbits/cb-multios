/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef COMMS_H
#define COMMS_H 1

#include <libcgc.h>

#define PACKED __attribute__((packed))

typedef struct session Session;
struct session {
	struct {
		char key[12];
		char username[12];
		char password[12];  
	} PACKED login;
	struct {
		char cmd[8];
		uint16_t bytes;
		char *data;
	} PACKED request;
	Session *next;
} PACKED;

typedef struct response Response;
struct response {
	char session_key[12];
	char answer[128];		// answer to command, if there is one
	char result[8];			// success/fail of request.
} PACKED;

Session *session_get_by_username(Session *s_list, Session *s);
void session_append(Session **s_list, Session *s);
Session *session_remove(Session **s_list, Session *s);

#endif