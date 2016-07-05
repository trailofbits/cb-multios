/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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
#include <stdlib.h>
#include <string.h>

#include "link.h"

void link_send(unsigned channel, unsigned length, const unsigned char *payload)
{
    size_t bytes;
    union {
        link_hdr_t hdr;
        unsigned char rawdata[LINK_PACKET_SIZE];
    } pkt;

    pkt.hdr.length = length;
    pkt.hdr.channel = channel;
    pkt.hdr.flow = 1;
    pkt.hdr.sbz = 0;

    if (length > LINK_PAYLOAD_SIZE)
        length = LINK_PAYLOAD_SIZE;

    memcpy(pkt.hdr.payload, payload, length);
    transmit(STDOUT, pkt.rawdata, length + sizeof(link_hdr_t), &bytes);
}

int link_recv(unsigned *channel, unsigned *length, unsigned char *payload)
{
    size_t bytes;
    link_hdr_t hdr;

retry:
    if (receive(STDIN, &hdr, sizeof(link_hdr_t), &bytes) != 0 || bytes < sizeof(link_hdr_t))
        return -1;
    
    if (hdr.length > LINK_PAYLOAD_SIZE)
        // bad packet, try again
        goto retry;

    if (receive(STDIN, payload, hdr.length, &bytes) != 0 || bytes != hdr.length)
        return -1;

    *channel = hdr.channel;
    *length = hdr.length;

    return 0;
}
