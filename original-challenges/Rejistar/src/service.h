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

#define MAX_AUTH_TYPE_SIZE 10
#define MAX_UINT_STR_SIZE 12
#define MAX_CMD_SIZE 16

#define QUIT_CMD "quit"

#define UP_AUTH_TYPE  "UserPass"

#define COMMAND_HDR "Command"
#define RESPONSE_HDR "Response"

#define DEFAULT_USER "user"
#define DEFAULT_PASS "pass"

#define RESPONSE_ERR_NO_AUTH "Failed Authentication"
#define RESPONSE_ERR_NO_SERVICE "Invalid Service"
#define RESPONSE_ERR_NO_MESSAGE "Invalid Message"

typedef struct {
 	int a;
  	void (* callback)(int, char*, unsigned int*);
 	char* name;
   	void* next;
} Service;

typedef struct {
	char* command;
	char auth[MAX_AUTH_TYPE_SIZE];
	int id;
	void* credential;
	char* body;
} Message;

typedef struct {
	char* username;
	char* password;
} UserPass;

unsigned int expiration_date=0;