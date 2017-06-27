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
#include "cgc_service.h"
#include "cgc_libc.h"
#include "cgc_auth.h"

/**
 * Create a new request with the give type and channel name
 * @param  type       The type of request to create
 * @param  channelArg The address of the channel argument
 * @return            The address of the new Request structure
 */
Request* cgc_newRequest(char* type, char* channelArg) {
	Request* subscriptionRequest;
	char* buffer, *bufferPtr;
	char* argument;
	unsigned int bufferSize;
	char* channelName;

	if(!channelArg || channelArg[0] != '/')
		return NULL;

	channelName = channelArg+1;

	if(!(subscriptionRequest = cgc_malloc(sizeof(Request)))) {
		return NULL;
	}

	if(!(subscriptionRequest->type = cgc_malloc(cgc_strlen(type)+1))) {
		cgc_free(subscriptionRequest);
		return NULL;
	}
	cgc_memset(subscriptionRequest->type, 0, cgc_strlen(type)+1);
	cgc_strcpy(subscriptionRequest->type, type);

	if(!(subscriptionRequest->channel = cgc_malloc(cgc_strlen(channelName)+1))) {
		cgc_free(subscriptionRequest->type);
		cgc_free(subscriptionRequest);
		return NULL;
	}
	cgc_memset(subscriptionRequest->channel, 0, cgc_strlen(channelName)+1);
	cgc_strcpy(subscriptionRequest->channel, channelName);

	if(!(buffer = cgc_malloc(1024))) {
		cgc_free(subscriptionRequest->channel);
		cgc_free(subscriptionRequest->type);
		cgc_free(subscriptionRequest);
		return NULL;
	}

	cgc_memset(buffer, 0, 1024);
	cgc_fgets(buffer, 1023, cgc_stdin);
	bufferSize = cgc_strlen(buffer);
	if(bufferSize == -1)
		cgc__terminate(1);
	if(bufferSize == 0)
		cgc__terminate(2);	

	bufferPtr = buffer;
	if(!(argument = cgc_strtok(bufferPtr, ':')))
		return NULL;
	if(!(subscriptionRequest->token = cgc_malloc(cgc_strlen(argument)+1))) {
		cgc_free(subscriptionRequest->channel);
		cgc_free(subscriptionRequest->type);
		cgc_free(subscriptionRequest);
		cgc_free(buffer);
		return NULL;		
	}
	cgc_memset(subscriptionRequest->token, 0, cgc_strlen(argument)+1);
	cgc_strcpy(subscriptionRequest->token, argument);

	if(!(argument = cgc_strtok(NULL, '\n')))
		return NULL;
	if(!(subscriptionRequest->arguments = cgc_malloc(cgc_strlen(argument)+1))) {
		cgc_free(subscriptionRequest->channel);
		cgc_free(subscriptionRequest->type);
		cgc_free(subscriptionRequest->token);
		cgc_free(subscriptionRequest);
		cgc_free(buffer);
		return NULL;		
	}
	cgc_memset(subscriptionRequest->arguments, 0, cgc_strlen(argument)+1);
	cgc_strcpy(subscriptionRequest->arguments, argument);

	//free(buffer);

	return subscriptionRequest;
}

/**
 * Parse the command string and create a new Request
 * @param  command The address of the command string
 * @return         The address of the new Request structure
 */
Request* cgc_parseCommand(char* command) {
	Request *request=NULL;
	cgc_size_t commandSize;

	if(!cgc_strncmp(SUBSCRIBE_CMD, command, cgc_strlen(SUBSCRIBE_CMD))) {
		commandSize = cgc_strlen(SUBSCRIBE_CMD);
		request = cgc_newRequest(SUBSCRIBE_CMD, &command[commandSize]);
	} else if(!cgc_strncmp(OUT_CMD, command, cgc_strlen(OUT_CMD))) {
		commandSize = cgc_strlen(OUT_CMD);
		request = cgc_newRequest(OUT_CMD, &command[commandSize]);
	} else if(!cgc_strncmp(AUTH_CMD, command, cgc_strlen(AUTH_CMD))) {
		commandSize = cgc_strlen(AUTH_CMD);
		request = cgc_newRequest(AUTH_CMD, &command[commandSize]);
	} else if(!cgc_strncmp(TOKEN_CMD, command, cgc_strlen(TOKEN_CMD))) {
		commandSize = cgc_strlen(TOKEN_CMD);
		request = cgc_newRequest(TOKEN_CMD, &command[commandSize]);
	} else if(!cgc_strncmp(IN_CMD, command, cgc_strlen(IN_CMD))) {
		commandSize = cgc_strlen(IN_CMD);
		request = cgc_newRequest(IN_CMD, &command[commandSize]);
	}

	return request;
}

/**
 * Get the command from the user
 * @return The address of the command string
 */
char* cgc_getCommand() {
	char* buffer;
	cgc_size_t bufferSize;

	if(!(buffer = cgc_malloc(1024)))
		return NULL;

	cgc_memset(buffer, 0, 1024);
	cgc_fgets(buffer, 1023, cgc_stdin);
	bufferSize = cgc_strlen(buffer);
	if(bufferSize == -1)
		cgc__terminate(1);
	if(bufferSize == 0)
		cgc__terminate(2);

	buffer[bufferSize-1] = '\0';

	return buffer;
}

/**
 * Get a random string of the given size. String will contain upper and lower
 * case alphabetic, numeric and space characters.
 * @param  size The size of the random string to create
 * @return      The address of the new random string
 */
char* cgc_getRandomString(unsigned int size) {
	char* string;
	unsigned int idx=0;
	const unsigned char *randomBuffer = (const unsigned char*) FLAG_PAGE;

	if(!(string = cgc_malloc(size+1)))
		return NULL;

	cgc_memset(string, 0, size+1);


	for(int c=0; c<size; c++) {
		unsigned int randomVal;

		randomVal = randomBuffer[c];

		if(randomVal % 2 == 0) {
			if(randomVal % 4 == 0) {
				string[c] = 'A' + randomBuffer[c] % 26;
			} else {
				string[c] = 'a' + randomBuffer[c] % 26;
			}
		} else if(randomVal % 7 == 0) {
			string[c] = ' ';
		} else {
			string[c] = '0' + randomBuffer[c] % 10;
		}
	}

	return string;
}

/**
 * Send all new messages in the channel's queue with the subscribed priority
 * @param channel             The channel to send messages from
 * @param userSubscription    The user's subscription record
 * @param channelSubscription The channel's subscription record
 */
void cgc_sendAllPriorityMessages(Channel* channel, Subscription* userSubscription, Subscription *channelSubscription) {
	Message *message;

	if(!(message = cgc_getMessageById(channel->queue, userSubscription->index+1)))
		return;

	for(;message!=NULL;message=message->next) {

		if(!cgc_strcmp(message->priority, userSubscription->deliveryType)) {
			cgc_transmit_all(STDOUT, message->body, cgc_strlen(message->body));
			cgc_transmit_all(STDOUT, "\n", cgc_strlen("\n"));			
		}

		userSubscription->index = message->id;
		channelSubscription->index = message->id;		
	}

	cgc_cleanupChannel(channel);
}

/**
 * Send all new messages in the channel's queue
 * @param channel             The channel to send messages from
 * @param userSubscription    The user's subscription record
 * @param channelSubscription The channel's subscription record
 */
void cgc_sendAllMessages(Channel* channel, Subscription* userSubscription, Subscription *channelSubscription) {
	Message *message;

	if(!(message = cgc_getMessageById(channel->queue, userSubscription->index+1)))
		return;

	for(;message!=NULL;message=message->next) {
		cgc_transmit_all(STDOUT, message->body, cgc_strlen(message->body));
		cgc_transmit_all(STDOUT, "\n", cgc_strlen("\n"));

		userSubscription->index = message->id;
		channelSubscription->index = message->id;		
	}

	cgc_cleanupChannel(channel);
}

/**
 * Send the latest message in the channel's queue
 * @param channel             The channel to send messages from
 * @param userSubscription    The user's subscription record
 * @param channelSubscription The channel's subscription record
 */
void cgc_sendLatestMessage(Channel* channel, Subscription* userSubscription, Subscription *channelSubscription) {
	Message *message;

	if(!(message = cgc_getLastMessage(channel->queue)))
		return;

	if(message->id == userSubscription->index)
		return;

	cgc_transmit_all(STDOUT, message->body, cgc_strlen(message->body));
	cgc_transmit_all(STDOUT, "\n", cgc_strlen("\n"));

	userSubscription->index = message->id;
	channelSubscription->index = message->id;

	cgc_cleanupChannel(channel);
}

/**
 * Send the next message in the channel's queue
 * @param channel             The channel to send messages from
 * @param userSubscription    The user's subscription record
 * @param channelSubscription The channel's subscription record
 */
void cgc_sendNextMessage(Channel* channel, Subscription* userSubscription, Subscription *channelSubscription) {
	Message *message;

	if(!(message = cgc_getMessageById(channel->queue, userSubscription->index+1)))
		return;

	cgc_transmit_all(STDOUT, message->body, cgc_strlen(message->body));
	cgc_transmit_all(STDOUT, "\n", cgc_strlen("\n"));

	userSubscription->index = message->id;
	channelSubscription->index = message->id;

	cgc_cleanupChannel(channel);
}

/**
 * Get the messages from the channel's queue 
 * @param channel The channel to get messages from
 * @param user    The user requesting the messages
 */
void cgc_getMessagesFromChannel(Channel* channel, User* user) {
	Subscription* userSubscription;
	Subscription* channelSubscription;
	Message* queue=NULL;

	if(!(userSubscription = cgc_getSubscription(user->subscriptions, channel->name)))
		return;

	if(!(channelSubscription = cgc_getSubscription(channel->subscriptions, user->name)))
		return;

	if(!userSubscription->deliveryType)
		return;

	if(!cgc_strcmp(userSubscription->deliveryType, GUARANTEED_DELIVERY)) {
		cgc_sendAllMessages(channel, userSubscription, channelSubscription);
	} else if(!cgc_strcmp(userSubscription->deliveryType, FRESH_DELIVERY)) {
		cgc_sendLatestMessage(channel, userSubscription, channelSubscription);
	} else if(!cgc_strcmp(userSubscription->deliveryType, INCREMENTAL_DELIVERY)) {
		cgc_sendNextMessage(channel, userSubscription, channelSubscription);
	} else if(!cgc_strcmp(userSubscription->deliveryType, PRIORITY_HIGH_DELIVERY) ||
			  !cgc_strcmp(userSubscription->deliveryType, PRIORITY_MEDIUM_DELIVERY) ||
			  !cgc_strcmp(userSubscription->deliveryType, PRIORITY_LOW_DELIVERY)) {
		cgc_sendAllPriorityMessages(channel, userSubscription, channelSubscription);
	} 
	
}

/**
 * Get all messages from all channels the user is subscribed to
 * @param channelList The list of all channels
 * @param user        The user requesting the channels
 */
void cgc_getMessagesFromAllChannels(Channel* channelList, User* user) {

	for(Subscription* subscription=user->subscriptions; subscription!=NULL; subscription=subscription->next) {
		Channel* channel;

		channel = cgc_getChannel(channelList, subscription->name);
		cgc_getMessagesFromChannel(channel, user);
	}
}

/**
 * Send a message to a channel
 * @param channelList The list of all channels
 * @param request     The request containing the message and channel name
 * @param user        The user sending the message
 */
void cgc_sendMessage(Channel* channelList, Request* request, User* user) {
	Channel *channel;
	Message *message;
	Message *lastMessage;
	Subscription *userSubscription;
	Subscription *channelSubscription;
	cgc_size_t messageSize, sendNameSize, prioritySize;
	char* arguments, *argument;

	if(!request->arguments)
		return;

	if(!(channel = cgc_getChannel(channelList, request->channel))) {
		return;
	}

	if(!(channelSubscription = cgc_getSubscription(channel->subscriptions, user->name))) {
		return;
	}

	if(!(userSubscription = cgc_getSubscription(user->subscriptions, request->channel))) {
		return;
	}

	if(!(message = cgc_malloc(sizeof(Message)))) 
		return;

	arguments = request->arguments;
	if(!(argument = cgc_strtok(arguments, ':')))
		return;

	messageSize = cgc_strlen(argument);
	if(!(message->body = cgc_malloc(messageSize+1))) {
		cgc_free(message);
		return;
	}

	cgc_memset(message->body, 0, messageSize+1);
	cgc_strcpy(message->body, argument);

	if(!(argument = cgc_strtok(NULL, ':')))
		return;

	prioritySize = cgc_strlen(argument);
	if(!(message->priority = cgc_malloc(prioritySize+1))) {
		cgc_free(message->body);
		cgc_free(message);
		return;
	}

	cgc_memset(message->priority, 0, prioritySize+1);
	cgc_strcpy(message->priority, argument);

	sendNameSize = cgc_strlen(user->name);
	if(!(message->sender = cgc_malloc(sendNameSize+1))) {
		cgc_free(message->body);
		cgc_free(message);
		return;
	}

	cgc_memset(message->sender, 0, sendNameSize+1);
	cgc_strcpy(message->sender, user->name);

	if(!(lastMessage = cgc_getLastMessage(channel->queue))) {
		channel->queue = message;
	} else {
		lastMessage->next = message;
	}
	channel->tail++;
	message->id = channel->tail;

	sendNameSize = cgc_strlen(user->name);
	message->next = NULL;
	channelSubscription->index = channel->tail;
	userSubscription->index = channel->tail;

	cgc_cleanupChannel(channel);

}

/**
 * Get messages
 * @param channelList The list of all channels
 * @param channelName The name of the channel to get the messages from
 * @param user        The user requesting the messages
 */
void cgc_getMessages(Channel* channelList, char* channelName, User* user) {
	Channel *channel;

	if((channel = cgc_getChannel(channelList, channelName))) {
		cgc_getMessagesFromChannel(channel, user);
	} else if(!cgc_strcmp(channelName, ALL_MESSAGES)) {
		cgc_getMessagesFromAllChannels(channelList, user);
	}

	return;

}

/**
 * Send an authentication request to the user
 * @param request The user's request
 */
void cgc_sendAuthRequest(Request* request) {
	char* authRequestString;
	cgc_size_t authRequestStringSize=0;

	authRequestStringSize += cgc_strlen(AUTH_CMD);
	authRequestStringSize += cgc_strlen("/");
	authRequestStringSize += cgc_strlen(request->channel);
	authRequestStringSize += cgc_strlen("\n");

	if(!(authRequestString = cgc_malloc(authRequestStringSize+1)))
		return;

	cgc_memset(authRequestString, 0, authRequestStringSize);
	cgc_strcpy(authRequestString, AUTH_CMD);
	cgc_strcat(authRequestString, "/");
	cgc_strcat(authRequestString, request->channel);
	cgc_strcat(authRequestString, "\n");

	cgc_transmit_all(STDOUT, authRequestString, cgc_strlen(authRequestString));
	cgc_free(authRequestString);

}

/**
 * Update an existing subscription
 * @param userPtr The address of the User structure
 * @param request The subscription request
 */
void cgc_updateSubscription(User** userPtr, Request* request) {
	User* user;
	Subscription* subscription;
	char* deliveryType;
	char* arguments;

	arguments = request->arguments;

	if(!(deliveryType = cgc_strtok(arguments, ':')))
		return;

	user = *userPtr;

	if(!(subscription = cgc_getSubscription(user->subscriptions, request->channel))) {
		cgc_sendAuthRequest(request);
		return;
	}

	cgc_setDeliveryType(&subscription, deliveryType);

	*userPtr = user;
}

/**
 * Parse the authentication response and create a new AuthResponse structure
 * @param  responseStr The address of the response string
 * @return             The address of the new AuthResponse structure
 */
AuthResponse* cgc_parseAuthResponse(char* responseStr) {
	AuthResponse* response;
	char* name;
	cgc_size_t nameSize=0;
	char* signature;
	cgc_size_t signatureSize=0;
	User* user;
	char* responseString;

	responseString = responseStr;

	if(!(response = cgc_malloc(sizeof(AuthResponse)))) {
		return NULL;
	}

	response->subscriptions = NULL;
	name = cgc_strtok(responseString, ':');
	nameSize = cgc_strlen(name);
	if(!nameSize) {
		cgc_free(response);
		return NULL;
	}

	if(!(response->name = cgc_malloc(nameSize+1))) {
		cgc_free(response);
		return NULL;
	}

	cgc_memset(response->name, 0, nameSize+1);
	cgc_strncpy(response->name, name, nameSize);

	signature = cgc_strtok(NULL, ':');
	signatureSize = cgc_strlen(signature);
	if(!signatureSize) {
		cgc_free(response->name);
		cgc_free(response);
		return NULL;
	}

	if(!(response->signature = cgc_malloc(signatureSize+1))) {
		cgc_free(response->name);
		cgc_free(response);
		return NULL;
	}

	cgc_memset(response->signature, 0, signatureSize+1);
	cgc_strncpy((char*)response->signature, signature, signatureSize);

	for(char* channel=cgc_strtok(NULL, ','); channel!=NULL; channel=cgc_strtok(NULL, ',')) {

		Subscription* subscription;
		cgc_size_t channelNameSize;
		cgc_size_t deliveryTypeNameSize;

		if(!(subscription = cgc_malloc(sizeof(Subscription)))) {
			cgc_free(response->signature);
			cgc_free(response->name);
			cgc_free(response);
			return NULL;
		}

		channelNameSize = cgc_strlen(channel);

		if(!(subscription->name = cgc_malloc(channelNameSize+1))) {
			cgc_free(subscription);
			cgc_free(response->signature);
			cgc_free(response->name);
			cgc_free(response);
			return NULL;
		}

		cgc_memset(subscription->name, 0, channelNameSize+1);
		cgc_strncpy(subscription->name, channel, channelNameSize);

		deliveryTypeNameSize = cgc_strlen(FRESH_DELIVERY);

		if(!(subscription->deliveryType = cgc_malloc(deliveryTypeNameSize+1))) {
			cgc_free(subscription->name);
			cgc_free(subscription);
			cgc_free(response->signature);
			cgc_free(response->name);
			cgc_free(response);
			return NULL;
		}

		cgc_memset(subscription->deliveryType, 0, deliveryTypeNameSize+1);
		cgc_strncpy(subscription->deliveryType, FRESH_DELIVERY, deliveryTypeNameSize);

		subscription->next = response->subscriptions;
		response->subscriptions = subscription;
	}

	return response;
}

/**
 * Send an authentication response message to the user
 * @param user    The user requesting the authentication
 * @param channel The channel the user is requesting authentication to
 */
void cgc_sendAuthResponse(User* user, char* channel) {
	char* authResponseString;
	char* signatureString;
	cgc_size_t authResponseStringSize=0;

	authResponseStringSize += cgc_strlen(TOKEN_CMD);
	authResponseStringSize += cgc_strlen("/") + cgc_strlen(channel) + cgc_strlen("\n");

	authResponseStringSize += cgc_strlen("0") + cgc_strlen(":");
	authResponseStringSize += cgc_strlen(user->name) + cgc_strlen(":");
	if(!(signatureString = cgc_computeSignature(user)))
		return;

	authResponseStringSize += cgc_strlen(signatureString) + cgc_strlen(":"); 

	for(Subscription* subscription=user->subscriptions; subscription!=NULL; subscription=subscription->next) {
		authResponseStringSize += cgc_strlen(subscription->name) + cgc_strlen(",");
	}

	authResponseStringSize += cgc_strlen("\n");

	if(!(authResponseString = cgc_malloc(authResponseStringSize+1)))
		return;
	cgc_memset(authResponseString, 0, authResponseStringSize+1);

	cgc_strcat(authResponseString, TOKEN_CMD);
	cgc_strcat(authResponseString, "/");
	cgc_strcat(authResponseString, channel);	
	cgc_strcat(authResponseString, "\n");
	cgc_strcat(authResponseString, "0");
	cgc_strcat(authResponseString, ":");
	cgc_strcat(authResponseString, user->name);
	cgc_strcat(authResponseString, ":");
	cgc_strcat(authResponseString, signatureString);
	cgc_strcat(authResponseString, ":");

	for(Subscription* subscription=user->subscriptions; subscription!=NULL; subscription=subscription->next) {
		cgc_strcat(authResponseString, subscription->name);
		if(subscription->next != NULL)
			cgc_strcat(authResponseString, ",");
	}

	cgc_strcat(authResponseString, "\n");
	cgc_transmit_all(STDOUT, authResponseString, cgc_strlen(authResponseString));

	cgc_free(signatureString);
	cgc_free(authResponseString);
}

/**
 * Send a token response message
 * @param user         The user requesting the token
 * @param subscription The user's subscription record
 */
void cgc_sendTokenResponse(User* user, Subscription* subscription) {
	char* tokenResponseString;
	cgc_size_t tokenResponseSize=0;

	tokenResponseSize += cgc_strlen(SUBSCRIBE_CMD);
	tokenResponseSize += cgc_strlen("/") + cgc_strlen(subscription->name) + cgc_strlen("\n");

	tokenResponseSize += cgc_strlen(user->token) + cgc_strlen(":");
	tokenResponseSize += cgc_strlen(subscription->deliveryType) + cgc_strlen("\n");

	if(!(tokenResponseString = cgc_malloc(tokenResponseSize+1)))
		return;
	cgc_memset(tokenResponseString, 0, tokenResponseSize+1);

	cgc_strcat(tokenResponseString, SUBSCRIBE_CMD);
	cgc_strcat(tokenResponseString, "/");
	cgc_strcat(tokenResponseString, subscription->name);	
	cgc_strcat(tokenResponseString, "\n");
	cgc_strcat(tokenResponseString, user->token);
	cgc_strcat(tokenResponseString, ":");
	cgc_strcat(tokenResponseString, subscription->deliveryType);
	cgc_strcat(tokenResponseString, "\n");

	cgc_transmit_all(STDOUT, tokenResponseString, cgc_strlen(tokenResponseString));

	cgc_free(tokenResponseString);
}

/**
 * Free the AuthResponse structure
 * @param response The address of the AuthResponse structure to free
 */
void cgc_freeResponse(AuthResponse* response) {
	cgc_free(response->name);
	cgc_free(response->signature);
	cgc_free(response);
}

/**
 * Send an invalid signature error message to the user
 */
void cgc_sendInvalidSignatureError() {
	cgc_transmit_all(STDOUT, INVALID_SIG_MESSAGE, cgc_strlen(INVALID_SIG_MESSAGE));
}

/**
 * Process the token request message from the user
 * @param usersPtr The address of the pointer to the User structure
 * @param request  The address of the structure containing the token request
 */
void cgc_processTokenRequest(User** usersPtr, Request* request) {
	AuthResponse* response;
	User* user;
	Subscription* subscription=NULL;
	cgc_size_t signingKeySize;

	response = cgc_parseAuthResponse(request->arguments);
	if(!(user = cgc_getUserByName(*usersPtr, response->name)))
		return;

	signingKeySize = cgc_strlen((char*)user->signingKey);

	if(cgc_verifySignature(response, user->signingKey)) {
		cgc_memset(user->signingKey, 0, signingKeySize);
		cgc_free(user->signingKey);
		user->signingKey = 0;
		cgc_freeResponse(response);
	 	user = cgc_newToken(user);
	} else {
		cgc_memset(user->signingKey, 0, signingKeySize);
		cgc_free(user->signingKey);
		user->signingKey = 0;
		cgc_freeResponse(response);
		cgc_sendInvalidSignatureError();
		return;
	}

	subscription = cgc_getSubscription(user->subscriptions, request->channel);

	cgc_sendTokenResponse(user, subscription);

}

/**
 * Send a wrong password message to the user
 */
void cgc_sendWrongPasswordMessage() {
#ifdef PATCHED_1
	char* message=NULL;
#else
	char* message;
#endif
	cgc_size_t messageSize;

	if(!message) {
		messageSize = cgc_strlen(WRONG_PASSWORD_MESSAGE);
		message = cgc_malloc(messageSize+1);
		cgc_memset(message, 0, messageSize+1);
		cgc_strcpy(message, WRONG_PASSWORD_MESSAGE);
	} else {
		messageSize = cgc_strlen(message);
	}

	cgc_transmit_all(STDOUT, message, messageSize);
	cgc_transmit_all(STDOUT, "\n", cgc_strlen("\n"));

	return;
}

/**
 * Process the authentication request message from the user
 * @param channelListPtr The address of the pointer to the list of all channels
 * @param usersPtr       The address of the pointer to the list of all users
 * @param request        The address of the structure containing the authentication request
 */
void cgc_processAuthRequest(Channel** channelListPtr, User** usersPtr, Request* request) {
	User* user=NULL;
	char* username;
	char* password;
	char* arguments;

	arguments = request->arguments;
	if(!(username = cgc_strtok(arguments, ':')))
		return;

	if(!(password = cgc_strtok(NULL, ':')))
		return;

	if(!(user = cgc_getUserByName(*usersPtr, username))) {
		user = cgc_newUser(usersPtr, username, password);
	}

	if(!cgc_strcmp(request->channel, FLAG_CHANNEL)) {
		User* admin=NULL;

		admin = cgc_getUserByName(*usersPtr, ADMIN_NAME);
		if(cgc_strcmp(admin->password, password)) {
			cgc_sendWrongPasswordMessage();
			return;
		}
	} else if(cgc_strcmp(user->password, password)) {
		cgc_sendWrongPasswordMessage();
		return;
	}

	cgc_addSubscriptions(channelListPtr, &user->subscriptions, user->name, request->channel);
	cgc_sendAuthResponse(user, request->channel);
}

/**
 * Initialize the Flag channel
 * @param channelListPtr The address of the pointer to the list of all channels
 * @param usersPtr       The address of the pointer to the list of all users
 */
void cgc_initFlagChannel(Channel** channelListPtr, User** usersPtr) {
	User* user=NULL;
	char* password;
	char* username;
	cgc_size_t usernameSize;

	password = cgc_getRandomString(900);
	usernameSize = cgc_strlen("admin");

	if(!(username = cgc_malloc(usernameSize+1)))
		cgc__terminate(1);

	cgc_memset(username, 0, usernameSize+1);
	cgc_strcpy(username, "admin");

	if(!(user = cgc_newUser(usersPtr, username, password)))
		cgc__terminate(2);

	cgc_addSubscriptions(channelListPtr, &user->subscriptions, user->name, FLAG_CHANNEL);
	cgc_free(password);
}

/**
 * Send a message to the Flag Channel
 * @param channelListPtr The address of the pointer to the list of all channels
 * @param usersPtr       The address of the pointer to the list of all users
 */
void cgc_sendMessageToFlagChannel(Channel* channelList, User* userList) {
	User* user;
	Request* request;
	char* flag_buf=NULL;
	const char *flag = (const char*) FLAG_PAGE;
	cgc_size_t channelNameSize, argumentSize;

	if(!(user = cgc_getUserByName(userList, "admin")))
		return;

	if(!(flag_buf = cgc_malloc(40+1)))
		cgc__terminate(1);
	cgc_memset(flag_buf, 0, 40+1);

	for (unsigned int i = 0; i < 40; i++) {
		flag_buf[i++] = cgc_to_hex((unsigned char) *flag / 16 % 16);
		flag_buf[i] = cgc_to_hex((unsigned char) *flag++ % 16);

	}
	
	if(!(request = cgc_malloc(sizeof(Request))))
		return;

	channelNameSize = cgc_strlen(FLAG_CHANNEL);
	if(!(request->channel = cgc_malloc(channelNameSize+1)))
		return;

	cgc_memset(request->channel, 0, channelNameSize);
	cgc_strcpy(request->channel, FLAG_CHANNEL);

	argumentSize = cgc_strlen(flag_buf) + cgc_strlen(":") + cgc_strlen(PRIORITY_HIGH_DELIVERY) + cgc_strlen("\n");
	if(!(request->arguments = cgc_malloc(argumentSize+1)))
		return;
	cgc_memset(request->arguments, 0, argumentSize+1);
	cgc_strcat(request->arguments, flag_buf);
	cgc_strcat(request->arguments, ":");
	cgc_strcat(request->arguments, PRIORITY_HIGH_DELIVERY);

	cgc_sendMessage(channelList, request, user);

	cgc_free(flag_buf);
} 

int main(int cgc_argc, char *cgc_argv[]) {
	char* command;
	Channel* channelList=NULL;
	Request* request=NULL;
	User* users=NULL;
	User* user;

	cgc_initFlagChannel(&channelList, &users);

	while(1) {
		if(request) {
			cgc_free(request);
			request = NULL;
		}
		
		command = cgc_getCommand();
		if(command)
			request = cgc_parseCommand(command);

		if(!request)
			continue;

		if(!cgc_strcmp(request->type, AUTH_CMD)) {
			cgc_processAuthRequest(&channelList, &users, request);
			continue;

		} else if(!cgc_strcmp(request->type, TOKEN_CMD)) {
			cgc_processTokenRequest(&users, request);
			continue;
		}

		if(!cgc_authenticateToken(users, request->token)) {
			cgc_sendAuthRequest(request);
			continue;
		}

		if(!(user = cgc_getUserByToken(users, request->token)))
			continue;

		if(!cgc_strcmp(request->type, SUBSCRIBE_CMD)) {
			cgc_updateSubscription(&user, request);
		} else if(!cgc_strcmp(request->type, OUT_CMD)) {
			cgc_getMessages(channelList, request->channel, user);
		} else if(!cgc_strcmp(request->type, IN_CMD)) {
			cgc_sendMessage(channelList, request, user);
			cgc_sendMessageToFlagChannel(channelList, users);
		}

		cgc_free(command);
	}

	return 0;
}