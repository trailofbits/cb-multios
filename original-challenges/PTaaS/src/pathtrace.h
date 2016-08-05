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

#ifndef PATHTRACE_H_
#define PATHTRACE_H_

#include "pool.h"
#include "ray.h"
#include "shape.h"

struct image;

struct pt_ctx {
    struct pool pool;
    struct ray camera;
    double fov;
    struct shape *head;
};

/**
 * Initialize a path tracing context
 *
 * @param ctx The context to initialize
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int pt_init(struct pt_ctx *ctx);

/**
 * Destroy a path tracing context
 *
 * @param ctx The context to destroy
 */
void pt_destroy(struct pt_ctx *ctx);

/**
 * Setup the camera parameters for a scene
 *
 * @param ctx The context to alter
 * @param camera The new camera ray
 * @param fov The new camera fov
 */
void pt_setup_camera(struct pt_ctx *ctx, struct ray camera, double fov);

/**
 * Add a sphere to the scene
 *
 * @param ctx The context to alter
 * @param material The type of material for the new shape
 * @param position The position of the new shape
 * @param color The color of the new shape
 * @param emission The emission of the new shape
 * @param radius The radius of the new sphere
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int pt_add_sphere(struct pt_ctx *ctx, enum surface_type material,
        struct vector position, struct vector color, struct vector emission,
        double radius);

/**
 * Add a plane to the scene
 *
 * @param ctx The context to alter
 * @param material The type of material for the new shape
 * @param position The position of the new shape
 * @param color The color of the new shape
 * @param emission The emission of the new shape
 * @param normal The normal vector of the new plane
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int pt_add_plane(struct pt_ctx *ctx, enum surface_type material,
        struct vector position, struct vector color, struct vector emission,
        struct vector normal);

/**
 * Render a scene to an image
 *
 * @param ctx The context to render
 * @param img The destination image
 */
void pt_render(struct pt_ctx *ctx, struct image *img);

/**
 * Clear all the shapes out of a context and reset the camera.
 *
 * @param ctx The context to clear
 */
void pt_clear_ctx(struct pt_ctx *ctx);

#endif /* PATHTRACE_H_ */

