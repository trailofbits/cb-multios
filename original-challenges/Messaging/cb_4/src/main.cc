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
#include <cstdlib.h>
#include <cstdio.h>
#include <cstring.h>
#include "mp.h"

extern "C" int rs_decode(unsigned char *encoded, int n_parity);

class packet
{
public:
    int length;
    unsigned char *data;
    int idx;
};

DEFINE_CLASS(Packet, packet)
    PROC(Packet, Constructor)
        ARGUMENT(int, hdr)
        ARGUMENT(const_string, data)
        NEW_CONTEXT(packet);

        int parity = (hdr >> 4) * 4;
        int data_per_block = 255 - parity;
        int blocks = (data.length() + 254) / 255;
        int missing = blocks * 255 - data.length();
        ctx->length = blocks * data_per_block - missing;
        ctx->data = new unsigned char [ctx->length];
        ctx->idx = 0;

        fprintf(stderr, "blocks %d, data_per_block %d, missing %d\n", blocks, data_per_block, missing);

        unsigned char encoded[255];
        for (int i = 0; i < blocks; i++)
        {
            if (i == blocks - 1)
            {
                memcpy(encoded, data.buffer() + i * 255, 255 - missing);
                memset(encoded + 255 - missing, 0, missing);
            }
            else
            {
                memcpy(encoded, data.buffer() + i * 255, 255);
            }

            // TODO check return value
            if (parity > 0)
                rs_decode(encoded, parity);

            if (i == blocks - 1)
            {
                memcpy(ctx->data + i * data_per_block, encoded + parity, data_per_block - missing);
            }
            else
            {
                memcpy(ctx->data + i * data_per_block, encoded + parity, data_per_block);
            }
        }

        CONTINUE((proxy_argument)self, hdr & 0xf);
    PROC_END()

    PROC(Packet, Destructor)
        delete ctx->data;
        delete ctx;
    PROC_END()

    PROC(Packet, ReadBytes)
        ARGUMENT(int, length)
        int remaining = ctx->length - ctx->idx;
        if (length < 0 || length > remaining)
        {
            CONTINUE(const_string("", 0));
        }
        else
        {
            const_string result((const char *)&ctx->data[ctx->idx], length);
            ctx->idx += length;
            CONTINUE(result);
        }
    PROC_END()
DEFINE_CLASS_END()

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    char *secret_page = (char *)secret_page_i;
    (void) secret_page;

    runPacket();

    return 0;
}
