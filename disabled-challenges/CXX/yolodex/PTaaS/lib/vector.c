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

#include "libcgc.h"

#include "cgc_stdio.h"

#include "cgc_vector.h"

struct vector
cgc_make_vector(double x, double y, double z)
{
    struct vector ret;
    ret.x = x;
    ret.y = y;
    ret.z = z;
    return ret;
}

struct vector
cgc_vector_add(struct vector a, struct vector b)
{
    return cgc_make_vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

struct vector
cgc_vector_sub(struct vector a, struct vector b)
{
    return cgc_make_vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

struct vector
cgc_vector_mul(struct vector a, struct vector b)
{
    return cgc_make_vector(a.x * b.x, a.y * b.y, a.z * b.z);
}

struct vector
cgc_vector_scale(struct vector a, double s)
{
    return cgc_make_vector(a.x * s, a.y * s, a.z * s);
}

double
cgc_vector_mag_sqr(struct vector a)
{
    return a.x * a.x + a.y * a.y + a.z * a.z;
}

double
cgc_vector_mag(struct vector a)
{
    return cgc_sqrt(cgc_vector_mag_sqr(a));
}

struct vector
cgc_vector_norm(struct vector a)
{
    return cgc_vector_scale(a, 1.0 / cgc_vector_mag(a));
}

double
cgc_vector_dot(struct vector a, struct vector b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
    
struct vector
cgc_vector_cross(struct vector a, struct vector b)
{
    return cgc_make_vector(a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x);
}

