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
#include "dealer.h"

static char OK[8] = {0};

/**
 * Create a checksum of the flag page to use as the OK byte string
 */
void gen_ok(void) {
    const char *fp = (char *)FLAG_PAGE;
    for (unsigned int idx = 0; idx < 4096; idx++) {
        OK[idx % 8] ^= fp[idx];
    }
}

int main(void) {

    ssize_t ret = 0;
    DBG("STARTING.\n");
    gen_ok();

    while (TRUE) {
        ret = process();

        SEND(STDOUT, (char *)OK, sizeof(OK));

        if (0 == ret) {
            DBG("process ok\n");
        } else {
            DBG("process quitting: %I\n", ret);
	        break;
        }

    }

    return 0;
}
