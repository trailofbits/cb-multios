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

#include "cgc_libc.h"
#include "cgc_list.h"
#include "cgc_rpnval.h"
#include "cgc_rpncalc.h"

static void
cgc_swap(rpnval *a, rpnval *b)
{
    rpnval tmp = *a;
    *a = *b;
    *b = tmp;
}

static int
cgc_generic_add(rpnval a, rpnval b, rpnval *res)
{
    int na, nb;
    struct matrix *ma, *mb, *mres;
    double da, db;

    unsigned int i, j;

    if (res == NULL)
        return -1;

    // Addition is commutative
    if (cgc_get_type(b) < cgc_get_type(a))
        cgc_swap(&a, &b);

    switch (cgc_get_type(a))
    {
    case INTEGER:
        if (cgc_as_integer(a, &na) != 0)
            return -1;

        switch (cgc_get_type(b)) {
        case INTEGER:
            if (cgc_as_integer(b, &nb) != 0)
                return -1;

            // Integer overflow here is OK for our purposes
            cgc_set_integer(na + nb, res);
            break;
        case MATRIX:
            if (cgc_as_matrix(b, &mb) != 0)
                return -1;

            if ((mres = cgc_malloc(SIZEOF_MATRIX(mb))) == NULL)
                return -1;

            mres->width = mb->width;
            mres->height = mb->height;

            for (i = 0; i < mb->width; i++)
                for (j = 0; j < mb->height; j++) {
#ifdef PATCHED
                    mres->data[j * mres->width + i] = na + mb->data[j * mb->width + i];

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        cgc_free(mres);
                        return -1;
                    }
#else
                    if (cgc_generic_add(a, mb->data[j * mb->width + i],
                                &mres->data[j * mres->width + i]) != 0) {
                        cgc_free(mres);
                        return -1;
                    }
#endif
                }

            cgc_set_matrix(mres, res);
            break;
        case DOUBLE:
            if (cgc_as_double(b, &db) != 0)
                return -1;

            cgc_set_double(na + db, res);
            if (IS_NAN(*res))
                return -1;

            break;
        default:
            return -1;
        }
        break;
    case MATRIX:
        if (cgc_as_matrix(a, &ma) != 0)
            return -1;

        switch (cgc_get_type(b)) {
        case MATRIX:
            if (cgc_as_matrix(b, &mb) != 0)
                return -1;

            if (ma->width != mb->width || ma->height != mb->height)
                return -1;

            if ((mres = cgc_malloc(SIZEOF_MATRIX(ma))) == NULL)
                return -1;

            mres->width = ma->width;
            mres->height = ma->height;

            for (i = 0; i < ma->width; i++)
                for (j = 0; j < ma->height; j++) {
                    mres->data[j * mres->width + i] = ma->data[j * ma->width + i] +
                        mb->data[j * mb->width + i];

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        cgc_free(mres);
                        return -1;
                    }
                }

            cgc_set_matrix(mres, res);
            break;
        case DOUBLE:
            if (cgc_as_double(b, &db) != 0)
                return -1;

            if ((mres = cgc_malloc(SIZEOF_MATRIX(ma))) == NULL)
                return -1;

            mres->width = ma->width;
            mres->height = ma->height;

            for (i = 0; i < ma->width; i++)
                for (j = 0; j < ma->height; j++) {
                    mres->data[j * mres->width + i] = ma->data[j * ma->width + i] + db;

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        cgc_free(mres);
                        return -1;
                    }
                }

            cgc_set_matrix(mres, res);
            break;
        default:
            return -1;
        }
        break;
    case DOUBLE:
        if (cgc_as_double(a, &da) != 0)
            return -1;

        if (cgc_as_double(b, &db) != 0)
            return -1;

        cgc_set_double(da + db, res);
        if (IS_NAN(*res))
            return -1;

        break;
    default:
        return -1;
    }

    return 0;
}

static int
cgc_generic_sub(rpnval a, rpnval b, rpnval *res)
{
    int nb, ret = 0;
    struct matrix *mb, *mnegb;
    double db;
    rpnval negb;

    unsigned int i, j;
    
    if (res == NULL)
        return -1;

    // res = a - b is equivalent to res = a + (-b)
    switch (cgc_get_type(b)) {
    case INTEGER:
        if (cgc_as_integer(b, &nb) != 0)
            return -1;

        cgc_set_integer(-nb, &negb);
        ret = cgc_generic_add(a, negb, res);
        break;
    case MATRIX:
        if (cgc_as_matrix(b, &mb) != 0)
            return -1;

        if ((mnegb = cgc_malloc(SIZEOF_MATRIX(mb))) == NULL)
            return -1;

        mnegb->width = mb->width;
        mnegb->height = mb->height;

        for (i = 0; i < mb->width; i++)
            for (j = 0; j < mb->height; j++)
                mnegb->data[j * mnegb->width + i] = -mb->data[j * mb->width + i];

        cgc_set_matrix(mnegb, &negb);
        ret = cgc_generic_add(a, negb, res);
        cgc_free(mnegb);
        break;
    case DOUBLE:
        if (cgc_as_double(b, &db) != 0)
            return -1;

        cgc_set_double(-db, &negb);
        ret = cgc_generic_add(a, negb, res);
        break;
    default:
        return -1;
    }

    return ret;
}

static int
cgc_generic_mul(rpnval a, rpnval b, rpnval *res)
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
    if (cgc_get_type(b) < cgc_get_type(a))
        cgc_swap(&a, &b);

    switch (cgc_get_type(a))
    {
    case INTEGER:
        if (cgc_as_integer(a, &na) != 0)
            return -1;

        switch (cgc_get_type(b)) {
        case INTEGER:
            if (cgc_as_integer(b, &nb) != 0)
                return -1;

            // Integer overflow here is OK for our purposes
            cgc_set_integer(na * nb, res);
            break;
        case MATRIX:
            if (cgc_as_matrix(b, &mb) != 0)
                return -1;

            if ((mres = cgc_malloc(SIZEOF_MATRIX(mb))) == NULL)
                return -1;

            mres->width = mb->width;
            mres->height = mb->height;

            for (i = 0; i < mb->width; i++)
                for (j = 0; j < mb->height; j++) {
#ifdef PATCHED
                    mres->data[j * mres->width + i] = na * mb->data[j * mb->width + i];

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        cgc_free(mres);
                        return -1;
                    }
#else
                    // Future support for integer matrices, can't push these yet... ;)
                    if (cgc_get_type(mb->data[j * mb->width + i]) == INTEGER) {
                        if (cgc_as_integer(mb->data[j * mb->width + i], &nb) != 0) {
                            cgc_free(mres);
                            return -1;
                        }

                        // This overflow check is legit right
                        nres = (long long)na * nb;
                        if (nres < 0)
                            nres = nres & 0xffffffff;

                        *((unsigned long long *)&mres->data[j * mres->width + i]) =
                            NAN_MASK | (unsigned long long)INTEGER << 32 | nres;
                    } else if (cgc_get_type(mb->data[j * mb->width + i]) == DOUBLE) {
                        if (cgc_as_double(mb->data[j * mb->width + i], &db) != 0) {
                            cgc_free(mres);
                            return -1;
                        }

                        mres->data[j * mres->width + i] = na * db;
                        if (IS_NAN(mres->data[j * mres->width + i])) {
                            cgc_free(mres);
                            return -1;
                        }
                    }
#endif
                }

            cgc_set_matrix(mres, res);
            break;
        case DOUBLE:
            if (cgc_as_double(b, &db) != 0)
                return -1;

            cgc_set_double(na * db, res);
            if (IS_NAN(*res))
                return -1;

            break;
        default:
            return -1;
        }
        break;
    case MATRIX:
        if (cgc_as_matrix(a, &ma) != 0)
            return -1;

        switch (cgc_get_type(b)) {
        case MATRIX:
            if (cgc_as_matrix(b, &mb) != 0)
                return -1;

            if (ma->width != mb->height)
                return -1;

            // If ma is a n x m matrix and mb is a m x p matrix, mres is a n x p
            // matrix
            if ((mres = cgc_malloc(sizeof(struct matrix) +
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
                            cgc_free(mres);
                            return -1;
                        }
                    }

            cgc_set_matrix(mres, res);
            break;
        case DOUBLE:
            if (cgc_as_double(b, &db) != 0)
                return -1;

            if ((mres = cgc_malloc(SIZEOF_MATRIX(ma))) == NULL)
                return -1;

            mres->width = ma->width;
            mres->height = ma->height;

            for (i = 0; i < ma->width; i++)
                for (j = 0; j < ma->height; j++) {
                    mres->data[j * mres->width + i] = ma->data[j * ma->width + i] * db;

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        cgc_free(mres);
                        return -1;
                    }
                }


            cgc_set_matrix(mres, res);
            break;
        default:
            return -1;
        }
        break;
    case DOUBLE:
        if (cgc_as_double(a, &da) != 0)
            return -1;

        if (cgc_as_double(b, &db) != 0)
            return -1;

        cgc_set_double(da * db, res);
        if (IS_NAN(*res))
            return -1;

        break;
    default:
        return -1;
    }

    return 0;
}

static int
cgc_generic_div(rpnval a, rpnval b, rpnval *res)
{
    int na, nb;
    struct matrix *ma, *mb, *mres;
    double da, db;

    unsigned int i, j;

    if (res == NULL)
        return -1;

    // Matrix division isn't a thing
    if (cgc_get_type(a) == MATRIX && cgc_get_type(b) == MATRIX)
        return -1;

    // Only case where we get an integer value
    if (cgc_get_type(a) == INTEGER && cgc_get_type(b) == INTEGER) {
        if (cgc_as_integer(a, &na) != 0)
            return -1;

        if (cgc_as_integer(b, &nb) != 0)
            return -1;

        if (nb == 0)
            return -1;

        cgc_set_integer(na / nb, res);
        return 0;
    }

    switch (cgc_get_type(a)) {
    case INTEGER:
        if (cgc_as_integer(a, &na) != 0)
            return -1;

        if (cgc_get_type(b) == MATRIX) {
            if (cgc_as_matrix(b, &mb) != 0)
                return -1;

            if ((mres = cgc_malloc(SIZEOF_MATRIX(mb))) == NULL)
                    return -1;

            mres->width = mb->width;
            mres->height = mb->height;

            for (i = 0; i < mb->width; i++)
                for (j = 0; j < mb->height; j++) {
                    if (mb->data[j * mb->width + i] == 0.0) {
                        cgc_free(mres);
                        return -1;
                    }

                    mres->data[j * mres->width + i] = na / mb->data[j * mb->width + i];

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        cgc_free(mres);
                        return -1;
                    }
                }

            cgc_set_matrix(mres, res);
        } else {
            if (cgc_as_double(b, &db) != 0)
                return -1;

            if (db == 0.0)
                return -1;
    
            cgc_set_double(na / db, res);
            if (IS_NAN(*res))
                return -1;
        }

        break;
    case MATRIX:
        if (cgc_as_matrix(a, &ma) != 0)
            return -1;

        if (cgc_get_type(b) == INTEGER) {
            if (cgc_as_integer(b, &nb) != 0)
                return -1;

            db = nb;
        } else {
            if (cgc_as_double(b, &db) != 0)
                return -1;
        }

        if ((mres = cgc_malloc(SIZEOF_MATRIX(ma))) == NULL)
                return -1;

        mres->width = ma->width;
        mres->height = ma->height;

        for (i = 0; i < ma->width; i++)
            for (j = 0; j < ma->height; j++) {
                if (db == 0.0) {
                    cgc_free(mres);
                    return -1;
                }

                mres->data[j * mres->width + i] = ma->data[j * ma->width + i] / db;

                if (IS_NAN(mres->data[j * mres->width + i])) {
                    cgc_free(mres);
                    return -1;
                }
            }

        cgc_set_matrix(mres, res);
        break;
    case DOUBLE:
        if (cgc_as_double(a, &da) != 0)
            return -1;

        if (cgc_get_type(b) == MATRIX) {
            if (cgc_as_matrix(b, &mb) != 0)
                return -1;

            if ((mres = cgc_malloc(SIZEOF_MATRIX(mb))) == NULL)
                    return -1;

            mres->width = mb->width;
            mres->height = mb->height;

            for (i = 0; i < mb->width; i++)
                for (j = 0; j < mb->height; j++) {
                    if (mb->data[j * mb->width + i] == 0.0) {
                        cgc_free(mres);
                        return -1;
                    }

                    mres->data[j * mres->width + i] = da / mb->data[j * mb->width + i];

                    if (IS_NAN(mres->data[j * mres->width + i])) {
                        cgc_free(mres);
                        return -1;
                    }
                }

            cgc_set_matrix(mres, res);
        } else {
            if (cgc_get_type(b) == INTEGER) {
                if (cgc_as_integer(b, &nb) != 0)
                    return -1;

                db = nb;
            } else {
                if (cgc_as_double(b, &db) != 0)
                    return -1;
            }

            if (db == 0.0)
                return -1;

            cgc_set_double(da / db, res);
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
cgc_matrix_inv(struct matrix *mat, struct matrix **res)
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

    if ((*res = cgc_malloc(SIZEOF_MATRIX(mat))) == NULL)
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
            cgc_free(*res);
            return -1;
        }
#endif
            
    return 0;
}

// push reads directly from cgc_stdin
static int
cgc_push(struct rpncalc_state *state)
{
    struct operand *op = NULL;
    unsigned int type;

    int n;
    double d;

    unsigned int i, width, height;
    cgc_size_t size;
    struct matrix *m = NULL;

    if ((op = cgc_malloc(sizeof(struct operand))) == NULL)
        return -1;

    if (cgc_read_all(STDIN, &type, sizeof(type)) != sizeof(type))
        goto free_op;

    switch (type & 0xffff) {
    case INTEGER:
        if (cgc_read_all(STDIN, &n, sizeof(n)) != sizeof(n))
            goto free_op;

        cgc_set_integer(n, &op->val);
        break;
    case MATRIX:
        width = (type & (0xff << 24)) >> 24;
        height = (type & (0xff << 16)) >> 16;
        // width < 256 and height < 256, so no overflow
        size = width * height * sizeof(double);

        if (width == 0 || height == 0)
            goto free_op;

        if ((m = cgc_malloc(sizeof(struct matrix) + size)) == NULL)
            goto free_op;

        m->width = width;
        m->height = height;

        if (cgc_read_all(STDIN, m->data, size) != size)
            goto free_m;

        // Check to make sure we didn't cgc_read in any NaNs
        for (i = 0; i < size / sizeof(double); i++)
            if (IS_NAN(m->data[i]))
                goto free_m;

        cgc_set_matrix(m, &op->val);
        break;
    case DOUBLE:
        if (cgc_read_all(STDIN, &d, sizeof(d)) != sizeof(d))
            goto free_op;

        if (IS_NAN(d))
            goto free_op;

        cgc_set_double(d, &op->val);
        break;
    default:
        goto free_op;
    }

    list_push_entry_front(struct operand, list, &state->stack, op);
    return 0;

free_m:
    cgc_free(m);

free_op:
    cgc_free(op);
    return -1;
}

// pop writes directly to cgc_stdout
static int
cgc_pop(struct rpncalc_state *state)
{
    int ret = -1;
    struct operand *op;
    enum rpnval_type type;

    int n;
    double d;

    unsigned int width, height;
    cgc_size_t size;
    struct matrix *m = NULL;

    op = list_pop_entry_front(struct operand, list, &state->stack);
    if (op == NULL)
        return -1;

    type = cgc_get_type(op->val);
    switch(type) {
    case INTEGER:
        if (cgc_as_integer(op->val, &n) != 0)
            goto free_op;

        if (cgc_write_all(STDOUT, &type, sizeof(type)) != sizeof(type))
            goto free_op;

        if (cgc_write_all(STDOUT, &n, sizeof(n)) != sizeof(n))
            goto free_op;

        break;
    case MATRIX:
        if (cgc_as_matrix(op->val, &m) != 0)
            goto free_op;

        width = m->width & 0xff;
        height = m->height & 0xff;
        size = width * height * sizeof(double);

        type = width << 24 | height << 16 | MATRIX;
        if (cgc_write_all(STDOUT, &type, sizeof(type)) != sizeof(type))
            goto free_m;

        if (cgc_write_all(STDOUT, m->data, size) != size)
            goto free_m;

        break;
    case DOUBLE:
        if (cgc_as_double(op->val, &d) != 0)
            goto free_op;

        if (cgc_write_all(STDOUT, &type, sizeof(type)) != sizeof(type))
            goto free_op;

        if (cgc_write_all(STDOUT, &d, sizeof(d)) != sizeof(d))
            goto free_op;

        break;
    default:
        goto free_op;
    }

    ret = 0;

free_m:
    cgc_free(m);

free_op:
    cgc_free(op);
    return ret;
}

static int
cgc_clear(struct rpncalc_state *state)
{
    struct operand *cur, *n;
    struct matrix *m;

    list_for_each_entry_safe(struct operand, list, &state->stack, n, cur) {
        list_remove_entry(struct operand, list, &state->stack, cur);
        
        if (cgc_get_type(cur->val) == MATRIX && cgc_as_matrix(cur->val, &m) == 0)
            cgc_free(m);
            
        cgc_free(cur);
    }
    
    return 0;
}

static int
cgc_binary_op(struct rpncalc_state *state, int (*op)(rpnval, rpnval, rpnval *))
{
    struct operand *a = NULL, *b = NULL, *res = NULL;
    struct matrix *ma, *mb;

    if (cgc_list_length(&state->stack) < 2)
        return -1;

    if ((b = list_pop_entry_front(struct operand, list, &state->stack)) == NULL)
        return -1;

    if ((a = list_pop_entry_front(struct operand, list, &state->stack)) == NULL)
        goto restore_stack;

    if ((res = cgc_malloc(sizeof(struct operand))) == NULL)
        goto restore_stack;

    if (op(a->val, b->val, &res->val) != 0)
        goto restore_stack;

    list_push_entry_front(struct operand, list, &state->stack, res);

    if (cgc_get_type(a->val) == MATRIX && cgc_as_matrix(a->val, &ma) == 0)
        cgc_free(ma);
    cgc_free(a);

    if (cgc_get_type(b->val) == MATRIX && cgc_as_matrix(b->val, &mb) == 0)
        cgc_free(mb);
    cgc_free(b);

    return 0;

restore_stack:
    if (a != NULL)
        list_push_entry_front(struct operand, list, &state->stack, a);

    if (b != NULL)
        list_push_entry_front(struct operand, list, &state->stack, b);

    cgc_free(res);
    return -1;
}

static int
cgc_add(struct rpncalc_state *state)
{
    return cgc_binary_op(state, cgc_generic_add);
}

static int
cgc_sub(struct rpncalc_state *state)
{
    return cgc_binary_op(state, cgc_generic_sub);
}

static int
cgc_mul(struct rpncalc_state *state)
{
    return cgc_binary_op(state, cgc_generic_mul);
}

static int
cgc_div(struct rpncalc_state *state)
{
    return cgc_binary_op(state, cgc_generic_div);
}

static int
cgc_inv(struct rpncalc_state *state)
{
    struct operand *a = NULL, *res = NULL;
    struct matrix *ma, *mres;

    if (cgc_list_length(&state->stack) < 1)
        return -1;

    if ((a = list_pop_entry_front(struct operand, list, &state->stack)) == NULL)
        return -1;

    if (cgc_get_type(a->val) != MATRIX || cgc_as_matrix(a->val, &ma) != 0)
        goto restore_stack;

    if ((res = cgc_malloc(sizeof(struct operand))) == NULL)
        goto restore_stack;

    if (cgc_matrix_inv(ma, &mres) != 0)
        goto restore_stack;

    cgc_set_matrix(mres, &res->val);

    list_push_entry_front(struct operand, list, &state->stack, res);

    cgc_free(ma);
    cgc_free(a);
    return 0;

restore_stack:
    if (a != NULL)
        list_push_entry_front(struct operand, list, &state->stack, a);

    cgc_free(res);
    return -1;
}

void
cgc_rpncalc_init(struct rpncalc_state *state)
{
    list_init(&state->stack);
}

void
cgc_rpncalc_destroy(struct rpncalc_state *state)
{
    cgc_clear(state);
}

static int (*rpncalc_ops[])(struct rpncalc_state *) = {
    cgc_push, cgc_pop, cgc_clear, cgc_add, cgc_sub, cgc_mul, cgc_div, cgc_inv
};

int
cgc_perform_rpncalc_op(struct rpncalc_state *state, enum rpncalc_op_type type)
{
    unsigned int index = (unsigned int)type;

    if (index >= sizeof(rpncalc_ops) / sizeof(rpncalc_ops[0]))
        return -1;

    return rpncalc_ops[index](state);
}

