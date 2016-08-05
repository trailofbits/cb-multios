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
#include <cstring.h>
#include "array.h"
#include "eval.h"
#include "parser.h"

const char *program = R"==END==(

proc encode_uint16(x):
    return chr(x >> 8) + chr(x)

proc encode_uint32(x):
    return chr(x >> 24) + chr(x >> 16) + chr(x >> 8) + chr(x)

proc read_uint16():
    var x
    x = ord(read(1)) << 8
    x = x | ord(read(1))
    return x

proc read_uint32():
    var x
    x = ord(read(1)) << 24
    x = x | (ord(read(1)) << 16)
    x = x | (ord(read(1)) << 8)
    x = x | (ord(read(1)))
    return x

proc main():
    echo(encode_uint32(0xdeadbeef))
    echo(encode_uint32(0x4347c000))

    var password = flag(0)
    var running = 1
    var numbers = Array()
    while running:
        var op = read_uint16()

        if op == 0xA80B:
            break
        elif op == 0x4141:
            var j = read_uint32()
            if j == password:
                var i = read_uint32()
                var f = flag(read_uint32())
                aset(numbers, i, f)
        elif op == 0xA097:
            var i = read_uint32()
            echo(encode_uint32(aget(numbers, i)))
        elif op == 0x2064:
            var i = read_uint32()
            aset(numbers, i, read_uint32())
        elif op == 0x2C56:
            var a = aget(numbers, read_uint32())
            var b = aget(numbers, read_uint32())
            aset(numbers, read_uint32(), a + b)
        elif op == 0x973D:
            var a = aget(numbers, read_uint32())
            var b = aget(numbers, read_uint32())
            aset(numbers, read_uint32(), a - b)
        elif op == 0xE925:
            var a = aget(numbers, read_uint32())
            var b = aget(numbers, read_uint32())
            aset(numbers, read_uint32(), a * b)
        elif (op == 0x71B8) || (op == 0x1510):
            var start = read_uint32()
            var end = read_uint32()
            var sum = (op == 0x1510)
            while start < end:
                var num = aget(numbers, start)
                if op == 0x71B8:
                    sum = sum + num
                else:
                    sum = sum * num
                start = start + 1
            aset(numbers, read_uint32(), sum)
        elif op == 0xC4C5:
            aset(numbers, read_uint32(), rand())
        else:
            echo(encode_uint32(op))

main()
)==END==";

static bool builtin_echo(void *arg, Evaluator &eval, const vector<unique_ptr<Var>>& args, unique_ptr<Var>& result)
{
    for (unsigned int i = 0; i < args.length(); i++)
    {
        Var *var = args[i].get();
        if (var == nullptr || var->getType() != VarType::String)
        {
            fprintf(stderr, "Error: bad type in echo\n");
            return false;
        }

        StringVar *svar = static_cast<StringVar *>(var);
        fwrite(svar->getBuffer(), svar->getLength(), stdout);
    }

    result.reset(nullptr);
    return true;
}

static bool builtin_read(void *arg, Evaluator &eval, const vector<unique_ptr<Var>>& args, unique_ptr<Var>& result)
{
    if (args.length() != 1 || !args[0] || args[0]->getType() != VarType::Number)
        return false;
    unsigned int length = static_cast<NumberVar*>(args[0].get())->getValue();
    unique_ptr<StringVar> svar = new StringVar();
    svar->resize(length);
    if (fread(svar->getBuffer(), length, stdin) != length)
        return false;
    result.reset(svar.release());
    return true;
}

static bool builtin_flag(void *arg, Evaluator &eval, const vector<unique_ptr<Var>>& args, unique_ptr<Var>& result)
{
    if (args.length() != 1 || !args[0] || args[0]->getType() != VarType::Number)
        return false;
    const unsigned int *secret_page = reinterpret_cast<const unsigned int *>(arg);
    NumberVar *var = new NumberVar(secret_page[static_cast<NumberVar*>(args[0].get())->getValue() & 0x3ff]);
    result.reset(var);
    return true;
}

static bool builtin_chr(void *arg, Evaluator &eval, const vector<unique_ptr<Var>>& args, unique_ptr<Var>& result)
{
    if (args.length() != 1 || !args[0] || args[0]->getType() != VarType::Number)
        return false;
    StringVar *svar = new StringVar();
    svar->resize(1);
    svar->getBuffer()[0] = static_cast<NumberVar*>(args[0].get())->getValue();
    result.reset(svar);
    return true;
}

static bool builtin_ord(void *arg, Evaluator &eval, const vector<unique_ptr<Var>>& args, unique_ptr<Var>& result)
{
    if (args.length() != 1 || !args[0] || args[0]->getType() != VarType::String)
        return false;
    StringVar *svar = static_cast<StringVar*>(args[0].get());
    if (svar->getLength() < 1)
        return false;
    result.reset(new NumberVar((unsigned char)svar->getBuffer()[0]));
    return true;
}

static bool builtin_rand(void *arg, Evaluator &eval, const vector<unique_ptr<Var>>& args, unique_ptr<Var>& result)
{
    static unsigned int state = 0x4347c000;
    static unsigned int idx = 0;
    const unsigned short *secret_page = reinterpret_cast<const unsigned short *>(arg);

    state ^= secret_page[idx];
    state ^= secret_page[idx+2];
    idx = (idx + 4) & 0x3ff;
    state *= 1234567;

    NumberVar *var = new NumberVar(state);
    result.reset(var);
    return true;
}

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    char *secret_page = (char *)secret_page_i;

    Parser parser(program);
    if (parser.parse())
    {
        Evaluator eval(parser.releaseRoot());
        ArrayVar::registerExternals(eval);
        eval.addExternal("chr", builtin_chr);
        eval.addExternal("echo", builtin_echo);
        eval.addExternal("ord", builtin_ord);
        eval.addExternal("flag", builtin_flag, secret_page);
        eval.addExternal("rand", builtin_rand, secret_page);
        eval.addExternal("read", builtin_read);
        if (!eval.run())
        {
            fprintf(stderr, "Eval error\n");
        }
    }
    else
    {
        fprintf(stderr, "Program error\n");
    }

    return 0;
}
