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

#include "cgc_sphere.h"

static double __attribute__((regparm(3))) cgc_sphere_intersect(struct sphere *, struct ray *ray, void *);

void
cgc_sphere_init(struct sphere *sphere, double radius)
{
    sphere->data = NULL;
    sphere->radius = cgc_fabs(radius);
    sphere->intersect = cgc_sphere_intersect;
}

static double __attribute__((regparm(3)))
cgc_sphere_intersect(struct sphere *sphere, struct ray *ray, void *data)
{
    // See https://en.wikipedia.org/wiki/Line-sphere_intersection
    double ret;
    struct vector o_minus_c = cgc_vector_trunc(cgc_vector_sub(ray->origin, sphere->shape.position));
    double b = cgc_vector_dot(cgc_vector_trunc(ray->direction), o_minus_c);
    double c = cgc_vector_dot(o_minus_c, o_minus_c) - (sphere->radius * sphere->radius);
    double disc = b * b - c;

    if (disc < 0)
        return 0.0;
    else
        disc = cgc_sqrt(disc);

    if ((ret = -b + disc) > EPSILON)
        return ret;
    else if ((ret = -b - disc) > EPSILON)
        return ret;
    else
        return 0.0;
}

