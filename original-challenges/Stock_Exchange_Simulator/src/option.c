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
#include "account.h"
#include "option.h"

uint32_t ORDER_ID = 1;

option_holding_t * match_holding(uint32_t acct_id, option_order_t *order){
	for(int i =0; i < MAX_HOLDINGS; i++){
		option_holding_t *h = &(ACCOUNTS[acct_id].holdings[i]);
		int mcp = memcmp(order->symbol, h->symbol, SYM_SIZE);
		if(mcp == 0)
			return h;


	}
	return NULL;
}

option_holding_t *add_holding(uint32_t acct_id, option_order_t *order){

	option_holding_t *n = match_holding(acct_id, order);
	// assume everyone has a bit of every holding
	if(n == NULL)
		_terminate(77);
	// dont rollover just keep it as the max
	if(n->qty != 0xFFFFFFFF)
		n->qty = n->qty + order->qty;
	return n;

}

option_holding_t *dec_holding(uint32_t acct_id, option_order_t *order){

	option_holding_t *n = match_holding(acct_id, order);
	// assume everyone has a bit of every holding
	if(n == NULL)
		_terminate(55);

	if(n->qty > order->qty)
		n->qty = n->qty - order->qty;
	return n;

}

OP_ERR fill_order(uint32_t acct_id, option_order_t *order, orderbook_order_t *matched_order){
	// this also assumes that the order account has the balance
	option_order_t *match = &(matched_order->contract);

	float purchase_price = order->qty * match->price;
	
	// decrement the account balance on buy side
	ACCOUNTS[acct_id].balance = ACCOUNTS[acct_id].balance -  purchase_price;

	ACCOUNTS[matched_order->acct_id].balance = ACCOUNTS[matched_order->acct_id].balance + purchase_price;


	// this is the sell order
	option_holding_t *debit_holding = match_holding(matched_order->acct_id, order);

	if(debit_holding == NULL)
		_terminate(88);
	dec_holding(matched_order->acct_id, order);
	
	
	// this is buy order	
	option_holding_t * credit_holding = match_holding(acct_id, order);
	if(credit_holding == NULL)
		_terminate(88);


	add_holding(acct_id, order);

	if(order->qty > match->qty)
		_terminate(102);

	match->qty = match->qty - order->qty;

	
	if(match->qty == 0){
		match->symbol[0] = 0x00;
		match->price = 0;
		return ORDERFILL;

	}
	if(credit_holding->qty == 0xFFFFFFFF)
		return QTY_OVERFLOW;



	return OK;


}

int match_symbol(option_order_t *l, option_order_t *r){
	return memcmp(l->symbol, r->symbol, SYM_SIZE);
}

float get_current_ask(char * sym){
	float price = 0.0;
	uint32_t low_oid = 0;
	for(int i = 0; i < NUM_ORDERS; i++){
		if(ORDERBOOK[i].direction == SELL){
			int mc = memcmp(ORDERBOOK[i].contract.symbol, sym, SYM_SIZE);
			if(mc == 0 && ORDERBOOK[i].contract.qty > 0){
				if(ORDERBOOK[i].order_id < low_oid || low_oid == 0){
					low_oid = ORDERBOOK[i].order_id;
					price = ORDERBOOK[i].contract.price;
				}
			}
		}

	}

	return price;
}



orderbook_order_t * find_sell_order(option_order_t *order){
	uint32_t low_oid = 0;
	orderbook_order_t * o = NULL;
	for(int i =0; i < NUM_ORDERS; ++i){

		option_order_t *potential = &(ORDERBOOK[i].contract);
		int ms =  1;
		if(potential != NULL && potential->symbol[0] != 0x0){
			ms = match_symbol(potential, order);
		} 
				
		if(potential != NULL && ms == 0 && potential->price <= order->price && potential->qty > 0 && potential->qty >= order->qty){
			if(low_oid == 0){
				low_oid = ORDERBOOK[i].order_id;
				o = &(ORDERBOOK[i]);
				
			}else if(ORDERBOOK[i].order_id < low_oid ){
				low_oid = ORDERBOOK[i].order_id;
				o = &(ORDERBOOK[i]);
			}
		}


	}
	return o;

}

OP_ERR add_to_order_book(option_order_t *o, uint32_t acct_id, OP_TYPE direction){
	
	for(int i = 0; i < NUM_ORDERS; ++i){
		if(ORDERBOOK[i].contract.symbol[0] == 0x0){
			char * obsym = ORDERBOOK[i].contract.symbol;
			memcpy(o->symbol, obsym, SYM_SIZE);
			ORDERBOOK[i].contract.qty = o->qty;
			ORDERBOOK[i].contract.price = o->price;
			ORDERBOOK[i].acct_id = acct_id;
			if(direction != BUY && direction != SELL)
				_terminate(99);
			ORDERBOOK[i].direction = direction;
			ORDERBOOK[i].order_id = ORDER_ID;
			ORDER_ID += 1;
			
			return SELL_ADD;
		}
	}
	return ORDERS_FULL;
}

OP_ERR check_account_balance_can_buy(option_order_t *o, uint32_t acct_id){
	if(acct_id < NUM_ACCOUNTS){
		
		if((o->qty * o->price) < ACCOUNTS[acct_id].balance){
			return OK;
		}
		else{
			return NO_FILL;
		}
	}
	return BAD_ACCT;
}

void generic_resp(packet_t *resp, OP_TYPE ot, uint32_t acct_id){
	resp->rt = RESPONSE;
	resp->ot = ot;
	resp->acct_id = acct_id;

}

size_t gen_order_fill_msg(packet_t *resp, OP_TYPE ot, char * sym, uint32_t qty, uint32_t acct_id){
	generic_resp(resp, ot, acct_id);
	if(ot != BUY && ot != SELL)
		_terminate(99);
	orderfill_t *of = (orderfill_t *) &(resp->op_data);
	memcpy(sym, &(of->symbol), SYM_SIZE);
	of->qty = qty;
	return sizeof(orderfill_t)-sizeof(void *);
}

OP_ERR check_account_holding_in_qty_sell(option_order_t *sell_order, uint32_t acct_id){
	account_record_t *ar = &(ACCOUNTS[acct_id]);
	for(int i = 0; i < MAX_HOLDINGS; i++){
		option_holding_t *h = &(ar->holdings[i]);
		if(memcmp(h->symbol, sell_order->symbol, SYM_SIZE) == OK){
			if(sell_order->qty <= h->qty){
				return OK;
			}
			else {
				return NO_HOLD;
			}
		}
	}
	return NO_MATCH;
}


OP_ERR fill_buy_order(uint32_t acct_id, orderbook_order_t *matched_order, option_order_t *order){
	if(matched_order == NULL){
		return NO_MATCH;
	}
	return fill_order(acct_id, order, matched_order);

}

OP_ERR run_option_transaction(uint32_t acct_id, option_order_t *order, OP_TYPE ot){
	if(ot == BUY){

		OP_ERR e = check_account_balance_can_buy(order, acct_id);
		
		if(e != OK)
			return e;
		// we reject buy orders with no sell order
		orderbook_order_t * matched_order = find_sell_order(order);	
		OP_ERR ofe = fill_buy_order(acct_id, matched_order, order);
		if(ofe != OK)
			return ofe;
		return OK;

	} else if(ot == SELL){
		OP_ERR e = check_account_holding_in_qty_sell(order, acct_id);
		if(e != OK)
			return e;

		return add_to_order_book(order, acct_id, SELL);
	}
	
	return UNK_E;
}
