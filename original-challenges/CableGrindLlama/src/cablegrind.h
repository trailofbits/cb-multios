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
#include <stdint.h>
#include "libdupe.h"
#ifndef CABLEGRIND_H
#define CABLEGRIND_H

#define SIZEERR "Not cool."
typedef struct llama_hdr {
    uint64_t to;
    uint64_t from;
    uint32_t time;
    uint32_t type;
} llama_hdr_t;

/**
 * Process Regular Output For LAN Packet
 *
 * @param payload Payload buffer to process
 * @param size Size of payload
 */
void process_llama(uint8_t *payload, int size);

/**
 * Process Dissector Upload Packet Encapsulation Packet
 *
 * @param f Pointer to DUPE file
 */
void process_dupe(dupefile_t *f); 
#endif
