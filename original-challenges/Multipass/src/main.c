/*
 * Copyright (c) 2014 Kaprica Security, Inc.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 */
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "multipass_protocol.h"

typedef struct card_info {
    uint32_t card_id;
    uint32_t auth_code;
    uint32_t value;

    struct card_info *next;
} card_info_t;

typedef struct transaction {
    uint32_t auth_code; // used internally
    uint32_t vendor_id;
    OP_CODE op_code : 8;
    PKT_TYPE state : 8;
    STATUS status : 8;
    uint32_t id;
    uint32_t card_id;
    void *data;
} transaction_t;

// GLOBAL VARIABLES
static packet_head_t pkthdr; // last received packet header
static transaction_t *transaction;
static transaction_t *transactions_array = NULL;
static size_t transactions_length = 0;
static size_t transactions_idx = 0;
static card_info_t *card_info_list;

static int send(void *data, size_t length)
{
    if (writeall(STDOUT, data, length) != length)
        return 1;
    return 0;
}

static int read_fully(void *dest, size_t length)
{
    size_t read = 0, bytes;
    while (read < length)
    {
        if (receive(STDIN, (uint8_t *)dest + read, length - read, &bytes) != 0)
            return 1;
        if (bytes == 0)
            return 1;
        read += bytes;
    }
    return 0;
}

static void send_error(STATUS status, char *msg)
{
    packet_head_t hdr;
    
    hdr = pkthdr; // initialize with values from received header
    hdr.status = status;
    send(&hdr, sizeof(hdr));

    packet_data_error_t data;
    data.length = sizeof(data.msg);
    strncpy(data.msg, msg, data.length);
    send(&data, sizeof(data));

    if (transaction)
        transaction->status = status;

    // according to the spec, exit on error
    exit(0);
}

static int enlarge_transactions_array(size_t new_length)
{
    if (new_length <= transactions_length)
        return 0;

#if 0
    void *new_array = realloc(transactions_array, sizeof(transaction_t) * new_length);
    if (new_array == NULL)
        return 1;
    transactions_array = new_array;
    transactions_length = new_length;
#endif

    if (new_length > 8*1024*1024 / sizeof(transaction_t))
        return 1;

    void *new_array;
    if (allocate(8*1024*1024, 0, &new_array) != 0)
        return 1;
    transactions_array = new_array;
    transactions_length = 8*1024*1024 / sizeof(transaction_t);
    return 0;
}

static uint32_t next_card_id()
{
    static uint32_t next = FIRST_CARD_ID;

    // update next
    uint32_t retval = next;
    next++;

    return retval;
}

static uint32_t next_auth_code()
{
    static uint32_t next = FIRST_CARD_AUTH_CODE;

    // update next
    uint32_t retval = next;
    next = ((next >> 17) ^ (next << 3)) * 31337;

    return retval;
}

static card_info_t *lookup_card(uint32_t card_id)
{
    card_info_t *card;
    for (card = card_info_list; card != NULL; card = card->next)
        if (card->card_id == card_id) 
            return card;
    return NULL;
}

static int handle_issue()
{
    packet_data_issue_t *data = transaction->data;

    card_info_t *card = malloc(sizeof(card_info_t));
    if (card == NULL)
    {
        send_error(ERRNO_MP_ALLOC, ALLOC_MSG);
        return 1;
    }

    card->card_id = next_card_id();
    card->auth_code = next_auth_code();
    card->value = data->amount;
    card->next = card_info_list;
    card_info_list = card;

    packet_head_t hdr;
    memset(&hdr, 0, sizeof(hdr));
    hdr.card_id = card->card_id;
    hdr.auth_code = card->auth_code;
    hdr.pkt_type = INIT;
    hdr.op_code = ISSUE;
    hdr.status = OK;
    hdr.transaction_id = transaction->id;

    transaction->card_id = card->card_id;
    transaction->auth_code = card->auth_code;
    send(&hdr, sizeof(hdr));
    return 0;
}

static int read_data(transaction_t *t)
{
    size_t datalen;
    switch (pkthdr.op_code)
    {
    case ISSUE:
    case HISTORY:
        datalen = 4;
        break;
    case REFUND:
        datalen = 8;
        break;
    case RECHARGE:
        datalen = 10;
        break;
    case PURCHASE:
        datalen = 14;
        break;
    case BALANCE:
        datalen = 0;
        break;
    default:
        return 1;
    }

    if (datalen > 0)
    {
        t->data = malloc(datalen);
        if (t->data == NULL)
            goto fail;
        if (read_fully(t->data, datalen) != 0)
            goto fail;
    }
    else
    {
        t->data = NULL;
    }

    size_t extralen = 0;
    if (pkthdr.op_code == PURCHASE)
    {
        packet_data_purchase_t *data = t->data;
        extralen = data->v.vendor_location_sz;
    }
    else if (pkthdr.op_code == RECHARGE)
    {
        packet_data_recharge_t *data = t->data;
        extralen = data->v.vendor_location_sz;
    }

    if (extralen > 0)
    {
        void *newdata = realloc(t->data, datalen+extralen);
        if (newdata == NULL)
            goto fail;
        t->data = newdata;
        if (read_fully((uint8_t *)t->data + datalen, extralen) != 0)
            goto fail;
    }
    return 0;

fail:
    free(t->data);
    t->data = NULL;
    return 1;
}

static transaction_t *new_transaction()
{
    if (enlarge_transactions_array(transactions_idx+10) != 0)
        return NULL;

    transaction_t *t = &transactions_array[transactions_idx++];
    memset(t, 0, sizeof(transaction_t));
    t->id = (uint32_t) t;
    t->op_code = pkthdr.op_code;
    t->state = pkthdr.pkt_type;
    t->status = OK;
    t->card_id = pkthdr.card_id;
    t->auth_code = pkthdr.auth_code;
    return t;
}

static transaction_t *lookup_transaction(uint32_t id)
{
    transaction_t *t = (transaction_t*) id;
#ifdef PATCHED // another patch would be to use index rather than pointers
    uint32_t i;
    for (i = 0; i < transactions_idx; i++)
    {
        if (t == &transactions_array[i])
            return t;
    }
    return NULL;
#else
    if (t < transactions_array || t >= &transactions_array[transactions_idx])
        return NULL;
    return t;
#endif
}

static int handle_purchase()
{
    packet_data_purchase_t *data = transaction->data;
    card_info_t *card = lookup_card(transaction->card_id);

    if (data->cost <= card->value)
    {
        card->value -= data->cost;
        transaction->state = OPS;
        transaction->status = OK;
        transaction->vendor_id = data->v.vendor_id;
    }
    else
    {
        send_error(ERRNO_MP_PURCHASE_ISF, PURCHASE_ISF_MSG);
        return 1;
    }

    packet_head_t hdr;
    hdr = pkthdr;
    hdr.status = OK;
    send(&hdr, sizeof(hdr));
    return 0;
}

static int handle_recharge()
{
    packet_data_recharge_t *data = transaction->data;
    card_info_t *card = lookup_card(transaction->card_id);

    if (data->amount <= UINT32_MAX - card->value)
    {
        card->value += data->amount;
        transaction->state = OPS;
        transaction->status = OK;
        transaction->vendor_id = data->v.vendor_id;
    }
    else
    {
        send_error(ERRNO_MP_RECHARGE_FULL, RECHARGE_FULL_MSG);
        return 1;
    }

    packet_head_t hdr;
    hdr = pkthdr;
    hdr.status = OK;
    send(&hdr, sizeof(hdr));
    return 0;
}

static int handle_balance()
{
    card_info_t *card = lookup_card(transaction->card_id);

    transaction->data = malloc(sizeof(packet_data_balance_t));
    if (transaction->data == NULL)
    {
        send_error(ERRNO_MP_ALLOC, ALLOC_MSG);
        return 1;
    }

    packet_head_t hdr;
    hdr = pkthdr;
    hdr.status = OK;
    send(&hdr, sizeof(hdr));

    packet_data_balance_t *data = transaction->data;
    memset(data, 0, sizeof(packet_data_balance_t));
    data->balance = card->value;
    send(data, sizeof(packet_data_balance_t));

    transaction->state = OPS;
    transaction->status = OK;
    return 0;
}

static int handle_history()
{
    packet_data_history_t *data = transaction->data;
    size_t count, i;

    // figure out how many things we will actually send back
    for (count = 0, i = 0; i < transactions_idx; i++)
        if (transactions_array[i].state == FIN && transactions_array[i].card_id == transaction->card_id)
            count++; 

    if (count < data->count)
        data->count = count;

    if (count == 0)
    {
        send_error(ERRNO_MP_NO_HISTORY, NO_HISTORY_MSG);
        return 1;
    }

    packet_head_t hdr;
    hdr = pkthdr;
    hdr.status = OK;
    send(&hdr, sizeof(hdr));
    send(data, sizeof(packet_data_history_t));

    for (i = transactions_idx; i > 0 && count > 0; i--, count--)
    {
        // we only send successful transactions
        while ((transactions_array[i-1].state != FIN || transactions_array[i].card_id == transaction->card_id) && i > 0)
            i--;
        if (i == 0)
            break;

        transaction_t *t = &transactions_array[i-1];

        packet_data_transaction_t dt;
        memset(&dt, 0, sizeof(dt));
        dt.op_code = t->op_code;
        dt.state = t->state;
        dt.status = t->status;
        dt.card_id = t->card_id;
        dt.id = t->id;
        send(&dt, sizeof(dt));
    }

    transaction->state = OPS;
    transaction->status = OK;
    return 0;
}

static int handle_refund()
{
    packet_data_refund_t *data = transaction->data;
    card_info_t *card = lookup_card(transaction->card_id);

    transaction_t *old_trans = lookup_transaction(data->transaction_id);
    if (old_trans == NULL || old_trans->op_code != PURCHASE || old_trans->state != FIN || old_trans->status != OK)
    {
        send_error(ERRNO_MP_UNK, UNK_ERROR_MSG);
        return 1;
    }

    packet_data_purchase_t *old_data = old_trans->data;
    if (old_data->purchase_id != data->purchase_id)
    {
        send_error(ERRNO_MP_UNK, UNK_ERROR_MSG);
        return 1;
    }

    if (old_data->cost <= UINT32_MAX - card->value)
    {
        card->value += old_data->cost;
        transaction->state = OPS;
        transaction->status = OK;
        transaction->vendor_id = old_data->v.vendor_id;
        old_trans->state = REFUNDED;
    }
    else
    {
        send_error(ERRNO_MP_REFUND_FULL, REFUND_FULL_MSG);
        return 1;
    }

    packet_head_t hdr;
    hdr = pkthdr;
    hdr.status = OK;
    send(&hdr, sizeof(hdr));
    return 0;
}

static int process_ops()
{
    if (pkthdr.op_code == PURCHASE)
        return handle_purchase();
    else if (pkthdr.op_code == RECHARGE)
        return handle_recharge();
    else if (pkthdr.op_code == BALANCE)
        return handle_balance();
    else if (pkthdr.op_code == HISTORY)
        return handle_history();
    else if (pkthdr.op_code == REFUND)
        return handle_refund();
    else
    {
        send_error(ERRNO_MP_INVALID_OPCODE, INVALID_OPCODE_MSG);
        return 1;
    }
}

int main()
{
    uint32_t *last_id = NULL;
    enlarge_transactions_array(10);

    while (1)
    {
        if (read_fully(&pkthdr, sizeof(pkthdr)) != 0)
            break;

        transaction = NULL;
        if (last_id != NULL && *last_id != pkthdr.transaction_id)
        {
            send_error(ERRNO_MP_NOT_FOUND, NOT_FOUND_MSG);
            goto fail;
        }

        transaction_t *last_transaction = lookup_transaction(pkthdr.transaction_id);
        
        if (pkthdr.op_code == ISSUE)
        {
            if (pkthdr.pkt_type == INIT)
            {
                transaction = new_transaction();
                if (!transaction)
                {
                    send_error(ERRNO_MP_ALLOC, ALLOC_MSG);
                    goto fail;
                }

                if (read_data(transaction) != 0)
                {
                    send_error(ERRNO_MP_UNK, UNK_ERROR_MSG);
                    goto fail;
                }

                if (handle_issue() != 0)
                    goto fail;

                last_id = &transaction->id;
            }
            else if (pkthdr.pkt_type == FIN && last_transaction)
            {
                last_id = NULL;
                transaction = last_transaction;
                if (transaction->card_id == pkthdr.card_id && transaction->auth_code == pkthdr.auth_code)
                {
                    packet_head_t hdr;
                    hdr = pkthdr;
                    hdr.status = OK;
                    send(&hdr, sizeof(hdr));
                    transaction->state = FIN;
                }
                else
                {
                    send_error(ERRNO_MP_NO_INIT, NO_INIT_MSG);
                    goto fail;
                }
            }
            else
            {
                send_error(ERRNO_MP_NO_INIT, NO_INIT_MSG);
                goto fail;
            }
        }
        else if (last_transaction == NULL)
        {
            if (pkthdr.pkt_type == AUTH)
            {
                card_info_t *card = lookup_card(pkthdr.card_id);
                if (card == NULL || card->auth_code != pkthdr.auth_code)
                {
                    send_error(ERRNO_MP_INVALID_CARD, INVALID_CARD_MSG);
                    goto fail;
                }
                transaction = new_transaction();
                packet_head_t hdr;
                hdr = pkthdr;
                hdr.status = OK;
                hdr.transaction_id = transaction->id;
                send(&hdr, sizeof(hdr));

                last_id = &transaction->id;
            }
            else
            {
                send_error(ERRNO_MP_NO_AUTH, NO_AUTH_MSG);
                goto fail;
            }
        }
        else
        {
            if (pkthdr.op_code != last_transaction->op_code || 
                pkthdr.card_id != last_transaction->card_id ||
                pkthdr.auth_code != last_transaction->auth_code)
            {
                send_error(ERRNO_MP_UNK, UNK_ERROR_MSG);
                goto fail;
            }

            transaction = last_transaction;
            if (pkthdr.pkt_type == OPS)
            {
                if (transaction->state != AUTH)
                {
                    send_error(ERRNO_MP_NO_AUTH, NO_AUTH_MSG);
                    goto fail;
                }

                if (read_data(transaction) != 0)
                {
                    send_error(ERRNO_MP_UNK, UNK_ERROR_MSG);
                    goto fail;
                }

                if (process_ops() != 0)
                    goto fail;
            }
            else if (pkthdr.pkt_type == FIN)
            {
                last_id = NULL;
                if (transaction->state != OPS)
                {
                    send_error(ERRNO_MP_NO_OPS, NO_OPS_MSG);
                    goto fail;
                }

                transaction->state = FIN;
                packet_head_t hdr;
                hdr = pkthdr;
                hdr.status = OK;
                send(&hdr, sizeof(hdr));
            }
            else
            {
                send_error(ERRNO_MP_INVALID_P_TYPE, INVALID_PKT_TYPE_MSG);
                goto fail;
            }
        }

        continue;

fail:
        last_id = NULL;
        continue;
    }
    return 0;
}
