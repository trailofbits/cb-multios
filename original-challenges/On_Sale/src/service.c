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
#include "products.h"

static char STATUS_OK[2] 	= {0};
static char STATUS_ERR[2] 	= {0};
static char STATUS_QUIT[2]	= {0};

/**
 * Compute the status codes based on the values of the flag page
 */
void gen_status_codes(void) {
    const char *fp = (char *)FLAG_PAGE;
    for (unsigned int idx = 0; idx < 4094; idx += 3) {
        STATUS_OK[idx % 2]          ^= fp[idx];
        STATUS_ERR[(idx + 1) % 2]   ^= fp[idx + 1];
        STATUS_QUIT[(idx + 2) % 2]  ^= fp[idx + 2];
    }
}

/**
 * Send resulting status of command processing to client
 *
 * @param status_code  The 2 status code bytes to send.
 */
 void send_status(char *status_code) {
    SEND(STDOUT, status_code, 2);
}

int main(void) {

    short ret = 0;

    gen_status_codes();

    setup();

    while (TRUE) {
        ret = process_cmd();

        if (0 == ret) {
        	send_status((char *)STATUS_OK);
        } else if (-1 == ret) {
        	send_status((char *)STATUS_ERR);
        } else {
	        send_status((char *)STATUS_QUIT);
	        break;
        }
    }

    return 0;
}
