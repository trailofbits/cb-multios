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
#include "cttp.h"

/**
 * Make some backups of the flag page
 *
 * @param s Destination
 * @param np Number of times to copy it
 */
void initialize(char *s, size_t np) {
    size_t i;

    if (np > 16)
        return;

    for (i = 0; i < np; i++)
        memcpy(s+(i*PAGE_SIZE), (char *)FLAG_PAGE, PAGE_SIZE);
}

int main() {
    char stack[PAGE_SIZE*16];

    int fd;
    fd_set readfds;
    int numready = 0;
    struct timeval timeout = {2, 0};
    size_t i, res, recvd = 0;

    //lets be nice and make some backup copies of the flag page :)
    initialize(stack, 16);

    //get our stack cookies ready
    __stack_cookie_init();

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);

        res = fdwait(fd+1, &readfds, NULL, &timeout, &numready);

        if (!res && numready) {
            if (!handle_request())
                break;
        } else {
            break;
        }
    }

    //send stats!
    print_stats();

    return 0;
}
