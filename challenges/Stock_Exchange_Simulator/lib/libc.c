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
 
#include "cgc_libc.h"
#define OK 0
#define NOTOK 1

void cgc_memcpy(void *src, void *dst, cgc_size_t l){
	char * s = (char *) src;
	char * d = (char *) dst;

	for(int i = 0; i < l; i++){
		d[i] = s[i];

	}
	return;
	

}

cgc_size_t cgc_strlen(char * s){
	for(int i = 0; i < 65535; i++){
		if( s[i] == 0x0){
			return i;
		}
	}
	return 65535;

}

int cgc_memcmp(void *l, void *r, cgc_size_t s){
	char *  ll = (char *) l;
	char * rr = (char *)  r;
	for(int i = 0; i < s; i++){
		if(ll[i] != rr[i])			
			return 1;
	}
	return OK;
}

void cgc_memclr(void *l, cgc_size_t s){
	char * m = (char *) l;
	for(int i = 0; i < s; i++)
		m[i] = 0x0;

}

int cgc_recv_all(const cgc_size_t size, void *buf){
	cgc_size_t call_recvd = 0;
	cgc_size_t total_recv = 0;
	int errno = 1;
	while(total_recv < size){

		errno = cgc_receive(STDIN, buf+total_recv, size-total_recv, &call_recvd);
		if(errno != 0)
			return errno;		
		if(call_recvd == 0){
			return NOTOK;
		}
		total_recv = total_recv + call_recvd;
		
	}
	if(total_recv != size)
		return NOTOK;

	return OK;
}

int cgc_transmit_all(void *buf, cgc_size_t s){
	cgc_size_t r = 0;
	cgc_size_t total_xmit = 0;
	int tx_code = 0;
	while(total_xmit < s){
		tx_code = cgc_transmit(STDOUT, buf+total_xmit, s-total_xmit, &r);
		if(tx_code != 0)
			return tx_code;
		if(r == 0)
			return NOTOK; 
		total_xmit = total_xmit + r;

	}
	return OK;
}