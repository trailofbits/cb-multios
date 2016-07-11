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
#include <libcgc.h>
#include "libc.h"
#include "csum.h"

uint32_t crctable[256] = {0};
uint32_t md5table[64] = {0};
uint8_t calcd = 0;


uint64_t additive(uint8_t* data, uint32_t s) {
    uint32_t i;
    uint64_t csum = 0xDEADBEEFC0FFEE;

    if(s % sizeof(uint64_t))
        return csum;

    for(i = 0; i < s; i+=sizeof(uint64_t))
        csum += *(uint64_t*)(data+i); 
    return csum;
}

uint64_t addxoradd(uint8_t *data, uint32_t s) {
    uint32_t i;
    uint64_t csum = 0x31337157C0FFEE;

    if(s % sizeof(uint64_t))
        return csum;

    for(i = 0; i < s; i+=sizeof(uint64_t)) {
        csum += *(uint64_t*)(data+i);
        csum ^= *(uint64_t*)(data+i);
        csum += *(uint64_t*)(data+i);
    }
    return csum;
}

static void compute_me_crc(){
    uint32_t i, j, k;
    for (i = 0; i < 256; i++) {
        k = i;
        for (j = 0; j < 8; j++) {
            if(k & 1)
                k = 0xedb88320 ^ (k >> 1);
            else
                k >>= 1;
        }
        crctable[i] = k;
    }
    calcd = 1;
}

uint32_t updatecrc(uint8_t *data, uint32_t s, uint32_t crc) {
    uint32_t i,j = crc;
    if(!calcd)
        compute_me_crc();
    for (i = 0; i < s; i++) 
        j = crctable[(j&0xff)^*(data+i)] ^ ( j >> 8);
    return j;
}

uint32_t crc32(uint8_t *data, uint32_t s) {
    return updatecrc(data, s, ~0x50C0FFEE)^0xffffffff;
}

double fpadditive(uint8_t *data, uint32_t s) {
    uint32_t i;
    double csum = 3.141592;

    if(s % 4)
        return csum;

    for(i = 0; i < s; i+=sizeof(double))
        csum += *(double *)(data+i); 

    return csum;
}

static uint32_t F(uint32_t x, uint32_t y, uint32_t z) {
    return (((x) & (y)) | ((~x) & (z)));
}
static uint32_t G(uint32_t x, uint32_t y, uint32_t z) { 
    return (((x) & (z)) | ((y) & (~z)));
}
static uint32_t H(uint32_t x, uint32_t y, uint32_t z) { 
    return ((x) ^ (y) ^ (z));
}
static uint32_t I(uint32_t x, uint32_t y, uint32_t z) {
    return ((y) ^ ((x) | (~z)));
}

#define ROL(x, n) (((x) << (n)) | ((x) >> (32-(n))))


void calc_me_md5() {
    uint32_t i;

    for (i=0; i < 64; i++)
        md5table[i] = (uint32_t)(fabs(sin(i+1))*pow(2,32));
}

void md5(uint8_t *data, size_t s, uint32_t* out) {
    size_t len;
    uint32_t i,j,n,b;
    uint16_t k,l,m;
    //uint32_t d[16] = {0};
    uint8_t* d;
    uint32_t curb[16] = {0};
    uint32_t block[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476}; 
    uint32_t final[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
    uint32_t (*funcs[])(uint32_t,uint32_t,uint32_t) = {&F,&G,&H,&I};
    uint16_t rot[6][4] = { 
                            {7,12,17,22},
                            {5,9,14,20},
                            {4,11,16,23},
                            {6,10,15,21},
                            {1,5,3,7},
                            {0,1,5,0}
    };

    calc_me_md5();

    //alloc our temp buffer
    len = (((s+8)/64)+1)*64;
    ALLOC(0, (void**)&d, len);
    memset(d, '\x00', len);
    memcpy(d, data, s);

    //pad appropriately
    d[s] = 0x80;
    i = 8*s;
    memcpy(&d[len-8], &i, 4);

    for (b=0; b < len/64; b++) {
        memcpy(curb, d+(b*64), 64);
        for (i=0; i< 4; i++) {
            k = rot[4][i];
            l = rot[5][i];
            for(j=0; j < 16; j++) {
                m = (k*j + l) % 16;
                n = block[1] + ROL(block[0] + funcs[i](block[1],block[2],block[3]) +
                        md5table[j+16*i] + curb[m], rot[i][j%4]);
                block[0] = block[3];
                block[3] = block[2];
                block[2] = block[1];
                block[1] = n;
            }
        }
        for (i=0; i < 4; i++) {
            final[i] += block[i];
            block[i] = final[i];
        }
    }
    memcpy(out,final,16);
}
