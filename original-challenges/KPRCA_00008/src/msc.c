/*
 * Author: Andrew Wesie <andrew.wesie@kapricasecurity.com>
 *
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
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "endian.h"
#include "msc.h"
#include "usb.h"

//#define NUM_BLOCKS 262144
#define NUM_BLOCKS 128
#define BLOCK_SIZE 512

// aligned for SSE copies
static uint8_t memory[NUM_BLOCKS * BLOCK_SIZE] __attribute__((__aligned__(16)));

void *memcpy_fast(void *dst, void *src, size_t length);
static int rbc_handle_packet(msc_t *msc, uint8_t *data, size_t length);
static int rbc_handle_data(msc_t *msc, uint8_t *data, size_t length);

int msc_init(msc_t *msc)
{
    memset(msc, 0, sizeof(msc_t));
    msc->state = MSC_ST_IDLE;
    msc->memory = memory;
    return 1;
}

int msc_handle_ep0(usb_t *usb, urb_t *urb)
{
    if (urb->setup[0] == 0xA1)
    {
        if (urb->setup[1] == 0xFE) /* Get Max LUN */
        {
            uint8_t data = 1;
            usb_send_reply(usb, urb, 0, 1);
            usb->send(&data, 1);
            return 1;
        }
    }
    else if (urb->setup[0] == 0x21)
    {
        if (urb->setup[1] == 0xFF) /* Reset */
        {
            usb_send_reply(usb, urb, 0, 0);
            return 1;
        }
    }
    return 0;
}

int msc_handle_urb(usb_t *usb, urb_t *urb)
{
    msc_t *msc = &usb->msc;
#ifdef DEBUG
    fprintf(stderr, "URB (st=%d,seq=%d,dir=%d,ep=%02x,flags=%04x,length=%d,interval=%d)\n", msc->state, urb->seqnum, urb->direction, urb->endpoint, urb->flags, urb->length, urb->interval);
#endif

    if (msc->state == MSC_ST_IDLE)
    {
        if (urb->direction != DIR_OUT)
            // XXX phase error
            return 0;

        if (urb->length < 31)
            return 0;
        
        cbw_t *cbw = (cbw_t *)urb->data;
        if (cbw->magic != 0x43425355)
            return 0;

        msc->cbw = *cbw;
        msc->count = 0;
        msc->status = !rbc_handle_packet(msc, cbw->cb, cbw->cb_length);

        usb_send_reply(usb, urb, 0, urb->length);
    }
    else if (msc->state == MSC_ST_OUT)
    {
        if (urb->direction != DIR_IN)
            // XXX phase error
            return 0;

        uint32_t length = urb->length;
        if (length > msc->out_length)
            length = msc->out_length;
        
        usb_send_reply(usb, urb, 0, length);
        usb->send(msc->out_buffer + msc->count, length);
        
        msc->count += length;
        msc->out_length -= length;

        if (msc->out_length == 0)
            msc->state = MSC_ST_STATUS;
    }
    else if (msc->state == MSC_ST_IN)
    {
        if (urb->direction != DIR_OUT)
            // XXX phase error
            return 0;

        if (!rbc_handle_data(msc, urb->data, urb->length))
        {
            msc->status = 1;
            msc->state = MSC_ST_STATUS;
            usb_send_reply(usb, urb, 0, 0);
        }
        else
        {
            usb_send_reply(usb, urb, 0, urb->length);
        }
    }
    else if (msc->state == MSC_ST_STATUS)
    {
        if (urb->direction != DIR_IN)
            // XXX phase error
            return 0;

        if (urb->length < sizeof(csw_t))
            // XXX phase error
            return 0;

        msc->csw.magic = 0x53425355;
        msc->csw.tag = msc->cbw.tag;
        msc->csw.residue = msc->cbw.data_length - msc->count;
        msc->csw.status = msc->status;

#ifdef DEBUG
        fprintf(stderr, "CSW residue=%d, status=%d\n", msc->csw.residue, msc->csw.status);
#endif

        usb_send_reply(usb, urb, 0, sizeof(csw_t));
        usb->send(&msc->csw, sizeof(csw_t));

        msc->state = MSC_ST_IDLE;
    }
    return 1;
}

static void msc_send(msc_t *msc, const uint8_t *buffer, size_t length, unsigned int flags)
{
    msc->out_flags = flags;
    msc->out_length = length;
    msc->out_buffer = buffer;
    msc->state = MSC_ST_OUT;

    if (msc->out_length > msc->cbw.data_length)
        msc->out_length = msc->cbw.data_length;
}

/*
 * Reduced Block Command
 *
 * Required commands:
 *  - READ (10): 0x28
 *  - READ CAPACITY: 0x25
 *  - START STOP UNIT: 0x1B
 *  - SYNCHRONIZE CACHE: 0x35
 *  - WRITE (10): 0x2A
 *  - VERIFY (10): 0x2F
 * (the following commands are from SPC-2)
 *  - INQUIRY: 0x12
 *  - MODE SELECT: 0x55
 *  - MODE SENSE: 0x5A
 *  - TEST UNIT READY: 0x00
 *  - WRITE BUFFER: 0x3B
 */

static const uint8_t inquiry_data[] = {
    0x0E, 0x00, 0x04, 0x02, 0x20, 0x00, 0x00, 0x00, 
    // Vendor identification
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // Product identification
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    // Product revision
    0x00, 0x00, 0x00, 0x00,
};

static int rbc_handle_packet(msc_t *msc, uint8_t *data, size_t length)
{
    uint8_t *buffer = msc->out_static;

    /* clear state */
    msc->state = MSC_ST_STATUS;
    msc->out_length = 0;
    msc->out_buffer = NULL;
    msc->out_flags = 0;

    switch (data[0])
    {
    case 0x00: /* TEST UNIT READY */
        /* just acknowledge with status 0x00 */
        msc->state = MSC_ST_STATUS;
        break;
    case 0x12: /* INQUIRY */
        msc_send(msc, inquiry_data, data[4] < sizeof(inquiry_data) ? data[4] : sizeof(inquiry_data), 0);
        break;
    case 0x25: /* READ CAPACITY */
        *(uint32_t *)&buffer[0] = htobe32(NUM_BLOCKS-1);
        *(uint32_t *)&buffer[4] = htobe32(BLOCK_SIZE);
        msc_send(msc, buffer, 8, 0);
        break;
    case 0x28: { /* READ (10) */
        uint32_t lba = be32toh(*(uint32_t *)&data[2]);
        uint16_t len = be16toh(*(uint16_t *)&data[7]);
#ifdef DEBUG
        fprintf(stderr, "read from %d, %d bytes\n", lba * BLOCK_SIZE, len * BLOCK_SIZE);
#endif
        if (lba > NUM_BLOCKS)
            return 0;
        else if (lba + len > NUM_BLOCKS)
            return 0;
        msc_send(msc, &msc->memory[lba * BLOCK_SIZE], len * BLOCK_SIZE, 0);
        break;
    }
    case 0x2A: { /* WRITE (10) */
        uint32_t lba = be32toh(*(uint32_t *)&data[2]);
        uint16_t len = be16toh(*(uint16_t *)&data[7]);
#ifdef DEBUG
        fprintf(stderr, "write to %d, %d bytes\n", lba * BLOCK_SIZE, len * BLOCK_SIZE);
#endif
        if (lba > NUM_BLOCKS)
            return 0;
        else if (lba + len > NUM_BLOCKS)
            return 0;
        msc->state = MSC_ST_IN;
        msc->in_state.write.lba = lba;
        msc->in_state.write.length = len * BLOCK_SIZE;
        break;
    }
    case 0x5A: /* MODE SENSE */
        if (data[2] == 0x3F || data[2] == 0x06)
        {
            memset(buffer, 0, 18);
            *(uint16_t *)&buffer[0] = htobe16(16);
            buffer[8] = 0x86;
            buffer[9] = 0x08;
            buffer[10] = 0x01;
            *(uint16_t *)&buffer[11] = htobe16(BLOCK_SIZE);
            buffer[13] = 0;
            *(uint32_t *)&buffer[14] = htobe32(NUM_BLOCKS);
            msc_send(msc, buffer, 18, 0);
        }
        break;
    case 0x1B: /* START STOP UNIT */
    case 0x2F: /* VERIFY (10) */
    case 0x35: /* SYNCHRONIZE CACHE */
    case 0x3B: /* WRITE BUFFER */
    case 0x55: /* MODE SELECT */
        /* XXX these are not used by Linux driver, so left unimplemented */
    default:
        msc->status = 1;
        msc_send(msc, NULL, 0, 0);
        break;
    }

    return 1;
}

static int rbc_handle_data(msc_t *msc, uint8_t *data, size_t length)
{
    switch (msc->cbw.cb[0])
    {
    case 0x2A: /* WRITE (10) */
        if (msc->count + length > msc->in_state.write.length)
            length = msc->in_state.write.length - msc->count;

        memcpy_fast(&msc->memory[msc->in_state.write.lba * BLOCK_SIZE + msc->count], data, length);
        msc->count += length;
        if (msc->count == msc->in_state.write.length)
            msc->state = MSC_ST_STATUS;
        break;
    default:
        return 0;
    }

    return 1;
}
