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

#include "float.h"
#include "image.h"
#include "limits.h"
#include "plane.h"
#include "pool.h"
#include "shape.h"
#include "sphere.h"
#include "stdlib.h"
#include "trunc.h"
#include "vector.h"

#include "pathtrace.h"

static int intersect(struct pt_ctx *, struct ray *, struct shape **, double *);
static double drand(void);
static struct vector radiance(struct pt_ctx *, struct ray *, unsigned int);

int
pt_init(struct pt_ctx *ctx)
{
    if (pool_init(&ctx->pool, MAX(sizeof(struct sphere), sizeof(struct plane))) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    pt_clear_ctx(ctx);

    return EXIT_SUCCESS;
}

void
pt_destroy(struct pt_ctx *ctx)
{
    pool_destroy(&ctx->pool);
}

void
pt_setup_camera(struct pt_ctx *ctx, struct ray camera, double fov)
{
    ctx->camera = camera;
    ctx->fov = fov;
}

int
pt_add_sphere(struct pt_ctx *ctx, enum surface_type material,
        struct vector position, struct vector color, struct vector emission,
        double radius)
{
    struct sphere *sphere;

    if ((sphere = pool_alloc(&ctx->pool)) == NULL)
        return EXIT_FAILURE;

    shape_init(&sphere->shape, SPHERE, material, position, color, emission);
    sphere_init(sphere, radius);

    sphere->shape.next = ctx->head;
    ctx->head = &sphere->shape;

    return EXIT_SUCCESS;
}

int
pt_add_plane(struct pt_ctx *ctx, enum surface_type material,
        struct vector position, struct vector color, struct vector emission,
        struct vector normal)
{
    struct plane *plane;

    if ((plane = pool_alloc(&ctx->pool)) == NULL)
        return EXIT_FAILURE;

    shape_init(&plane->shape, PLANE, material, position, color, emission);
    plane_init(plane, normal);

    plane->shape.next = ctx->head;
    ctx->head = &plane->shape;

    return EXIT_SUCCESS;
}

void
pt_render(struct pt_ctx *ctx, struct image *img)
{
    struct ray r;
    struct vector d, cx, cy;
    unsigned int x, y;

    r.origin = ctx->camera.origin;
    cx = make_vector((img->width * ctx->fov) / img->height, 0.0, 0.0);
    cy = vector_trunc(vector_norm(vector_cross(cx, ctx->camera.direction)));

    for (y = 0; y < img->height; y++) {
        for (x = 0; x < img->width; x++) {
            d = vector_add(vector_add(vector_scale(cx, ((double)x / img->width) - 0.5),
                    vector_scale(cy, ((double)y / img->height) - 0.5)), vector_trunc(ctx->camera.direction));
            r.direction = vector_trunc(vector_norm(d));
            image_write_pixel(img, x, y, color_to_pixel(radiance(ctx, &r, 0), 2.2));
        }
    }
}

void
pt_clear_ctx(struct pt_ctx *ctx)
{
    ctx->head = NULL;
    pool_free_all(&ctx->pool);
    pt_setup_camera(ctx, make_ray(make_vector(0.0, 200.0, 0.0), make_vector(0.0, -1.0, 0.0)), 0.6);
}

static int
intersect(struct pt_ctx *ctx, struct ray *ray, struct shape **shape, double *distance)
{
    struct shape *cur;
    struct sphere *sphere;
    struct plane *plane;

    double d, best_distance = 1e100;
    struct shape *best_shape = NULL;

    for (cur = ctx->head; cur != NULL; cur = cur->next) {
        switch (cur->type) {
        case SPHERE:
            sphere = (struct sphere *)cur;
            d = sphere->intersect(sphere, ray, sphere->data);
            if  (d > EPSILON && d < best_distance) {
                best_distance = d;
                best_shape = cur;
            }
            break;
        case PLANE:
            plane = (struct plane *)cur;
            d = plane->intersect(plane, ray, plane->data);
            if  (d > EPSILON && d < best_distance) {
                best_distance = d;
                best_shape = cur;
            }
            break;
        default:
            break;
        }
    }

    if (best_shape == NULL)
        return 0;

    *shape = best_shape;
    *distance = best_distance;

    return 1;
}

static struct vector
radiance(struct pt_ctx *ctx, struct ray *ray, unsigned int depth)
{
    double distance;
    struct shape *shape, *shadow_shape, *cur;
    struct ray shadow_ray, specular_ray;
    struct vector ret = make_vector(0.0, 0.0, 0.0);
    
    if (depth > 3)
        return ret;

    if (intersect(ctx, ray, &shape, &distance)) {
        struct vector x = vector_trunc(vector_add(ray->origin,
                    vector_trunc(vector_scale(vector_trunc(ray->direction), distance))));
        struct vector n = shape->type == SPHERE ?
            vector_trunc(vector_norm(vector_sub(x, shape->position))) :
            vector_trunc(vector_norm(((struct plane *)shape)->normal));
        if (vector_dot(n, vector_trunc(ray->direction)) > 0)
            n = vector_trunc(vector_scale(n, -1));

        if (vector_mag_sqr(shape->emission) > EPSILON) {
            return vector_trunc(vector_norm(shape->emission));
        } else if (shape->material == DIFFUSE) {
            for (cur = ctx->head; cur != NULL; cur = cur->next) {
                if (vector_mag_sqr(cur->emission) > EPSILON) {
                    struct vector l = vector_trunc(vector_norm(vector_sub(cur->position, n)));
                    double factor = vector_dot(n, l);

                    shadow_ray = make_ray(x, l);
                    if (intersect(ctx, &shadow_ray, &shadow_shape, &distance))
                        factor /= 2.0;

                    ret = vector_trunc(vector_add(vector_trunc(vector_norm(shape->emission)),
                            vector_add(ret, vector_trunc(vector_scale(vector_trunc(vector_norm(shape->color)), factor)))));
                }
            }
        } else if (shape->material == SPECULAR) {
            specular_ray = make_ray(x, vector_trunc(vector_sub(vector_trunc(ray->direction),
                            vector_trunc(vector_scale(n, -2 * vector_dot(n, vector_trunc(ray->direction)))))));
            return vector_trunc(vector_add(vector_trunc(vector_norm(shape->emission)),
                        vector_mul(vector_trunc(vector_norm(shape->color)),
                        vector_trunc(radiance(ctx, &specular_ray, depth + 1)))));
        }
    }

    return ret;
}

