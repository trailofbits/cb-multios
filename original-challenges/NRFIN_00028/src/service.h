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


#ifndef SERVICE_H
#define SERVICE_H

#define SEGERR "Only the sigs deal in absolutes."
#define SEGKEY "My voice is my passport."
#define SEGDONE "fin."
#define MAX_SEG_SIZE 4096

#define MAX_NUM_SEGS 10

typedef struct seg {
    size_t size;
    char name[16];
    char desc[112];
    uint8_t code[4096];
} seg_t;

typedef struct segnode segnode_t;
struct segnode {
    segnode_t *next;
    seg_t *s;
    int (*f)();
};

/**
 * Calculate our verification checksum
 *
 * @param in Data to verify
 * @param out Buffer to save verification buf to
 * @param size Size of input buffer
 * @return Verification code in out buffer
 */
void scramble(uint8_t *in, uint8_t *out, size_t len);

/**
 * Run a SEG
 *
 * @param curnode segnode to start at
 * @return 0, terminates on error
 */
int run_seg(segnode_t *curnode);

/**
 * Load a SEG
 *
 * @param curnode segnode to start at
 * @return 0
 */
int load_seg(segnode_t *curnode);

/**
 * Ensure name and desc lengths > 0
 *
 * @param s seg to check
 * @return 1 if seg name or desc > 0, 0 if not
 */
int sanitycheck(seg_t *s);

/**
 * Validate a SEG
 *
 * @param curnode segnode to start at
 * @return 0 if valid, 1 if not
 */
int validate_seg(segnode_t *curnode);

/**
 * Receive a SEG
 *
 * @return First node in segnode list, terminates on error
 */
segnode_t *recv_seg();
#endif
