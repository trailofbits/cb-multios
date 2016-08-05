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

#include "stdio.h"
#include "string.h"

#include "tokenizer.h"
#include "parser.h"

#include "prettyprinter.h"

void
pretty_print_tokens(struct token *tokens, size_t n)
{
    size_t i;
    char name[5] = {};

    for (i = 0; i < n; i++) {
        switch (tokens[i].type) {
        case TOK_CONSTANT:
            printf("%d", tokens[i].val.i);
            break;
        case TOK_VARIABLE:
            memset(name, '\0', sizeof(name));
            strncpy(name, tokens[i].val.s, 4);
            printf("%s", name);
            break;
        case TOK_ASSIGNMENT:
            printf("=");
            break;
        case TOK_ADD:
            printf("+");
            break;
        case TOK_SUBTRACT:
            printf("-");
            break;
        case TOK_MULTIPLY:
            printf("*");
            break;
        case TOK_DIVIDE:
            printf("/");
            break;
        case TOK_NEGATE:
            printf("~");
            break;
        case TOK_ADDRESS_OF:
            printf("&");
            break;
        case TOK_DEREFERENCE:
            printf("$");
            break;
        case TOK_LEFT_PARENTHESIS:
            printf("(");
            break;
        case TOK_RIGHT_PARENTHESIS:
            printf(")");
            break;
        }
    }

    printf("\n");
}

static void
pretty_print_ast_node(struct ast_node *node)
{
    char name[5] = {};
    static const char unary_operators[] = { '~', '&', '$' };
    static const char binary_operators[] = { '=', '+', '-', '*', '/' };

    switch (node->type) {
    case AST_CONSTANT:
        printf("%d", node->expr.constant);
        break;
    case AST_VARIABLE:
        memset(name, '\0', sizeof(name));
        strncpy(name, node->expr.variable, 4);
        printf("%s", name);
        break;
    case AST_UNARY_OPERATOR:
        printf("%c", unary_operators[node->expr.un_op.type]);
        pretty_print_ast_node(node->expr.un_op.n);
        break;
    case AST_BINARY_OPERATOR:
        printf("(");
        pretty_print_ast_node(node->expr.bin_op.lhs);
        printf("%c", binary_operators[node->expr.bin_op.type]);
        pretty_print_ast_node(node->expr.bin_op.rhs);
        printf(")");
        break;
    default:
        return;
    }
}

void
pretty_print_ast(struct ast *ast)
{
    pretty_print_ast_node(ast->expr);
    printf("\n");
}


