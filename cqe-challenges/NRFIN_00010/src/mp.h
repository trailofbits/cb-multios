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


#ifndef MULTIPASS_H
#define MULTIPASS_H
#include "service.h"

#define FIRST_CARD_ID 			223344
#define FIRST_CARD_AUTH_CODE	114466
#define FIRST_TRANSACTION_ID	191919

typedef enum {
	TRANSIT = 0,	// 0
	VENDING,		// 1
	CONVENIENCE,	// 2
	RESTAURANT,		// 3
	GAS,			// 4
	MOVIE,			// 5
	CAR 			// 6
} VENDOR_TYPE;

typedef enum {
	PURCHASE = 0,	// 0
	RECHARGE,		// 1
	BALANCE,		// 2
	HISTORY,		// 3
	ISSUE,			// 4
	REFUND			// 5
} OP_CODE;

typedef enum {
	INIT = 0,	// 0
	AUTH,		// 1
	OPS,		// 2
	FIN 		// 3
} PKT_TYPE;


typedef struct vendor {
	uint32_t vendor_id;			
	VENDOR_TYPE vendor_type : 8;
	uint8_t vendor_location_sz;
	char * vendor_location;
} vendor_t;

typedef struct packet_head {
	uint32_t card_id;			// 4 bytes
	uint32_t auth_code;			// 4 bytes
	PKT_TYPE pkt_type : 8;		// 1 byte
	OP_CODE op_code : 8;		// 1 byte
	STATUS status : 8;			// 1 byte
	uint32_t transaction_id;	// 4 bytes
} packet_head_t;

typedef struct packet_data_error {
	uint32_t length;
	char * msg;
} packet_data_error_t;

typedef struct packet_data_issue {
	uint32_t amount;
} packet_data_issue_t;

typedef struct packet_data_balance {
	uint32_t balance;
} packet_data_balance_t;

typedef struct packet_data_history {
	uint32_t count;
} packet_data_history_t;

typedef struct packet_data_purchase {
	uint32_t purchase_id;
	uint32_t cost;
	vendor_t v;
} packet_data_purchase_t;

typedef struct packet_data_recharge {
	uint32_t amount;
	vendor_t v;
} packet_data_recharge_t;

typedef struct packet_data_refund {
	uint32_t purchase_id;
	uint32_t transaction_id;
} packet_data_refund_t;

typedef struct transaction {
	OP_CODE op_code : 8;
	PKT_TYPE state : 8;
	STATUS status : 8;
	uint32_t card_id;
	uint32_t transaction_id;
	void * details;
} transaction_t;

typedef struct card {
	uint32_t card_id;
	uint32_t auth_code;
	uint32_t balance;
} card_t;


int transaction_node_contains(struct node * nd, void * key_value);
int card_node_contains(struct node * nd, void * key_value);

int card_create(card_t ** card, uint32_t card_count, uint32_t initial_amount);
int card_add_to_list(card_t * card, list_t * card_list);
int card_create_and_add_to_list(card_t ** card, list_t * card_list, uint32_t initial_amount);
int card_get(card_t ** card, uint32_t card_id, list_t * card_list);
int card_is_valid(uint32_t card_id, uint32_t auth_code, list_t * card_list);

int card_purchase(uint32_t card_id, list_t * card_list, uint32_t amount);
int card_recharge(uint32_t card_id, list_t * card_list, uint32_t amount);
int card_get_balance(uint32_t card_id, list_t * card_list, uint32_t * balance);
int card_refund(uint32_t card_id, list_t * card_list, transaction_t * tr);

int transaction_create(transaction_t ** tr, uint32_t tr_count, packet_head_t * pkt_hdr_ptr);
int transaction_add_to_list(transaction_t * tr, list_t * tr_list);
int transaction_create_and_add_to_list(transaction_t ** tr, list_t * tr_list, packet_head_t * pkt_hdr_ptr, uint32_t card_id);
int transaction_get(transaction_t ** tr, uint32_t transaction_id, OP_CODE op_code, list_t * tr_list);
void transaction_update_state(transaction_t ** tr, PKT_TYPE state);
void transaction_set_details(transaction_t ** tr, void * pd);

int transaction_get_and_verify_purchase_id(list_t * tr_list, packet_data_refund_t * pdr, transaction_t ** ref_tr);
int transaction_rm_purchase_details(transaction_t ** tr);
int transaction_rm_from_list(node_t ** tr, list_t * tr_list, uint32_t transaction_id);
int transaction_destroy(list_t * tr_list, uint32_t transaction_id);

int transaction_get_history_count_and_send(uint32_t card_id, list_t * tr_list, uint32_t max_tr_count);
int transaction_list_send_last_n(uint32_t card_id, list_t * tr_list, uint32_t tr_count);

int transaction_send_details(transaction_t * tr);
void transaction_send_purchase(void * details);
void transaction_send_recharge(void * details);
void transaction_send_balance(void * details);
void transaction_send_history(void * details);
void transaction_send_issue(void * details);
void transaction_send_refund(void * details);
void transaction_send_vendor_loc(vendor_t * v);

int transaction_recv_issue(packet_data_issue_t ** pdi);
int transaction_recv_purchase(packet_data_purchase_t ** pdp);
int transaction_recv_recharge(packet_data_recharge_t ** pdr);
int transaction_recv_balance(packet_data_balance_t ** pdb);
int transaction_recv_history(packet_data_history_t ** pdh);
int transaction_recv_refund(packet_data_refund_t ** pdr);


int transaction_init_done(transaction_t ** tr, packet_head_t * pkt_hdr_ptr, list_t * tr_list);
int transaction_authd(transaction_t ** tr, packet_head_t * pkt_hdr_ptr, list_t * tr_list);
int transaction_ops_done(transaction_t ** tr, packet_head_t * pkt_hdr_ptr, list_t * tr_list);

int packet_from_transaction(transaction_t * tr, packet_head_t ** pkt_hdr, uint32_t auth_code);
int packet_from_transaction_and_send(transaction_t * tr, uint32_t auth_code);
 #endif