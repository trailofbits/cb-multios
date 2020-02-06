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

#include "cgc_option.h"
#include "cgc_account.h"
#include "cgc_libc.h"
#include "cgc_hashtime.h"
#define OK 0

cgc_size_t cgc_get_data_len(packet_t *p){
	switch(p->ot){
		case BUY:
			return sizeof(option_order_t) - sizeof(void *);
		case SELL:
			return sizeof(option_order_t) - sizeof(void *);

		case QUOTE:
			return sizeof(option_quote_t) - sizeof(void *);

		default:
			return 0;
	}
}

int cgc_recv_rest(packet_t *p){
	cgc_size_t rest_data_sz = cgc_get_data_len(p);
	
	return cgc_recv_all(rest_data_sz, ((void * ) p ) + sizeof(packet_t));

}

cgc_size_t cgc_err_resp(OP_ERR e, packet_t *req, packet_t *p){
	if(e == QTY_OVERFLOW){
		option_order_t *o = (option_order_t *) &(req->op_data);
        //NOTE: this can also overflow, leading to TYPE1 pov.
		// vuln deference of qty, only 4 bytes though, need to have length field to transmit
#ifdef PATCHED_1
		cgc_memcpy("FAIL", (void *) (&p->op_data), sizeof(uint32_t));
#else
		cgc_memcpy((void *) req->bank_id, (void *) (&p->op_data), req->data_l);
#endif

		p->data_l = req->data_l;
		return p->data_l;
	}else{
		p->op_data = (void *) e;
	}
	p->acct_id = req->acct_id;
	
	p->ot = ERR;
	p->rt = RESPONSE;
	return sizeof(packet_t);

}

OP_ERR cgc_checksum_order(uint32_t acct_id, option_order_t *o, char * chk_dst){
	
	cgc_checksum(acct_id, o->qty, o->symbol, o->price, chk_dst);
	int mc = cgc_memcmp(chk_dst, o->sig, KEY_LEN);
	if(mc == 0)
		return OK;
	return BAD_SIG;

}

void cgc_run_sell(packet_t *p, packet_t *resp){
	option_order_t *order = (option_order_t *) &(p->op_data);
	char chk_dst[KEY_LEN];
	OP_ERR chk_okay = cgc_checksum_order(p->acct_id, order, chk_dst);
	if(chk_okay != OK){
		cgc__terminate(21);
	}

		
	OP_ERR can_sell = cgc_run_option_transaction(p->acct_id, order, p->ot);
	int i = 0;

	if(can_sell != OK){
		cgc_size_t esz = cgc_err_resp(can_sell, p, resp);
		int tr = cgc_transmit_all(resp, esz);
		if(tr != OK)
			cgc__terminate(44);


		return;				
	}

	// now we send back an order fill message
	cgc_size_t resp_size = cgc_gen_order_fill_msg(resp, SELL, order->symbol, order->qty, p->acct_id);
	if(cgc_transmit_all((void *) resp, sizeof(packet_t) + resp_size) != OK)
		cgc__terminate(16);
	return;

}

void cgc_run_buy(packet_t *p, packet_t *resp){
	option_order_t *order = (option_order_t *) &(p->op_data);
	char chk_dst[KEY_LEN];
	OP_ERR chk_okay = cgc_checksum_order(p->acct_id, order, chk_dst);


	if(chk_okay != OK){

		cgc__terminate(28);
	}


	OP_ERR can_buy = cgc_run_option_transaction(p->acct_id, order, p->ot);
	if(can_buy != OK){
		cgc_size_t esz = cgc_err_resp(can_buy, p, resp);
		int tr = cgc_transmit_all(resp, esz);
		if(tr != OK)
			cgc__terminate(7);
		if(can_buy == QTY_OVERFLOW)
			cgc__terminate(64);
		return;				
	}

	// now we send back an order fill message
	cgc_size_t resp_size = cgc_gen_order_fill_msg(resp, BUY, order->symbol, order->qty, p->acct_id);
	if(cgc_transmit_all((void *) resp, sizeof(packet_t) + resp_size) != OK)
		cgc__terminate(15);
	return;
}
void cgc_run_quote(packet_t *p, packet_t *resp){
	option_quote_t * qr = (option_quote_t *) &(p->op_data);
	if(qr->symbol != 0x0){

		float ask = cgc_get_current_ask(qr->symbol);
		qr->ask = ask;

		cgc_size_t data_sz = cgc_get_data_len(p);
		cgc_memcpy(p, resp, data_sz+sizeof(packet_t));
		resp->rt = RESPONSE;

		if(cgc_transmit_all((void *) resp, data_sz+sizeof(packet_t)) != OK)
			cgc__terminate(23);

		return;
	
	}
	cgc__terminate(44);
}

int main(int cgc_argc, char *cgc_argv[]){
	cgc_init_accounts();

	char pkt_buf[PKTSIZE];
	char resp_buf[PKTSIZE];
	packet_t *p = (packet_t *) pkt_buf;
	packet_t *resp = (packet_t *) resp_buf;
	uint32_t ct = 0;
	uint32_t tol = 0;
	while(1){
		tol += 1;
		cgc_memclr(p, sizeof(packet_t));
		int errno = cgc_recv_all(sizeof(packet_t), (void *) p);

		if(errno != OK)
			cgc__terminate(1);

		if(p->rt != REQUEST)
			cgc__terminate(2);
		if(p->acct_id >= NUM_ACCOUNTS)
			cgc__terminate(3);

		int all_ok = cgc_recv_rest(p);
		if(all_ok != OK)
			cgc__terminate(all_ok);
		switch(p->ot){
			case BUY:
				cgc_run_buy(p, resp);
				break;
			case SELL:
				cgc_run_sell(p, resp);
				break;
			case QUOTE:
				cgc_run_quote(p, resp);
				break;
			case ERR:
				cgc__terminate(20);
				break;



		}
		ct += 1;
	}




	return 0;
}
