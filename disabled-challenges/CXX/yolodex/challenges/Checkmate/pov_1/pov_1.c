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

#include "libpov.h"

#define NEGOTIATE_FD (3)
#define INITIAL_BOARD_LEN (1144)

static const char *pov = "e4%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x\n";
static const char *quit = "quit\n";

int
main(int cgc_argc, char *cgc_argv[])
{
    cgc_size_t len;
    char *endp, *line = NULL;
    unsigned int flag = 0;
    static char buf[4096];

    unsigned negotiate = 2;
    unsigned params[3];

    if (cgc_transmit_all(NEGOTIATE_FD, &negotiate, sizeof(negotiate)) != 0)
        return -1;

    if (cgc_length_read(NEGOTIATE_FD, (unsigned char *)&params, sizeof(params)) != sizeof(params))
        return -1;

    if (cgc_length_read(STDIN, (unsigned char *)buf, INITIAL_BOARD_LEN) != INITIAL_BOARD_LEN)
        return -1;

    len = cgc_strlen(pov);
    if (cgc_transmit_all(STDOUT, pov, len) != 0)
        return -1;

    // Intial newline
    if (cgc_length_read(STDIN, (unsigned char *)buf, 1) != 1)
        return -1;

    // Printed move string
    cgc_delimited_read(STDIN, (unsigned char **)&line, (unsigned int *)&len, (unsigned char *)"\n", 1);
    flag = cgc_strtoul(line + len - 9, &endp, 16);

    if (cgc_transmit_all(NEGOTIATE_FD, &flag, sizeof(flag)) != 0)
        return -1;

    len = cgc_strlen(quit);
    if (cgc_transmit_all(STDOUT, quit, len) != 0)
        return -1;

    return 0;
}

