/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "cgc_stdlib.h"

#include "cgc_cmdb.h"
#include "cgc_user.h"
#include "cgc_admin.h"
#include "cgc_debug.h"

enum {DEBUG = 0, ADMIN = 1, USER = 2};

int main(int cgc_argc, char *cgc_argv[])
{
    int exited = 0;
    int user = USER;

    cgc_init_movies();
    cgc_printf("========= Movie Rental Service v0.1 =========\n");
    cgc_printf("   . . . Initializing the inventory . . .\n");
    cgc_printf("         (movie info from IMDb.com)\n");
    cgc_printf("=============================================\n");


    while (!exited) {
        if (user == USER)
            exited = cgc_run_user_mode(&user);
        else if(user == ADMIN)
        {
            if (cgc_run_admin_mode(&user) < 0)
                exited = 1;
        }
        else if(user == DEBUG)
            cgc_run_debug_mode(&user);

        if (!exited)
            cgc_printf("\n");
    }
    cgc_printf("Bye!\n");
}
