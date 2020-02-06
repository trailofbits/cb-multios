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
#include "cgc_cstdlib.h"
#include "cgc_cstdio.h"
#include "cgc_cstring.h"
#include "cgc_mp.h"

class connection
{
};

DEFINE_CLASS(Connection, connection)
    PROC(Connection, Constructor)
        NEW_CONTEXT(connection);
        CONTINUE(self);
    PROC_END()

    PROC(Connection, Destructor)
        delete ctx;
    PROC_END()

    PROC(Connection, ReadInteger)
        int result;
        if (cgc_fread(&result, sizeof(result), cgc_stdin) <= 0)
        {
            MsgSend1(ServerStatic, (int)Server::Shutdown);
        }
        else
        {
            CONTINUE(result);
        }
    PROC_END()

    PROC(Connection, ReadBytes)
        ARGUMENT(int, length);
        char *buf = new char [length];
        if (cgc_fread(buf, length, cgc_stdin) <= 0)
        {
            MsgSend1(ServerStatic, (int)Server::Shutdown);
        }
        else
        {
            CONTINUE(const_string(buf, length));
            delete[] buf;
        }
    PROC_END()

    PROC(Connection, ReadPacket)
        unsigned int size = 1000, i = 0, eor = 0;
        char *buf = (char *)cgc_malloc(size);
        while (1)
        {
            if (cgc_fread(&buf[i], 1, cgc_stdin) <= 0)
            {
                MsgSend1(ServerStatic, (int)Server::Shutdown);
                break;
            }

            if (buf[i] == 0x7F) break;
            else if (buf[i] == 0x7E) eor = 0x40;
            else
            {
                buf[i] ^= eor;
                eor = 0;
                i++;
            }

            if (i == size)
            {
                size += 1000;
                buf = (char *)cgc_realloc(buf, size);
            }
        }
        CONTINUE(const_string(buf, i));
        cgc_free(buf);
    PROC_END()

    PROC(Connection, WriteBytes)
        ARGUMENT(const_string, data);
        cgc_fwrite(data.buffer(), data.length(), cgc_stdout);
        CONTINUE();
    PROC_END()
DEFINE_CLASS_END()

extern "C" int main(int secret_page_i,  char *unused[]) {
    secret_page_i = CGC_FLAG_PAGE_ADDRESS;

    char *secret_page = (char *)secret_page_i;
    (void) secret_page;

    runConnection();

    return 0;
}
