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

#include "conv.h"
#include "stdlib.h"
#include "string.h"

#include "tokenizer.h"

static int
parse_variable(char *str, struct token *token)
{
    char *start = str, *end = str;

    if (*end == '_')
        end++;
    else
        while (islower(*end))
            end++;

    if (end == NULL || end - start > 4)
        return EXIT_FAILURE;

    token->type = TOK_VARIABLE;

    memset(token->val.s, '\0', 4);
    strncpy(token->val.s, start, end - start);

    return end - start;
}

static int
parse_constant(char *str, struct token *token)
{
    int ret, result;

    if ((ret = strtoi(str, 10, &result)) < 0)
        return ret;

    token->type = TOK_CONSTANT;
    token->val.i = result;
    return ret;
}

ssize_t
tokenize(char *str, struct token *tokens)
{
    int ret;
    char c;
    struct token *token = tokens;

    while ((c = *str++)) {
        if (c == '_' || islower(c)) {
            if ((ret = parse_variable(str - 1, token)) < 0)
                return ret;

            str += ret - 1;
            token++;
            continue;
        }

        if (isdigit(c)) {
            if ((ret = parse_constant(str - 1, token)) < 0)
                return ret;

            str += ret - 1;
            token++;
            continue;
        }

        switch (c) {
        case '=':
            token->type = TOK_ASSIGNMENT;
            break;
        case '+':
            token->type = TOK_ADD;
            break;
        case '-':
            token->type = TOK_SUBTRACT;
            break;
        case '*':
            token->type = TOK_MULTIPLY;
            break;
        case '/':
            token->type = TOK_DIVIDE;
            break;
        case '~':
            token->type = TOK_NEGATE;
            break;
        case '&':
            token->type = TOK_ADDRESS_OF;
            break;
        case '$':
            token->type = TOK_DEREFERENCE;
            break;
        case '(':
            token->type = TOK_LEFT_PARENTHESIS;
            break;
        case ')':
            token->type = TOK_RIGHT_PARENTHESIS;
            break;
        case ' ':
            continue;
        default:
            return EXIT_FAILURE;
        }

        token++;
    }

    return token - tokens;
}

