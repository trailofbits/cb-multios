#include "stack.h"

#ifndef ACCELFUNC_H_
#define ACCELFUNC_H_

typedef double (*handle_op_t)(stack_t **args, int *is_bad_formula);

typedef struct {
    const char *name;
    handle_op_t function;
} operator_t;

double handle_op_avg(stack_t **args, int *is_bad_formula);
double handle_op_count(stack_t **args, int *is_bad_formula);
double handle_op_max(stack_t **args, int *is_bad_formula);
double handle_op_median(stack_t **args, int *is_bad_formula);
double handle_op_min(stack_t **args, int *is_bad_formula);
double handle_op_stddev(stack_t **args, int *is_bad_formula);
double handle_op_abs(stack_t **args, int *is_bad_formula);
double handle_op_add(stack_t **args, int *is_bad_formula);
double handle_op_cos(stack_t **args, int *is_bad_formula);
double handle_op_ln(stack_t **args, int *is_bad_formula);
double handle_op_log10(stack_t **args, int *is_bad_formula);
double handle_op_power(stack_t **args, int *is_bad_formula);
double handle_op_product(stack_t **args, int *is_bad_formula);
double handle_op_quotient(stack_t **args, int *is_bad_formula);
double handle_op_sin(stack_t **args, int *is_bad_formula);
double handle_op_sqrt(stack_t **args, int *is_bad_formula);
double handle_op_subtract(stack_t **args, int *is_bad_formula);
double handle_op_sum(stack_t **args, int *is_bad_formula);

#endif /* ACCELFUNC_H */
