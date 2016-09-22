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

 // Globals
uint32_t enckey[SZ_ENCKEY] = { 0 };
uint32_t auth_token = { 0 };
msg msgNull = { 0 };


int op_add(size_t x, size_t y, size_t *expected_answer) {
    DBG("\n");

    int ret = SUCCESS;
    msg req = msgNull, resp = msgNull;
    
    *expected_answer = x + y;

    req.dst = PIPE_CB2_A;
    req.x = x;
    req.y = y;
    req.op = OP_ADD;

    if (SUCCESS != (ret = send_bytes(PIPE_SEND_TAP, (char *)&req, sizeof(req)))) {
        DBG("[E] failed to send request to SERVER\n");
        goto bail;
    }
    DBG("[D] sent:\n");
    MSG_DUMP(req);

bail:
    return ret;
}


int op_sub(size_t x, size_t y, size_t *expected_answer) {
    DBG("\n");

    int ret = SUCCESS;
    msg req = msgNull, resp = msgNull;
    
    *expected_answer = x - y;

    req.dst = PIPE_CB2_A;
    req.x = x;
    req.y = y;
    req.op = OP_SUB;

    if (SUCCESS != (ret = send_bytes(PIPE_SEND_TAP, (char *)&req, sizeof(req)))) {
        DBG("[E] failed to send request to SERVER\n");
        goto bail;
    }
    DBG("[D] sent:\n");
    MSG_DUMP(req);

bail:
    return ret;
}


int op_mul(size_t x, size_t y, size_t *expected_answer) {
    DBG("\n");

    int ret = SUCCESS;
    msg req = msgNull, resp = msgNull;
    
    *expected_answer = x * y;

    req.dst = PIPE_CB2_A;
    req.x = x;
    req.y = y;
    req.op = OP_MUL;

    if (SUCCESS != (ret = send_bytes(PIPE_SEND_TAP, (char *)&req, sizeof(req)))) {
        DBG("[E] failed to send request to SERVER\n");
        goto bail;
    }
    DBG("[D] sent:\n");
    MSG_DUMP(req);

bail:
    return ret;
}


int op_div(size_t x, size_t y, size_t *expected_answer) {
    DBG("\n");

    int ret = SUCCESS;
    msg req = msgNull, resp = msgNull;

    if (y == 0) { *expected_answer = 0; } 
    else { *expected_answer = x / y; }

    req.dst = PIPE_CB2_A;
    req.x = x;
    req.y = y;
    req.op = OP_DIV;

    if (SUCCESS != (ret = send_bytes(PIPE_SEND_TAP, (char *)&req, sizeof(req)))) {
        DBG("[E] failed to send request to SERVER\n");
        goto bail;
    }
    DBG("[D] sent:\n");
    MSG_DUMP(req);

bail:
    return ret;
}

// The next request is determined by reading a byte from the PRNG 
// (which is keyed from the flag page). 
int get_request_type(byte_t *operation) {
    DBG("\n");

    int ret = SUCCESS;

    // We're basically jsut getting a byte out of the PRNG.
    if (SUCCESS != (ret = prng_get_bytes(operation, 1))) {
        DBG("[E] failed to get bytes for next operation\n");
        goto bail;
    }
    DBG("[D] operation = 0x%02x\n", *operation);

bail:
    return ret;
}


int do_request(size_t x, size_t y, size_t *expected_answer) {
    DBG("\n");

    int ret = SUCCESS;
    byte_t operation;

    // Get next request type, dispatch to appropriate function pointer.
    if (SUCCESS != (ret = get_request_type(&operation))) {
        DBG("[E] failed during get_request_type\n");
        goto bail;
    }
    if (OP_MOD == operation) { operation = OP_ADD; }

    // Dispatch to appropriate function pointer.
    if (SUCCESS != (ret = (int)(operations[operation])(x, y, expected_answer))) {
        DBG("[E] failed during request operation\n");
        goto bail;
    }

bail:
    return ret;
}


int do_response(size_t expected_answer) {
    DBG("\n");

    int ret = SUCCESS;
    byte_t operation;
    msg resp = msgNull;

    // Get everything but sz_result
    DBG("[D] waiting for RESPONSE\n");
    if (SUCCESS != (ret = recv_bytes(PIPE_RECV, (char *)&resp, sizeof(resp)))) {
        DBG("[E] failed to recv request from SERVER\n");
        goto bail;
    }
    if (DST_EXIT == resp.dst) { do_exit(); }
    if (PIPE_CB1_A > resp.dst || PIPE_CB2_B < resp.dst || STDERR == resp.dst) {
        DBG("[E] invalid dst (%d); bailing\n", resp.dst);
        goto bail;
    }
    DBG("[D] recv'ed:\n");
    MSG_DUMP(resp);

    uint64_t result = resp.result;
    DBG("[D] CT result: 0x"); DBG_SIMPLE("%08x", result >> 32); DBG_SIMPLE("%08x\n", result);
    if (SUCCESS != (ret = decrypt_1block(&result, &enckey))) {
        DBG("[E] unable to decrypt result\n")
        goto bail;
    }
    DBG("[D] PT result: 0x"); DBG_SIMPLE("%08x", result >> 32); DBG_SIMPLE("%08x\n", result);

    uint32_t answer = result >> 32;

    if (answer != expected_answer) {
        DBG("[D] wrong answer 0x%08x (actual) != 0x%08x (expected)\n", answer, expected_answer);
        ret = ERRNO_WRONG_ANSWER;
        goto bail;
    }
    DBG("[D] answer checks out\n")

bail:
    return ret;
}

// Negotiate encryption key and auth token.
// CLIENT chooses encryption key; SERVER chooses auth token.
int negotiate(void) {
    DBG("\n");

    int ret = SUCCESS;
    size_t rnd_bytes = 0;
    uint32_t enckey_idx = 0, enckey_idx_actual = 0;
    uint32_t auth_token_idx = 0, auth_token_idx_actual = 0;
    uint32_t dummy = 0;
    msg ack = msgNull;

    // The offset can't be from random() because then the poller wouldn't have access to it?
    enckey_idx = *(uint32_t *)(VA_FLAG + OFF_ENCKEY_IDX);
    enckey_idx_actual = (enckey_idx % SZ_PAGE) & ~0xF;

    enckey[0] = *(uint32_t *)(VA_FLAG + enckey_idx_actual + sizeof(uint32_t) * 0);
    enckey[1] = *(uint32_t *)(VA_FLAG + enckey_idx_actual + sizeof(uint32_t) * 1);
    enckey[2] = *(uint32_t *)(VA_FLAG + enckey_idx_actual + sizeof(uint32_t) * 2);
    enckey[3] = *(uint32_t *)(VA_FLAG + enckey_idx_actual + sizeof(uint32_t) * 3);
    DBG("[D] enckey_idx = 0x%08x, enckey_idx_actual = 0x%08x; enckey = 0x%08x%08x%08x%08x\n", 
        enckey_idx, enckey_idx_actual, enckey[0], enckey[1], enckey[2], enckey[3]);

    if (SUCCESS != (ret = send_bytes(PIPE_SEND_NO_TAP, (char *)&enckey_idx, sizeof(enckey_idx)))) {
        DBG("[E] failed to send enckey_idx (0x%08x) to SERVER\n", enckey_idx);
        goto bail;
    }

    if (SUCCESS != (ret = recv_bytes(PIPE_RECV, (char *)&ack, sizeof(ack))) || ack.op != OP_ACK) {
        DBG("[E] failed to get ack from SERVER\n");
        ret = ERRNO_ACK;
        goto bail;
    }

    // Now onto the auth_token

    if (SUCCESS != (ret = recv_bytes(PIPE_RECV, (char *)&auth_token_idx, sizeof(auth_token_idx)))) {
        DBG("[E] failed to recv auth_token_idx from SERVER\n");
        goto bail;
    }

    auth_token_idx_actual = (auth_token_idx % SZ_PAGE) & ~0xF;
    auth_token = *(uint32_t *)(VA_FLAG + auth_token_idx_actual);
    DBG("[D] auth_token_idx = 0x%08x; auth_token = 0x%08x\n", 
        auth_token_idx, auth_token);

    ack = msgNull;
    ack.op = OP_ACK;
    if (SUCCESS != (ret = send_bytes(PIPE_SEND_NO_TAP, (char *)&ack, sizeof(ack)))) {
        DBG("[E] failed send ACK to SERVER\n");
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
    uint32_t state = STATE_REQUEST;
    size_t x, y, expected_answer;

    // Do initial setup things.
    DBG("[D] initial setup\n");
    if (SUCCESS != (ret = negotiate())) {
        DBG("[E] failed to negotiate\n");
        goto bail;
    }

    // Set the PRNG key from bytes in the flag page (arbitrary offsets).
    /// PRNG output will therefore be predicated on contents of the flag page.
    DBG("[D] setting PRNG key\n");
    byte_t my_prng_key[16] = { 
        *(byte_t *)(VA_FLAG +  2), *(byte_t *)(VA_FLAG +  3), // 2
        *(byte_t *)(VA_FLAG +  5), *(byte_t *)(VA_FLAG +  7), // 4
        *(byte_t *)(VA_FLAG + 11), *(byte_t *)(VA_FLAG + 13), // 6
        *(byte_t *)(VA_FLAG + 17), *(byte_t *)(VA_FLAG + 19), // 8
        *(byte_t *)(VA_FLAG + 23), *(byte_t *)(VA_FLAG + 29), // 10
        *(byte_t *)(VA_FLAG + 31), *(byte_t *)(VA_FLAG + 37), // 12
        *(byte_t *)(VA_FLAG + 41), *(byte_t *)(VA_FLAG + 43), // 14
        *(byte_t *)(VA_FLAG + 53), *(byte_t *)(VA_FLAG + 59), // 16
    };
    if (SUCCESS != (ret = prng_set_key((byte_t *)&my_prng_key))) {
        DBG("[E] failed to set prng key\n");
        goto bail;
    }

    // Main request / response loop.
    DBG("[D] entering main loop\n");
    while(TRUE) {
        
        switch(state) {

            // Really the request and response portions could be combined into 
            // a single function, but this gives them more to reason about.

            case STATE_REQUEST:
                DBG("[D] STATE_REQUEST\n");
                // Pick arguments
                uint32_t args[2] = { 0 };
                prng_get_bytes(&args, 2 * sizeof(uint32_t));
                x = args[0]; y = args[1];
                if (SUCCESS != (ret = do_request(x, y, &expected_answer))) {
                    DBG("[E] error during do_request(); bailing...\n");
                    goto bail;
                }
                state = STATE_RESPONSE;
                break;

            case STATE_RESPONSE:
                DBG("[D] STATE_RESPONSE\n");
                if (SUCCESS != (ret = do_response(expected_answer))) {
                    DBG("[E] error during do_response(); bailing...\n");
                    goto bail;
                }
                state = STATE_REQUEST;
                break;

            default:
                DBG("[E] INVALID state (SHOULDN'T HAPPEN); bailing...\n");
                ret = ERRNO_INVALID_STATE;
                goto bail;
                break;
        }
    }

bail:
    return ret;
}

