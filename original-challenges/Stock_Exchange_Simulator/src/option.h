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

#ifndef OPTION_H
#define OPTION_H
#define KEY_LEN 32
#define NUM_ORDERS 1024
#define SYM_SIZE 8
#define PGSIZE 4096
#define PKTSIZE 4096*4
#include "libc.h"
#include "account.h"

typedef enum {
	BUY = 0,
	SELL = 0xFF,
	QUOTE = 0xDD00,

	
	ERR = 0xFFFF,


} OP_TYPE;

typedef enum {
	OK = 0,
	NO_CASH,
	NO_FILL = 0x55,
	NO_MATCH = 0x88,
	NO_HOLD = 0x66,
	EMPTY_ORDER = 0xbb,
	SELL_ADD = 0x99,
	BAD_SIG = 0xcc,
	QTY_OVERFLOW = 0xee,
	NO_HOLD_QTY,
	BAD_ACCT,
	UNK_E,
	ORDERS_FULL = 0xFFFFFF,
	ORDERFILL = 0xFF0000,

} OP_ERR;

typedef enum {
	REQUEST = 0,
	RESPONSE
} R_TYPE;

typedef struct packet {
	R_TYPE rt;
	OP_TYPE ot;
	uint32_t acct_id;
	uint32_t data_l;
	uint32_t bank_id;
	void * op_data;

} packet_t;

typedef struct option_quote {
	float ask;
	char symbol[SYM_SIZE];

} option_quote_t;


typedef struct orderfill {
	char symbol[SYM_SIZE];
	uint32_t qty;

} orderfill_t;


typedef struct option_order {

	float price;
	uint32_t qty;
	char symbol[SYM_SIZE];
	char sig[KEY_LEN];
} option_order_t;


typedef struct orderbook_order{
	uint32_t acct_id;
	option_order_t contract;
	uint32_t order_id;
	OP_TYPE direction;

	

	
} orderbook_order_t;

orderbook_order_t ORDERBOOK[NUM_ORDERS];

OP_ERR run_option_transaction(uint32_t acct_id, option_order_t *order, OP_TYPE ot);
size_t gen_order_fill_msg(packet_t *resp, OP_TYPE ot, char * sym, uint32_t qty, uint32_t acct_id);
float get_current_ask(char * sym);


#endif
