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

#include "libcgc.h"
#include "cgc_stdint.h"
#include "cgc_libc.h"
#include "cgc_recv_all.h"
#include "cgc_send.h"
#include "cgc_memcmp.h"
#include "cgc_memcpy.h"

#include "cgc_breakfast.h"

#define INITIAL_ORDER_ID 4242

const char cgc_INPUT_TYPE_PLAIN[4] =        {'\xdd','\x11','\x44','\xaa'};
const char cgc_INPUT_TYPE_SERIALIZED[4] =   {'\x00','\xaa','\xdd','\x11'};

static Stream *in;

static char OK[4] = {0};
static char ERR[4] = {0};

/**
 * Create a checksum of the flag page to use as the OK/ERR byte strings
 */
void cgc_gen_result_bufs(void) {
    const char *fp = (char *)FLAG_PAGE;
    for (unsigned int idx = 0; idx < 4095; idx+=2) {
        OK[idx % 4] ^= fp[idx];
        ERR[(idx + 1) % 4] ^= fp[idx + 1];
    }
}

/**
 * Receive input buffer, convert to Stream object
 *
 * @return SUCCESS on success, else, -1 on error
 */
cgc_ssize_t cgc_receive_input(void) {
    cgc_ssize_t res;
    Stream tmp;
    // recv Input type and size
    res = cgc_recv_all((char *)&tmp, sizeof(tmp));
    if (res != sizeof(tmp)) {
        cgc__terminate(ERRNO_RECV);
    }

    // check for invalid INPUT_TYPE
    if (cgc_memcmp(cgc_INPUT_TYPE_PLAIN, (const char *)tmp.type, sizeof(cgc_INPUT_TYPE_PLAIN)) &&
        cgc_memcmp(cgc_INPUT_TYPE_SERIALIZED, (const char *)tmp.type, sizeof(cgc_INPUT_TYPE_SERIALIZED))) {
        return -1;
    }

    in = cgc_malloc(sizeof(tmp) + tmp.size);
    MALLOC_OK(in);

    in->size = tmp.size;
    cgc_memcpy(in->type, tmp.type, sizeof(cgc_INPUT_TYPE_SERIALIZED));

    res = cgc_recv_all(in->content, in->size);
    if (res != in->size) {
        cgc__terminate(ERRNO_RECV);
    }

    return SUCCESS;
}

int main(int cgc_argc, char *cgc_argv[]) {

    cgc_ssize_t ret = 0;
    int order_id = INITIAL_ORDER_ID;

    cgc_gen_result_bufs();

    while (TRUE) {

        ret = cgc_receive_input();
        if (0 > ret) {
            goto check_res;
        }

        cgc_send((char *)&order_id, sizeof(order_id));

        if (0 == cgc_memcmp(cgc_INPUT_TYPE_PLAIN, (const char *)in->type, sizeof(cgc_INPUT_TYPE_PLAIN))) {
            ret = cgc_process_plain_input(in);
        } else {
            ret = cgc_process_serialized_input(in);
        }
check_res:
        if (0 == ret) {
            cgc_send(OK, sizeof(OK));
        } else {
            cgc_send(ERR, sizeof(ERR));
	        break;
        }

        cgc_free(in);
        order_id++;
    }

    return 0;
}
