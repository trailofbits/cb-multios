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

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <libcgc.h>

enum token_type {
    TOK_CONSTANT,
    TOK_VARIABLE,
    TOK_ASSIGNMENT,
    TOK_ADD,
    TOK_SUBTRACT,
    TOK_MULTIPLY,
    TOK_DIVIDE,
    TOK_NEGATE,
    TOK_ADDRESS_OF,
    TOK_DEREFERENCE,
    TOK_LEFT_PARENTHESIS,
    TOK_RIGHT_PARENTHESIS
};

struct token {
    enum token_type type;
    union {
        char s[4];
        int i;
    } val;
};

/**
 * Split a string into a buffer of tokens.
 *
 * @param str The string to tokenize
 * @param token The buffer to place the tokens, ensure it has enough room to
 *      receive up to strlen(str) tokens
 * @return The number of tokens in the stream on success, or EXIT_FAILURE on
 *      failure
 */
ssize_t tokenize(char *str, struct token *token);

#endif /* TOKENIZER_H_ */

