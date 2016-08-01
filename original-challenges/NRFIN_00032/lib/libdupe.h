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


#ifndef LIBDUPE_H
#define LIBDUPE_H

#define MAX_DUPE_SIZE 3*1024*1024


typedef struct dupefile {
    uint32_t version;
    uint32_t captype;
    int caplen;
    int framelen;
    uint32_t idx;
    uint32_t heaptype;
    uint8_t data[0];
} dupefile_t;

typedef struct dupepkt_hdr {
    uint32_t timestamp;
    int size;
} dupepkt_hdr_t;

typedef struct dupepkt {
    dupefile_t *parent;
    dupepkt_hdr_t hdr;
    uint8_t payload[0];
} dupepkt_t;

/**
 * Open a DUPE file stored in buffer
 *
 * @param data Buffer where DUPE file is stored
 * @return Open dupefile_t
 */
dupefile_t *dupe_open(uint8_t *data);

/**
 * Get next DUPE packet from file
 *
 * @param f Open DUPE file
 * @return New dupepkt_t*
 */
dupepkt_t *dupe_next(dupefile_t *f);

/**
 * Free outstanding DUPE packet
 *
 * @param pkt DUPE pkt
 */
void dupe_free(dupepkt_t *pkt);

/**
 * Free outstanding DUPE file
 *
 * @param f Open DUPE file
 */
void dupe_close(dupefile_t *f);
#endif
