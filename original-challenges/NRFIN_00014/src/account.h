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
 
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "ll.h"
#include "multipass.h"

#define TXN_OPEN 1
#define TXN_CLOSED 0

typedef struct account_entry {
	uint32_t card_id;
	uint32_t auth_code;
	uint32_t initial_balance;
	uint32_t balance;
	alloc_head_t *txn_log;

} account_entry_t;

typedef struct accounts_listing {
	alloc_head_t *accounts;
	uint32_t n_entries;

} accounts_listing_t;

typedef struct txn_entry {
	char is_open;
	// duplicate, but easier to reference
	uint32_t transaction_id;
	size_t data_sz;
	packet_head_t *p;
	PKT_TYPE state;
	void * data;

} txn_entry_t;

typedef struct acct_txn_entry{
	account_entry_t *ae;
	txn_entry_t *txn;
}acct_txn_entry_t;

txn_entry_t * get_transaction(account_entry_t *ae, uint32_t txn_id);
account_entry_t * get_account(uint32_t card_id, uint32_t auth_code);
int create_account(uint32_t card_id,	uint32_t auth_code, packet_data_balance_t *b);
void init_account_register();
txn_entry_t * open_txn(account_entry_t *ae, packet_head_t * ph);
size_t get_size_of_data_for_pkt_head_only(packet_head_t *ph, uint32_t is_client);
txn_entry_t * add_transaction_log_entry(account_entry_t * ae,  pack_and_data_t *pad);
txn_entry_t * transaction_iterator(account_entry_t *ae);
int finalize_transaction(txn_entry_t * te);
txn_entry_t * remove_transaction_log_entry(account_entry_t * ae, txn_entry_t * ti);

#endif