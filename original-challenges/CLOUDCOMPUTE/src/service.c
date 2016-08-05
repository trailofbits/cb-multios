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

unsigned char rx_buf[BUF_RX_SZ];
session_t sessions[SESSIONS_MAX] = { 0 };
uint8_t sessions_num = 0;
// The last byte allocated for session data. session_window must not expand 
// beyond this.
uint8_t *session_dat = NULL; 
// A pointer to the lowest address currently used for sessions. This pointer is 
// subtracted as new sessions are allocated, "widening" the window.
uint8_t *session_window = NULL;
uint32_t tmp = 0;


session_t * find_session(uint32_t id) {
    for (uint32_t i = 0; i < SESSIONS_MAX; i++) {
        if (id == sessions[i].id) {
            return &sessions[i];
        }
    }
    return NULL;
}


int do_init(session_t **session) {

    int ret = SUCCESS;
    memset(rx_buf, 0, BUF_RX_SZ);
    uint32_t requested_session_id = 0;

    #ifdef DEBUG
    fprintf(stderr, "[D] %s | ENTER\n", __func__);
    #endif

    // Get session ID from CRS.
    if (SUCCESS != (ret = recv_bytes(STDIN, (char *)&rx_buf, sizeof(uint32_t)))) { 
        #ifdef DEBUG
        fprintf(stderr, "[E] %s | during receive ()\n", __func__);
        #endif

        ret = ERRNO_RECV;
        goto bail;
    }
    requested_session_id = *(uint32_t*)&rx_buf;
    #ifdef DEBUG
    fprintf(stderr, "[D] %s | requested_session_id = 0x%08x\n", __func__, requested_session_id);
    #endif  

    // Check for MAGIC_EXIT
    if (MAGIC_EXIT == requested_session_id) {
        #ifdef DEBUG
        fprintf(stderr, "[D] %s | got MAGIC_EXIT; _terminate(0)ing...\n", __func__);
        #endif 
        _terminate(0);
    }

    // Check proposed session IDs against blacklist.
    if (MAGIC_ERR_MIN <= requested_session_id && requested_session_id <= MAGIC_ERR_MAX) {
        
        // Condition:
        // - they've sent a blacklisted session ID

        // Send error response.
        #ifdef DEBUG
        fprintf(stderr, "[D] %s | bad session ID (0x%08x); rejecting\n", __func__, requested_session_id);
        #endif  

        tmp = MAGIC_ERR_BAD_ID;
        if (SUCCESS != (ret = send_bytes(STDOUT, (const char *)&tmp, sizeof(tmp)))) { 
            #ifdef DEBUG
            fprintf(stderr, "[E] %s | during transmit ()\n", __func__);
            #endif
            ret = ERRNO_TRANSMIT;
            goto bail;
        }

        // Return NULL session.
        *session = NULL;
        goto bail;
    }

    // Condition:
    // - they've sent a non-blacklisted session ID

    if (MAGIC_NEW_SESSION != requested_session_id) {

        // Condition:
        // - they're requesting an existing session

        #ifdef DEBUG
        fprintf(stderr, "[D] %s | session 0x%08x is requested\n", __func__, requested_session_id);
        #endif
        
        if (NULL == (*session = find_session(requested_session_id))) {

            // Condition:
            // - they're requesting an existing session
            // - the requested session doesn't exist

            // Send error code & bail.
            #ifdef DEBUG
            fprintf(stderr, 
                "[D] %s | session 0x%08x doesn't exist; sending error...\n", 
                __func__, requested_session_id);
            #endif 
            
            tmp = MAGIC_ERR_SESSION_DOESNT_EXIST;
            if (SUCCESS != (ret = send_bytes(STDOUT, (const char *)&tmp, sizeof(tmp)))) { 
                #ifdef DEBUG
                fprintf(stderr, "[E] %s | during transmit ()\n", __func__);
                #endif
        
                ret = ERRNO_TRANSMIT;
                goto bail;
            }

            goto bail;
        }

        // Condition:
        // - they're requesting an existing session
        // - the requested session exists

        // Reflect the session ID.
        #ifdef DEBUG
        fprintf(stderr, "[D] %s | session 0x%08x exists; reflecting ID\n", __func__, (*session)->id);
        #endif

        if (SUCCESS != (ret = send_bytes(STDOUT, (const char *)&(*session)->id, sizeof(uint32_t)))) { 
            #ifdef DEBUG
            fprintf(stderr, "[E] %s | during transmit ()\n", __func__);
            #endif

            ret = ERRNO_TRANSMIT;
            goto bail;
        }

        // We're done.
        goto bail;
    }


    // Condition:
    // - they're requesting a new session

    #ifdef DEBUG
    fprintf(stderr, "[D] %s | got MAGIC_NEW_SESSION; starting new session\n", __func__);
    #endif

    if (SESSIONS_MAX <= sessions_num + 1) {

        // Condition:
        // - they're requesting a new session
        // - there's no more room for sessions

        // Send error & bail.
        #ifdef DEBUG
        fprintf(stderr, 
            "[D] %s | no space for a new session (%d <= %d); rejecting request\n", 
            __func__, SESSIONS_MAX, sessions_num+1);
        #endif 

        tmp = MAGIC_ERR_NO_SPACE;
        if (SUCCESS != (ret = send_bytes(STDOUT, (const char *)&tmp, sizeof(uint32_t)))) { 
            #ifdef DEBUG
            fprintf(stderr, "[E] %s | during transmit ()\n", __func__);
            #endif
    
            ret = ERRNO_TRANSMIT;
            goto bail;
        }

        *session = NULL;
        goto bail;
    }

    // Condition:
    // - they're requesting a new session
    // - there's room for more sessions

    #ifdef DEBUG
    fprintf(stderr, 
        "[D] %s | NEW session requested; we have room (%d >= %d)\n", 
        __func__, SESSIONS_MAX, sessions_num+1);
    #endif

    if (NULL == (*session = find_session(requested_session_id))) {
        #ifdef DEBUG
        fprintf(stderr, "[E] %s | unable to find empty session; SHOULDN'T HAPPEN; bailing...\n", __func__);
        #endif
        goto bail;
    }

    // Generate a session ID.
    size_t rnd_bytes = 0;
    while(1) {
        rnd_bytes = 0;
        if (SUCCESS != random(&(*session)->id, 4, &rnd_bytes) || 4 != rnd_bytes) {
            #ifdef DEBUG
            fprintf(stderr, "[E] %s | during random (); SHOULDN'T HAPPEN; bailing...\n", __func__);
            #endif
            goto bail;
        }

        // If we end up with a blacklisted session ID, try again.
        if (MAGIC_NEW_SESSION == (*session)->id || (MAGIC_ERR_MIN <= (*session)->id && MAGIC_ERR_MAX >= (*session)->id)) {
            #ifdef DEBUG
            fprintf(stderr, "[D] %s | generated a blacklisted ID; trying again (1/16 chance)\n", __func__);
            #endif
            continue;
        } else { break; }
    }

    // Condition:
    // - they're requesting a new session
    // - there's room for more sessions
    // - we've decided on an ID

    #ifdef DEBUG
    fprintf(stderr, "[D] %s | NEW session ID chosen: 0x%08x\n", __func__, (*session)->id);
    #endif

    // Echo the new session ID back to the CRS.
    if (SUCCESS != (ret = send_bytes(STDOUT, (const char *)&(*session)->id, sizeof(uint32_t)))) {
        #ifdef DEBUG
        fprintf(stderr, "[E] %s | during transmit ()\n", __func__);
        #endif

        ret = ERRNO_TRANSMIT;
        goto bail;
    }

    // Condition:
    // - they're requesting a new session
    // - there's room for more sessions
    // - we've decided on an ID
    // - we've sent the ID to them

    // Next protocol step:
    // CRS -> CB: 4B session ID | 2B session SZ 
    if (SUCCESS != (ret = recv_bytes(STDIN, (char *)&tmp, sizeof(uint32_t)))) { 
        #ifdef DEBUG
        fprintf(stderr, "[E] %s | during receive ()\n", __func__);
        #endif

        ret = ERRNO_RECV;
        goto bail;
    }

    // Does this session ID pertain to the expected session?
    if ((*session)->id != tmp) {
        #ifdef DEBUG
        fprintf(stderr, 
            "[D] %s | session ID changed mid-exchange (should be: 0x%08x, is: 0x%08x); bailing...\n", 
            __func__, (*session)->id, tmp);
        #endif

        tmp = MAGIC_ERR_HANDSHAKE_FAILURE;
        if (SUCCESS != (ret = send_bytes(STDOUT, (const char *)&tmp, sizeof(tmp)))) { 
            #ifdef DEBUG
            fprintf(stderr, "[E] %s | during transmit ()\n", __func__);
            #endif
            ret = ERRNO_TRANSMIT;
            goto bail;
        }

        *session = NULL;
        goto bail;
    }

    // Condition:
    // - they're requesting a new session
    // - there's room for more sessions
    // - we've decided on an ID
    // - we've sent the ID to them
    // - they've sent us a packet with matching session ID

    // Now we need the session size.
    if (SUCCESS != (ret = recv_bytes(STDIN, (char *)&(*session)->sz, sizeof(uint16_t)))) { 
        #ifdef DEBUG
        fprintf(stderr, "[E] %s | during receive ()\n", __func__);
        #endif

        ret = ERRNO_RECV;
        goto bail;
    }

    // Reject any session size that isn't a multiple of OPERATION_SZ.
    if (0 != (*session)->sz % OPERATION_SZ) {
        #ifdef DEBUG
        fprintf(stderr, "[D] %s | rejecting new session sz with a non-multiple of OPERATION_SZ\n", __func__);
        #endif

        *session = NULL;
        goto bail;
    }

    // We've set aside SESSION_SZ for 2B base addr + opcodes + scratch space.
    // If the requested sized exceeds this, we complain and refuse.
    if (OPCODE_SZ_MAX < (*session)->sz) {
        #ifdef DEBUG
        fprintf(stderr, 
            "[D] %s | session->sz is too large: 0x%04x (%d); sending error\n", 
            __func__, (*session)->sz, (*session)->sz);
        #endif

        tmp = MAGIC_ERR_TOO_LARGE;
        if (SUCCESS != (ret = send_bytes(STDOUT, (const char *)&tmp, sizeof(uint32_t)))) { 
            #ifdef DEBUG
            fprintf(stderr, "[E] %s | during transmit ()\n", __func__);
            #endif
    
            ret = ERRNO_TRANSMIT;
            goto bail;
        }

        *session = NULL;
        goto bail;
    }

    // Condition:
    // - they're requesting a new session
    // - there's room for more sessions
    // - we've decided on an ID
    // - we've sent the ID to them
    // - they've sent us a packet with matching session ID
    // - we've gotten a valid size request

    session_window -= (BASE_ADDR_SZ + (*session)->sz + SCRATCH_SZ);
    (*session)->buf = session_window;
    sessions_num++;

    #ifdef DEBUG
    fprintf(stderr, 
        "[D] %s | creation of session 0x%08x of size 0x%04x (%d), successful; finished with INIT state\n", 
        __func__, (*session)->id, (*session)->sz, (*session)->sz);
    #endif

bail:
    #ifdef DEBUG
    fprintf(stderr, "[D] %s | LEAVE\n", __func__);
    #endif
    return ret;
}


int do_exec(session_t *session) {

    int ret = SUCCESS;

    #ifdef DEBUG
    fprintf(stderr, "[D] %s | ENTER; session expected: 0x%08x\n", __func__, session->id);
    #endif

    // 0) read & verify (if PATCHED) session ID
    tmp = 0;
    if (SUCCESS != (ret = recv_bytes(STDIN, (char *)&tmp, sizeof(uint32_t)))) { 
        #ifdef DEBUG
        fprintf(stderr, "[E] %s | during receive ()\n", __func__);
        #endif

        ret = ERRNO_RECV;
        goto bail;
    }
    #ifdef DEBUG
    fprintf(stderr, "[D] %s | session received: 0x%08x\n", __func__, tmp);
    #endif

    if (session->id != tmp) {
        #ifdef PATCHED_1

        #ifdef DEBUG
        fprintf(stderr, "[D] %s | PATCHED: session ID changed mid-exchange; bailing...\n", __func__);
        #endif

        tmp = MAGIC_ERR_HANDSHAKE_FAILURE;
        if (SUCCESS != (ret = send_bytes(STDOUT, (const char *)&tmp, sizeof(tmp)))) { 
            #ifdef DEBUG
            fprintf(stderr, "[E] %s | during transmit ()\n", __func__);
            #endif
            ret = ERRNO_TRANSMIT;
            goto bail;
        }

        // This is the part that makes this the PATCHED version.
        session = NULL;
        goto bail;

        // UNPATCHED
        #else
        
        #ifdef DEBUG
        fprintf(stderr, 
            "[D] %s | UNPATCHED: session ID changed mid-exchange; vuln being exercised...\n", 
            __func__);
        #endif

        // VULN HERE: If the session ID sent in this part of the handshake does 
        // not correspond to the expected session, we don't throw an error and 
        // terminate.  This ultimate causes us to use a confused session SZ, 
        // resulting in linear buffer overflow.

        // Terminate the PATCHED / UNPATCHED guards.
        #endif 
    }

    // This is pointless in the PATCHED version because tmp == session->id 
    // (and therefore the lookup should return same struct).
    session_t *session_we_use_for_sz = NULL;
    if (NULL == (session_we_use_for_sz = find_session(tmp))) {
        #ifdef DEBUG
        fprintf(stderr, "[D] %s | unable to find session; bailing\n", __func__);
        #endif
        goto bail;
    }
    #ifdef DEBUG
    fprintf(stderr, "[D] %s | found session @ 0x%08x\n", __func__, session);
    #endif

    // 1) populate BASE_ADDR
    // Check if one already exists.
    tmp =   (session->buf[0] <<  0) |
            (session->buf[1] <<  8) |
            (session->buf[2] << 16) |
            (0x00            << 24);
    if (0 == tmp) {
        #ifdef DEBUG
        fprintf(stderr, 
            "[D] %s | NULL base_addr at session->buf; populating...\n", 
            __func__);
        #endif

        tmp = (0xFFFFFF00 & (uint32_t)session->buf) >> 8;
        memcpy(session->buf, &tmp, BASE_ADDR_SZ);
    }

    #ifdef DEBUG
    tmp =   (session->buf[0] <<  0) |
            (session->buf[1] <<  8) |
            (session->buf[2] << 16) |
            (0x00            << 24);
    fprintf(stderr, 
        "[D] %s | current base addr: 0x%08x\n", 
        __func__, tmp);
    #endif

    // 2) read opcode buffer off the wire into the session's OPCODE buffer
    #ifdef DEBUG
    fprintf(stderr,
        "[D] %s | WARNING: about to copy 0x%04x (%d) bytes into session 0x%08x; session's sz: 0x%04x (%d)\n", 
        __func__, session_we_use_for_sz->sz, session_we_use_for_sz->sz, session->id, session->sz, session->sz);
    #endif
    if (SUCCESS != (ret = recv_bytes(STDIN, (char *)(session->buf + BASE_ADDR_SZ), session_we_use_for_sz->sz))) { 
        #ifdef DEBUG
        fprintf(stderr, 
            "[E] %s | during receive (); session->sz: %d, got 0x%08x bytes\n", 
            __func__, session->sz, &session->buf + BASE_ADDR_SZ);
        #endif

        ret = ERRNO_RECV;
        goto bail;
    }
    #ifdef DEBUG
    fprintf(stderr, "[D] %s | successfully read opcode buffer\n", __func__);
    #endif

    // 3) execute bytecode
    if (SUCCESS != (ret = bytecode_exec(session->buf, session->sz))) {
        #ifdef DEBUG
        fprintf(stderr, "[E] %s | bytecode execution failed; propagating error\n", __func__);
        #endif
        goto bail;
    }
    #ifdef DEBUG
    fprintf(stderr, "[D] %s | finished bytecode execution\n", __func__);
    #endif

    // 4) return result (the entirely of the scratch space)
    // 4B session ID | scratch area (of length SCRATCH_SZ)
    if (SUCCESS != (ret = send_bytes(STDOUT, (const char *)(&session->id), 4))) { 
        #ifdef DEBUG
        fprintf(stderr, "[E] %s | during transmit ()\n", __func__);
        #endif

        ret = ERRNO_TRANSMIT;
        goto bail;
    }
    // The address of the send needs to be derived from the BASE_ADDR for easy pwnage.
    uint32_t base_addr = ((*(uint32_t *)session->buf) & 0x00FFFFFF) << 8;
    uint32_t scratch_base = (base_addr | ((uint32_t)session->buf & 0x000000FF)) + BASE_ADDR_SZ + session->sz;
    if (SUCCESS != (ret = send_bytes(STDOUT, (const char *)scratch_base, SCRATCH_SZ))) { 
        #ifdef DEBUG
        fprintf(stderr, "[E] %s | during transmit ()\n", __func__);
        #endif

        ret = ERRNO_TRANSMIT;
        goto bail;
    }

bail:
    #ifdef DEBUG
    if (NULL == session) {
        fprintf(stderr, "[D] %s | LEAVE; session: NULL\n", __func__);
    } else {
        fprintf(stderr, "[D] %s | LEAVE; session: 0x%08x\n", __func__, session->id);
    }
    #endif
    return ret;
}


int main(void) {

    int ret = SUCCESS;
    uint32_t state = STATE_INIT;
    session_t *session = NULL;

    // Allocate large buffer for all session data.
    // To have a unique upper 2B and lower 2B  for each session, we need to allocate:
    // SESSION_SZ (0x10101) * SESSIONS_MAX (20) = 0x141414
    // This should be feasible.
    #define SESSION_ALLOC_LEN (SESSION_SZ * SESSIONS_MAX)
    if (SUCCESS != (ret = allocate(SESSION_ALLOC_LEN, FALSE, (void **)&session_dat))) {

        #ifdef DEBUG
        fprintf(stderr, "[E] %s | failed session_dat allocation; bailing...\n", __func__);
        #endif

        goto bail;
    }

    // Initialize the window to closed. We later widen the window by 
    // subtracting from session_window, which is initialily something like 
    // 0xb8000000 (the first unmapped byte).
    session_window = session_dat + SESSION_ALLOC_LEN;
    
    while (1) {

        switch(state) {

            case STATE_INIT:

                #ifdef DEBUG
                fprintf(stderr, "[D] %s | state = STATE_INIT\n", __func__);
                #endif

                session = NULL;
                if (SUCCESS != (ret = do_init(&session))) {
                    #ifdef DEBUG
                    fprintf(stderr, "[E] %s | non-SUCCESS from do_init; bailing\n", __func__);
                    #endif
                    goto bail;
                }

                // Advance state iff we populated session.
                if (NULL != session) { state = STATE_EXEC; }
                break;

            case STATE_EXEC:

                #ifdef DEBUG
                fprintf(stderr, "[D] %s | state = STATE_EXEC\n", __func__);
                #endif

                if (SUCCESS != (ret = do_exec(session))) {
                    #ifdef DEBUG
                    fprintf(stderr, "[E] %s | non-SUCCESS from do_exec; bailing\n", __func__);
                    #endif
                    goto bail;
                }

                state = STATE_INIT;
                break;

            default:
                #ifdef DEBUG
                fprintf(stderr, "[E] %s | state = INVALID (SHOULDN'T HAPPEN); bailing...\n", __func__);
                #endif
                ret = ERRNO_INVALID_STATE;
                goto bail;
                break;
        }
    }

bail:
    return ret;
}

