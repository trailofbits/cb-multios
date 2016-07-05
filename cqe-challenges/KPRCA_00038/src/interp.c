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
#include <string.h>
#include "dict.h"
#include "interp.h"
#include "io.h"
#include "lex.h"
#include "regexp.h"

#define BUF_SIZE 4096
#define MAX_FIELDS (0x10000)

enum {
    FALSE = 0,
    TRUE = 1
};

enum {
    EVAL_ERROR = 0,
    EVAL_FINISHED,
    EVAL_CONTINUE,
    EVAL_BREAK,
    EVAL_NEXT,
    EVAL_EXIT
};

typedef struct {
    program_t *prog;
    io_t *io;
    dict_t vars;
    char *buf;
    const char *field0;
    char **fields;
    int num_fields;
    var_t result;
} interp_t;

extern int eprintf(int fd, const char *fmt, var_t *args, unsigned int cnt);
static int eval_expression(interp_t *interp, expr_t *expr);

static var_t *new_number(unsigned int value)
{
    var_t *var = calloc(1, sizeof(var_t));
    if (var == NULL)
        return NULL;
    var->type = VAR_NUMBER;
    var->v_number.value = value;
    return var;
}

static var_t *new_string(char *value)
{
    if (value == NULL)
        return NULL;

    var_t *var = calloc(1, sizeof(var_t));
    if (var == NULL)
        return NULL;

    var->type = VAR_STRING;
    var->v_string.value = value;
    return var;
}

static void free_var(void *v)
{
    var_t *var = v;
    switch (var->type)
    {
    case VAR_NUMBER:
        free(var->v_number.strvalue);
        break;
    case VAR_STRING:
        //free(var->v_string.value);
        break;
#if 0
    case VAR_ARRAY:
        dict_free(var->v_array.value);
        free(var->v_array.value);
        break;
#endif
    }
    var->type = VAR_NULL;
}

static int copy_var(var_t *dst, var_t *src)
{
    char *s;

    switch (src->type)
    {
    case VAR_NUMBER:
        dst->v_number.value = src->v_number.value;
        dst->v_number.strvalue = NULL;
        break;
    case VAR_STRING:
        if ((s = strdup(src->v_string.value)) == NULL)
            return 0;
        dst->v_string.value = s;
        break;
    }
    dst->type = src->type;
    return 1;
}

static void move_var(var_t *dst, var_t *src)
{
    switch (src->type)
    {
    case VAR_NUMBER:
        dst->v_number = src->v_number;
        break;
    case VAR_STRING:
        dst->v_string = src->v_string;
        break;
    }

    dst->type = src->type;
    src->type = VAR_NULL;
}

static void to_string_buf(unsigned int value, char *tmp)
{
    sprintf(tmp, "%d", value);
}

static char *to_string(unsigned int value)
{
    char tmp[20];
    sprintf(tmp, "%d", value);
    return strdup(tmp);
}

static var_t *get_var(interp_t *interp, const char *name)
{
    var_t *var;

    var = dict_get(&interp->vars, name);
    if (var == NULL)
    {
        // initialize as null variable
        var = malloc(sizeof(var_t));
        if (var == NULL)
            return NULL;
        var->type = VAR_NULL;
        if (!dict_add(&interp->vars, name, var))
        {
            free(var);
            return NULL;
        }
    }

    return var;
}

static const char *get_string(interp_t *interp, const char *name)
{
    var_t *var;

    var = get_var(interp, name);
    if (var == NULL)
        return NULL;

    if (var->type == VAR_NUMBER)
    {
        if (var->v_number.strvalue == NULL)
        {
            // convert to a string
            char *str = to_string(var->v_number.value);
            if (str == NULL)
                return NULL;
            var->v_number.strvalue = str;
        }
        return var->v_number.strvalue;
    }
    if (var->type == VAR_STRING)
        return var->v_string.value;
    if (var->type == VAR_NULL)
        return "";
    return NULL;
}

static int coerce_number(interp_t *interp, var_t *var)
{
    if (var->type == VAR_NULL)
        return 0;
    if (var->type == VAR_NUMBER)
        return var->v_number.value;
    if (var->type == VAR_STRING)
        return strtol(var->v_string.value, NULL, 0);
    return 0;
}

static int coerce_bool(interp_t *interp, var_t *var)
{
    if (var->type == VAR_NUMBER)
        return var->v_number.value ? TRUE : FALSE;
    if (var->type == VAR_STRING)
        return var->v_string.value[0] ? TRUE : FALSE;
    return FALSE;
}

static int get_number(interp_t *interp, const char *name, int *result)
{
    var_t *var;

    var = get_var(interp, name);
    if (var == NULL)
        return 0;

    if (var->type == VAR_ARRAY)
        return 0;
    
    *result = coerce_number(interp, var);
    return 1;
}

static int read_record(interp_t *interp)
{
    unsigned int i, min, ignore_blank = 0;
    const char *rs = get_string(interp, "RS");
    if (rs == NULL)
        goto fail;

    min = strlen(rs);
    if (min == 0)
    {
        rs = "\n";
        ignore_blank = 1;
        min = 1;
    }

    if (min >= BUF_SIZE)
        goto fail;

    do {
        for (i = 0; i < BUF_SIZE-1; )
        {
            int c;
            c = io_getc(interp->io);
            if (c < 0)
                goto fail;
            interp->buf[i++] = c;

            if (i >= min)
            {
                if (strncmp(&interp->buf[i - min], rs, min) == 0)
                {
                    i -= min;
                    break;
                }
            }
        }
        interp->buf[i] = 0;
    } while (ignore_blank && strlen(interp->buf) == 0);

    return 1;

fail:
    return 0;
}

static void free_fields(interp_t *interp)
{
    int i;
    if (interp->fields)
    {
        for (i = 0; i < interp->num_fields; i++)
            free(interp->fields[i]);
        free(interp->fields);
    }
    interp->fields = NULL;
    interp->num_fields = 0;
}

static int read_fields(interp_t *interp)
{
    unsigned int i, cnt, min, last;
    const char *fs = get_string(interp, "FS");
    char *s;

    if (fs == NULL)
        goto fail;

    min = strlen(fs);

    free_fields(interp);
    interp->field0 = interp->buf;

    if (interp->buf[0] == 0)
        return 1;

    for (cnt = 0, i = 0; interp->buf[i] != 0; i++)
    {
        if (min == 0)
        {
            cnt++;
        }
        else if (strncmp(&interp->buf[i], fs, min) == 0)
        {
            i += min - 1;
            cnt++;
        }
    }

    if (cnt >= MAX_FIELDS)
        goto fail;

    interp->num_fields = cnt + 1;
    interp->fields = calloc(sizeof(char *), interp->num_fields);
    if (interp->fields == NULL)
        goto fail;

    
    for (last = 0, cnt = 0, i = 0; interp->buf[i] != 0; i++)
    {
        if (min != 0 && strncmp(&interp->buf[i], fs, min) != 0)
            continue;
        s = malloc(i - last + 1);
        if (s == NULL)
            goto fail;
        memcpy(s, &interp->buf[last], i - last);
        s[i - last] = 0;
        interp->fields[cnt++] = s;

        if (cnt == interp->num_fields)
            goto fail;

        if (min)
            i += min - 1;
        last = i + 1;
    }

    s = malloc(i - last + 1);
    if (s == NULL)
        goto fail;
    memcpy(s, &interp->buf[last], i - last);
    s[i - last] = 0;
    interp->fields[cnt++] = s;
    return 1;

fail:
    free_fields(interp);
    return 0;
}

static int combine_fields(interp_t *interp)
{
    unsigned int cnt, i, ofs_len;
    const char *ofs = get_string(interp, "OFS");
    ofs_len = strlen(ofs);

    for (cnt = 0, i = 0; i < interp->num_fields; i++)
    {
        unsigned int len = interp->fields[i] == NULL ? 0 : strlen(interp->fields[i]);
        if (cnt + len + ofs_len >= BUF_SIZE - 1)
            return 0;
        if (i)
            cnt += ofs_len;
        cnt += len;
    }

    for (cnt = 0, i = 0; i < interp->num_fields; i++)
    {
        unsigned int len = interp->fields[i] == NULL ? 0 : strlen(interp->fields[i]);
        if (i)
        {
            memcpy(&interp->buf[cnt], ofs, ofs_len);
            cnt += ofs_len;
        }
        memcpy(&interp->buf[cnt], interp->fields[i], len);
        cnt += len;
    }
    interp->buf[cnt] = 0;
    interp->field0 = interp->buf;

    return 1;
}

static const char *get_field(interp_t *interp, unsigned int num)
{
    if (interp->fields == NULL)
    {
        if (num == 0)
            return interp->buf;

        if (!read_fields(interp))
            return NULL;
    }

    if (num > interp->num_fields)
        return "";

    if (num == 0)
    {
        if (interp->field0 == NULL)
            if (!combine_fields(interp))
                return NULL;
        return interp->field0;
    }

    return interp->fields[num-1] ? : "";
}

static int set_field(interp_t *interp, unsigned int num, const char *value)
{
    char **fields, *copy;
    if (num > MAX_FIELDS)
        return 0;

    if (interp->fields == NULL && num > 0)
    {
        if (!read_fields(interp))
            return 0;
    }

    if (num > interp->num_fields)
    {
        fields = realloc(interp->fields, num * sizeof(char *));
        if (fields == NULL)
            return 0;
        interp->fields = fields;
        memset(&interp->fields[interp->num_fields], 0, sizeof(char *) * (num - interp->num_fields));
        interp->num_fields = num;
    }

    if (num == 0)
    {
        if (strlen(value) >= BUF_SIZE - 1)
            return 0;
        strcpy(interp->buf, value);
        free_fields(interp);
        interp->field0 = interp->buf;
    }
    else
    {
        copy = strdup(value);
        if (copy == NULL)
            return 0;

        interp->fields[num-1] = copy;
        interp->field0 = NULL;
    }
    return 1;
}

static int set_result_string(interp_t *interp, char *value)
{
    free_var(&interp->result);

    interp->result.type = VAR_STRING;
    interp->result.v_string.value = value;
    return 1;
}

static int set_result_number(interp_t *interp, unsigned int value)
{
    free_var(&interp->result);

    interp->result.type = VAR_NUMBER;
    interp->result.v_number.value = value;
    return 1;
}

static int set_result_var(interp_t *interp, var_t *var)
{
    free_var(&interp->result);

    if (var->type == VAR_NUMBER)
    {
        interp->result.v_number.value = var->v_number.value;
    }
    else if (var->type == VAR_STRING)
    {
        char *s = strdup(var->v_string.value);
        if (s == NULL)
            return 0;
        interp->result.v_string.value = s;
    }
    interp->result.type = var->type;
    return 1;
}

static int assign_result(interp_t *interp, expr_t *expr)
{
    char tmp[20];
    if (expr->op == OP_FIELD || expr->op == OP_FIELD_VAR)
    {
        int num;
        if (expr->op == OP_FIELD)
            num = expr->e_cint.value;
        else
        {
            if (!get_number(interp, expr->e_var.name, &num))
                return 0;
        }

        if (interp->result.type == VAR_NUMBER)
        {
            to_string_buf(interp->result.v_number.value, tmp);
            return set_field(interp, num, tmp);
        }
        else if (interp->result.type == VAR_STRING)
        {
            return set_field(interp, num, interp->result.v_string.value);
        }
        return 0;
    }
    else if (expr->op == OP_VAR)
    {
        var_t *var = NULL;
        if (interp->result.type == VAR_STRING)
            var = new_string(strdup(interp->result.v_string.value));
        else
            var = new_number(interp->result.v_number.value);
        if (var == NULL)
            return 0;
        return dict_add(&interp->vars, expr->e_var.name, var);
    }
    else
    {
        return 0;
    }
}

static int compare_value(var_t *lhs, var_t *rhs)
{
    char tmp[20];

    if (lhs->type == VAR_STRING && rhs->type == VAR_STRING)
        return strcmp(lhs->v_string.value, rhs->v_string.value);

    if (lhs->type == VAR_STRING && rhs->type == VAR_NUMBER)
    {
        to_string_buf(rhs->v_number.value, tmp);
        return strcmp(lhs->v_string.value, tmp);
    }

    if (lhs->type == VAR_NUMBER && rhs->type == VAR_STRING)
    {
        sprintf(tmp, "%d", lhs->v_number.value);
        return strcmp(tmp, rhs->v_string.value);
    }

    if (lhs->type == VAR_NUMBER && rhs->type == VAR_NUMBER)
        return lhs->v_number.value - rhs->v_number.value;

    if (lhs->type == VAR_NULL && rhs->type == VAR_STRING)
        return strcmp("", rhs->v_string.value);
    if (rhs->type == VAR_NULL && lhs->type == VAR_STRING)
        return strcmp(rhs->v_string.value, "");

    if (lhs->type == VAR_NULL && rhs->type == VAR_NUMBER)
        return 0 - rhs->v_number.value;
    if (rhs->type == VAR_NULL && lhs->type == VAR_NUMBER)
        return rhs->v_number.value - 0;

    return 1;
}

static int do_concat(interp_t *interp, expr_t *e1, expr_t *e2)
{
    char *out;
    unsigned int len = 0;
    int result = 0;
    var_t v1, v2;
    
    v1.type = v2.type = VAR_NULL;

    if (!eval_expression(interp, e1))
        goto fail;

    move_var(&v1, &interp->result);

    if (!eval_expression(interp, e2))
        goto fail;

    move_var(&v2, &interp->result);

    if (v1.type == VAR_STRING)
        len += strlen(v1.v_string.value) + 1;
    else if (v1.type == VAR_NUMBER || v1.type == VAR_NULL)
        len += 20;
    else
        goto fail;

    if (v2.type == VAR_STRING)
        len += strlen(v2.v_string.value) + 1;
    else if (v2.type == VAR_NUMBER || v2.type == VAR_NULL)
        len += 20;
    else
        goto fail;

    out = malloc(len);
    if (out == NULL)
        goto fail;

    if (v1.type == VAR_STRING)
        sprintf(out, "%s", v1.v_string.value);
    else if (v1.type == VAR_NUMBER)
        sprintf(out, "%d", v1.type == VAR_NUMBER ? v1.v_number.value : 0);
    else
        out[0] = 0;

    if (v2.type == VAR_STRING)
        sprintf(out + strlen(out), "%s", v2.v_string.value);
    else if (v2.type == VAR_NUMBER)
        sprintf(out + strlen(out), "%d", v2.type == VAR_NUMBER ? v2.v_number.value : 0);

    result = set_result_string(interp, out);

fail:
    free_var(&v1);
    free_var(&v2);
    return result;
}

static int do_match(interp_t *interp, expr_t *lhs, expr_t *rhs)
{
    int result;
    char tmp1[20], tmp2[20];
    const char *str = NULL, *exp = NULL;
    regexp_t r;

    if (lhs == NULL)
    {
        str = get_field(interp, 0);
    }
    else
    {
        if (!eval_expression(interp, lhs))
            return 0;
        
        if (interp->result.type == VAR_STRING)
        {
            str = interp->result.v_string.value;
        }
        else if (interp->result.type == VAR_NUMBER)
        {
            to_string_buf(interp->result.v_number.value, tmp1);
            str = tmp1;
        }
    }

    if (str == NULL)
        return 0;

    if (rhs->op == OP_CONST_REGEXP)
    {
        exp = rhs->e_cregexp.value;
    }
    else
    {
        if (!eval_expression(interp, rhs))
            return 0;

        if (interp->result.type == VAR_STRING)
        {
            exp = interp->result.v_string.value;
        }
        else if (interp->result.type == VAR_NUMBER)
        {
            to_string_buf(interp->result.v_number.value, tmp2);
            exp = tmp2;
        }
    }

    if (exp == NULL)
        return 0;

    if (!regexp_init(&r, exp))
        return 0;

    result = regexp_match(&r, str);
    regexp_free(&r);

    return set_result_number(interp, result ? TRUE : FALSE);
}

static int eval_expression(interp_t *interp, expr_t *expr)
{
    const char *s;
    int i, t1, t2;
    var_t tmp;

#ifdef PATCHED
    if (expr == NULL)
        return 0;
#endif

    switch(expr->op)
    {
    case OP_CONST_STRING:
        if (!set_result_string(interp, strdup(expr->e_cstring.value)))
            return 0;
        break;
    case OP_CONST_INT:
        if (!set_result_number(interp, expr->e_cint.value))
            return 0;
        break;
    case OP_FIELD:
        s = get_field(interp, expr->e_cint.value);
        if (s == NULL)
            return 0;
        if (!set_result_string(interp, strdup(s)))
            return 0;
        break;
    case OP_FIELD_VAR:
        if (!get_number(interp, expr->e_var.name, &i))
            return 0;
        s = get_field(interp, i);
        if (s == NULL)
            return 0;
        if (!set_result_string(interp, strdup(s)))
            return 0;
        break;
    case OP_VAR:
        if (!set_result_var(interp, get_var(interp, expr->e_var.name)))
            return 0;
        break;
    case OP_ASSIGN:
        if (!eval_expression(interp, expr->e_binop.rhs))
            return 0;
        // set lhs to interp->result
        if (!assign_result(interp, expr->e_binop.lhs))
            return 0;
        break;
    case OP_CONDITIONAL:
        if (!eval_expression(interp, expr->e_cond.cond))
            return 0;
        if (coerce_bool(interp, &interp->result))
        {
            if (!eval_expression(interp, expr->e_cond.vtrue))
                return 0;
        }
        else
        {
            if (!eval_expression(interp, expr->e_cond.vfalse))
                return 0;
        }
        break;
    case OP_OR:
        if (!eval_expression(interp, expr->e_binop.lhs))
            return 0;
        if (coerce_bool(interp, &interp->result))
        {
            if (!set_result_number(interp, TRUE))
                return 0;
        }
        else
        {
            if (!eval_expression(interp, expr->e_binop.rhs))
                return 0;
            if (!set_result_number(interp,
                    coerce_bool(interp, &interp->result) ? TRUE : FALSE))
                return 0;
        }
        break; 
    case OP_AND:
        if (!eval_expression(interp, expr->e_binop.lhs))
            return 0;
        if (!coerce_bool(interp, &interp->result))
        {
            if (!set_result_number(interp, FALSE))
                return 0;
        }
        else
        {
            if (!eval_expression(interp, expr->e_binop.rhs))
                return 0;
            if (!set_result_number(interp,
                    coerce_bool(interp, &interp->result) ? TRUE : FALSE))
                return 0;
        }
        break; 
    case OP_MATCH:
    case OP_NOT_MATCH:
        if (!do_match(interp, expr->e_binop.lhs, expr->e_binop.rhs))
            return 0;
        if (expr->op == OP_NOT_MATCH)
            interp->result.v_number.value = interp->result.v_number.value == TRUE ? FALSE : TRUE;
        break;
    case OP_CONST_REGEXP:
        if (!do_match(interp, NULL, expr))
            return 0;
        break;
    case OP_LT:
    case OP_GT:
    case OP_LTE:
    case OP_GTE:
    case OP_EQ:
    case OP_NEQ:
        if (!eval_expression(interp, expr->e_binop.lhs))
            return 0;
        move_var(&tmp, &interp->result);
        if (!eval_expression(interp, expr->e_binop.rhs))
            return 0;
        t1 = compare_value(&tmp, &interp->result);
        if ((expr->op == OP_LT && t1 < 0) ||
            (expr->op == OP_GT && t1 > 0) ||
            (expr->op == OP_LTE && t1 <= 0) ||
            (expr->op == OP_GTE && t1 >= 0) ||
            (expr->op == OP_EQ && t1 == 0) ||
            (expr->op == OP_NEQ && t1 != 0))
        {
            if (!set_result_number(interp, TRUE))
                return 0;
        }
        else
        {
            if (!set_result_number(interp, FALSE))
                return 0;
        }
        free_var(&tmp);
        break;
    case OP_ADD:
    case OP_ASSIGN_ADD:
    case OP_SUB:
    case OP_ASSIGN_SUB:
    case OP_MUL:
    case OP_ASSIGN_MUL:
    case OP_DIV:
    case OP_ASSIGN_DIV:
    case OP_MOD:
    case OP_ASSIGN_MOD:
        if (!eval_expression(interp, expr->e_binop.lhs))
            return 0;
        t1 = coerce_number(interp, &interp->result);
        if (!eval_expression(interp, expr->e_binop.rhs))
            return 0;
        t2 = coerce_number(interp, &interp->result);
        if (expr->op == OP_ADD || expr->op == OP_ASSIGN_ADD)
            t1 = t1 + t2;
        else if (expr->op == OP_SUB || expr->op == OP_ASSIGN_SUB)
            t1 = t1 - t2;
        else if (expr->op == OP_MUL || expr->op == OP_ASSIGN_MUL)
            t1 = t1 * t2;
        else if (expr->op == OP_DIV || expr->op == OP_ASSIGN_DIV)
        {
            if (t2 == 0)
                return 0;
            t1 = t1 / t2;
        }
        else if (expr->op == OP_MOD || expr->op == OP_ASSIGN_MOD)
        {
            if (t2 == 0)
                return 0;
            t1 = t1 % t2;
        }
        if (!set_result_number(interp, t1))
            return 0;

        if (expr->op == OP_ASSIGN_ADD ||
            expr->op == OP_ASSIGN_SUB ||
            expr->op == OP_ASSIGN_MUL ||
            expr->op == OP_ASSIGN_DIV ||
            expr->op == OP_ASSIGN_MOD)
        {
            if (!assign_result(interp, expr->e_binop.lhs))
                return 0;
        }
        break;
    case OP_INC_PRE:
    case OP_DEC_PRE:
    case OP_INC_POST:
    case OP_DEC_POST:
        if (!eval_expression(interp, expr->e_unop.expr))
            return 0;
        move_var(&tmp, &interp->result);
        t1 = coerce_number(interp, &tmp);
        if (expr->op == OP_INC_PRE || expr->op == OP_INC_POST)
            t2 = t1 + 1;
        else
            t2 = t1 - 1;
        if (!set_result_number(interp, t2))
            return 0;
        if (!assign_result(interp, expr->e_unop.expr))
            return 0;

        if (expr->op == OP_INC_POST || expr->op == OP_DEC_POST)
            move_var(&interp->result, &tmp);
        else
            free_var(&tmp);
        break;
    case OP_NEGATE:
    case OP_NOT:
        if (!eval_expression(interp, expr->e_unop.expr))
            return 0;
        t1 = coerce_number(interp, &interp->result);
        if (expr->op == OP_NEGATE)
            t2 = -t1;
        else
            t2 = coerce_bool(interp, &interp->result) == TRUE ? FALSE : TRUE;
        if (!set_result_number(interp, t2))
            return 0;
        break;
    case OP_CONCAT:
        if (!do_concat(interp, expr->e_binop.lhs, expr->e_binop.rhs))
            return 0;
        break;
    default:
        return 0;
    }

    return 1;
}

static int do_print(interp_t *interp, stmt_t *stmt)
{
    int result;
    unsigned int cnt, i;
    var_t *args, fmt;
    expr_t *e;
    if (stmt->s_print.fmt == NULL)
    {
        for (e = stmt->s_print.expr; e != NULL; e = e->next)
        {
            if (!eval_expression(interp, e))
                return 0;

            if (interp->result.type == VAR_STRING)
                fdprintf(STDOUT, "%s", interp->result.v_string.value);
            else if (interp->result.type == VAR_NUMBER)
                fdprintf(STDOUT, "%d", interp->result.v_number.value);
            else if (interp->result.type != VAR_NULL)
                return 0;

            if (e->next != NULL)
                fdprintf(STDOUT, "%s", get_string(interp, "OFS"));
        }

        if (stmt->s_print.expr == NULL)
        {
#ifdef PATCHED
            if (get_field(interp, 0) == NULL)
                return 0;
            else
#endif
            fdprintf(STDOUT, "%s", get_field(interp, 0));
        }

        fdprintf(STDOUT, "%s", get_string(interp, "ORS"));
        return 1;
    }
    
    if (!eval_expression(interp, stmt->s_print.fmt))
        return 0;
    
    if (interp->result.type == VAR_NUMBER)
    {
        fdprintf(STDOUT, "%d", interp->result.v_number.value);
        return 1;
    }
    else if (interp->result.type != VAR_STRING)
    {
        return 1;
    }

    result = 0;

    move_var(&fmt, &interp->result);
    for (cnt = 0, e = stmt->s_print.expr; e != NULL; e = e->next)
        cnt++;
    args = calloc(sizeof(var_t), cnt);
    if (args == NULL)
        goto done;
    for (i = 0, e = stmt->s_print.expr; e != NULL; e = e->next, i++)
    {
        if (!eval_expression(interp, e))
            goto done;

        move_var(&args[i], &interp->result);
    }
    if (eprintf(STDOUT, fmt.v_string.value, args, cnt) < 0)
        goto done;
    result = 1;

done:
    if (args != NULL)
    {
        for (i = 0; i < cnt; i++)
            free_var(&args[i]);
    }
    free_var(&fmt);
    return result;
}

static int eval_statements(interp_t *interp, stmt_t *stmt)
{
    for (; stmt != NULL; stmt = stmt->next)
    {
        int result;

        switch (stmt->type)
        {
        case STMT_IF:
            if (!eval_expression(interp, stmt->s_if.cond))
                return EVAL_ERROR;
            if (coerce_bool(interp, &interp->result))
            {
                result = eval_statements(interp, stmt->s_if.child);
                if (result != EVAL_FINISHED)
                    return result;
            }
            break;
        case STMT_WHILE:
            if (!stmt->s_while.post)
            {
                if (!eval_expression(interp, stmt->s_while.cond))
                    return EVAL_ERROR;
                if (!coerce_bool(interp, &interp->result))
                    break;
            }
            do {
                result = eval_statements(interp, stmt->s_while.child);
                if (result == EVAL_BREAK)
                    break;
                if (result != EVAL_CONTINUE && result != EVAL_FINISHED)
                    return result;                
                if (!eval_expression(interp, stmt->s_while.cond))
                    return EVAL_ERROR;
            } while (coerce_bool(interp, &interp->result));
            break;
        case STMT_FOR:
            if (!eval_expression(interp, stmt->s_for.init))
                return EVAL_ERROR;
            if (!eval_expression(interp, stmt->s_for.cond))
                return EVAL_ERROR;
            while (coerce_bool(interp, &interp->result))
            {
                result = eval_statements(interp, stmt->s_for.child);
                if (result == EVAL_BREAK)
                    break;
                if (result != EVAL_CONTINUE && result != EVAL_FINISHED)
                    return result;
                if (!eval_expression(interp, stmt->s_for.post))
                    return EVAL_ERROR;
                if (!eval_expression(interp, stmt->s_for.cond))
                    return EVAL_ERROR;
            }
            break;
        case STMT_CONTINUE:
            return EVAL_CONTINUE;
        case STMT_BREAK:
            return EVAL_BREAK;
        case STMT_NEXT:
            return EVAL_NEXT;
        case STMT_EXIT:
            return EVAL_EXIT;
        case STMT_PRINT:
            if (!do_print(interp, stmt))
                return EVAL_ERROR;
            break;
        case STMT_EXPR:
            if (!eval_expression(interp, stmt->s_expr.expr))
                return EVAL_ERROR;
            break;
        }
    }
    return EVAL_FINISHED;
}

int program_run(program_t *prog, io_t *io)
{
    int result = EVAL_ERROR;
    interp_t interp;
    memset(&interp, 0, sizeof(interp_t));

    interp.io = io;
    interp.prog = prog;
    
    if (!dict_init(&interp.vars, free_var))
        return 0;

    if ((interp.buf = malloc(BUF_SIZE)) == NULL)
        goto done;

    if (!dict_add(&interp.vars, "RS", new_string(strdup("\n"))))
        goto done;

    if (!dict_add(&interp.vars, "ORS", new_string(strdup("\n"))))
        goto done;

    if (!dict_add(&interp.vars, "FS", new_string(strdup(" "))))
        goto done;

    if (!dict_add(&interp.vars, "OFS", new_string(strdup(" "))))
        goto done;

    while (1)
    {
        pattern_t *p;

        result = EVAL_FINISHED;
        if (!read_record(&interp))
            break;

#define DO_EVAL() do { \
            result = eval_statements(&interp, p->stmt); \
            if (result == EVAL_NEXT) \
                goto next; \
            else if (result != EVAL_FINISHED) \
                goto done; \
        } while (0)

        // apply BEGIN patterns
        for (p = interp.prog->patterns; p != NULL; p = p->next)
        {
            if (p->pattern == PATTERN_BEGIN)
                DO_EVAL();
        }

        // apply normal patterns
        for (p = interp.prog->patterns; p != NULL; p = p->next)
        {
            if (p->pattern == PATTERN_INVALID || p->pattern == PATTERN_BEGIN || p->pattern == PATTERN_END)
                continue;

            if (p->pattern == PATTERN_EMPTY)
            {
                DO_EVAL();
            }
            else
            {
                if (!eval_expression(&interp, (expr_t*)p->pattern))
                    goto done;
                if (coerce_bool(&interp, &interp.result))
                    DO_EVAL();
            }
        }

next:
        // apply END patterns
        for (p = interp.prog->patterns; p != NULL; p = p->next)
        {
            if (p->pattern == PATTERN_END)
                DO_EVAL();
        }

        free_fields(&interp);
    }

done:
    free_fields(&interp);
    free(interp.buf);
    dict_free(&interp.vars);
    return result != EVAL_ERROR;
}
