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
#include "subscription.h"
#define VALID_TOKEN 1

#define INVALID_TOKEN 0
#define TOKEN_SIZE 40

#define VALID_SIGNATURE 1
#define INVALID_SIGNATURE 0

#define INVALID_SIG_MESSAGE "Invalid Signature.\n"

typedef struct {
	char* token;
	char* name;
	char* password;
	unsigned char* signingKey;
	Subscription* subscriptions;
	void* next;
} User;

typedef struct {
	char* name;
	unsigned char* signature;
	Subscription* subscriptions;
} AuthResponse;

unsigned int authenticateToken(User* users, char* token);
User* getUserByName(User* users, char* name);
User* getUserByToken(User* users, char* token);
User* newToken(User* user);
User* newUser(User** usersPtr, char* name, char* password);
unsigned int verifySignature(AuthResponse* response, unsigned char* signingKey);
char* computeSignature(User* user);