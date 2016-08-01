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

#include "libc.h"
#include "list.h"
#include "rpnval.h"
#include "rpncalc.h"

static void
swap(rpnval *a, rpnval *b)
{
    rpnval tmp = *a;
    *a = *b;
    *b = tmp;
}

static int
generic_add(rpnval a, rpnval b, rpnval *res)
{
    int na, nb;
    struct matrix *ma, *mb, *mres;
    double da, db;

    unsigned int i, j;

    if (res == NULL)
        return -1;

    // Addition is commutative
    if (get_type(b) < get_type(a))
        swap(&a, &b);

    switch (get_type(a))
    {
    case INTEGER:
        if (as_integer(a, &na) != 0)
            return -1;

        switch (get_type(b)) {
        case INTEGER:
            if (as_integer(b, &nb) != 0)
                return -1;

            // Integer overflow here is OK for our purposes
            set_integer(na + nb, res);
            break;
        case MATRIX:
            if (as_matrix(b, &mb) != 0)
                return -1;

            if ((mres = malloc(SIZEOF_MATRIX(mb))) == NULL)
                return -1;

            mres->width = mb->width;
            mres->height = mb->height;

            for (i = 0; i < mb->width; i++)
                for (j = 0; j < mb->height; j++) {
#ifdef PATCHED
                    mres->data[j * mres->width + i] = na + mb->data[j * mb->width + i];

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        free(mres);
                        return -1;
                    }
#else
                    if (generic_add(a, mb->data[j * mb->width + i],
                                &mres->data[j * mres->width + i]) != 0) {
                        free(mres);
                        return -1;
                    }
#endif
                }

            set_matrix(mres, res);
            break;
        case DOUBLE:
            if (as_double(b, &db) != 0)
                return -1;

            set_double(na + db, res);
            if (IS_NAN(*res))
                return -1;

            break;
        default:
            return -1;
        }
        break;
    case MATRIX:
        if (as_matrix(a, &ma) != 0)
            return -1;

        switch (get_type(b)) {
        case MATRIX:
            if (as_matrix(b, &mb) != 0)
                return -1;

            if (ma->width != mb->width || ma->height != mb->height)
                return -1;

            if ((mres = malloc(SIZEOF_MATRIX(ma))) == NULL)
                return -1;

            mres->width = ma->width;
            mres->height = ma->height;

            for (i = 0; i < ma->width; i++)
                for (j = 0; j < ma->height; j++) {
                    mres->data[j * mres->width + i] = ma->data[j * ma->width + i] +
                        mb->data[j * mb->width + i];

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        free(mres);
                        return -1;
                    }
                }

            set_matrix(mres, res);
            break;
        case DOUBLE:
            if (as_double(b, &db) != 0)
                return -1;

            if ((mres = malloc(SIZEOF_MATRIX(ma))) == NULL)
                return -1;

            mres->width = ma->width;
            mres->height = ma->height;

            for (i = 0; i < ma->width; i++)
                for (j = 0; j < ma->height; j++) {
                    mres->data[j * mres->width + i] = ma->data[j * ma->width + i] + db;

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        free(mres);
                        return -1;
                    }
                }

            set_matrix(mres, res);
            break;
        default:
            return -1;
        }
        break;
    case DOUBLE:
        if (as_double(a, &da) != 0)
            return -1;

        if (as_double(b, &db) != 0)
            return -1;

        set_double(da + db, res);
        if (IS_NAN(*res))
            return -1;

        break;
    default:
        return -1;
    }

    return 0;
}

static int
generic_sub(rpnval a, rpnval b, rpnval *res)
{
    int nb, ret = 0;
    struct matrix *mb, *mnegb;
    double db;
    rpnval negb;

    unsigned int i, j;
    
    if (res == NULL)
        return -1;

    // res = a - b is equivalent to res = a + (-b)
    switch (get_type(b)) {
    case INTEGER:
        if (as_integer(b, &nb) != 0)
            return -1;

        set_integer(-nb, &negb);
        ret = generic_add(a, negb, res);
        break;
    case MATRIX:
        if (as_matrix(b, &mb) != 0)
            return -1;

        if ((mnegb = malloc(SIZEOF_MATRIX(mb))) == NULL)
            return -1;

        mnegb->width = mb->width;
        mnegb->height = mb->height;

        for (i = 0; i < mb->width; i++)
            for (j = 0; j < mb->height; j++)
                mnegb->data[j * mnegb->width + i] = -mb->data[j * mb->width + i];

        set_matrix(mnegb, &negb);
        ret = generic_add(a, negb, res);
        free(mnegb);
        break;
    case DOUBLE:
        if (as_double(b, &db) != 0)
            return -1;

        set_double(-db, &negb);
        ret = generic_add(a, negb, res);
        break;
    default:
        return -1;
    }

    return ret;
}

static int
generic_mul(rpnval a, rpnval b, rpnval *res)
{
    int na, nb;
    struct matrix *ma, *mb, *mres;
    double da, db;

    unsigned int i, j, k;
#ifndef PATCHED
    long long nres;
#endif

    if (res == NULL)
        return -1;

    // Multiplication is commutative except for two matrices, but in that case
    // get_type(a) == get_type(b)
    if (get_type(b) < get_type(a))
        swap(&a, &b);

    switch (get_type(a))
    {
    case INTEGER:
        if (as_integer(a, &na) != 0)
            return -1;

        switch (get_type(b)) {
        case INTEGER:
            if (as_integer(b, &nb) != 0)
                return -1;

            // Integer overflow here is OK for our purposes
            set_integer(na * nb, res);
            break;
        case MATRIX:
            if (as_matrix(b, &mb) != 0)
                return -1;

            if ((mres = malloc(SIZEOF_MATRIX(mb))) == NULL)
                return -1;

            mres->width = mb->width;
            mres->height = mb->height;

            for (i = 0; i < mb->width; i++)
                for (j = 0; j < mb->height; j++) {
#ifdef PATCHED
                    mres->data[j * mres->width + i] = na * mb->data[j * mb->width + i];

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        free(mres);
                        return -1;
                    }
#else
                    // Future support for integer matrices, can't push these yet... ;)
                    if (get_type(mb->data[j * mb->width + i]) == INTEGER) {
                        if (as_integer(mb->data[j * mb->width + i], &nb) != 0) {
                            free(mres);
                            return -1;
                        }

                        // This overflow check is legit right
                        nres = (long long)na * nb;
                        if (nres < 0)
                            nres = nres & 0xffffffff;

                        *((unsigned long long *)&mres->data[j * mres->width + i]) =
                            NAN_MASK | (unsigned long long)INTEGER << 32 | nres;
                    } else if (get_type(mb->data[j * mb->width + i]) == DOUBLE) {
                        if (as_double(mb->data[j * mb->width + i], &db) != 0) {
                            free(mres);
                            return -1;
                        }

                        mres->data[j * mres->width + i] = na * db;
                        if (IS_NAN(mres->data[j * mres->width + i])) {
                            free(mres);
                            return -1;
                        }
                    }
#endif
                }

            set_matrix(mres, res);
            break;
        case DOUBLE:
            if (as_double(b, &db) != 0)
                return -1;

            set_double(na * db, res);
            if (IS_NAN(*res))
                return -1;

            break;
        default:
            return -1;
        }
        break;
    case MATRIX:
        if (as_matrix(a, &ma) != 0)
            return -1;

        switch (get_type(b)) {
        case MATRIX:
            if (as_matrix(b, &mb) != 0)
                return -1;

            if (ma->width != mb->height)
                return -1;

            // If ma is a n x m matrix and mb is a m x p matrix, mres is a n x p
            // matrix
            if ((mres = malloc(sizeof(struct matrix) +
                            mb->width * ma->height * sizeof(double))) == NULL)
                return -1;

            mres->width = mb->width;
            mres->height = ma->height;

            for (i = 0; i < mres->width * mres->height; i++)
                mres->data[i] = 0.0;

            // Naive algorithm here, for simplicity
            for (i = 0; i < mres->height; i++)
                for (j = 0; j < mres->width; j++)
                    for (k = 0; k < ma->width; k++) {
                        mres->data[i * mres->width + j] += ma->data[i * ma->width + k] *
                            mb->data[k * mb->width + j];

#ifdef PATCHED
                        if (IS_NAN(mres->data[i * mres->width + j])) {
#else
                        if (IS_NAN(mres->data[j * mres->width + i])) {
#endif
                            free(mres);
                            return -1;
                        }
                    }

            set_matrix(mres, res);
            break;
        case DOUBLE:
            if (as_double(b, &db) != 0)
                return -1;

            if ((mres = malloc(SIZEOF_MATRIX(ma))) == NULL)
                return -1;

            mres->width = ma->width;
            mres->height = ma->height;

            for (i = 0; i < ma->width; i++)
                for (j = 0; j < ma->height; j++) {
                    mres->data[j * mres->width + i] = ma->data[j * ma->width + i] * db;

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        free(mres);
                        return -1;
                    }
                }


            set_matrix(mres, res);
            break;
        default:
            return -1;
        }
        break;
    case DOUBLE:
        if (as_double(a, &da) != 0)
            return -1;

        if (as_double(b, &db) != 0)
            return -1;

        set_double(da * db, res);
        if (IS_NAN(*res))
            return -1;

        break;
    default:
        return -1;
    }

    return 0;
}

static int
generic_div(rpnval a, rpnval b, rpnval *res)
{
    int na, nb;
    struct matrix *ma, *mb, *mres;
    double da, db;

    unsigned int i, j;

    if (res == NULL)
        return -1;

    // Matrix division isn't a thing
    if (get_type(a) == MATRIX && get_type(b) == MATRIX)
        return -1;

    // Only case where we get an integer value
    if (get_type(a) == INTEGER && get_type(b) == INTEGER) {
        if (as_integer(a, &na) != 0)
            return -1;

        if (as_integer(b, &nb) != 0)
            return -1;

        if (nb == 0)
            return -1;

        set_integer(na / nb, res);
        return 0;
    }

    switch (get_type(a)) {
    case INTEGER:
        if (as_integer(a, &na) != 0)
            return -1;

        if (get_type(b) == MATRIX) {
            if (as_matrix(b, &mb) != 0)
                return -1;

            if ((mres = malloc(SIZEOF_MATRIX(mb))) == NULL)
                    return -1;

            mres->width = mb->width;
            mres->height = mb->height;

            for (i = 0; i < mb->width; i++)
                for (j = 0; j < mb->height; j++) {
                    if (mb->data[j * mb->width + i] == 0.0) {
                        free(mres);
                        return -1;
                    }

                    mres->data[j * mres->width + i] = na / mb->data[j * mb->width + i];

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        free(mres);
                        return -1;
                    }
                }

            set_matrix(mres, res);
        } else {
            if (as_double(b, &db) != 0)
                return -1;

            if (db == 0.0)
                return -1;
    
            set_double(na / db, res);
            if (IS_NAN(*res))
                return -1;
        }

        break;
    case MATRIX:
        if (as_matrix(a, &ma) != 0)
            return -1;

        if (get_type(b) == INTEGER) {
            if (as_integer(b, &nb) != 0)
                return -1;

            db = nb;
        } else {
            if (as_double(b, &db) != 0)
                return -1;
        }

        if ((mres = malloc(SIZEOF_MATRIX(ma))) == NULL)
                return -1;

        mres->width = ma->width;
        mres->height = ma->height;

        for (i = 0; i < ma->width; i++)
            for (j = 0; j < ma->height; j++) {
                if (db == 0.0) {
                    free(mres);
                    return -1;
                }

                mres->data[j * mres->width + i] = ma->data[j * ma->width + i] / db;

                if (IS_NAN(mres->data[j * mres->width + i])) {
                    free(mres);
                    return -1;
                }
            }

        set_matrix(mres, res);
        break;
    case DOUBLE:
        if (as_double(a, &da) != 0)
            return -1;

        if (get_type(b) == MATRIX) {
            if (as_matrix(b, &mb) != 0)
                return -1;

            if ((mres = malloc(SIZEOF_MATRIX(mb))) == NULL)
                    return -1;

            mres->width = mb->width;
            mres->height = mb->height;

            for (i = 0; i < mb->width; i++)
                for (j = 0; j < mb->height; j++) {
                    if (mb->data[j * mb->width + i] == 0.0) {
                        free(mres);
                        return -1;
                    }

                    mres->data[j * mres->width + i] = da / mb->data[j * mb->width + i];

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        free(mres);
                        return -1;
                    }
                }

            set_matrix(mres, res);
        } else {
            if (get_type(b) == INTEGER) {
                if (as_integer(b, &nb) != 0)
                    return -1;

                db = nb;
            } else {
                if (as_double(b, &db) != 0)
                    return -1;
            }

            if (db == 0.0)
                return -1;

            set_double(da / db, res);
            if (IS_NAN(*res))
                return -1;
        }

        break;
    default:
        return -1;
    }

    return 0;
}

static int
matrix_inv(struct matrix *mat, struct matrix **res)
{
    double det, *d = mat->data;
#ifdef PATCHED
    unsigned int i;
#endif

    if (res == NULL)
        return -1;

    // Only support specific cases, for simplicity
    if (mat->width != mat->height || mat->width > 2)
        return -1;

    if (mat->width == 1)
        det = d[0];
    else if (mat->width == 2)
        det = d[0] * d[3] - d[1] * d[2];
    else
        return -1;

    if (IS_NAN(det))
        return -1;

#ifdef PATCHED
    if (det == 0.0)
        return -1;
#endif

    if ((*res = malloc(SIZEOF_MATRIX(mat))) == NULL)
        return -1;

    (*res)->width = mat->width;
    (*res)->height = mat->height;

    if ((*res)->width == 1)
        (*res)->data[0] = 1.0 / det;
    else if ((*res)->width == 2) {
        (*res)->data[0] = d[3] / det;
        (*res)->data[1] = -d[1] / det;
        (*res)->data[2] = -d[2] / det;
        (*res)->data[3] = d[0] / det;
    }

#ifdef PATCHED
    for (i = 0; i < (*res)->width * (*res)->height; i++)
        if (IS_NAN((*res)->data[i])) {
            free(*res);
            return -1;
        }
#endif
            
    return 0;
}

// push reads directly from stdin
static int
push(struct rpncalc_state *state)
{
    struct operand *op = NULL;
    unsigned int type;

    int n;
    double d;

    unsigned int i, width, height;
    size_t size;
    struct matrix *m = NULL;

    if ((op = malloc(sizeof(struct operand))) == NULL)
        return -1;

    if (read_all(STDIN, &type, sizeof(type)) != sizeof(type))
        goto free_op;

    switch (type & 0xffff) {
    case INTEGER:
        if (read_all(STDIN, &n, sizeof(n)) != sizeof(n))
            goto free_op;

        set_integer(n, &op->val);
        break;
    case MATRIX:
        width = (type & (0xff << 24)) >> 24;
        height = (type & (0xff << 16)) >> 16;
        // width < 256 and height < 256, so no overflow
        size = width * height * sizeof(double);

        if (width == 0 || height == 0)
            goto free_op;

        if ((m = malloc(sizeof(struct matrix) + size)) == NULL)
            goto free_op;

        m->width = width;
        m->height = height;

        if (read_all(STDIN, m->data, size) != size)
            goto free_m;

        // Check to make sure we didn't read in any NaNs
        for (i = 0; i < size / sizeof(double); i++)
            if (IS_NAN(m->data[i]))
                goto free_m;

        set_matrix(m, &op->val);
        break;
    case DOUBLE:
        if (read_all(STDIN, &d, sizeof(d)) != sizeof(d))
            goto free_op;

        if (IS_NAN(d))
            goto free_op;

        set_double(d, &op->val);
        break;
    default:
        goto free_op;
    }

    list_push_entry_front(struct operand, list, &state->stack, op);
    return 0;

free_m:
    free(m);

free_op:
    free(op);
    return -1;
}

// pop writes directly to stdout
static int
pop(struct rpncalc_state *state)
{
    int ret = -1;
    struct operand *op;
    enum rpnval_type type;

    int n;
    double d;

    unsigned int width, height;
    size_t size;
    struct matrix *m = NULL;

    op = list_pop_entry_front(struct operand, list, &state->stack);
    if (op == NULL)
        return -1;

    type = get_type(op->val);
    switch(type) {
    case INTEGER:
        if (as_integer(op->val, &n) != 0)
            goto free_op;

        if (write_all(STDOUT, &type, sizeof(type)) != sizeof(type))
            goto free_op;

        if (write_all(STDOUT, &n, sizeof(n)) != sizeof(n))
            goto free_op;

        break;
    case MATRIX:
        if (as_matrix(op->val, &m) != 0)
            goto free_op;

        width = m->width & 0xff;
        height = m->height & 0xff;
        size = width * height * sizeof(double);

        type = width << 24 | height << 16 | MATRIX;
        if (write_all(STDOUT, &type, sizeof(type)) != sizeof(type))
            goto free_m;

        if (write_all(STDOUT, m->data, size) != size)
            goto free_m;

        break;
    case DOUBLE:
        if (as_double(op->val, &d) != 0)
            goto free_op;

        if (write_all(STDOUT, &type, sizeof(type)) != sizeof(type))
            goto free_op;

        if (write_all(STDOUT, &d, sizeof(d)) != sizeof(d))
            goto free_op;

        break;
    default:
        goto free_op;
    }

    ret = 0;

free_m:
    free(m);

free_op:
    free(op);
    return ret;
}

static int
clear(struct rpncalc_state *state)
{
    struct operand *cur, *n;
    struct matrix *m;

    list_for_each_entry_safe(struct operand, list, &state->stack, n, cur) {
        list_remove_entry(struct operand, list, &state->stack, cur);
        
        if (get_type(cur->val) == MATRIX && as_matrix(cur->val, &m) == 0)
            free(m);
            
        free(cur);
    }
    
    return 0;
}

static int
binary_op(struct rpncalc_state *state, int (*op)(rpnval, rpnval, rpnval *))
{
    struct operand *a = NULL, *b = NULL, *res = NULL;
    struct matrix *ma, *mb;

    if (list_length(&state->stack) < 2)
        return -1;

    if ((b = list_pop_entry_front(struct operand, list, &state->stack)) == NULL)
        return -1;

    if ((a = list_pop_entry_front(struct operand, list, &state->stack)) == NULL)
        goto restore_stack;

    if ((res = malloc(sizeof(struct operand))) == NULL)
        goto restore_stack;

    if (op(a->val, b->val, &res->val) != 0)
        goto restore_stack;

    list_push_entry_front(struct operand, list, &state->stack, res);

    if (get_type(a->val) == MATRIX && as_matrix(a->val, &ma) == 0)
        free(ma);
    free(a);

    if (get_type(b->val) == MATRIX && as_matrix(b->val, &mb) == 0)
        free(mb);
    free(b);

    return 0;

restore_stack:
    if (a != NULL)
        list_push_entry_front(struct operand, list, &state->stack, a);

    if (b != NULL)
        list_push_entry_front(struct operand, list, &state->stack, b);

    free(res);
    return -1;
}

static int
add(struct rpncalc_state *state)
{
    return binary_op(state, generic_add);
}

static int
sub(struct rpncalc_state *state)
{
    return binary_op(state, generic_sub);
}

static int
mul(struct rpncalc_state *state)
{
    return binary_op(state, generic_mul);
}

static int
div(struct rpncalc_state *state)
{
    return binary_op(state, generic_div);
}

static int
inv(struct rpncalc_state *state)
{
    struct operand *a = NULL, *res = NULL;
    struct matrix *ma, *mres;

    if (list_length(&state->stack) < 1)
        return -1;

    if ((a = list_pop_entry_front(struct operand, list, &state->stack)) == NULL)
        return -1;

    if (get_type(a->val) != MATRIX || as_matrix(a->val, &ma) != 0)
        goto restore_stack;

    if ((res = malloc(sizeof(struct operand))) == NULL)
        goto restore_stack;

    if (matrix_inv(ma, &mres) != 0)
        goto restore_stack;

    set_matrix(mres, &res->val);

    list_push_entry_front(struct operand, list, &state->stack, res);

    free(ma);
    free(a);
    return 0;

restore_stack:
    if (a != NULL)
        list_push_entry_front(struct operand, list, &state->stack, a);

    free(res);
    return -1;
}

void
rpncalc_init(struct rpncalc_state *state)
{
    list_init(&state->stack);
}

void
rpncalc_destroy(struct rpncalc_state *state)
{
    clear(state);
}

static int (*rpncalc_ops[])(struct rpncalc_state *) = {
    push, pop, clear, add, sub, mul, div, inv
};

int
perform_rpncalc_op(struct rpncalc_state *state, enum rpncalc_op_type type)
{
    unsigned int index = (unsigned int)type;

    if (index >= sizeof(rpncalc_ops) / sizeof(rpncalc_ops[0]))
        return -1;

    return rpncalc_ops[index](state);
}

