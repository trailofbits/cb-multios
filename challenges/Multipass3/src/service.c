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
#include "libcgc.h"

#include "cgc_libc.h"
#include "cgc_sheap.h"
#include "cgc_multipass.h"
#include "cgc_account.h"

pack_and_data_t *PAD;
void * BACKING_DATA;

void cgc_init_recv_structs(){
    PAD = (pack_and_data_t *) cgc_malloc(sizeof(pack_and_data_t));
    
    BACKING_DATA = cgc_malloc(sizeof(packet_head_t) + sizeof(packet_data_recharge_t) + 1024);

    PAD->ph = BACKING_DATA;
    PAD->data = PAD->ph + 1;
    PAD->pay_data_l = 0;
}

int cgc_recv_all(void * buf, cgc_size_t count, cgc_size_t *rx_bytes){
    int r = EPIPE;
    assert(rx_bytes != NULL);
    cgc_size_t total_bytes = 0;
    cgc_size_t call_recvd = 0;
    for(; total_bytes < count; total_bytes += call_recvd){
       r = cgc_receive(STDIN, buf+total_bytes, count-total_bytes, &call_recvd);
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
pack_and_data_t * cgc_recv_pack_and_data(){
    packet_head_t *ph = PAD->ph;

    cgc_size_t ph_sz = sizeof(packet_head_t);
    cgc_size_t rx_b = 0;
    cgc_size_t rx_pay = 0;

    int r = cgc_recv_all(ph, ph_sz, &rx_b);
    if(r != OK || ph_sz != rx_b)
        return NULL;

    PAD->pay_data_l = 0;
    PAD->data = NULL;

    cgc_size_t data_sz = cgc_get_size_of_data_for_pkt_head_only(ph, 1);
    cgc_size_t data_rc = 0;


    if(data_sz > 0){
        PAD->data = (PAD->ph + 1);
        void *data = PAD->data;
        
        int x = cgc_recv_all(data, data_sz, &data_rc);
        if(x != OK || data_rc != data_sz)
            return NULL;
        assert(data_rc == data_sz);
        

        cgc_size_t ds = 0;
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
                    d = data+cgc_get_size_of_data_for_pkt_head_only(ph, 1);
                    inner_recv = cgc_recv_all(d, ds, &rx_pay);
                    if(inner_recv != OK || ds != rx_pay)
                        return NULL;
                    break;
                case RECHARGE:
                    pr = data;
                    ds = pr->v.vendor_location_sz;
                    d = data+cgc_get_size_of_data_for_pkt_head_only(ph, 1);
                    inner_recv = cgc_recv_all(d, ds, &rx_pay);
                    if(inner_recv != OK || ds != rx_pay)
                        return NULL;
                    break;
            }


        }
    }
    PAD->pay_data_l = data_rc+rx_pay;

    return PAD;

}



pack_and_data_t * cgc_ops_delegate(pack_and_data_t *pad, cgc_size_t *data_sz){
    packet_head_t *ph = pad->ph;

    switch(ph->op_code){
        case PURCHASE:
            return cgc_process_client_purchase_op(pad);
        case RECHARGE:

            return cgc_process_client_recharge_op(pad);
        case BALANCE:
            return cgc_process_client_balance(pad);
        case HISTORY:
            return cgc_process_client_history(pad, data_sz);
        case ISSUE:
            return NULL;
        case REFUND:
            return cgc_process_client_refund_op(pad);

    }
    cgc_ERRNO = ERRNO_MP_INVALID_OPCODE;
    return NULL;


}

void cgc_free_pad(pack_and_data_t *pad){
    void * ph = pad->ph;
    void * data = pad->data;
    if(data-ph == sizeof(packet_head_t)){

        cgc_free(ph);
        return;
       
    }
    cgc_free(ph);
    if(data != NULL)
        cgc_free(data);

};

int main(int cgc_argc, char *cgc_argv[]) {
    int ret;
    cgc_size_t size;

    cgc_malloc_init();
    cgc_init_recv_structs();
    cgc_init_resp_structs();

    int i = 0;
    while(1){
        pack_and_data_t *pad = cgc_recv_pack_and_data();
        if(pad == NULL)
            cgc__terminate(1);

        packet_head_t *ph = pad->ph;
        pack_and_data_t * resp = NULL;
        cgc_size_t data_sz = 0;
        if( pad == NULL || ph == NULL){
            cgc__terminate(1);
        }

        switch(ph->pkt_type){

            case INIT:
                i += 1;
                resp = cgc_generate_new_init_and_init_resp(pad);
                break;
            case AUTH:
                resp = cgc_process_client_auth(pad);
                break;
            case OPS:
                resp = cgc_ops_delegate(pad, &data_sz);
                break;
            case FIN:
                resp = cgc_process_client_fin(pad);
                break;
            default:
                break;
        }
        
        if(resp == NULL){
            resp = cgc_generate_error(ph);
        }


        if(resp == NULL)
            break;
        cgc_transmit_all(STDOUT, (const char *) resp->ph, sizeof(packet_head_t));
        if(resp->pay_data_l != 0)
            cgc_transmit_all(STDOUT, (const char *) resp->data, resp->pay_data_l);

        
        data_sz = 0;

    }
    
    cgc__terminate(1);
}
