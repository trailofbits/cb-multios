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
 
#include "cgc_zoom.h"
#include "cgc_libc.h"
#include "cgc_asciiencode.h"

// error out at 0.001

const double cgc_ERROR_LG = -6.907755278982137;
const double cgc_LN_2_RAISE_2 = 0.480453013918201;
const double cgc_LN2 = 0.6931471805599453;
// todo why this hash constant
const unsigned int cgc_HASH_CONST = 0x9747b28c;

zoom_filter_t * cgc_new_zoom_filter(int num_elements){
	if(num_elements == 0){

 
		return NULL;
	}
	double entry_bits;
	zoom_filter_t *zf = cgc_malloc(sizeof(zoom_filter_t));
	// todo check for null here
	if(zf == NULL)
		return NULL;

	zf->inserted_elements = 0;
	zf->num_elements =num_elements;

	entry_bits = -(cgc_ERROR_LG / cgc_LN_2_RAISE_2);


	zf->num_bits = (unsigned int)(num_elements * entry_bits);

	zf->hashes = (unsigned int)(cgc_LN2*entry_bits);

	zf->data_len = ((zf->num_bits / 8 )+1 )* sizeof(unsigned char);
	// todo figure out why calloc broke here...
	zf->data = (unsigned char *) cgc_calloc(1, zf->data_len);
	if(zf->data == NULL){

        	
       
		return NULL;
	}




	return zf;
}

unsigned int cgc_get_sample_n_bits(cgc_size_t sz){
	unsigned int nbits = 0;
	zoom_filter_t *zft = cgc_new_zoom_filter(cgc_n_elements_from_sampsz(sz));

	if(zft == NULL)
		return 0;
	nbits = zft->num_bits;
	cgc_zoom_free(zft);
	return nbits;
}

cgc_size_t cgc_n_elements_from_sampsz(cgc_size_t sz){
	double mult = 1.25;
	cgc_size_t s = (cgc_size_t) (((double) sz) * mult);
	return s;

}

zoom_filter_t * cgc_load_zoom_filter(char *fromwire, unsigned int num_bits){
	cgc_size_t encoded_sz = cgc_strlen(fromwire);
	char *decstr = cgc_decode(fromwire, encoded_sz);
	if(decstr == NULL)
		return NULL;
	cgc_size_t datalen = cgc_strlen(fromwire)/BLOCK_SZ; 
	zoom_filter_t *zf = cgc_malloc(sizeof(zoom_filter_t));
	// todo check math based on new_zoom_filter_above
	zf->data_len = datalen;

	zf->num_bits = num_bits;
	double entry_bits = -(cgc_ERROR_LG / cgc_LN_2_RAISE_2);

	
	zf->hashes = (unsigned int )(cgc_LN2 * entry_bits);
	zf->data = (unsigned char *) decstr;
	return zf;


}

void cgc_zoom_free(zoom_filter_t *zf){
	cgc_free(zf->data);
	cgc_free(zf);
}

// todo replace with own variant not mummur
unsigned int cgc_crazy_hash(const char * key, cgc_size_t sz, unsigned int seed){
	static const unsigned int c1 = 0x1239dace;//0xcc9e2d51;
	static const unsigned int c2 = 0x98ba38de;//0x1b873593;
	static const unsigned int r1 = 15;
	static const unsigned int r2 = 13;
	static const unsigned int m = 5;
	static const unsigned int n = 0xfeba391a;//0xe6546b64;

	unsigned int hash = seed;

	const int nblocks = sz / 4;
	const unsigned int *blocks = (unsigned int *) key;
	for(int i = 0; i < nblocks; i++){
		unsigned int k = blocks[i];
		k *= c1;
		k = (k << r1) | (k >> (32-r1));
		k *= c2;
		hash ^= k;
		hash = ((hash<<r2) |(hash >> (32-r2))) * m + n;

	}
	const unsigned char *tail = (const unsigned char *) (key+nblocks*4);
	unsigned int k1 =0;
	switch(sz & 3){
		case 3:
		k1 ^= tail[2] << 16;
		case 2:
		k1 ^= tail[1] << 8;
		case 1:
		k1 ^= tail[0];

		k1 *= c1;
		k1 = (k1 << r1) | (k1 >> (32-r1));
		k1 *= c2;
		hash ^= k1;
 	}
 	hash ^= sz;
 	hash ^= (hash >> 16);
 	hash *= 0x3298ba21;//0x85ebca6b;
 	hash ^= (hash >> 13);
 	hash *= 0x573ea193;//0xc2b2ae35;
 	hash ^= (hash >> 16);

 	return hash;
}

hash_pair_t * cgc_hash_pair_buf(char *input, cgc_size_t buf_sz){
	unsigned int h1 = cgc_crazy_hash(input, buf_sz, cgc_HASH_CONST);
	unsigned int h2 = cgc_crazy_hash(input, buf_sz, h1);

	hash_pair_t * hp = cgc_malloc(sizeof(hash_pair_t));
	// todo check for bad alloc
	hp->h1 = h1;
	hp->h2 = h2;
	return hp;

}

void cgc_zoom_add(hash_pair_t * hp, zoom_filter_t *zf){


	unsigned int x;
	
	unsigned int byte;
	unsigned int mask;
	unsigned char c;

	for(int i = 0; i < zf->hashes; ++i){
		x = (hp->h1 + i*hp->h2) % zf->num_bits;
		byte = x >> 3;
		c = zf->data[byte];
		mask = 1 << (x%8);
		if(!(c & mask)){
			zf->data[byte] = c | mask;
			zf->inserted_elements += 1;

		}



	}


}


int cgc_zoom_check(hash_pair_t *hp, zoom_filter_t *zf){
	int results = 0;


	unsigned int x;
	
	unsigned int byte;
	unsigned int mask;
	unsigned char c;

	for(int i = 0; i < zf->hashes; ++i){
		x = (hp->h1 + i*hp->h2) % zf->num_bits;
		byte = x >> 3;
		c = zf->data[byte];
		mask = 1 << (x%8);
		if(c & mask){
			results +=1;

		}



	}
	if(results == zf->hashes)
		return 1;

	return 0;

}

