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

#include "cgc_rpncalc.h"

int
main(int cgc_argc, char *cgc_argv[]) {
    int cmd, ret;
    struct rpncalc_state state;

    cgc_rpncalc_init(&state);

    while (1) {
        if (cgc_read_all(STDIN, &cmd, sizeof(cmd)) != sizeof(cmd))
            continue;

        if (cmd == -1)
            break;

        ret = cgc_perform_rpncalc_op(&state, cmd);
        cgc_write_all(STDOUT, &ret, sizeof(ret));
    }

    cgc_rpncalc_destroy(&state);

    return 0;
}

