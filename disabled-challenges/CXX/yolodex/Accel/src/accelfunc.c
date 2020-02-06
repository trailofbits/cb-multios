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
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_accelfunc.h"
#include "cgc_convert.h"

double cgc_handle_op_avg(stack_t **args, int *is_bad_formula)
{
    cgc_size_t i = 0;
    if (*args == NULL)
        goto error;

    double result = 0.0, operand;
    char *front = cgc_pop_copy(args);
    while(front != NULL) {
        operand = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
        cgc_free(front);
        if(*is_bad_formula)
            goto error;

        result += operand;
        front = cgc_pop_copy(args);
        i++;
    }

    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    if (i == 0) {
        i = 1;
        goto error;
    }
    return result / (double) i;
}

double cgc_handle_op_count(stack_t **args, int *is_bad_formula)
{
    cgc_size_t i = 0;
    if (*args == NULL)
        goto error;

    double result = 0.0, operand;
    char *front = cgc_pop_copy(args);
    while(front != NULL) {
        operand = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
        cgc_free(front);
        if(*is_bad_formula)
            goto error;

        front = cgc_pop_copy(args);
        i++;
    }

    result = i;
    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    if (i == 0) {
        i = 1;
        goto error;
    }
    return result;
}

double cgc_handle_op_max(stack_t **args, int *is_bad_formula)
{
    cgc_size_t i = 0;
    double max = 0.0;
    if (*args == NULL)
        goto error;

    double operand;
    char *front = cgc_pop_copy(args);
    if (front != NULL) {
        max = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
        cgc_free(front);
        if (*is_bad_formula)
            goto error;
        i++;
    }

    front = cgc_pop_copy(args);
    while(front != NULL) {
        operand = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
        cgc_free(front);
        if(*is_bad_formula)
            goto error;

        if (operand > max)
            max = operand;

        front = cgc_pop_copy(args);
        i++;
    }

    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
    max = 0.0;
done:
    if (i == 0) {
        i = 1;
        goto error;
    }
	return max;
}

double cgc_handle_op_median(stack_t **args, int *is_bad_formula)
{
    cgc_size_t i = 0;
    stack_t *sorted, *tmp, *prev;
#ifdef PATCHED
    sorted = NULL;
#endif
    if (*args == NULL)
        goto error;
    sorted = NULL;

    double median = 0.0, operand, temp;
    char *front = cgc_pop_copy(args);

    operand = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    if(*is_bad_formula) {
        cgc_free(front);
        goto error;
    } else {
        cgc_push(&sorted, front);
        i++;
    }

    front = cgc_pop_copy(args);
    while(front != NULL) {
        operand = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
        if(*is_bad_formula)
            goto error;

        //using stack as linked list
        tmp = sorted;
        int passed_first = 0, is_inserted = 0;
        stack_t *elem = NULL;
        while (tmp != NULL) {
            temp = cgc_atof(tmp->data, cgc_strlen(tmp->data) + 1, is_bad_formula);
            if (operand <= temp) {
                if (!passed_first) {
                    cgc_push(&sorted, front);
                } else {
                    elem = cgc_malloc(sizeof(stack_t));
                    elem->data = front;
                    elem->next = tmp;
                    prev->next = elem;
                }
                is_inserted = 1;
                break;
            } else {
                prev = tmp;
                tmp = tmp->next;
                passed_first++;
            }
        }
        if (!is_inserted) {
            tmp = sorted;
            while (tmp->next != NULL)
                tmp = tmp->next;

            elem = cgc_malloc(sizeof(stack_t));
            elem->data = front;
            elem->next = NULL;
            tmp->next = elem;
        }

        front = cgc_pop_copy(args);
        i++;
    }

    tmp = sorted;
    int j = 0;
    if (i % 2 == 0) {
        for(j = 0; j < (i / 2) - 1; j++)
            tmp = tmp->next;

        median += cgc_atof(tmp->data, cgc_strlen(tmp->data) + 1, is_bad_formula);
        tmp = tmp->next;
        median += cgc_atof(tmp->data, cgc_strlen(tmp->data) + 1, is_bad_formula);

        median /= 2;
    } else {
        for(j = 0; j < (i / 2); j++)
            tmp = tmp->next;

        median += cgc_atof(tmp->data, cgc_strlen(tmp->data) + 1, is_bad_formula);
    }

    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
    median = 0.0;
done:
    if (i == 0) {
        i = 1;
        goto error;
    }
    cgc_clear_stack(&sorted);
	return median;
}

double cgc_handle_op_min(stack_t **args, int *is_bad_formula)
{
    cgc_size_t i = 0;
    double min = 0.0;
    if (*args == NULL)
        goto error;

    double operand;
    char *front = cgc_pop_copy(args);
    if (front != NULL) {
        min = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
        cgc_free(front);
        if (*is_bad_formula)
            goto error;
        i++;
    }

    front = cgc_pop_copy(args);
    while(front != NULL) {
        operand = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
        cgc_free(front);
        if(*is_bad_formula)
            goto error;

        if (operand < min)
            min = operand;

        front = cgc_pop_copy(args);
        i++;
    }

    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
    min = 0.0;
done:
    if (i == 0) {
        i = 1;
        goto error;
    }
	return min;
}

double cgc_handle_op_stddev(stack_t **args, int *is_bad_formula)
{
    cgc_size_t i = 0;
    if (*args == NULL)
        goto error;

    double result = 0.0, operand, mean = 0.0;
    stack_t *tmp = *args;

    while (tmp != NULL) {
        operand = cgc_atof(tmp->data, cgc_strlen(tmp->data) + 1, is_bad_formula);
        if(*is_bad_formula)
            goto error;

        mean += operand;
        i++;
        tmp = tmp->next;
    }
    if (i == 0)
        goto done;
    mean /= i;

    i = 0;
    char *front = cgc_pop_copy(args);
    while(front != NULL) {
        operand = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
        cgc_free(front);

        //TODO - Look into this, I don't know why pow is failing
        //result += (cgc_pow((operand - mean), 2.0));
        result += ((operand - mean) * (operand - mean));
        front = cgc_pop_copy(args);
        i++;
    }

    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    if (i == 0) {
        i = 1;
        goto error;
    }
    return cgc_sqrt(result / (double) i);
}

double cgc_handle_op_abs(stack_t **args, int *is_bad_formula)
{
    if (*args == NULL)
        goto error;

    double result = 0.0, operand1;
    char *front;

    // Get first operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand1 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    if (*args != NULL)
        goto error;     // Too many arguments

    result = cgc_fabs(operand1);
    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    return result;
}

double cgc_handle_op_add(stack_t **args, int *is_bad_formula)
{
    if (*args == NULL)
        goto error;

    double result = 0.0, operand1, operand2;
    char *front;

    // Get first operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand1 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    // Get second operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand2 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    if (*args != NULL)
        goto error;     // Too many arguments

    result = operand1 + operand2;
    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    return result;
}

double cgc_handle_op_cos(stack_t **args, int *is_bad_formula)
{
    if (*args == NULL)
        goto error;

    double result = 0.0, operand1;
    char *front;

    // Get first operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand1 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    if (*args != NULL)
        goto error;     // Too many arguments

    result = cgc_cos(operand1);
    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    return result;
}

double cgc_handle_op_ln(stack_t **args, int *is_bad_formula)
{
    if (*args == NULL)
        goto error;

    double result = 0.0, operand1;
    char *front;

    // Get first operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand1 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    if (*args != NULL)
        goto error;     // Too many arguments

    if (operand1 == 0)
        goto error;

    result = cgc_log(operand1);
    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    return result;
}

double cgc_handle_op_log10(stack_t **args, int *is_bad_formula)
{
    if (*args == NULL)
        goto error;

    double result = 0.0, operand1;
    char *front;

    // Get first operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand1 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    if (*args != NULL)
        goto error;     // Too many arguments

    if (operand1 == 0)
        goto error;

    result = cgc_log10(operand1);
    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    return result;
}

double cgc_handle_op_power(stack_t **args, int *is_bad_formula)
{
    if (*args == NULL)
        goto error;

    double result = 0.0, operand1, operand2;
    char *front;

    // Get first operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand1 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    // Get second operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand2 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    if (*args != NULL)
        goto error;     // Too many arguments

    if (operand2 == 0.0)
        result = 1.0;
    else if (operand2 == 1.0)
        result = operand1;
    else if (isnan(operand2))
        result = operand2;
    else if (operand1 == 0 && operand2 > 0)
        result = 0.0;
    else if (operand1 < 0 && cgc_remainder(operand2, 1) == 0.0)
        result = cgc_pow(-operand1, operand2) * (cgc_remainder(operand2, 2) == 0 ? 1 : -1);
    else
        result = cgc_pow(operand1, operand2);
    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    return result;
}

double cgc_handle_op_product(stack_t **args, int *is_bad_formula)
{
    if (*args == NULL)
        goto error;

    double result = 0.0, operand1, operand2;
    char *front;

    // Get first operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand1 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    // Get second operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand2 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    if (*args != NULL)
        goto error;     // Too many arguments

    result = operand1 * operand2;
    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    return result;
}

double cgc_handle_op_quotient(stack_t **args, int *is_bad_formula)
{
    if (*args == NULL)
        goto error;

    double result = 0.0, operand1, operand2;
    char *front;

    // Get first operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand1 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    // Get second operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand2 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    if (*args != NULL)
        goto error;     // Too many arguments

    if (operand2 == 0)
        goto error;

    result = operand1 / operand2;
    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    return result;
}

double cgc_handle_op_sin(stack_t **args, int *is_bad_formula)
{
    if (*args == NULL)
        goto error;

    double result = 0.0, operand1;
    char *front;

    // Get first operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand1 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    if (*args != NULL)
        goto error;     // Too many arguments

    result = cgc_sin(operand1);
    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    return result;
}

double cgc_handle_op_sqrt(stack_t **args, int *is_bad_formula)
{
    if (*args == NULL)
        goto error;

    double result = 0.0, operand1;
    char *front;

    // Get first operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand1 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    if (*args != NULL)
        goto error;     // Too many arguments

    if (operand1 < 0)
        goto error;

    result = cgc_sqrt(operand1);
    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    return result;
}

double cgc_handle_op_subtract(stack_t **args, int *is_bad_formula)
{
    if (*args == NULL)
        goto error;

    double result = 0.0, operand1, operand2;
    char *front;

    // Get first operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand1 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    // Get second operand
    front = cgc_pop_copy(args);
    if (front == NULL)
        goto error;
    operand2 = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
    cgc_free(front);
    if(*is_bad_formula)
        goto error;

    if (*args != NULL)
        goto error;     // Too many arguments

    result = operand1 - operand2;
    goto done;

error:
    cgc_clear_stack(args);
    *is_bad_formula = 1;
	result = 0.0;
done:
    return result;
}

double cgc_handle_op_sum(stack_t **args, int *is_bad_formula)
{
    if (*args == NULL)
        goto error;

    double result = 0.0, operand;
    char *front = cgc_pop_copy(args);
    while(front != NULL) {
        operand = cgc_atof(front, cgc_strlen(front) + 1, is_bad_formula);
        cgc_free(front);
        if(*is_bad_formula)
            goto error;

        result += operand;
        front = cgc_pop_copy(args);
    }

    goto done;

error:
    *is_bad_formula = 1;
	result = 0.0;
done:
    return result;
}
