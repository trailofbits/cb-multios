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


#include "cgc_account.h"
#include "cgc_ll.h"
#include "cgc_sheap.h"



// this should stay encapsulated ...
accounts_listing_t *ACCOUNTS;

alloc_node_t *last;

int rev_it; 
txn_entry_t **txn_stack;
int cgc_txn_stack_sz = 0;
int cgc_txn_it_ct = 0;

txn_entry_t * cgc_transaction_iterator(account_entry_t *ae){
	
	// iterator start...
	if(ae != NULL){
		alloc_node_t * h = cgc_get_head(ae->txn_log);
		
		last = h;
		return (txn_entry_t * ) h->contents;
	}else if(ae == NULL && last != NULL){
		last = last->next;
		if(last == NULL)
			return NULL;

		return (txn_entry_t *) last->contents;
	}

	return NULL;

}



void cgc_lazy_account_init(){
	if(ACCOUNTS == NULL)
		cgc_init_account_register();
}

alloc_node_t * cgc_alloc_txn_head(){

	return (alloc_node_t *) cgc_malloc(sizeof(alloc_node_t));
}

cgc_size_t cgc_vendor_calc(vendor_t *v){
	return v->vendor_location_sz - sizeof(char *);
}
cgc_size_t cgc_packet_sz_by_op_code(uint32_t op_code, uint32_t is_client){
		switch(op_code){

		case PURCHASE:
			if(is_client){
				// cant do sizeof due to compiler padding mismatch with poll generator
				return 14;
			}
			return 0;

		case HISTORY:
			// this is both ways...
			return sizeof(packet_data_history_t);
			
		case RECHARGE:
			if(is_client){
				
				return 10;	
			}else{
				return 0;
			}
			
		case REFUND:
			if(is_client){
				return sizeof(packet_data_refund_t);	
			}
			return 0;

		case ISSUE:
			if(is_client){
				return sizeof(packet_data_issue_t);	
			}
			return 0;
			

		case BALANCE:
			if(is_client == 1)
				return 0;
			return sizeof(packet_data_balance_t);
		}
	return 0;
}

cgc_size_t cgc_get_log_data_sz(uint32_t op_code, void *txn_data){
	packet_data_recharge_t *d = NULL;
	packet_data_purchase_t * pp = NULL;
	switch(op_code){

		case PURCHASE:
			pp = (packet_data_purchase_t *) txn_data;
			return cgc_packet_sz_by_op_code(op_code, 1)+cgc_vendor_calc(&(pp->v));


		case HISTORY:
			return sizeof(packet_data_history_t);
		case RECHARGE:
			d = (packet_data_recharge_t *) txn_data;
			
			return cgc_packet_sz_by_op_code(op_code, 1)+cgc_vendor_calc(&(d->v));	
			
		case REFUND:
			return sizeof(packet_data_refund_t);	

		case ISSUE:
			return sizeof(packet_data_issue_t);	
			

		case BALANCE:
			return sizeof(packet_data_balance_t);
	}
	return 0;
}

cgc_size_t cgc_get_ops_data_sz(packet_head_t * ph, void *txn_data, uint32_t is_client){
	return cgc_packet_sz_by_op_code(ph->op_code, is_client);
}



cgc_size_t cgc_get_size_of_data_for_pkt(packet_head_t * ph, void *txn_data, uint32_t is_client){
	if(ph->status != OK){
		packet_data_error_t *pde = txn_data;
		return pde->length+sizeof(packet_data_error_t)-4;
	}

	switch(ph->pkt_type){
		case AUTH:
		 	return 0;
		case FIN:
			return 0;

		case INIT:
			if(ph->op_code  ==  ISSUE && ph->transaction_id == 0)
				return sizeof(packet_data_issue_t);
			return 0;

		case OPS:
			return cgc_get_ops_data_sz(ph, txn_data, is_client);

		
	}


	return 0;
}

cgc_size_t cgc_get_size_of_data_for_pkt_head_only(packet_head_t *ph, uint32_t is_client){
	return cgc_get_size_of_data_for_pkt(ph, ph+1, is_client);
	
}



txn_entry_t * cgc_get_transaction(account_entry_t *ae, uint32_t txn_id){
#ifdef PATCHED
	if(ae == NULL)
		return NULL;
#endif

	alloc_node_t * an = cgc_get_head(ae->txn_log);


	while(an != NULL){
		txn_entry_t *te = (txn_entry_t *) an->contents;
		if(te->transaction_id == txn_id)
			return te;
		an = an->next;
	}
	cgc_ERRNO = ERRNO_MP_NOT_FOUND;
	return NULL;
}

int cgc_finalize_transaction(txn_entry_t * te){
#ifdef PATCHED
	te->is_open = TXN_CLOSED;
	if(te->is_open != 0)
		return ERRNO_MP_NOT_FOUND;
#endif

#ifndef PATCHED
	te->is_open-= 1;

	if(te->is_open > 1){
		cgc_ERRNO = 255;
		return ERRNO_MP_NOT_FOUND;
	}
#endif

	te->state = FIN;

	return 0;
}

txn_entry_t * cgc_open_txn(account_entry_t * ae, packet_head_t * ph){
	alloc_node_t * an = cgc_alloc_txn_head();
	


	an->contents = cgc_malloc(sizeof(txn_entry_t));
	txn_entry_t *le = an->contents;
	le->is_open = TXN_OPEN;
	le->transaction_id = cgc_register_transaction();
	ph->transaction_id = le->transaction_id;
	le->p = cgc_malloc(sizeof(packet_head_t));
	if(le->p == NULL)
		return NULL;
	cgc_memcpy(le->p, ph, sizeof(packet_head_t));
	
	cgc_add_node(ae->txn_log, an);
	return le;

}


txn_entry_t * cgc_remove_transaction_log_entry(account_entry_t * ae, txn_entry_t * ti){
	// this is for refund

	alloc_node_t * an = cgc_get_head(ae->txn_log);
	while(an != NULL){
		txn_entry_t *te = (txn_entry_t *) an->contents;

		if(te->transaction_id == ti->transaction_id){
			// begin removal
			if(te->p != NULL)
				cgc_free(te->p);
			if(te->data_sz != 0)
				cgc_free(te->data);

			cgc_free(te);
			cgc_remove_node(ae->txn_log, an);

			return te;
		}
		an = an->next;
	}
	cgc_ERRNO = ERRNO_MP_NOT_FOUND;
	return NULL;
}


txn_entry_t * cgc_add_transaction_log_entry(account_entry_t * ae,  pack_and_data_t *pad){
	// we parse packet header here, again, and dump the whole transaction log into the linked list node

	packet_head_t *ph = pad->ph;
	void *txn_data = pad->data;
	txn_entry_t *le = cgc_get_transaction(ae, ph->transaction_id);
	if(le == NULL){

		return NULL;
	}


	if(le->p == NULL)
		le->p = (packet_head_t *) cgc_malloc(sizeof(packet_head_t));
	
	if(le->p == NULL)
		return NULL;
	

	



	// copy in original packet header and packet data ...
	cgc_memcpy(le->p, (void *) ph, sizeof(packet_head_t));

	cgc_size_t data_sz = pad->pay_data_l;
	le->data_sz = data_sz;


	if(data_sz != 0){
		le->data = cgc_malloc(data_sz);
		if(txn_data == NULL)
			return NULL;
		cgc_memcpy(le->data, txn_data, data_sz);	
	}
	
	return le;
}

alloc_head_t * cgc_init_ll_heap(){
    alloc_head_t * h;
    h = (alloc_head_t *) cgc_malloc(sizeof(alloc_head_t));
    if(h == NULL)
        return NULL;
    h->n_nodes = 0;
    h->n = NULL;
    return h;
}

int cgc_create_account(uint32_t card_id,	uint32_t auth_code, packet_data_balance_t *b){
	// assume these are all verified in caller
	uint32_t initial_balance = b->balance;
	// accounts should be created by init messages so card id and auth code should be clean
	cgc_lazy_account_init();
	alloc_node_t *an = cgc_malloc(sizeof(alloc_node_t));
	account_entry_t * ae = cgc_malloc(sizeof(account_entry_t));

	if(ae == NULL || an == NULL)
		return ERRNO_MP_ALLOC;

	ae->card_id = card_id;
	ae->auth_code = auth_code;
	ae->initial_balance = initial_balance;
	ae->balance = initial_balance;

	

	ae->txn_log = cgc_init_ll_heap();
	if(ae->txn_log == NULL)
		return ERRNO_MP_ALLOC;

	an->contents = (void *) ae;

	int add_ret = cgc_add_node(ACCOUNTS->accounts, an);
	if(add_ret != OPOKAY)
		return add_ret;


	

	return OK;
}


account_entry_t * cgc_get_account(uint32_t card_id, uint32_t auth_code){
	cgc_lazy_account_init();
	accounts_listing_t *accts = ACCOUNTS;
	alloc_node_t *acct_node = cgc_get_head(accts->accounts);
	if(acct_node == NULL)
		return NULL;

	account_entry_t *al =  (account_entry_t *) acct_node->contents;
	while(al != NULL){


		if(al->card_id == card_id){
			if(al->auth_code == auth_code){

				return al;
			}else{
				cgc_ERRNO = ERRNO_MP_NO_AUTH;
				return NULL;
			}
		}

		acct_node = acct_node->next;
		if(acct_node == NULL)
			break;

		al = acct_node->contents;
	}
	cgc_ERRNO = ERRNO_MP_NOT_FOUND;

	return NULL;

}




void cgc_init_account_register(){


	accounts_listing_t *a = cgc_malloc(sizeof(accounts_listing_t));
	a->accounts = cgc_init_ll();
	ACCOUNTS = a;
}