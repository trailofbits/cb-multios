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
#pragma once

#include "libcgc.h"
#include "cgc_stdint.h"

#define SZ_PRNG_BUF 8 // 64 bits
#define SZ_PRNG_KEY 16 // 128 bits

#define CRYPTO_ROUNDS 42
#define CRYPTO_DELTA 0xcafebabe // 0x9e3779b9 in TEA
#define CRYPTO_SUM (0xcafebabe * CRYPTO_ROUNDS) // 0xC6EF3720 in TEA

 /**
 * Set the global PRNG key.  This key acts as seed to the PRNG.  
 * Called during initial setup.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int cgc_prng_set_key(void *key);

 /**
 * Get count bytes of pesudo-random data and cgc_write it into the buffer pointed 
 * to by buf.
 *
 * Based on the the key schedule in the public domain Tiny Encryption Algorith.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int cgc_prng_get_bytes(void *buf, cgc_size_t count);

 /**
 * Provided 64 bits of plaintext, encrypt with a 128 bit key to form a 64 bit 
 * ciphertext block.  
 * 
 * Based on the public domain Tiny Encryption Algorithm.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int cgc_encrypt_1block(void *v, void *k);

 /**
 * Provided 64 bits of ciphertextr, decrypt with a 128 bit key to form a 64 bit 
 * plaintext block.  
 *
 * Based on the public domain Tiny Encryption Algorithm.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int cgc_decrypt_1block(void *v, void *k);
