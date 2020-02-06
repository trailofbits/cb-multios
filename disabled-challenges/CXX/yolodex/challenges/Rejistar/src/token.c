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
#include "cgc_token.h"
#include "cgc_malloc.h"
#include "cgc_strncmp.h"
#include "cgc_cbstdio.h"
#include "cgc_memcpy.h"
#include "cgc_atoi.h"
#include "cgc_strtok.h"
#include "cgc_util.h"
#include "cgc_comms.h"
#include "libcgc.h"

unsigned int cgc_flag_index = 0;

/**
* Generate a new request ID and return
* 
*
* @return a request ID
*/
unsigned int cgc_getToken() {
	unsigned int requestBits[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	const unsigned char *flag = (const unsigned char*) FLAG_PAGE;
	unsigned int token = 1;

	for (unsigned int i = 0; i < 10; i++) {
		if((flag[cgc_flag_index+i] % requestBits[i]) == 0)
			token = token * requestBits[i];
	}


	cgc_flag_index += 10;

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
int cgc_isTokenCommand(char* command) {

	if(!cgc_strncmp(command, TOKEN_CMD, cgc_strlen(TOKEN_CMD)))
		return 1;

	if(!cgc_strncmp(command, REFRESH_CMD, cgc_strlen(REFRESH_CMD)))
		return 1;

	if(!cgc_strncmp(command, REVOKE_TOKEN_CMD, cgc_strlen(REVOKE_TOKEN_CMD)))
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
cgc_size_t cgc_calculateTokenSize(Token *token) {
	cgc_size_t size, token_val_sz, token_exp_sz;
	char buffer[20];

	cgc_bzero(buffer, 20);
	cgc_sprintf(buffer, "!U", token->value);
	token_val_sz = cgc_strlen(buffer);

	cgc_bzero(buffer, 20);
	cgc_sprintf(buffer, "!U", token->expiration);
	token_exp_sz = cgc_strlen(buffer);

	size = cgc_strlen(TOKEN_HDR)+ 1;
	size += token_val_sz + 1;
	size += cgc_strlen(TOKEN_EXP_HDR)+ 1;
	size += token_exp_sz + 1;
	size += sizeof(TOKEN_USE_HDR) + 1;
	size += cgc_strlen(token->use);

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
void cgc_sendToken(unsigned int id, Token *token) {
	const char *flag = (const char*) FLAG_PAGE;
	char* flag_buf=0;
	cgc_size_t bytes, tokenSize;
	char* buffer;
	int ret;

	tokenSize = cgc_calculateTokenSize(token);
#ifdef PATCHED_2
	if(!(buffer = cgc_malloc(tokenSize+1)))
		cgc__terminate(1);
#else
	if(!(buffer = cgc_malloc(tokenSize)))
		cgc__terminate(1);
#endif
	cgc_bzero(buffer, tokenSize+1);

	if(!(flag_buf = cgc_malloc(64)))
		cgc__terminate(ALLOCATE_ERROR);
	cgc_bzero(flag_buf, 64);

	for (unsigned int i = 0; i < 10; i++) {
		cgc_sprintf(&flag_buf[i*4], "!H", (unsigned char) *flag++);
	}

	cgc_sprintf(buffer, "!X=!U;!X=!U;!X=!X?",
		TOKEN_HDR, token->value,
		TOKEN_EXP_HDR, token->expiration,
		TOKEN_USE_HDR, token->use);

	tokenSize = cgc_strlen(buffer);
	if((ret = cgc_transmit_all(STDOUT, buffer, tokenSize))) 
		cgc__terminate(1);
	cgc_free(buffer);
	cgc_free(flag_buf);

}

/**
* Find the token in the list of tokens
* 
* @param token The token to find
*
* @return The address of the found token, or NULL if not found
*/
Token* cgc_findToken(Token *token) {
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
int cgc_removeToken(Token* token) {
	Token *prev=NULL, *tok_ptr;

	for(tok_ptr=tokenStore, prev=tokenStore; tok_ptr != NULL; tok_ptr=tok_ptr->next) {
		if(token->value == tok_ptr->value) {
			if(prev != NULL)
				prev->next = tok_ptr->next;
			cgc_free(token);
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
int cgc_validateToken(Token* token, unsigned int* expiration_date) {
	Token *found;

	if(!token->value || !token->use || !token->expiration) {
		cgc_sendErrorResponse(RESPONSE_ERR_NO_TOK);

		return 0;
	}

	if(!(found = cgc_findToken(token))) {
		cgc_sendErrorResponse(RESPONSE_ERR_NO_TOK);

		return 0;
	}

	if(found->expiration > *expiration_date)
		return 1;

	cgc_removeToken(found);
	cgc_sendErrorResponse(RESPONSE_ERR_EXP_TOK);
	
	return 0;
}

/**
* Parse the buffer as a Token
* 
* @param buffer The buffer that contains the token
*
* @return The address of the new Token
*/
Token* cgc_parseToken(char* body) {
	Token* token;
	char *command, *val_str;
	cgc_size_t size;

	if(!(token = cgc_malloc(sizeof(Token))))
		cgc__terminate(1);
	cgc_bzero((char *)token, sizeof(Token));
	if(!token)
		cgc__terminate(1);

	cgc_initializeAttributes(body);
	cgc_getStringAttribute(&token->use, TOKEN_USE_HDR);
	cgc_getIntegerAttribute(&token->value, TOKEN_HDR);
	cgc_getIntegerAttribute(&token->expiration, TOKEN_EXP_HDR);

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
void cgc_refreshToken(int id, char* body, unsigned int* expiration_date) {
	Token *token, *found;

	if(!(token = cgc_parseToken(body)))
		return;

	if(!(found = cgc_findToken(token)))
		return;

	if(found->expiration > *expiration_date) {
		*expiration_date += 1;
		found->expiration = *expiration_date+100;
		cgc_sendToken(id, token);
	} else {
		cgc_removeToken(token);
		cgc_sendErrorResponse(RESPONSE_ERR_EXP_TOK);
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
void cgc_requestToken(int id, char* body, unsigned int* expiration_date) {
	Token* token;
	cgc_size_t bytes;
	int ret;

	if(!(token = cgc_parseToken(body)))
		return;

	/*
	if((ret = cgc_random(&token->value, sizeof(token->value), &bytes)))
		cgc__terminate(1);

	if(bytes != sizeof(token->value))
		cgc__terminate(1);
	*/

	token->value = cgc_getToken();
	*expiration_date += 1;
	token->expiration = *expiration_date + 100;

	cgc_sendToken(id, token);

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
int cgc_checkTokenUse(char* command, char* useList) {
	char* use;
	cgc_size_t size, size1, size2;

	if(!useList)
		return 0;

	use = cgc_strtok(useList,":");
	do {
		size1 = cgc_strlen(command);
		size2 = cgc_strlen(use);
		size = size1 > size2 ? size1 : size2;
		if(!cgc_strncmp(command, use, cgc_strlen(command)) ||
			!cgc_strncmp(REVOKE_TOKEN_CMD, command, cgc_strlen(REVOKE_TOKEN_CMD)))
			return 1;

		use = cgc_strtok(0, ":");
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
void cgc_revokeToken(int id, char* body, unsigned int* expiration_date) {
	Token *token, *found;
	int ret;
	cgc_size_t size;

	if(!(token = cgc_parseToken(body)))
		return;

	if(cgc_removeToken(token)) {
		cgc_sendErrorResponse(RESPONSE_TOKEN_REVOKED);
	} else
		cgc_sendErrorResponse(RESPONSE_ERR_NO_TOK);

	return;

}