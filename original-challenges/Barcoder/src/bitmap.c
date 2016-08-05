/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include <libcgc.h>
#include <string.h>
#include <stdio.h>
#include "barcode.h"
#include "bitmap.h"
#include "codes.h"

static unsigned char *create_barcode_bmp_data(barcode_128_t *barcode, unsigned int *bytes_alloc, int *bmp_width)
{
    *bytes_alloc = 0;
    *bmp_width = 0;
    char *barcode_ascii = create_barcode_ascii(barcode);
    char *barcode_ascii_start = barcode_ascii;
    if (!barcode_ascii || strlen(barcode->raw_str) > MAX_BARCODE_LENGTH)
        return NULL;
    *bytes_alloc = strlen(barcode_ascii) * PIXELW * PIXELH * 3;
    unsigned char *data = calloc(1, *bytes_alloc);
    unsigned char *pdata = data;
    unsigned int width = strlen(barcode_ascii) * PIXELW * 3;
    *bmp_width = width;

    int j = 0, i = 0;
    unsigned char *value;
    char *value_black = "\x00\x00\x00";
    char *value_white = "\xFF\xFF\xFF";
    while(*barcode_ascii) {
        if (*barcode_ascii == '|') {
            value = (unsigned char *)value_black; //Black
        } else {
            value = (unsigned char *)value_white; //White
        }

        for (i = 0; i < PIXELW; i++) {
            memcpy(pdata, value, 3);
            pdata += 3;
        }
        barcode_ascii++;
    }
    for (j = 1; j < PIXELH; j++)
        memcpy(&data[(j * width)], &data[0], width);

    free(barcode_ascii_start);
    return data;
}


int validate_bmp_headers(bmp_header_t *bheader, bmp_info_t *binfo)
{
    if (memcmp(bheader->magic, "BM", 2) != 0)
        goto error;
    if (bheader->reserved != 0)
        goto error;
    if (bheader->file_size != (binfo->imagesize + sizeof(barcode_bmp_t)))
        goto error;
    if (binfo->size != 40)
        goto error;
    if (binfo->width > ((MAX_BARCODE_LENGTH*11+14) * PIXELW) || binfo->height != PIXELH)
        goto error;
    if (binfo->planes != 1)
        goto error;
    if (binfo->bits != 24)
        goto error;
    if (binfo->compression != 0)
        goto error;
    if (binfo->imagesize != (binfo->width * binfo->height * (binfo->bits / 8)))
        goto error;
    if (binfo->hres != 2835 || binfo->vres != 2835)
        goto error;
    if (binfo->num_colors != 0)
        goto error;
    if (binfo->imp_colors != 0)
        goto error;

    return 0;
error:
    return -1;
}

barcode_bmp_t *create_barcode_bmp(barcode_128_t *barcode)
{
    bmp_header_t bheader;
    bmp_info_t binfo;

    unsigned int image_size = 0;
    int width = 0;
    unsigned char *bmp_data = create_barcode_bmp_data(barcode, &image_size, &width);
    if (!bmp_data || !image_size)
        return NULL;

    memcpy(bheader.magic, "BM", 2);
    bheader.reserved = 0;
    bheader.file_size = sizeof(barcode_bmp_t) + image_size;
    bheader.data_offset = sizeof(barcode_bmp_t);

    binfo.size = sizeof(bmp_info_t);
    binfo.bits = 24;
    binfo.width = width / (binfo.bits / 8);
    binfo.height = PIXELH;
    binfo.planes = 1;
    binfo.compression = 0;
    binfo.imagesize = (binfo.width * binfo.height) * (binfo.bits / 8);
    binfo.hres = 2835;
    binfo.vres = 2835;
    binfo.num_colors = 0;
    binfo.imp_colors = 0;

    barcode_bmp_t *barcode_bmp = malloc(sizeof(barcode_bmp_t) + image_size);
    memcpy(&barcode_bmp->header, &bheader, sizeof(bmp_header_t));
    memcpy(&barcode_bmp->info, &binfo, sizeof(bmp_info_t));
    memcpy(barcode_bmp->data, bmp_data, image_size);
    free(bmp_data);
    return barcode_bmp;
}

barcode_128_t *create_barcode_from_bmp(barcode_bmp_t *barcode_bmp)
{
    if (validate_bmp_headers(&barcode_bmp->header, &barcode_bmp->info) != 0)
        return NULL;

    char *barcode_ascii = calloc(1, (barcode_bmp->info.width / PIXELW) + 1);
    int j = 0, i = 0;
    int step = (barcode_bmp->info.bits /  8) * PIXELW;
    for (i = 0; i < barcode_bmp->info.width * (barcode_bmp->info.bits / 8); i+=step) {
        unsigned char value = barcode_bmp->data[i];
        if (value != '\x00' && value != (unsigned char)'\xFF')
            goto error;

        for (j = 1; j < step; j++) {
            if (barcode_bmp->data[i+j] != value)
                goto error;
        }

        barcode_ascii[i/step] = value == '\x00' ? '|' : ' ';
    }
    for (j = 1; j < PIXELH; j++) {
        unsigned char *p1 = &barcode_bmp->data[(j * barcode_bmp->info.width * (barcode_bmp->info.bits / 8))];
        if (memcmp(p1, &barcode_bmp->data, barcode_bmp->info.width * (barcode_bmp->info.bits / 8)) != 0)
            goto error;
    }

    barcode_128_t *new_barcode = create_barcode_from_encoded_data(barcode_ascii);
    free(barcode_ascii);
    return new_barcode;
error:
    free(barcode_ascii);
    return NULL;
}
