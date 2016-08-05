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
#ifndef BARCODE_H_
#define BARCODE_H_

#define MAX_LENGTH 40

enum {TYPE_B = 100, TYPE_C = 101};

typedef struct
{
    unsigned char code_b;
    unsigned char code_c[3];
    unsigned char binary_rep[14];
    unsigned int weight;
} barcode_128_lut_t;

typedef struct barcode_128
{
    int length;
    int encoding_type;
    char *raw_str;
    barcode_128_lut_t **encoded_data;
    int checksum;
} barcode_128_t;

barcode_128_t *create_barcode_from_str(char *barcode_str);
barcode_128_t *create_barcode_from_encoded_data(char *encoded_data);
char *create_barcode_ascii(barcode_128_t *barcode);
void print_barcode_ascii(barcode_128_t *barcode, int include_str);

#endif
