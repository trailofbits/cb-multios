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
#include <stdint.h>
#include "libc.h"
#include "recv_all.h"
#include "send.h"
#include "memcmp.h"
#include "memcpy.h"

#include "breakfast.h"

#define INITIAL_ORDER_ID 4242

const char INPUT_TYPE_PLAIN[4] =        {'\xdd','\x11','\x44','\xaa'};
const char INPUT_TYPE_SERIALIZED[4] =   {'\x00','\xaa','\xdd','\x11'};

static Stream *in;

static char OK[4] = {0};
static char ERR[4] = {0};

/**
 * Create a checksum of the flag page to use as the OK/ERR byte strings
 */
void gen_result_bufs(void) {
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
ssize_t receive_input(void) {
    ssize_t res;
    Stream tmp;
    // recv Input type and size
    res = recv_all((char *)&tmp, sizeof(tmp));
    if (res != sizeof(tmp)) {
        _terminate(ERRNO_RECV);
    }

    // check for invalid INPUT_TYPE
    if (memcmp(INPUT_TYPE_PLAIN, (const char *)tmp.type, sizeof(INPUT_TYPE_PLAIN)) &&
        memcmp(INPUT_TYPE_SERIALIZED, (const char *)tmp.type, sizeof(INPUT_TYPE_SERIALIZED))) {
        return -1;
    }

    in = malloc(sizeof(tmp) + tmp.size);
    MALLOC_OK(in);

    in->size = tmp.size;
    memcpy(in->type, tmp.type, sizeof(INPUT_TYPE_SERIALIZED));

    res = recv_all(in->content, in->size);
    if (res != in->size) {
        _terminate(ERRNO_RECV);
    }

    return SUCCESS;
}

int main(void) {

    ssize_t ret = 0;
    int order_id = INITIAL_ORDER_ID;

    gen_result_bufs();

    while (TRUE) {

        ret = receive_input();
        if (0 > ret) {
            goto check_res;
        }

        send((char *)&order_id, sizeof(order_id));

        if (0 == memcmp(INPUT_TYPE_PLAIN, (const char *)in->type, sizeof(INPUT_TYPE_PLAIN))) {
            ret = process_plain_input(in);
        } else {
            ret = process_serialized_input(in);
        }
check_res:
        if (0 == ret) {
            send(OK, sizeof(OK));
        } else {
            send(ERR, sizeof(ERR));
	        break;
        }

        free(in);
        order_id++;
    }

    return 0;
}
