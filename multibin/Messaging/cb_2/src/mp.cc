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
#include "mp.h"

static void _MsgSend(int fd, int id, int selector, int next_fd, int next_id, int next_selector, int nargs, ...)
{
    va_list ap;
    FILE *fp = fopen(fd, 1);
    fwrite(&id, sizeof(int), fp);
    fwrite(&selector, sizeof(int), fp);
    fwrite(&nargs, 1, fp);
    fwrite(&next_fd, sizeof(int), fp);
    fwrite(&next_id, sizeof(int), fp);
    fwrite(&next_selector, sizeof(int), fp);

    va_start(ap, nargs);
    for (int i = 0; i < nargs; i++)
    {
        // do stuff
        proxy_argument *arg = va_arg(ap, proxy_argument *);
        arg->send(fp);
    }
    va_end(ap);
    fflush(fp);
}

void MsgSend1(const object& obj, int selector)
{
    _MsgSend(obj.d_fd, obj.d_id, selector, 0, 0, 0, 0);
}

void MsgSend(const object& obj, int selector, const object& next_obj, int next_selector)
{
    _MsgSend(obj.d_fd, obj.d_id, selector, next_obj.d_fd, next_obj.d_id, next_selector, 0);
}

void MsgSend1(const object& obj, int selector, proxy_argument a1)
{
    _MsgSend(obj.d_fd, obj.d_id, selector, 0, 0, 0, 1, &a1);
}

void MsgSend(const object& obj, int selector, const object& next_obj, int next_selector, proxy_argument a1)
{
    _MsgSend(obj.d_fd, obj.d_id, selector, next_obj.d_fd, next_obj.d_id, next_selector, 1, &a1);
}

void MsgSend1(const object& obj, int selector, proxy_argument a1, proxy_argument a2)
{
    _MsgSend(obj.d_fd, obj.d_id, selector, 0, 0, 0, 2, &a1, &a2);
}

void MsgSend(const object& obj, int selector, const object& next_obj, int next_selector, proxy_argument a1, proxy_argument a2)
{
    _MsgSend(obj.d_fd, obj.d_id, selector, next_obj.d_fd, next_obj.d_id, next_selector, 2, &a1, &a2);
}

