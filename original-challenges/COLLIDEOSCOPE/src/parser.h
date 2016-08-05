/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "pool.h"

struct ast_node;
struct token;

enum ast_node_type {
    AST_CONSTANT,
    AST_VARIABLE,
    AST_BINARY_OPERATOR,
    AST_UNARY_OPERATOR,
    AST_PARENTHESIS
};

enum binary_op_type {
    BIN_ASSIGNMENT,
    BIN_ADD,
    BIN_SUBTRACT,
    BIN_MULTIPLY,
    BIN_DIVIDE
};

struct binary_op {
    enum binary_op_type type;
    struct ast_node *lhs, *rhs;
};

enum unary_op_type {
    UN_NEGATE,
    UN_ADDRESS_OF,
    UN_DEREFERENCE
};

struct unary_op {
    enum unary_op_type type;
    struct ast_node *n;
};

struct ast_node {
    struct ast_node *next;
    enum ast_node_type type;
    union {
        struct token *token;
        char variable[4];
        int constant;
        struct binary_op bin_op;
        struct unary_op un_op;
    } expr;
};

struct ast {
    struct pool pool;
    struct ast_node *expr;
};

/**
 * Parse a buffer of tokens into an AST.
 *
 * @param tokens The tokens to parse
 * @param n The number of tokens in the buffer 
 * @param out Pointer to the AST to parse into
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int parse(struct token *tokens, size_t n, struct ast *out);

/**
 * Destroy an AST and all nodes.
 *
 * @param ast The AST to destroy
 */
void ast_destroy(struct ast *ast);

#endif /* PARSER_H_ */

