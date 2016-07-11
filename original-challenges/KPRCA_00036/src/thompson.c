/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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

#include <libcgc.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "thompson.h"
#include "constants.h"

#define OPERATOR "|*+?()"
#define TOKEN "|*+?()[]\\"

static int normalize_infix(unsigned char **pinfix, size_t size)
{
    unsigned char *new_str = *pinfix;
    unsigned char unions[200], i = 0;
    unsigned char *infix = *pinfix, *s, *e, *t = *pinfix;
    int error;
    for (; *infix ; infix++ ) {
        if ( !isprint(*infix) ) {
            error = BAD_CHARACTER;
            goto failed;
        }

        if (strchr(OPERATOR, *infix) != NULL) {
            *infix += CHAR_OFFSET;
        } else if (*infix == '\\') {
            if (infix[1] != '\0' && strchr(TOKEN, infix[1]) != NULL) {
                *infix++ = SKIP;
            } else {
                error = BAD_RE;
                goto failed;
            }
        } else if (*infix == '[') {
            int found = FALSE;
            i = 0;
            s = infix;
            unions[i++] = LPAREN;
            while (!found && *++infix) {
                if (*infix != ']') {
                    if (i > 196 ) {
                        error = BAD_RE;
                        goto failed;
                    }
                    unions[i++] = *infix;
                    unions[i++] = UNION;
                } else {
                    if (i <= 1 ) {
                        error = BAD_RE;
                        goto failed;
                    }
                    e = ++infix;
                    found = TRUE;
                }
            }
            if (!found) {
                error = BAD_RE;
                goto failed;
            }

            unions[i] = '\0';
            unions[--i] = RPAREN;
            new_str = malloc(strlen(t) + strlen(unions) + 1);
            memcpy(new_str, t, s - t);
            memcpy(new_str + (s - t), unions, strlen(unions));
            memcpy(new_str + ((s - t) + strlen(unions)), e, strlen(e) + 1);
            infix = new_str + ((s - t) + strlen(unions)) - 1;
            free(t);
            t = new_str;
        }
    }

    *pinfix = new_str;
    return 0;

failed:
    return BAD_RE;
}

static unsigned char peek(unsigned char *list) {
    return *--list;
}

static int is_nonconcat_char(unsigned char c)
{
    return (c == UNION || c == STAR || c == PLUS || c == QMARK || c == RPAREN || c == SKIP);
}

void debug_print_re(unsigned char* re)
{
    unsigned char *temp = malloc(strlen(re) + 1);
    unsigned char *ptemp = temp, *pre = re;
    for( ; *re; re++)
        *temp++ = *re > CHAR_OFFSET ? *re - CHAR_OFFSET : *re;
    temp = '\0';

    printf("Normalized re = %s\n", ptemp);
    printf("Original re = %s\n", pre);
    free(temp);
}

int retorpn(unsigned char *infix, size_t size, unsigned char **rpn)
{
    *rpn = NULL;
    if(strlen(infix) == 0)
        return BAD_RE;
    else if(strlen(infix) > MAX_RE_SIZE)
        return RE_TOO_LONG;
    else if(strlen(infix) > size)
        return BUF_OVERFLOW;

    unsigned char *output = calloc(1, (strlen(infix) * 2) + 1); // Factor in all the concats
    unsigned char *operators = calloc(1, strlen(infix) + 1);
    unsigned char *out_iter = output;
    unsigned char *op_iter = operators;
    unsigned char *ninfix = malloc(size);

    int error = 0;
    int bad_paren = 0;
    unsigned char c;

    strcpy(ninfix, infix);
    infix = ninfix;
    error = normalize_infix(&infix, size);
    if (error != 0)
        goto failed;

    for (; *infix ; infix++ ) {
        switch(*infix) {
        case SKIP:
            break;
        case LPAREN:
            if (infix[1] == '\0' || is_nonconcat_char(infix[1])) {
                error = BAD_RE;
                goto failed;
            }

            PUSH(op_iter, *infix);
            continue;
        case RPAREN:
            bad_paren = 1;
            while(op_iter != operators) {
                if(peek(op_iter) != LPAREN) {
                    POP(op_iter, c);
                    PUSH(out_iter, c);
                } else {
                    POP(op_iter, c);
                    bad_paren = 0;
                    break;
                }
            }
            break;
        case UNION:
            if (out_iter == output || infix[1] == '\0' || is_nonconcat_char(infix[1])) {
                error = BAD_RE;
                goto failed;
            }

            while(op_iter != operators) {
                if(peek(op_iter) != LPAREN && peek(op_iter) != UNION) {
                    POP(op_iter, c);
                    PUSH(out_iter, c);
                } else {
                    break;
                }
            }
            PUSH(op_iter, *infix);
            break;
        case STAR:
        case PLUS:
        case QMARK:
            if (out_iter == output) {
                error = BAD_RE;
                goto failed;
            }
            while(op_iter != operators) {
                c = peek(op_iter);
                if(c == STAR || c == PLUS || c == QMARK) {
                    POP(op_iter, c);
                    PUSH(out_iter, c);
                } else {
                    break;
                }
            }
            PUSH(op_iter, *infix);
            break;
        default:
            PUSH(out_iter, *infix);
            break;
        }

        if (*infix != UNION && infix[1] != '\0' && !is_nonconcat_char(infix[1])) {
            while(op_iter != operators) {
                c = peek(op_iter);
                if(c == STAR || c == PLUS || c == QMARK || c == CONCAT) {
                    POP(op_iter, c);
                    PUSH(out_iter, c);
                } else {
                    break;
                }
            }
            PUSH(op_iter, CONCAT);
        }

        if (bad_paren) {
            error = BAD_RE;
            goto failed;
        }
    }

    while(op_iter != operators) {
        POP(op_iter, c);
        PUSH(out_iter, c);
    }

    *rpn = output;
    free(ninfix);
    free(operators);
    return 0;

failed:
    free(ninfix);
    free(output);
    free(operators);
    return error;
}

