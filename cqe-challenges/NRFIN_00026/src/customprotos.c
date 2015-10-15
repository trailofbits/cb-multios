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
#include "customprotos.h"
#include "cablegrind.h"


static uint32_t ntohl(uint32_t n) {
    uint8_t *p = (uint8_t*)&n;
    return p[0]<<24 | p[1]<<16 | p[2]<<8 | p[3];
}

STACKPROTECTINIT
void process_trolololo(uint8_t **payload, int *size) {
void (*next_dissectors[]) (uint8_t **, int *) = {process_trolololo};
STACKPROTECTADD
    int i;
    uint32_t buf[MAX_TRL_BUF_SIZE];
    uint32_t bsize = 0;
    uint32_t *src = *(uint32_t**)payload;
    SSENDL(sizeof("===trolololo===")-1,"===trolololo===");

    if (*size < sizeof(uint32_t)) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    bsize = src[0];
    *payload += sizeof(uint32_t);
    *size -= sizeof(uint32_t);

    #ifndef PATCHED
    if (bsize > MAX_TRL_PKT_SIZE) {
    #else
    if (bsize > MAX_TRL_BUF_SIZE) {
    #endif
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    if (*size < (int)(bsize*sizeof(uint32_t))) {
        SSENDL(sizeof(SIZEERR)-1,SIZEERR);
        _terminate(28);
    }

    for (i = 1; i < bsize+1; i++) {
        buf[i-1] = ntohl(src[i]);
    }

STACKPROTECTCHK
}
