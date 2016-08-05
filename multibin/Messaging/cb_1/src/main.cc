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

#define TITL 0x4C544954
#define ALBM 0x4d424c41
#define ARTS 0x53545241

#define SMALL_LEN 60

class metadata
{
public:
    char *title;
    char _title[SMALL_LEN];
    char *album;
    char _album[SMALL_LEN];
    char *artist;
    char _artist[SMALL_LEN];

    object pkt;
    object saved_next;
    int saved_next_selector;

    int length;
    int offset;

    int frame_type;
};

// returns a null-terminated string
static char * escape_string(char *buf, const char *input, int length)
{
#define ESCAPE_CHR(x, y) else if (c == x) { buf[j++] = '\\'; buf[j++] = y; }
    int i, j;
    for (i = 0, j = 0; i < length; i++)
    {
        char c = input[i];

        if (0) {} /* placeholder */
        ESCAPE_CHR('\0', '0')
        ESCAPE_CHR('\b', 'b')
        ESCAPE_CHR('\r', 'r')
        ESCAPE_CHR('\n', 'n')
        ESCAPE_CHR('\t', 't')
        else buf[j++] = c;
    }
    buf[j] = 0;
    return buf;
}

DEFINE_CLASS(Metadata, metadata)
    PROC(Metadata, Constructor)
        ARGUMENT(object, pkt)
        NEW_CONTEXT(metadata);

        ctx->title = NULL;
        ctx->album = NULL;
        ctx->artist = NULL;
        ctx->pkt = pkt;
        ctx->saved_next = __next;
        ctx->saved_next_selector = __next_selector;

        MsgSend(pkt, (int)Packet::ReadBytes, self, (int)Metadata::ParseHeader, 9);
    PROC_END()

    PROC(Metadata, Destructor)
        if (ctx->title != NULL && ctx->title != ctx->_title)
            delete[] ctx->title;
        if (ctx->album != NULL && ctx->album != ctx->_album)
            delete[] ctx->album;
        if (ctx->artist != NULL && ctx->artist != ctx->_artist)
            delete[] ctx->artist;
        delete ctx;
    PROC_END()

    PROC(Metadata, ParseHeader)
        ARGUMENT(const_string, data)
        const char *buf = data.buffer();
        //fprintf(stderr, "ParseHeader: %s\n", buf);
        if (data.length() == 0 || memcmp(buf, "HDR", 3) != 0 || buf[3] != 5)
        {
            MsgSend1(ctx->saved_next, ctx->saved_next_selector, self);
        }
        else
        {
            int length = 0;
            length |= buf[5];
            length <<= 7;
            length |= buf[6];
            length <<= 7;
            length |= buf[7];
            length <<= 7;
            length |= buf[8];
            ctx->length = length;
            ctx->offset = 0;
            MsgSend1(self, (int)Metadata::ReadFrame);
        }
    PROC_END()

    PROC(Metadata, ReadFrame)
        //fprintf(stderr, "ReadFrame: length=%d, offset=%d\n", ctx->length, ctx->offset);
        if (ctx->offset + 8 < ctx->length)
            MsgSend(ctx->pkt, (int)Packet::ReadBytes, self, (int)Metadata::ParseFrame, 8);
        else
            MsgSend1(ctx->saved_next, ctx->saved_next_selector, self);
    PROC_END()

    PROC(Metadata, ParseFrame)
        ARGUMENT(const_string, data)
        const char *buf = data.buffer();
        //fprintf(stderr, "ParseFrame: length=%d, data=%s\n", data.length(), data.buffer());
        if (data.length() == 0)
        {
            MsgSend1(ctx->saved_next, ctx->saved_next_selector, self);
        }
        else
        {
            ctx->offset += 8;

            ctx->frame_type = *(int*)buf;
            int length = 0;
            length |= buf[4];
            length <<= 7;
            length |= buf[5];
            length <<= 7;
            length |= buf[6];
            length <<= 7;
            length |= buf[7];

            //fprintf(stderr, "ParseFrame: length=%d, offset=%d\n", length, ctx->offset);
            MsgSend(ctx->pkt, (int)Packet::ReadBytes, self, (int)Metadata::ParseFrameData, length);
        }
    PROC_END()

    PROC(Metadata, ParseFrameData)
        ARGUMENT(const_string, data)
        const char *buf = data.buffer();
        int length = data.length();
        //fprintf(stderr, "ParseFrameData: type=%08X, length=%d, data=%s\n", ctx->frame_type, data.length(), data.buffer());
        if (data.length() == 0)
        {
            MsgSend1(ctx->saved_next, ctx->saved_next_selector, self);
        }
        else
        {
            ctx->offset += data.length();
            char *dst;
#ifdef PATCHED_1
            int alloc_length = 2 * length + 1;
#else
            int alloc_length = length + 1;
#endif

            switch (ctx->frame_type)
            {
            case TITL:
                if (alloc_length <= SMALL_LEN) dst = ctx->_title;
                else dst = new char [alloc_length];
                ctx->title = escape_string(dst, buf, length);
                break;
            case ALBM:
                if (alloc_length <= SMALL_LEN) dst = ctx->_album;
                else dst = new char [alloc_length];
                ctx->album = escape_string(dst, buf, length);
                break;
            case ARTS:
                if (alloc_length <= SMALL_LEN) dst = ctx->_artist;
                else dst = new char [alloc_length];
                ctx->artist = escape_string(dst, buf, length);
                break;
            }
            MsgSend1(self, (int)Metadata::ReadFrame);
        }
    PROC_END()

    PROC(Metadata, Dump)
        ARGUMENT(object, connection)

        if (ctx->title)
        {
            MsgSend1(connection, (int)Connection::WriteBytes, const_string("Title: "));
            MsgSend1(connection, (int)Connection::WriteBytes, const_string(ctx->title));
            MsgSend1(connection, (int)Connection::WriteBytes, const_string("\n"));
        }

        if (ctx->album)
        {
            MsgSend1(connection, (int)Connection::WriteBytes, const_string("Album: "));
            MsgSend1(connection, (int)Connection::WriteBytes, const_string(ctx->album));
            MsgSend1(connection, (int)Connection::WriteBytes, const_string("\n"));
        }

        if (ctx->artist)
        {
            MsgSend1(connection, (int)Connection::WriteBytes, const_string("Artist: "));
            MsgSend1(connection, (int)Connection::WriteBytes, const_string(ctx->artist));
            MsgSend1(connection, (int)Connection::WriteBytes, const_string("\n"));
        }

        CONTINUE();
    PROC_END()
DEFINE_CLASS_END()

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    char *secret_page = (char *)secret_page_i;
    (void) secret_page;

    runMetadata();

    return 0;
}
