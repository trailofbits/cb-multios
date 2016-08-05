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
#include "array.h"

static inline int abs(int x)
{
    if (x < 0)
        return -x;
    else
        return x;
}

ArrayVar::ArrayVar()
    : Var(VarType::Array)
{
    array.reset(new Array());
}

ArrayVar::~ArrayVar()
{
}

Var* ArrayVar::copy()
{
    return new ArrayVar(*this);
}

bool Array::set(int i, Var* val)
{
    if (i < 0)
    {
        if (abs(i) > length())
            return false;
        i += length();
#ifdef PATCHED_1
        if (i < 0) return false;
#endif
    }

    if (i >= items.length())
    {
        if (i >= MAX_ITEMS)
            return false;

        items.resize(i + 1);
    }

    items[i].reset(val);
    return true;
}

bool Array::get(int i, Var** pval)
{
    if (i < 0)
    {
        if (abs(i) > length())
            return false;
        i += length();
#ifdef PATCHED_1
        if (i < 0) return false;
#endif
    }

    if (i >= items.length())
    {
        *pval = nullptr;
    }
    else
    {
        *pval = items[i].get();
    }
    return true;
}

static bool func_Array(void *arg, Evaluator& eval, const vector<unique_ptr<Var>>& args, unique_ptr<Var>& result)
{
    if (args.length() != 0)
        return false;
    result.reset(new ArrayVar());
    return true;
}

static bool func_aget(void *arg, Evaluator& eval, const vector<unique_ptr<Var>>& args, unique_ptr<Var>& result)
{
    Var *item;
    if (args.length() != 2 || args[0]->getType() != VarType::Array || args[1]->getType() != VarType::Number)
        goto error;
    if (!static_cast<ArrayVar*>(args[0].get())->getArray().get(static_cast<NumberVar*>(args[1].get())->getValue(), &item))
        goto error;
    if (item == nullptr)
        result.reset(new Var(VarType::Nil));
    else
        result.reset(item->copy());
    return true;
error:
    return false;
}

static bool func_aset(void *arg, Evaluator& eval, const vector<unique_ptr<Var>>& args, unique_ptr<Var>& result)
{
    Var *item;
    if (args.length() != 3 || args[0]->getType() != VarType::Array || args[1]->getType() != VarType::Number)
        goto error;
    item = args[2] ? args[2]->copy() : nullptr;
    if (!static_cast<ArrayVar*>(args[0].get())->getArray().set(static_cast<NumberVar*>(args[1].get())->getValue(), item))
        goto error;
    result.reset(new Var(VarType::Nil));
    return true;
error:
    return false;
}

void ArrayVar::registerExternals(Evaluator& eval)
{
    eval.addExternal("Array", func_Array);
    eval.addExternal("aget", func_aget);
    eval.addExternal("aset", func_aset);
}
