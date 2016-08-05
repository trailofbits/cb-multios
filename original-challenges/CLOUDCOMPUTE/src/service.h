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

//// Protocol
// *** NEW SESSION ***
// CRS -> CB: 4B MAGIC_NEW_SESSION
// CRS <- CB: 4B (generated) session ID
// CRS -> CB: 4B session ID | 2B session SZ -- THIS STEP DOESN'T EXIST IN OLD SESSION
// CRS -> CB: 4B session ID | opcodes (of length session->sz)
// CRS <- CB: 4B session ID | scratch area (of length SCRATCH_SZ)

// *** OLD SESSION ***
// CRS -> CB: 4B (existing) session ID
// CRS <- CB: 4B (reflected) session ID
// CRS -> CB: 4B session ID | opcodes (of length session->sz)
// CRS <- CB: 4B session ID | scratch area (of length SCRATCH_SZ)

//// POV
// 0) attacker sets up the heap
// 1) attacker overflows from one session to another, controlling the vulnerable buffer's BASE_ADDR
// 2) attacker uses legit bytecode functionality to manipulate most VA in memory via the overflown session

// 0a) attacker creates the vulnerable buffer (session A)
// CRS -> CB: 4B MAGIC_NEW_SESSION
// CRS <- CB: 4B session A
// CRS -> CB: 4B session A | 2B session A SZ
// CRS -> CB: 4B session A | opcodes
// CRS <- CB: 4B session A | scratch area

// 0b) attacker creates an adjacent buffer (session B)
// CRS -> CB: 4B MAGIC_NEW_SESSION
// CRS <- CB: 4B session B
// CRS -> CB: 4B session B | 2B session B SZ
 	// - session B SZ is BASE_ADDR_SZ + SCRATCH_SZ smaller than session A SZ
// CRS -> CB: 4B session B | opcodes
// CRS <- CB: 4B session B | scratch area

// 1) attacker overflows from session B to session A, controlling the session A's BASE_ADDR
// CRS -> CB: 4B session A
// CRS <- CB: 4B session A
// CRS -> CB: 4B session B | opcodes
 	// vuln here: 
 	// - CB fails to check that session B is the expected session
 	// - the opcode copy happens with session A's SZ (which is SCRATCH_SZ + BASE_ADDR_SZ larger than session B SZ)
 	// - this allows the attacker to copy enough "opcodes" to fill:
 		// - session B's opcode buffer (session->sz)
 		// - session B's scratch buffer (session->sz + SCRATCH_SZ)
 		// - BASE_ADDR_SZ of session A's opcode buffer (session->sz + SCRATCH_SZ + BASE_ADDR_SZ)
 	// - this overflow provides the attacker with arbitrary control over session A's BASE_ADDR
 	// - to make it simple, the attacker can just specify a bunch of unknown opcodes so no side-effects happen
// CRS <- CB: 4B session B | scratch area

// 2) attacker uses legit bytecode functionality to manipulate arbitrary VA in memory via the overflown session
// CRS -> CB: 4B session A
// CRS <- CB: 4B session A
// CRS -> CB: 4B session A | opcodes
 	// - because attacker controls session A's BASE_ADDR, attacker is able to R/W any VA with the mask: 0xFFFF00FF
 	// - this can be used to achieve either type 1 or type 2 POV
// CRS <- BC: 4B session A | scratch area


#ifndef SERVICE_H
#define SERVICE_H

#include <libcgc.h>
#include "bytecode.h"

#define TRUE 1
#define FALSE 0

#define SESSIONS_MAX 20
#define SCRATCH_SZ 256
#define OPCODE_SZ_MAX 512
#define SESSION_SZ (BASE_ADDR_SZ + OPCODE_SZ_MAX + SCRATCH_SZ)

#define STATE_INIT 0
#define STATE_EXEC 1

#define MAGIC_NEW_SESSION 0

// The 0xE0000000 - 0xEFFFFFFF range is reserved for error codes.
#define MAGIC_ERR_MIN 0xE0000000
#define MAGIC_EXIT 0xE3E3F046
#define MAGIC_ERR_BAD_ID 0xE0DEADE9
#define MAGIC_ERR_NO_SPACE 0xE2EA8684
#define MAGIC_ERR_SESSION_DOESNT_EXIST 0xE9280DFC
#define MAGIC_ERR_TOO_LARGE 0xE33BF5BE
#define MAGIC_ERR_HANDSHAKE_FAILURE 0xE2DDAA66
#define MAGIC_ERR_MAX 0xEFFFFFFF

#define BUF_RX_SZ 65536

typedef struct {
	// The unique 32bit value identifying this session.
	uint32_t id;
	// A pointer to this session's backing memory.  The backing memory contains 
	// the session's BASE_ADDR, opcode buffer and scratch buffer.
	uint8_t *buf;
	// The size of the session's opcode buffer.  Dictated by the CRS during 
	// session initialization.
	uint16_t sz;
} session_t;

/**
 * Look up a session based on its session ID.  Backing memory is memset() to 
 * \x00, so this function is also used to look up the next free session slot 
 * (the first session with a session ID of \x00\x00\x00\x00).
 *
 * @param id The requested session ID.
 * @return A pointer to the requested session_t struct (if found) or NULL 
 *	(if not found).
 */
session_t * find_session(uint32_t id);

/**
 * Initialize a new session instance.  There is a maximum of 20 sessions, but 
 * an unlimited number of times one can exercise a session.  Each time a 
 * session is exercised (a new session or old), this function is called to 
 * initialize the session instance.  This function is responsible for speaking 
 * the protocol up until the CB has bytecode to execute.  Barring any error, 
 * state is advanced to STATE_EXEC and do_exec is called in succession.
 *
 * @param session A pointer to a pointer to a session struct that is to be 
 *	populated by values exchanged during session instance negotiation.
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int do_init(session_t **session);

/**
 * Session instance negotiation is complete and we continue with session 
 * negotiation, setting up session memory for bytecode execution. At a high 
 * level, this function is responsible for the following:
 * 0) read & verify (if PATCHED) session ID
 * 1) populate BASE_ADDR
 * 2) read opcode buffer off the wire into the session's opcode buffer
 * 3) execute bytecode
 * 4) transmit the session's scratch buffer back to the CRS
 *
 * @param session A pointer to a session struct that was initialized by 
 *	do_init().
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int do_exec(session_t *session);

/**
 * The main loop.  Responsible for maintaining the simple state machine and 
 * dispatching to do_init() and do_exec().  Should not return.
 *
 * @return An int indicating SUCCESS (0) or an error condition (!=0).
 */
int main(void);


#endif
