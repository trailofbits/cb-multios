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

#include "tbir_image_data.h"

int tbir_read_chksum( ptbir_image_data tid )
{
	int checksum = 0;

	if ( tid == NULL ) {
		return 0;
	}

	if ( tbir_read_nbits( tid, 32, &checksum) == 0 ) {
		return 0;
	}

	if ( tid->flags & TBIR_PIXELS ) {
		if ( tid->checksum != checksum ) {
			return 0;
		}
	}

	tid->checksum = checksum;
	tid->flags |= TBIR_CHKSUM;

	return 1;
}

int tbir_read_pixels( ptbir_image_data tid )
{
	char one[] = { ' ', '.' };
	char two[] = { ' ', '#', '*', '@' };
	char six[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	char seven[] = {' ','!','"','#','$','%','&','\'','(',')','*','+',',','-','.','/','0','1','2','3','4','5','6','7','8','9',':',';','<','=','>','?','@','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','[','\\',']','^','_','`','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','{','|','}','~'};

	int dword_count;
	int *dwords;
	int sum = 0;

	int pixel_count;
	int index = 0;
	int pixel;
	int bits_to_consume;

	int column;
	int row;
	int count;

	if ( tid == NULL ) {
		return 0;
	}

	if ( !(tid->flags & TBIR_HEADER) || !(tid->flags & TBIR_FLAGS) 
		|| !(tid->flags & TBIR_PIXELT) || !(tid->flags & TBIR_LOADD) ) {
		return 0;
	}

	/// Should be aligned to 8 bits
	if ( tid->cbit != 0 ) {
		return 0;
	}

	tid->flags |= TBIR_PIXELS;
	
	/// Calculate the length of the pixel data. Round to next 32 bit boundary to assume padding
	dword_count = (tid->width * tid->height) * tid->pixel_type;
	bits_to_consume = ( (dword_count + 31) & 0xffffffe0) - dword_count;

	dword_count = (dword_count+bits_to_consume) / 32;

	/// Check boundaries
	if ( (dword_count * 4) + tid->cbyte > tid->max ) {
		printf("Dword count too hight: @d @d @d\n", dword_count*4, tid->cbyte, tid->max);
		return 0;
	}

	dwords = (int*)(tid->buffer + tid->cbyte);

	while ( index < dword_count ) {
		sum = sum ^ dwords[index];
		index++;
	}

	/// If the checksum has already been set then check it
	if ( tid->flags & TBIR_CHKSUM ) {
		if ( sum != tid->checksum ) {
			return 0;
		}
	} else {
		tid->checksum = sum;
	}

	tid->image_length = (tid->height * tid->width);

	if ( allocate( tid->image_length + 1, 0, (void**)&tid->image) != 0 ) {
		return 0;
	}

	memset( tid->image, ' ', tid->image_length);
	tid->image[ tid->image_length ] = '\x00';

	count = 0;
	pixel = 0;

	while ( count < tid->image_length ) {
		if ( tbir_read_nbits( tid, tid->pixel_type, &pixel) == 0 ) {
			deallocate( tid->image, tid->image_length +1);
			tid->image = NULL;
			tid->image_length = 0;
			return 0;
		}

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
				deallocate( tid->image, tid->image_length +1);
				tid->image = NULL;
				tid->image_length = 0;
                                return 0;
		};

		index = (row * tid->width ) + column;

		switch ( tid->pixel_type ) {
			case 1:
				if ( pixel > 1 ) {
					deallocate( tid->image, tid->image_length +1);
					tid->image = NULL;
					tid->image_length = 0;
					return tid->image_length;
				}

				if ( index > tid->image_length + 1 || index < 0 ) {
					deallocate( tid->image, tid->image_length +1);
					tid->image = NULL;
					tid->image_length = 0;
					return tid->image_length;
				}
					
				tid->image[index] = one[pixel];
				break;
			case 2:
				if ( pixel > 3 ) {
					deallocate( tid->image, tid->image_length +1);
					tid->image = NULL;
					tid->image_length = 0;
					return tid->image_length;
				}

				if ( index > tid->image_length + 1 || index < 0) {
					deallocate( tid->image, tid->image_length +1);
					tid->image = NULL;
					tid->image_length = 0;
					return tid->image_length;
				}

				tid->image[index] = two[pixel];
				break;
			case 6:
				if ( pixel > 61 ) {
					deallocate( tid->image, tid->image_length +1);
					/// Bug
#ifdef PATCHED
					tid->image = NULL;
					tid->image_length = 0;
#endif
					return tid->image_length;
				}

				if ( index > tid->image_length + 1 || index < 0) {
					deallocate( tid->image, tid->image_length +1);
					tid->image = NULL;
					tid->image_length = 0;
					return tid->image_length;
				}

				tid->image[index] = six[pixel];
				break;
			case 7:
				if ( pixel > 0x5e ) {
					deallocate( tid->image, tid->image_length +1);
					tid->image = NULL;
					tid->image_length = 0;
					return tid->image_length;
				}

				if ( index > tid->image_length + 1 || index < 0) {
					deallocate( tid->image, tid->image_length +1);
					tid->image = NULL;
					tid->image_length = 0;
					return tid->image_length;
				}

				tid->image[index] = seven[pixel];
				break;
			default:
				printf("[ERROR] Invalid pixel type\n");
				deallocate( tid->image, tid->image_length +1);
				tid->image = NULL;
				tid->image_length = 0;
				return tid->image_length;
				break;
		};

		//printf("Added @c at row @d column: @d type: @d direction: @d\n", tid->image[index], row, column, tid->pixel_type, tid->load_direction);

		count++;
	}

	/// Consume the remainder bits to align to 32 bits
	if ( tbir_read_nbits( tid, bits_to_consume, &index) == 0 ) {
		deallocate( tid->image, tid->image_length +1);
		tid->image = NULL;
		tid->image_length = 0;
		return 0;
	}

	return 1;

}

int tbir_read_flags( ptbir_image_data tid )
{

	if ( tbir_read_pixeltype( tid ) == 0 ) {
		return 0;
	}

	//printf("Pixel type: @d\n", tid->pixel_type);

	if ( tbir_read_loadd( tid ) == 0 ) {
		return 0;
	}

	//printf("Load: @d\n", tid->load_direction);

	tid->flags |= TBIR_FLAGS;
	return 1;
}

int tbir_display_img( ptbir_image_data tid )
{
	int field = 0;

	if ( tid == NULL ) {
		return 0;
	}

	if ( tbir_read_magic( tid ) == 0 ) {
		return 0;
	}

	field = tbir_read_typef( tid );

	while ( field != 0 ) {
		switch ( field ) {
			case 0xaaaa:
				//printf("Header\n");
				if ( tid->flags & TBIR_HEADER ) {
					printf("[ERROR] Only one header\n");
					return 0;
				}

				if ( tbir_read_header( tid ) == 0 ) {
					return 0;
				}
				break;
			case 0xaabb:
				//printf("Flags\n");
				if ( tid->flags & TBIR_FLAGS ) {
					printf("[ERROR] Only one flags field\n");
					return 0;
				}

				if ( tbir_read_flags( tid) == 0 ) {
					return 0;
				}
				break;
			case 0xaacc:
				if ( tid->flags & TBIR_PIXELS ) {
					printf("[ERROR] Only one pixel set\n");
					return 0;
				}

				if ( tbir_read_pixels( tid ) == 0 ) {
					return 0;
				}

				break;
			case 0xaadd:
				if ( tid->flags & TBIR_CHKSUM ) {
					printf("[ERROR] Only one checksum field\n");
					return 0;
				}

				if ( tbir_read_chksum( tid ) == 0 ) {
					return 0;
				}
				break;
			case 0xaaee:
				//printf("End the image\n");
				/// Check to ensure that all fields have been handled
				if ( (tid->flags & TBIR_HEADER) && (tid->flags & TBIR_FLAGS) && ( tid->flags & TBIR_PIXELS) && (tid->flags & TBIR_CHKSUM)) {
					for ( int i = 0; i < tid->image_length; i++ ) {
						if ( i % tid->width == 0 && i != 0 ) {
							printf("\n");
						}
							printf("@c", tid->image[i]);
					}
					printf("\n");
					return 1;
				} else {
					printf("[ERROR] Missing a required tag\n");
					return 0;
				}
			default:
				printf("invalide field\n");
				return 0;
		};

		field = tbir_read_typef( tid );
	}

	return 0;
}

int tbir_read_width( ptbir_image_data tid ) 
{
	int width = 0;

	if ( tid == NULL ) {
		return 0;
	}

	if ( tbir_read_nbits( tid, 8, &width) == 0 ) {
		return 0;
	}

	if ( width > 128 ) {
		return 0;
	}

	tid->width = width;

	//printf("Width: @d\n", tid->width);

	return 1;
}

int tbir_read_height( ptbir_image_data tid )
{
	int retval = 0;

	if ( tid == NULL ) {
		goto end;
	}

	if ( tbir_read_nbits( tid, 8, &(tid->height) ) == 0 ) {
		goto end;
	}

	if ( tid->height > 128 ) {
		goto end;
	}

	//printf("Height: @d\n", tid->height);

	retval = 1;

end:
	return retval;
}

int tbir_read_header( ptbir_image_data tid )
{
	if ( tid == NULL ) {
		return 0;
	}

	if ( tbir_read_width( tid ) == 0 ) {
		return 0;
	}

	if ( tbir_read_height( tid ) == 0 ) {
		return 0;
	}

	tid->flags |= TBIR_HEADER;
	return 1;
}

int tbir_read_loadd( ptbir_image_data tid )
{
	int data = 0;
	int retval = 0;

	if ( tbir_read_nbits( tid, 4, &data ) == 0 ) {
		goto end;
	}

	/// Only 0-7 are valid load direction flags
	if ( data > 8 ) {
		goto end;
	}

	tid->load_direction = data;
	tid->flags |= TBIR_LOADD;

	retval = 1;
end:
	return retval;
}

int tbir_read_pixeltype( ptbir_image_data tid )
{
	int pt = 0;
	int value = 0;

	if ( tid == NULL ) {
		goto end;
	}

	if ( tbir_read_nbits( tid, 4, &value) == 0 ) {
		goto end;
	}

	/// only 1,2,6,7 are valid values
	if ( value > 7 || ( value > 2 && value < 6 ) || value == 0 ) {
		goto end;
	}

	tid->pixel_type = value;
	tid->flags |= TBIR_PIXELT;

	pt = 1;
end:
	return pt;
}

int tbir_read_typef( ptbir_image_data tid )
{
	int type;

	if ( tbir_read_nbits( tid, 16, &type) == 0 ) {
		printf("da bits failed\n");
		return 0;
	}

	switch (type) {
		case 0xaaaa:
		case 0xaabb:
		case 0xaacc:
		case 0xaadd:
		case 0xaaee:
			return type;
		default:
			printf("wrong one\n");
			return 0;
	};

	printf("fail\n");
	return 0;
}

int tbir_read_check( ptbir_image_data tid, int bitcount )
{
	int success = 0;
	int maxbits = 0;
	int currentbits = 0;
	int bitsleft = 0;

	if ( tid == NULL ) {
		goto end;
	}

	if (tid->buffer == NULL ) {
		goto end;
	}

	if ( bitcount > 32 ) {
		goto end;
	}

	maxbits = tid->max * 8;
	currentbits = (tid->cbyte * 8 ) + tid->cbit;
	bitsleft = maxbits - currentbits;

	if ( bitcount <= bitsleft ) {
		success = 1;
	}

end:
	return success;
}

int tbir_read_nbits( ptbir_image_data tid, int bitcount, int *value )
{
	int data;
	int bitsleft;

	if ( tid == NULL ) {
		return 0;
	}

	if ( tbir_read_check( tid, bitcount ) == 0 ) {
		return 0;
	}

	bitsleft = 8 - tid->cbit;

	if ( bitsleft > bitcount ) {
		data = tid->buffer[tid->cbyte];
		data = data >> (bitsleft - bitcount);
		data = data & (expi(2, bitcount)-1);

		tid->cbit += bitcount;

		*value = data;
		return 1;
	}

	data = 0;

	while ( bitcount ) {
		data = data << 1;
		data = data | ((tid->buffer[tid->cbyte] >> (7-tid->cbit)) & 0x1);
		
		tid->cbyte += (tid->cbit + 1) / 8;
		tid->cbit = ( tid->cbit + 1 ) % 8;
		bitcount -= 1;
	}

	*value = data;

	return 1;
}

int tbir_read_magic( ptbir_image_data tid )
{
	int magic;

	if ( tbir_read_nbits( tid, 32, &magic) == 0 ) {
		return 0;
	}

	if ( magic != TBIR_MAGIC ) {
		return 0;
	}

	return 1;
}
