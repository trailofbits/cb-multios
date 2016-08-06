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
#include "rle.h"


void decode(video *vid, char key){
    uint32_t i, csum = 0, j, cur;

    if (key != vid->key) {
        if(vid->decbuf && vid) {
            DEALLOC((void*)vid->decbuf, vid->dlen);
            vid->decbuf = NULL;
            vid->dlen = 0;
        }
        return;
    }

    vid->dlen = 0;

    for (i=0; i < vid->elen/4; i++) 
        csum += *(((uint32_t*)vid->encbuf)+i) ^ (key<<24|key<<16|key<<8|key);
    
    if (csum != vid->csum) {
        return;
    }

    //now run over buffer and analyze how big decompressed vid will be
    for (i=0; i < vid->elen; i+=2) { 
        vid->dlen += (uint8_t)(vid->encbuf[i]^vid->key);
        vid->dlen++;
    }

    ALLOC(0, (void**)&(vid->decbuf), vid->dlen);

    //now, actually decode/decompress
    cur = 0;
    for (i=0; i < vid->elen; i+=2) {
        for(j=0; j <= (uint8_t)(vid->encbuf[i]^vid->key); j++)
            vid->decbuf[cur++] = vid->encbuf[i+1]^vid->key;
    }

}
