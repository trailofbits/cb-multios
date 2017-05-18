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
/*
 * Provides the low-level RPC protocol used by the generated C code
 */
#include "cgc_stdlib.h"
#include "cgc_librpc.h"

cgc_ssize_t cgc__rpc_recv(rpc_common *rpc, unsigned char *buf, cgc_size_t size)
{
    unsigned int hdr;
    cgc_size_t bytes;

    if (cgc_receive(rpc->fdr, &hdr, 4, &bytes) != 0 || bytes != 4)
        return -1;

    if (hdr >> 31)
        // TODO support multiple fragments
        return -1;

    if (hdr > size)
        return -1;

    if (cgc_receive(rpc->fdr, buf, hdr, &bytes) != 0 || bytes != hdr)
        return -1;

    return hdr;
}

int cgc__rpc_send(rpc_common *rpc, unsigned char *buf, cgc_size_t size)
{
    unsigned int hdr;
    cgc_size_t bytes;

    hdr = size;
    if (cgc_transmit(rpc->fdw, &hdr, 4, &bytes) != 0 || bytes != 4)
        return -1;

    if (cgc_transmit(rpc->fdw, buf, hdr, &bytes) != 0 || bytes != hdr)
        return -1;

    return 0;
}
