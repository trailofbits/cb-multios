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

#include "fpti_image_data.h"

int fpti_add_pixel( pfpti_image_data fid, int x, int y, char *image, int xlen, int ylen, int at)
{
	int pixel_index = 0;
	char c = 0;
	
	if ( fid == NULL ) {
		return 0;
	}

	if ( image == NULL ) {
		return 0;
	}

	if ( at == 1 ) {
		pixel_index = ((-y)*xlen) + x;
	} else if ( at == 2 ) {
		pixel_index = ((-y)*xlen) + ( (xlen-1) + x );
	} else if ( at == 3 ) {
		pixel_index = (((ylen-1)-y)*xlen) + x;
	} else if ( at == 4 ) {
		pixel_index = (((ylen-1)-y)*xlen) + ( (xlen-1) + x );
	} else if ( at == 7 ) {
		int midx = xlen/2;
		int midy = ylen/2;

		int base = (midy*xlen) + midx;
		pixel_index = base + (-y * xlen) + x;
	} else {
		return 0;
	}

	if ( fid->pixel == 0 ) {
		c = '.';
	} else if ( fid->pixel == 1 ) {
		c = '*';
	} else if ( fid->pixel == 2 ) {
		c = '#';
	} else if ( fid->pixel == 3 ) {
		c = '+';
	}

	if ( pixel_index > xlen * ylen ) {
		printf("[ERROR] Pixel beyond image: @d > @d\n", pixel_index, xlen*ylen);
		return 0;
	}

	image[ pixel_index ] = c;

	return 1;
}

int fpti_display_img( pfpti_image_data fid )
{
	int xlen = 0;
	int ylen = 0;
	int ptype = 0;
	int axist = 0;

	int minx = 0;
	int miny = 0;
	int maxy = 0;
	int maxx = 0;

	int x = 0;
	int y = 0;

	char *image = NULL;
	int image_length = 0;

	if ( fid == NULL ) {
		return 0;
	}

	if ( fpti_read_magic( fid ) == 0 ) {
		//printf("magic failed\n");
		return 0;
	}

	xlen = fpti_read_xaxis( fid );

	if ( !xlen ) {
		//printf("xlen fail\n");
		return xlen;
	}

	ylen = fpti_read_yaxis( fid );

	if ( !ylen ) {
		return ylen;
	}

	//printf("Xlen: @d Ylen: @d\n", xlen, ylen);

	if ( fpti_read_ptype( fid, &ptype) == 0 ) {
		ptype = 0;
		return ptype;
	}

	axist = fpti_read_axist( fid );

	//printf("Axis: @d\n", axist);

	if ( !axist ) {
		return axist;
	}

	if ( fpti_read_check( fid, 15 ) ==0 ) {
		return 0;
	}

	if ( fpti_read_nbits( fid, 15, &x) == 0 ) {
		return 0;
	}

	switch (axist) {
		case 1:
			minx = 0;
			miny = -ylen + 1;
			maxx = xlen - 1;
			maxy = 0;
			break;
		case 2:
			minx = -xlen + 1;
			miny = -ylen + 1;
			maxx = 0;
			maxy = 0;
			break;
		case 3:
			minx = 0;
			miny = 0;
			maxx = xlen - 1;
			maxy = ylen - 1;
			break;
		case 4:
			minx = -xlen + 1;
			miny = 0;
			maxx = 0;
			maxy = ylen - 1;
			break;
		case 7:
			minx = -xlen/2;
			maxy = ylen/2;
			maxx = (xlen/2) - ((xlen+1)%2);
			miny = -((ylen/2) - ((ylen+1)%2));
			break;
		default:
			printf("[ERROR] Invalid FPTI Axis Type\n");
			return 0;
			break;
	};		

	//printf("maxx: @d minx: @d maxy: @d miny: @d\n", maxx, minx, maxy, miny);

	image_length = xlen * ylen;

	if ( allocate( image_length + 1, 0, (void**)&image) != 0 ) {
		return 0;
	}

	memset( image, ' ', image_length);
	image[image_length] = '\x00';

	while ( fpti_read_pixel( fid, &x, &y) ) {
		//printf("@d, @d\n", x, y);

		if ( x < minx || x > maxx ) {
			printf("X out of bounds: @d\n", x );
			return 0;
		}

		/// bug here
#ifdef PATCHED
		if ( y < miny || y > maxy ) {
#else
		if ( y < miny && y > maxy ) {
#endif
			printf("Y out of bounds: @d\n", y );
			return 0;
		}

		if ( fpti_add_pixel( fid, x, y, image, xlen, ylen, axist) == 0 ) {
			return 0;
		}
	}
	
        for (int i = 0; i < image_length; i++) {
                if (i%xlen == 0 && i != 0) {
                        printf("\n");
                }

                printf("@c", image[i]);
        }

	printf("\n");
	return 1;
}

int fpti_read_pixel( pfpti_image_data fid, int *x, int *y )
{
	int retval = 0;
	int py = 0;
	int px = 0;

	int xsign = 0;
	int ysign = 0;

	if ( fid == NULL ) {
		goto end;
	}

	if ( x == NULL || y == NULL ) {
		goto end;
	}

	if ( fpti_read_check( fid, 14 ) == 0 ) {
		goto end;
	}

	if ( fpti_read_nbits( fid, 1, &xsign) == 0 ) {
		goto end;
	}

	if ( fpti_read_nbits( fid, 6, &px ) == 0 ) {
		goto end;
	}

	if ( fpti_read_nbits( fid, 1, &ysign) == 0 ) {
		goto end;
	}

	if ( fpti_read_nbits( fid, 6, &py ) == 0 ) {
		goto end;
	}

	if ( xsign == 1 ) {
		px *= -1;
	}

	if ( ysign == 1 ) {
		py *= -1;
	}

	*x = px;
	*y = py;

	retval = 1;
end:
	return retval;
}

int fpti_read_axist( pfpti_image_data fid )
{
	int retval = 0;

	if ( fid == NULL ) {
		goto end;
	}

	retval = fpti_read_check( fid, 3 );

	if ( !retval ) {
		goto end;
	}

	if ( fpti_read_nbits( fid, 3, &retval ) == 0 ) {
		retval = 0;
		goto end;
	}

end:
	return retval;

}

int fpti_read_ptype( pfpti_image_data fid, int*ptype )
{
	int t = 0;
	int retval = 0;

	if ( fid == NULL ) {
		return 0;
	}

	retval = fpti_read_check( fid, 2 );

	if ( !retval ) {
		return retval;
	}

	retval = fpti_read_nbits( fid, 2, &t);

	if ( !retval) {
		return retval;
	}

	*ptype = t;

	/// Set the pixel for the image
	fid->pixel = t;

	return retval;
}

int fpti_read_xaxis( pfpti_image_data fid )
{
	int value = 0;

	if ( fid == NULL ) {
		goto end;
	}

	if ( fpti_read_check( fid, 6 ) == 0 ) {
		goto end;
	}

	if ( fpti_read_nbits( fid, 6, &value) == 0 ) {
		value = 0;
		goto end;
	}

end:
	return value;
}

int fpti_read_yaxis( pfpti_image_data fid )
{
	int value = 0;

	if ( fid == NULL ) {
		goto end;
	}

	if ( fpti_read_check(fid, 6 ) == 0 ) {
		goto end;
	}

	if ( fpti_read_nbits( fid, 6, &value) == 0 ) {
		value = 0;
		goto end;
	}

end:
	return value;
}

int fpti_read_magic( pfpti_image_data fid )
{
	int magic = 0;

	if ( fpti_read_check( fid, 32 ) == 0 ) {
		return 0;
	}

	if ( fpti_read_nbits( fid, 32, &magic) == 0 ) {
		return 0;
	}

	if ( magic != FPTI_MAGIC ) {
		return 0;
	}

	return 1;
}

int fpti_read_check( pfpti_image_data fid, int bitcount)
{
	int total_bits = 0;
	int end_bits = 0;

	if ( fid == NULL ) {
		return 0;
	}

	if ( fid->buffer == NULL ) {
		//printf("null buff\n");
		return 0;
	}

	if ( bitcount > 32 ) {
		return 0;
	}

	total_bits = (fid->max * 8);
	end_bits = (fid->cbyte * 8) + fid->cbit + bitcount;

	if (total_bits < end_bits ) {
		//printf("t: @d e: @d\n", total_bits, end_bits);
		return 0;
	}

	return 1;
}

int fpti_read_nbits( pfpti_image_data fid, int bitcount, int *value)
{
	int index = 0;
	int data = 0;
	int tcb = 0;

	if ( value == NULL ) {
		return 0;
	}

	if ( bitcount > 32 ) {
		return 0;
	}

	if ( fpti_read_check( fid, bitcount ) == 0 ) {
		return 0;
	}

	/// See if enough bits are available to satisfy the request
	tcb = 8-fid->cbit;

	if ( tcb > bitcount ) {
		data = (fid->buffer[ fid->cbyte ] >> (tcb-bitcount)) & (expi(2, bitcount) - 1);
		fid->cbit = (fid->cbit + bitcount) % 8;

		if (fid->cbit == 0 ) {
			fid->cbyte++;
		}

		*value = data;
		return 1;
	}

	while ( index < bitcount ) {
		tcb = fid->buffer[ fid->cbyte ];

		tcb = (tcb>>(7-fid->cbit)) & 1;
		data = (data<<1) | tcb;

		fid->cbit = (fid->cbit+1)%8;

		if ( fid->cbit == 0 ) {
			fid->cbyte++;
		}

		index++;
	}

	*value = data;
	return 1;
}
