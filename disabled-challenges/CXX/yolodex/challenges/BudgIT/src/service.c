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
#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_service.h"
#include "cgc_map.h"

void cgc_receiveInstruction(unsigned long *instruction) {
	int bytes_read;
	bytes_read = cgc_recv(STDIN, (char *)instruction, sizeof(unsigned long));
	if(bytes_read < 0)
		cgc__terminate(RECEIVE_ERROR);
}

void cgc_receiveValue(int* value) {
	int bytes_read;

	bytes_read = cgc_recv(STDIN, (char *)value, sizeof(int));
	if(bytes_read < 0)
		cgc__terminate(RECEIVE_ERROR);

}

// Possible Vuln 1: Reuse dynamic memory for new key
// Possible Vuln 2: SHUFFLE Vuln
void cgc_receiveKey(char* key) {
	int bytes_read;

	//tmpKey = (char *)malloc(MAX_KEY_SIZE+1);
	cgc_memset(key, 0, MAX_KEY_SIZE+1);
	bytes_read = cgc_recvline(STDIN, key, MAX_KEY_SIZE);
	if(bytes_read < 0)
		cgc__terminate(RECEIVE_ERROR);

}

void cgc_sendReport(Map *map) {
	uint32_t size;
	char report_buf[40] = {0};
	int totalBalance = 0;
	Map *mapPtr;
	int ret;

	size = cgc_getSize(map);
	mapPtr = map;

	while(size--) {
		totalBalance += mapPtr->value;
		ret = cgc_transmit_all(STDOUT, mapPtr->key, sizeof(mapPtr->key));
		if(ret != 0)
			cgc__terminate(TRANSMIT_ERROR);
		ret = cgc_int2str(report_buf, sizeof(report_buf), mapPtr->value);
		if(ret != 0)
			cgc__terminate(CONVERSION_ERROR);
		ret = cgc_transmit_all(STDOUT, report_buf, sizeof(report_buf));
		if(ret != 0)
			cgc__terminate(TRANSMIT_ERROR);
		cgc_memset(report_buf, 0, sizeof(report_buf));
		mapPtr = mapPtr->next;

	}

	ret = cgc_int2str(report_buf, sizeof(report_buf), totalBalance);
	if(ret != 0)
		cgc__terminate(CONVERSION_ERROR);
	ret = cgc_transmit_all(STDOUT, report_buf, sizeof(report_buf));
	if(ret != 0)
		cgc__terminate(TRANSMIT_ERROR);
}

int main(int cgc_argc, char *cgc_argv[]) {
	Map* map=NULL;
	unsigned long instruction;
	char key[MAX_KEY_SIZE+1];
	int value;
	int ret;

	while(1) {
		
		cgc_receiveInstruction(&instruction);

		if(instruction == NEW_BUDGET_INSTR) {
			cgc_receiveKey(key);
			cgc_receiveValue(&value);
			if(value < 0)
				continue;
			ret = cgc_setMap(&map, key, value);

			if(ret == 1) {
				ret = cgc_transmit_all(STDOUT, NEW_BUDGET_STR, sizeof(NEW_BUDGET_STR)-1);
				if(ret != 0)
					cgc__terminate(TRANSMIT_ERROR);
			} else {
				ret = cgc_transmit_all(STDOUT, BUDGET_FULL_STR, sizeof(BUDGET_FULL_STR)-1);
				if(ret != 0)
					cgc__terminate(TRANSMIT_ERROR);	
			}

		}

		if(instruction == TRANSACTION_INSTR) {
			int budget;

			cgc_receiveKey(key);
			cgc_receiveValue(&value);
			budget = cgc_getValue(map, key);
			budget -= value;
			cgc_setMap(&map, key, budget);
			if(budget < 0) {
				ret = cgc_transmit_all(STDOUT, key, cgc_strlen(key));
				if(ret != 0)
					cgc__terminate(TRANSMIT_ERROR);	
				ret = cgc_transmit_all(STDOUT, OVERBUDGET_STR, sizeof(OVERBUDGET_STR)-1);
				if(ret != 0)
					cgc__terminate(TRANSMIT_ERROR);	
			}
		}

		if(instruction == GET_BUDGET_INSTR) {
			int val; // Possible vuln. Re-use value that is still pointing to another value
			char value_buf[40] = {0};
			cgc_receiveKey(key);
			val =  cgc_getValue(map, key);

			ret = cgc_int2str(value_buf, sizeof(value_buf), val);
			if(ret != 0)
				cgc__terminate(CONVERSION_ERROR);
			ret = cgc_transmit_all(STDOUT, value_buf, sizeof(value_buf));
			if(ret != 0)
				cgc__terminate(TRANSMIT_ERROR);
		}

		if(instruction == DELETE_BUDGET_INSTR) {
			cgc_receiveKey(key);
			if(!cgc_strcmp(key, "BACON"))
				cgc_removeMap(&map, key);
		}

		if(instruction == REPORT_INSTR) {
			cgc_sendReport(map);

		}

		if(instruction >= QUIT_INSTR) {
			return 0;
		}

	}

}
