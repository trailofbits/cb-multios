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

#define MAINFILE
#include <libcgc.h>

#include "libc.h"
#include "sheap.h"
#include "multipass.h"
#include "account.h"

pack_and_data_t *PAD;
void * BACKING_DATA;

void init_recv_structs(){
    PAD = (pack_and_data_t *) malloc(sizeof(pack_and_data_t));
    
    BACKING_DATA = malloc(sizeof(packet_head_t) + sizeof(packet_data_recharge_t) + 1024);

    PAD->ph = BACKING_DATA;
    PAD->data = PAD->ph + 1;
    PAD->pay_data_l = 0;
}

int recv_all(void * buf, size_t count, size_t *rx_bytes){
    int r = EPIPE;
    assert(rx_bytes != NULL);
    size_t total_bytes = 0;
    size_t call_recvd = 0;
    for(; total_bytes < count; total_bytes += call_recvd){
       r = receive(STDIN, buf+total_bytes, count-total_bytes, &call_recvd);
       if(call_recvd == 0){
            break;
       }
       if(r != OK){
            break;
       }
    }
    *rx_bytes = total_bytes;
    
    return r;
}

// reuse same pack head
pack_and_data_t * recv_pack_and_data(){
    packet_head_t *ph = PAD->ph;

    size_t ph_sz = sizeof(packet_head_t);
    size_t rx_b = 0;
    size_t rx_pay = 0;

    int r = recv_all(ph, ph_sz, &rx_b);
    if(r != OK || ph_sz != rx_b)
        return NULL;

    PAD->pay_data_l = 0;
    PAD->data = NULL;

    size_t data_sz = get_size_of_data_for_pkt_head_only(ph, 1);
    size_t data_rc = 0;


    if(data_sz > 0){
        PAD->data = (PAD->ph + 1);
        void *data = PAD->data;
        
        int x = recv_all(data, data_sz, &data_rc);
        if(x != OK || data_rc != data_sz)
            return NULL;
        assert(data_rc == data_sz);
        

        size_t ds = 0;
        if(ph->pkt_type == OPS && ( ph->op_code == PURCHASE || ph->op_code == RECHARGE)){
            // then we also must receive vendor data...
            
            void *d;
            packet_data_purchase_t * pur;
            packet_data_recharge_t * pr;
            
            // we already recvd first 4 bytes of vendor loc with above
            int inner_recv = 0;
            switch(ph->op_code){
                case PURCHASE:
                    pur = data;
                    ds = pur->v.vendor_location_sz;
                    // instead of pointer math because sizeof isn't handled right
                    d = data+get_size_of_data_for_pkt_head_only(ph, 1);
                    inner_recv = recv_all(d, ds, &rx_pay);
                    if(inner_recv != OK || ds != rx_pay)
                        return NULL;
                    break;
                case RECHARGE:
                    pr = data;
                    ds = pr->v.vendor_location_sz;
                    d = data+get_size_of_data_for_pkt_head_only(ph, 1);
                    inner_recv = recv_all(d, ds, &rx_pay);
                    if(inner_recv != OK || ds != rx_pay)
                        return NULL;
                    break;
            }


        }
    }
    PAD->pay_data_l = data_rc+rx_pay;

    return PAD;

}



pack_and_data_t * ops_delegate(pack_and_data_t *pad, size_t *data_sz){
    packet_head_t *ph = pad->ph;

    switch(ph->op_code){
        case PURCHASE:
            return process_client_purchase_op(pad);
        case RECHARGE:

            return process_client_recharge_op(pad);
        case BALANCE:
            return process_client_balance(pad);
        case HISTORY:
            return process_client_history(pad, data_sz);
        case ISSUE:
            return NULL;
        case REFUND:
            return process_client_refund_op(pad);

    }
    ERRNO = ERRNO_MP_INVALID_OPCODE;
    return NULL;


}

void free_pad(pack_and_data_t *pad){
    void * ph = pad->ph;
    void * data = pad->data;
    if(data-ph == sizeof(packet_head_t)){

        free(ph);
        return;
       
    }
    free(ph);
    if(data != NULL)
        free(data);

};

int main(void) {
    int ret;
    size_t size;

    malloc_init();
    init_recv_structs();
    init_resp_structs();

    int i = 0;
    while(1){
        pack_and_data_t *pad = recv_pack_and_data();
        if(pad == NULL)
            _terminate(1);

        packet_head_t *ph = pad->ph;
        pack_and_data_t * resp = NULL;
        size_t data_sz = 0;
        if( pad == NULL || ph == NULL){
            _terminate(1);
        }

        switch(ph->pkt_type){

            case INIT:
                i += 1;
                resp = generate_new_init_and_init_resp(pad);
                break;
            case AUTH:
                resp = process_client_auth(pad);
                break;
            case OPS:
                resp = ops_delegate(pad, &data_sz);
                break;
            case FIN:
                resp = process_client_fin(pad);
                break;
            default:
                break;
        }
        
        if(resp == NULL){
            resp = generate_error(ph);
        }


        if(resp == NULL)
            break;
        transmit_all(STDOUT, (const char *) resp->ph, sizeof(packet_head_t));
        if(resp->pay_data_l != 0)
            transmit_all(STDOUT, (const char *) resp->data, resp->pay_data_l);

        
        data_sz = 0;

    }
    
    _terminate(1);
}
