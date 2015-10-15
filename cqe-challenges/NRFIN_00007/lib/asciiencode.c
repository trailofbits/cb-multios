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

#include "asciiencode.h"
#include "libc.h"

// 64 char alphabet, every byte has 4 possible bytes

unsigned char get_num_for_char(unsigned char u){
	
	for(int i = 0; i < ABETSZ ; ++i){
		if(u == (unsigned char) ALPHABET[i])
			return i;
		
	}
	return 128;
}

char * encode(char * input, size_t size){
	
	size_t sz = size*BLOCK_SZ;
	char *outbuf = (char *) calloc(1, sz+1);
	if(outbuf == NULL)
		return NULL;
	int outidx = 0;
	for(int i =0; i < size; i++){
		unsigned char inch = (unsigned char) input[i];
		unsigned int idx1 = inch/divisor;
		unsigned int idx2 = inch % divisor;
		if(idx1 >= ABETSZ || idx2 >= ABETSZ){
			free(outbuf);
			return NULL;
		}
		outbuf[outidx] = ALPHABET[idx1];
		outbuf[outidx+1] = ALPHABET[idx2];
		outidx += BLOCK_SZ;
		
 
	}
	outbuf[sz+1] = 0x00;

	return outbuf;

}

char * decode(char * input, size_t size){
	unsigned char * outbuf = calloc(1, size/BLOCK_SZ);
	int outct = 0;
	for(int i =0; i < size; i+=BLOCK_SZ){
		unsigned char in1 = input[i];
		unsigned char in2 = input[i+1];
		unsigned char ch1 = get_num_for_char(in1);
		unsigned char ch2 = get_num_for_char(in2);
		if(ch1 < 127 &&  ch2 < 127 ){
			outbuf[outct] = ch1 * divisor + ch2;

		}else{
			free(outbuf);
			return NULL;
		}
		outct +=1;

	}
	return (char *) outbuf;
}