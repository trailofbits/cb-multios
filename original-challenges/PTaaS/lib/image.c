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

#include "stdio.h"
#include "string.h"
#include "math.h"
#include "vector.h"

#include "image.h"

int
image_init(struct image *img, unsigned width, unsigned height)
{
    if (width > IMG_MAX_WIDTH || height > IMG_MAX_HEIGHT)
        return EXIT_FAILURE;

    img->width = width;
    img->height = height;
    memset(img->data, '\0', sizeof(struct pixel) * width * height);
    return EXIT_SUCCESS;
}

void
image_destroy(struct image *img)
{
    img->width = 0;
    img->height = 0;
}

int
image_write_pixel(struct image *img, unsigned x, unsigned y, struct pixel pixel)
{
    if (x > img->width || y > img->height)
        return EXIT_FAILURE;

    img->data[y * img->width + x] = pixel;
    return EXIT_SUCCESS;
}

int
image_get_pixel(struct image *img, unsigned x, unsigned y, struct pixel *pixel)
{
    if (x > img->width || y > img->height)
        return EXIT_FAILURE;

    *pixel = img->data[y * img->width + x];
    return EXIT_SUCCESS;
}

struct pixel
color_to_pixel(struct vector color, double gamma)
{
    struct pixel ret;
    ret.r = pow(clamp(color.x), 1.0 / gamma) * 255.0;
    ret.g = pow(clamp(color.y), 1.0 / gamma) * 255.0;
    ret.b = pow(clamp(color.z), 1.0 / gamma) * 255.0;
    return ret;
}

