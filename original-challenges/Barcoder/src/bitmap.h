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
#ifndef BITMAP_H_
#define BITMAP_H_

#pragma pack(push, 1)
typedef struct {
    unsigned char magic[2];
    unsigned int file_size;
    unsigned int reserved;
    unsigned int data_offset;
} bmp_header_t;
#pragma pack(pop)

typedef struct {
    unsigned int size;
    int width;
    int height;
    unsigned short planes;
    unsigned short bits;
    unsigned int compression;
    unsigned int imagesize;
    int hres;
    int vres;
    unsigned int num_colors;
    unsigned int imp_colors;
} bmp_info_t;

#pragma pack(push, 1)
typedef struct {
    bmp_header_t header;
    bmp_info_t info;
    unsigned char data[];
} barcode_bmp_t;
#pragma pack(pop)

int validate_bmp_headers(bmp_header_t *bheader, bmp_info_t *binfo);
barcode_bmp_t *create_barcode_bmp(barcode_128_t *barcode);
barcode_128_t *create_barcode_from_bmp(barcode_bmp_t *barcode_bmp);

#endif
