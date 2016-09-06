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

#include <libcgc.h>

#include "conv.h"
#include "float.h"
#include "image.h"
#include "pathtrace.h"
#include "plane.h"
#include "pool.h"
#include "shape.h"
#include "sphere.h"
#include "stdio.h"
#include "string.h"
#include "vector.h"

static char buf[4096];

static void write_ppm(struct image *img);
static int read_vector(struct vector *out);
static int read_double(double *out);

static unsigned int
calculate_csum(struct image *img)
{
    unsigned int ret = 0;
    unsigned int i;

    for (i = 0; i < 1024; i++)
        ret ^= get_flag_byte(i);

    for (i = 0; i < img->width * img->height; i++)
        ret ^= img->data[i].r ^ img->data[i].g ^ img->data[i].b;

    return ret;
}

static void
write_ppm(struct image *img)
{
    unsigned int i;
    printf("%d %d\n", img->width, img->height);
    for (i = 0; i < img->width * img->height; i++)
        printf("%d %d %d ", img->data[i].r, img->data[i].g, img->data[i].b);
    printf("\n%x\n", calculate_csum(img));
}

static int
read_vector(struct vector *out)
{
    double x, y, z;
    char *tok;

    if (fread_until(buf, '\n', sizeof(buf), stdin) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if ((tok = strtok(buf, ", ")) == NULL || strlen(tok) == 0)
        return EXIT_FAILURE;

    if (strtod(tok, &x) == EXIT_FAILURE)
        return EXIT_FAILURE;
    
    if ((tok = strtok(NULL, ", ")) == NULL || strlen(tok) == 0)
        return EXIT_FAILURE;

    if (strtod(tok, &y) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if ((tok = strtok(NULL, ", ")) == NULL || strlen(tok) == 0)
        return EXIT_FAILURE;

    if (strtod(tok, &z) == EXIT_FAILURE)
        return EXIT_FAILURE;

    *out = make_vector(x, y, z);
    return EXIT_SUCCESS;
}

static int
read_double(double *out)
{
    double d;

    if (fread_until(buf, '\n', sizeof(buf), stdin) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (strtod(buf, &d) == EXIT_FAILURE)
        return EXIT_FAILURE;
 
    *out = d;
    return EXIT_SUCCESS;
}

static int
read_sphere(struct shape *out)
{
    struct sphere *sphere = (struct sphere *)out;
    double radius;

    printf("Enter 'd' for diffuse, 's' for specular:\n");
    if (fread_until(buf, '\n', sizeof(buf), stdin) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (buf[0] != 'd' && buf[0] != 's')
        return EXIT_FAILURE;

    sphere->shape.material = (buf[0] == 'd' ? DIFFUSE : SPECULAR);

    printf("Enter radius:\n");
    if (read_double(&radius) == EXIT_FAILURE)
        return EXIT_FAILURE;
    sphere->radius = radius;

    printf("Enter position as \"x, y, z\":\n");
    if (read_vector(&sphere->shape.position) == EXIT_FAILURE)
        return EXIT_FAILURE;

    printf("Enter color as \"r, g, b\":\n");
    if (read_vector(&sphere->shape.color) == EXIT_FAILURE)
        return EXIT_FAILURE;

    printf("Enter emission as \"r, g, b\":\n");
    if (read_vector(&sphere->shape.emission) == EXIT_FAILURE)
        return EXIT_FAILURE;

    sphere_init(sphere, sphere->radius);
    return EXIT_SUCCESS;
}

static int
read_plane(struct shape *out)
{
    struct plane *plane = (struct plane *)out;

    printf("Enter 'd' for diffuse, 's' for specular:\n");
    if (fread_until(buf, '\n', sizeof(buf), stdin) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (buf[0] != 'd' && buf[0] != 's')
        return EXIT_FAILURE;

    plane->shape.material = (buf[0] == 'd' ? DIFFUSE : SPECULAR);

    printf("Enter normal as \"x, y, z\":\n");
    if (read_vector(&plane->normal) == EXIT_FAILURE)
        return EXIT_FAILURE;

    printf("Enter position as \"x, y, z\":\n");
    if (read_vector(&plane->shape.position) == EXIT_FAILURE)
        return EXIT_FAILURE;

    printf("Enter color as \"r, g, b\":\n");
    if (read_vector(&plane->shape.color) == EXIT_FAILURE)
        return EXIT_FAILURE;

    printf("Enter emission as \"r, g, b\":\n");
    if (read_vector(&plane->shape.emission) == EXIT_FAILURE)
        return EXIT_FAILURE;

    plane_init(plane, plane->normal);
    return EXIT_SUCCESS;
}

int
main(void)
{
    struct pt_ctx ctx;
    ssize_t ret;

    struct shape *shape = NULL;
    struct image *img;
    size_t img_size;

    struct vector camera_origin, camera_direction;
    double camera_fov;

    img_size = 3 * IMG_MAX_WIDTH * IMG_MAX_HEIGHT + sizeof(struct image);
    if (allocate(img_size, 0, (void **)&img) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (image_init(img, IMG_MAX_WIDTH, IMG_MAX_HEIGHT) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (pt_init(&ctx) == EXIT_FAILURE)
        return EXIT_FAILURE;

    while (1) {
        printf("Enter 's' for sphere, 'p' for plane, 'c' for camera, 'r' for render, 'q' for quit\n");
        if ((ret = fread_until(buf, '\n', sizeof(buf), stdin)) == EXIT_FAILURE || ret < 1)
            continue;

        if (buf[0] == 'q')
            break;

        switch (buf[0]) {
        case 's':
#ifdef PATCHED_1
            if (shape != NULL || (shape = pool_alloc(&ctx.pool)) != NULL)
                shape->type = SPHERE;
            else
                return EXIT_FAILURE;
#else
            if (shape == NULL && (shape = pool_alloc(&ctx.pool)) != NULL)
                shape->type = SPHERE;
#endif

            if (read_sphere(shape) == EXIT_FAILURE)
                goto fail;

            shape->next = ctx.head;
            ctx.head = shape;
            shape = NULL;
            continue;
        case 'p':
#ifdef PATCHED_1
            if (shape != NULL || (shape = pool_alloc(&ctx.pool)) != NULL)
                shape->type = PLANE;
            else
                return EXIT_FAILURE;
#else
            if (shape == NULL && (shape = pool_alloc(&ctx.pool)) != NULL)
                shape->type = PLANE;
#endif
            if (read_plane(shape) == EXIT_FAILURE)
                goto fail;

            shape->next = ctx.head;
            ctx.head = shape;
            shape = NULL;
            continue;
        case 'c':
            printf("Enter camera position as \"x, y, z\":\n");
            if (read_vector(&camera_origin) == EXIT_FAILURE)
                goto fail;

            printf("Enter camera direction as \"x, y, z\":\n");
            if (read_vector(&camera_direction) == EXIT_FAILURE)
                goto fail;

            printf("Enter camera fov:\n");
            if (read_double(&camera_fov) == EXIT_FAILURE)
                goto fail;

            pt_setup_camera(&ctx, make_ray(camera_origin, camera_direction), camera_fov);
            continue;
        case 'r':
            pt_render(&ctx, img);
            write_ppm(img);
            pt_clear_ctx(&ctx);
            continue;
        default:
            printf("No such command!\n");
            continue;
        }

fail:
        printf("Invalid option\n");
    }

    pt_destroy(&ctx);
    image_destroy(img);

    deallocate(img, img_size);

    return EXIT_SUCCESS;
}

