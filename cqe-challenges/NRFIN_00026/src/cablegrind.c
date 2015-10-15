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
#include "cablegrind.h"
#include "libdupe.h"
#include "cablegrindprotos.h"
#include "phydissectors.h"

void (*phy_dissectors[]) (uint8_t *payload, int size) = {
                                process_rofl,
                                process_lol
};

void process_rofl(uint8_t *payload, int size) {
    rofl_hdr_t *hdr = (rofl_hdr_t*)payload;

    if (sizeof(rofl_hdr_t) > size)
        return;
    LOG("\n\n===rofl===\n\n")

    #ifdef PATCHED
    if (hdr->type < (sizeof(rofl_dissectors)/sizeof(rofl_dissectors[0]))) {
    #else
    if (hdr->type < sizeof(rofl_dissectors)) {
    #endif
        size -= sizeof(rofl_hdr_t);
        payload += sizeof(rofl_hdr_t);
        if (size > 0)
            rofl_dissectors[hdr->type](&payload,&size);
    }
}

void process_lol(uint8_t *payload, int size) {
    lol_hdr_t *hdr = (lol_hdr_t*)payload;

    if (sizeof(lol_hdr_t) > size)
        return;

    LOG("\n\n===lol===\n\n")

    #ifdef PATCHED
    if (hdr->type < (sizeof(lol_dissectors)/sizeof(lol_dissectors[0]))) {
    #else
    if (hdr->type < sizeof(lol_dissectors)) {
    #endif
        size -= sizeof(lol_hdr_t);
        payload += sizeof(lol_hdr_t);
        if (size > 0)
            lol_dissectors[hdr->type](&payload,&size);
    }
}

void process_dupe(dupefile_t *f) {
    dupepkt_t *cur = NULL;
    LOG("Starting dissection...")
    while ((cur = dupe_next(f)) && cur != NULL) {
        LOG("\n\n====New Packet====");
        #ifdef PATCHED
        if (cur->hdr.size > f->framelen || f->captype >= (sizeof(phy_dissectors)/sizeof(phy_dissectors[0])))
        #else
        if (cur->hdr.size > f->framelen || f->captype > sizeof(phy_dissectors))
        #endif
            break;
        phy_dissectors[f->captype](cur->payload,cur->hdr.size);
    }
    LOG("\n\n===Dissection finished===");
}
