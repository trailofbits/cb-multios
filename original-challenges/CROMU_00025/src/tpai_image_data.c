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

#include "tpai_image_data.h"

int tpai_read_pixel( ptpai_image_data tid, unsigned int *pixel )
{
	char ascii_index[] = {' ','!','"','#','$','%','&','\'','(',')','*','+',',','-','.','/','0','1','2','3','4','5','6','7','8','9',':',';','<','=','>','?','@','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','[','\\',']','^','_','`','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','{','|','}','~'};
	int value = 0;

	if (pixel == NULL ) {
		return 0;
	}

	if ( tpai_read_nbits( tid, 7, &value ) == 0 ) {
		return 0;
	}

	if ( value > 0x5f || value == 0) {
		return 0;
	}

	value -= 1;

	*pixel = ascii_index[value];

	return 1;	
}

int tpai_display_image( ptpai_image_data tid )
{
	char *image = NULL;
	unsigned int image_length = 0;
	unsigned int pixel = 0;
	unsigned int index = 0;
	unsigned int count = 0;
	unsigned int column = 0;
	unsigned int row = 0;

	if ( tid == NULL ) {
		return 0;
	}

	if ( tpai_read_magic( tid ) == 0 ) {
		return 0;
	}

	if ( tpai_read_width( tid ) == 0 ) {
		return 0;
	}

	if ( tpai_read_height( tid ) == 0 ) {
		return 0;
	}

	if ( tpai_read_loadd( tid, &image_length ) == 0 ) {
		return 0;
	}

	if ( tpai_skip_rsrvd( tid ) == 0 ) {
		return 0;
	}

	if ( tpai_calc_checksum( tid ) == 0 ) {
		return 0;
	}

	image_length = tid->width * tid->height;

	if ( allocate( image_length + 1, 0, (void**)&image) != 0 ) {
		return 0;
	}

	memset( image, ' ', image_length);
	image[image_length] = '\x00';

	while ( tpai_read_pixel( tid, &pixel) != 0 ) {
		switch ( tid->load_direction ) {
			case 0:
				row = count / tid->width;
				column = count % tid->width;				
				break;
			case 1:
				row =  count / tid->width;
				column = (tid->width-1) - (count % tid->width);
				break;
			case 2:
				row = (tid->height-1) - (count/tid->width);
				column = count % tid->width;
				break;
			case 3:
				row = (tid->height-1) - (count/tid->width);
				column = (tid->width-1) - ( count % tid->width);
				break;
			case 4:
				row = count % tid->height;
				column = count / tid->height;
				break;
			case 5:
				row = count % tid->height;
				column = (tid->width-1) - (count / tid->height );
				break;
			case 6:
				row = ( tid->height-1 ) - ( count % tid->height );
				column = count / tid->height;
				break;
			case 7:
				row = ( tid->height-1) - ( count % tid->height );
				column = (tid->width-1) - ( count / tid->height );
				break;
			default:
				deallocate( image, image_length + 1 );
				return 0;
		};

		index = (row * tid->width) + column;

		if ( index > image_length ) {
			printf("[ERROR] Pixel out of bounds\n");
			deallocate( image, image_length + 1 );
			return 0;
		}

		image[index] = pixel;
		count++;
	}

	for (index = 0; index < image_length; index++) {
		if ( index % tid->width == 0 && index != 0 ) {
			printf("\n");
		}

		printf("@c", image[index]);
	}

	printf("\n");
	deallocate(image, image_length + 1 );

	return 1;
}

int tpai_calc_checksum( ptpai_image_data tid )
{
	int shorts = 0;
	short *pixels = NULL;
	short sum = 0;
	int index = 0;
	int tid_sum = 0;

	if ( tid == NULL ) {
		return 0;
	}

	if ( tid->cbit != 0 ) {
		return 0;
	}

	shorts = (tid->max - tid->cbyte);

	if ( shorts & 1 ) {
		return 0;
	}

	shorts /= 2;

	/// Account for the final checksum
	shorts -= 1;

	if ( shorts <= 0 ) {
		return 0;
	}

	pixels = (short*)(tid->buffer + tid->cbyte);

	while ( index < shorts ) {
		sum = sum ^ pixels[index];
		index++;
	}

	if ( pixels[shorts] != sum ) {
		return 0;
	}

	return 1;	
}

int tpai_skip_rsrvd( ptpai_image_data tid )
{	
	int value = 0;

	if ( tpai_read_nbits( tid, 17, &value ) == 0 ) {
		value = 0;
		return value;
	}

	if ( value != 0 ) {
		return 0;
	}

	return 1;
}

int tpai_read_loadd( ptpai_image_data tid, unsigned int *dir)
{
	int value = 0;

	if ( dir == NULL ) {
		return 0;
	}

	if ( tpai_read_nbits( tid, 3, &value ) == 0 ) {
		value &= 0;
		return value;
	}

	*dir = value;
	tid->load_direction = value;

	return 1;
}

int tpai_read_width( ptpai_image_data tid )
{
	int width = 0;

	if ( tpai_read_nbits( tid, 6, &width) == 0 ) {
		return 0;
	}

	tid->width = width;

	return width;
}

int tpai_read_height( ptpai_image_data tid )
{
	int height = 0;

	if ( tpai_read_nbits( tid, 6, &height) == 0 ) {
		return 0;
	}

	tid->height = height;

	return height;
}

int tpai_read_magic( ptpai_image_data tid )
{
	int magic;

	if ( tid == NULL ) {
		return 0;
	}

	if ( tpai_read_nbits( tid, 32, &magic) == 0 ) {
		return 0;
	}

	if ( magic != TPAI_MAGIC ) {
		return 0;
	}

	return 1;
}

int tpai_read_check( ptpai_image_data tid, int bitcount )
{
	int used_bits = 0;

	if ( tid == NULL ) {
		return 0;
	}

	if ( tid->buffer == NULL ) {
		return 0;
	}

	if ( bitcount > 32 ) {
		return 0;
	}

	used_bits = tid->cbit + (tid->cbyte * 8);

	if ( used_bits + bitcount > tid->max * 8 ) {
		return 0;
	}

	return 1;
}

int tpai_read_nbits( ptpai_image_data tid, int bitcount, int *value )
{
	int data = 0;
	char c = '\x00';
	
	if ( tpai_read_check( tid, bitcount ) == 0 ) {
		return 0;
	}

	while ( bitcount > 0 ) {
		c = tid->buffer[ tid->cbyte ];

		c = c >> (7-tid->cbit);
		c &= 1;

		data = (data <<1 ) | c;

		tid->cbit = (tid->cbit + 1 ) % 8;

		if ( !tid->cbit ) {
			tid->cbyte++;
		}

		bitcount--;
	}

	*value = data;
	return 1;
}
