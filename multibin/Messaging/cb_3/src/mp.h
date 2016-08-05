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
#pragma once

#include <cstdio.h>
#include <cstdlib.h>
#include <cstring.h>

#define MAX_ARGUMENTS 4

#define DEFINE_CLASS(cls, clsctx) \
void run##cls() \
{ \
    FILE *__fp = fopen(__##cls##_fd + 1, 0); \
    while (true) \
    { \
        int __id; \
        int __selector; \
        int __next_selector; \
        object __next(0, 0); \
        unsigned char __nargs; \
        clsctx *ctx; \
        proxy_argument __args[MAX_ARGUMENTS]; \
        fread(&__id, sizeof(int), __fp); \
        fread(&__selector, sizeof(int), __fp); \
        fread(&__nargs, 1, __fp); \
        fread(&__next.d_fd, sizeof(int), __fp); \
        fread(&__next.d_id, sizeof(int), __fp); \
        fread(&__next_selector, sizeof(int), __fp); \
        for (int i = 0; i < __nargs; i++) \
        { \
            __args[i] = proxy_argument::read(__fp); \
        } \
        ctx = (clsctx *)__id; \
        object self(__##cls##_fd, __id); \
        if (__selector < 0) break; \
        switch ((cls)__selector) \
        {
#define DEFINE_CLASS_END() \
        } \
    } \
}

#define PROC(cls, selector) \
case cls::selector: { \
    int __nused_args = 0; (void) __nused_args;
#define ARGUMENT(type, name) \
    type name = __args[__nused_args++];
#define NEW_CONTEXT(clsctx) do { \
    ctx = new clsctx; \
    self.d_id = (int) ctx; \
} while (0)
#define CONTINUE(...) do { \
    if (__next.d_fd > 0) MsgSend1(__next, __next_selector, ## __VA_ARGS__); \
} while (0)
#define PROC_END() \
} \
break;

#define DECLARE_CLASS(cls, fd) \
static const int __##cls##_fd = fd; \
static const object cls##Static (fd, 0); \
enum class cls : int {
#define DECLARE_CLASS_END() \
};

class string
{
private:
    char *d_buf;
    unsigned int d_length;
public:
    string() : d_buf(NULL), d_length(0) {}
    string(char *buf, unsigned int length) : d_buf(buf), d_length(length) {}

    char *buffer() const { return d_buf; }
    unsigned int length() const { return d_length; }
};

class const_string
{
private:
    const char *d_buf;
    unsigned int d_length;
public:
    const_string() : d_buf(NULL), d_length(0) {}
    const_string(const char *buf, unsigned int length) : d_buf(buf), d_length(length) {}
    const_string(const char *buf) : d_buf(buf)
    {
        d_length = strlen(buf);
    }
    const_string(const string& s)
    {
        d_buf = s.buffer();
        d_length = s.length();
    };

    const char *buffer() const { return d_buf; }
    unsigned int length() const { return d_length; }
};

class object
{
public:
    int d_fd;
    int d_id;

    object() : d_fd(0), d_id(0) {}
    object(int fd, int id) : d_fd(fd), d_id(id) {}
};

class proxy_argument
{
private:
    enum class type : char
    {
        None,
        Integer,
        String,
        Float,
        Object
    };
    type d_type;
    union value {
        value(int x) : integer(x) {}
        value(float x) : fp(x) {}
        value(const_string s) : string(s) {}
        value(object o) : obj(o) {}

        int integer;
        const_string string;
        float fp;
        object obj;
    } d_value;

public:
    proxy_argument() : d_type(type::None), d_value(0) {}
    proxy_argument(int value) : d_type(type::Integer), d_value(value) {}
    proxy_argument(float value) : d_type(type::Float), d_value(value) {}
    proxy_argument(const const_string &s) : d_type(type::String), d_value(s) {}
    proxy_argument(const char *s) : d_type(type::String), d_value(const_string(s)) {}
    proxy_argument(const object &o) : d_type(type::Object), d_value(o) {}

    operator const char *() { return d_value.string.buffer(); }
    operator int () { return d_value.integer; }
    operator float () { return d_value.fp; }
    operator object () { return d_value.obj; }
    operator const_string () { return d_value.string; }

    void send(FILE *f)
    {
        fwrite(&d_type, 1, f);
        switch (d_type)
        {
        case type::None:
            break;
        case type::Integer:
            fwrite(&d_value.integer, sizeof(int), f);
            break;
        case type::Float:
            fwrite(&d_value.fp, sizeof(float), f);
            break;
        case type::String: {
                unsigned int len = d_value.string.length();
                fwrite(&len, sizeof(len), f);
                fwrite(d_value.string.buffer(), len, f);
            }
            break;
        case type::Object:
            fwrite(&d_value.obj.d_fd, sizeof(int), f);
            fwrite(&d_value.obj.d_id, sizeof(int), f);
            break;
        }
    }

    static proxy_argument read(FILE *f)
    {
        unsigned char t;
        fread(&t, 1, f);
        switch ((type)t)
        {
        case type::None:
            return proxy_argument();
        case type::Integer: {
                int x;
                fread(&x, sizeof(int), f);
                return x;
            }
        case type::Float: {
                float x;
                fread(&x, sizeof(float), f);
                return x;
            }
        case type::String: {
                unsigned int len;
                char *s;
                fread(&len, sizeof(len), f);
                s = new char [len];
                fread(s, len, f);
                return const_string(s, len);
            }
        case type::Object: {
                int fd;
                int id;
                fread(&fd, sizeof(int), f);
                fread(&id, sizeof(id), f);
                return object(fd, id);
            }
        }
    }
};

void MsgSend1(const object& obj, int selector);
void MsgSend1(const object& obj, int selector, proxy_argument a1);
void MsgSend1(const object& obj, int selector, proxy_argument a1, proxy_argument a2);
void MsgSend(const object& obj, int selector, const object& next, int next_selector);
void MsgSend(const object& obj, int selector, const object& next, int next_selector, proxy_argument a1);
void MsgSend(const object& obj, int selector, const object& next, int next_selector, proxy_argument a1, proxy_argument a2);

DECLARE_CLASS(Metadata, 3)
    Constructor,
    Destructor,
    Dump,
    ParseHeader,
    ParseFrame,
    ParseFrameData,
    ReadFrame
DECLARE_CLASS_END()

DECLARE_CLASS(Connection, 5)
    Constructor,
    Destructor,
    ReadInteger,
    ReadBytes,
    ReadPacket,
    WriteBytes
DECLARE_CLASS_END()

DECLARE_CLASS(Server, 7)
    Shutdown,
    Constructor,
    Destructor,
    MainLoop,
    NewPacket,
    ParsePacket,
    HandleMetadata,
DECLARE_CLASS_END()

DECLARE_CLASS(Packet, 9)
    Constructor,
    Destructor,
    ReadBytes
DECLARE_CLASS_END()
