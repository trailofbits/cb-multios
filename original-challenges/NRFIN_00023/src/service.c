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

#include "stock.h"

enum command_type {
    LIST_STOCKS,
    LIST_ORDERS,
    PLACE_ORDER,
    CHECK_ORDER,
    CANCEL_ORDER,
    QUIT
};

struct command {
    enum command_type type;
    unsigned int arg0, arg1, arg2, arg3;
};

static struct stock_state state = {};

int
main(void) {
    int cmd_ret = 0;
    size_t size = 0;
    struct command cmd = {};

    stock_init(&state);

    while (1) {
        if (read_all(STDIN, &cmd, sizeof(cmd)) != sizeof(cmd))
            continue;

        switch (cmd.type) {
        case LIST_STOCKS:
            cmd_ret = cmd_list_stocks(&state);
            break;
        case LIST_ORDERS:
            cmd_ret = cmd_list_orders(&state, (char *)&cmd.arg0);
            break;
        case PLACE_ORDER:
            cmd_ret = cmd_place_order(&state, (char *)&cmd.arg0, cmd.arg1,
                    cmd.arg2, cmd.arg3);
            break;
        case CHECK_ORDER:
            cmd_ret = cmd_check_order(&state, cmd.arg0);
            break;
        case CANCEL_ORDER:
            cmd_ret = cmd_cancel_order(&state, cmd.arg0);
            break;
        case QUIT:
            goto out;
        default:
            cmd_ret = -1;
        }

        write_all(STDOUT, &cmd_ret, sizeof(cmd_ret));
    }
   
out:
    stock_destroy(&state);

    return 0;
}

