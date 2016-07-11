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

#define BALANCE_RECORD 0
#define NO_MORE_RECORDS -1
#define STOCK_RECORD 1
#define MAX_INPUT_SIZE 20
#define EOL_STR "\n"
#define LEARNING_MODE_SIZE 100
#define GOAL_STR "You doubled your money!\n"
#define GOAL_VAL 20000
#define STARTING_BALANCE 10000
#define X_STR 'X'
#define Y_STR 'Y'
#define RECORD_SIZE 8
#define INIT_ENTRY_LIST 16

#define TRANSMIT_ERROR 1
#define RECEIVE_ERROR 2
#define ALLOCATE_ERROR 3
#define DEALLOCATE_ERROR 4

typedef struct {
	unsigned short x;
	unsigned short y;
} Record; 

typedef struct {
	int sampleSize;
	float mean;
	float Q;
	float variance;
	float stdDev;
} Dataset;

typedef struct {
	char symbol;
	unsigned short currentPrice;
	unsigned short purchasedPrice;
} Stock;

typedef struct {
	unsigned short cashBalance;
	unsigned short assetBalance;
	unsigned short goal;
	unsigned short numEntries;
	Stock* stocks;
} Portfolio;
