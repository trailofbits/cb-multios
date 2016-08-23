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
#include "service.h"

uint32_t enckey[SZ_ENCKEY] = { 0, 0, 0, 0 };
uint32_t auth_token = { 0 };
msg msgNull = { 0 };


__attribute__ ((regparm (3))) int op_add(uint32_t x, uint32_t y, uint8_t nmb) {
    DBG("\n");

    int ret = SUCCESS;
    msg resp = msgNull;

    resp.dst = PIPE_CB1_A;
    resp.op = OP_ADD;

    uint32_t answer = x + y;
    uint64_t result = (((uint64_t)answer) << 32 | auth_token);

    DBG("[D] PT result: 0x"); DBG_SIMPLE("%08x", result >> 32); DBG_SIMPLE("%08x\n", result);
    if (SUCCESS != (ret = encrypt_1block(&result, &enckey))) {
        DBG("[E] unable to encrypt result\n")
        goto bail;
    }
    DBG("[D] CT result: 0x"); DBG_SIMPLE("%08x", result >> 32); DBG_SIMPLE("%08x\n", result);

    #ifndef PATCHED_2
    if (SUCCESS != (ret = get_match_run_length(answer, auth_token, &resp.nmb))) {
        DBG("[E] failed to get match length\n")
        goto bail;
    }
    #else /* PATCHED_2 */
    if (SUCCESS != (ret = random(&nmb, sizeof(nmb), NULL))) {
        ERR("[E] couldn't get a random nmb value\n");
    }
    resp.nmb = nmb;
    #endif /* PATCHED_2 */

    resp.result = result;

    if (SUCCESS != (ret = send_bytes(PIPE_SEND_TAP, (char *)&resp, sizeof(resp)))) {
        DBG("[E] failed to send response to CLIENT\n")
        goto bail;
    }
    DBG("[D] sent:\n");
    MSG_DUMP(resp);

bail:
    return ret;
}


__attribute__ ((regparm (3))) int op_sub(uint32_t x, uint32_t y, uint8_t nmb) {
    DBG("\n");

    int ret = SUCCESS;
    msg resp = msgNull;

    resp.dst = PIPE_CB1_A;
    resp.op = OP_SUB;

    uint32_t answer = x - y;
    uint64_t result = (((uint64_t)answer) << 32 | auth_token);
    DBG("[D] PT result: 0x"); DBG_SIMPLE("%08x", result >> 32); DBG_SIMPLE("%08x\n", result);
    if (SUCCESS != (ret = encrypt_1block(&result, &enckey))) {
        DBG("[E] unable to encrypt result\n")
        goto bail;
    }
    DBG("[D] CT result: 0x"); DBG_SIMPLE("%08x", result >> 32); DBG_SIMPLE("%08x\n", result);

    #ifndef PATCHED_2
    if (SUCCESS != (ret = get_match_run_length(answer, auth_token, &resp.nmb))) {
        DBG("[E] failed to get match length\n")
        goto bail;
    }
    #else /* PATCHED_2 */
    if (SUCCESS != (ret = random(&nmb, sizeof(nmb), NULL))) {
        ERR("[E] couldn't get a random nmb value\n");
    }
    resp.nmb = nmb;
    #endif /* PATCHED_2 */

    resp.result = result;

    if (SUCCESS != (ret = send_bytes(PIPE_SEND_TAP, (char *)&resp, sizeof(resp)))) {
        DBG("[E] failed to send response to CLIENT\n")
        goto bail;
    }
    DBG("[D] sent:\n");
    MSG_DUMP(resp);

bail:
    return ret;
}


__attribute__ ((regparm (3))) int op_mul(uint32_t x, uint32_t y, uint8_t nmb) {
    DBG("\n");

    int ret = SUCCESS;
    msg resp = msgNull;

    resp.dst = PIPE_CB1_A;
    resp.op = OP_MUL;

    uint32_t answer = x * y;
    uint64_t result = (((uint64_t)answer) << 32 | auth_token);
    
    DBG("[D] PT result: 0x"); DBG_SIMPLE("%08x", result >> 32); DBG_SIMPLE("%08x\n", result);
    if (SUCCESS != (ret = encrypt_1block(&result, &enckey))) {
        DBG("[E] unable to encrypt result\n")
        goto bail;
    }
    DBG("[D] CT result: 0x"); DBG_SIMPLE("%08x", result >> 32); DBG_SIMPLE("%08x\n", result);

    #ifndef PATCHED_2
    if (SUCCESS != (ret = get_match_run_length(answer, auth_token, &resp.nmb))) {
        DBG("[E] failed to get match length\n")
        goto bail;
    }
    #else /* PATCHED_2 */
    if (SUCCESS != (ret = random(&nmb, sizeof(nmb), NULL))) {
        ERR("[E] couldn't get a random nmb value\n");
    }
    resp.nmb = nmb;
    #endif /* PATCHED_2 */

    resp.result = result;

    if (SUCCESS != (ret = send_bytes(PIPE_SEND_TAP, (char *)&resp, sizeof(resp)))) {
        DBG("[E] failed to send response to CLIENT\n")
        goto bail;
    }
    DBG("[D] sent:\n");
    MSG_DUMP(resp);

bail:
    return ret;
}


__attribute__ ((regparm (3))) int op_div(uint32_t x, uint32_t y, uint8_t nmb) {
    DBG("\n");

    int ret = SUCCESS;
    msg resp = msgNull;

    resp.dst = PIPE_CB1_A;
    resp.op = OP_DIV;

    uint32_t answer = 0;

    if (y == 0) { answer = 0; } 
    else { answer = x / y; }

    uint64_t result = (((uint64_t)answer) << 32 | auth_token);
    DBG("[D] PT result: 0x"); DBG_SIMPLE("%08x", result >> 32); DBG_SIMPLE("%08x\n", result);
    if (SUCCESS != (ret = encrypt_1block(&result, &enckey))) {
        DBG("[E] unable to encrypt result\n")
        goto bail;
    }
    DBG("[D] CT result: 0x"); DBG_SIMPLE("%08x", result >> 32); DBG_SIMPLE("%08x\n", result);
    
    #ifndef PATCHED_2
    if (SUCCESS != (ret = get_match_run_length(answer, auth_token, &resp.nmb))) {
        DBG("[E] failed to get match length\n")
        goto bail;
    }
    #else /* PATCHED_2 */
    if (SUCCESS != (ret = random(&nmb, sizeof(nmb), NULL))) {
        ERR("[E] couldn't get a random nmb value\n");
    }
    resp.nmb = nmb;
    #endif /* PATCHED_2 */

    resp.result = result;

    if (SUCCESS != (ret = send_bytes(PIPE_SEND_TAP, (char *)&resp, sizeof(resp)))) {
        DBG("[E] failed to send response to CLIENT\n")
        goto bail;
    }
    DBG("[D] sent:\n");
    MSG_DUMP(resp);

bail:
    return ret;
}

// An authenticated function used to reconfigure the operations 
// (and provide type 1 PoV).
__attribute__ ((regparm (3))) int op_mod(uint32_t x, uint32_t y, uint8_t nmb) {
    DBG("\n");

    int ret = SUCCESS;
    msg resp = msgNull;
    msg ack = msgNull;
    ack.dst = PIPE_CB1_A;
    ack.op = OP_ACK;


    // We only honor requests that contain a valid auth_token.
    if (x != auth_token) {
        DBG("[D] x != auth_token; rejecting request\n");
        goto bail;
    } else {
        DBG("[D] successfully authenticated to the OP_MOD function\n");
    }

    // Okay we're authenticated.
    // y = the new function pointer
    // op = OP_MOD
    // nmb = the op index we're going to modify
    #ifndef PATCHED_1
    DBG("[D] set operation 0x%02x (%lu) to 0x%08x\n", nmb, y);
    operations[nmb] = (__attribute__ ((regparm (3))) int (*)(uint32_t x, uint32_t y, uint8_t nmb))y;
    #else /* PATCHED_1 */
    if (y == (uint32_t)operations[OP_ADD] ||
        y == (uint32_t)operations[OP_SUB] ||
        y == (uint32_t)operations[OP_MUL] ||
        y == (uint32_t)operations[OP_DIV]) {
        DBG("[D] set operation 0x%02x (%lu) to 0x%08x\n", nmb, y);
        operations[nmb] = (__attribute__ ((regparm (3))) int (*)(uint32_t x, uint32_t y, uint8_t nmb))y;
    } else {
        DBG("[D] (patched) refusing to MOD to invalid addr\n");
    }
    #endif /* PATCHED_1 */

bail:
    // Send an ACK (something in response required by TAP).
    if (SUCCESS != (ret = send_bytes(PIPE_SEND_TAP, (char *)&ack, sizeof(msg)))) {
        DBG("[E] failed to send response to CLIENT\n")
        goto bail;
    }
    DBG("[D] sent:\n");
    MSG_DUMP(ack);
    
    DBG("[D] returning from OP_MOD\n");

    return ret;
}


int negotiate(void) {
    DBG("\n");

    int ret = SUCCESS;
    size_t rnd_bytes = 0;
    uint32_t enckey_idx = 0, enckey_idx_actual = 0;
    uint32_t auth_token_idx = 0, auth_token_idx_actual = 0;
    uint32_t dummy = 0;
    msg ack = msgNull;

    if (SUCCESS != (ret = recv_bytes(PIPE_RECV, (char *)&enckey_idx, sizeof(enckey_idx)))) {
        DBG("[E] failed to recv enckey_idx from CLIENT\n");
        goto bail;
    }

    enckey_idx_actual = (enckey_idx % SZ_PAGE) & ~0xF;
    enckey[0] = *(uint32_t *)(VA_FLAG + enckey_idx_actual + sizeof(uint32_t) * 0);
    enckey[1] = *(uint32_t *)(VA_FLAG + enckey_idx_actual + sizeof(uint32_t) * 1);
    enckey[2] = *(uint32_t *)(VA_FLAG + enckey_idx_actual + sizeof(uint32_t) * 2);
    enckey[3] = *(uint32_t *)(VA_FLAG + enckey_idx_actual + sizeof(uint32_t) * 3);
    DBG("[D] enckey_idx_actual = 0x%08x; enckey = 0x%08x%08x%08x%08x\n", 
        enckey_idx_actual, enckey[0], enckey[1], enckey[2], enckey[3]);

    ack.op = OP_ACK;
    if (SUCCESS != (ret = send_bytes(PIPE_SEND_NO_TAP, (char *)&ack, sizeof(ack)))) {
        DBG("[E] failed send ACK to CLIENT\n");
        goto bail;
    }

    // We've negotiated enckey; now we need the auth token.

    auth_token_idx = *(uint32_t *)(VA_FLAG + OFF_AUTH_TOKEN_IDX);
    auth_token_idx_actual = (auth_token_idx % SZ_PAGE) & ~0xF;
    auth_token = *(uint32_t *)(VA_FLAG + auth_token_idx_actual);
    DBG("[D] auth_token_idx = 0x%08x; auth_token = 0x%08x\n", 
        auth_token_idx, auth_token);

    if (SUCCESS != (ret = send_bytes(PIPE_SEND_NO_TAP, (char *)&auth_token_idx, sizeof(auth_token_idx)))) {
        DBG("[E] failed to send auth_token_idx (0x%08x) to CLIENT\n", auth_token_idx);
        goto bail;
    }

    if (SUCCESS != (ret = recv_bytes(PIPE_RECV, (char *)&ack, sizeof(ack))) || ack.op != OP_ACK) {
        DBG("[E] failed to get ack from CLIENT\n");
        ret = ERRNO_ACK;
        goto bail;
    }

bail:
    return ret;
}


void do_exit(void) {
    DBG("\n");
    int ret = SUCCESS;

    DBG("[D] got exit() message; terminating...\n");

bail:
    _terminate(ret);
}


int main(void) {
    DBG("\n");

    int ret = SUCCESS;
    msg req = msgNull;

    // Do initial setup things.
    DBG("[D] initial setup\n");
    if (SUCCESS != (ret = negotiate())) {
        DBG("[E] failed to negotiate\n");
        ret = ERRNO_KEY_EXCHANGE;
        goto bail;
    }

    // Enter main loop.
    DBG("[D] entering main loop\n");
    while(TRUE) {
        
        // Get the request.
        req = msgNull;
        DBG("[D] waiting for REQUEST\n");
        if (SUCCESS != (ret = recv_bytes(PIPE_RECV, (char *)&req, sizeof(req)))) {
            DBG("[E] failed to recv req from CLIENT\n");
            goto bail;
        }
        DBG("[D] got a REQUEST\n");
        if (DST_EXIT == req.dst) { do_exit(); }
        if (PIPE_CB1_A > req.dst || PIPE_CB2_B < req.dst || STDERR == req.dst) {
            DBG("[E] invalid dst (%d); bailing\n", req.dst);
            goto bail;
        }
        DBG("[D] got request for op %d\n", req.op);
        MSG_DUMP(req);

        // Dispatch to appropriate handler.
        DBG("[D] got request for op %d; about to call %p\n", req.op, operations[req.op]);
        if (SUCCESS != (ret = (int)(*operations[req.op])(req.x, req.y, req.nmb))) {
            DBG("[E] failed during operation 0x%02x\n", req.op);
            goto bail;
        }
    }

bail:
    return ret;
}

