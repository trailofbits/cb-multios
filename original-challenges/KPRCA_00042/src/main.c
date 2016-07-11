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

#include <stdlib.h>

#include "cmdb.h"
#include "user.h"
#include "admin.h"
#include "debug.h"

enum {DEBUG = 0, ADMIN = 1, USER = 2};

int main()
{
    int exited = 0;
    int user = USER;

    init_movies();
    printf("========= Movie Rental Service v0.1 =========\n");
    printf("   . . . Initializing the inventory . . .\n");
    printf("         (movie info from IMDb.com)\n");
    printf("=============================================\n");


    while (!exited) {
        if (user == USER)
            exited = run_user_mode(&user);
        else if(user == ADMIN)
        {
            if (run_admin_mode(&user) < 0)
                exited = 1;
        }
        else if(user == DEBUG)
            run_debug_mode(&user);

        if (!exited)
            printf("\n");
    }
    printf("Bye!\n");
}
