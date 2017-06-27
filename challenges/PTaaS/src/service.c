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

#include "cgc_conv.h"
#include "cgc_float.h"
#include "cgc_image.h"
#include "cgc_pathtrace.h"
#include "cgc_plane.h"
#include "cgc_pool.h"
#include "cgc_shape.h"
#include "cgc_sphere.h"
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_vector.h"

static char buf[4096];

static void cgc_write_ppm(struct image *img);
static int cgc_read_vector(struct vector *out);
static int cgc_read_double(double *out);

static unsigned int
cgc_calculate_csum(struct image *img)
{
    unsigned int ret = 0;
    unsigned int i;

    for (i = 0; i < 1024; i++)
        ret ^= cgc_get_flag_byte(i);

    for (i = 0; i < img->width * img->height; i++)
        ret ^= img->data[i].r ^ img->data[i].g ^ img->data[i].b;

    return ret;
}

static void
cgc_write_ppm(struct image *img)
{
    unsigned int i;
    cgc_printf("%d %d\n", img->width, img->height);
    for (i = 0; i < img->width * img->height; i++)
        cgc_printf("%d %d %d ", img->data[i].r, img->data[i].g, img->data[i].b);
    cgc_printf("\n%x\n", cgc_calculate_csum(img));
}

static int
cgc_read_vector(struct vector *out)
{
    double x, y, z;
    char *tok;

    if (cgc_fread_until(buf, '\n', sizeof(buf), cgc_stdin) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if ((tok = cgc_strtok(buf, ", ")) == NULL || cgc_strlen(tok) == 0)
        return EXIT_FAILURE;

    if (cgc_strtod(tok, &x) == EXIT_FAILURE)
        return EXIT_FAILURE;
    
    if ((tok = cgc_strtok(NULL, ", ")) == NULL || cgc_strlen(tok) == 0)
        return EXIT_FAILURE;

    if (cgc_strtod(tok, &y) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if ((tok = cgc_strtok(NULL, ", ")) == NULL || cgc_strlen(tok) == 0)
        return EXIT_FAILURE;

    if (cgc_strtod(tok, &z) == EXIT_FAILURE)
        return EXIT_FAILURE;

    *out = cgc_make_vector(x, y, z);
    return EXIT_SUCCESS;
}

static int
cgc_read_double(double *out)
{
    double d;

    if (cgc_fread_until(buf, '\n', sizeof(buf), cgc_stdin) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (cgc_strtod(buf, &d) == EXIT_FAILURE)
        return EXIT_FAILURE;
 
    *out = d;
    return EXIT_SUCCESS;
}

static int
cgc_read_sphere(struct shape *out)
{
    struct sphere *sphere = (struct sphere *)out;
    double radius;

    cgc_printf("Enter 'd' for diffuse, 's' for specular:\n");
    if (cgc_fread_until(buf, '\n', sizeof(buf), cgc_stdin) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (buf[0] != 'd' && buf[0] != 's')
        return EXIT_FAILURE;

    sphere->shape.material = (buf[0] == 'd' ? DIFFUSE : SPECULAR);

    cgc_printf("Enter radius:\n");
    if (cgc_read_double(&radius) == EXIT_FAILURE)
        return EXIT_FAILURE;
    sphere->radius = radius;

    cgc_printf("Enter position as \"x, y, z\":\n");
    if (cgc_read_vector(&sphere->shape.position) == EXIT_FAILURE)
        return EXIT_FAILURE;

    cgc_printf("Enter color as \"r, g, b\":\n");
    if (cgc_read_vector(&sphere->shape.color) == EXIT_FAILURE)
        return EXIT_FAILURE;

    cgc_printf("Enter emission as \"r, g, b\":\n");
    if (cgc_read_vector(&sphere->shape.emission) == EXIT_FAILURE)
        return EXIT_FAILURE;

    cgc_sphere_init(sphere, sphere->radius);
    return EXIT_SUCCESS;
}

static int
cgc_read_plane(struct shape *out)
{
    struct plane *plane = (struct plane *)out;

    cgc_printf("Enter 'd' for diffuse, 's' for specular:\n");
    if (cgc_fread_until(buf, '\n', sizeof(buf), cgc_stdin) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (buf[0] != 'd' && buf[0] != 's')
        return EXIT_FAILURE;

    plane->shape.material = (buf[0] == 'd' ? DIFFUSE : SPECULAR);

    cgc_printf("Enter normal as \"x, y, z\":\n");
    if (cgc_read_vector(&plane->normal) == EXIT_FAILURE)
        return EXIT_FAILURE;

    cgc_printf("Enter position as \"x, y, z\":\n");
    if (cgc_read_vector(&plane->shape.position) == EXIT_FAILURE)
        return EXIT_FAILURE;

    cgc_printf("Enter color as \"r, g, b\":\n");
    if (cgc_read_vector(&plane->shape.color) == EXIT_FAILURE)
        return EXIT_FAILURE;

    cgc_printf("Enter emission as \"r, g, b\":\n");
    if (cgc_read_vector(&plane->shape.emission) == EXIT_FAILURE)
        return EXIT_FAILURE;

    cgc_plane_init(plane, plane->normal);
    return EXIT_SUCCESS;
}

int
main(int cgc_argc, char *cgc_argv[])
{
    struct pt_ctx ctx;
    cgc_ssize_t ret;

    struct shape *shape = NULL;
    struct image *img;
    cgc_size_t img_size;

    struct vector camera_origin, camera_direction;
    double camera_fov;

    img_size = 3 * IMG_MAX_WIDTH * IMG_MAX_HEIGHT + sizeof(struct image);
    if (cgc_allocate(img_size, 0, (void **)&img) == EXIT_FAILURE)
        return EXIT_FAILURE;
    if (cgc_image_init(img, IMG_MAX_WIDTH, IMG_MAX_HEIGHT) == EXIT_FAILURE)
        return EXIT_FAILURE;

    if (cgc_pt_init(&ctx) == EXIT_FAILURE)
        return EXIT_FAILURE;

    while (1) {
        cgc_printf("Enter 's' for sphere, 'p' for plane, 'c' for camera, 'r' for render, 'q' for quit\n");
        if ((ret = cgc_fread_until(buf, '\n', sizeof(buf), cgc_stdin)) == EXIT_FAILURE || ret < 1)
            continue;

        if (buf[0] == 'q')
            break;

        switch (buf[0]) {
        case 's':
#ifdef PATCHED_1
            if (shape != NULL || (shape = cgc_pool_alloc(&ctx.pool)) != NULL)
                shape->type = SPHERE;
            else
                return EXIT_FAILURE;
#else
            if (shape == NULL && (shape = cgc_pool_alloc(&ctx.pool)) != NULL)
                shape->type = SPHERE;
#endif

            if (cgc_read_sphere(shape) == EXIT_FAILURE)
                goto fail;

            shape->next = ctx.head;
            ctx.head = shape;
            shape = NULL;
            continue;
        case 'p':
#ifdef PATCHED_1
            if (shape != NULL || (shape = cgc_pool_alloc(&ctx.pool)) != NULL)
                shape->type = PLANE;
            else
                return EXIT_FAILURE;
#else
            if (shape == NULL && (shape = cgc_pool_alloc(&ctx.pool)) != NULL)
                shape->type = PLANE;
#endif
            if (cgc_read_plane(shape) == EXIT_FAILURE)
                goto fail;

            shape->next = ctx.head;
            ctx.head = shape;
            shape = NULL;
            continue;
        case 'c':
            cgc_printf("Enter camera position as \"x, y, z\":\n");
            if (cgc_read_vector(&camera_origin) == EXIT_FAILURE)
                goto fail;

            cgc_printf("Enter camera direction as \"x, y, z\":\n");
            if (cgc_read_vector(&camera_direction) == EXIT_FAILURE)
                goto fail;

            cgc_printf("Enter camera fov:\n");
            if (cgc_read_double(&camera_fov) == EXIT_FAILURE)
                goto fail;

            cgc_pt_setup_camera(&ctx, cgc_make_ray(camera_origin, camera_direction), camera_fov);
            continue;
        case 'r':
            cgc_pt_render(&ctx, img);
            cgc_write_ppm(img);
            cgc_pt_clear_ctx(&ctx);
            continue;
        default:
            cgc_printf("No such command!\n");
            continue;
        }

fail:
        cgc_printf("Invalid option\n");
    }

    cgc_pt_destroy(&ctx);
    cgc_image_destroy(img);

    cgc_deallocate(img, img_size);

    return EXIT_SUCCESS;
}

