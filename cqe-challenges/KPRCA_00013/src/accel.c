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

#include "accel.h"
#include "accelio.h"
#include "accelfunc.h"

#include "stack.h"
#include "queue.h"

#include "convert.h"

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

static operator_t *get_op(char *name);
static cell_type_e parsearg(char *arg);
static int is_arg_arithmetic(char *arg);
static cell_t *get_cell(char *cell_id);
static queue_t *infixtorpn(char *infix, size_t size);
static double eval_formula(char *formula, int *is_bad_formula, stack_t **cir_ref, int id);

static cell_t *_g_sheet = NULL;
static cell_t **g_sheet = NULL;

static operator_t operators[] =
{
    { "AVG", handle_op_avg },
    { "COUNT", handle_op_count },
    { "MAX", handle_op_max },
    { "MEDIAN", handle_op_median },
    { "MIN", handle_op_min },
    { "STDDEV", handle_op_stddev },
    { "ABS", handle_op_abs },
    { "+", handle_op_add },
    { "COS", handle_op_cos },
    { "LN", handle_op_ln },
    { "LOG10", handle_op_log10 },
    { "POWER", handle_op_power },
    { "*", handle_op_product },
    { "/", handle_op_quotient },
    { "SIN", handle_op_sin },
    { "SQRT", handle_op_sqrt },
    { "-", handle_op_subtract },
    { "SUM", handle_op_sum },
    { NULL, NULL}
};

int init_sheet()
{
    size_t i, j;
    unsigned int id = 0;
    // LARGEST SHEET SIZE: ZZ99 (676 rows by 100 columns)

    _g_sheet = calloc(MAX_ROWS * MAX_COLS, sizeof(cell_t));
    if (_g_sheet == NULL)
        return -1;

    g_sheet = malloc(MAX_ROWS * sizeof(cell_t*));
    if (g_sheet == NULL)
        return -1;

    for (i = 0; i < MAX_ROWS; i++)
        g_sheet[i] = &_g_sheet[i * MAX_COLS];

    for (i = 0; i < MAX_ROWS; i++)
        for (j = 0; j < MAX_COLS; j++)
            g_sheet[i][j].id = id++;

    return 0;
}

char *show_cell(char *cell_id, int is_repr, char* val_str, size_t size)
{
    int is_bad_formula;
    double val = 0.0;
    cell_t *cell = get_cell(cell_id);

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
        val = eval_formula(cell->formula, &is_bad_formula, &cir_ref, cell->id);
        if (is_bad_formula) {
            return "!FORMULA: CIRREF/STR/DIV0";
        }

        ftoa(val, val_str, size);
        return val_str;
    } else {
        return cell->str;
    }
}


int set_cell(char *cell_id, char *cell_str, size_t size)
{
    if (cell_str == NULL || strlen(cell_str) == 0 || strlen(cell_str) >= size)
        return -1;

    cell_t *cell = get_cell(cell_id);
    if (cell == NULL)
        return -1;

    if (cell->cell_type != UNUSED) {
        free(cell->str);
        cell->str = NULL;
        cell->cell_type = UNUSED;
        cell->formula = NULL;
    }

    cell->str = malloc(strlen(cell_str) + 1);
    if(cell->str == NULL)
        return -1;

    strcpy(cell->str, cell_str);
    if (strlen(cell_str) >= 2 && cell_str[0] == '=') {
        cell->formula = &cell->str[1];
        cell->cell_type = FORMULA;
    } else {
        // Non functions can only be a double or a string
        cell->cell_type = parsearg(cell->str);
        if (cell->cell_type != DOUBLE)
            cell->cell_type = STRING;
    }

    return 0;
}

int clear_cell(char *cell_id)
{

    cell_t *cell = get_cell(cell_id);

    if (cell == NULL)
        return -1;

    if (cell->cell_type != UNUSED) {
        free(cell->str);
        cell->str = NULL;
        cell->cell_type = UNUSED;
        cell->formula = NULL;
    }

    return 0;
}

void print_assigned_cells()
{
    char row_id[3];
    char col_id[4];
    size_t i, j;
    unsigned int id;
    cell_t *cell;
    for (i = 0; i < MAX_ROWS; i++) {
        for (j = 0; j < MAX_COLS; j++) {
            cell = &g_sheet[i][j];
            if (cell->cell_type != UNUSED) {
                id = cell->id;
                itoa(id % 100, col_id, sizeof(col_id));
                row_id[2] = '\0';
                row_id[1] = (id / (100 * 26)) == 0 ? '\0' : ((id / 100) % 26) + 'A';
                row_id[0] = (id / (100 * 26)) == 0 ? ((id / 100) % 26) + 'A' : (((id / (100 * 26)) - 1) % 26) + 'A';
                printf("%s%s=%s\n", row_id, col_id, cell->str);
            }
        }
    }
}

static operator_t *get_op(char *name)
{
    if(name == NULL)
        return NULL;

    char *upper_name = (char *) malloc(strlen(name) + 1);
    strcpy(upper_name, name);
    size_t i, len = strlen(upper_name);
    for (i = 0; i < len; i++)
        upper_name[i] = toupper(upper_name[i]);

    operator_t *op = NULL;
    for (op = &operators[0]; op->name != NULL; op++) {
        if (strcmp(op->name, upper_name) == 0)
            break;
    }

    free(upper_name);
    if (op->name == NULL)
        return NULL;
    else
        return op;
}

static cell_type_e parsearg(char *arg)
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

        if (valid_cell_id(arg) == 0)
            return CELL_ID;

        if (get_op(arg) != NULL)
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

static int is_arg_arithmetic(char *arg)
{
    return ((memcmp(arg, "+", 2) == 0) ||
            (memcmp(arg, "-", 2) == 0) ||
            (memcmp(arg, "/", 2) == 0) ||
            (memcmp(arg, "*", 2) == 0));
}

static cell_t *get_cell(char *cell_id)
{
    char row_str[3];
    char col_str[3];
    int row_idx = 0, col_idx = 0;
    int i, len;

    if (get_rowcol(cell_id, row_str, col_str, '\0') == -1)
        return NULL;

    len = strlen(row_str);
    for (i = 0; i < len; i++)
        row_idx += ((row_str[i] - 64) * pow(26, len - i - 1));

    --row_idx;
    col_idx = strtol(col_str, NULL, 10);
    return &g_sheet[row_idx][col_idx];

}

static int eval_function(operator_t *op, stack_t **values, char *val_str, size_t size)
{
    if (op == NULL || val_str == NULL || size <= 2)
        return -1;

    double val = 0.0;
    char *arg;
    char *op_name = (char *) op->name;
    size_t i, num_args = 0;
    int is_bad_formula = 0;
    operator_t *nested_op;

    stack_t *args = NULL;
    if (is_arg_arithmetic(op_name)) {
        num_args = 2;
    } else {
        char *arg_count = pop_copy(values);
        if (arg_count == NULL)
            goto error;

        num_args = strtol(arg_count, NULL, 10);
        free(arg_count);
    }

    for (i = 0; i < num_args; i++) {
        arg = pop_copy(values);
        //printf("arg[%d]==%s\n", i, arg);
        if (parsearg(arg) == FUNCTION) {
            nested_op = get_op(arg);
            free(arg);
            if (eval_function(nested_op, values, val_str, size) == 0)
                push_copy(&args, val_str, size);
            else
                goto error;

        } else if (push(&args, arg) != 0) {
            goto error;
        }
    }

    val = op->function(&args, &is_bad_formula);
    if (is_bad_formula)
        goto error;

    if (ftoa(val, val_str, size) == NULL)
        goto error;

    return 0;

error:
    clear_stack(&args);
    return -1;
}

static double eval_formula(char *formula, int *is_bad_formula, stack_t **cir_ref, int id)
{
    char val_str[TMP_STR_SIZE];
    char tmp_id_str[TMP_STR_SIZE];
    size_t size = TMP_STR_SIZE;
    double val = 0.0;
    double result = 0.0;
    *is_bad_formula = 0;
    cell_type_e cell_type;
    char *arg;

    if(itoa(id, tmp_id_str, size) == NULL)
        goto error;

    push_copy(cir_ref, tmp_id_str, strlen(tmp_id_str) + 1);
    queue_t *rpn = infixtorpn(formula, strlen(formula) + 1);

    queue_t *args = NULL;
    stack_t *values = NULL;

    stack_t *tmp = NULL;
    operator_t *op = NULL;

    while (rpn != NULL) {
        arg = dequeue_copy(&rpn);
        cell_type = parsearg(arg);
        switch(cell_type) {
            case DOUBLE:
                push(&values, arg);
                break;
            case FUNCTION:
                op = get_op(arg);
                if (eval_function(op, &values, val_str, size) == -1) {
                    goto error;
                }

                push_copy(&values, val_str, size);
                break;
            case CELL_ID:
                tmp = *cir_ref;
                cell_t *cell = get_cell(arg);
                if(cell == NULL)
                    goto error;

                while (tmp != NULL) {
                    if(itoa(cell->id, tmp_id_str, size) == NULL)
                        goto error;

                    if (memcmp(tmp->data, tmp_id_str, strlen(tmp->data) + 1) == 0)
                        goto error; //Circular reference
                    tmp = tmp->next;
                }

                if (cell->cell_type == UNUSED) {
                    push_copy(&values, "0", sizeof("0"));
                } else if (cell->cell_type == DOUBLE) {
                    push_copy(&values, cell->str, strlen(cell->str) + 1);
                } else if(cell->cell_type == FORMULA) {
                    val = eval_formula(cell->formula, is_bad_formula, cir_ref, cell->id);
                    if(*is_bad_formula)
                        goto error;

                    ftoa(val, val_str, size);
                    push_copy(&values, val_str, size);
                } else {
                    goto error;
                }

                break;
            default:
                goto error;
        }
    }

    char *result_str = pop_copy(&values);
    if (values != NULL)
        goto error;

    result = atof(result_str, size, is_bad_formula);
    if (*is_bad_formula)
        goto error;

    goto cleanup;

error:
    *is_bad_formula = 1;
    val = 0.0;
    clear_queue(&rpn);
    clear_queue(&args);
    clear_stack(&values);
cleanup:
    free(pop_copy(cir_ref));

    return result;
}

static queue_t *infixtorpn(char *infix, size_t size)
{
    /* Use RPN */
    int is_mismatched = 0;
    int func_size = 16;
    int func_idx = -1;
    char *formula = malloc(size);
    int *func_args = malloc(func_size * sizeof(int));

    char *delims = "():,+-*/";
    char *arg, *iter;
    char delim;
    char arith_op[2] = {'\0', '\0'};
    char *value;
    cell_type_e arg_type;
    stack_t *operators = NULL;
    queue_t *output_q = NULL;

    memcpy(formula, infix, size);
    if (sanitize_formula(formula, size) != 0)
        goto cleanup;

    arg = iter = formula;
    size_t i = 0;
    char prev_char = 0;
    while ( i++ < size) {
        if (strchr(delims, *iter) == NULL && *iter != '\0') {
            prev_char = *iter;
            iter++;
            continue;
        } else if (strchr(delims, *iter) != NULL) {
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
        arg_type = parsearg(arg);
        switch (arg_type) {
            case DOUBLE:
            case CELL_ID:
                enqueue_copy(&output_q, arg, strlen(arg) + 1);
                break;
            case FUNCTION:
#ifdef PATCHED
                if(func_idx == func_size-1) {
#else
                if(func_idx == func_size) {
#endif
                    func_size *= 2;
                    int *temp = realloc(func_args, func_size * sizeof(int));
                    if (temp == NULL)
                        goto error;
                    func_args = temp;
                }

                func_args[++func_idx] = 0;
                push_copy(&operators, arg, strlen(arg) + 1);
                break;
            case BAD_CELL:
                break;
            default:
                goto error;
        }

        is_mismatched = 0;
        switch(delim) {
            case '(':
                push_copy(&operators, "(", strlen("(") + 1);
                break;
            case ')':
                is_mismatched = 1;
                while (operators != NULL) {
                    if (strcmp(peek_top(operators), "(") == 0) {
                        value = pop_copy(&operators);
                        free(value);
                        is_mismatched = 0;
                        break;
                    } else {
                        enqueue(&output_q, pop_copy(&operators));
                    }
                }

                // handle parens without any operator
                if (peek_top(operators) == NULL || func_idx < 0)
                    break;

                char num_args_str[16];
                if(strchr(delims, peek_top(operators)[0]) != NULL) {
                    break;
                } else if (parsearg(peek_top(operators)) == FUNCTION) {
                    enqueue_copy(&output_q, itoa(func_args[func_idx--] + 1, num_args_str,
                                    sizeof(num_args_str)), sizeof(num_args_str));
                    enqueue(&output_q, pop_copy(&operators));
                }

                break;
            case ',':
                is_mismatched = 1;
                while (operators != NULL) {
                    if (strcmp(peek_top(operators), "(") == 0) {
                        if (func_idx >= 0)
                            func_args[func_idx]++;
                        is_mismatched = 0;
                        break;
                    } else {
                        enqueue(&output_q, pop_copy(&operators));
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
                    if (strcmp(peek_top(operators), "-") == 0 || strcmp(peek_top(operators), "+") == 0 ||
                        strcmp(peek_top(operators), "+") == 0 || strcmp(peek_top(operators), "/") == 0)
                        enqueue(&output_q, pop_copy(&operators));
                    else
                        break;
                }

                push_copy(&operators, arith_op, strlen(arith_op)+1);
                break;
            case '*':
            case '/':
                //TODO - FIXME - precedence is broken
                arith_op[0] = delim;
                while (operators != NULL) {
                    if (strcmp(peek_top(operators), "/") == 0 || strcmp(peek_top(operators), "*") == 0)
                        enqueue(&output_q, pop_copy(&operators));
                    else
                        break;

                }

                push_copy(&operators, arith_op, strlen(arith_op)+1);
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
        if (strcmp(peek_top(operators), "(") == 0 || strcmp(peek_top(operators), ")") == 0)
            goto error;

        enqueue(&output_q, pop_copy(&operators));
    }

    goto cleanup;

error:
    clear_queue(&output_q);
    clear_stack(&operators);

cleanup:
    free(formula);
    free(func_args);
    return output_q;
}
