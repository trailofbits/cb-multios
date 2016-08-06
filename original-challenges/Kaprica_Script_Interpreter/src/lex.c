/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lex.h"
#include "strio.h"

//#define DEBUG

#define MAX_NAME 256

#define END_STMT 0x100
#define END_PRINT 0x101

// prototypes
static expr_t *init_expression(int op);
static void free_expression(void *exp);
static void free_pattern(void *pat);
static void free_statement(stmt_t *stmt);

static void *parse_pattern(program_t *prog);
static int parse_statements(program_t *prog, stmt_t **result);
static int parse_expression(program_t *prog, expr_t **result, int end);
static int parse_quoted_string(program_t *prog, expr_t **result);
static int parse_regexp(program_t *prog, expr_t **result);
static int parse_number(program_t *prog, expr_t **result);
static int parse_variable(program_t *prog, expr_t **result);

static int match(program_t *prog, const char *s);
static int pattern_match(program_t *prog, const char *s);
static void skip_line(program_t *prog);
static void skip_whitespace(program_t *prog);
static int verify_expression(expr_t *expr);
static int treeify_expression(expr_t **expr, int stages);
#ifdef DEBUG
static void print_expression(expr_t *expr, const char *prefix);
static void print_statement(stmt_t *stmt, const char *prefix);
#endif
static int is_keyword(const char *s);
static int is_unary(int op);
static int is_binary(int op);
static int is_assign(int op);
static int is_assignable(int op);

void program_init(program_t *prog, io_t *io)
{
    memset(prog, 0, sizeof(program_t));
    prog->io = io;
}

int program_parse(program_t *prog)
{
    void *pat;
    pattern_t *p, *tail = NULL;
    stmt_t *actions;

    do {
        io_mark(prog->io);
        pat = parse_pattern(prog);
        if (pat == PATTERN_INVALID)
            goto fail;
        if (!parse_statements(prog, &actions))
            goto fail;
#ifdef DEBUG
        print_statement(actions, "");
#endif

        p = malloc(sizeof(pattern_t));
        if (p == NULL)
            break;

        p->pattern = pat;
        p->stmt = actions;
        p->next = NULL;

        if (tail == NULL)
            tail = prog->patterns = p;
        else
            tail = tail->next = p;
    } while (pat != PATTERN_END);
    return 1;

fail:
    free_pattern(pat);
    return 0;
}

static void *parse_pattern(program_t *prog)
{
    int c;
    unsigned int pos;
    expr_t *exp;

    if (pattern_match(prog, "BEGIN"))
        return PATTERN_BEGIN;
    if (pattern_match(prog, "END"))
        return PATTERN_END;
    if (pattern_match(prog, ""))
        return PATTERN_EMPTY;

    pos = io_tell(prog->io);
    if (!parse_expression(prog, &exp, '{'))
    {
        io_seek(prog->io, pos);
        return PATTERN_INVALID;
    }

    io_ungetc(prog->io);
    return exp;
}

static int pattern_match(program_t *prog, const char *s)
{
    unsigned int pos = io_tell(prog->io), i;
    int c;
    
    while ((c = io_getc(prog->io)) >= 0)
        if (!isspace(c))
            break;
    if (c < 0) goto fail;
    io_ungetc(prog->io);

    for (i = 0; s[i] != 0; i++)
    {
        if ((c = io_getc(prog->io)) < 0)
            goto fail;
        if (s[i] != c)
            goto fail;
    }

    skip_whitespace(prog);
    if (io_peek(prog->io) != '{')
        goto fail;

    return 1;

fail:
    io_seek(prog->io, pos);
    return 0;
}

static void free_pattern(void *pat)
{
    if (pat == PATTERN_INVALID || pat == PATTERN_EMPTY || pat == PATTERN_BEGIN || pat == PATTERN_END)
        return;

    free_expression(pat);
}

static void free_expression(void *expr)
{
}

static void free_statement(stmt_t *stmt)
{
}

static char *parse_var(program_t *prog)
{
    char tmp[MAX_NAME+1];
    unsigned int i;

    for (i = 0; i < sizeof(tmp) - 1; i++)
    {
        int c;
        c = io_getc(prog->io);
        if (c < 0)
            return NULL;
        if (islower(c) || isupper(c) || (i > 0 && isdigit(c)))
            tmp[i] = c;
        else
            break;
    }

    if (i == sizeof(tmp))
        return NULL;

    io_ungetc(prog->io);
    tmp[i] = 0;
    return strdup(tmp);
}

static int parse_statements(program_t *prog, stmt_t **result)
{
    int c;
    unsigned int pos = io_tell(prog->io), pos2;
    char *kw = NULL;
    stmt_t *stmt = NULL;
    
    skip_whitespace(prog);
    if (io_getc(prog->io) == '{')
    {
        stmt_t *tail = NULL;
        while (1)
        {
            stmt_t *tmp;

            skip_whitespace(prog);
            
            c = io_peek(prog->io);
            if (c == '#')
            {
                // skip comments
                skip_line(prog);
                continue;
            }

            if (c == '}')
            {
                io_getc(prog->io);
                break;
            }
            
            if (!parse_statements(prog, &tmp))
                goto fail;

#ifdef PATCHED
            if (tmp == NULL)
                continue;
#endif

            if (stmt == NULL)
                tail = stmt = tmp;
            else
                tail = tail->next = tmp;
        }
        *result = stmt;
        return 1;
    }
    
    pos2 = io_tell(prog->io) - 1;
    io_seek(prog->io, pos2);
    kw = parse_var(prog);
    if (kw == NULL)
        goto fail;
    skip_whitespace(prog);

    stmt = calloc(1, sizeof(stmt_t));

    if (strcmp(kw, "if") == 0)
    {
        stmt->type = STMT_IF;
        if (io_getc(prog->io) != '(')
            goto fail;
        if (!parse_expression(prog, &stmt->s_if.cond, ')'))
            goto fail;
        if (!parse_statements(prog, &stmt->s_if.child))
            goto fail;
    }
    else if (strcmp(kw, "while") == 0)
    {
        stmt->type = STMT_WHILE;
        stmt->s_while.post = 0;
        if (io_getc(prog->io) != '(')
            goto fail;
        if (!parse_expression(prog, &stmt->s_while.cond, ')'))
            goto fail;
        if (!parse_statements(prog, &stmt->s_while.child))
            goto fail;
    }
    else if (strcmp(kw, "do") == 0)
    {
        stmt->type = STMT_WHILE;
        stmt->s_while.post = 1;
        if (!parse_statements(prog, &stmt->s_while.child))
            goto fail;
        free(kw);
        skip_whitespace(prog);
        kw = parse_var(prog);
        if (kw == NULL || strcmp(kw, "while"))
            goto fail;
        skip_whitespace(prog);
        if (io_getc(prog->io) != '(')
            goto fail;
        if (!parse_expression(prog, &stmt->s_while.cond, ')'))
            goto fail;
        skip_whitespace(prog);
        if (io_getc(prog->io) != ';')
            goto fail;
    }
    else if (strcmp(kw, "for") == 0)
    {
        stmt->type = STMT_FOR;
        if (io_getc(prog->io) != '(')
            goto fail;
        if (parse_expression(prog, &stmt->s_for.init, ';'))
        {
            if (!parse_expression(prog, &stmt->s_for.cond, ';'))
                goto fail;
            if (!parse_expression(prog, &stmt->s_for.post, ')'))
                goto fail;
            if (!parse_statements(prog, &stmt->s_for.child))
                goto fail;
        }
        else
        {
            // TODO try for each syntax
            goto fail;
        }
    }
    else if (strcmp(kw, "continue") == 0)
    {
        stmt->type = STMT_CONTINUE;
        skip_whitespace(prog);
        if (io_getc(prog->io) != ';')
            goto fail;
    }
    else if (strcmp(kw, "break") == 0)
    {
        stmt->type = STMT_BREAK;
        skip_whitespace(prog);
        if (io_getc(prog->io) != ';')
            goto fail;
    }
    else if (strcmp(kw, "next") == 0)
    {
        stmt->type = STMT_NEXT;
        skip_whitespace(prog);
        if (io_getc(prog->io) != ';')
            goto fail;
    }
    else if (strcmp(kw, "exit") == 0)
    {
        stmt->type = STMT_EXIT;
        skip_whitespace(prog);
        if (io_getc(prog->io) != ';')
            goto fail;
    }
    else if (strcmp(kw, "printf") == 0 || strcmp(kw, "print") == 0)
    {
        expr_t *tail = NULL;

        stmt->type = STMT_PRINT;
        if (strcmp(kw, "printf") == 0)
        {
            if (!parse_expression(prog, &stmt->s_print.fmt, END_PRINT))
                goto fail;
            io_ungetc(prog->io);
            if (io_getc(prog->io) != ',')
                goto fail; // missing second argument
        }

        do {
            expr_t *tmp;
            if (!parse_expression(prog, &tmp, END_PRINT))
                goto fail;
            if (tail == NULL)
                tail = stmt->s_print.expr = tmp;
            else
                tail = tail->next = tmp;
        } while ((io_ungetc(prog->io), io_getc(prog->io)) == ',');
    }
    else
    {
        io_seek(prog->io, pos2);
        stmt->type = STMT_EXPR;
        if (!parse_expression(prog, &stmt->s_expr.expr, END_STMT))
            goto fail;
    }

    *result = stmt;
    return 1;

fail:
    free(kw);
    free_statement(stmt);
    io_seek(prog->io, pos);
    return 0;
}

static int parse_expression(program_t *prog, expr_t **result, int end)
{
    int pos;
    expr_t *head = NULL, *tail = NULL;
    skip_whitespace(prog);

    do
    {
        expr_t *tmp = NULL;
        int c;
        
        // strip whitespace, but need to know if there is whitespace to
        // support concatenation
        skip_whitespace(prog);

        c = io_getc(prog->io);
        if (c == end)
            break;
        // special case: new-line or semicolon terminates a statement
        if (end == END_STMT && (c == '\n' || c == ';'))
            break;
        // special case: comma or semicolon terminates expression in print
        if (end == END_PRINT && (c == '\n' || c == ';' || c == ','))
            break;

        switch (c) {
        case '(':
            if (!parse_expression(prog, &tmp, ')'))
                goto fail;
            break;
        case '"':
            io_ungetc(prog->io);
            if (!parse_quoted_string(prog, &tmp))
                goto fail;
            break;
        case '\\':
            if (io_getc(prog->io) != '\n')
                goto fail;
            break;
        case '$':
            pos = io_tell(prog->io);
            if (parse_number(prog, &tmp))
            {
                tmp->op = OP_FIELD;
                break;
            }

            io_seek(prog->io, pos);
            if (parse_variable(prog, &tmp))
            {
                tmp->op = OP_FIELD_VAR;
                break;
            }

            goto fail;
        case '?':
            tmp = init_expression(OP_CONDITIONAL);
            if (tmp == NULL)
                goto fail;
            if (!parse_expression(prog, &tmp->e_cond.vtrue, ':'))
                goto fail; 
            break;
        case '=':
            if (io_getc(prog->io) == '=')
            {
                // equality test
                tmp = init_expression(OP_EQ);
                if (tmp == NULL)
                    goto fail;
            }
            else
            {
                // assignment
                io_ungetc(prog->io);
                tmp = init_expression(OP_ASSIGN);
                if (tmp == NULL)
                    goto fail;
            }
            break;
        case '>':
            if (io_getc(prog->io) == '=')
                tmp = init_expression(OP_GTE);
            else
            {
                io_ungetc(prog->io);
                tmp = init_expression(OP_GT);
            }
            if (tmp == NULL)
                goto fail;
            break;
        case '<':
            if (io_getc(prog->io) == '=')
                tmp = init_expression(OP_LTE);
            else
            {
                io_ungetc(prog->io);
                tmp = init_expression(OP_LT);
            }
            if (tmp == NULL)
                goto fail;
            break;
        case '*':
            c = io_getc(prog->io);
            if (c == '=')
                tmp = init_expression(OP_ASSIGN_MUL);
            else
            {
                io_ungetc(prog->io);
                tmp = init_expression(OP_MUL);
            }
            break;
        case '/':
            if (tail == NULL || is_unary(tail->op) || is_binary(tail->op))
            {
                // regexp
                io_ungetc(prog->io);
                if (!parse_regexp(prog, &tmp))
                    goto fail;
            }
            else
            {
                // divide
                c = io_getc(prog->io);
                if (c == '=')
                    tmp = init_expression(OP_ASSIGN_DIV);
                else
                {
                    io_ungetc(prog->io);
                    tmp = init_expression(OP_DIV);
                }
            }
            break;
        case '%':
            c = io_getc(prog->io);
            if (c == '=')
                tmp = init_expression(OP_ASSIGN_MOD);
            else
            {
                io_ungetc(prog->io);
                tmp = init_expression(OP_MOD);
            }
            break;
        case '-':
            c = io_getc(prog->io);
            if (c == '-')
                tmp = init_expression(OP_DEC);
            else if (c == '=')
                tmp = init_expression(OP_ASSIGN_SUB);
            else
            {
                io_ungetc(prog->io);
                tmp = init_expression(OP_NEGATE_OR_SUB);
            }
            break;
        case '+':
            c = io_getc(prog->io);
            if (c == '+')
                tmp = init_expression(OP_INC);
            else if (c == '=')
                tmp = init_expression(OP_ASSIGN_ADD);
            else
            {
                io_ungetc(prog->io);
                tmp = init_expression(OP_ADD);
            }
            break;
        case '&':
            if (io_getc(prog->io) == '&')
                tmp = init_expression(OP_AND);
            else
                goto fail;
            break;
        case '|':
            if (io_getc(prog->io) == '|')
                tmp = init_expression(OP_OR);
            else
                goto fail;
            break;
        case '~':
            tmp = init_expression(OP_MATCH);
            break;
        case '!':
            c = io_getc(prog->io);
            if (c == '=')
                tmp = init_expression(OP_NEQ);
            else if (c == '~')
                tmp = init_expression(OP_NOT_MATCH);
            else
            {
                io_ungetc(prog->io);
                tmp = init_expression(OP_NOT);
            }
            break;
        default:
            io_ungetc(prog->io);

            pos = io_tell(prog->io);
            if (parse_number(prog, &tmp))
                break;

            io_seek(prog->io, pos);
            if (parse_variable(prog, &tmp))
                break;

            goto fail;
        }

        // XXX somehow merge expr and tmp
        if (tmp != NULL)
        {
            if (tail == NULL)
            {
                head = tail = tmp;
                tmp->next = NULL;
                tmp->prev = NULL;
            }
            else
            {
                tail->next = tmp;
                tmp->prev = tail;
                tmp->next = NULL;
                tail = tmp;
            }
        }
    } while (1);

    // convert linked list into tree using precedence rules
    if (!treeify_expression(&head, 99))
        goto fail;

    *result = head;
    return 1;

fail:
    free_expression(head);
    return 0;
}

static int parse_variable(program_t *prog, expr_t **result)
{
    char *name = NULL;
    expr_t *expr = NULL;

    name = parse_var(prog);
    if (name == NULL || strlen(name) == 0 || is_keyword(name))
        goto fail;

    expr = init_expression(OP_VAR);
    if (expr == NULL)
        goto fail;

    expr->e_var.name = name;
    *result = expr;
    return 1;

fail:
    free(name);
    return 0;
}

// TODO: support octal and hexadecimal constants
static int parse_number(program_t *prog, expr_t **result)
{
    char buf[64];
    int c, i = 0, value;
    expr_t *expr = NULL;

    do {
        c = io_getc(prog->io);
        if (c < 0)
            goto fail;
        buf[i++] = c;
    } while (i < sizeof(buf) && isdigit(c));

    io_ungetc(prog->io);
    if (i <= 1)
        goto fail;

    buf[i-1] = 0;
    value = strtol(buf, NULL, 10);

    expr = init_expression(OP_CONST_INT);
    if (expr == NULL)
        goto fail;

    expr->e_cint.value = value;
    *result = expr;

    return 1;

fail:
    free(expr);
    return 0;
}

static int parse_regexp(program_t *prog, expr_t **result)
{
    int c;
    expr_t *expr = NULL;
    strio_t str;

    strio_init(&str);

    if (!io_getc(prog->io) == '"')
        goto fail;

    while (1)
    {
        c = io_getc(prog->io);
        if (c < 0)
            goto fail;
        else if (c == '/')
            break;
        else if (c != '\\')
            strio_append_char(&str, c);
        else
        {
            if (io_getc(prog->io) == '/')
                strio_append_char(&str, '/');
            else
                io_ungetc(prog->io);
        }
    }

    expr = init_expression(OP_CONST_REGEXP);
    if (expr == NULL)
        goto fail;

    expr->e_cregexp.value = strio_dup(&str);
    if (expr->e_cregexp.value == NULL)
        goto fail;

    strio_free(&str);
    *result = expr;
    return 1;

fail:
    free(expr);
    strio_free(&str);
    return 0;
}

static int parse_quoted_string(program_t *prog, expr_t **result)
{
    int c;
    expr_t *expr = NULL;
    strio_t str;

    strio_init(&str);

    if (!io_getc(prog->io) == '"')
        goto fail;

    while (1)
    {
        c = io_getc(prog->io);
        if (c < 0)
            goto fail;
        else if (c == '"')
            break;
        else if (c != '\\')
            strio_append_char(&str, c);
        else
        {
            int c2 = io_getc(prog->io);
            if (c2 < 0)
                goto fail;
            switch (c2)
            {
            case '\n':
                // ignore
                break;
            case 'a':
                strio_append_char(&str, '\a');
                break;
            case 'b':
                strio_append_char(&str, '\b');
                break;
            case 't':
                strio_append_char(&str, '\t');
                break;
            case 'n':
                strio_append_char(&str, '\n');
                break;
            case 'v':
                strio_append_char(&str, '\v');
                break;
            case 'f':
                strio_append_char(&str, '\f');
                break;
            case 'r':
                strio_append_char(&str, '\r');
                break;
            case 'x':
                // XXX parse hex
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                // XXX parse octal
                break;
            default:
                strio_append_char(&str, c);
                // fall through
            case '\\':
            case '"':
                strio_append_char(&str, c2);
                break;
            }
        }
    }

    expr = init_expression(OP_CONST_STRING);
    if (expr == NULL)
        goto fail;

    expr->e_cstring.value = strio_dup(&str);
    if (expr->e_cstring.value == NULL)
        goto fail;

    *result = expr;
    strio_free(&str);
    return 1;

fail:
    free(expr);
    strio_free(&str);
    return 0;
}

static void skip_line(program_t *prog)
{
    int c;
    while ((c = io_getc(prog->io)) >= 0)
    {
        if (c == '\n')
            break;
    }
}

static void skip_whitespace(program_t *prog)
{
    int c;
    while ((c = io_getc(prog->io)) >= 0)
    {
        if (!isspace(c))
        {
            io_ungetc(prog->io);
            break;
        }
    }
}

static int is_keyword(const char *s)
{
    if (strcmp(s, "if") == 0 ||
        strcmp(s, "while") == 0 ||
        strcmp(s, "continue") == 0 ||
        strcmp(s, "do") == 0 ||
        strcmp(s, "for") == 0 || 
        strcmp(s, "break") == 0 ||
        strcmp(s, "next") == 0 ||
        strcmp(s, "exit") == 0 ||
        strcmp(s, "print") == 0 ||
        strcmp(s, "printf") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

static const char *op_to_name(int op)
{
#define CASE(x) case OP_##x : \
    return #x ;

    switch (op)
    {
    CASE(CONST_STRING)
    CASE(CONST_INT)
    CASE(CONST_REGEXP)
    CASE(FIELD)
    CASE(FIELD_VAR)
    CASE(VAR)
    CASE(ASSIGN)
    CASE(ASSIGN_ADD)
    CASE(ASSIGN_SUB)
    CASE(ASSIGN_MUL)
    CASE(ASSIGN_DIV)
    CASE(ASSIGN_MOD)
    CASE(CONDITIONAL)
    CASE(OR)
    CASE(AND)
    /*CASE(IN)*/
    CASE(MATCH)
    CASE(NOT_MATCH)
    CASE(LT)
    CASE(GT)
    CASE(LTE)
    CASE(GTE)
    CASE(EQ)
    CASE(NEQ)
    CASE(CONCAT)
    CASE(ADD)
    CASE(SUB)
    CASE(MUL)
    CASE(DIV)
    CASE(MOD)
    CASE(NEGATE)
    CASE(NOT)
    CASE(INC_PRE)
    CASE(INC_POST)
    CASE(DEC_PRE)
    CASE(DEC_POST)
    CASE(INC)
    CASE(DEC)
    CASE(NEGATE_OR_SUB)
    default:
        return "???";
    }

#undef CASE
}

static int is_unary(int op)
{
    return op == OP_NEGATE ||
        op == OP_NOT ||
        op == OP_INC_PRE ||
        op == OP_INC_POST ||
        op == OP_DEC_PRE ||
        op == OP_DEC_POST;
}

static int is_binary(int op)
{
    return op == OP_ASSIGN ||
        op == OP_ASSIGN_ADD ||
        op == OP_ASSIGN_SUB ||
        op == OP_ASSIGN_MUL ||
        op == OP_ASSIGN_DIV || 
        op == OP_ASSIGN_MOD ||
        op == OP_OR ||
        op == OP_AND ||
        /*op == OP_IN ||*/
        op == OP_MATCH ||
        op == OP_NOT_MATCH ||
        op == OP_LT ||
        op == OP_GT ||
        op == OP_LTE ||
        op == OP_GTE ||
        op == OP_EQ ||
        op == OP_NEQ ||
        op == OP_CONCAT ||
        op == OP_ADD ||
        op == OP_SUB ||
        op == OP_MUL ||
        op == OP_DIV ||
        op == OP_MOD;
}

static int is_assign(int op)
{
    return op == OP_ASSIGN ||
        op == OP_ASSIGN_ADD ||
        op == OP_ASSIGN_SUB ||
        op == OP_ASSIGN_MUL ||
        op == OP_ASSIGN_DIV ||
        op == OP_ASSIGN_MOD;
}

static int is_assignable(int op)
{
    return op == OP_FIELD ||
        op == OP_FIELD_VAR ||
        op == OP_VAR;
}

static void unlink(expr_t *e)
{
    if (e->next)
        e->next->prev = e->prev;
    if (e->prev)
        e->prev->next = e->next;
    e->next = NULL;
    e->prev = NULL;
}

static int treeify_expression(expr_t **expr, int stages)
{
    expr_t *iter, *old;
    if (*expr == NULL)
        return 1;

    old = (*expr)->prev;
    (*expr)->prev = NULL;

    for (iter = *expr; iter != NULL; iter = iter->next)
    {
        if (iter->op == OP_NOT && iter->e_unop.expr == NULL)
        {
            if (iter->next == NULL)
                goto fail;
            if (!treeify_expression(&iter->next, 1))
                goto fail;
            iter->e_unop.expr = iter->next;
            unlink(iter->e_unop.expr);
        }
    }

    if (stages < 2)
        goto done;

    // process post- and pre- increment/decrement
    for (iter = *expr; iter != NULL; iter = iter->next)
    {
        if (iter->op == OP_DEC && iter->e_unop.expr == NULL)
        {
            if (iter->prev != NULL && is_assignable(iter->prev->op))
            {
                iter->op = OP_DEC_POST;
                iter->e_unop.expr = iter->prev;
                unlink(iter->e_unop.expr);
                if (*expr == iter->e_unop.expr)
                    *expr = iter;
            }
            else if (iter->next != NULL && is_assignable(iter->next->op))
            {
                iter->op = OP_DEC_PRE;
                iter->e_unop.expr = iter->next;
                unlink(iter->e_unop.expr);
            }
        }
        if (iter->op == OP_INC && iter->e_unop.expr == NULL)
        {
            if (iter->prev != NULL && is_assignable(iter->prev->op))
            {
                iter->op = OP_INC_POST;
                iter->e_unop.expr = iter->prev;
                unlink(iter->e_unop.expr);
                if (*expr == iter->e_unop.expr)
                    *expr = iter;
            }
            else if (iter->next != NULL && is_assignable(iter->next->op))
            {
                iter->op = OP_INC_PRE;
                iter->e_unop.expr = iter->next;
                unlink(iter->e_unop.expr);
            }
        }
    }

    if (stages < 4)
        goto done;

    // process assignments first from right-to-left
    for (iter = *expr; iter->next != NULL; iter = iter->next) ;
    while (iter != NULL)
    {
        if (is_assign(iter->op) && iter->e_binop.lhs == NULL)
        {
            if (iter->prev == NULL || iter->next == NULL)
                goto fail;
            if (!is_assignable(iter->prev->op))
                goto fail;

            if (!treeify_expression(&iter->next, 99))
                goto fail;

            iter->e_binop.lhs = iter->prev;
            iter->e_binop.rhs = iter->next;
            unlink(iter->e_binop.lhs);
            unlink(iter->e_binop.rhs);

            if (*expr == iter->e_binop.lhs)
                *expr = iter;
        }
        iter = iter->prev;
    }

    // process conditionals
    for (iter = *expr; iter->next != NULL; iter = iter->next) ;
    while (iter != NULL)
    {
        if (iter->op == OP_CONDITIONAL && iter->e_cond.cond == NULL)
        {
            if (iter->prev == NULL || iter->next == NULL)
                goto fail;

            if (!treeify_expression(&iter->next, 99))
                goto fail;
            iter->e_cond.vfalse = iter->next;
            unlink(iter->e_cond.vfalse);

            iter->e_cond.cond = *expr;
            iter->prev->next = NULL;
            iter->prev = NULL;
            *expr = iter;
            if (!treeify_expression(&iter->e_cond.cond, 99))
                goto fail;
        }
        iter = iter->prev;
    }

#define HANDLE_BINOP(x) do { \
        if (iter->op == x && iter->e_binop.lhs == NULL) { \
            if (iter->prev == NULL || iter->next == NULL) \
                goto fail; \
            if (!treeify_expression(&iter->next, 99)) \
                goto fail; \
            iter->e_binop.lhs = iter->prev; \
            iter->e_binop.rhs = iter->next; \
            unlink(iter->e_binop.lhs); \
            unlink(iter->e_binop.rhs); \
            if (*expr == iter->e_binop.lhs) \
                *expr = iter; \
        } \
    } while (0)

    // process logical operators
    for (iter = *expr; iter != NULL; iter = iter->next)
    {
        HANDLE_BINOP(OP_OR);
    }
    
    for (iter = *expr; iter != NULL; iter = iter->next)
    {
        HANDLE_BINOP(OP_AND);
    }

#if 0
    for (iter = *expr; iter != NULL; iter = iter->next)
    {
        HANDLE_BINOP(OP_IN);
    }
#endif

    // process match operators
    for (iter = *expr; iter != NULL; iter = iter->next)
    {
        HANDLE_BINOP(OP_NOT_MATCH);
        HANDLE_BINOP(OP_MATCH);
    }

    // process relational operators
    for (iter = *expr; iter != NULL; iter = iter->next)
    {
        HANDLE_BINOP(OP_EQ);
        HANDLE_BINOP(OP_NEQ);
        HANDLE_BINOP(OP_LT);
        HANDLE_BINOP(OP_LTE);
        HANDLE_BINOP(OP_GT);
        HANDLE_BINOP(OP_GTE);
    }

    // process arithmetic operators
    for (iter = *expr; iter != NULL; iter = iter->next)
    {
        HANDLE_BINOP(OP_ADD);
        if (iter->op == OP_NEGATE_OR_SUB)
        {
            if (iter->next != NULL && iter->prev != NULL)
            {
                iter->op = OP_SUB;
                HANDLE_BINOP(OP_SUB);
            }
        }
    }

    for (iter = *expr; iter != NULL; iter = iter->next)
    {
        HANDLE_BINOP(OP_MUL);
        HANDLE_BINOP(OP_DIV);
        HANDLE_BINOP(OP_MOD);
    }

    // unary operators
    for (iter = *expr; iter != NULL; iter = iter->next)
    {
        if (iter->op == OP_NEGATE_OR_SUB)
        {
            if (iter->next == NULL)
                goto fail;
            if (!treeify_expression(&iter->next, 99))
                goto fail;
            iter->op = OP_NEGATE;
            iter->e_unop.expr = iter->next;
            unlink(iter->e_unop.expr);
        }
    }

    // combine remainder with concatenations
    while ((*expr)->next)
    {
        if (!treeify_expression(&(*expr)->next, 99))
            goto fail;

        iter = init_expression(OP_CONCAT);
        iter->e_binop.lhs = *expr;
        iter->e_binop.rhs = (*expr)->next;
        unlink((*expr)->next);
        unlink(*expr);
        *expr = iter;
    }

#undef HANDLE_BINOP

done:
    (*expr)->prev = old;
    return 1;

fail:
    (*expr)->prev = old;
    return 0;
}

static int verify_expression(expr_t *expr)
{
#ifdef DEBUG
    print_expression(expr, "");
#endif
    fdprintf(STDERR, "\n");
    return 1;
}

static expr_t *init_expression(int op)
{
    expr_t *expr = calloc(1, sizeof(expr_t));
    if (expr == NULL)
        return NULL;
    expr->op = op;
    return expr;
}

#ifdef DEBUG
static void print_expression(expr_t *expr, const char *prefix)
{
    char buf[64];
    if (expr == NULL)
        return;

    strcpy(buf, prefix);
    fdprintf(STDERR, "%s%s", prefix, op_to_name(expr->op));
    switch (expr->op)
    {
    case OP_CONST_REGEXP:
        fdprintf(STDERR, "[%s]", expr->e_cregexp.value);
        break;
    case OP_CONST_STRING:
        fdprintf(STDERR, "[%s]", expr->e_cstring.value);
        break;
    case OP_FIELD:
    case OP_CONST_INT:
        fdprintf(STDERR, " [%d]", expr->e_cint.value);
        break;
    case OP_FIELD_VAR:
    case OP_VAR:
        fdprintf(STDERR, " [%s]", expr->e_var.name);
        break;
    default:
        break;
    }

    fdprintf(STDERR, "\n");

    if (strlen(buf) < sizeof(buf)-1)
        strcat(buf, "\t");

    if (expr->op == OP_CONDITIONAL)
    {
        fdprintf(STDERR, "%scond=\n", prefix);
        print_expression(expr->e_cond.cond, buf);
        fdprintf(STDERR, "%svtrue=\n", prefix);
        print_expression(expr->e_cond.vtrue, buf);
        fdprintf(STDERR, "%svfalse=\n", prefix);
        print_expression(expr->e_cond.vfalse, buf);
    }
    else if (is_unary(expr->op))
    {
        print_expression(expr->e_unop.expr, buf);
    }
    else if (is_binary(expr->op))
    {
        fdprintf(STDERR, "%slhs=\n", prefix);
        print_expression(expr->e_binop.lhs, buf);
        fdprintf(STDERR, "%srhs=\n", prefix);
        print_expression(expr->e_binop.rhs, buf);
    }

    print_expression(expr->next, prefix);
}

static const char *stmt_to_name(int type)
{
#define CASE(x) case STMT_##x : \
    return #x ;
    switch(type)
    {
    CASE(IF)
    CASE(WHILE)
    CASE(FOR)
    CASE(FOREACH)
    CASE(CONTINUE)
    CASE(BREAK)
    CASE(NEXT)
    CASE(EXIT)
    CASE(PRINT)
    CASE(EXPR)
    default:
        return "???";
    }
#undef CASE
}

static void print_statement(stmt_t *stmt, const char *prefix)
{
    char buf[64];
    if (stmt == NULL)
        return;

    fdprintf(STDERR, "%s%s\n", prefix, stmt_to_name(stmt->type));
    
    strcpy(buf, prefix);
    if (strlen(buf) < sizeof(buf) - 1)
        strcat(buf, "\t");

    switch(stmt->type)
    {
    case STMT_WHILE:
        fdprintf(STDERR, "%spost=%d\n", prefix, stmt->s_while.post);
        fdprintf(STDERR, "%scond=\n", prefix);
        print_expression(stmt->s_while.cond, buf);
        fdprintf(STDERR, "%schild=\n", prefix);
        print_statement(stmt->s_while.child, buf);
        break;
    case STMT_EXIT:
        fdprintf(STDERR, "%svalue=%d\n", stmt->s_exit.value);
        break;
    case STMT_IF:
        fdprintf(STDERR, "%scond=\n", prefix);
        print_expression(stmt->s_if.cond, buf);
        fdprintf(STDERR, "%schild=\n", prefix);
        print_statement(stmt->s_if.child, buf);
        break;
    case STMT_EXPR:
        fdprintf(STDERR, "%sexpr=\n", prefix);
        print_expression(stmt->s_expr.expr, buf);
        break;
    case STMT_FOR:
        fdprintf(STDERR, "%sinit=\n", prefix);
        print_expression(stmt->s_for.init, buf);
        fdprintf(STDERR, "%scond=\n", prefix);
        print_expression(stmt->s_for.cond, buf);
        fdprintf(STDERR, "%spost=\n", prefix);
        print_expression(stmt->s_for.post, buf);
        fdprintf(STDERR, "%schild=\n", prefix);
        print_statement(stmt->s_for.child, buf);
        break;
    case STMT_PRINT:
        fdprintf(STDERR, "%sfmt=\n", prefix);
        print_expression(stmt->s_print.fmt, buf);
        fdprintf(STDERR, "%sargs=\n", prefix);
        print_expression(stmt->s_print.expr, buf);
        break;
    }

    print_statement(stmt->next, prefix);
}
#endif
