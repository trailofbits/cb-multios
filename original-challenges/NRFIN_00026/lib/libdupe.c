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
#include "libdupe.h"

dupefile_t * dupe_open(uint8_t *data) {
    dupefile_t *f = (dupefile_t *)data;
    
    if (f->version > 3 || f->idx >= f->caplen)
        return NULL;

    if (f->caplen <= 0)
        return NULL;

    return f;
}

dupepkt_t *dupe_next(dupefile_t *f) {
    dupepkt_t *pkt = NULL;

    if (f->framelen > 65536 || f->framelen < 0)
        return NULL;

    if (f->caplen > MAX_DUPE_SIZE || f->caplen < 0)
        return NULL;

    pkt = malloc(sizeof(dupepkt_hdr_t)+f->framelen);
    if (!pkt)
        return NULL;

    if (f->idx+sizeof(dupepkt_hdr_t) > f->caplen) {
        free(pkt);
        return NULL;
    }

    pkt->parent = f;
    memcpy(&pkt->hdr, f->data+f->idx, sizeof(dupepkt_hdr_t));
    f->idx += sizeof(dupepkt_hdr_t);

    if (pkt->hdr.size <= 0 || f->idx+pkt->hdr.size > f->caplen || pkt->hdr.size > f->framelen) {
        free(pkt);
        return NULL;
    }

    memcpy(pkt->payload, f->data+f->idx, pkt->hdr.size);

    f->idx += pkt->hdr.size;

    return pkt;
}

void dupe_free(dupepkt_t *pkt) {
    free(pkt);
}

void dupe_close(dupefile_t *f) {
    free(f);
}
