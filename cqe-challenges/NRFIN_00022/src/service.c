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
#include "libc.h"
#include "operation.h"
#include "service.h"

enum {
    CMD_ADD_HAIKU = 1492,
    CMD_GET_HAIKU_BY_ID = 1999,
    CMD_GET_HAIKU_RANDOM = 200042,
    CMD_GET_COUNT = 1210000,
    CMD_GET_IDS = 8675309,
};

int main(void) {

    uint32_t command[1] = {0};
    int ret = 0;


    while (1) {
        RECV(command, sizeof(uint32_t));

        switch (command[0]) {
            case CMD_ADD_HAIKU:
                ret = add_haiku();
                break;
            case CMD_GET_HAIKU_BY_ID:
                ret = get_haiku_by_id();
                break;
            case CMD_GET_HAIKU_RANDOM:
                ret = get_haiku_random();
                break;
            case CMD_GET_COUNT:
                ret = get_haiku_count();
                break;
            case CMD_GET_IDS:
                ret = get_haiku_ids();
                break;
            default:
                ret = ERR_INVALID_CMD;
        }

        if (ret < 0) {
            SENDSI(ret);
            return ret;
        }

        command[0] = 0;
    }

    return ret;
}
