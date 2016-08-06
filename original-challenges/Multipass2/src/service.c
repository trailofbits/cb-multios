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
#include "service.h"
#include "mp.h"

int issue_card(packet_head_t * pkt_hdr_ptr);
int make_purchase(transaction_t ** tr, packet_head_t * pkt_hdr_ptr);
int recharge_card(transaction_t ** tr, packet_head_t * pkt_hdr_ptr);
int get_card_balance(transaction_t ** tr, packet_head_t * pkt_hdr_ptr);
int get_transaction_history(transaction_t ** tr, packet_head_t * pkt_hdr_ptr);
int refund_purchase(transaction_t ** tr, packet_head_t * pkt_hdr_ptr);

int process_op_code(transaction_t ** tr, packet_head_t * pkt_hdr_ptr);
int process_fin(transaction_t ** tr, packet_head_t * pkt_hdr_ptr);

void send_error(packet_head_t * pkt_hdr_ptr, uint8_t err_status, char * err_msg);
void send_error_pkt(packet_head_t * pkt_hdr_ptr, uint8_t err_status);

int auth_new_transaction(packet_head_t * pkt_hdr_ptr);

int init_completed(transaction_t ** tr, packet_head_t * pkt_hdr_ptr);
int auth_completed(transaction_t ** tr, packet_head_t * pkt_hdr_ptr);
int ops_completed(transaction_t ** tr, packet_head_t * pkt_hdr_ptr);

int dispatch_packet(packet_head_t * pkt_hdr_ptr);

list_t * transaction_list = NULL;
list_t * card_list = NULL;

// process the ISSUE op_code
// success: SUCCESS
// failure: ERRNO_MP_RECV, ERRNO_MP_LIST_PUSH, ERRNO_MP_ALLOC
int issue_card(packet_head_t * pkt_hdr_ptr) {
    // read card amount
    packet_data_issue_t * pdi = NULL;

    RET_ON_FAIL(transaction_recv_issue(&pdi));

    // create card and add it to the card_list
    card_t * card = NULL;
    RET_ON_FAIL(card_create_and_add_to_list(&card, card_list, pdi->amount));

    // create transaction and add it to the transaction_list
    transaction_t * tr = NULL;
    RET_ON_FAIL(transaction_create_and_add_to_list(&tr, transaction_list, pkt_hdr_ptr, card->card_id));
 
    // assign issue details to transaction
    transaction_set_details(&tr, (void *)pdi);

    // create outgoing packet header and send it; use values from transaction
    RET_ON_FAIL(packet_from_transaction_and_send(tr, card->auth_code));

    return SUCCESS;
}

// process the PURCHASE op_code and log results in tr
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_RECV, ERRNO_MP_NOT_FOUND, ERRNO_MP_PURCHASE_ISF
int make_purchase(transaction_t ** tr, packet_head_t * pkt_hdr_ptr) {

    packet_data_purchase_t * pdp = NULL;

    RET_ON_FAIL(transaction_recv_purchase(&pdp));

    // assign the purchase details to the transaction.
    transaction_set_details(tr, (void *)pdp);

    // set transaction state to OPS
    transaction_update_state(tr, OPS);

    // subtract cost from balance on card
    RET_ON_FAIL(card_purchase(pkt_hdr_ptr->card_id, card_list, pdp->cost));

    // create outgoing packet header and send it; use values from transaction
    RET_ON_FAIL(packet_from_transaction_and_send(*tr, pkt_hdr_ptr->auth_code));

    return SUCCESS;
}

// process the RECHARGE op_code and log results in tr
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_RECV, ERRNO_MP_NOT_FOUND, ERRNO_MP_RECHARGE_FULL
int recharge_card(transaction_t ** tr, packet_head_t * pkt_hdr_ptr) {

    packet_data_recharge_t * pdr = NULL;

    RET_ON_FAIL(transaction_recv_recharge(&pdr));

    // assign recharge details to the transaction
    transaction_set_details(tr, (void *)pdr);

    // set transaction state to OPS
    transaction_update_state(tr, OPS);

    // update card with new balance
    RET_ON_FAIL(card_recharge(pkt_hdr_ptr->card_id, card_list, pdr->amount));

    // create outgoing packet header and send it; use values from transaction
    RET_ON_FAIL(packet_from_transaction_and_send(*tr, pkt_hdr_ptr->auth_code));

    return SUCCESS;
}

// process the BALANCE op_code and log results in tr
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_RECV, ERRNO_MP_NOT_FOUND
int get_card_balance(transaction_t ** tr, packet_head_t * pkt_hdr_ptr) {

    packet_data_balance_t * pdb = NULL;

    // alloc a balance struct pointed to by pdb.
    RET_ON_FAIL(transaction_recv_balance(&pdb));

    // assign balance details to the transaction
    transaction_set_details(tr, (void *)pdb);

    // set transaction state to OPS
    transaction_update_state(tr, OPS);

    RET_ON_FAIL(card_get_balance(pkt_hdr_ptr->card_id, card_list, &(pdb->balance)));

    // create outgoing packet header and send it; use values from transaction
    RET_ON_FAIL(packet_from_transaction_and_send(*tr, pkt_hdr_ptr->auth_code));

    // send packet_data to client
    transaction_send_balance((void *)pdb);

    // create 
    return SUCCESS;
}

// process the HISTORY op_code and log results in tr
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_RECV, ERRNO_MP_NOT_FOUND, ERRNO_MP_NO_HISTORY
int get_transaction_history(transaction_t ** tr, packet_head_t * pkt_hdr_ptr) {

    packet_data_history_t * pdh = NULL;

    RET_ON_FAIL(transaction_recv_history(&pdh));

    // assign history details to the transaction
    transaction_set_details(tr, (void *)pdh);

    // set transaction state to OPS
    transaction_update_state(tr, OPS);

    // create outgoing packet header and send it; use values from transaction
    RET_ON_FAIL(packet_from_transaction_and_send(*tr, pkt_hdr_ptr->auth_code));

    // send a History Data blob with count set to the number of transactions
    //  that will be sent.
    RET_ON_FAIL(transaction_get_history_count_and_send(pkt_hdr_ptr->card_id, transaction_list, pdh->count));
    
    // send each transaction that matches the card_id in this pkt_hdr, up to pdh->count transactions.
    // start at the end of the transaction_list and work backwards
    RET_ON_FAIL(transaction_list_send_last_n(pkt_hdr_ptr->card_id, transaction_list, pdh->count));

    return SUCCESS;
}

// process the REFUND op_code and log results in tr
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_RECV, ERRNO_MP_NOT_FOUND, ERRNO_MP_DEALLOC, ERRNO_MP_REFUND_FULL
int refund_purchase(transaction_t ** tr, packet_head_t * pkt_hdr_ptr) {

    packet_data_refund_t * pdr = NULL;

    RET_ON_FAIL(transaction_recv_refund(&pdr));

    // assign refund details to the transaction
    transaction_set_details(tr, (void *)pdr);

    // set transaction state to OPS
    transaction_update_state(tr, OPS);

// THIS IS THE VULNERABLE CODE

//get transaction node from list and get ptr to transaction (node->data)
//verify it matches the purchase_id
//get purchase amount from transaction
//refund purchase amount to card
//rm purchase details from transaction and dealloc details (does not set tr->details to NULL)

// proper way (PATCHED) -- do here
// vuln way (NOT PATCHED) - do in process_fin())
//rm transaction node from list and get ptr to transaction node
//set transaction details to NULL
//rm transaction data from node and dealloc and set data to NULL
//destroy node

    // process refund
    transaction_t * ref_tr = NULL;
    // get transaction with pdr->transaction_id and verify it matches pdr->purchase_id
    RET_ON_FAIL(transaction_get_and_verify_purchase_id(transaction_list, pdr, &ref_tr));

    // refund amount to card balance
    RET_ON_FAIL(card_refund(pkt_hdr_ptr->card_id, card_list, ref_tr));

    // delete/dealloc transaction details from the transaction node having pdr->purchase_id
    RET_ON_FAIL(transaction_rm_purchase_details(&ref_tr));

#ifdef PATCHED
    // call transaction_destroy() in refund_purchase()
    RET_ON_FAIL(transaction_destroy(transaction_list, pdr->transaction_id));

#else
    // call transaction_destroy() in process_fin()
#endif

    // create outgoing packet header and send it; use values from this transaction (not the one being removed)
    RET_ON_FAIL(packet_from_transaction_and_send(*tr, pkt_hdr_ptr->auth_code));

    return SUCCESS;
}

// Do the operations. Dispatch the processing based on op_code
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_RECV, ERRNO_MP_NOT_FOUND, 
//          ERRNO_MP_PURCHASE_ISF, ERRNO_MP_RECHARGE_FULL, ERRNO_MP_REFUND_FULL
int process_op_code(transaction_t ** tr, packet_head_t * pkt_hdr_ptr) {
    int ret = SUCCESS;

    switch(pkt_hdr_ptr->op_code) {
        case PURCHASE :
            ret = make_purchase(tr, pkt_hdr_ptr);
            break;
        case RECHARGE :
            ret = recharge_card(tr, pkt_hdr_ptr);
            break;
        case BALANCE :
            ret = get_card_balance(tr, pkt_hdr_ptr);
            break;
        case HISTORY :
            ret = get_transaction_history(tr, pkt_hdr_ptr);
            break;
        case REFUND :
            ret = refund_purchase(tr, pkt_hdr_ptr);
            break;
        default :
            ret = ERRNO_MP_INVALID_OPCODE;
    }

    return ret;
}

// process FIN packets
// success: SUCCESS
// failure: ERRNO_MP_ALLOC, ERRNO_MP_DEALLOC
int process_fin(transaction_t ** tr, packet_head_t * pkt_hdr_ptr) {
    int ret = SUCCESS;

    switch(pkt_hdr_ptr->op_code) {
        case REFUND :
#ifdef PATCHED
            // call transaction_destroy() in refund_purchase()
#else
        {
            // call transaction_destroy() in process_fin()
            packet_data_refund_t * pdr = (packet_data_refund_t *)(*tr)->details;

            RET_ON_FAIL(transaction_destroy(transaction_list, pdr->transaction_id));
        }
#endif    

        case ISSUE:
        case PURCHASE :
        case RECHARGE :
        case BALANCE :
        case HISTORY :
            // mark transaction state as FIN
            transaction_update_state(tr, FIN);

            // create outgoing packet header and send it; use values from transaction
            RET_ON_FAIL(packet_from_transaction_and_send(*tr, pkt_hdr_ptr->auth_code));
            break;
        default :
            ret = ERRNO_MP_INVALID_OPCODE;
    }

    return ret;
}

// send a header packet and a follow-on packet data error
void send_error(packet_head_t * pkt_hdr_ptr, uint8_t err_status, char * err_msg) {

    // re-use packet header, but set error condition
    pkt_hdr_ptr->status = err_status;
    // send header
    send((char *)pkt_hdr_ptr, sizeof(packet_head_t));

    // create packet_data_error_t
    packet_data_error_t pkt_err = { 0 };

    // define msg length and msg
    if (err_msg == NULL) {
        err_msg = UNK_ERROR_MSG;
    }
    pkt_err.msg = err_msg;

    pkt_err.length = strlen(err_msg);

// typedef struct packet_data_error {
//     uint32_t length;
//     char * msg;
// } packet_data_error_t;

    // send err msg length
    send((char *)&pkt_err, sizeof(uint32_t));
    // send err msg
    send((char *)pkt_err.msg, pkt_err.length);
}

// dispatch correct error packets based on err status.
void send_error_pkt(packet_head_t * pkt_hdr_ptr, uint8_t err_status) {
    switch(err_status) {
        case ERRNO_MP_LIST_PUSH : // Failed to add node to list
            send_error(pkt_hdr_ptr, err_status, LIST_PUSH_MSG);
            break;
        case ERRNO_MP_LIST_RM : // Failed to rm node from list
            send_error(pkt_hdr_ptr, err_status, LIST_RM_MSG);
            break;
        case ERRNO_MP_ALLOC :         // Failed to allocate memory
            send_error(pkt_hdr_ptr, err_status, ALLOC_MSG);
            break;
        case ERRNO_MP_DEALLOC :         // Failed to deallocate memory
            send_error(pkt_hdr_ptr, err_status, DEALLOC_MSG);
            break;
        case ERRNO_MP_PURCHASE_ISF :      // Insufficient Funds
            send_error(pkt_hdr_ptr, err_status, PURCHASE_ISF_MSG);
            break;
        case ERRNO_MP_RECHARGE_FULL : // Recharge would case card balance to wrap
            send_error(pkt_hdr_ptr, err_status, RECHARGE_FULL_MSG);
            break;
        case ERRNO_MP_REFUND_FULL : // Recharge would case card balance to wrap
            send_error(pkt_hdr_ptr, err_status, REFUND_FULL_MSG);
            break;
        case ERRNO_MP_NO_HISTORY :       // No matching transaction history in transaction list.
            send_error(pkt_hdr_ptr, err_status, NO_HISTORY_MSG);
            break;
        case ERRNO_MP_INVALID_OPCODE :    // Invalid OP_code
            send_error(pkt_hdr_ptr, err_status, INVALID_OPCODE_MSG);
            break;
        case ERRNO_MP_INVALID_P_TYPE :    // Invalid Packet Type
            send_error(pkt_hdr_ptr, err_status, INVALID_PKT_TYPE_MSG);
            break;
        case ERRNO_MP_INVALID_V_TYPE :    // Invalid Vendor Type
            send_error(pkt_hdr_ptr, err_status, INVALID_V_TYPE_MSG);
            break;
        case ERRNO_MP_NO_AUTH :       // Transaction did not complete AUTH step
            send_error(pkt_hdr_ptr, err_status, NO_AUTH_MSG);
            break;
        case ERRNO_MP_NO_INIT :       // Transaction did not complete INIT step
            send_error(pkt_hdr_ptr, err_status, NO_INIT_MSG);
            break;
        case ERRNO_MP_NO_OPS :        // Transaction did not complete OPS step
            send_error(pkt_hdr_ptr, err_status, NO_OPS_MSG);
            break;
        case ERRNO_MP_NOT_FOUND :     // When the card or transaction is not in the list
            send_error(pkt_hdr_ptr, err_status, NOT_FOUND_MSG);
            break;
        case ERRNO_MP_INVALID_CARD :  // Card does not exist or is invalid
            send_error(pkt_hdr_ptr, err_status, INVALID_CARD_MSG);
            break;
        case ERRNO_MP_RECV :  // Card does not exist or is invalid
            send_error(pkt_hdr_ptr, err_status, RECV_FAIL_MSG);
            break;
        default : // unknown error
            send_error(pkt_hdr_ptr, err_status, UNK_ERROR_MSG);
    }
}

// all OP_CODE's except ISSUE have to start the transaction with an AUTH
// verify card_id/auth_code are valid, and create a new transaction
// send back header with new transaction_id
// success: SUCCESS
// failure: ERRNO_MP_INVALID_CARD, ERRNO_MP_ALLOC, ERRNO_MP_LIST_PUSH
int auth_new_transaction(packet_head_t * pkt_hdr_ptr) {
    // verify card exists in card_list with given card_id and auth_code
    RET_ON_FAIL(card_is_valid(pkt_hdr_ptr->card_id, pkt_hdr_ptr->auth_code, card_list));

    // create new transaction and add it to the transaction_list
    transaction_t * tr = NULL;
    RET_ON_FAIL(transaction_create_and_add_to_list(&tr, transaction_list, pkt_hdr_ptr, pkt_hdr_ptr->card_id));
 
    // create outgoing packet header and send it; use values from transaction
    RET_ON_FAIL(packet_from_transaction_and_send(tr, pkt_hdr_ptr->auth_code));

    return SUCCESS;
}

// this only applies to the ISSUE op_code
// validate the card and transaction ID, ensure this transaction is in the INIT state
// success: SUCCESS
// failure: ERRNO_MP_NOT_FOUND, ERRNO_MP_INVALID_CARD, ERRNO_MP_NO_INIT
int init_completed(transaction_t ** tr, packet_head_t * pkt_hdr_ptr) {
    // verify card exists in card_list with given card_id and auth_code
    RET_ON_FAIL(card_is_valid(pkt_hdr_ptr->card_id, pkt_hdr_ptr->auth_code, card_list));
    // verify transaction with this transaction ID is in the AUTH state (it completed AUTH)
    RET_ON_FAIL(transaction_init_done(tr, pkt_hdr_ptr, transaction_list));

    return SUCCESS;
}

// validate the card and transaction ID, ensure this transaction is in the AUTH state
// success: SUCCESS
// failure: ERRNO_MP_NOT_FOUND, ERRNO_MP_INVALID_CARD, ERRNO_MP_NO_AUTH
int auth_completed(transaction_t ** tr, packet_head_t * pkt_hdr_ptr) {
    // verify card exists in card_list with given card_id and auth_code
    RET_ON_FAIL(card_is_valid(pkt_hdr_ptr->card_id, pkt_hdr_ptr->auth_code, card_list));
    // verify transaction with this transaction ID is in the AUTH state (it completed AUTH)
    RET_ON_FAIL(transaction_authd(tr, pkt_hdr_ptr, transaction_list));

    return SUCCESS;
}

// validate the card and transaction ID, ensure this transaction is in the OPS state
// success: SUCCESS
// failure: ERRNO_MP_NOT_FOUND, ERRNO_MP_INVALID_CARD, ERRNO_MP_NO_OPS
int ops_completed(transaction_t ** tr, packet_head_t * pkt_hdr_ptr) {
    // verify card exists in card_list with given card_id and auth_code
    RET_ON_FAIL(card_is_valid(pkt_hdr_ptr->card_id, pkt_hdr_ptr->auth_code, card_list));
    // verify transaction with this transaction ID is in the OPS state (it completed OPS)
    RET_ON_FAIL(transaction_ops_done(tr, pkt_hdr_ptr, transaction_list));

    return SUCCESS;
}

// dispatch processing based on pkt_type
// success: SUCCESS
// failure: ERRNO_MP_INVALID_OPCODE, ERRNO_MP_INVALID_P_TYPE,
//      plus those ERRNO_x from subordinate funcs.
int dispatch_packet(packet_head_t * pkt_hdr_ptr) {
    int ret = SUCCESS;

    switch(pkt_hdr_ptr->pkt_type) {
        case INIT :
            // INIT is only for ISSUE to createa new card
            if (pkt_hdr_ptr->op_code == ISSUE) {
                ret = issue_card(pkt_hdr_ptr);
            } else {
                ret = ERRNO_MP_INVALID_OPCODE;
            }
            break;
        case AUTH :
            // AUTH all op_code's except ISSUE before they can do OPS
            if (pkt_hdr_ptr->op_code == PURCHASE ||
                pkt_hdr_ptr->op_code == RECHARGE ||
                pkt_hdr_ptr->op_code == BALANCE ||
                pkt_hdr_ptr->op_code == HISTORY ||
                pkt_hdr_ptr->op_code == REFUND) {
                ret = auth_new_transaction(pkt_hdr_ptr);
            } else {
                ret = ERRNO_MP_INVALID_OPCODE;
            }
            break;
        case OPS :
            // all op_codes except ISSUE can do OPS
            if (pkt_hdr_ptr->op_code == PURCHASE ||
                pkt_hdr_ptr->op_code == RECHARGE ||
                pkt_hdr_ptr->op_code == BALANCE ||
                pkt_hdr_ptr->op_code == HISTORY ||
                pkt_hdr_ptr->op_code == REFUND) {

                // verify AUTH was completed.
                transaction_t * tr = NULL;
                RET_ON_FAIL(auth_completed(&tr, pkt_hdr_ptr));

                ret = process_op_code(&tr, pkt_hdr_ptr);
            } else {
                ret = ERRNO_MP_INVALID_OPCODE;
            }
            break;
        case FIN :
            if (pkt_hdr_ptr->op_code == PURCHASE ||
                pkt_hdr_ptr->op_code == RECHARGE ||
                pkt_hdr_ptr->op_code == BALANCE ||
                pkt_hdr_ptr->op_code == HISTORY ||
                pkt_hdr_ptr->op_code == REFUND ||
                pkt_hdr_ptr->op_code == ISSUE) {

                // get transaction associated with this pkt
                // verify OPS was completed; except for ISSUE which completed INIT
                transaction_t * tr = NULL;
                if(pkt_hdr_ptr->op_code == ISSUE) {
                    RET_ON_FAIL(init_completed(&tr, pkt_hdr_ptr));
                } else {
                    RET_ON_FAIL(ops_completed(&tr, pkt_hdr_ptr));
                }

                ret = process_fin(&tr, pkt_hdr_ptr);
            } else {
                ret = ERRNO_MP_INVALID_OPCODE;
            }

            break;
        default :
            ret = ERRNO_MP_INVALID_P_TYPE;
    }

    return ret;
}

int main(void) {

    int ret = SUCCESS;

    if (NULL == (transaction_list = list_create(transaction_node_contains))) {
        ret = ERRNO_MP_ALLOC;
        goto _fail_main;
    }

    if (NULL == (card_list = list_create(card_node_contains))) {
        ret = ERRNO_MP_ALLOC;
        goto _fail_main;
    }

    packet_head_t * pkt_header_ptr = NULL;
    char pkt_buf_ptr[sizeof(packet_head_t)];

    while (1) {
        pkt_header_ptr = NULL;

        // read in pkt header, fail if we didn't get a full header
        if (sizeof(packet_head_t) != recv_all(pkt_buf_ptr, sizeof(packet_head_t))) {
            ret = ERRNO_MP_RECV;
            goto _fail_main;
        } else {
            pkt_header_ptr = (packet_head_t *)pkt_buf_ptr;
        }

        if(SUCCESS != (ret = dispatch_packet(pkt_header_ptr))) {
            goto _fail_main;
        }
    }

_fail_main:
    if (pkt_header_ptr != NULL) {
        send_error_pkt(pkt_header_ptr, ret);
    }

    return ret;
}


