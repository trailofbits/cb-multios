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

#include "fpai_image_data.h"

int fpai_add_pixel( pfpai_image_data fid, char *image, int x, int y, char pixel)
{
	int index = 0;
	int midx;
	int midy;
	int base;

	if ( fid == NULL ) {
		return 0;
	}

	if ( !image ) {
		return 0;
	}

	/// Calculate the index based upon the origin location
	switch( fid->axist ) {
		case 1:
			index = ((-y)*fid->xlen) + x;
			break;
		case 2:
                	index = ((-y)*fid->xlen) + ( (fid->xlen-1) + x );
			break;
		case 3:
                	index = (((fid->ylen-1)-y)*fid->xlen) + x;
			break;
		case 4:
                	index = (((fid->ylen-1)-y)*fid->xlen) + ( (fid->xlen-1) + x );
			break;
		case 7:
                	midx = fid->xlen/2;
                	midy = fid->ylen/2;

                	base = (midy*fid->xlen) + midx;
                	index = base + (-y * fid->xlen) + x;
			break;
		default:
			return 0;
	};

	/// The index should not go beyond width * height	
	if ( index > fid->xlen * fid->ylen ) {
		return 0;
	}

	image[index] = pixel;
	//printf("index: @d\n", index);
	return 1;
}

int fpai_display_img( pfpai_image_data fid )
{
	int x;
	int y;
	int pchar;
	short ts;
	char *image;

	int minx = 0;
        int miny = 0;
        int maxy = 0;
        int maxx = 0;

	char ascii_index[] = {' ','!','"','#','$','%','&','\'','(',')','*','+',',','-','.','/','0','1','2','3','4','5','6','7','8','9',':',';','<','=','>','?','@','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','[','\\',']','^','_','`','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','{','|','}','~'};

	if ( fid == NULL ) {
		return 0;
	}

	if ( fpai_read_magic( fid ) == 0 ) {
		return 0;
	}

	if ( fpai_read_xaxis( fid ) == 0 ) {
		return 0;
	}

	if ( fpai_read_yaxis( fid ) == 0 ) {
		return 0;
	}

	if ( fpai_read_axist( fid ) == 0 ) {
		return 0;
	}

	if ( fpai_read_cksum( fid, &ts) == 0 ) {
		return 0;
	}

	/// Skip reserve bit
	if ( fpai_read_nbits( fid, 1, &x ) == 0 ) {
		return 0;
	}

	if ( fpai_calc_cksum( fid ) == 0 ) {
		printf("[ERROR] Checksum failed\n");
		return 0;
	}

        switch (fid->axist) {
                case 1:
                        minx = 0;
                        miny = -fid->ylen + 1;
                        maxx = fid->xlen - 1;
                        maxy = 0;
                        break;
                case 2:
                        minx = -fid->xlen + 1;
                        miny = -fid->ylen + 1;
                        maxx = 0;
                        maxy = 0;
                        break;
                case 3:
                        minx = 0;
                        miny = 0;
                        maxx = fid->xlen - 1;
                        maxy = fid->ylen - 1;
                        break;
                case 4:
                        minx = -fid->xlen + 1;
                        miny = 0;
                        maxx = 0;
                        maxy = fid->ylen - 1;
                        break;
                case 7:
                        minx = -fid->xlen/2;
                        maxy = fid->ylen/2;
                        maxx = (fid->xlen/2) - ((fid->xlen+1)%2);
                        miny = -( (fid->ylen/2) - ((fid->ylen+1)%2));
                        break;
                default:
                        return 0;
                        break;
        };


	int image_length = fid->xlen * fid->ylen;

	if ( allocate( image_length + 1, 0, (void**)&image) != 0 ) {
		return 0;
	}

	memset( image, ' ', image_length );
	image[image_length] = '\x00';

	//printf("minx: @d maxx: @d miny: @d maxy: @d\n", minx, maxx, miny, maxy);
	//printf("x: @d y: @d axis: @d csum: @d\n", fid->xlen, fid->ylen, fid->axist, fid->checksum);

	while ( fpai_read_pixel( fid, &x, &y, &pchar) != 0 ) {
		//printf("x: @d y: @d pchar: @c\n", x,y,pchar);
		if ( x < minx || x > maxx ) {
			printf("X out of bounds\n");
			return 0;
		}

		if ( y < miny || y > maxy ) {
			printf("Y out of bounds\n");
			return 0;
		}

		if ( fpai_add_pixel( fid, image, x, y, (char)pchar) == 0 ) {
			printf("pixel placement failed\n");
			return 0;
		}
	}

        for (int i = 0; i < image_length; i++) {
                if (i%fid->xlen == 0 && i != 0) {
                        printf("\n");
                }

                printf("@c", image[i]);
        }

	printf("\n");
	return 1;

}

int fpai_read_check( pfpai_image_data fid, int bitcount )
{
	int total_bits;
	int bits_read;
	int bits_left;

	if ( fid == NULL ) {
		return 0;
	}

	if ( fid->buffer == NULL ) {
		return 0;
	}

	total_bits = fid->max * 8;
	bits_read = fid->cbyte * 8;
	bits_read += fid->cbit;

	bits_left = total_bits - bits_read;

	if ( bitcount <= bits_left ) {
		return 1;
	}

	return 0;
}

int fpai_read_nbits( pfpai_image_data fid, int bitcount, int *value)
{
	int bits;

	if ( bitcount > 32 ) {
		return 0;
	}

	if ( !fid || !value) {
		return 0;
	}

	bits &= 0;

	while ( bitcount ) {
		bits = (bits << 1) | ((fid->buffer[ fid->cbyte ] >> (7-fid->cbit)) & 0x1);

		fid->cbit = (fid->cbit +1) % 8;

		if ( !fid->cbit ) {
			fid->cbyte++;
		}

		bitcount--;
	}

	*value = bits;

	return 1;
}

int fpai_read_magic( pfpai_image_data fid )
{
	int magic = 0;

	if ( fid == NULL ) {
		return magic;
	}

	if ( !fpai_read_check( fid, 32 ) ) {
		return magic;
	}

	if ( !fpai_read_nbits( fid, 32, &magic) ) {
		magic = 0;
		return magic;
	}

	if ( ((magic >>24) & 0xff) != 0xde ) {
		return 0;
	}

	if ( ((magic>>16) & 0xff) != 0xb6 ) {
		return 0;
	}

	if ( ((magic>>8) & 0xff) != 0xd9 ) {
		return 0;
	}

	if ( (magic&0xff) != 0x55 ) {
		return 0;
	}

	return 1;
}

int fpai_read_xaxis( pfpai_image_data fid )
{
	int xaxis;

	if ( !fpai_read_check( fid, 6 ) ) {
		return 0;
	}

	if ( !fpai_read_nbits( fid, 6, &xaxis) ) {
		return 0;
	}

	fid->xlen = xaxis;

	return xaxis;
}

int fpai_read_yaxis( pfpai_image_data fid )
{
	int yaxis = 0;

	if ( !fid ) {
		return 0;
	}

	if ( !fpai_read_check( fid, 6 ) ) {
		return yaxis;
	}

	if ( !fpai_read_nbits( fid, 6, &yaxis) ) {
		return 0;
	}

	fid->ylen = yaxis;

	return yaxis;
}

int fpai_read_axist( pfpai_image_data fid )
{
	int axist;

	if ( fid == NULL ) {
		return 0;
	}

	if ( !fpai_read_check( fid, 3 ) ) {
		return 0;
	}

	if ( !fpai_read_nbits( fid, 3, &axist ) ) {
		return 0;
	}

	if ( axist == 5 || axist == 6 || axist == 0 ) {
		return 0;
	}

	fid->axist = axist;
	
	return axist;
}

int fpai_read_cksum( pfpai_image_data fid, short *cksum)
{
	int checksum = 0;

	if ( !fpai_read_check(fid, 16) ) {
		return 0;
	}

	if ( !fpai_read_nbits( fid, 16, &checksum) ) {
		return 0;
	}

	fid->checksum = (int)checksum;

	return 1;
}

int fpai_calc_cksum( pfpai_image_data fid )
{
	short *items = NULL;
	short cksum = 0;
	int total = 0;
	int index = 0;

	if ( fid == NULL ) {
		return 0;
	}

	/// The bit index must start at 0
	if ( fid->cbit ) {
		return 0;
	}

	/// The remaining byte count must be a multiple of 16 bits
	total = fid->max - fid->cbyte;

	/// If it is not evenly divisible by 2 then it is not a multiple of 16 bits
	if ( total % 2 ) {
		return 0;
	}

	items = (short*)(fid->buffer+fid->cbyte);

	total /= 2;

	while ( index < total ) {
		cksum += items[index];
		index++;
	}

	if ( cksum != fid->checksum ) {
		printf("[ERROR] Checksum failed\n");
		return 0;
	}

	return 1;
}

int fpai_read_pixel( pfpai_image_data fid, int *x, int*y, int*pixel)
{
	int signx;
	int px;
	int signy;
	int py;
	int pc;

	if ( fid == NULL ) {
		return 0;
	}

	if ( fpai_read_check( fid, 1 ) == 0 ) {
		return 0;
	}

	if ( !fpai_read_nbits( fid, 1, &signx) ) {
		return 0;
	}

	if ( fpai_read_check( fid, 6 ) == 0 ) {
		return 0;
	}

	if ( !fpai_read_nbits( fid, 6, &px) ) {
		return 0;
	}

	if ( fpai_read_check( fid, 1 ) == 0 ) {
		return 0;
	}

	if ( !fpai_read_nbits( fid, 1, &signy) ) {
		return 0;
	}

	if ( fpai_read_check( fid, 6 ) == 0 ) {
		return 0;
	}

	if ( !fpai_read_nbits( fid, 6, &py) ) {
		return 0;
	}

	if ( !fpai_read_check( fid, 7 )) {
		return 0;
	}

	if ( !fpai_read_nbits( fid, 7, &pc ) ) {
		return 0;
	}

	if ( pc > 0x5e ) {
		return 0;
	}

	if ( signx ) {
		px *= -1;
	}

	if ( signy ) {
		py *= -1;
	}

	*x = px;
	*y = py;
	*pixel = pc+0x20;

	return 1;
}

