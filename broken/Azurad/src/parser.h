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

#include <cstdio.h>
#include "vector.h"

namespace std
{
    typedef unsigned int size_t;
};

class Node;

enum class TokenType
{
    Ignore,
    Optional,
    Repeat,
    Or,
    And,

    Indent,
    Identifier,
    Number,
    String,
    Discard,
    Var,
    Assign,
    Operator,
    Declare,
    DeclareAssign,
    Call,
    Stmt,
    Expr,
    Block,
    While,
    If,
    Elif,
    Else,
    BinOp,
    Proc,
    Break,
    Return
};

class Token
{
public:
    Token();
    Token(TokenType type);
    Token(const char *str);
    Token(const char *str, TokenType type);
    Token(const char *str, size_t len, TokenType type);
    Token(const Token &child, TokenType type);

    bool parse(const char *input, size_t length, Node **pNode, size_t *pLength) const;
    void set(const Token &child);
    void setAfter(Token &after);

    Token operator++(int ignored);
    Token operator+(Token rhs);
    Token operator|(Token rhs);
    Token operator&();
protected:
    bool parse_(const char *input, size_t length, Node **pNode, size_t *pLength) const;
    void after_(const char *input, size_t length, Node **pNode, size_t *pLength) const;
protected:
    TokenType type;

    vector<Token> children;
    Token *indirect, *after;
    const char *literal;
    size_t length;
};

class Node
{
    friend class Token;
public:
    Node(TokenType type);
    ~Node();

    static void deleteTree(Node *root);
    void dump(unsigned int level);
    void setLiteral(const char *start, size_t length);

    TokenType getType() { return type; }
    Node *getChild() { return child; }
    Node *getNext() { return next; }
    unsigned int getLength() { return length; }
    const char *getLiteral() { return literal; }
protected:
    char *literal;
    unsigned int length;
    TokenType type;
    Node *child;

    Node *next;
};

class Parser
{
public:
    Parser(const char *input);
    ~Parser();

    bool parse();
    Node *releaseRoot()
    {
        Node *result = root;
        root = nullptr;
        return result;
    }
private:
    const char *input;
    size_t length;
    size_t parsedLength;

    Node *root;
};

Token operator "" _T(const char *, std::size_t);
