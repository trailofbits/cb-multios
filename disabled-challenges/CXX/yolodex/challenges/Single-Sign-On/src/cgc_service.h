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

#ifndef SERVICE_H
#define SERVICE_H

#define RESOURCE_SIZE 10
#define MAX_ARGS_SIZE 4600
#define CMD_TYPE_SIZE 4
#define MAX_COMMAND_SIZE  CMD_TYPE_SIZE+sizeof(long)+MAX_ARGS_SIZE
#define FAILED_AUTH_STR "Authentication failed for resource "
#define ACCESS_STR "Access to "
#define SUCCESS_AUTH_STR " is granted!"
#define ACCESS_GRANTED_STR "Access granted!\n"
#define EOL "\n"
#define REAUTH_STR "Please re-authenticate.\n"
#define AUTH_STR "Please log in.\n"
#define LOGGED_OUT_STR "Logged out successfully.\n"
#define CMD_FAIL_STR "Command failed.\n"
#define REVOKE_DENIED_STR "Revocation denied.\n"
#define RES_REVOKED_STR "Resource revoked.\n"

#define REQUEST_CMD "REQR"
#define AUTH_CMD "AUTH"
#define LOGOUT_CMD "LOUT"
#define REVOKE_RESOURCE_CMD "REVR"

#define TRANSMIT_ERROR 1
#define RECEIVE_ERROR 2
#define ALLOCATE_ERROR 3
#define DEALLOCATE_ERROR 4
#define RANDOM_ERROR 5

#define AUTH_FAIL 0
#define AUTH_SUCCESS 1
#define NOT_FOUND 0
#define ACCESS_REVOKED 1

typedef struct {
	char type[4];
	unsigned long id;
	unsigned long token;
	char input[MAX_ARGS_SIZE];
} Command;

typedef struct resource_t {
	struct resource_t *next;
	char name[RESOURCE_SIZE];
	unsigned long token;
} Resource;

typedef struct user_t {
	struct user_t *next;
	unsigned long id;
	unsigned long token;
	Resource* resourceList;
} User;

#endif