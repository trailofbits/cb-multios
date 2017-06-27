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
#include "cgc_libc.h"
#include "cgc_operation.h"
#include "cgc_math_fun.h"
#include "cgc_service.h"

int main(int cgc_argc, char *cgc_argv[]) {

    uint8_t command[1];
    int ret = 0;

    while (1) {
        if ((ret = cgc_do_nonce()) == 0) {
            
            RECV(command, sizeof(uint8_t));

            switch (command[0]) {
                case 0: // create
                    ret = cgc_do_create();
                    break;
                case 1: // eval
                    ret = cgc_do_eval();
                    break;
                default:
                    // bad command input
                    ret = -150;
            }
        } 

        if (ret < 0) {
            SENDSI(ret);
            return ret;
        }
    }
    return ret;
}
