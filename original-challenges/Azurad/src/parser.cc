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
#include <cstdlib.h>
#include <cstring.h>

#define DBG(x) fprintf(stderr, x "\n")

#include "parser.h"

static Node emptyNode(TokenType::Ignore);

static const char *typeToString(TokenType type)
{
#define T(t) case TokenType::t: return #t ; 
    switch (type)
    {
    T(Ignore)
    T(Optional)
    T(Repeat)
    T(Or)
    T(And)
    T(Indent)
    T(Identifier)
    T(Number)
    T(String)
    T(Discard)
    T(Var)
    T(Assign)
    T(Operator)
    T(Declare)
    T(DeclareAssign)
    T(Call)
    T(Stmt)
    T(Expr)
    T(Block)
    T(While)
    T(BinOp)
    T(Proc)
    T(Break)
    T(Return)
    T(If)
    T(Elif)
    T(Else)
    default:
        return "UNKNOWN";
    }
#undef T
}

Parser::Parser(const char *input_)
    : input(input_), root(nullptr)
{
    length = strlen(input);
}

Parser::~Parser()
{
    if (root)
        Node::deleteTree(root);
}

bool Parser::parse()
{
    auto indent = Token(Token(" "_T ++, TokenType::Optional), TokenType::Indent);

    auto ws = Token((" "_T | "\t"_T) ++);
    auto optws = Token(ws, TokenType::Optional);

    auto op = Token(("+"_T | "-"_T | "*"_T | "/"_T | "<"_T | ">"_T | "="_T | "@"_T | "$"_T | "~"_T | "&"_T | "%"_T | "!"_T | "^"_T | "|"_T) ++, TokenType::Operator);

    auto digit = "0"_T | "1"_T | "2"_T | "3"_T | "4"_T | "5"_T | "6"_T | "7"_T | "8"_T | "9"_T;
    auto hexdigit = (digit | "a"_T | "b"_T | "c"_T | "d"_T | "e"_T | "f"_T | "A"_T | "B"_T | "C"_T | "D"_T | "E"_T | "F"_T);
    auto number = Token(
            ("0x"_T + (hexdigit++)) |
            (digit++),
        TokenType::Number);

    auto lowercase = "a"_T | "b"_T | "c"_T | "d"_T | "e"_T | "f"_T | "g"_T | "h"_T | "i"_T | "j"_T | "k"_T | "l"_T | "m"_T | "n"_T | "o"_T | "p"_T | "q"_T | "r"_T | "s"_T | "t"_T | "u"_T | "v"_T | "w"_T | "x"_T | "y"_T | "z"_T;
    auto uppercase = "A"_T | "B"_T | "C"_T | "D"_T | "E"_T | "F"_T | "G"_T | "H"_T | "I"_T | "J"_T | "K"_T | "L"_T | "M"_T | "N"_T | "O"_T | "P"_T | "Q"_T | "R"_T | "S"_T | "T"_T | "U"_T | "V"_T | "W"_T | "X"_T | "Y"_T | "Z"_T;
    auto identifier = Token(
            (lowercase | uppercase) +
            Token((lowercase | uppercase | digit | "_") ++, TokenType::Optional),
        TokenType::Identifier);

    auto string = Token("\""_T + Token((lowercase | uppercase | "_"_T | ","_T | "."_T | ws), TokenType::Optional) + "\""_T, TokenType::String);

    auto assignment = Token(TokenType::Assign);
    auto call = Token(TokenType::Call);
    auto expression = Token(TokenType::Expr);
    expression.set(
        ("("_T + optws + &expression + optws + ")"_T) |
        (&assignment) |
        (op + optws + &expression) |
        (&call) |
        (number) |
        (string) |
        (identifier)
    );
    auto after_expression = Token(
        (optws + op + optws + &expression) |
        (ws + "or"_T + ws + &expression) |
        (ws + "and"_T + ws + &expression), TokenType::BinOp);
    expression.setAfter(after_expression);

    assignment.set(identifier + ws + "="_T + ws + &expression);

    auto callarguments_ = Token((optws + "," + optws + &expression)++, TokenType::Optional);
    auto callarguments = Token(&expression + callarguments_, TokenType::Optional);
    call.set(
        identifier + optws + "(" + optws + callarguments + optws + ")"
    );

    auto procarguments_ = Token((optws + "," + optws + identifier)++, TokenType::Optional);
    auto procarguments = Token(identifier + procarguments_, TokenType::Optional);
    auto proc =
        identifier + optws + "(" + optws + procarguments + optws + ")";

    auto block = Token(TokenType::Repeat);
    auto statement = Token(
        //Token("discard"_T + ws + &expression, TokenType::Discard) |
        Token("var"_T + ws + &assignment, TokenType::DeclareAssign) |
        Token("var"_T + ws + identifier, TokenType::Declare) |
        Token("block:"_T, TokenType::Block) |
        Token("while"_T + ws + &expression + optws + ":", TokenType::While) |
        Token("if"_T + ws + &expression + optws + ":", TokenType::If) |
        Token("elif"_T + ws + &expression + optws + ":", TokenType::Elif) |
        Token("else:"_T, TokenType::Else) |
        Token("proc"_T + ws + proc + optws + ":", TokenType::Proc) |
        Token("break", TokenType::Break) |
        Token("return"_T + optws + Token(&expression, TokenType::Optional), TokenType::Return) |
        &expression);

    auto line = Token(
        (Token(indent + statement, TokenType::Stmt) + optws + "\n"_T) |
        (optws + "\n"_T));

    block.set(line);

    parsedLength = 0;
    root = nullptr;
    bool result = block.parse(input, length, &root, &parsedLength);
    if (result)
    {
        if (parsedLength != length)
        {
            DBG("unable to parse entire file");
            result = false;
        }
    }
    else
    {
        DBG("unable to parse file");
    }
    return result;
}

Token::Token()
    : type(TokenType::Ignore), indirect(nullptr), after(nullptr), literal(nullptr), length(0)
{
}

Token::Token(TokenType type_)
    : Token()
{
    type = type_;
}

Token::Token(const char *str)
    : Token()
{
    literal = str;
    length = strlen(str);
}

Token::Token(const char *str, TokenType type_)
    : Token(type_)
{
    literal = str;
    length = strlen(str);
}

Token::Token(const char *str, size_t len, TokenType type_)
    : Token(type_)
{
    literal = str;
    length = len;
}

Token::Token(const Token &child_, TokenType type_)
    : Token(type_)
{
    children.resize(1);
    children[0] = child_;
}

Token Token::operator++(int ignored)
{
    return Token(*this, TokenType::Repeat);
}

Token Token::operator+(Token rhs)
{
    Token t(TokenType::And);
    t.children.resize(2);
    t.children[0] = *this;
    t.children[1] = rhs;
    return t;
}

Token Token::operator|(Token rhs)
{
    Token t(TokenType::Or);
    if (this->type == TokenType::Or)
    {
        t.children.resize(this->children.length() + 1);
        for (unsigned int i = 0; i < this->children.length(); i++)
            t.children[i] = this->children[i];
        t.children[this->children.length()] = rhs;
    }
    else
    {
        t.children.resize(2);
        t.children[0] = *this;
        t.children[1] = rhs;
    }
    return t;
}

Token Token::operator&()
{
    Token t;
    t.indirect = this;
    return t;
}

Token operator "" _T(const char *str, std::size_t len)
{
    return Token(str, len, TokenType::Ignore);
}

void Token::after_(const char *input, size_t length, Node **pNode, size_t *pLength) const
{
    Node *node;

    if (after == nullptr)
        return;

    size_t actual = 0;
    if (after->parse(input, length, &node, &actual))
    {
        if ((*pNode)->next != nullptr)
        {
            DBG("in after_, pNode already has next");
        }
        (*pNode)->next = node->child;
        node->child = *pNode;
        *pLength += actual;
        *pNode = node;
        node->setLiteral(input - node->child->length, node->child->length + actual);
    }
}

bool Token::parse_(const char *input, size_t length, Node **pNode, size_t *pLength) const
{
    if (indirect != nullptr)
    {
        return indirect->parse(input, length, pNode, pLength);
    }
    else if (literal != nullptr)
    {
        if (length < this->length)
            return false;
        if (memcmp(input, literal, this->length) != 0)
            return false;
        if (type != TokenType::Ignore && type != TokenType::Optional && type != TokenType::Repeat)
        {
            *pNode = new Node(type);
            (*pNode)->setLiteral(input, this->length);
        }
        else
        {
            *pNode = nullptr;
        }
        *pLength += this->length;
        return true;
    }
    else if (children.length())
    {
        if (type == TokenType::Or)
        {
            for (unsigned int i = 0; i < children.length(); i++)
            {
                if (children[i].parse(input, length, pNode, pLength))
                    return true;
            }
            return false;
        }
        else if (type == TokenType::And)
        {
            size_t old = *pLength;
            if (!children[0].parse(input, length, pNode, pLength))
                return false;
            if (*pNode)
            {
                Node *node = *pNode;
                while (node->next != nullptr) node = node->next;
                return children[1].parse(input + *pLength - old, length - (*pLength - old), &node->next, pLength);
            }
            else
                return children[1].parse(input + *pLength - old, length - (*pLength - old), pNode, pLength);
        }

        if (type == TokenType::Ignore || type == TokenType::Optional || type == TokenType::Repeat)
            return children[0].parse(input, length, pNode, pLength);

        Node *node;
        size_t actual = 0;
        if (!children[0].parse(input, length, &node, &actual))
            return false;

        *pNode = new Node(type);
        (*pNode)->child = node;
        (*pNode)->setLiteral(input, actual);
        *pLength += actual;
        return true;
    }
    else
    {
        DBG("missing child or literal");
        return false;
    }
}

bool Token::parse(const char *input, size_t length, Node **pNode, size_t *pLength) const
{
    bool result;
    size_t actual, old = *pLength;
    Node *node;

    if (type == TokenType::Optional)
    {
        actual = 0;
        result = parse_(input, length, &node, &actual);
        if (result)
        {
            *pNode = node;
            *pLength += actual;
            input += actual;
            length -= actual;
        }
        else
        {
            *pNode = nullptr;
        }
        after_(input, length, pNode, pLength);
        return true;
    }
    else if (type == TokenType::Repeat)
    {
        bool success = false;
        Node *head = nullptr, *tail = nullptr;
        do {
            actual = 0;
            result = parse_(input, length, &node, &actual);
            if (result)
            {
                if (node != nullptr)
                {
                    if (head == nullptr)
                        head = tail = node;
                    else
                        tail = tail->next = node;
                }
                input += actual;
                length -= actual;
                *pLength += actual;
                success = true;
            }
        } while (result);

        *pNode = head;
        if (success)
            after_(input, length, pNode, pLength);
        return success;
    }
    else
    {
        if (parse_(input, length, pNode, pLength))
        {
            after_(input + *pLength - old, length - (*pLength - old), pNode, pLength);
            return true;
        }
        else
            return false;
    }
}

void Token::set(const Token &child)
{
    children.resize(1);
    children[0] = child;
}

void Token::setAfter(Token &after)
{
    this->after = reinterpret_cast<Token *>(&reinterpret_cast<char&>(after));
}

Node::Node(TokenType type_)
    : literal(nullptr), type(type_), child(nullptr), next(nullptr)
{
}

Node::~Node()
{
    if (literal)
        delete[] literal;
}

void Node::deleteTree(Node *root)
{
    if (root->child)
        deleteTree(root->child);

    Node *next = root->next;
    delete root;
    if (next)
        deleteTree(next);
}

void Node::dump(unsigned int level)
{
    for (unsigned int i = 0; i < level * 2; i++)
        fprintf(stderr, " ");
    fprintf(stderr, "%s - (%d) %s\n", typeToString(type), length, literal);
    if (child != nullptr)
        child->dump(level + 1);
    if (next != nullptr)
        next->dump(level);
}

void Node::setLiteral(const char *start, size_t length)
{
    if (literal)
        delete[] literal;
    literal = new char [length + 1];
    memcpy(literal, start, length);
    literal[length] = 0;
    this->length = length;
}
