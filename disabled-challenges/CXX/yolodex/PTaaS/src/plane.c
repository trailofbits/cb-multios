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

#include "cgc_float.h"
#include "cgc_ray.h"
#include "cgc_shape.h"
#include "cgc_stdlib.h"
#include "cgc_trunc.h"
#include "cgc_vector.h"

#include "cgc_plane.h"

static double __attribute__((regparm(3))) cgc_plane_intersect(struct plane *, struct ray *, void *);

void
cgc_plane_init(struct plane *plane, struct vector normal)
{
    plane->data = NULL;
    plane->normal = normal;
    plane->intersect = cgc_plane_intersect;
}

static double __attribute__((regparm(3)))
cgc_plane_intersect(struct plane *plane, struct ray *ray, void *data)
{
    // See https://en.wikipedia.org/wiki/Line-plane_intersection
    struct vector l0 = cgc_vector_add(ray->origin, cgc_vector_trunc(ray->direction));
    struct vector p0_minus_l0 = cgc_vector_trunc(cgc_vector_sub(plane->shape.position, l0));
    double p0_minus_l0_dot_n = cgc_vector_dot(p0_minus_l0, cgc_vector_trunc(cgc_vector_norm(plane->normal)));

    if (cgc_fabs(p0_minus_l0_dot_n) > EPSILON)
        return p0_minus_l0_dot_n / cgc_vector_dot(cgc_vector_trunc(ray->direction), cgc_vector_trunc(cgc_vector_norm(plane->normal)));
    else
        return 0.0;
}

