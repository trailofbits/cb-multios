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
/**
 * @file rpnval.h
 *
 * Types and utility functions for manipulating rpnvals.
 */

#ifndef RPNVAL_H_
#define RPNVAL_H_

#include <libcgc.h>

typedef double rpnval;

struct matrix {
    unsigned int width, height;
    double data[0];
};

#define NAN_MASK (0x7ff8ull << 48)
// This will also catch +/- inf
#define IS_NAN(x) ((*((unsigned long long *)(&x)) & (0x7ff0ull << 48)) == (0x7ff0ull << 48))
#define GET_TYPE(x) ((*((unsigned long long *)(&x)) & ((0xffffull) << 32)) >> 32)
#define GET_VALUE(x) ((unsigned long)(*((unsigned long long *)(&x)) & 0xfffffffful))
#define SIZEOF_MATRIX(m) (sizeof(struct matrix) + m->width * m->height * sizeof(double))

enum rpnval_type {
    INTEGER,
    MATRIX,
    DOUBLE
};

/**
 * Return the type of the rpnval.
 *
 * @param val The rpnval
 * @return The type of val
 */
static inline enum rpnval_type
get_type(rpnval val)
{
    int type = GET_TYPE(val);

    if (IS_NAN(val)) {
        if (type == INTEGER)
            return INTEGER;
        else if (type == MATRIX)
            return MATRIX;
    }

    return DOUBLE;
}

/**
 * Get the integer value of an rpnval.
 *
 * @param val The rpnval
 * @param out Output pointer
 * @return 0 if successful, -1 if not
 */
static inline int
as_integer(rpnval val, int *out)
{
    if (out == NULL)
        return -1;

    if (get_type(val) != INTEGER)
        return -1;

    *out = GET_VALUE(val);

    // If out == INT_MIN, this causes erroneous SIGFPE, so disallow this
    if (*out == INT_MIN)
        return -1;

    return 0;
}

/**
 * Set the value of an rpnval to a given integer.
 *
 * @param val_ The integer value to set
 * @param out_ Output pointer
 */
static inline void
set_integer(int val_, rpnval *out_)
{
    unsigned long long *out = (unsigned long long *)out_;
    unsigned long long tag = (unsigned long long)INTEGER << 32;
    unsigned long long val = (unsigned long long)val_ & 0xffffffff;

    *out = NAN_MASK | tag | val;
}

/**
 * Get the matrix value of an rpnval.
 * 
 * @param val The rpnval
 * @param out Output pointer
 * @return 0 if successful, -1 if not
 */
static inline int
as_matrix(rpnval val, struct matrix **out)
{
    if (out == NULL)
        return -1;

    if (get_type(val) != MATRIX)
        return -1;

    *out = (struct matrix *)GET_VALUE(val);
    return 0;
}

/**
 * Set the value of an rpnval to a given matrix.
 *
 * @param val_ The matrix value to set
 * @param out_ Output pointer
 */
static inline void
set_matrix(struct matrix *val_, rpnval *out_)
{
    unsigned long long *out = (unsigned long long *)out_;
    unsigned long long tag = (unsigned long long)MATRIX << 32;
    unsigned long long val = (unsigned long long)val_;

    *out = NAN_MASK | tag | val;
}

/**
 * Get the double value of an rpnval.
 *
 * @param val The rpnval
 * @param out Output pointer
 * @return 0 if successful, -1 of not
 */
static inline int
as_double(rpnval val, double *out)
{
    if (out == NULL)
        return -1;

    if (get_type(val) != DOUBLE)
        return -1;

    *out = val;
    return 0;
}

/**
 * Set the value of an rpnval to a given double.
 *
 * @param val The double value to set
 * @param out Ouput pointer
 */
static inline void
set_double(double val, rpnval *out)
{
    *out = val;
}

#endif /* RPNVAL_H_ */

