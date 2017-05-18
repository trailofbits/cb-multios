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

#include "cgc_stdio.h"
#include "cgc_string.h"

#include "cgc_tokenizer.h"
#include "cgc_parser.h"

#include "cgc_prettyprinter.h"

void
cgc_pretty_print_tokens(struct token *tokens, cgc_size_t n)
{
    cgc_size_t i;
    char name[5] = {};

    for (i = 0; i < n; i++) {
        switch (tokens[i].type) {
        case TOK_CONSTANT:
            cgc_printf("%d", tokens[i].val.i);
            break;
        case TOK_VARIABLE:
            cgc_memset(name, '\0', sizeof(name));
            cgc_strncpy(name, tokens[i].val.s, 4);
            cgc_printf("%s", name);
            break;
        case TOK_ASSIGNMENT:
            cgc_printf("=");
            break;
        case TOK_ADD:
            cgc_printf("+");
            break;
        case TOK_SUBTRACT:
            cgc_printf("-");
            break;
        case TOK_MULTIPLY:
            cgc_printf("*");
            break;
        case TOK_DIVIDE:
            cgc_printf("/");
            break;
        case TOK_NEGATE:
            cgc_printf("~");
            break;
        case TOK_ADDRESS_OF:
            cgc_printf("&");
            break;
        case TOK_DEREFERENCE:
            cgc_printf("$");
            break;
        case TOK_LEFT_PARENTHESIS:
            cgc_printf("(");
            break;
        case TOK_RIGHT_PARENTHESIS:
            cgc_printf(")");
            break;
        }
    }

    cgc_printf("\n");
}

static void
cgc_pretty_print_ast_node(struct ast_node *node)
{
    char name[5] = {};
    static const char unary_operators[] = { '~', '&', '$' };
    static const char binary_operators[] = { '=', '+', '-', '*', '/' };

    switch (node->type) {
    case AST_CONSTANT:
        cgc_printf("%d", node->expr.constant);
        break;
    case AST_VARIABLE:
        cgc_memset(name, '\0', sizeof(name));
        cgc_strncpy(name, node->expr.variable, 4);
        cgc_printf("%s", name);
        break;
    case AST_UNARY_OPERATOR:
        cgc_printf("%c", unary_operators[node->expr.un_op.type]);
        cgc_pretty_print_ast_node(node->expr.un_op.n);
        break;
    case AST_BINARY_OPERATOR:
        cgc_printf("(");
        cgc_pretty_print_ast_node(node->expr.bin_op.lhs);
        cgc_printf("%c", binary_operators[node->expr.bin_op.type]);
        cgc_pretty_print_ast_node(node->expr.bin_op.rhs);
        cgc_printf(")");
        break;
    default:
        return;
    }
}

void
cgc_pretty_print_ast(struct ast *ast)
{
    cgc_pretty_print_ast_node(ast->expr);
    cgc_printf("\n");
}


