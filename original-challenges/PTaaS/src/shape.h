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

#ifndef SHAPE_H_
#define SHAPE_H_

#include "vector.h"

enum shape_type {
    SPHERE,
    PLANE
};

enum surface_type {
    DIFFUSE,
    SPECULAR
};

struct shape {
    struct shape *next;
    enum shape_type type;
    enum surface_type material;
    struct vector position, color, emission;
};

/**
 * Initialize a new shape
 *
 * @param shape The shape to initialize
 * @param type The type of the new shape
 * @param material The type of material to assign the new shape
 * @param position The position of the new shape
 * @param color The color of the new shape
 * @param emission The emission of the new shape
 */
void shape_init(struct shape *shape, enum shape_type type, enum surface_type material,
        struct vector position, struct vector color, struct vector emission);

#endif /* SHAPE_H_ */

