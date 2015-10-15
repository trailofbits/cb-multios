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
    MODE_BUILD = 13980,
    MODE_EXAMINE = 809110,
};

int main(void) {

    uint32_t mode[1] = {0};
    int ret = 0;

    while (1) {
        if ((ret = do_nonce()) == 0) {            
            RECV(mode, sizeof(uint32_t));

            switch (mode[0]) {
                case MODE_BUILD:
                    ret = do_build();
                    break;
                case MODE_EXAMINE:
                    ret = do_examine();
                    break;
                default:
                    ret = ERR_INVALID_MODE;
            }
        } 

        if (ret < 0) {
            SENDSI(ret);
            return ret;
        }
    }
    return ret;
}
