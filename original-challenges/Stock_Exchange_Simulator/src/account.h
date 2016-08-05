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


#ifndef ACCOUNTSTATIC_H
#define ACCOUNTSTATIC_H
#define NUM_ACCOUNTS 100
#define KEY_LEN 32
#define MAX_HOLDINGS 32
#define SYM_SIZE 8
#include "option.h"
typedef struct option_holding {
	uint32_t qty;
	char symbol[SYM_SIZE];

} option_holding_t; 

typedef struct account_record {
	float balance;
	char key[KEY_LEN];
	option_holding_t holdings[MAX_HOLDINGS];
} account_record_t;


extern account_record_t ACCOUNTS[];
void init_account(uint32_t idx, float balance, char *key);
void init_accounts();
option_holding_t * next_holding(uint32_t acct_id);
#endif
