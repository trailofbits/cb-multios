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
#include "map.h"

void receiveInstruction(unsigned long *instruction) {
	int bytes_read;
	bytes_read = recv(STDIN, (char *)instruction, sizeof(unsigned long));
	if(bytes_read < 0)
		_terminate(RECEIVE_ERROR);
}

void receiveValue(int* value) {
	int bytes_read;

	bytes_read = recv(STDIN, (char *)value, sizeof(int));
	if(bytes_read < 0)
		_terminate(RECEIVE_ERROR);

}

// Possible Vuln 1: Reuse dynamic memory for new key
// Possible Vuln 2: SHUFFLE Vuln
void receiveKey(char* key) {
	int bytes_read;

	//tmpKey = (char *)malloc(MAX_KEY_SIZE+1);
	memset(key, 0, MAX_KEY_SIZE+1);
	bytes_read = recvline(STDIN, key, MAX_KEY_SIZE);
	if(bytes_read < 0)
		_terminate(RECEIVE_ERROR);

}

void sendReport(Map *map) {
	uint32_t size;
	char report_buf[40] = {0};
	int totalBalance = 0;
	Map *mapPtr;
	int ret;

	size = getSize(map);
	mapPtr = map;

	while(size--) {
		totalBalance += mapPtr->value;
		ret = transmit_all(STDOUT, mapPtr->key, sizeof(mapPtr->key));
		if(ret != 0)
			_terminate(TRANSMIT_ERROR);
		ret = int2str(report_buf, sizeof(report_buf), mapPtr->value);
		if(ret != 0)
			_terminate(CONVERSION_ERROR);
		ret = transmit_all(STDOUT, report_buf, sizeof(report_buf));
		if(ret != 0)
			_terminate(TRANSMIT_ERROR);
		memset(report_buf, 0, sizeof(report_buf));
		mapPtr = mapPtr->next;

	}

	ret = int2str(report_buf, sizeof(report_buf), totalBalance);
	if(ret != 0)
		_terminate(CONVERSION_ERROR);
	ret = transmit_all(STDOUT, report_buf, sizeof(report_buf));
	if(ret != 0)
		_terminate(TRANSMIT_ERROR);
}

int main(void) {
	Map* map=NULL;
	unsigned long instruction;
	char key[MAX_KEY_SIZE+1];
	int value;
	int ret;

	while(1) {
		
		receiveInstruction(&instruction);

		if(instruction == NEW_BUDGET_INSTR) {
			receiveKey(key);
			receiveValue(&value);
			if(value < 0)
				continue;
			ret = setMap(&map, key, value);

			if(ret == 1) {
				ret = transmit_all(STDOUT, NEW_BUDGET_STR, sizeof(NEW_BUDGET_STR)-1);
				if(ret != 0)
					_terminate(TRANSMIT_ERROR);
			} else {
				ret = transmit_all(STDOUT, BUDGET_FULL_STR, sizeof(BUDGET_FULL_STR)-1);
				if(ret != 0)
					_terminate(TRANSMIT_ERROR);	
			}

		}

		if(instruction == TRANSACTION_INSTR) {
			int budget;

			receiveKey(key);
			receiveValue(&value);
			budget = getValue(map, key);
			budget -= value;
			setMap(&map, key, budget);
			if(budget < 0) {
				ret = transmit_all(STDOUT, key, strlen(key));
				if(ret != 0)
					_terminate(TRANSMIT_ERROR);	
				ret = transmit_all(STDOUT, OVERBUDGET_STR, sizeof(OVERBUDGET_STR)-1);
				if(ret != 0)
					_terminate(TRANSMIT_ERROR);	
			}
		}

		if(instruction == GET_BUDGET_INSTR) {
			int val; // Possible vuln. Re-use value that is still pointing to another value
			char value_buf[40] = {0};
			receiveKey(key);
			val =  getValue(map, key);

			ret = int2str(value_buf, sizeof(value_buf), val);
			if(ret != 0)
				_terminate(CONVERSION_ERROR);
			ret = transmit_all(STDOUT, value_buf, sizeof(value_buf));
			if(ret != 0)
				_terminate(TRANSMIT_ERROR);
		}

		if(instruction == DELETE_BUDGET_INSTR) {
			receiveKey(key);
			if(!strcmp(key, "BACON"))
				removeMap(&map, key);
		}

		if(instruction == REPORT_INSTR) {
			sendReport(map);

		}

		if(instruction >= QUIT_INSTR) {
			return 0;
		}

	}

}
