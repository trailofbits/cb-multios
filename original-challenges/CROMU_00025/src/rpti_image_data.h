/*
Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#ifndef __RPTI_IMAGE_DATA__
#define __RPTI_IMAGE_DATA__
#include <libcgc.h>
#include <stdlib.h>

#define RPTI_MAGIC 0xc35109d3
/**
 * Structure to hold the rpti image data.
 * It points to the current byte/bit to be read
 **/
typedef struct rpti_image_data {
	char *buffer;
	int max;
	int cbyte;
	int cbit;
} rpti_image_data, *prpti_image_data;

int rpti_display_img( prpti_image_data );
int rpti_read_magic( prpti_image_data );
int rpti_read_xaxis( prpti_image_data );
int rpti_read_yaxis( prpti_image_data );
int rpti_read_initx( prpti_image_data rid, int *out_data );
int rpti_read_inity( prpti_image_data rid, int *out_data );
int rpti_read_axist( prpti_image_data );
int rpti_read_pixel( prpti_image_data rid, int *out_data  );
int rpti_read_check( prpti_image_data, int bit_count );
int rpti_inc_index( prpti_image_data, int bit_count );
int rpti_read_bits( prpti_image_data, int bit_count, int *out_data );

#endif
