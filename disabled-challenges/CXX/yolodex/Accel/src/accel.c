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

#include "cgc_accel.h"
#include "cgc_accelio.h"
#include "cgc_accelfunc.h"

#include "cgc_stack.h"
#include "cgc_queue.h"

#include "cgc_convert.h"

#define LINE_SIZE 512
#define TMP_STR_SIZE 512
#define MAX_ROWS 26 * 27
#define MAX_COLS 100

typedef enum { UNUSED, BAD_CELL, STRING, QUOTED_STRING, DOUBLE, FUNCTION, CELL_ID, FORMULA } cell_type_e;
typedef struct cell {
    unsigned int id;
    cell_type_e cell_type;
    char *str;
    char *formula;
} cell_t;

static operator_t *cgc_get_op(char *name);
static cell_type_e cgc_parsearg(char *arg);
static int cgc_is_arg_arithmetic(char *arg);
static cell_t *cgc_get_cell(char *cell_id);
static queue_t *cgc_infixtorpn(char *infix, cgc_size_t size);
static double cgc_eval_formula(char *formula, int *is_bad_formula, stack_t **cir_ref, int id);

static cell_t *_g_sheet = NULL;
static cell_t **g_sheet = NULL;

static operator_t operators[] =
{
    { "AVG", cgc_handle_op_avg },
    { "COUNT", cgc_handle_op_count },
    { "MAX", cgc_handle_op_max },
    { "MEDIAN", cgc_handle_op_median },
    { "MIN", cgc_handle_op_min },
    { "STDDEV", cgc_handle_op_stddev },
    { "ABS", cgc_handle_op_abs },
    { "+", cgc_handle_op_add },
    { "COS", cgc_handle_op_cos },
    { "LN", cgc_handle_op_ln },
    { "LOG10", cgc_handle_op_log10 },
    { "POWER", cgc_handle_op_power },
    { "*", cgc_handle_op_product },
    { "/", cgc_handle_op_quotient },
    { "SIN", cgc_handle_op_sin },
    { "SQRT", cgc_handle_op_sqrt },
    { "-", cgc_handle_op_subtract },
    { "SUM", cgc_handle_op_sum },
    { NULL, NULL}
};

int cgc_init_sheet()
{
    cgc_size_t i, j;
    unsigned int id = 0;
    // LARGEST SHEET SIZE: ZZ99 (676 rows by 100 columns)

    _g_sheet = cgc_calloc(MAX_ROWS * MAX_COLS, sizeof(cell_t));
    if (_g_sheet == NULL)
        return -1;

    g_sheet = cgc_malloc(MAX_ROWS * sizeof(cell_t*));
    if (g_sheet == NULL)
        return -1;

    for (i = 0; i < MAX_ROWS; i++)
        g_sheet[i] = &_g_sheet[i * MAX_COLS];

    for (i = 0; i < MAX_ROWS; i++)
        for (j = 0; j < MAX_COLS; j++)
            g_sheet[i][j].id = id++;

    return 0;
}

char *cgc_show_cell(char *cell_id, int is_repr, char* val_str, cgc_size_t size)
{
    int is_bad_formula;
    double val = 0.0;
    cell_t *cell = cgc_get_cell(cell_id);

    if (cell == NULL)
        return NULL;

    if (cell->cell_type == UNUSED)
        return "";
    if (cell->cell_type == BAD_CELL)
        return "!VALUE";

    if (is_repr)
        return cell->str;

    if (cell->formula != NULL) {
        stack_t *cir_ref = NULL;
        val = cgc_eval_formula(cell->formula, &is_bad_formula, &cir_ref, cell->id);
        if (is_bad_formula) {
            return "!FORMULA: CIRREF/STR/DIV0";
        }

        cgc_ftoa(val, val_str, size);
        return val_str;
    } else {
        return cell->str;
    }
}


int cgc_set_cell(char *cell_id, char *cell_str, cgc_size_t size)
{
    if (cell_str == NULL || cgc_strlen(cell_str) == 0 || cgc_strlen(cell_str) >= size)
        return -1;

    cell_t *cell = cgc_get_cell(cell_id);
    if (cell == NULL)
        return -1;

    if (cell->cell_type != UNUSED) {
        cgc_free(cell->str);
        cell->str = NULL;
        cell->cell_type = UNUSED;
        cell->formula = NULL;
    }

    cell->str = cgc_malloc(cgc_strlen(cell_str) + 1);
    if(cell->str == NULL)
        return -1;

    cgc_strcpy(cell->str, cell_str);
    if (cgc_strlen(cell_str) >= 2 && cell_str[0] == '=') {
        cell->formula = &cell->str[1];
        cell->cell_type = FORMULA;
    } else {
        // Non functions can only be a double or a string
        cell->cell_type = cgc_parsearg(cell->str);
        if (cell->cell_type != DOUBLE)
            cell->cell_type = STRING;
    }

    return 0;
}

int cgc_clear_cell(char *cell_id)
{

    cell_t *cell = cgc_get_cell(cell_id);

    if (cell == NULL)
        return -1;

    if (cell->cell_type != UNUSED) {
        cgc_free(cell->str);
        cell->str = NULL;
        cell->cell_type = UNUSED;
        cell->formula = NULL;
    }

    return 0;
}

void cgc_print_assigned_cells()
{
    char row_id[3];
    char col_id[4];
    cgc_size_t i, j;
    unsigned int id;
    cell_t *cell;
    for (i = 0; i < MAX_ROWS; i++) {
        for (j = 0; j < MAX_COLS; j++) {
            cell = &g_sheet[i][j];
            if (cell->cell_type != UNUSED) {
                id = cell->id;
                cgc_itoa(id % 100, col_id, sizeof(col_id));
                row_id[2] = '\0';
                row_id[1] = (id / (100 * 26)) == 0 ? '\0' : ((id / 100) % 26) + 'A';
                row_id[0] = (id / (100 * 26)) == 0 ? ((id / 100) % 26) + 'A' : (((id / (100 * 26)) - 1) % 26) + 'A';
                cgc_printf("%s%s=%s\n", row_id, col_id, cell->str);
            }
        }
    }
}

static operator_t *cgc_get_op(char *name)
{
    if(name == NULL)
        return NULL;

    char *upper_name = (char *) cgc_malloc(cgc_strlen(name) + 1);
    cgc_strcpy(upper_name, name);
    cgc_size_t i, len = cgc_strlen(upper_name);
    for (i = 0; i < len; i++)
        upper_name[i] = cgc_toupper(upper_name[i]);

    operator_t *op = NULL;
    for (op = &operators[0]; op->name != NULL; op++) {
        if (cgc_strcmp(op->name, upper_name) == 0)
            break;
    }

    cgc_free(upper_name);
    if (op->name == NULL)
        return NULL;
    else
        return op;
}

static cell_type_e cgc_parsearg(char *arg)
{
    if (arg == NULL)
        return BAD_CELL;

    int is_double = 0, has_period = 0, has_negative = 0;
    int is_hard_string = 0, is_soft_string = 0;
    char *beg_arg = arg;

    while (*arg != '\0') {
        if (*arg >= '0' && *arg <= '9') {
            is_double++;
        } else if (*arg == '-') {
            is_double++;
            has_negative++;
        } else if (*arg == '.') {
            is_double++;
            has_period++;
        } else if (*arg == '"') {
            is_hard_string++;
        } else {
            is_soft_string++;
        }
        arg++;
    }
    arg = beg_arg;

    if (is_hard_string) {
        if (is_hard_string == 2 && *(--arg) == '"')
            return QUOTED_STRING;
        else
            return STRING;
    } else if (is_soft_string) {
        if (has_period > 1 || has_negative > 1)
            return STRING;

        if (cgc_valid_cell_id(arg) == 0)
            return CELL_ID;

        if (cgc_get_op(arg) != NULL)
            return FUNCTION;

        return STRING;
    } else if (is_double) {
        if (has_period > 1 || has_negative > 1)
            return STRING;

        if ((has_period && is_double == 1) || (has_period && has_negative && is_double == 2))
            return STRING;

        if (has_negative && is_double == 1)
            return FUNCTION;

        return DOUBLE;
    } else {
        return BAD_CELL;
    }
}

static int cgc_is_arg_arithmetic(char *arg)
{
    return ((cgc_memcmp(arg, "+", 2) == 0) ||
            (cgc_memcmp(arg, "-", 2) == 0) ||
            (cgc_memcmp(arg, "/", 2) == 0) ||
            (cgc_memcmp(arg, "*", 2) == 0));
}

static cell_t *cgc_get_cell(char *cell_id)
{
    char row_str[3];
    char col_str[3];
    int row_idx = 0, col_idx = 0;
    int i, len;

    if (cgc_get_rowcol(cell_id, row_str, col_str, '\0') == -1)
        return NULL;

    len = cgc_strlen(row_str);
    for (i = 0; i < len; i++)
        row_idx += ((row_str[i] - 64) * cgc_pow(26, len - i - 1));

    --row_idx;
    col_idx = cgc_strtol(col_str, NULL, 10);
    return &g_sheet[row_idx][col_idx];

}

static int cgc_eval_function(operator_t *op, stack_t **values, char *val_str, cgc_size_t size)
{
    if (op == NULL || val_str == NULL || size <= 2)
        return -1;

    double val = 0.0;
    char *arg;
    char *op_name = (char *) op->name;
    cgc_size_t i, num_args = 0;
    int is_bad_formula = 0;
    operator_t *nested_op;

    stack_t *args = NULL;
    if (cgc_is_arg_arithmetic(op_name)) {
        num_args = 2;
    } else {
        char *arg_count = cgc_pop_copy(values);
        if (arg_count == NULL)
            goto error;

        num_args = cgc_strtol(arg_count, NULL, 10);
        cgc_free(arg_count);
    }

    for (i = 0; i < num_args; i++) {
        arg = cgc_pop_copy(values);
        //cgc_printf("arg[%d]==%s\n", i, arg);
        if (cgc_parsearg(arg) == FUNCTION) {
            nested_op = cgc_get_op(arg);
            cgc_free(arg);
            if (cgc_eval_function(nested_op, values, val_str, size) == 0)
                cgc_push_copy(&args, val_str, size);
            else
                goto error;

        } else if (cgc_push(&args, arg) != 0) {
            goto error;
        }
    }

    val = op->function(&args, &is_bad_formula);
    if (is_bad_formula)
        goto error;

    if (cgc_ftoa(val, val_str, size) == NULL)
        goto error;

    return 0;

error:
    cgc_clear_stack(&args);
    return -1;
}

static double cgc_eval_formula(char *formula, int *is_bad_formula, stack_t **cir_ref, int id)
{
    char val_str[TMP_STR_SIZE];
    char tmp_id_str[TMP_STR_SIZE];
    cgc_size_t size = TMP_STR_SIZE;
    double val = 0.0;
    double result = 0.0;
    *is_bad_formula = 0;
    cell_type_e cell_type;
    char *arg;

    if(cgc_itoa(id, tmp_id_str, size) == NULL)
        goto error;

    cgc_push_copy(cir_ref, tmp_id_str, cgc_strlen(tmp_id_str) + 1);
    queue_t *rpn = cgc_infixtorpn(formula, cgc_strlen(formula) + 1);

    queue_t *args = NULL;
    stack_t *values = NULL;

    stack_t *tmp = NULL;
    operator_t *op = NULL;

    while (rpn != NULL) {
        arg = cgc_dequeue_copy(&rpn);
        cell_type = cgc_parsearg(arg);
        switch(cell_type) {
            case DOUBLE:
                cgc_push(&values, arg);
                break;
            case FUNCTION:
                op = cgc_get_op(arg);
                if (cgc_eval_function(op, &values, val_str, size) == -1) {
                    goto error;
                }

                cgc_push_copy(&values, val_str, size);
                break;
            case CELL_ID:
                tmp = *cir_ref;
                cell_t *cell = cgc_get_cell(arg);
                if(cell == NULL)
                    goto error;

                while (tmp != NULL) {
                    if(cgc_itoa(cell->id, tmp_id_str, size) == NULL)
                        goto error;

                    if (cgc_memcmp(tmp->data, tmp_id_str, cgc_strlen(tmp->data) + 1) == 0)
                        goto error; //Circular reference
                    tmp = tmp->next;
                }

                if (cell->cell_type == UNUSED) {
                    cgc_push_copy(&values, "0", sizeof("0"));
                } else if (cell->cell_type == DOUBLE) {
                    cgc_push_copy(&values, cell->str, cgc_strlen(cell->str) + 1);
                } else if(cell->cell_type == FORMULA) {
                    val = cgc_eval_formula(cell->formula, is_bad_formula, cir_ref, cell->id);
                    if(*is_bad_formula)
                        goto error;

                    cgc_ftoa(val, val_str, size);
                    cgc_push_copy(&values, val_str, size);
                } else {
                    goto error;
                }

                break;
            default:
                goto error;
        }
    }

    char *result_str = cgc_pop_copy(&values);
    if (values != NULL)
        goto error;

    result = cgc_atof(result_str, size, is_bad_formula);
    if (*is_bad_formula)
        goto error;

    goto cleanup;

error:
    *is_bad_formula = 1;
    val = 0.0;
    cgc_clear_queue(&rpn);
    cgc_clear_queue(&args);
    cgc_clear_stack(&values);
cleanup:
    cgc_free(cgc_pop_copy(cir_ref));

    return result;
}

static queue_t *cgc_infixtorpn(char *infix, cgc_size_t size)
{
    /* Use RPN */
    int is_mismatched = 0;
    int func_size = 16;
    int func_idx = -1;
    char *formula = cgc_malloc(size);
    int *func_args = cgc_malloc(func_size * sizeof(int));

    char *delims = "():,+-*/";
    char *arg, *iter;
    char delim;
    char arith_op[2] = {'\0', '\0'};
    char *value;
    cell_type_e arg_type;
    stack_t *operators = NULL;
    queue_t *output_q = NULL;

    cgc_memcpy(formula, infix, size);
    if (cgc_sanitize_formula(formula, size) != 0)
        goto cleanup;

    arg = iter = formula;
    cgc_size_t i = 0;
    char prev_char = 0;
    while ( i++ < size) {
        if (cgc_strchr(delims, *iter) == NULL && *iter != '\0') {
            prev_char = *iter;
            iter++;
            continue;
        } else if (cgc_strchr(delims, *iter) != NULL) {
            if (*iter == '-') {
                if(i <= 1 || (prev_char != ')' && (prev_char < '0' || prev_char > '9'))) {
                    prev_char = *iter;
                    iter++;
                    continue;
                }
            }
        }

        prev_char = *iter;
        delim = *iter;
        *iter = '\0';
        arg_type = cgc_parsearg(arg);
        switch (arg_type) {
            case DOUBLE:
            case CELL_ID:
                cgc_enqueue_copy(&output_q, arg, cgc_strlen(arg) + 1);
                break;
            case FUNCTION:
#ifdef PATCHED
                if(func_idx == func_size-1) {
#else
                if(func_idx == func_size) {
#endif
                    func_size *= 2;
                    int *temp = cgc_realloc(func_args, func_size * sizeof(int));
                    if (temp == NULL)
                        goto error;
                    func_args = temp;
                }

                func_args[++func_idx] = 0;
                cgc_push_copy(&operators, arg, cgc_strlen(arg) + 1);
                break;
            case BAD_CELL:
                break;
            default:
                goto error;
        }

        is_mismatched = 0;
        switch(delim) {
            case '(':
                cgc_push_copy(&operators, "(", cgc_strlen("(") + 1);
                break;
            case ')':
                is_mismatched = 1;
                while (operators != NULL) {
                    if (cgc_strcmp(cgc_peek_top(operators), "(") == 0) {
                        value = cgc_pop_copy(&operators);
                        cgc_free(value);
                        is_mismatched = 0;
                        break;
                    } else {
                        cgc_enqueue(&output_q, cgc_pop_copy(&operators));
                    }
                }

                // handle parens without any operator
                if (cgc_peek_top(operators) == NULL || func_idx < 0)
                    break;

                char num_args_str[16];
                if(cgc_strchr(delims, cgc_peek_top(operators)[0]) != NULL) {
                    break;
                } else if (cgc_parsearg(cgc_peek_top(operators)) == FUNCTION) {
                    cgc_enqueue_copy(&output_q, cgc_itoa(func_args[func_idx--] + 1, num_args_str,
                                    sizeof(num_args_str)), sizeof(num_args_str));
                    cgc_enqueue(&output_q, cgc_pop_copy(&operators));
                }

                break;
            case ',':
                is_mismatched = 1;
                while (operators != NULL) {
                    if (cgc_strcmp(cgc_peek_top(operators), "(") == 0) {
                        if (func_idx >= 0)
                            func_args[func_idx]++;
                        is_mismatched = 0;
                        break;
                    } else {
                        cgc_enqueue(&output_q, cgc_pop_copy(&operators));
                    }
                }
                break;
            case '+':
            case '-':
                //TODO - FIXME - precedence is broken
                //TODO - FIXME - negative is still broken
                // 4/5-5
                arith_op[0] = delim;
                while (operators != NULL) {
                    if (cgc_strcmp(cgc_peek_top(operators), "-") == 0 || cgc_strcmp(cgc_peek_top(operators), "+") == 0 ||
                        cgc_strcmp(cgc_peek_top(operators), "+") == 0 || cgc_strcmp(cgc_peek_top(operators), "/") == 0)
                        cgc_enqueue(&output_q, cgc_pop_copy(&operators));
                    else
                        break;
                }

                cgc_push_copy(&operators, arith_op, cgc_strlen(arith_op)+1);
                break;
            case '*':
            case '/':
                //TODO - FIXME - precedence is broken
                arith_op[0] = delim;
                while (operators != NULL) {
                    if (cgc_strcmp(cgc_peek_top(operators), "/") == 0 || cgc_strcmp(cgc_peek_top(operators), "*") == 0)
                        cgc_enqueue(&output_q, cgc_pop_copy(&operators));
                    else
                        break;

                }

                cgc_push_copy(&operators, arith_op, cgc_strlen(arith_op)+1);
                break;

            case '\0':
                goto finish;
            default:
                goto error;
        }

        if (is_mismatched)
            goto error;

        arg = ++iter;
    }
finish:

    while (operators != NULL) {
        if (cgc_strcmp(cgc_peek_top(operators), "(") == 0 || cgc_strcmp(cgc_peek_top(operators), ")") == 0)
            goto error;

        cgc_enqueue(&output_q, cgc_pop_copy(&operators));
    }

    goto cleanup;

error:
    cgc_clear_queue(&output_q);
    cgc_clear_stack(&operators);

cleanup:
    cgc_free(formula);
    cgc_free(func_args);
    return output_q;
}
