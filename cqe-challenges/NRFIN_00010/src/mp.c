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

#include "mp.h"

uint32_t next_card_id = FIRST_CARD_ID;
uint32_t next_card_auth_code = FIRST_CARD_AUTH_CODE;
uint32_t next_transaction_id = FIRST_TRANSACTION_ID;

// need function for transaction node comparison in the list.
//  -- should return SUCCESS when node nd contains value, 1 when not.
int transaction_node_contains(node_t * nd, void * key_value) {
	transaction_t * tr = (transaction_t *)nd->data;
	uint32_t * transaction_id = (uint32_t *)key_value;
	if (tr->transaction_id == *transaction_id) {
		return SUCCESS;
	} else {
		return 1;
	}
}

// need function for card node comparison in the list.
//  -- should return SUCCESS when node nd contains value, 1 when not.
int card_node_contains(node_t * nd, void * key_value) {
	card_t * c = (card_t *)nd->data;
	uint32_t * card_id = (uint32_t *)key_value;
	if (c->card_id == *card_id) {
		return SUCCESS;
	} else {
		return 1;
	}
}

// create a new card using the inital amount.
// the card_id starts at FIRST_CARD_ID and increments by 1.
// card_count is the number of cards in the card list.
// success: SUCCESS
// failure: ERRNO_MP_ALLOC
int card_create(card_t ** card, uint32_t card_count, uint32_t initial_amount) {
	ALLOC(sizeof(card_t), 0, (void **)card);
	(*card)->balance = initial_amount;
	(*card)->card_id = next_card_id;
	(*card)->auth_code = next_card_auth_code;
	next_card_id++;
	next_card_auth_code++;
	return SUCCESS;
}

// add the card to the card_list
//  success: SUCCESS
//  failure: ERRNO_MP_LIST_PUSH
int card_add_to_list(card_t * card, list_t * card_list) {
	node_t * nd = node_create((void *)card);
	if(SUCCESS != list_push(card_list, nd, (void *)&(card->card_id))) {return ERRNO_MP_LIST_PUSH;}

	return SUCCESS;
}

// create a new card with the given inital_amount as the balance and add it to the card_list
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_LIST_PUSH
int card_create_and_add_to_list(card_t ** card, list_t * card_list, uint32_t initial_amount) {
	// create card
    RET_ON_FAIL(card_create(card, card_list->count, initial_amount));

    // add card to list
    RET_ON_FAIL(card_add_to_list(*card, card_list));

    return SUCCESS;
}

// find card in card_list having card_id and return ptr to it via card
// success: SUCCESS
// failure: ERRNO_MP_NOT_FOUND if that card_id is not found; in that case card is undefined.
int card_get(card_t ** card, uint32_t card_id, list_t * card_list) {
	node_t * c1 = NULL;
	if(NULL == (c1 = list_find(card_list, &card_id))) {return ERRNO_MP_NOT_FOUND;}
	*card = (card_t *)c1->data;

	return SUCCESS;
}

// determine if card is valid (exists and has matching auth_code)
// valid: SUCCESS
// not valid: ERRNO_MP_INVALID_CARD
int card_is_valid(uint32_t card_id, uint32_t auth_code, list_t * card_list) {
	card_t * card = NULL;
	if(SUCCESS != card_get(&card, card_id, card_list)) {return ERRNO_MP_INVALID_CARD;}
	if(card->auth_code != auth_code) {return ERRNO_MP_INVALID_CARD;}

	return SUCCESS;
}

// subtract amount from the balance of card with id card_id in card_list
// success: SUCCESS
// failure: ERRNO_MP_NOT_FOUND, ERRNO_MP_PURCHASE_ISF
int card_purchase(uint32_t card_id, list_t * card_list, uint32_t amount) {

	int ret = 0;
	// find card
	card_t * card = NULL;
	RET_ON_FAIL(card_get(&card, card_id, card_list));

	// update card balance if sufficient funds
	if(card->balance >= amount) {
		card->balance -= amount;
	} else {
		return ERRNO_MP_PURCHASE_ISF;
	}

	return SUCCESS;
}

// add amount to the balance of card with id card_id in card_list
// success: SUCCESS
// failure: ERRNO_MP_NOT_FOUND, ERRNO_MP_RECHARGE_FULL
int card_recharge(uint32_t card_id, list_t * card_list, uint32_t amount) {

	// find card having card_id
	card_t * card = NULL;
	RET_ON_FAIL(card_get(&card, card_id, card_list));

	// if balance will wrap around, return error.
	if(card->balance + amount >= amount) {
		// update card balance
		card->balance += amount;
	} else {
		return ERRNO_MP_RECHARGE_FULL;
	}

	return SUCCESS;
}

// look up the balance of the card with card_id and write it into balance.
// success: SUCCESS
// failure: ERRNO_MP_NOT_FOUND
int card_get_balance(uint32_t card_id, list_t * card_list, uint32_t * balance) {

	// find card having card_id
	card_t * card = NULL;
	RET_ON_FAIL(card_get(&card, card_id, card_list));

	// return card balance
	*balance = card->balance;

	return SUCCESS;
}

// refund amount from purchase transaction to card in card_list
// success: SUCCESS
// failure: ERRNO_MP_NOT_FOUND, ERRNO_MP_REFUND_FULL
int card_refund(uint32_t card_id, list_t * card_list, transaction_t * tr) {

	// verify card_id matches that used in the transaction
	if(card_id != tr->card_id) {
		RET_ON_FAIL(ERRNO_MP_NOT_FOUND);
	}

	// find card having card_id
	card_t * card = NULL;
	RET_ON_FAIL(card_get(&card, card_id, card_list));

	// get purchase out of transaction
	packet_data_purchase_t * p = (packet_data_purchase_t *)tr->details;

	// if balance will wrap around, return error.
	if(card->balance + p->cost >= p->cost) {
		// add purchase amount to card balance
		card->balance += p->cost;
	} else {
		return ERRNO_MP_REFUND_FULL;
	}	

	return SUCCESS;
}

// create a new transaction using the values from the packet header.
// the transaction_id starts at FIRST_TRANSACTION_ID and increments by 1.
// tr_count is the number of transactions in the transaction list.
// success: SUCCESS, 
// failure: ERRNO_MP_ALLOC
int transaction_create(transaction_t ** tr, uint32_t tr_count, packet_head_t * pkt_hdr_ptr) {
	ALLOC(sizeof(transaction_t), 0, (void **)tr);
	(*tr)->op_code = pkt_hdr_ptr->op_code;
	(*tr)->state = pkt_hdr_ptr->pkt_type;
	(*tr)->card_id = pkt_hdr_ptr->card_id;
	(*tr)->transaction_id = next_transaction_id;
	(*tr)->details = NULL;
	next_transaction_id++;
	return SUCCESS;
}

// add new transaction to the transaction list
// success: SUCCESS, 
// failure: ERRNO_MP_LIST_PUSH
int transaction_add_to_list(transaction_t * tr, list_t * tr_list) {
	node_t * nd = node_create((void *)tr);
	if(SUCCESS != list_push(tr_list, nd, (void *)&(tr->transaction_id))) {return ERRNO_MP_LIST_PUSH;}
	return SUCCESS;
}

// create a new transaction and add it to the transaction_list
// success: SUCCESS, 
// failure: ERRNO_MP_ALLOC, ERRNO_MP_LIST_PUSH
int transaction_create_and_add_to_list(transaction_t ** tr, 
										list_t * tr_list, 
										packet_head_t * pkt_hdr_ptr, 
										uint32_t card_id) {
	RET_ON_FAIL(transaction_create(tr, tr_list->count, pkt_hdr_ptr));

    // update transaction with new card id
    (*tr)->card_id = card_id;

    RET_ON_FAIL(transaction_add_to_list(*tr, tr_list));

    return SUCCESS;
}

// find transaction in tr_list having transaction_id and op_code, and return ptr to it via tr
// success: SUCCESS
// failure: ERRNO_MP_NOT_FOUND if that transaction_id is not found; in that case tr is undefined.
int transaction_get(transaction_t ** tr, uint32_t transaction_id, OP_CODE op_code, list_t * tr_list) {
	node_t * tr1 = NULL;
	if(NULL == (tr1 = list_find(tr_list, (void *)&transaction_id))) {return ERRNO_MP_NOT_FOUND;}
	*tr = (transaction_t *)tr1->data;
	if ((*tr)->op_code != op_code) {return ERRNO_MP_NOT_FOUND;}

	return SUCCESS;
}

// set the transaction state to a new value
void transaction_update_state(transaction_t ** tr, PKT_TYPE state) {
	(*tr)->state = state;
}

// assign the details content to the transaction
void transaction_set_details(transaction_t ** tr, void * pd) {
    (*tr)->details = pd;
}

// find the transaction in tr_list that was a purchase with purchase_id and return it in ref_tr
// success: SUCCESS
// failure: ERRNO_MP_NOT_FOUND
int transaction_get_and_verify_purchase_id(list_t * tr_list, packet_data_refund_t * pdr, transaction_t ** ref_tr) {
	RET_ON_FAIL(transaction_get(ref_tr, pdr->transaction_id, PURCHASE, tr_list));

	// verify purchase_id
	packet_data_purchase_t * p = (packet_data_purchase_t *)(*ref_tr)->details;
	if(p->purchase_id != pdr->purchase_id) {return ERRNO_MP_NOT_FOUND;}

	return SUCCESS;
}

// delete the purchase details from the transaction
// success: SUCCESS
// failure: ERRNO_MP_ALLOC
int transaction_rm_purchase_details(transaction_t ** tr) {

	packet_data_purchase_t * pdp = NULL;
    pdp = (packet_data_purchase_t *)(*tr)->details;

    // get purchase vendor location info to use in dealloc
    uint8_t vendor_loc_sz = pdp->v.vendor_location_sz;
    char * vendor_loc = pdp->v.vendor_location;

    // dealloc purchase_location
    if(SUCCESS != deallocate((void *)vendor_loc, vendor_loc_sz * sizeof(char))) {return ERRNO_MP_ALLOC;}

    // dealloc purchase and vendor details
    if(SUCCESS != deallocate((void *)pdp, sizeof(packet_data_purchase_t))) {return ERRNO_MP_ALLOC;}

    (*tr)->details = NULL;

    return SUCCESS;
}

// remove transaction node from the transaction list and return ptr to it in tr
// success: SUCCESS, 
// failure: ERRNO_MP_LIST_RM
int transaction_rm_from_list(node_t ** tr, list_t * tr_list, uint32_t transaction_id) {
	if(NULL == (*tr = list_remove(tr_list, (void *)&transaction_id))) {return ERRNO_MP_LIST_RM;}
	return SUCCESS;
}

// remove transaction node from transaction list, and dealloc
//  the data pointer to by transaction->details should be reset and deallocated before calling this function
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_LIST_RM
int transaction_destroy(list_t * tr_list, uint32_t transaction_id) {
    //rm transaction node from list and get ptr to transaction node
    node_t * tr_node = NULL;
    RET_ON_FAIL(transaction_rm_from_list(&tr_node, tr_list, transaction_id));
    transaction_t * tr = (transaction_t *)tr_node->data;

    // deallocate the memory used by the transaction
    if(SUCCESS != deallocate((void *)tr, sizeof(transaction_t))) {return ERRNO_MP_ALLOC;}
   
    //destroy node
    RET_ON_FAIL(node_destroy(tr_node));

    return SUCCESS;
}

// for the HISTORY op_code, determine how many transactions will be sent by transaction_list_send_last_n()
//  create a packet_data_history struct and send it with the count value equal to the number of
//  transactions that will be sent.
// success: SUCCESS
// failure: ERRNO_MP_NO_HISTORY
int transaction_get_history_count_and_send(uint32_t card_id, list_t * tr_list, uint32_t max_tr_count) {

	if(0 == tr_list->count) {return ERRNO_MP_NO_HISTORY;}

	int tr_send_count = 0;
	node_t * curr = tr_list->tail->prev;

	while(curr != tr_list->head && (max_tr_count > tr_send_count)) {

		// curr->data is the pointer to the transaction entry;
		// get transaction
		transaction_t * tr = (transaction_t *)curr->data;

		// if this transaction matches card_id, count it
		if(card_id == tr->card_id) {

			// increment tr_send_count
			tr_send_count++;
		}

		// get next node
		curr = curr->prev;
	}

	// create and send the history details
	packet_data_history_t pdh;
	pdh.count = tr_send_count;

	// send history details
	transaction_send_history(&pdh);

	return SUCCESS;
}

// for the HISTORY op_code, start at the end of the transaction_list and send up to tr_count
// transactions that match card_id.
// success: SUCCESS
// failure: ERRNO_MP_NO_HISTORY
int transaction_list_send_last_n(uint32_t card_id, list_t * tr_list, uint32_t tr_count) {

	if(0 == tr_list->count) {return ERRNO_MP_NO_HISTORY;}

	int tr_sent_count = 0;
	node_t * curr = tr_list->tail->prev;

	while(curr != tr_list->head && (tr_count > tr_sent_count)) {

		// curr->data is the pointer to the transaction entry;
		// get transaction
		transaction_t * tr = (transaction_t *)curr->data;

		// if this transaction matches card_id, send transaction
		if(card_id == tr->card_id) {

			// send transaction header except the details pointer.
		    send((char *)tr, sizeof(transaction_t) - sizeof(void *));

			// send transaction details
			transaction_send_details(tr);

			// increment tr_sent_count
			tr_sent_count++;
		}

		// get next node
		curr = curr->prev;
	}

	return SUCCESS;
}

// send transaction details (call func based on op_code).
// success: SUCCESS
// failure: ERRNO_MP_INVALID_OPCODE
int transaction_send_details(transaction_t * tr) {

#ifdef PATCHED
	// VULNERABLE CODE: the transaction does not have details in the AUTH phase
	if (tr->state == AUTH) {
		return SUCCESS;
	}
#endif
	// get op_code to determine type of transaction
	switch(tr->op_code) {
		case PURCHASE :
			transaction_send_purchase(tr->details);
			break;
		case RECHARGE :
			transaction_send_recharge(tr->details);
			break;
		case BALANCE :
			transaction_send_balance(tr->details);
			break;
		case HISTORY :
			transaction_send_history(tr->details);
			break;
		case ISSUE :
			transaction_send_issue(tr->details);
			break;
		case REFUND :
			transaction_send_refund(tr->details);
			break;
		default :
			return ERRNO_MP_INVALID_OPCODE;
	}
	return SUCCESS;
}

// send purchase details
void transaction_send_purchase(void * details) {
	packet_data_purchase_t * pdp = (packet_data_purchase_t *)details;
    vendor_t * v = &(pdp->v);

    // sanity check to ensure cost wasn't zero
    if(pdp->cost > 0) { 
		// send first 2 fields in purchase + fixed vendor fields (not location)
	    send((char *)pdp, 14);
	    // send vendor info
	    transaction_send_vendor_loc(v);
    }
}

// send recharge details
void transaction_send_recharge(void * details) {
	packet_data_recharge_t * pdr = (packet_data_recharge_t *)details;
    vendor_t * v = &(pdr->v);

    // sanity check to ensure amount wasn't zero
    if(pdr->amount > 0) {
		// send first field in recharge + fixed vendor fields (not location)
	    send((char *)pdr, 10);
	    // send vendor info
	    transaction_send_vendor_loc(v);
	}
}

// send balance details
void transaction_send_balance(void * details) {
	packet_data_balance_t * pdb = (packet_data_balance_t *)details;
    send((char *)pdb, sizeof(packet_data_balance_t));
}

// send history details
void transaction_send_history(void * details) {
	packet_data_history_t * pdh = (packet_data_history_t *)details;
    send((char *)pdh, sizeof(packet_data_history_t));
}

// send issue details
void transaction_send_issue(void * details) {
	packet_data_issue_t * pdi = (packet_data_issue_t *)details;
    send((char *)pdi, sizeof(packet_data_issue_t));
}

// send refund details
void transaction_send_refund(void * details) {
	packet_data_refund_t * pdr = (packet_data_refund_t *)details;
    send((char *)pdr, sizeof(packet_data_refund_t));
}

// send vendor location details
void transaction_send_vendor_loc(vendor_t * v) {
    send((char *)v->vendor_location, v->vendor_location_sz);
}

// recv issue details
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_RECV
int transaction_recv_issue(packet_data_issue_t ** pdi) {
    // create memory for issue data
    ALLOC(sizeof(packet_data_issue_t), 0, (void **)pdi);
    if(sizeof(packet_data_issue_t) != recv_all((char *)*pdi, sizeof(packet_data_issue_t))) {return ERRNO_MP_RECV;}

    return SUCCESS;
}

// recv purchase details
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_RECV
int transaction_recv_purchase(packet_data_purchase_t ** pdp) {
    // create memory for purchase data + vendor
    ALLOC(sizeof(packet_data_purchase_t), 0, (void **)pdp);
    // read purchase data and vendor data (except vendor_location)
    if(14 != recv_all((char *)*pdp, 14)) {return ERRNO_MP_RECV;}

    uint32_t vls = (*pdp)->v.vendor_location_sz;
    if(vls == 0) {return ERRNO_MP_RECV;}

    // create memory for vendor_location char array
    ALLOC(vls, 0, (void **)&((*pdp)->v.vendor_location));
    // read vendor_location (size is in previous read)
    if(vls != recv_all((char *)(*pdp)->v.vendor_location, vls)) {return ERRNO_MP_RECV;}

    return SUCCESS;
}

// recv recharge details
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_RECV
int transaction_recv_recharge(packet_data_recharge_t ** pdr) {
    // create memory for recharge data + vendor
    ALLOC(sizeof(packet_data_recharge_t), 0, (void **)pdr);
    // read recharge data and vendor data (except vendor_location)
    if(10 != recv_all((char *)*pdr, 10)) {return ERRNO_MP_RECV;}

    uint32_t vls = (*pdr)->v.vendor_location_sz;
    if(vls == 0) {return ERRNO_MP_RECV;}

    // create memory for vendor_location char array
    ALLOC(vls, 0, (void **)&((*pdr)->v.vendor_location));
    // read vendor_location (size is in previous read)
    if(vls != recv_all((char *)(*pdr)->v.vendor_location, vls)) {return ERRNO_MP_RECV;}

    return SUCCESS;
}

// Allocate memory to store balance details
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_RECV
int transaction_recv_balance(packet_data_balance_t ** pdb) {
    // create memory for balance data
    ALLOC(sizeof(packet_data_balance_t), 0, (void **)pdb);

    return SUCCESS;
}

// recv history details
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_RECV
int transaction_recv_history(packet_data_history_t ** pdh) {
    // create memory for history data
    ALLOC(sizeof(packet_data_history_t), 0, (void **)pdh);
    if(sizeof(packet_data_history_t) != recv_all((char *)*pdh, sizeof(packet_data_history_t))) {return ERRNO_MP_RECV;}

    return SUCCESS;
}

// recv refund details
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_RECV
int transaction_recv_refund(packet_data_refund_t ** pdr) {
    // create memory for refund data
    ALLOC(sizeof(packet_data_refund_t), 0, (void **)pdr);
    if(sizeof(packet_data_refund_t) != recv_all((char *)*pdr, sizeof(packet_data_refund_t))) {return ERRNO_MP_RECV;}

    return SUCCESS;
}


// check the given transaction_id to verify there is an assocated transaction in the INIT state
//  having the same op_code
// return associated transaction via tr
// success: SUCCESS, 
// failure: ERRNO_MP_NOT_FOUND, ERRNO_MP_INVALID_CARD, ERRNO_MP_NO_INIT
int transaction_init_done(transaction_t ** tr, packet_head_t * pkt_hdr_ptr, list_t * tr_list) {
	RET_ON_FAIL(transaction_get(tr, pkt_hdr_ptr->transaction_id, pkt_hdr_ptr->op_code, tr_list));
	if(pkt_hdr_ptr->card_id != (*tr)->card_id) {return ERRNO_MP_INVALID_CARD;}
	if((*tr)->state != INIT) {return ERRNO_MP_NO_INIT;}

	return SUCCESS;
}

// check the given transaction_id to verify there is an assocated transaction in the AUTH state
//  having the same op_code
// return associated transaction via tr
// success: SUCCESS
// failure: ERRNO_MP_NOT_FOUND, ERRNO_MP_INVALID_CARD, ERRNO_MP_NO_AUTH
int transaction_authd(transaction_t ** tr, packet_head_t * pkt_hdr_ptr, list_t * tr_list) {
	RET_ON_FAIL(transaction_get(tr, pkt_hdr_ptr->transaction_id, pkt_hdr_ptr->op_code, tr_list));
	if(pkt_hdr_ptr->card_id != (*tr)->card_id) {return ERRNO_MP_INVALID_CARD;}
	if((*tr)->state != AUTH) {return ERRNO_MP_NO_AUTH;}

	return SUCCESS;
}

// check the given transaction id to verify there is an associated transaction in the OPS state
//  having the same op_code
// return associated transaction via tr
// success: SUCCESS
// failure: ERRNO_MP_NOT_FOUND, ERRNO_MP_INVALID_CARD, ERRNO_MP_NO_OPS
int transaction_ops_done(transaction_t ** tr, packet_head_t * pkt_hdr_ptr, list_t * tr_list) {
	RET_ON_FAIL(transaction_get(tr, pkt_hdr_ptr->transaction_id, pkt_hdr_ptr->op_code, tr_list));
	if(pkt_hdr_ptr->card_id != (*tr)->card_id) {return ERRNO_MP_INVALID_CARD;}
	if((*tr)->state != OPS) {return ERRNO_MP_NO_OPS;}

	return SUCCESS;
}

// create new packet header with values from transaction.
// success: SUCCESS
// failure: ERRNO_MP_ALLOC
int packet_from_transaction(transaction_t * tr, packet_head_t ** pkt_hdr, uint32_t auth_code) {
	ALLOC(sizeof(packet_head_t), 0, (void **)pkt_hdr);
	(*pkt_hdr)->card_id = tr->card_id;
	(*pkt_hdr)->auth_code = auth_code;
	(*pkt_hdr)->pkt_type = tr->state;
	(*pkt_hdr)->op_code = tr->op_code;
	(*pkt_hdr)->status = tr->status;
	(*pkt_hdr)->transaction_id = tr->transaction_id;
	return SUCCESS;
}

// create new packet header with values from transaction.
// and send packet header
// success: SUCCESS
// failure: ERRNO_MP_ALLOC
int packet_from_transaction_and_send(transaction_t * tr, uint32_t auth_code) {
    packet_head_t * new_pkt_header = NULL;
    RET_ON_FAIL(packet_from_transaction(tr, &new_pkt_header, auth_code));

    // send packet_header to client
    send((char *)new_pkt_header, sizeof(packet_head_t));

    // free memory for new_pkt_header.
    if(SUCCESS != deallocate((void *)new_pkt_header, sizeof(packet_head_t))) {return ERRNO_MP_ALLOC;}

    return SUCCESS;
}
