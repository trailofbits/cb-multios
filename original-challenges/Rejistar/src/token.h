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
#define FLAG_PAGE 0x4347C000

#define TOKEN_AUTH_TYPE  "Token"

#define TOKEN_CMD "newTokens"
#define REFRESH_CMD "refreshToken"
#define REVOKE_TOKEN_CMD "revokeT"

#define TOKEN_HDR "Token"
#define TOKEN_EXP_HDR "Expiration"
#define TOKEN_USE_HDR "Use"
#define TOKEN_VALUE_SIZE 8

#define COMMAND_HDR "Command"

#define RESPONSE_ERR_EXP_TOK "Expired Token"
#define RESPONSE_ERR_NO_TOK "Invalid Token"
#define RESPONSE_TOKEN_REVOKED "Token Revoked"

typedef struct {
	unsigned int expiration;
	char* use;
	unsigned int value;
	void* next;
} Token;

Token *tokenStore;

Token* parseToken(char* body);
int validateToken(Token* token, unsigned int* expiration_date);
int checkTokenUse(char* command, char* useList);
int isTokenCommand(char* command);

void requestToken(int id, char* body, unsigned int* expiration_date);
void refreshToken(int id, char* body, unsigned int* expiration_date);
void revokeToken(int id, char* body, unsigned int* expiration_date);
