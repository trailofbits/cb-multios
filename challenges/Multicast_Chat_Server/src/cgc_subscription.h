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
#define GUARANTEED_DELIVERY "guaranteed"
#define FRESH_DELIVERY "latest"
#define INCREMENTAL_DELIVERY "next"
#define PRIORITY_HIGH_DELIVERY "high"
#define PRIORITY_MEDIUM_DELIVERY "medium"
#define PRIORITY_LOW_DELIVERY "low"

typedef struct {
	unsigned int id;
	char* sender;
	char* body;
	char* priority;
	void* next;
} Message;

typedef struct {
	char* name;
	char* deliveryType;
	unsigned int index;
	void* next;
} Subscription;

typedef struct {
	char* name;
	unsigned int head;
	unsigned int tail;
	Message* queue;
	Subscription* subscriptions;
	void* next;
} Channel;

void cgc_addSubscriptions(Channel** channelListPtr, Subscription** userSubscriptionsPtr, char* userName, char* channelName);
int cgc_setDeliveryType(Subscription** subscriptionPtr, char* deliveryType);
Subscription* cgc_getSubscription(Subscription* subscriptions, char* subscriptionName);
Subscription* cgc_newSubscription(char* name, unsigned index, char* deliveryType);
Channel* cgc_getChannel(Channel* channelList, char* channelName);
Message* cgc_getLastMessage(Message* queue);
Message* cgc_getMessageById(Message* queue, unsigned int id);
void cgc_cleanupChannel(Channel* channel);
