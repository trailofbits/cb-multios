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

#include "libcgc.h"
#include "cgc_ctype.h"
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_thompson.h"
#include "cgc_constants.h"

#define OPERATOR "|*+?()"
#define TOKEN "|*+?()[]\\"

static int normalize_infix(unsigned char **pinfix, cgc_size_t size)
{
    unsigned char *new_str = *pinfix;
    unsigned char unions[200], i = 0;
    unsigned char *infix = *pinfix, *s, *e, *t = *pinfix;
    int error;
    for (; *infix ; infix++ ) {
        if ( !cgc_isprint(*infix) ) {
            error = BAD_CHARACTER;
            goto failed;
        }

        if (cgc_strchr(OPERATOR, *infix) != NULL) {
            *infix += CHAR_OFFSET;
        } else if (*infix == '\\') {
            if (infix[1] != '\0' && cgc_strchr(TOKEN, infix[1]) != NULL) {
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
            new_str = cgc_malloc(cgc_strlen(t) + cgc_strlen(unions) + 1);
            cgc_memcpy(new_str, t, s - t);
            cgc_memcpy(new_str + (s - t), unions, cgc_strlen(unions));
            cgc_memcpy(new_str + ((s - t) + cgc_strlen(unions)), e, cgc_strlen(e) + 1);
            infix = new_str + ((s - t) + cgc_strlen(unions)) - 1;
            cgc_free(t);
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

void cgc_debug_print_re(unsigned char* re)
{
    unsigned char *temp = cgc_malloc(cgc_strlen(re) + 1);
    unsigned char *ptemp = temp, *pre = re;
    for( ; *re; re++)
        *temp++ = *re > CHAR_OFFSET ? *re - CHAR_OFFSET : *re;
    temp = '\0';

    cgc_printf("Normalized re = %s\n", ptemp);
    cgc_printf("Original re = %s\n", pre);
    cgc_free(temp);
}

int cgc_retorpn(unsigned char *infix, cgc_size_t size, unsigned char **rpn)
{
    *rpn = NULL;
    if(cgc_strlen(infix) == 0)
        return BAD_RE;
    else if(cgc_strlen(infix) > MAX_RE_SIZE)
        return RE_TOO_LONG;
    else if(cgc_strlen(infix) > size)
        return BUF_OVERFLOW;

    unsigned char *output = cgc_calloc(1, (cgc_strlen(infix) * 2) + 1); // Factor in all the concats
    unsigned char *operators = cgc_calloc(1, cgc_strlen(infix) + 1);
    unsigned char *out_iter = output;
    unsigned char *op_iter = operators;
    unsigned char *ninfix = cgc_malloc(size);

    int error = 0;
    int bad_paren = 0;
    unsigned char c;

    cgc_strcpy(ninfix, infix);
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
    cgc_free(ninfix);
    cgc_free(operators);
    return 0;

failed:
    cgc_free(ninfix);
    cgc_free(output);
    cgc_free(operators);
    return error;
}

