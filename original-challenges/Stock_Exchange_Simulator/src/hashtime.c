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


#include "account.h"
#include "hashtime.h"
#include "libc.h"

void checksum(uint32_t acct_id, uint32_t qty, char * symbol, float price, char *dst){
	for(int i = 0; i < KEY_LEN; i++){
		dst[i] = 0x0;
	}
	// dst and accd_id are both assumed to be 32 chars
	int sym_tail = KEY_LEN-SYM_SIZE;
	for(int i =0; i < SYM_SIZE; i++){
		// make a copy of symbol front and back of chksum
		dst[i] = symbol[i];
		dst[sym_tail+i] = symbol[i];
	}

	memcpy(&qty, (void *) &(dst[SYM_SIZE]), sizeof(uint32_t));
	memcpy(&acct_id, (void *) &(dst[SYM_SIZE+sizeof(uint32_t)]), sizeof(uint32_t));
	uint32_t chksum = acct_id*2+qty;
	uint32_t chk_off = sizeof(uint32_t)*2+SYM_SIZE;

	memcpy(&chksum, &(dst[chk_off]), sizeof(uint32_t));
	char * k = ACCOUNTS[acct_id].key;
	memcpy(k, &(dst[chk_off+sizeof(uint32_t)]), 4);

	for(int i = 0; i < KEY_LEN; i++){
		dst[i] = dst[i] ^ k[i];
		
	}


}
