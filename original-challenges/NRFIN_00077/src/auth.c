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
#include "auth.h"
#include "libc.h"

char* privateKey=NULL;

/**
 * Locate a user with the same token
 * @param  users The current list of users
 * @param  token The token to find
 * @return       VALID_TOKEN if a user with the same token is found,
 *               INVALID_TOKEN otherwise.
 */
unsigned int authenticateToken(User* users, char* token) {

	for(User* user=users; user!=NULL; user=user->next) {
		if(user->token && !strcmp(user->token, token)) 
			return VALID_TOKEN;
	}

	return INVALID_TOKEN;
}

/**
 * Generate a random token of the requested size
 * @param  tokenSize the size of the request token
 * @return           The address of the generated token string
 */
char* generateRandomToken(unsigned int tokenSize) {
	char* token;
	unsigned int idx=0;
	char randomBuffer[1024];
	size_t rnd_bytes;

	if(tokenSize > 1024) {
		return NULL;
	}

	if(!(token = malloc(tokenSize+1)))
		return NULL;

	memset(token, 0, tokenSize+1);

	if(random((void*)randomBuffer, sizeof(randomBuffer), &rnd_bytes))
		return NULL;

	if(rnd_bytes < sizeof(randomBuffer))
		return NULL;


	for(int c=0; c<tokenSize; c++) {
		unsigned int randomVal;

		randomVal = randomBuffer[c];

		if(c != 0 && c % 9 == 0) {
			token[c] = '-';
		} else if(randomVal % 2 == 0) {
			if(randomVal % 4 == 0) {
				token[c] = 'A' + randomVal % 26;
			} else {
				token[c] = 'a' + randomVal % 26;
			}
		} else {
			token[c] = '0' + randomVal % 10;
		}
	}

	return token;
}

/**
 * Create a new user
 * @param  usersPtr The address of the user list
 * @param  name     The name of the new user
 * @param  password The password of the new user
 * @return          The address of a new User structure
 */
User* newUser(User** usersPtr, char* name, char* password) {
	User* user=NULL;
	User* users=NULL;

	users = *usersPtr;

	if(!(user = malloc(sizeof(User)))) {
		return NULL;
	}

	if(!(user->name = malloc(strlen(name)+1))) {
		free(user);
		return NULL;
	}
	memset(user->name, 0, strlen(name)+1);
	strcpy(user->name, name);

	if(!(user->password = malloc(strlen(password)+1))) {
		free(user->name);
		free(user);
		return NULL;
	}
	memset(user->password, 0, strlen(password)+1);
	strcpy(user->password, password);

	user->token = NULL;
	user->signingKey = NULL;
	user->subscriptions = NULL;
	user->next = *usersPtr;
	*usersPtr = user;

	return user;
}

/**
 * Find a user with the matching token
 * @param  users The list of users
 * @param  token The token to match
 * @return       The address of the found User structure,
 *               NULL if not found.
 */
User* getUserByToken(User* users, char* token) {

	for(User* user=users; user!=NULL; user=user->next) {
		if(user->token && !strcmp(user->token, token)) {
			return user;
		}
	}

	return NULL;
}

/**
 * Find a user with the matching name
 * @param  users The list of users
 * @param  name  The name to match
 * @return       The address of the found User structure,
 *               NULL if not found.
 */
User* getUserByName(User* users, char* name) {

	for(User* user=users; user!=NULL; user=user->next) {
		if(!strcmp(user->name, name)) {
			return user;
		}
	}

	return NULL;
}

/**
 * Create a new token and assign it
 * @param  user The address of the User structure to assign the token to
 * @return      The address of the modified User structure
 */
User* newToken(User* user) {

	user->token = generateRandomToken(TOKEN_SIZE);

	return user;
}

/**
 * Generate a new signing key of the requested size
 * @param  keySize The size of the requested signing key
 * @return         The address of the signing key string
 */
unsigned char* generateSigningKey(size_t keySize) {
	unsigned char* signingKey;
	char* randomBuffer;
	size_t rnd_bytes;

	if(!(signingKey = malloc(keySize+1)))
		return NULL;

	memset(signingKey, 0, keySize+1);

	if(random((void*)signingKey, keySize, &rnd_bytes))
		return NULL;

	if(rnd_bytes < keySize)
		return NULL;

	return signingKey;
}

/**
 * Reverse the list of subscriptions
 * @param subscriptionsPtr The address of the list of subscriptions
 */
void reverseSubscriptionList(Subscription** subscriptionsPtr) {
	Subscription* prevSub=NULL, *nextSub=NULL;

	for(Subscription* subscription=*subscriptionsPtr; subscription!=NULL; subscription=nextSub) {
		nextSub = subscription->next;
		subscription->next = prevSub;
		prevSub = subscription;
	}

	*subscriptionsPtr = prevSub;
}

/**
 * Verify the signature of the response
 * @param  response   The response to verify
 * @param  signingKey The signing key used to verify the signature
 * @return            VALID_SIGNATURE if the signature is valid
 *                    INVALID_SIGNATURE otherwise.
 */
unsigned int verifySignature(AuthResponse* response, unsigned char* signingKey) {
	char* subscriptionString;
	unsigned int idx=0;

	reverseSubscriptionList(&response->subscriptions);

	for(Subscription* subscription=response->subscriptions; subscription!=NULL; subscription=subscription->next) {
		size_t stringSize;

		stringSize = strlen(subscription->name);
		for(int c=0; c<stringSize; c++) {
			unsigned char sigChar;

			sigChar = to_bin(response->signature[idx++]) * 16 + to_bin(response->signature[idx++]);

			if(subscription->name[c] != (signingKey[(idx-2)/2] ^ sigChar))
				return INVALID_SIGNATURE;
		}
	}

	return VALID_SIGNATURE;
}

/**
 * Compute the signature for a given subscription list
 * @param  user The User structure containing the subscription list to sign
 * @return      The address of the signature string
 */
char* computeSignature(User* user) {
	char *signature, *signatureString;
	size_t signatureSize=0, signatureStringSize=0;

	for(Subscription* subscription=user->subscriptions; subscription!=NULL; subscription=subscription->next) {
		signatureSize += strlen(subscription->name);
	}

	if(!(user->signingKey = generateSigningKey(signatureSize)))
		return NULL;

	if(!(signature = malloc(signatureSize+1)))
		return NULL;

	memset(signature, 0, signatureSize+1);

	for(Subscription* subscription=user->subscriptions; subscription!=NULL; subscription=subscription->next) {
		strcat(signature, subscription->name);
	}

	for(int idx=0; idx<signatureSize; idx++) {
		signature[idx] = signature[idx] ^ user->signingKey[idx];
	}

	signatureStringSize = signatureSize*2 + 1;
	if(!(signatureString = malloc(signatureStringSize+1)))
		return NULL;

	memset(signatureString, 0, signatureStringSize+1);

	for(unsigned int i=0; i < signatureSize*2; i++) {
		signatureString[i++] = to_hex((unsigned char) *signature / 16 % 16);
		signatureString[i] = to_hex((unsigned char) *signature++ % 16);
	}

	return signatureString;

}
