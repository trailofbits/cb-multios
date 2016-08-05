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

#include "namespace.h"
#include "parser.h"

#include "interpreter.h"

static int
eval_ast_node(struct ast_node *node, struct namespace *ns, struct variable *result)
{
    const char *name;
    struct variable *var;
    struct variable n = { .type = VAR_INTEGER };
    struct variable lhs = { .type = VAR_INTEGER };
    struct variable rhs = { .type = VAR_INTEGER };

    switch (node->type) {
    case AST_CONSTANT:
        result->type = VAR_INTEGER;
        result->val.i = node->expr.constant;
        return EXIT_SUCCESS;
    case AST_VARIABLE:
        if ((var = lookup_variable(ns, node->expr.variable)) == NULL)
            return EXIT_FAILURE;

        *result = *var;
        return EXIT_SUCCESS;
    case AST_UNARY_OPERATOR:
        switch (node->expr.un_op.type) {
        case UN_NEGATE:
            if (eval_ast_node(node->expr.un_op.n, ns, &n) < 0)
                return EXIT_FAILURE;

            if (n.type != VAR_INTEGER)
                return EXIT_FAILURE;

#ifdef PATCHED_2
            result->type = VAR_INTEGER;
#endif
            result->val.i = -n.val.i;
            return EXIT_SUCCESS;
        case UN_ADDRESS_OF:
            // Our parser ensures that the subexpr is a variable
            if ((var = lookup_variable(ns, node->expr.un_op.n->expr.variable)) == NULL)
                return EXIT_FAILURE;

            result->type = VAR_POINTER;
            result->val.p = var;
            return EXIT_SUCCESS;
        case UN_DEREFERENCE:
            if (eval_ast_node(node->expr.un_op.n, ns, &n) < 0)
                return EXIT_FAILURE;

            if (n.type != VAR_POINTER)
                return EXIT_FAILURE;

            *result = *(struct variable *)n.val.p;
            return EXIT_SUCCESS;
        }
    case AST_BINARY_OPERATOR:
        if (node->expr.bin_op.type != BIN_ASSIGNMENT &&
                eval_ast_node(node->expr.bin_op.lhs, ns, &lhs) < 0)
            return EXIT_FAILURE;

        if (eval_ast_node(node->expr.bin_op.rhs, ns, &rhs) < 0)
            return EXIT_FAILURE;

        if (node->expr.bin_op.type != BIN_ASSIGNMENT &&
                (lhs.type != VAR_INTEGER || rhs.type != VAR_INTEGER))
            return EXIT_FAILURE;

        switch (node->expr.bin_op.type) {
        case BIN_ASSIGNMENT:
            // Our parser ensures that the subexpr is a variable or deref
            if (node->expr.bin_op.lhs->type == AST_VARIABLE) {
                name = node->expr.bin_op.lhs->expr.variable;
            } else {
                if (eval_ast_node(node->expr.bin_op.lhs, ns, &lhs) < 0)
                    return EXIT_FAILURE;
                name = lhs.name;
            }

            var = insert_variable(ns, name, rhs.type);
            var->val = rhs.val;

            if ((var = lookup_variable(ns, name)) != NULL)
                var->type = rhs.type;

            *result = rhs;
            return EXIT_SUCCESS;
        case BIN_ADD:
            result->type = VAR_INTEGER;
            result->val.i = lhs.val.i + rhs.val.i;
            return EXIT_SUCCESS;
        case BIN_SUBTRACT:
            result->type = VAR_INTEGER;
            result->val.i = lhs.val.i - rhs.val.i;
            return EXIT_SUCCESS;
        case BIN_MULTIPLY:
            result->type = VAR_INTEGER;
            result->val.i = lhs.val.i * rhs.val.i;
            return EXIT_SUCCESS;
        case BIN_DIVIDE:
            if (rhs.val.i == 0)
                return EXIT_FAILURE;

            result->type = VAR_INTEGER;
            result->val.i = lhs.val.i / rhs.val.i;
            return EXIT_SUCCESS;
        }
    default:
        return EXIT_FAILURE;
    }
}

int
eval(struct ast *ast, struct namespace *ns, struct variable *result)
{
    return eval_ast_node(ast->expr, ns, result);
}


