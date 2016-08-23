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

static char *secret_page;
static int hash_secret(int type)
{
    static unsigned int initial_state[] = {
        0,
        0x12345678,
        0x9abcdef,
        0x13579bdf,
        0x02468ace,
        0xdeadbeef,
        0xea7beef,
        0x98765432
    };
    unsigned int result = initial_state[type];
    for (int i = 0; i < 0x1000; i += 4)
    {
        int foo = *(int *)(secret_page + i);
        result = (result << 7) ^ (result >> 24);
        result ^= foo;
        result = (result << 13) ^ (result >> 20);
    }
    return result;
}

class server
{
public:
    object connection;
};

DEFINE_CLASS(Server, server)
    PROC(Server, Shutdown)
        MsgSend1(MetadataStatic, -1);
        MsgSend1(ConnectionStatic, -1);
        MsgSend1(ServerStatic, -1);
        MsgSend1(PacketStatic, -1);
    PROC_END()

    PROC(Server, Constructor)
        ARGUMENT(object, connection)
        NEW_CONTEXT(server);
        ctx->connection = connection;
        MsgSend1(self, (int)Server::MainLoop);
    PROC_END()

    PROC(Server, Destructor)
        delete ctx;
    PROC_END()

    PROC(Server, MainLoop)
        MsgSend(ctx->connection, (int)Connection::ReadPacket, self, (int)Server::NewPacket);
    PROC_END()

    PROC(Server, NewPacket)
        ARGUMENT(const_string, data)
        const char *buf = data.buffer();

        // verify header
        if (data.length() <= 2 || buf[0] != ~buf[1])
        {
            MsgSend1(self, (int)Server::MainLoop);
        }
        else
        {
            MsgSend(PacketStatic, (int)Packet::Constructor, self, (int)Server::ParsePacket, buf[0], const_string(buf+2, data.length()-2));
        }
    PROC_END()

    PROC(Server, ParsePacket)
        ARGUMENT(object, pkt)
        ARGUMENT(int, type)

        if (type == 0)
            MsgSend(MetadataStatic, (int)Metadata::Constructor, self, (int)Server::HandleMetadata, pkt);
        else
        {
            int hash = hash_secret(type);
            MsgSend(ctx->connection, (int)Connection::WriteBytes, self, (int)Server::MainLoop, const_string((char *)&hash, 4));
        }
    PROC_END()

    PROC(Server, HandleMetadata)
        ARGUMENT(object, metadata)

        MsgSend(metadata, (int)Metadata::Dump, self, (int)Server::MainLoop, ctx->connection);
        MsgSend1(metadata, (int)Metadata::Destructor);
    PROC_END()
DEFINE_CLASS_END()

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    secret_page = (char *)secret_page_i;

    MsgSend(ConnectionStatic, (int)Connection::Constructor, ServerStatic, (int)Server::Constructor);
    runServer();

    return 0;
}
