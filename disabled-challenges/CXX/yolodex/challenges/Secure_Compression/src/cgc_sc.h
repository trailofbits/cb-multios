/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef SC_H
#define SC_H

#define MAX_DATA_SIZE   4096
#define BLOCK_SIZE      512

typedef struct bit_io {
    unsigned char *data;
    unsigned int didx;
    unsigned int bidx;
} bio_t;

bio_t* cgc_bit_new(unsigned char *data);
unsigned char cgc_bit_read(bio_t *bio, cgc_size_t n);
void cgc_bit_write(bio_t *bio, unsigned char data, cgc_size_t n);

typedef struct sc_obj {
    unsigned char order[95];
    unsigned char *data;
    cgc_size_t data_len;
    int (*cmp) (unsigned char *, unsigned char *, unsigned char *, cgc_size_t);
} sc_obj_t;

sc_obj_t* cgc_sc_new(unsigned char *key);
int cgc_sc_scompress(sc_obj_t *sc, unsigned char **out, cgc_size_t *outlen);
int cgc_sc_sdecompress(sc_obj_t *sc, unsigned char **out, cgc_size_t *outlen);
int cgc_sc_set_data(sc_obj_t *sc, unsigned char *data, cgc_size_t data_len);
unsigned char* cgc_sc_bwt(sc_obj_t *sc, int op, cgc_size_t *outlen);
unsigned char* cgc_sc_mtf(sc_obj_t *sc, int op, cgc_size_t *outlen);

#endif
