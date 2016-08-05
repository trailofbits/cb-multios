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
#include "strinfo.h"
#ifdef DEBUG
 // this is the libc from EAGLE_00005/pov_1/
 // the only change I've made is to define fprintf() in e_libc.c
 // this is only used when debugging.
#include "e_libc.h"
#endif

#define GIMME "Give me your sentences.\x03"
#define DONE "Here are your results...\x03"
#define TERM '\x03'

#define INBUFSZ 1024

int main(void) {

    char input[INBUFSZ] = {0};
    int bytes_recv = 0;

    #ifdef DEBUG
        char *s_ptr = (char *)FLAG_PAGE;
        fprintf(stderr, "FLAG: ");
        for (unsigned int i = 0; i < 10; i++) {
            fprintf(stderr, "%02x", (unsigned char) *s_ptr++);
        }
        fprintf(stderr, "\n");
    #endif

    while(1) {
        struct results r;
        // ask for input.
        if (24 != send_bytes(STDOUT, GIMME, 24)) {
            _terminate(10);
        }
        #ifdef DEBUG
        fprintf(stderr, "sent GIMME\n");
        #endif

        memset(input, 0, INBUFSZ);
        memset(&r, 0, sizeof(r));

        // get input
        // bug: 1048 > INBUFSZ
        //  Allows overwrite of VA of _start and write OOB beyond input buf to cause SEGFAULT.
        //  The bytes are read by the input parsing code, but not written to registers.
        //  Not a CFE POV.
        if (0 > (bytes_recv = recv_until_delim_n(STDIN, TERM, input, 1048))) {
            _terminate(20);
        }
        #ifdef DEBUG
        fprintf(stderr, "recvd input bytes\n");
        #endif

        // process input
        if (SUCCESS != process(input, TERM, &r)) {
            _terminate(15);
        }
        #ifdef DEBUG
        fprintf(stderr, "processed input\n");
        #endif

        // send results
        if (25 != send_bytes(STDOUT, DONE, 25)) {
            _terminate(10);
        }
        #ifdef DEBUG
        fprintf(stderr, "sent TERM\n");
        #endif
        if (sizeof(r) != send_bytes(STDOUT, (const char *)&r, sizeof(r))) {
            _terminate(10);
        }

    }
    return 0;
}


