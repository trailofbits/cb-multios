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
#include "token.h"
#include "malloc.h"
#include "strncmp.h"
#include "cbstdio.h"
#include "memcpy.h"
#include "atoi.h"
#include "strtok.h"
#include "util.h"
#include "comms.h"
#include <libcgc.h>

unsigned int flag_index = 0;

/**
* Generate a new request ID and return
* 
*
* @return a request ID
*/
unsigned int getToken() {
	unsigned int requestBits[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	const unsigned char *flag = (const unsigned char*) FLAG_PAGE;
	unsigned int token = 1;

	for (unsigned int i = 0; i < 10; i++) {
		if((flag[flag_index+i] % requestBits[i]) == 0)
			token = token * requestBits[i];
	}


	flag_index += 10;

	while (token < 10000000) {
		token = token * 10;
	}

	while (token > 99999999) {
		token = token / 10;
	}

	return token;
}

/**
* Is the command a valud Token command
* 
* @param command the command string
*
* @return 1 if true, 0 if false
*/
int isTokenCommand(char* command) {

	if(!strncmp(command, TOKEN_CMD, strlen(TOKEN_CMD)))
		return 1;

	if(!strncmp(command, REFRESH_CMD, strlen(REFRESH_CMD)))
		return 1;

	if(!strncmp(command, REVOKE_TOKEN_CMD, strlen(REVOKE_TOKEN_CMD)))
		return 1;

	return 0;
}

/**
* Calculate how many bytes are needed to store the Token as a string
* 
* @param token The address of the Token
*
* @return The number of bytes to store the Token as a string
*/
size_t calculateTokenSize(Token *token) {
	size_t size, token_val_sz, token_exp_sz;
	char buffer[20];

	bzero(buffer, 20);
	sprintf(buffer, "!U", token->value);
	token_val_sz = strlen(buffer);

	bzero(buffer, 20);
	sprintf(buffer, "!U", token->expiration);
	token_exp_sz = strlen(buffer);

	size = strlen(TOKEN_HDR)+ 1;
	size += token_val_sz + 1;
	size += strlen(TOKEN_EXP_HDR)+ 1;
	size += token_exp_sz + 1;
	size += sizeof(TOKEN_USE_HDR) + 1;
	size += strlen(token->use);

	return size;
}

/**
* Send the token as a string to the requestor
* 
* @param id The id of the initial requesting message
* @param token The token to send
*
* @return None
*/
void sendToken(unsigned int id, Token *token) {
	const char *flag = (const char*) FLAG_PAGE;
	char* flag_buf=0;
	size_t bytes, tokenSize;
	char* buffer;
	int ret;

	tokenSize = calculateTokenSize(token);
#ifdef PATCHED_2
	if(!(buffer = malloc(tokenSize+1)))
		_terminate(1);
#else
	if(!(buffer = malloc(tokenSize)))
		_terminate(1);
#endif
	bzero(buffer, tokenSize+1);

	if(!(flag_buf = malloc(64)))
		_terminate(ALLOCATE_ERROR);
	bzero(flag_buf, 64);

	for (unsigned int i = 0; i < 10; i++) {
		sprintf(&flag_buf[i*4], "!H", (unsigned char) *flag++);
	}

	sprintf(buffer, "!X=!U;!X=!U;!X=!X?",
		TOKEN_HDR, token->value,
		TOKEN_EXP_HDR, token->expiration,
		TOKEN_USE_HDR, token->use);

	tokenSize = strlen(buffer);
	if((ret = transmit_all(STDOUT, buffer, tokenSize))) 
		_terminate(1);
	free(buffer);
	free(flag_buf);

}

/**
* Find the token in the list of tokens
* 
* @param token The token to find
*
* @return The address of the found token, or NULL if not found
*/
Token* findToken(Token *token) {
	Token *found;

	for(found=tokenStore; found != NULL; found=found->next) {
		if(found->value == token->value)
			return found;
	}

	return NULL;
}

/**
* Remove the token from the list of tokens
* 
* @param token The address of the token to remove
*
* @return 1 if removed, 0 if not
*/
int removeToken(Token* token) {
	Token *prev=NULL, *tok_ptr;

	for(tok_ptr=tokenStore, prev=tokenStore; tok_ptr != NULL; tok_ptr=tok_ptr->next) {
		if(token->value == tok_ptr->value) {
			if(prev != NULL)
				prev->next = tok_ptr->next;
			free(token);
			return 1;
		}
		prev = tok_ptr;
	}

	return 0;
}

/**
* Ensure the token is valid
* 
* @param token The address of the token to check
* @param expiration_date The current date
*
* @return 1 if certificate is valid, 0 if it is not
*/
int validateToken(Token* token, unsigned int* expiration_date) {
	Token *found;

	if(!token->value || !token->use || !token->expiration) {
		sendErrorResponse(RESPONSE_ERR_NO_TOK);

		return 0;
	}

	if(!(found = findToken(token))) {
		sendErrorResponse(RESPONSE_ERR_NO_TOK);

		return 0;
	}

	if(found->expiration > *expiration_date)
		return 1;

	removeToken(found);
	sendErrorResponse(RESPONSE_ERR_EXP_TOK);
	
	return 0;
}

/**
* Parse the buffer as a Token
* 
* @param buffer The buffer that contains the token
*
* @return The address of the new Token
*/
Token* parseToken(char* body) {
	Token* token;
	char *command, *val_str;
	size_t size;

	if(!(token = malloc(sizeof(Token))))
		_terminate(1);
	bzero((char *)token, sizeof(Token));
	if(!token)
		_terminate(1);

	initializeAttributes(body);
	getStringAttribute(&token->use, TOKEN_USE_HDR);
	getIntegerAttribute(&token->value, TOKEN_HDR);
	getIntegerAttribute(&token->expiration, TOKEN_EXP_HDR);

	return token;
}

/**
* Refresh the expiration date of the token
* 
* @param id The id of the initial requesting message
* @param body The body of the requesting message
* @param expiration_date The current date
*
* @return None
*/
void refreshToken(int id, char* body, unsigned int* expiration_date) {
	Token *token, *found;

	if(!(token = parseToken(body)))
		return;

	if(!(found = findToken(token)))
		return;

	if(found->expiration > *expiration_date) {
		*expiration_date += 1;
		found->expiration = *expiration_date+100;
		sendToken(id, token);
	} else {
		removeToken(token);
		sendErrorResponse(RESPONSE_ERR_EXP_TOK);
	}

}

/**
* Request a new token
* 
* @param id The id of the initial requesting message
* @param body The body of the requesting message
* @param expiration_date The current date
*
* @return None
*/
void requestToken(int id, char* body, unsigned int* expiration_date) {
	Token* token;
	size_t bytes;
	int ret;

	if(!(token = parseToken(body)))
		return;

	/*
	if((ret = random(&token->value, sizeof(token->value), &bytes)))
		_terminate(1);

	if(bytes != sizeof(token->value))
		_terminate(1);
	*/

	token->value = getToken();
	*expiration_date += 1;
	token->expiration = *expiration_date + 100;

	sendToken(id, token);

	token->next = tokenStore;
	tokenStore = token;

}

/**
* Check that the token is allowed to be used for the command
* 
* @param command The command the requestor wants to use the token for
* @param useList The list of uses contained in the token
*
* @return 1 if use is valid, 0 if it is not
*/
int checkTokenUse(char* command, char* useList) {
	char* use;
	size_t size, size1, size2;

	if(!useList)
		return 0;

	use = strtok(useList,":");
	do {
		size1 = strlen(command);
		size2 = strlen(use);
		size = size1 > size2 ? size1 : size2;
		if(!strncmp(command, use, strlen(command)) ||
			!strncmp(REVOKE_TOKEN_CMD, command, strlen(REVOKE_TOKEN_CMD)))
			return 1;

		use = strtok(0, ":");
	} while(use);

	return 0;

}

/**
* Revoke a token
* 
* @param id The id of the initial requesting message
* @param body The body of the requesting message
* @param expiration_date The current date
*
* @return None
*/
void revokeToken(int id, char* body, unsigned int* expiration_date) {
	Token *token, *found;
	int ret;
	size_t size;

	if(!(token = parseToken(body)))
		return;

	if(removeToken(token)) {
		sendErrorResponse(RESPONSE_TOKEN_REVOKED);
	} else
		sendErrorResponse(RESPONSE_ERR_NO_TOK);

	return;

}