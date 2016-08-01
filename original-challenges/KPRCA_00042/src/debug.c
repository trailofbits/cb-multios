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

#include "cmdb_backend.h"
#include "readline.h"

#define LINE_SIZE 512

enum {DEBUG = 0, ADMIN = 1, USER = 2};

int run_debug_mode(int *user)
{
    char line[LINE_SIZE];
    unsigned int dcmd = 0;

    printf("##: ");
    readline(STDIN, line, LINE_SIZE);
    dcmd = (line[0] & 0xFF)<<24 | (line[1] & 0xFF)<<16 | (line[2] & 0xFF)<<8 | (line[3] & 0xFF);

    switch(dcmd) {
    case 1294579383: // = \x4D\x29\xB6\xB7
        dag(&line[4]);
        break;
    case 388502:     // = \x00\x05\xED\x96
        dar(&line[4]);
        break;
    default:
        *user = ADMIN;
    }

    return 0;
}
