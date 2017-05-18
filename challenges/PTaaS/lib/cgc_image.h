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

#ifndef IMAGE_H_
#define IMAGE_H_

#include "cgc_stdio.h"
#include "cgc_vector.h"

#define IMG_MAX_WIDTH (40)
#define IMG_MAX_HEIGHT (40)

struct pixel {
    unsigned char r, g, b;
} __attribute__((packed));

struct image {
    unsigned int width, height;
    struct pixel data[0];
} __attribute__((packed));

/**
 * Initialize an image
 *
 * @param img The image to initliaze
 * @param width The width of the image
 * @param height THe height of the image
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int cgc_image_init(struct image *img, unsigned width, unsigned height);

/**
 * Destroy an image
 *
 * @param img The image to destroy
 */
void cgc_image_destroy(struct image *img);

/**
 * Write a pixel to the image at a specific coordinate
 *
 * @param img The image to cgc_write to
 * @param x The x coordinate to cgc_write to
 * @param y The y coordinate to cgc_write to
 * @param pixel The color to cgc_write
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int cgc_image_write_pixel(struct image *img, unsigned x, unsigned y, struct pixel pixel);

/**
 * Get a pixel from the image at a specific coordinate
 *
 * @param img The image to cgc_read from
 * @param x The x coordinate to cgc_read from
 * @param y The y coordinate to cgc_read from
 * @param pixel Out parameter for the color
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int cgc_image_get_pixel(struct image *img, unsigned x, unsigned y, struct pixel *pixel);

/**
 * Convert a vector representing a color to a pixel value
 *
 * @param color The color to convert
 * @param gamma Gamma correction
 * @return A pixel value representing the given color
 */
struct pixel cgc_color_to_pixel(struct vector color, double gamma);

#endif /* IMAGE_H_ */

