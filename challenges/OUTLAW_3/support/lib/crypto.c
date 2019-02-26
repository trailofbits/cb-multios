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
#include "libc.h"

byte_t prng_bytes_remaining = 0;

// inititalized from flag page in main()
byte_t prng_key[SZ_PRNG_KEY]; 

// Iniitialize the prng_buf to something static.  
// The key is taken from the flag page and initialized in main().
byte_t prng_buf[SZ_PRNG_BUF] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77 };


int encrypt_1block(void *v, void *k) {
	DBG("\n");

	int ret = SUCCESS;
	uint32_t *_v = v, *_k = k;

	uint32_t v0 = _v[0], v1 = _v[1], sum = 0, i;
	uint32_t delta = CRYPTO_DELTA; 
	uint32_t k0 = _k[0], k1 = _k[1], k2 = _k[2], k3 = _k[3];

	for (i=0; i < CRYPTO_ROUNDS; i++) {
		sum += delta;
		v0 += ((v1<<6) + k0) ^ (v1 + sum) ^ ((v1>>7) + k1);
		v1 += ((v0<<6) + k2) ^ (v0 + sum) ^ ((v0>>7) + k3);
	} 

	_v[0]=v0; _v[1] =v1;

bail:
	return ret;
}


int decrypt_1block(void *v, void *k) {
	DBG("\n");

	int ret = SUCCESS;
	uint32_t *_v = v, *_k = k;

	uint32_t v0 = _v[0], v1 = _v[1], sum = CRYPTO_SUM, i;
	uint32_t delta = CRYPTO_DELTA; 
	uint32_t k0 = _k[0], k1 = _k[1], k2 = _k[2], k3 = _k[3];

	for (i=0; i < CRYPTO_ROUNDS; i++) {
		v1 -= ((v0<<6) + k2) ^ (v0 + sum) ^ ((v0>>7) + k3);
		v0 -= ((v1<<6) + k0) ^ (v1 + sum) ^ ((v1>>7) + k1);
		sum -= delta;
	} 

	_v[0]=v0; _v[1] =v1;

bail:
	return ret;
}


int prng_set_key(void *key) {
	DBG("\n");
	int ret = SUCCESS;
	memcpy(prng_key, key, sizeof(prng_key));
bail:
	return ret;
}


int prng_refill_cache(void) {
	DBG("\n");

	int ret = SUCCESS;

	DBG("[D] repopulating prng_buf with prng_key = "
		"0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n", 
		prng_key[0], prng_key[1], prng_key[2], prng_key[3],
		prng_key[4], prng_key[5], prng_key[6], prng_key[7],
		prng_key[8], prng_key[9], prng_key[10], prng_key[11],
		prng_key[12], prng_key[13], prng_key[14], prng_key[15]);

	DBG("[D] prng_buf before: 0x%02x%02x%02x%02x%02x%02x%02x%02x\n", 
		prng_buf[0], prng_buf[1], prng_buf[2], prng_buf[3], 
		prng_buf[4], prng_buf[5], prng_buf[6], prng_buf[7]);

	uint32_t v[2] = { // 32 * 2 = 64
		prng_buf[0] <<  0 | prng_buf[1] <<  8 | prng_buf[2] << 16 | prng_buf[3] << 24,
		prng_buf[4] <<  0 | prng_buf[5] <<  8 | prng_buf[6] << 16 | prng_buf[7] << 24,
	};
	uint32_t k[4] = { // 32 * 4 = 128
		prng_key[ 0] <<  0 | prng_key[ 1] <<  8 | prng_key[ 2] << 16 | prng_key[ 3] << 24,
		prng_key[ 4] <<  0 | prng_key[ 5] <<  8 | prng_key[ 6] << 16 | prng_key[ 7] << 24,
		prng_key[ 8] <<  0 | prng_key[ 9] <<  8 | prng_key[10] << 16 | prng_key[11] << 24,
		prng_key[12] <<  0 | prng_key[13] <<  8 | prng_key[14] << 16 | prng_key[15] << 24,
	};
	decrypt_1block((uint32_t *)&v, (uint32_t *)&k);
	prng_buf[0] = (v[0] >>  0) & 0xFF; prng_buf[1] = (v[0] >>  8) & 0xFF;
	prng_buf[2] = (v[0] >> 16) & 0xFF; prng_buf[3] = (v[0] >> 24) & 0xFF;
	prng_buf[4] = (v[1] >>  0) & 0xFF; prng_buf[5] = (v[1] >>  8) & 0xFF;
	prng_buf[6] = (v[1] >> 16) & 0xFF; prng_buf[7] = (v[1] >> 24) & 0xFF;

	DBG("[D] prng_buf after: 0x%02x%02x%02x%02x%02x%02x%02x%02x\n", 
		prng_buf[0], prng_buf[1], prng_buf[2], prng_buf[3], 
		prng_buf[4], prng_buf[5], prng_buf[6], prng_buf[7]);

	prng_bytes_remaining = SZ_PRNG_BUF;

bail:
	return ret;
}

// our key schedule is just TEA decryption, cached in an 8B buffer
int prng_get_bytes(void *buf, size_t count) {
	DBG("\n");

	int ret = SUCCESS;

	DBG("[D] %d bytes requested\n", count);

	size_t idx_buf = 0;
	// size_t i;
	byte_t *buf_bytes = buf;

	while (count) {

		// consume any bytes we can out of cache
		while(prng_bytes_remaining && count) {
			buf_bytes[idx_buf] = prng_buf[SZ_PRNG_BUF - prng_bytes_remaining];
			prng_bytes_remaining--;
			count--;
			idx_buf++;
		}

		// refill cache as necessary
		if (0 == prng_bytes_remaining) { prng_refill_cache(); }
	}

bail:
	return ret;
}



