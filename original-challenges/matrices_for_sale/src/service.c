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
#include <libcgc.h>
#include "libc.h"
#include "service.h"

void identityMap(Message* message)
{

}

void constantMap(Message* message)
{
		message->value[PERM_FIELD] = 1;

}

void absoluteValueMap(Message* message)
{
	// Vuln: Use unsigned int for absolute value conversion
	unsigned short absoluteVal;
	short mask;
	short i;

#ifdef PATCHED
	for(i = LENGTH_FIELD; i < NUM_VALS; i++) {
#else
	for(i = LENGTH_FIELD; i < NUM_VALS-2; i++) {
#endif

#ifdef PATCHED
		if(SHRT_MIN == message->value[i]) {
			message->value[i] = SHRT_MAX;
		} else {
#else
#endif
			mask = message->value[i] >> (sizeof(short) * CHAR_BIT - 1);
			absoluteVal = (message->value[i] + mask) ^ mask;
			message->value[i] = absoluteVal;
#ifdef PATCHED	
		}
#else
#endif
	}

}

int modulus(short n, short M) {
	short result;
	if (M == 0)
		return n;
	//result = ((n % M) + M) % M;
	result = n % M;
	return result;
}

void modulusCoordinatesWithDimensions(Message* message)
{

	message->value[X_FIELD] = modulus(message->value[X_FIELD], message->value[LENGTH_FIELD]);
	message->value[Y_FIELD] = modulus(message->value[Y_FIELD], message->value[WIDTH_FIELD]);

}

void processMessage(Worker* worker)
{
	Message* message;
	message = worker->inbox;

	if(message != NULL) {
		worker->processMessage(message);
		worker->outbox = message;
		worker->inbox = NULL;
	}
}


void receiveMessage(Message* message) {
	size_t bytes_read = 0;
	size_t message_size;
	char *message_ptr;

	message_ptr = (char *) message;
	message_size = sizeof(Message) - sizeof(short**) - 2;

	while(message_size) {
		if(receive(STDIN, message_ptr++, 1, &bytes_read))
			_terminate(ERROR_FAILED_RECV);

		message_size--;
	}
}

void sendMessage(Message* message) {

	if(transmit_all(STDOUT, (char *) message, sizeof(Message) - sizeof(short**)))
		_terminate(ERROR_FAILED_SEND);

}

void swap (Worker *workerA, Worker *workerB)
{
 	void (* temp)(Message* );
	temp = workerA->processMessage;
	workerA->processMessage = workerB->processMessage;
	workerB->processMessage = temp;

}

void permute(Worker* list, int start, int end, int* index, int stop)
{
	int j;
	
	if((*index) == stop)
		return;

	if(start == end)
	{
		(*index)++;
	}
	else 
	{
		for(j = start; j <= end; j++)
		{
			swap(&list[start], &list[j]);
			permute(list, start+1, end, index, stop);
			if((*index) != stop)
				swap(&list[start], &list[j]);
			else
				break;
		}
	}

}

void computeResult(Message *message)
{
	short x, y;
	x = message->value[X_FIELD];
	y = message->value[Y_FIELD];

	if(message->result == NULL) {
		int ret;
		short *result_data;

		ret = allocate(message->value[LENGTH_FIELD]*sizeof(short*), 0, (void **) &message->result);
		if (ret != 0)
			_terminate(1);

		ret = allocate(message->value[LENGTH_FIELD]*message->value[WIDTH_FIELD]*sizeof(short), 0, (void **) &result_data);
		if (ret != 0)
			_terminate(1);

		int i;
		for(i=0; i<message->value[LENGTH_FIELD]; i++)
			message->result[i] = result_data + i * message->value[WIDTH_FIELD];
	}

	int i;
	for(i=0; i < message->value[LENGTH_FIELD]*message->value[WIDTH_FIELD]; i++)
	{
		message->result[x][y] = 1;

#ifdef PATCHED
		x = message->value[LENGTH_FIELD] - x;
		if( message->value[X_FIELD] >= x)
			x = message->value[X_FIELD] - x;
		else
			x = message->value[LENGTH_FIELD] - x + message->value[X_FIELD];

		y = message->value[WIDTH_FIELD] - y;
		if( message->value[Y_FIELD] >= y)
			y = message->value[Y_FIELD] - y;
		else
			y = message->value[WIDTH_FIELD] - y + message->value[Y_FIELD];
		
#else
		x = modulus(x+message->value[X_FIELD], message->value[LENGTH_FIELD]);
		y = modulus(y+message->value[Y_FIELD], message->value[WIDTH_FIELD]);
#endif

	}

}

int main(void) {
	Message* message = NULL;
	Worker worker[4] = {0};
	int i;
	int index;
	int ret;

	ret = allocate(sizeof(Message), 0, (void **) &message);
	if(ret != 0)
		_terminate(1);

	receiveMessage(message);

	worker[0].processMessage = identityMap;
	worker[1].processMessage = constantMap;
	worker[2].processMessage = absoluteValueMap;
	worker[3].processMessage = modulusCoordinatesWithDimensions;

	index = 0; 

	permute(worker, 0, 3, &index, message->value[PERM_FIELD]);

	while(1) {

		worker[0].inbox = message;

		for(i=3; i>=0; i--) {
			processMessage(&worker[i]);

			if(i<3)
				worker[i+1].inbox = worker[i].outbox;
		}

		if(worker[3].outbox != NULL) {

			computeResult(worker[3].outbox);

			sendMessage(worker[3].outbox);

			ret = deallocate(worker[3].outbox->result[0], worker[3].outbox->value[LENGTH_FIELD]*worker[3].outbox->value[WIDTH_FIELD]*sizeof(short));
			if (ret != 0)
				_terminate(2);

			ret = deallocate(worker[3].outbox->result, worker[3].outbox->value[LENGTH_FIELD]*sizeof(short*));
			if (ret != 0)
				_terminate(2);

			ret = deallocate(worker[3].outbox, sizeof(Message));
			if (ret != 0)
				_terminate(2);
		}

		ret = allocate(sizeof(Message), 0, (void **) &message);
		if(ret != 0)
			_terminate(1);

		receiveMessage(message);
	}


}
