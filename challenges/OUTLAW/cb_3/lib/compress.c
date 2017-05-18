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


int cgc_get_match_run_length(uint32_t i1, uint32_t i2, uint8_t *num_matching) {
	DBG("\n");

	int ret = SUCCESS;

	DBG("[D] finding initial matching bit run: 0x%08x vs. 0x%08x\n", i1, i2);

	for (cgc_size_t i=0; i<NUM_BITS_IN_A_UINT32; i++) {
		if ((1 & (i1 >> (NUM_BITS_IN_A_UINT32-1-i))) == (1 & (i2 >> (NUM_BITS_IN_A_UINT32-1-i)))) {
			*num_matching = *num_matching+1;
		} else {
			break;
		}
	}

	DBG("[D] 0x%08x & 0x%08x share %d initial matching bits\n", i1, i2, *num_matching);

bail:
	return ret;
}
