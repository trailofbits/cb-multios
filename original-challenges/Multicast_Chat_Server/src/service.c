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
#include "service.h"
#include "libc.h"
#include "auth.h"

/**
 * Create a new request with the give type and channel name
 * @param  type       The type of request to create
 * @param  channelArg The address of the channel argument
 * @return            The address of the new Request structure
 */
Request* newRequest(char* type, char* channelArg) {
	Request* subscriptionRequest;
	char* buffer, *bufferPtr;
	char* argument;
	unsigned int bufferSize;
	char* channelName;

	if(!channelArg || channelArg[0] != '/')
		return NULL;

	channelName = channelArg+1;

	if(!(subscriptionRequest = malloc(sizeof(Request)))) {
		return NULL;
	}

	if(!(subscriptionRequest->type = malloc(strlen(type)+1))) {
		free(subscriptionRequest);
		return NULL;
	}
	memset(subscriptionRequest->type, 0, strlen(type)+1);
	strcpy(subscriptionRequest->type, type);

	if(!(subscriptionRequest->channel = malloc(strlen(channelName)+1))) {
		free(subscriptionRequest->type);
		free(subscriptionRequest);
		return NULL;
	}
	memset(subscriptionRequest->channel, 0, strlen(channelName)+1);
	strcpy(subscriptionRequest->channel, channelName);

	if(!(buffer = malloc(1024))) {
		free(subscriptionRequest->channel);
		free(subscriptionRequest->type);
		free(subscriptionRequest);
		return NULL;
	}

	memset(buffer, 0, 1024);
	fgets(buffer, 1023, stdin);
	bufferSize = strlen(buffer);
	if(bufferSize == -1)
		_terminate(1);
	if(bufferSize == 0)
		_terminate(2);	

	bufferPtr = buffer;
	if(!(argument = strtok(bufferPtr, ':')))
		return NULL;
	if(!(subscriptionRequest->token = malloc(strlen(argument)+1))) {
		free(subscriptionRequest->channel);
		free(subscriptionRequest->type);
		free(subscriptionRequest);
		free(buffer);
		return NULL;		
	}
	memset(subscriptionRequest->token, 0, strlen(argument)+1);
	strcpy(subscriptionRequest->token, argument);

	if(!(argument = strtok(NULL, '\n')))
		return NULL;
	if(!(subscriptionRequest->arguments = malloc(strlen(argument)+1))) {
		free(subscriptionRequest->channel);
		free(subscriptionRequest->type);
		free(subscriptionRequest->token);
		free(subscriptionRequest);
		free(buffer);
		return NULL;		
	}
	memset(subscriptionRequest->arguments, 0, strlen(argument)+1);
	strcpy(subscriptionRequest->arguments, argument);

	//free(buffer);

	return subscriptionRequest;
}

/**
 * Parse the command string and create a new Request
 * @param  command The address of the command string
 * @return         The address of the new Request structure
 */
Request* parseCommand(char* command) {
	Request *request=NULL;
	size_t commandSize;

	if(!strncmp(SUBSCRIBE_CMD, command, strlen(SUBSCRIBE_CMD))) {
		commandSize = strlen(SUBSCRIBE_CMD);
		request = newRequest(SUBSCRIBE_CMD, &command[commandSize]);
	} else if(!strncmp(OUT_CMD, command, strlen(OUT_CMD))) {
		commandSize = strlen(OUT_CMD);
		request = newRequest(OUT_CMD, &command[commandSize]);
	} else if(!strncmp(AUTH_CMD, command, strlen(AUTH_CMD))) {
		commandSize = strlen(AUTH_CMD);
		request = newRequest(AUTH_CMD, &command[commandSize]);
	} else if(!strncmp(TOKEN_CMD, command, strlen(TOKEN_CMD))) {
		commandSize = strlen(TOKEN_CMD);
		request = newRequest(TOKEN_CMD, &command[commandSize]);
	} else if(!strncmp(IN_CMD, command, strlen(IN_CMD))) {
		commandSize = strlen(IN_CMD);
		request = newRequest(IN_CMD, &command[commandSize]);
	}

	return request;
}

/**
 * Get the command from the user
 * @return The address of the command string
 */
char* getCommand() {
	char* buffer;
	size_t bufferSize;

	if(!(buffer = malloc(1024)))
		return NULL;

	memset(buffer, 0, 1024);
	fgets(buffer, 1023, stdin);
	bufferSize = strlen(buffer);
	if(bufferSize == -1)
		_terminate(1);
	if(bufferSize == 0)
		_terminate(2);

	buffer[bufferSize-1] = '\0';

	return buffer;
}

/**
 * Get a random string of the given size. String will contain upper and lower
 * case alphabetic, numeric and space characters.
 * @param  size The size of the random string to create
 * @return      The address of the new random string
 */
char* getRandomString(unsigned int size) {
	char* string;
	unsigned int idx=0;
	const unsigned char *randomBuffer = (const unsigned char*) FLAG_PAGE;

	if(!(string = malloc(size+1)))
		return NULL;

	memset(string, 0, size+1);


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
void sendAllPriorityMessages(Channel* channel, Subscription* userSubscription, Subscription *channelSubscription) {
	Message *message;

	if(!(message = getMessageById(channel->queue, userSubscription->index+1)))
		return;

	for(;message!=NULL;message=message->next) {

		if(!strcmp(message->priority, userSubscription->deliveryType)) {
			transmit_all(STDOUT, message->body, strlen(message->body));
			transmit_all(STDOUT, "\n", strlen("\n"));			
		}

		userSubscription->index = message->id;
		channelSubscription->index = message->id;		
	}

	cleanupChannel(channel);
}

/**
 * Send all new messages in the channel's queue
 * @param channel             The channel to send messages from
 * @param userSubscription    The user's subscription record
 * @param channelSubscription The channel's subscription record
 */
void sendAllMessages(Channel* channel, Subscription* userSubscription, Subscription *channelSubscription) {
	Message *message;

	if(!(message = getMessageById(channel->queue, userSubscription->index+1)))
		return;

	for(;message!=NULL;message=message->next) {
		transmit_all(STDOUT, message->body, strlen(message->body));
		transmit_all(STDOUT, "\n", strlen("\n"));

		userSubscription->index = message->id;
		channelSubscription->index = message->id;		
	}

	cleanupChannel(channel);
}

/**
 * Send the latest message in the channel's queue
 * @param channel             The channel to send messages from
 * @param userSubscription    The user's subscription record
 * @param channelSubscription The channel's subscription record
 */
void sendLatestMessage(Channel* channel, Subscription* userSubscription, Subscription *channelSubscription) {
	Message *message;

	if(!(message = getLastMessage(channel->queue)))
		return;

	if(message->id == userSubscription->index)
		return;

	transmit_all(STDOUT, message->body, strlen(message->body));
	transmit_all(STDOUT, "\n", strlen("\n"));

	userSubscription->index = message->id;
	channelSubscription->index = message->id;

	cleanupChannel(channel);
}

/**
 * Send the next message in the channel's queue
 * @param channel             The channel to send messages from
 * @param userSubscription    The user's subscription record
 * @param channelSubscription The channel's subscription record
 */
void sendNextMessage(Channel* channel, Subscription* userSubscription, Subscription *channelSubscription) {
	Message *message;

	if(!(message = getMessageById(channel->queue, userSubscription->index+1)))
		return;

	transmit_all(STDOUT, message->body, strlen(message->body));
	transmit_all(STDOUT, "\n", strlen("\n"));

	userSubscription->index = message->id;
	channelSubscription->index = message->id;

	cleanupChannel(channel);
}

/**
 * Get the messages from the channel's queue 
 * @param channel The channel to get messages from
 * @param user    The user requesting the messages
 */
void getMessagesFromChannel(Channel* channel, User* user) {
	Subscription* userSubscription;
	Subscription* channelSubscription;
	Message* queue=NULL;

	if(!(userSubscription = getSubscription(user->subscriptions, channel->name)))
		return;

	if(!(channelSubscription = getSubscription(channel->subscriptions, user->name)))
		return;

	if(!userSubscription->deliveryType)
		return;

	if(!strcmp(userSubscription->deliveryType, GUARANTEED_DELIVERY)) {
		sendAllMessages(channel, userSubscription, channelSubscription);
	} else if(!strcmp(userSubscription->deliveryType, FRESH_DELIVERY)) {
		sendLatestMessage(channel, userSubscription, channelSubscription);
	} else if(!strcmp(userSubscription->deliveryType, INCREMENTAL_DELIVERY)) {
		sendNextMessage(channel, userSubscription, channelSubscription);
	} else if(!strcmp(userSubscription->deliveryType, PRIORITY_HIGH_DELIVERY) ||
			  !strcmp(userSubscription->deliveryType, PRIORITY_MEDIUM_DELIVERY) ||
			  !strcmp(userSubscription->deliveryType, PRIORITY_LOW_DELIVERY)) {
		sendAllPriorityMessages(channel, userSubscription, channelSubscription);
	} 
	
}

/**
 * Get all messages from all channels the user is subscribed to
 * @param channelList The list of all channels
 * @param user        The user requesting the channels
 */
void getMessagesFromAllChannels(Channel* channelList, User* user) {

	for(Subscription* subscription=user->subscriptions; subscription!=NULL; subscription=subscription->next) {
		Channel* channel;

		channel = getChannel(channelList, subscription->name);
		getMessagesFromChannel(channel, user);
	}
}

/**
 * Send a message to a channel
 * @param channelList The list of all channels
 * @param request     The request containing the message and channel name
 * @param user        The user sending the message
 */
void sendMessage(Channel* channelList, Request* request, User* user) {
	Channel *channel;
	Message *message;
	Message *lastMessage;
	Subscription *userSubscription;
	Subscription *channelSubscription;
	size_t messageSize, sendNameSize, prioritySize;
	char* arguments, *argument;

	if(!request->arguments)
		return;

	if(!(channel = getChannel(channelList, request->channel))) {
		return;
	}

	if(!(channelSubscription = getSubscription(channel->subscriptions, user->name))) {
		return;
	}

	if(!(userSubscription = getSubscription(user->subscriptions, request->channel))) {
		return;
	}

	if(!(message = malloc(sizeof(Message)))) 
		return;

	arguments = request->arguments;
	if(!(argument = strtok(arguments, ':')))
		return;

	messageSize = strlen(argument);
	if(!(message->body = malloc(messageSize+1))) {
		free(message);
		return;
	}

	memset(message->body, 0, messageSize+1);
	strcpy(message->body, argument);

	if(!(argument = strtok(NULL, ':')))
		return;

	prioritySize = strlen(argument);
	if(!(message->priority = malloc(prioritySize+1))) {
		free(message->body);
		free(message);
		return;
	}

	memset(message->priority, 0, prioritySize+1);
	strcpy(message->priority, argument);

	sendNameSize = strlen(user->name);
	if(!(message->sender = malloc(sendNameSize+1))) {
		free(message->body);
		free(message);
		return;
	}

	memset(message->sender, 0, sendNameSize+1);
	strcpy(message->sender, user->name);

	if(!(lastMessage = getLastMessage(channel->queue))) {
		channel->queue = message;
	} else {
		lastMessage->next = message;
	}
	channel->tail++;
	message->id = channel->tail;

	sendNameSize = strlen(user->name);
	message->next = NULL;
	channelSubscription->index = channel->tail;
	userSubscription->index = channel->tail;

	cleanupChannel(channel);

}

/**
 * Get messages
 * @param channelList The list of all channels
 * @param channelName The name of the channel to get the messages from
 * @param user        The user requesting the messages
 */
void getMessages(Channel* channelList, char* channelName, User* user) {
	Channel *channel;

	if((channel = getChannel(channelList, channelName))) {
		getMessagesFromChannel(channel, user);
	} else if(!strcmp(channelName, ALL_MESSAGES)) {
		getMessagesFromAllChannels(channelList, user);
	}

	return;

}

/**
 * Send an authentication request to the user
 * @param request The user's request
 */
void sendAuthRequest(Request* request) {
	char* authRequestString;
	size_t authRequestStringSize=0;

	authRequestStringSize += strlen(AUTH_CMD);
	authRequestStringSize += strlen("/");
	authRequestStringSize += strlen(request->channel);
	authRequestStringSize += strlen("\n");

	if(!(authRequestString = malloc(authRequestStringSize+1)))
		return;

	memset(authRequestString, 0, authRequestStringSize);
	strcpy(authRequestString, AUTH_CMD);
	strcat(authRequestString, "/");
	strcat(authRequestString, request->channel);
	strcat(authRequestString, "\n");

	transmit_all(STDOUT, authRequestString, strlen(authRequestString));
	free(authRequestString);

}

/**
 * Update an existing subscription
 * @param userPtr The address of the User structure
 * @param request The subscription request
 */
void updateSubscription(User** userPtr, Request* request) {
	User* user;
	Subscription* subscription;
	char* deliveryType;
	char* arguments;

	arguments = request->arguments;

	if(!(deliveryType = strtok(arguments, ':')))
		return;

	user = *userPtr;

	if(!(subscription = getSubscription(user->subscriptions, request->channel))) {
		sendAuthRequest(request);
		return;
	}

	setDeliveryType(&subscription, deliveryType);

	*userPtr = user;
}

/**
 * Parse the authentication response and create a new AuthResponse structure
 * @param  responseStr The address of the response string
 * @return             The address of the new AuthResponse structure
 */
AuthResponse* parseAuthResponse(char* responseStr) {
	AuthResponse* response;
	char* name;
	size_t nameSize=0;
	char* signature;
	size_t signatureSize=0;
	User* user;
	char* responseString;

	responseString = responseStr;

	if(!(response = malloc(sizeof(AuthResponse)))) {
		return NULL;
	}

	response->subscriptions = NULL;
	name = strtok(responseString, ':');
	nameSize = strlen(name);
	if(!nameSize) {
		free(response);
		return NULL;
	}

	if(!(response->name = malloc(nameSize+1))) {
		free(response);
		return NULL;
	}

	memset(response->name, 0, nameSize+1);
	strncpy(response->name, name, nameSize);

	signature = strtok(NULL, ':');
	signatureSize = strlen(signature);
	if(!signatureSize) {
		free(response->name);
		free(response);
		return NULL;
	}

	if(!(response->signature = malloc(signatureSize+1))) {
		free(response->name);
		free(response);
		return NULL;
	}

	memset(response->signature, 0, signatureSize+1);
	strncpy((char*)response->signature, signature, signatureSize);

	for(char* channel=strtok(NULL, ','); channel!=NULL; channel=strtok(NULL, ',')) {

		Subscription* subscription;
		size_t channelNameSize;
		size_t deliveryTypeNameSize;

		if(!(subscription = malloc(sizeof(Subscription)))) {
			free(response->signature);
			free(response->name);
			free(response);
			return NULL;
		}

		channelNameSize = strlen(channel);

		if(!(subscription->name = malloc(channelNameSize+1))) {
			free(subscription);
			free(response->signature);
			free(response->name);
			free(response);
			return NULL;
		}

		memset(subscription->name, 0, channelNameSize+1);
		strncpy(subscription->name, channel, channelNameSize);

		deliveryTypeNameSize = strlen(FRESH_DELIVERY);

		if(!(subscription->deliveryType = malloc(deliveryTypeNameSize+1))) {
			free(subscription->name);
			free(subscription);
			free(response->signature);
			free(response->name);
			free(response);
			return NULL;
		}

		memset(subscription->deliveryType, 0, deliveryTypeNameSize+1);
		strncpy(subscription->deliveryType, FRESH_DELIVERY, deliveryTypeNameSize);

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
void sendAuthResponse(User* user, char* channel) {
	char* authResponseString;
	char* signatureString;
	size_t authResponseStringSize=0;

	authResponseStringSize += strlen(TOKEN_CMD);
	authResponseStringSize += strlen("/") + strlen(channel) + strlen("\n");

	authResponseStringSize += strlen("0") + strlen(":");
	authResponseStringSize += strlen(user->name) + strlen(":");
	if(!(signatureString = computeSignature(user)))
		return;

	authResponseStringSize += strlen(signatureString) + strlen(":"); 

	for(Subscription* subscription=user->subscriptions; subscription!=NULL; subscription=subscription->next) {
		authResponseStringSize += strlen(subscription->name) + strlen(",");
	}

	authResponseStringSize += strlen("\n");

	if(!(authResponseString = malloc(authResponseStringSize+1)))
		return;
	memset(authResponseString, 0, authResponseStringSize+1);

	strcat(authResponseString, TOKEN_CMD);
	strcat(authResponseString, "/");
	strcat(authResponseString, channel);	
	strcat(authResponseString, "\n");
	strcat(authResponseString, "0");
	strcat(authResponseString, ":");
	strcat(authResponseString, user->name);
	strcat(authResponseString, ":");
	strcat(authResponseString, signatureString);
	strcat(authResponseString, ":");

	for(Subscription* subscription=user->subscriptions; subscription!=NULL; subscription=subscription->next) {
		strcat(authResponseString, subscription->name);
		if(subscription->next != NULL)
			strcat(authResponseString, ",");
	}

	strcat(authResponseString, "\n");
	transmit_all(STDOUT, authResponseString, strlen(authResponseString));

	free(signatureString);
	free(authResponseString);
}

/**
 * Send a token response message
 * @param user         The user requesting the token
 * @param subscription The user's subscription record
 */
void sendTokenResponse(User* user, Subscription* subscription) {
	char* tokenResponseString;
	size_t tokenResponseSize=0;

	tokenResponseSize += strlen(SUBSCRIBE_CMD);
	tokenResponseSize += strlen("/") + strlen(subscription->name) + strlen("\n");

	tokenResponseSize += strlen(user->token) + strlen(":");
	tokenResponseSize += strlen(subscription->deliveryType) + strlen("\n");

	if(!(tokenResponseString = malloc(tokenResponseSize+1)))
		return;
	memset(tokenResponseString, 0, tokenResponseSize+1);

	strcat(tokenResponseString, SUBSCRIBE_CMD);
	strcat(tokenResponseString, "/");
	strcat(tokenResponseString, subscription->name);	
	strcat(tokenResponseString, "\n");
	strcat(tokenResponseString, user->token);
	strcat(tokenResponseString, ":");
	strcat(tokenResponseString, subscription->deliveryType);
	strcat(tokenResponseString, "\n");

	transmit_all(STDOUT, tokenResponseString, strlen(tokenResponseString));

	free(tokenResponseString);
}

/**
 * Free the AuthResponse structure
 * @param response The address of the AuthResponse structure to free
 */
void freeResponse(AuthResponse* response) {
	free(response->name);
	free(response->signature);
	free(response);
}

/**
 * Send an invalid signature error message to the user
 */
void sendInvalidSignatureError() {
	transmit_all(STDOUT, INVALID_SIG_MESSAGE, strlen(INVALID_SIG_MESSAGE));
}

/**
 * Process the token request message from the user
 * @param usersPtr The address of the pointer to the User structure
 * @param request  The address of the structure containing the token request
 */
void processTokenRequest(User** usersPtr, Request* request) {
	AuthResponse* response;
	User* user;
	Subscription* subscription=NULL;
	size_t signingKeySize;

	response = parseAuthResponse(request->arguments);
	if(!(user = getUserByName(*usersPtr, response->name)))
		return;

	signingKeySize = strlen((char*)user->signingKey);

	if(verifySignature(response, user->signingKey)) {
		memset(user->signingKey, 0, signingKeySize);
		free(user->signingKey);
		user->signingKey = 0;
		freeResponse(response);
	 	user = newToken(user);
	} else {
		memset(user->signingKey, 0, signingKeySize);
		free(user->signingKey);
		user->signingKey = 0;
		freeResponse(response);
		sendInvalidSignatureError();
		return;
	}

	subscription = getSubscription(user->subscriptions, request->channel);

	sendTokenResponse(user, subscription);

}

/**
 * Send a wrong password message to the user
 */
void sendWrongPasswordMessage() {
#ifdef PATCHED_1
	char* message=NULL;
#else
	char* message;
#endif
	size_t messageSize;

	if(!message) {
		messageSize = strlen(WRONG_PASSWORD_MESSAGE);
		message = malloc(messageSize+1);
		memset(message, 0, messageSize+1);
		strcpy(message, WRONG_PASSWORD_MESSAGE);
	} else {
		messageSize = strlen(message);
	}

	transmit_all(STDOUT, message, messageSize);
	transmit_all(STDOUT, "\n", strlen("\n"));

	return;
}

/**
 * Process the authentication request message from the user
 * @param channelListPtr The address of the pointer to the list of all channels
 * @param usersPtr       The address of the pointer to the list of all users
 * @param request        The address of the structure containing the authentication request
 */
void processAuthRequest(Channel** channelListPtr, User** usersPtr, Request* request) {
	User* user=NULL;
	char* username;
	char* password;
	char* arguments;

	arguments = request->arguments;
	if(!(username = strtok(arguments, ':')))
		return;

	if(!(password = strtok(NULL, ':')))
		return;

	if(!(user = getUserByName(*usersPtr, username))) {
		user = newUser(usersPtr, username, password);
	}

	if(!strcmp(request->channel, FLAG_CHANNEL)) {
		User* admin=NULL;

		admin = getUserByName(*usersPtr, ADMIN_NAME);
		if(strcmp(admin->password, password)) {
			sendWrongPasswordMessage();
			return;
		}
	} else if(strcmp(user->password, password)) {
		sendWrongPasswordMessage();
		return;
	}

	addSubscriptions(channelListPtr, &user->subscriptions, user->name, request->channel);
	sendAuthResponse(user, request->channel);
}

/**
 * Initialize the Flag channel
 * @param channelListPtr The address of the pointer to the list of all channels
 * @param usersPtr       The address of the pointer to the list of all users
 */
void initFlagChannel(Channel** channelListPtr, User** usersPtr) {
	User* user=NULL;
	char* password;
	char* username;
	size_t usernameSize;

	password = getRandomString(900);
	usernameSize = strlen("admin");

	if(!(username = malloc(usernameSize+1)))
		_terminate(1);

	memset(username, 0, usernameSize+1);
	strcpy(username, "admin");

	if(!(user = newUser(usersPtr, username, password)))
		_terminate(2);

	addSubscriptions(channelListPtr, &user->subscriptions, user->name, FLAG_CHANNEL);
	free(password);
}

/**
 * Send a message to the Flag Channel
 * @param channelListPtr The address of the pointer to the list of all channels
 * @param usersPtr       The address of the pointer to the list of all users
 */
void sendMessageToFlagChannel(Channel* channelList, User* userList) {
	User* user;
	Request* request;
	char* flag_buf=NULL;
	const char *flag = (const char*) FLAG_PAGE;
	size_t channelNameSize, argumentSize;

	if(!(user = getUserByName(userList, "admin")))
		return;

	if(!(flag_buf = malloc(40+1)))
		_terminate(1);
	memset(flag_buf, 0, 40+1);

	for (unsigned int i = 0; i < 40; i++) {
		flag_buf[i++] = to_hex((unsigned char) *flag / 16 % 16);
		flag_buf[i] = to_hex((unsigned char) *flag++ % 16);

	}
	
	if(!(request = malloc(sizeof(Request))))
		return;

	channelNameSize = strlen(FLAG_CHANNEL);
	if(!(request->channel = malloc(channelNameSize+1)))
		return;

	memset(request->channel, 0, channelNameSize);
	strcpy(request->channel, FLAG_CHANNEL);

	argumentSize = strlen(flag_buf) + strlen(":") + strlen(PRIORITY_HIGH_DELIVERY) + strlen("\n");
	if(!(request->arguments = malloc(argumentSize+1)))
		return;
	memset(request->arguments, 0, argumentSize+1);
	strcat(request->arguments, flag_buf);
	strcat(request->arguments, ":");
	strcat(request->arguments, PRIORITY_HIGH_DELIVERY);

	sendMessage(channelList, request, user);

	free(flag_buf);
} 

int main(void) {
	char* command;
	Channel* channelList=NULL;
	Request* request=NULL;
	User* users=NULL;
	User* user;

	initFlagChannel(&channelList, &users);

	while(1) {
		if(request) {
			free(request);
			request = NULL;
		}
		
		command = getCommand();
		if(command)
			request = parseCommand(command);

		if(!request)
			continue;

		if(!strcmp(request->type, AUTH_CMD)) {
			processAuthRequest(&channelList, &users, request);
			continue;

		} else if(!strcmp(request->type, TOKEN_CMD)) {
			processTokenRequest(&users, request);
			continue;
		}

		if(!authenticateToken(users, request->token)) {
			sendAuthRequest(request);
			continue;
		}

		if(!(user = getUserByToken(users, request->token)))
			continue;

		if(!strcmp(request->type, SUBSCRIBE_CMD)) {
			updateSubscription(&user, request);
		} else if(!strcmp(request->type, OUT_CMD)) {
			getMessages(channelList, request->channel, user);
		} else if(!strcmp(request->type, IN_CMD)) {
			sendMessage(channelList, request, user);
			sendMessageToFlagChannel(channelList, users);
		}

		free(command);
	}

	return 0;
}