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
#include "eval.h"

#include <cstdio.h>
#define DBG(x) fprintf(stderr, x "\n");

Var::Var(VarType type)
{
    this->type = type;
}

Var::~Var()
{
}

Scope::Scope(Scope *parent)
    : breaking(false), returning(false)
{
    this->parent = parent;
}

Scope::~Scope()
{
}

unique_ptr<Var>* Scope::findName(const CString& name)
{
    if (names.has(name))
        return &names[name];
    else 
        return parent == nullptr ? nullptr : parent->findName(name);
}

Evaluator::Evaluator(Node *root_)
    : root(root_)
{
    StringVar::registerOps(*this);
    NumberVar::registerOps(*this);
}

Evaluator::~Evaluator()
{
    Node::deleteTree(root);
}

void Evaluator::addExternal(const char *identifier, External func, void *arg)
{
    externals[identifier] = pair<External, void *>(func, arg);
}

void Evaluator::addOp(const CString& op, VarType a, VarType b, OpFunc func)
{
    _Op _op = { .a = a, .b = b, .fn = func };
    operators[op].push_back(_op);
}

bool Evaluator::run()
{
    Scope scope(nullptr);
    scope.procScope = &scope;
    // root->dump(0);
    return eval_block(scope, root, 0);
}

bool Evaluator::eval_expr(Scope& scope, Node *node, unique_ptr<Var>& outresult)
{
    while (node->getType() == TokenType::Expr)
        node = node->getChild();
    switch (node->getType())
    {
    case TokenType::Operator:
    {
        unique_ptr<Var> rhs;
        CString op;

        op = node->getLiteral();
        if (!eval_expr(scope, node->getNext(), rhs))
            return false;
        if (!eval_op(op, rhs.get(), nullptr, outresult))
            return false;
        break;
    }
    case TokenType::BinOp:
    {
        unique_ptr<Var> lhs, rhs;
        CString op;

        Node *child = node->getChild();
        if (!eval_expr(scope, child, lhs))
            return false;
        child = child->getNext();
        op = child->getLiteral();
        child = child->getNext();
        if (!eval_expr(scope, child, rhs))
            return false;
        if (!eval_op(op, lhs.get(), rhs.get(), outresult))
            return false;
        break;
    }
    case TokenType::Assign:
    {
        Node *child = node->getChild();
        unique_ptr<Var>* var = scope.findName(child->getLiteral());
        if (var == nullptr)
        {
            DBG("undefined identifier");
            return false;
        }
        if (!eval_expr(scope, child->getNext(), *var))
            return false;
        outresult = var->get()->copy();
        break;
    }
    case TokenType::Identifier:
    {
        unique_ptr<Var>* var = scope.findName(node->getLiteral());
        if (var == nullptr)
        {
            DBG("undefined identifier");
            return false;
        }
        outresult = var->get()->copy();
        break;
    }
    case TokenType::Number:
    {
        outresult.reset(new NumberVar(strtoul(node->getLiteral(), 0, 0)));
        break;
    }
    case TokenType::Call:
    {
        Node *child = node->getChild();
        unique_ptr<Var>* var = scope.findName(child->getLiteral());
        if (var != nullptr)
        {
            if (var->get()->getType() != VarType::Proc)
            {
                DBG("Procedure has wrong type.");
                return false;
            }
            child = child->getNext();

            Procedure *proc = static_cast<Procedure *>(var->get());
            Scope calleeScope(&proc->getScope());
            calleeScope.procScope = &calleeScope;
            auto args = proc->getArguments();
            for (unsigned int i = 0; i < args.length(); i++)
            {
                unique_ptr<Var> result;
                if (child == nullptr || !eval_expr(scope, child, result))
                {
                    DBG("Bad expression in call");
                    return false;
                }
                calleeScope.names[args[i]].reset(result.release());
                child = child->getNext();
            }
            if (!eval_block(calleeScope, proc->getBlock(), proc->getIndent()))
                return false;
            if (calleeScope.retval)
                outresult = calleeScope.retval.release();
            else
                outresult.reset(nullptr);
        }
        else if (externals.has(child->getLiteral()))
        {
            auto external = externals[child->getLiteral()];
            child = child->getNext();
            unsigned int nargs = 0;
            for (Node *node = child; node != nullptr; node = node->getNext())
                nargs++;
            vector<unique_ptr<Var>> args;
            args.resize(nargs);
            unsigned int i = 0;
            for (Node *node = child; node != nullptr; node = node->getNext(), i++)
            {
                unique_ptr<Var> result;
                if (!eval_expr(scope, node, result))
                {
                    DBG("Bad expression in extern call");
                    return false;
                }
                args[i].reset(result.release());
            }
            if (!external.left(external.right, *this, args, outresult))
                return false;
        }
        else
        {
            fprintf(stderr, "Undefined procedure: %s\n", child->getLiteral());
            return false;
        }
        break;
    }
    default:
        DBG("Unknown expression.");
        node->dump(0);
        return false;
    }
    return true;
}

bool Evaluator::eval_block(Scope& scope, Node *node, unsigned int indent)
{
    bool retval = true, inIf = false, skipElse = false;

    while (node != nullptr && !scope.procScope->breaking && !scope.procScope->returning)
    {
        Node *child;
        if (node->getType() != TokenType::Stmt)
        {
            DBG("wrong type in eval_block");
            return false;
        }
        child = node->getChild();
        if (child->getType() != TokenType::Indent)
        {
            DBG("wrong indent type in eval_block");
            return false;
        }
        if (child->getLength() != indent)
            break;
        child = child->getNext();

        if (child->getType() != TokenType::Else && child->getType() != TokenType::Elif)
            inIf = false;

        switch (child->getType())
        {
        case TokenType::Declare:
        {
            child = child->getChild();
            if (scope.names.has(child->getLiteral()))
            {
                DBG("Warning: redefining name");
                scope.names.remove(child->getLiteral());
            }
            scope.names[child->getLiteral()] = nullptr;

            node = node->getNext();
            break;
        }
        case TokenType::DeclareAssign:
        {
            child = child->getChild();
            Node *name = child->getChild();
            if (scope.names.has(name->getLiteral()))
            {
                DBG("Warning: redefining name");
                scope.names.remove(name->getLiteral());
            }
            scope.names[name->getLiteral()] = nullptr;

            unique_ptr<Var> result;
            if (!eval_expr(scope, child, result))
                return false;

            node = node->getNext();
            break;
        }
        case TokenType::BinOp:
        case TokenType::Expr:
        {
            unique_ptr<Var> result;

            if (!eval_expr(scope, child, result))
            {
                retval = false;
                goto error;
            }

            node = node->getNext();
            break;
        }
        case TokenType::Return:
        {
            if (!eval_expr(scope, child->getChild(), scope.retval))
            {
                retval = false;
                goto error;
            }
            scope.procScope->returning = true;
            break;
        }
        case TokenType::Break:
        {
            scope.procScope->breaking = true;
            break;
        }
        case TokenType::Else:
        {
            if (!inIf)
                return false;

            Node *block = node->getNext();
            unsigned int blockIndent = block->getChild()->getLength();
            if (blockIndent <= indent)
            {
                DBG("Error: block indent incorrect");
                return false;
            }

            if (!skipElse)
            {
                Scope blockScope(&scope);
                blockScope.procScope = scope.procScope;

                if (!eval_block(blockScope, block, blockIndent))
                    return false;
            }

            inIf = false;

            node = node->getNext(); // skip else
            while (node != nullptr && node->getChild()->getLength() >= blockIndent)
                node = node->getNext();
            break;
        }
        case TokenType::If:
        case TokenType::Elif:
        case TokenType::While:
        {
            unique_ptr<Var> cond;
            Node *condExpr = child->getChild();

            if (child->getType() == TokenType::If)
            {
                inIf = true;
                skipElse = false;
            }
            else if (child->getType() == TokenType::Elif && !inIf)
            {
                return false;
            }

            Node *block = node->getNext();
            unsigned int blockIndent = block->getChild()->getLength();
            if (blockIndent <= indent)
            {
                DBG("Error: block indent incorrect");
                return false;
            }

            if (child->getType() != TokenType::Elif || !skipElse)
            {
                do
                {
                    if (!eval_expr(scope, condExpr, cond))
                        return false;

                    if (cond->getType() != VarType::Number)
                        return false;

                    if (!static_cast<NumberVar*>(cond.get())->getValue())
                        break;

                    Scope blockScope(&scope);
                    blockScope.procScope = scope.procScope;

                    skipElse = true;

                    if (!eval_block(blockScope, block, blockIndent))
                        return false;

                    if (scope.procScope->breaking || scope.procScope->returning)
                        break;
                } while (child->getType() == TokenType::While);
            }

            if (child->getType() == TokenType::While)
                scope.procScope->breaking = false;

            node = node->getNext(); // skip if/elif/while
            while (node != nullptr && node->getChild()->getLength() >= blockIndent)
                node = node->getNext();
            break;
        }
        case TokenType::Proc:
        {
            child = child->getChild();
            if (scope.names.has(child->getLiteral()))
            {
                DBG("Warning: redefining name");
                scope.names.remove(child->getLiteral());
            }
            node = node->getNext();
            unsigned int procIndent = node->getChild()->getLength();
            if (procIndent <= indent)
            {
                DBG("Error: procedure indent incorrect");
                retval = false;
                goto error;
            }
            Var *var = new Procedure(scope, child->getNext(), node, procIndent);
            scope.names[CString(child->getLiteral()).ensure()] = var;
            while (node != nullptr && node->getChild()->getLength() >= procIndent)
                node = node->getNext();
            break;
        }
        default:
            DBG("Unknown statement type.");
            node->dump(0);
            retval = false;
            goto error;
        }
    }

error:
    return retval;
}

bool Evaluator::eval_op(const CString& op, Var* a, Var* b, unique_ptr<Var>& outresult)
{
    if (!operators.has(op))
    {
        DBG("missing operator");
        return false;
    }
    auto ops = operators[op];
    for (unsigned int i = 0; i < ops.length(); i++)
    {
        auto _op = ops[i];
        if (b == nullptr)
        {
            if (_op.a == a->getType() && _op.b == VarType::Nil)
                return _op.fn(op, a, b, outresult);
        }
        else
        {
            if (_op.a == a->getType() && _op.b == b->getType())
                return _op.fn(op, a, b, outresult);
        }
    }

    DBG("missing compatible operator");
    return false;
}

Procedure::Procedure(Scope &scope_, Node *arglist, Node *block, unsigned int indent)
    : Var(VarType::Proc), scope(scope_)
{
    for (Node *node = arglist; node != nullptr; node = node->getNext())
        args.push_back(node->getLiteral());

    this->block = block;
    this->indent = indent;
}

Procedure::~Procedure()
{
}

Var* Procedure::copy()
{
    return new Procedure(*this);
}

NumberVar::NumberVar(unsigned int val)
    : Var(VarType::Number), value(val)
{
}

NumberVar::~NumberVar()
{
}

Var* NumberVar::copy()
{
    return new NumberVar(*this);
}

StringVar::StringVar()
    : Var(VarType::String)
{
}

StringVar::~StringVar()
{
}

Var* StringVar::copy()
{
    return new StringVar(*this);
}

#define OP(name, t1, t2) \
    eval.addOp(name, VarType::t1, VarType::t2, \
        [] (const CString& op, Var *a, Var *b, unique_ptr<Var>& result) -> bool {
#define OP_END });
void NumberVar::registerOps(Evaluator &eval)
{
#define NUMOP(_op) \
    eval.addOp(#_op, VarType::Number, VarType::Number, \
        [] (const CString& op, Var *a, Var *b, unique_ptr<Var>& result) -> bool { \
            const NumberVar *na = static_cast<NumberVar*>(a); \
            const NumberVar *nb = static_cast<NumberVar*>(b); \
            result.reset(new NumberVar(na->value _op nb->value)); \
            return true; \
    });
    NUMOP(>>)
    NUMOP(<<)
    NUMOP(*)
    NUMOP(/)
    NUMOP(+)
    NUMOP(-)
    NUMOP(|)
    NUMOP(&)
    NUMOP(<)
    NUMOP(>)
    NUMOP(<=)
    NUMOP(>=)
    NUMOP(!=)
    NUMOP(==)
    NUMOP(||) // "or" is currently broken
    NUMOP(&&) // "and" is currently broken
#undef NUMOP
#define NUMOP(_op) \
    eval.addOp(#_op, VarType::Number, VarType::Nil, \
        [] (const CString& op, Var *a, Var *b, unique_ptr<Var>& result) -> bool { \
            const NumberVar *na = static_cast<NumberVar*>(a); \
            result.reset(new NumberVar(_op na->value)); \
            return true; \
    });
    NUMOP(-)
    NUMOP(~)
#undef NUMOP
}

void StringVar::registerOps(Evaluator &eval)
{
    OP("+", String, String)
        const StringVar *sa = static_cast<StringVar*>(a);
        const StringVar *sb = static_cast<StringVar*>(b);

        StringVar *out = new StringVar();
        out->resize(sa->data.length() + sb->data.length());

        unsigned int i, j;
        for (i = 0; i < sa->data.length(); i++)
            out->data[i] = sa->data[i];
        for (j = 0; j < sb->data.length(); j++)
            out->data[i + j] = sb->data[j];
        result.reset(out);

        return true;
    OP_END
}
