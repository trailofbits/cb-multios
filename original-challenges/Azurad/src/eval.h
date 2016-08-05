/*
 * Copyright (c) 2016 Kaprica Security, Inc.
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

#include "ccstring.h"
#include "parser.h"
#include "map.h"
#include "pair.h"
#include "unique_ptr.h"

class Evaluator;
class Scope;

enum class VarType
{
    Nil,
    Proc,
    String,
    Number,
    Array
};

class Var
{
public:
    Var() : Var(VarType::Nil) {}
    Var(VarType type);
    virtual ~Var();

    VarType getType() const { return type; }
    virtual Var* copy() { return new Var(type); }
protected:
    VarType type;
};

class Procedure : public Var
{
public:
    Procedure(Scope &scope, Node *arglist, Node *block, unsigned int indent);
    ~Procedure();

    Procedure(const Procedure &other)
        : Var(other.type), scope(other.scope)
    {
        block = other.block;
        indent = other.indent;
        args = other.args;
    }
    Procedure& operator=(const Procedure &) = delete;

    Var* copy();

    const vector<CString>& getArguments() const { return args; }
    Node *getBlock() { return block; }
    unsigned int getIndent() { return indent; }
    Scope& getScope() { return scope; }
private:
    Scope &scope;
    Node *block;
    unsigned int indent;
    vector<CString> args;
};

class NumberVar : public Var
{
public:
    NumberVar(unsigned int val);
    ~NumberVar();

    NumberVar(const NumberVar &other)
        : Var(other.type)
    {
        value = other.value;
    }
    NumberVar& operator=(const NumberVar &) = delete;

    static void registerOps(Evaluator &);
    Var* copy();

    unsigned int getValue() { return value; }
private:
    unsigned int value;
};

class StringVar : public Var
{
public:
    StringVar();
    ~StringVar();

    StringVar(const StringVar &other)
        : Var(other.type)
    {
        data = other.data;
    }
    StringVar& operator=(const StringVar &) = delete;

    static void registerOps(Evaluator &);
    Var* copy();

    char *getBuffer() { return data.length() == 0 ? nullptr : &data[0]; }
    unsigned int getLength() { return data.length(); }
    void resize(unsigned int length) { data.resize(length); }
private:
    vector<char> data;
};

class Scope
{
    friend class Evaluator;
public:
    Scope(Scope *parent);
    ~Scope();

    unique_ptr<Var>* findName(const CString& name);

    Scope *parent, *procScope;
    map<CString, unique_ptr<Var>> names;
    unique_ptr<Var> retval;
    bool breaking;
    bool returning;
};

class Evaluator
{
public:
    typedef bool (*External) (void *arg, Evaluator& eval, const vector<unique_ptr<Var>>& args, unique_ptr<Var>& result);
    typedef bool (*OpFunc) (const CString& op, Var* a, Var* b, unique_ptr<Var>& result);

    Evaluator(Node *root);
    ~Evaluator();

    bool run();
    void addExternal(const char *identifier, External func, void *arg);
    void addExternal(const char *identifier, External func) { addExternal(identifier, func, nullptr); }
    void addOp(const CString& op, VarType a, VarType b, OpFunc func);
private:
    bool eval_block(Scope& scope, Node *node, unsigned int indent);
    bool eval_expr(Scope& scope, Node *node, unique_ptr<Var>& outresult);
    bool eval_op(const CString& op, Var* a, Var* b, unique_ptr<Var>& outresult);
private:
    struct _Op
    {
        VarType a;
        VarType b;
        OpFunc fn;
    };
    Node *root;
    map<CString, pair<External, void *>> externals;
    map<CString, vector<_Op>> operators;
};
