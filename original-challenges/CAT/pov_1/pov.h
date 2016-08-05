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

#ifndef POV_H
#define POV_H

// #define DEBUG 1

#include <libpov.h>

typedef uint8_t byte_t;
typedef uint8_t bool;
#define TRUE 1
#define FALSE 0

#define STDIN 0
#define STDOUT 1
#define SUCCESS 0
#define INT_MAX 0x7FFFFFFF

// Things that don't change about the target VA space:
#define FLAG_BGN 0x4347C000 // per CFE rules
#define STCK_BGN 0xbaa8b000 // per CGC kernel source
#define STCK_END 0xbaaab000 // per CGC kernel source
#define HEAP_BGN 0xb7fff000 // empirically for this CB
#define SZ_DATA 0x1500 // empirically for this CB

// We run the risk of timing out during &data and &func_ptr leakage, so we help 
// the search along:
#define SRCH_DATA_BGN STCK_BGN+0x1F000 // &data leaked from stack frame

#define MAGIC_DATA_BEFORE 0xCAFEBABE
#define MAGIC_DATA_AFTER 0xBBBBBBBB
#define MAGIC_PTR_BEFORE 0xDEADBEEF
#define MAGIC_PTR_AFTER 0xAAAAAAAA

#define MAGIC_RND 0xFFFFFFFF

#define REGNUM_EAX 0


#ifdef DEBUG
#include "pov_debug.h"
#define dbg(args...) fprintf(stderr, "[D] %s:%d @ %s | ", __FILE__, __LINE__, __func__);fprintf(stderr, args);
#define err(args...) \
    fprintf(stderr, "[E] %s:%d @ %s | ", __FILE__, __LINE__, __func__);\
    fprintf(stderr, args);\
    if(SUCCESS == ret) { ret = -1; }\
    goto bail;
#else
#define dbg(args...) do { } while (0);
#define err(args...) goto bail;
#endif

#define CHK_SUCCESS(code, args...) if (SUCCESS != (ret = code)) { err(args); }

typedef enum {
    S_REQ,
    S_RESP,
    S_ERROR,
    S_EXIT,
    S_LAST = INT_MAX,
} status_t;

typedef enum {
    X_NORMAL,
    X_SCRATCH,
    X_STATIC,
    X_PREV,
    X_LAST = INT_MAX,
} access_t;

typedef enum {
    A_READ,
    A_WRITE,
    A_LAST = INT_MAX,
} action_t;

typedef enum {
    OP2_IMM,
    OP2_MEM,
    OP2_LAST = INT_MAX,
} op2type_t;

typedef struct __attribute__((packed)) {
    action_t action; // 4
    op2type_t op2type; // 8
    uint32_t dst; // 12
    uint32_t src; // 16
} instruction_t;

typedef struct __attribute__((packed)) {
    status_t status; // 4
    // The sequence number.  Used for correlating requests & responses.
    uint32_t seq; // 8
    // Access type (NORMAL, STATIC, SCRATCH)
    access_t type; // 12
    // Operation
    instruction_t inst; // 12 + 16 = 28
} packet_t;

// Support
int recv_bytes(int fd, char *buf, unsigned int size);
int send_bytes(int fd, const char *buf, unsigned int size);
int inline_send_bytes(int fd, const char *buf, unsigned int size);
int new_pkt(packet_t *pkt, status_t status, uint32_t seq, access_t type, action_t action, op2type_t op2type, uint32_t dst, uint32_t src);

// Main exploit logic
int find_needle(bool deref, uint32_t bgn, uint32_t end, uint32_t magic_before, uint32_t magic_after, uint32_t *assign);
int find_func_ptr(void);
int find_data(void);
int transmit_sc(byte_t *sc, uint32_t loc);
int leak_4B(byte_t *leaked);
int main(void);

// VAs on target (to leak)
uint32_t t_data_bgn;
uint32_t t_data_end;
uint32_t t_func_ptr;

// Determined at runtime
uint32_t t_sc;

#endif
