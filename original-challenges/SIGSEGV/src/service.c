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
#include "service.h"
#include "trusted.h"

#define FLAG_PAGE 0x4347C000

char *responses[] = {
    "It's all just electrons.",
    "TOO MANY SECRETS",
    "It's a living.",
    "Mess with the best...",
    "You can't stop the signal, Mal.",
};

void scramble(uint8_t *in, uint8_t *out, size_t len) {
    uint8_t state[256] = {0};
    uint8_t *key = in; //our data is the key!
    uint32_t i,j,k,l;
    char c;


    for (i=0, j=255; i < 256; i++,j--) {
        state[i] = j;
    }

    for (i = 0, j = 0; i < 256; i++) {
        j = (j + state[i] + key[i%len]) % 256;
        l = state[i];
        state[i] = state[j];
        state[j] = l;
    }

    for (i = 0, j = 0, k = 0; i < len; i++) {
        c = *in++;
        k = (k+1) % 256;
        j = (j+state[k]) % 256;

        l = state[k];
        state[k] = state[j];
        state[j] = l;

        out[k%16] ^= c ^ state[(state[k]+state[j])%256];

        //note: if len < 16, out will contain NULLs...

    }
}

int run_seg(segnode_t *curnode) {
    char *n;
    char *d;
    int i;

    if (!(n = calloc(MEMBERSIZE(seg_t,name)))) {
        TERM(SEGERR,3);
    }

    if (!(d = calloc(MEMBERSIZE(seg_t,desc)))) {
        TERM(SEGERR,3);
    }

    do { 
        //could overflow if not patched
        strcpy(n,curnode->s->name);
        strcpy(d,curnode->s->desc);
        SSENDL(strlen(n),n);
        SSENDL(strlen(d),d);
        //note, this may not work on some platforms without a cache flush
        //surprisingly, this can indeed crash if f()
        //contains unsafe code.
        i = curnode->f();
        SSENDL(strlen(responses[i-1]),responses[i-1]); //gogogo
    } while ((curnode = curnode->next));

    free(n);
    free(d);
    return 0;
}

int load_seg(segnode_t *curnode) {
    int err = 0;

    do {

        ALLOC(1,(void**)&(curnode->f),MEMBERSIZE(seg_t,code));

        memcpy((void *)curnode->f,curnode->s->code,MEMBERSIZE(seg_t,code));

    } while ((curnode = curnode->next));

    return err;
}

int sanitycheck(seg_t *s) {
    return !(strlen(s->name) > 0 && strlen(s->desc) > 0);
}

int validate_seg(segnode_t *curnode) {
    uint8_t res[17];
    int err = 0;
    int i = 0;
    int j = 0;

    do {

        //segs 1 and 2 are allowed to have null names/desc!
        if (j++ > 1) {
            if ((err = sanitycheck(curnode->s)))
                goto flail;
        #ifndef PATCHED_2
                goto flail;
        #endif
        }

        memset(res,0,sizeof(res));
        scramble(curnode->s->code, res, MEMBERSIZE(seg_t,code));

        #ifndef PATCHED_1
        for (i=0; i < NUM_TRUSTED && (err = strncmp((char*)res,(char*)trusted[i],16)); i++);
        #else
        for (i=0; i < NUM_TRUSTED && (err = memcmp(res,trusted[i],16)); i++);
        #endif
        if (err)
            goto flail;
        
    } while ((curnode = curnode->next));

flail:
    return err;
}

segnode_t *recv_seg() {
    int i;
    uint32_t nsegs = 0;
    segnode_t *head = NULL;
    segnode_t *curnode = NULL;
    segnode_t *lastnode = NULL;
    seg_t *new = NULL;


    RECV(sizeof(nsegs),(char *)&nsegs);

    if (nsegs == 0 || nsegs > MAX_SEG_SIZE) {
        TERM(SEGERR,1);
    }

    for (i = 0; i < nsegs; i++) {


        if (!(new = calloc(sizeof(seg_t)))) {
            TERM(SEGERR,2);
        }

        if (!(curnode = calloc(sizeof(segnode_t)))) {
            TERM(SEGERR,2);
        }

        curnode->s = new;


        RECV(sizeof(seg_t),(char *)curnode->s);

        if (curnode->s->size != MEMBERSIZE(seg_t,code)) {

            TERM(SEGERR,2);
        }

        curnode->s->name[MEMBERSIZE(seg_t,name)-1] = '\0';
        curnode->s->desc[MEMBERSIZE(seg_t,desc)-1] = '\0';

        if (lastnode)
            lastnode->next = curnode;
        else
            head = curnode;

        lastnode = curnode;
    }

    //should never happen
    if (!head) {
        TERM(SEGERR,3);
    }
    return head;
}

int main(void) {
    segnode_t *head = NULL;
    segnode_t *prev = NULL;
    int err = 0;
    uint32_t *flag = (uint32_t*)FLAG_PAGE;
    uint32_t val = flag[0]^flag[1]^flag[2]^flag[3];

    SSEND(sizeof(val),(char*)&val);

    head = recv_seg();

    if (validate_seg(head)) {
        err = 1;
        goto done;
    }

    if (load_seg(head)) {
        err = 2;
        goto done;
    }

    run_seg(head);

done:
    do { 
        if (prev)
            free(prev);

        free(head->s);
        DEALLOC(head->f,MEMBERSIZE(seg_t,code));
        prev = head;
    } while ((head = head->next));

    free(prev);

    LOG(SEGDONE);
    return err;
}
