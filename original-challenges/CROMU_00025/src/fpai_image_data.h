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

#ifndef __FPAI_IMAGE_DATA__
#define __FPAI_IMAGE_DATA__
#include <libcgc.h>
#include <stdlib.h>

#define FPAI_MAGIC 0x55d9b6de

typedef struct fpai_image_data {
        char *buffer;
        int max;
        int cbyte;
        int cbit;
	int xlen;
	int ylen;
	int axist;
	short checksum;
} fpai_image_data, *pfpai_image_data;

int fpai_add_pixel( pfpai_image_data fid, char *image, int x, int y, char pixel );
int fpai_display_img( pfpai_image_data fid );
int fpai_read_check( pfpai_image_data fid, int bitcount );
int fpai_read_nbits( pfpai_image_data fid, int bitcount, int *value);
int fpai_read_magic( pfpai_image_data fid );
int fpai_read_xaxis( pfpai_image_data fid );
int fpai_read_yaxis( pfpai_image_data fid );
int fpai_read_axist( pfpai_image_data fid );
int fpai_read_cksum( pfpai_image_data fid, short *cksum);
int fpai_calc_cksum( pfpai_image_data fid);
int fpai_read_pixel( pfpai_image_data fid, int *x, int*y, int*pixel);

#endif
