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

#ifndef __FPTI_IMAGE_DATA__
#define __FPTI_IMAGE_DATA__
#include <libcgc.h>
#include <mymath.h>
#include <stdlib.h>

#define FPTI_MAGIC 0x24c7ee85

/**
 * Structure to hold the fpti image data.
 * It points to the current byte/bit to be read
 **/
typedef struct fpti_image_data {
        char *buffer;
        int max;
        int cbyte;
        int cbit;
	char pixel;
} fpti_image_data, *pfpti_image_data;

int fpti_add_pixel( pfpti_image_data fid, int x, int y, char *image, int xlen, int ylen, int at);
int fpti_display_img( pfpti_image_data fid );
int fpti_read_magic( pfpti_image_data fid );
int fpti_read_xaxis( pfpti_image_data fid );
int fpti_read_yaxis( pfpti_image_data fid );
int fpti_read_axist( pfpti_image_data fid );
int fpti_read_ptype( pfpti_image_data fid, int *ptype);
int fpti_read_pixel( pfpti_image_data fid, int *x, int *y);
int fpti_read_check( pfpti_image_data fid, int bitcount);
int fpti_read_nbits( pfpti_image_data fid, int bitcount, int *value);

#endif
