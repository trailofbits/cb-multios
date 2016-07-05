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

#include "rpti_image_data.h"

int rpti_add_pixel( char *image, int nextx, int nexty, int axis_type, int xlen, int ylen )
{
	int actual_index = 0;
	int midx = xlen/2;
	int midy = ylen/2;

	int base = 0;

	if (image == NULL ) {
		return 0;
	}

	switch (axis_type) {
		case 1:	/// upper left
			actual_index = ((nexty*-1)*xlen) + nextx;
			break;
		case 2: /// upper right
			actual_index = ((nexty*-1)*xlen) + ( (xlen-1) + nextx );
			break;
		case 3: /// lower left
			actual_index = (((ylen-1)-nexty)*xlen) + nextx;
			break;
		case 4: /// lower right
			actual_index = (((ylen-1)-nexty)*xlen) + ( (xlen-1) + nextx);
			break;
		case 7: /// midpoint
			base = (midy*xlen) + midx;
			actual_index = base + (-nexty * xlen ) + nextx;
			break;
		default:
			return 0;
	};

	if ( actual_index > xlen * ylen ) {
		printf("[ERROR] Pixel beyond image border\n");
		return 0;
	}

	image[actual_index] = '.';
	
	return 1;
}

/**
 * Displays the provided image to the screen
 * @param rid Pointer to an rpti image structure
 * @return Returns 0 on success, 1 on failure
 **/
int rpti_display_img( prpti_image_data rid)
{
	char *image = NULL;
	int image_length = 0;

	int axis_type = 0;
	int xlen = 0;
	int ylen = 0;
	int current_x = 0;
	int current_y = 0;
	int maxx = 0;
	int maxy = 0;
	int minx = 0;
	int miny = 0;

	int pixel = 0;
	int px = 0;
	int py = 0;

	int nextx = 0;
	int nexty = 0;

	/// Check the magic
	if ( rpti_read_magic( rid ) == 0 ) {
		printf("RPTI magic fail\n");
		return 0;
	}

	xlen = rpti_read_xaxis( rid );

	if ( xlen == 0 ) {
		printf("rpti xlen fail\n");
		return 0;
	}

	//printf("Xlen: @d\n", xlen);

	ylen = rpti_read_yaxis( rid );

	if ( ylen == 0 ) {
		printf("rpti ylen fail\n");
		return 0;
	}

	//printf("Ylen: @d\n", ylen);

	if (  rpti_read_initx( rid , &current_x ) == 0 ) {
		printf("rpti initx fail\n");
		return 0;
	}
	//printf("Initx: @d\n", current_x);

	if( rpti_read_inity( rid , &current_y ) == 0 ) {
		printf("rpti inity fail\n");
		return 0;
	}

	//printf("Inity: @d\n", current_y);
	axis_type = rpti_read_axist( rid );

	if ( axis_type == 0 ) {
		printf("axis type fail\n");
		return 0;
	}

	/// Skip the reserved bits
	if ( rpti_inc_index( rid, 3 ) == 0 ) {
		return 0;
	}

	//printf("Axistype: @d\n", axis_type);
	/// Calculate the x/y max/min
	switch (axis_type) {
		case 1:
			minx = 0;
			miny = -ylen + 1;
			maxx = xlen-1;
			maxy = 0;
			break;
		case 2:
			minx = -xlen+1;
			miny = -ylen+1;
			maxx = 0;
			maxy = 0;
			break;
		case 3:
			minx = 0;
			miny = 0;
			maxx = xlen-1;
			maxy = ylen-1;
			break;
		case 4:
			minx = -xlen+1;
			miny = 0;
			maxx = 0;
			maxy = ylen-1;
			break;
		case 7:
			maxx = (xlen/2) - ((xlen+1)%2);
			minx = -xlen/2;

			miny = -((ylen/2) - ((ylen+1)%2));
			maxy = ylen/2;
			break;
		default:
			printf("type switch fail\n");
			return 0;
			break;
	};

	/// Calculate image length;
	image_length = (xlen) * (ylen);

	/// Allocate image buffer
	if ( allocate( image_length+1, 0, (void**)&image) != 0 ) {
		return 0;
	}

	/// Set all empty pixels to spaces
	memset( image, ' ', image_length );
	
	/// End the image with a NULL byte
	image[image_length] = '\x00';

	//printf(" maxx: @d maxy: @d\nminx: @d miny: @d\n", maxx, maxy, minx, miny);

	while ( rpti_read_pixel( rid, &pixel) != 0 ) {
		px = pixel >> 7;
		py = pixel & 0x7f;

		if ( px & 0x40 ) {
			px = (px & 0x3f) * -1;
		}

		if ( py & 0x40 ) {
			py = (py & 0x3f) * -1;
		}

		nextx = current_x + px;
		nexty = current_y + py;

		//printf("Current x: @d Current y: @d\n", current_x, current_y);
		//printf("Next x: @d Next y: @d\n", nextx, nexty);
		if (nextx < minx || nextx > maxx ) {
			printf("X out of bounds\n");
			deallocate( image, image_length + 1 );
			return 0;
		}

		if ( nexty < miny || nexty > maxy ) {
			printf("Y out of bounds\n");
			deallocate( image, image_length + 1 );
			return 0;
		}

		if ( rpti_add_pixel( image, nextx, nexty, axis_type, xlen, ylen ) == 0 ) {
			deallocate( image, image_length + 1 );
			printf("add pixel fail\n");
			return 0;
		}

		current_x = nextx;
		current_y = nexty;

	}

	for (int i = 0; i < image_length; i++) {
		if (i%xlen == 0 && i != 0) {
			printf("\n");
		}

		printf("@c", image[i]);
	}

	deallocate( image, image_length + 1 );
	printf("\n");
	return 1;
}

/**
 * Reads the requested number of bits upto a max of 32
 * @param rid Pointer to an rpti image structure
 * @param bit_count Number of bits to read
 * @param out_data Pointer to an integer to receive the data
 * @return Returns the data in the outdata pointer 0 on failure, 1 on success.
 **/ 
int rpti_read_bits( prpti_image_data rid, int bit_count, int *out_data )
{
	int returnData = 0;
	char bit = 0;

	if ( out_data == NULL ) {
		return 0;
	}

	if ( bit_count > 32 ) {
		return 0;
	}

	if ( rpti_read_check( rid, bit_count) == 0 ) {
		return 0;
	}

	while ( bit_count ) {
		bit = rid->buffer[ rid->cbyte ];

		/// Copy the current bit
		bit = (bit >> (7-rid->cbit)) & 1;

		/// Increment the counter
		rid->cbit = (rid->cbit+1) % 8;

		/// Check for a byte loop
		if (rid->cbit == 0 ) {
			rid->cbyte++;
		}

		returnData = (returnData<<1) | bit;
		bit_count--;
	}

	*out_data = returnData;

	return 1;
}

/**
 * Increments the index bits
 * @param rid Pointer to an rpti image structure
 * @param bit_count Number of bits to be incremented
 * @return Returns 0 if the increment goes beyond the bounds 1 on success
 **/
int rpti_inc_index( prpti_image_data rid, int bit_count )
{
	int index = 0;

	if ( rid == NULL ) {
		return 0;
	}

	if (rid->buffer == NULL ) {
		return 0;
	}

	if ( rpti_read_check( rid, bit_count ) == 0 ) {
		return 0;
	}

	/// First add the bytes
	index = (rid->cbit + bit_count) / 8;

	if ( index > 0 ) {
		rid->cbyte += index;
	}

	/// Now add the bits
	rid->cbit = (rid->cbit + bit_count) % 8;

	return 1;
}

/**
 * Determines if the read is valid
 * @param rid Pointer ot an rpti image structure
 * @param bit_count Number of bits requested to be read
 * @return Returns 0 if the read cannot be satisfied 1 otherwise
 **/
int rpti_read_check( prpti_image_data rid, int bit_count )
{
	if ( rid == NULL ) {
		return 0;
	}

	if ( rid->buffer == NULL ) {
		return 0;
	}

	if ( (rid->max*8) - ((rid->cbyte*8)+rid->cbit) >= bit_count ) {
		return 1;
	}

	return 0;	
}

/**
 * Reads 32 bit magic. If it is not the start of the image data then error
 * Expected magic for RPTI is 0xc35109d3
 * @param rid Pointer to an rpti image structure
 * @return Returns 0 on failure 1 on success
 */
int rpti_read_magic( prpti_image_data rid )
{
	int magic = 0;

	if ( rid == NULL ) {
		return 0;
	}
	
	if (rid->buffer == NULL ) {
		return 0;
	}

	/// It must be the start of the image
	if ( rid->cbyte != 0 || rid->cbit != 0 ) {
		return 0;
	}

	/// Need at least 4 bytes for the magic
	if ( rpti_read_check( rid, 32 ) == 0 ) {
		return 0;
	}

	memcpy( &magic, rid->buffer, 4 );

	if ( magic != RPTI_MAGIC ) {
		return 0;
	}

	/// Skip the 4 byte magic
	if ( rpti_inc_index( rid, 32 ) == 0 ) {
		return 0;
	}

	return 1;
}

/**
 * Read the 6 bit X axis total length
 * @param Pointer to an rpti structure
 * @return Returns the 6 bits of the x axis length. 0 on failure
 **/
int rpti_read_xaxis( prpti_image_data rid )
{
	int axis = 0;

	if ( rid == NULL ) {
		return 0;
	}

	if ( rid->buffer == NULL ) {
		return 0;
	}

	if ( rpti_read_bits( rid, 6, &axis ) == 0 ) {
		return 0;
	}

	return axis;
}

int rpti_read_yaxis( prpti_image_data rid )
{
	int axis = 0;

	if ( rpti_read_bits( rid, 6, &axis ) == 0 ) {
		return 0;
	}

	return axis;
}

int rpti_read_initx( prpti_image_data rid, int *out_data )
{
	int initx = 0;
	int sign = 0;

	if ( rid == NULL ) {
		return 0;
	}

	if ( rid->buffer == NULL ) {
		return 0;
	}

	if ( out_data == NULL ) {
		return 0;
	}

	if ( rpti_read_bits( rid, 1, &sign) == 0 ) {
		return 0;
	}

	if ( rpti_read_bits( rid, 6, &initx) == 0 ) {
		return 0;
	}

	if ( sign == 1 ) {
		initx *= -1;
	}

	*out_data = initx;

	return 1;
}

int rpti_read_inity( prpti_image_data rid, int *out_data )
{
	int inity = 0;
	int sign = 0;

	if ( rid == NULL ) {
		return 0;
	}

	if ( rid->buffer == NULL ) {
		return 0;
	}

	if (out_data == NULL ) {
		return 0;
	}

	/// Read the sign bit
	if ( rpti_read_bits( rid, 1, &sign) == 0 ) {
		return 0;
	}

	if ( rpti_read_bits( rid, 6, &inity) == 0 ) {
		return 0;
	}

	if ( sign == 1 ) {
		inity *= -1;
	}

	*out_data = inity;

	return 1;
}

int rpti_read_axist( prpti_image_data rid )
{
	int axis_type = 0;

	if ( rid == NULL ) {
		goto end;
	}

	if ( rid->buffer == NULL ) {
		goto end;
	}

	if ( rpti_read_bits( rid, 3, &axis_type) == 0 ) {
		axis_type = 0;
		goto end;
	}

	/// 5 and 6 are not valid axis types
	if ( axis_type > 4 && axis_type < 7 ) {
		axis_type = 0;
	}

end:
	return axis_type;
}

int rpti_read_pixel( prpti_image_data rid, int *out_data )
{
	int xpixel = 0;
	int ypixel = 0;
	int final = 0;

	if ( rid == NULL ) {
		return 0;
	}

	if ( rid->buffer == NULL ) {
		return 0;
	}

	if ( out_data == NULL ) {
		return 0;
	}

	if ( rpti_read_bits( rid, 7, &xpixel) == 0 ) {
		return 0;
	}

	if ( rpti_read_bits( rid, 7, &ypixel) == 0 ) {
		return 0;
	}

	final = (xpixel << 7) | ypixel;

	*out_data = final;

	return 1;
}
