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

#ifndef __TBIR_IMAGE_DATA__
#define __TBIR_IMAGE_DATA__

#include <libcgc.h>
#include <stdlib.h>
#include <mymath.h>

#define TBIR_MAGIC 0xb0c4df76
#define TBIR_HEADER 0x00000001
#define TBIR_FLAGS  0x00000010
#define TBIR_PIXELT 0x00000100
#define TBIR_LOADD  0x00001000
#define TBIR_PIXELS 0x00010000
#define TBIR_CHKSUM 0x00100000
#define TBIR_EOF    0x01000000

typedef struct tbir_image_data {
	char *buffer;
	int max;
	int cbyte;
	int cbit;
	int width;
	int height;
	int pixel_type;
	int load_direction;
	char *image;
	int image_length;
	int checksum;

	/// Used to determine which sections have been encountered
	/// 0x00000001 - Header parsed
	/// 0x00000010 - Flags parsed
	/// 0x00000100 - Pixel type parsed
	/// 0x00001000 - Load direction parsed
	/// 0x00010000 - Pixels parsed
	/// 0x00100000 - Checksum checked
	/// 0x01000000 - EOF reached
	int flags;
} tbir_image_data, *ptbir_image_data;

int tbir_read_check( ptbir_image_data tid, int bitcount);
int tbir_read_nbits( ptbir_image_data tid, int bitcount, int *value);
int tbir_read_magic( ptbir_image_data tid );
int tbir_read_typef( ptbir_image_data tid );
int tbir_read_pixeltype( ptbir_image_data tid );
int tbir_read_loadd( ptbir_image_data tid );
int tbir_read_flags( ptbir_image_data tid );
int tbir_read_header( ptbir_image_data tid );
int tbir_read_width( ptbir_image_data tid );
int tbir_read_height( ptbir_image_data tid);
int tbir_display_img( ptbir_image_data tid);
int tbir_read_pixels( ptbir_image_data tid);
int tbir_read_chksum( ptbir_image_data tid);
#endif
