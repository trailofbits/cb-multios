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
#include "libc.h"

/**
 * Create a new subscription with the given name, index and delivery type
 * @param  name         The name of the new subscription
 * @param  index        The initial index of the new subscription
 * @param  deliveryType The delivery type of the new subscription
 * @return              The address of the new Subscription structure
 */
Subscription* newSubscription(char* name, unsigned index, char* deliveryType) {
	Subscription* subscription;
	size_t channelNameLength;

	if(!(subscription = malloc(sizeof(Subscription))))
		return NULL;

	if(setDeliveryType(&subscription, deliveryType)) {
		free(subscription);
		return NULL;
	}

	channelNameLength  = strlen(name);
	if(!(subscription->name = malloc(channelNameLength+1))) {
		free(subscription->deliveryType);
		free(subscription);
		return NULL;
	}

	memset(subscription->name, 0, channelNameLength+1);
	strncpy(subscription->name, name, channelNameLength);
	subscription->index = index;
	subscription->next = NULL;

	return subscription;
}

/**
 * Find a channel that matches channelName
 * @param  channelList The list of channels to search
 * @param  channelName The channel name to match
 * @return             The address of the found Channel structure,
 *                     NULL if not found.
 */
Channel* getChannel(Channel* channelList, char* channelName) {
	for(Channel* channel=channelList; channel!=NULL; channel=channel->next) {
		if(!strcmp(channel->name, channelName)) 
			return channel;
	}

	return NULL;
}

/**
 * Find a subscription that matches subscriptionName
 * @param  subscriptions 	 The list of subscriptions to search
 * @param  subscriptionName  The subscription name to match
 * @return                   The address of the found Subscription structure,
 *                           NULL if not found.
 */
Subscription* getSubscription(Subscription* subscriptions, char* subscriptionName) {
	for(Subscription* subscription=subscriptions; subscription!=NULL; subscription=subscription->next) {
		if(!strcmp(subscription->name, subscriptionName)) 
			return subscription;
	}

	return NULL;
}

/**
 * Set the delivery type of the subscription
 * @param  subscriptionPtr The address of the pointer to the Subscription
 * @param  deliveryType    The delivery type to assign
 * @return                 1 if the assignment fails, 0 otherwise.
 */
int setDeliveryType(Subscription** subscriptionPtr, char* deliveryType) {
	Subscription* subscription;

	subscription = *subscriptionPtr;

	if(!strcmp(GUARANTEED_DELIVERY, deliveryType) ||
	   !strcmp(FRESH_DELIVERY, deliveryType) ||
	   !strcmp(PRIORITY_HIGH_DELIVERY, deliveryType) ||
	   !strcmp(PRIORITY_MEDIUM_DELIVERY, deliveryType) ||
	   !strcmp(PRIORITY_LOW_DELIVERY, deliveryType)) {

		if(!(subscription->deliveryType = malloc(strlen(deliveryType)+1)))
			return 1;

		memset(subscription->deliveryType, 0, strlen(deliveryType)+1);
		strcpy(subscription->deliveryType, deliveryType);
	} else if(atoi(deliveryType) > 0) {
		if(!(subscription->deliveryType = malloc(strlen(deliveryType)+1)))
			return 1;

		memset(subscription->deliveryType, 0, strlen(deliveryType)+1);
		strcpy(subscription->deliveryType, deliveryType);			
	} else {
		return 1;
	}

	*subscriptionPtr = subscription;

	return 0;
}

/**
 * Get the message from the queue with the matching id
 * @param  queue The queue to search
 * @param  id    The message id to match
 * @return       The address of the found Message structure,
 *               NULL if not found.
 */
Message* getMessageById(Message* queue, unsigned int id) {
	Message* message=NULL;

	for(message=queue; message!=NULL; message=message->next) {
		if(message->id == id)
			return message;
	}

	return NULL;
}

/**
 * Get the last message in the queue
 * @param  queue The queue to search
 * @return       The address of the found Message structure,
 *               NULL if not found.
 */
Message* getLastMessage(Message* queue) {
	Message* lastMessage;

	if(!queue)
		return NULL;

	for(lastMessage=queue; lastMessage->next!=NULL; lastMessage=lastMessage->next);

	return lastMessage;
}

/**
 * Remove all messages from the channel's queue that will not be sent,
 * and update head value
 * @param channel The address of the channel to cleanup
 */
void cleanupChannel(Channel* channel) {
	unsigned int head;

	head = channel->tail;
	for(Subscription* subscription=channel->subscriptions; subscription!= NULL; subscription=subscription->next) {
		if(subscription->index < head)
			head = subscription->index;
	}

	while(head > channel->head) {
		Message* message;

		message = channel->queue;
		channel->queue = message->next;
		channel->head++;
	}
}

/**
 * Create a new channel
 * @param  name The name to assign the channel
 * @return      The address of the new Channel structure
 */
Channel* newChannel(char* name) {
	Channel* channel;
	size_t nameSize;

	if(!(channel = malloc(sizeof(Channel))))
		return NULL;

	nameSize = strlen(name);
	if(!(channel->name = malloc(nameSize))) {
		free(channel);
		return NULL;
	}
	memset(channel->name, 0, nameSize);
	strcpy(channel->name, name);
	channel->head = 0;
	channel->tail = 0;
	channel->subscriptions = NULL;
	channel->queue = NULL;
	channel->next = NULL;

	return channel;
}

/**
 * Add subscribed channels to the user
 * @param channelListPtr       The list of channels
 * @param userSubscriptionsPtr The list of the user's subscriptions
 * @param userName             The name of the user
 * @param channelName          The name of the channel to subscribe the user to
 */
void addSubscriptions(Channel** channelListPtr, Subscription** userSubscriptionsPtr, char* userName, char* channelName) {
	Subscription* userSubscription;
	Subscription* channelSubscription;
	Subscription* subscriptions;
	Channel* channelList;
	Channel* channel;

	channelList = *channelListPtr;
	if(!(channel = getChannel(channelList, channelName))) {
		if(!(channel = newChannel(channelName)))
			return;
		channel->next = *channelListPtr;
		*channelListPtr = channel;
	}

	subscriptions = *userSubscriptionsPtr;
	if((userSubscription = getSubscription(subscriptions, channel->name))) {
		userSubscription->index = channel->tail;
		return;
	}


	userSubscription = newSubscription(channel->name, channel->tail, FRESH_DELIVERY);
	userSubscription->next = subscriptions;
	subscriptions = userSubscription;

	channelSubscription = newSubscription(userName, channel->tail, FRESH_DELIVERY);
	channelSubscription->next = channel->subscriptions;
	channel->subscriptions = channelSubscription;

	*userSubscriptionsPtr = subscriptions;
	
}
