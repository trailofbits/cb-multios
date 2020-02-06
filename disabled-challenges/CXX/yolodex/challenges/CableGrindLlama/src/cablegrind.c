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

#include "cgc_libc.h"
#include "cgc_cablegrind.h"
#include "cgc_libdupe.h"
#include "cgc_cablegrindprotos.h"
#include "cgc_phydissectors.h"

void (*phy_dissectors[]) (uint8_t *payload, int size) = {
                                cgc_process_llama
};

void cgc_process_llama(uint8_t *payload, int size) {
    llama_hdr_t *hdr = (llama_hdr_t*)payload;

    if (sizeof(llama_hdr_t) > size)
        return;
    LOG("\n\n===llama===\n\n")

    if (hdr->type < sizeof(llama_dissectors)/sizeof(llama_dissectors[0])) {
        size -= sizeof(llama_hdr_t);
        payload += sizeof(llama_hdr_t);
        if (size > 0)
            llama_dissectors[hdr->type](&payload,&size);
    }
}

void cgc_process_dupe(dupefile_t *f) {
    dupepkt_t *cur = NULL;
    LOG("Starting dissection...")
    while ((cur = cgc_dupe_next(f)) && cur != NULL) {
        LOG("\n\n====New Packet====");
        if (cur->hdr.size > f->framelen || f->captype >= sizeof(phy_dissectors)/sizeof(phy_dissectors[0]))
            break;
        phy_dissectors[f->captype](cur->payload,cur->hdr.size);
    }
    LOG("\n\n===Dissection finished===");
}
