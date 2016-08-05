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
#include "election.h"

#define FAIL "Is voting too hard?!\n"


int main(void) {

    unsigned int choice = 0;
    int ret = SUCCESS;

    init_election();

    while (SUCCESS == ret) {
        print_menu(NO_AUTH);
        ret = get_choice(&choice);

        if (ERRNO_CONV != ret) {
            ret = decider(choice);

            // successful login will return creds
            if ((VOTER == ret) || (E_MGR == ret)) {
                print_menu(ret);
                ret = get_choice(&choice);

                if (ERRNO_CONV != ret) {
                    ret = decider(choice);
                    if (NO_AUTH == ret)
                        ret = -1;
                }
            } else if (NO_AUTH == ret) {
                ret = -1;
            }
        } else {
            break;
        }
    }

    if (0 > ret) {
        SEND(STDOUT, FAIL, sizeof(FAIL));
    }

    return 0;
}


