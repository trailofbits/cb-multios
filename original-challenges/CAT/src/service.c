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

#include "service.h"


// Assumption: each access is 4B (the word size) in length.
bool access_check(byte_t *loc, byte_t *bgn, byte_t *end) {
    if ((loc >= bgn && loc <= end) || // standard
        (loc+(sizeof(size_t)-1) >= bgn && loc+(sizeof(size_t)-1) <= end)) { // offcut up to 3 bytes
        return TRUE;
    }
    return FALSE;
}


/**
 * Write a packet to the wire.
 *
 * @param pkt Pointer the packet struct to be serialized & sent.
 * @param resp Pointer to a packet_t that is to be populated with the response.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int packet_send(packet_t *resp) {

    int ret = SUCCESS;

    CHK_SUCCESS(
            send_bytes(STDOUT, (char *)resp, sizeof(packet_t)), 
            "failed to send packet\n");

bail:
    return ret;
}


/**
 * Read a packet off the wire.
 *
 * @param pkt Pointer the packet struct to be populated.
 * @param resp Pointer to a packet_t that is to be populated with the response.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int packet_recv(packet_t *req) {

    int ret = SUCCESS;

    // These things should never happen.
    if ((&rx_buf[BUF_RX_SZ] - rx_buf_cursor + sizeof(packet_t)) > BUF_RX_SZ) {
        err("rx_buf_cursor is in a place it shouldn't be (0x%08x), sizeof(packet_t): %d\n", 
            rx_buf_cursor, sizeof(packet_t));
    }

    // If we've read all the packets in the recv buffer, then:
    if (rx_buf_cursor == &rx_buf[BUF_RX_SZ]) {
        // In this case, we need to read more off the wire...
        CHK_SUCCESS(
            recv_bytes(STDIN, (char *)&rx_buf, BUF_RX_SZ), 
            "failed to recv additional bytes\n");
        // ...and reset rx_buf_cursor.
        rx_buf_cursor = rx_buf;
    }

    // We have at least one more packet_t to read out of the recv buffer.
    memcpy(req, rx_buf_cursor, sizeof(packet_t));
    rx_buf_cursor += sizeof(packet_t);

bail:
    return ret;
}


/**
 * Query against the "normal" region.
 *
 * @param req Pointer to a packet_t containing the normal request.
 * @param resp Pointer to a packet_t that is to be populated with the response.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int do_normal(packet_t *req, packet_t *resp) {
    dbg("%s()\n", __func__);

    int ret = SUCCESS;

    // "Normal" permits access to:
    // 1) R: BLACKLIST: flag page
    // 2) W: WHITELIST: .text, & (if unpatched) .data/bss. Writing to .text 
    //  would obviously cause a SIGSEGV, but that doesn't get competitors 
    //  anything.  We don't allow WRITES to the stack.  SC needs to go on heap.

    if (A_READ == req->inst.action) {

        // blacklist the FLAG page
        if (OP2_MEM == req->inst.op2type && 
            TRUE == access_check(
                (byte_t *)req->inst.src, 
                FLAG_PAGE_BGN, 
                FLAG_PAGE_END)) {
            dbg("attempt to read from FLAG page; returning error packet\n");
            resp->status = S_ERROR;
            goto bail;
        }

        // Reads from an immediate don't really make much sense; they just 
        // result in a reflection of the immediate.
        resp->inst.dst = (OP2_IMM == req->inst.op2type) ? 
            (req->inst.src) : (*(uint32_t *)req->inst.src);

    } else { // A_WRITE
        
        // To simplify things, disallow OP2_MEM.
        if (OP2_IMM != req->inst.op2type) {
            dbg("attempted NORMAL + WRITE with OP2_MEM; returning error packet\n");
            resp->status = S_ERROR;
            goto bail;
        }

        // For dst, apply blacklist per above.
        if (FALSE == access_check( // if it's not in the .text section...
                (byte_t *)req->inst.dst,
                TEXT_BGN,
                TEXT_END) 
#ifndef PATCHED_1 // Data section write access only allowed on unpatched.
            &&
            FALSE == access_check( // ...and it's not in the data section...
                (byte_t *)req->inst.dst,
                DATA_BGN,
                DATA_END)
#endif
            ) {
            // ...reject it.
            dbg("attempted NORMAL + WRITE to outside allowed bounds\n");
            resp->status = S_ERROR;
            goto bail;
        }

        // Otherwise we're good and we do the WRITE.
        *(uint32_t *)req->inst.dst = req->inst.src;
    }

    resp->status = S_RESP;

bail:
    return ret;
}


/**
 * Query against the "scratch" region.
 *
 * @param req Pointer to a packet_t containing the scratch request.
 * @param resp Pointer to a packet_t that is to be populated with the response.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int do_scratch(packet_t *req, packet_t *resp) {
    dbg("%s()\n", __func__);

    int ret = SUCCESS;
    byte_t *loc = NULL, *loc2 = NULL;

    // Times when we could R/W outside of the SCRATCH buffer:
    // READ, IMM: (none)
    // READ, MEM: src
    // WRITE, IMM: dst
    // WRITE, MEM: src & dst

    if (A_READ == req->inst.action && OP2_IMM == req->inst.op2type) {
       // READ, IMM: (none)
    } else if (A_READ == req->inst.action && OP2_MEM == req->inst.op2type) {
        // READ, MEM: src 
        loc = (byte_t *)req->inst.src; 
    } else if (A_WRITE == req->inst.action && OP2_IMM == req->inst.op2type) {
        // WRITE, IMM: dst
        loc = (byte_t *)req->inst.dst; 
    } else if (A_WRITE == req->inst.action && OP2_MEM == req->inst.op2type) {
        // WRITE, MEM: src & dst
        loc = (byte_t *)req->inst.src;
        loc2 = (byte_t *)req->inst.dst;
    } else {
        err("this should never happen\n");
    }

    // This is pretty hacky.
    if (NULL != loc &&
        FALSE == access_check(loc, buf_scratch, &buf_scratch[SZ_SCRATCH])) { 
        dbg("attempt to R/W @ %p, which is outside of SCRATCH region [%p - %p]; returning error packet\n", 
            loc, buf_scratch, &buf_scratch[SZ_SCRATCH]);
        resp->status = S_ERROR;
        goto bail;
    }

    if (NULL != loc2 && 
        FALSE == access_check(loc2, buf_scratch, &buf_scratch[SZ_SCRATCH])) {
        dbg("attempt to R/W @ %p, which is outside of SCRATCH region [%p - %p]; returning error packet\n", 
            loc2, buf_scratch, &buf_scratch[SZ_SCRATCH]);        
        resp->status = S_ERROR;
        goto bail;
    }

    dbg("req->inst.dst = 0x%08x, req->inst.src = 0x%08x\n", req->inst.dst, req->inst.src);

    if (A_READ == req->inst.action) {
        resp->inst.dst = (OP2_IMM == req->inst.op2type) ? 
            (req->inst.src) : (*(uint32_t *)req->inst.src);
        dbg("READ; value = 0x%08x\n", resp->inst.dst);
    } else { // Only other option is A_WRITE.
        //dbg("WRITE @ %p; before value = 0x%08x\n", (uint32_t *)req->inst.dst, *(uint32_t *)req->inst.dst);
        *(uint32_t *)req->inst.dst = (OP2_IMM == req->inst.op2type) ? 
            (req->inst.src) : (*(uint32_t *)req->inst.src);
        //dbg("WRITE @ %p; after  value = 0x%08x\n", (uint32_t *)req->inst.dst, *(uint32_t *)req->inst.dst);
    }

    resp->status = S_RESP;

bail:
    return ret;
}


/**
 * Query against the "static" region.
 * Involves unnecessarily complex code.
 *
 * @param req Pointer to a packet_t containing the static request.
 * @param resp Pointer to a packet_t that is to be populated with the response.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int do_static(packet_t *req, packet_t *resp) {
    dbg("%s()\n", __func__);

    int ret = SUCCESS;

    // We only allow READs here and we don't care about OP2 type, both are 
    // assumed be idxs into the "static" region(s).
    if (A_READ != req->inst.action) {
        dbg("malformed packet; returning error packet\n");
        resp->status = S_ERROR;
        goto bail;
    }

    size_t idx = req->inst.src;
    if (STATIC_MAX_SWITCH >= idx) {
        resp->inst.dst = static_switch(idx);
        resp->status = S_RESP;
    } else {
        dbg("idx out of range; returning error packet\n");
        resp->status = S_ERROR;
        goto bail;
    }

bail:
    return ret;
}


/**
 * Generate a "bad request" response packet for the corresponding request.
 *
 * @param req Pointer to a packet_t containing the bad request.
 * @param resp Pointer to a packet_t that is to be populated with the response.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int bad_request(packet_t *req, packet_t *resp) {
    dbg("%s()\n", __func__);

    int ret = SUCCESS;

    resp->status = S_ERROR;

bail:
    return ret;
}


/**
 * Allocate heap space for SCRATCH queries.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int init(void) {
    dbg("%s()\n", __func__);

    int ret = SUCCESS;

    rx_buf_cursor = &rx_buf[BUF_RX_SZ];

    // Allocate 'scratch' (R/W/X) space.
    CHK_SUCCESS(
        allocate(SZ_SCRATCH, TRUE, (void **)&buf_scratch), 
        "failed to allocate scratch buffer\n");

    dbg("buf_scratch @ %p\n", buf_scratch);

bail:
    return ret;
}


/**
 * The main loop.
 *
 * @return Error status.
 */
int main(void) {
    dbg("%s()\n", __func__);

    int ret = SUCCESS;
    packet_t req, resp;
    int (* volatile *loc_func_ptr[3])(packet_t *req, packet_t *resp);

    // For leakage, we need something on main()'s stack frame that points to 
    // the .data segment.  We use some (otherwise unnecessary) indirection.
    loc_func_ptr[0] = (int (**)(packet_t *, packet_t *))MAGIC_DATA_BEFORE;
    loc_func_ptr[1] = &func_ptr[1]; // Read this to calculate base addr of .data.
    loc_func_ptr[2] = (int (**)(packet_t *, packet_t *))MAGIC_DATA_AFTER;

    dbg("LEAK: loc_func_ptr[1] @ 0x%08x, func_ptr[1] @ 0x%08x\n", 
        &loc_func_ptr[1], &func_ptr[1]);
    
    CHK_SUCCESS(init(), "init failed\n");

    // Main Loop
    while (TRUE) {

        func_ptr[0] = (int (*)(packet_t *, packet_t *))MAGIC_PTR_BEFORE;
        func_ptr[2] = (int (*)(packet_t *, packet_t *))MAGIC_PTR_AFTER;

        CHK_SUCCESS(packet_recv(&req), "could not receive packet\n");

        // Check for magics.
        if (req.status == S_EXIT) { 
            dbg("got EXIT message\n");
            goto bail; 
        }

        memset((void *)&resp, 0, sizeof(packet_t));
        resp.seq = req.seq;

        // Generic validation
        if ( S_REQ != req.status ||
            (A_READ != req.inst.action && A_WRITE != req.inst.action) ||
            (OP2_IMM != req.inst.op2type && OP2_MEM != req.inst.op2type)) {
            dbg("malformed packet; sending error packet\n");
            resp.status = S_ERROR;
            goto respond;
        }

        dbg("req.type = %d\n", req.type);
        switch (req.type) {
            case X_NORMAL: func_ptr[1] = &do_normal; break;
            case X_SCRATCH: func_ptr[1] = &do_scratch; break;
            case X_STATIC: func_ptr[1] = &do_static; break;
            case X_PREV: break; // Leave func_ptr[1] alone.
            default: func_ptr[1] = &bad_request; break;
        }

        dbg("about to call handler @ 0x%08x\n", func_ptr[1]);

        CHK_SUCCESS(func_ptr[1](&req, &resp), "HANDLER failure\n");

respond:
        CHK_SUCCESS(packet_send(&resp), "could not send packet\n");
    }

bail:
    return ret;
}

