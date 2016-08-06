/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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
#include <stdarg.h>

#include "IO.h"

DefineClass(IO, Object)

DefineFunction(IO, void, $init)
{
    this->input_fd = STDIN;
    this->output_fd = STDOUT;
}

DefineFunction(IO, void, format, const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfdprintf(this->output_fd, fmt, ap);
    va_end(ap);
}

DefineFunction(IO, void, wait_for, char c)
{
    char in;

    do {
        size_t bytes;
        if (receive(this->input_fd, &in, 1, &bytes) != 0 || bytes != 1)
            break;
    } while (in != c);
}

DefineFunction(IO, void, wait_for_input)
{
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(this->input_fd, &rfds);

    // wait indefinitely for user input
    fdwait(this->input_fd + 1, &rfds, NULL, NULL, NULL);
}

DefineFunction(IO, size_t, receive, void *buf, size_t count)
{
    size_t bytes;
    if (receive(this->input_fd, buf, count, &bytes) != 0)
        bytes = 0;
    return bytes;
}
