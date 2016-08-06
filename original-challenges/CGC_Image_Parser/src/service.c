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

#include "service.h"

/**
 * Reads two bytes from a user which specify length to read.
 * If that length is less than 4096 then allocate a buffer and
 * read the specified size.
 * @param data Pointer to a char *that will receive the newly allocated buffer. Null on failure
 * @return Returns the length of the new buffer. Zero length on failure and the pointer is set to NULL
 **/
int readData( char **data )
{
	int readLength = 0;
	size_t bytesRead = 0;

	char *nd = NULL;

	if ( data == NULL ) {
		return 0;
	}

	///  Receive the 2 byte file size. Max of 2048
	if ( receive( 0, &readLength, 2, &bytesRead ) != 0 ) {
		return 0;
	}

	if ( readLength > 2048 ) {
		return 0;
	}

	if ( allocate( readLength, 0, (void**)&nd ) != 0 ) {
		return 0;
	}

	if ( receive( 0, nd, readLength, &bytesRead ) != 0 ) {
		return 0;
	}

	if ( bytesRead != readLength ) {
		return 0;
	}

	*data = nd;

	return bytesRead;
}

int selectRenderer( pimage_meta img )
{
	int magic;
	char *image;
	int image_length;
	fpai_image_data fpai;
	fpti_image_data fpti;
	rpti_image_data rpti;
	tbir_image_data tbir;
	tpai_image_data tpai;

	if ( img == NULL ) {
		return 0;
	}

	if ( img->data == NULL ) {
		return 0;
	}

	if ( img->len < 4 ) {
		return 0;
	}

	image = img->data;
	image_length = img->len;

	memcpy( &magic, image, 4 );

	if ( magic == FPAI_MAGIC ) {
		memset( &fpai, 0, sizeof(tpai_image_data) );
		fpai.buffer = image;
		fpai.max = image_length;

		if ( fpai_display_img( &fpai ) == 0 ) {
			return 0;
		}
	} else if ( magic == 0x85eec724 ) { /// FPTI 
		memset( &fpti, 0, sizeof(fpti_image_data) );
		fpti.buffer = image;
		fpti.max = image_length;

		if ( fpti_display_img( &fpti ) == 0 ) {
			return 0;
		}
	} else if ( magic == RPTI_MAGIC ) {
		memset( &rpti, 0, sizeof(rpti_image_data) );
		rpti.buffer = image;
		rpti.max = image_length;

		if ( rpti_display_img( &rpti ) == 0 ) {
			return 0;
		}
	} else if ( magic == 0x76dfc4b0 ) { /// TBIR_MAGIC
		memset( &tbir, 0, sizeof(tbir_image_data) );
		tbir.buffer = image;
		tbir.max = image_length;

		if ( tbir_display_img( &tbir ) == 0 ) {
			return 0;
		}
	} else if ( magic == 0x310f59cb ) { /// TPAI_MAGIC
		memset( &tpai, 0, sizeof(tpai_image_data) );
		tpai.buffer = image;
		tpai.max = image_length;

		if ( tpai_display_image( &tpai ) == 0 ) {
			return 0;
		}

	} else {
		printf("[ERROR] Unknown Format\n");
	}
	
	return 1;
}

int menu( void )
{
	int selection = 0;
	int image_length = 0;
	size_t bytes_read;
	image_meta root;
	char name[16];

	pimage_meta newimage;
	pimage_meta prev;

	bzero( &root, sizeof(image_meta));
	
	while ( 1 ) {
		printf("1- Upload Image\n");
		printf("2- List Images\n");
		printf("3- Remove Image\n");
		printf("4- Display Image\n");
		printf("5- Leave\n");
		printf("} ");

		selection = 0;

		if ( receive_until( (char*)&selection, '\n', 2 ) == 0 ) {
			printf("[ERROR] Failed to read choice\n");
			return 0;
		}

		selection -= 0x30;

		switch (selection) {
			case 1:
				/// Allocate the meta structure to hold the image data
				if ( allocate( sizeof( image_meta ), 0, (void**)&newimage) != 0 ) {
					printf("[ERROR] Failed to allocate buffer\n");
					return 0;
				}

				memset( newimage, 0x00, sizeof(image_meta) );

				/// Receive the name
				printf("Image Name: ");
				if ( receive_until ( newimage->name, '\n', 15) == 0 ) {
					printf("[ERROR] Receive name failed\n");
					deallocate( newimage, sizeof(image_meta));
					return 0;
				}

				/// Receive the length of the image
				if ( receive( 0, &image_length, 2, &bytes_read) != 0 ) {
					printf("[ERROR] Receive length failed\n");
					deallocate( newimage, sizeof(image_meta));
					return 0;
				}

				/// No images greater than 2k
				if ( image_length > 2048 ) {
					printf("[ERROR] Image length to large\n");
					deallocate( newimage, sizeof(image_meta));
					continue;
				}

				/// Allocate the image data buffer
				if ( allocate( image_length + 1, 0, (void**)(&newimage->data)) != 0 ) {
					printf("[ERROR] Failed to allocate image buffer\n");
					deallocate( newimage, sizeof(image_meta));
					return 0;
				}
	
				/// Receive the image data
				if ( receive( 0,  newimage->data, image_length, &bytes_read ) != 0 ) {
					printf("[ERROR] Failed to receive image data\n");
					deallocate( newimage->data, image_length + 1 );
					deallocate( newimage, sizeof(image_meta));
					return 0;
				}

				newimage->len = image_length;
				newimage->next = root.next;
				root.next = newimage;
				newimage = NULL;

				break;
			case 2:
				newimage = root.next;

				while ( newimage ) {
					printf("@s\n", newimage->name);
					newimage = newimage->next;
				}
				break;
			case 3:
				printf("Image Name: ");
				bzero( name, 16 );

				if ( receive_until ( name, '\n', 15) == 0 ) {
					printf("[ERROR] Failed to receive name\n");
					continue;
				}

				newimage = root.next;
				prev = &root;

				while ( newimage ) {
					if ( strcmp( newimage->name, name) == 0 ) {
						deallocate(newimage->data, newimage->len + 1);
						prev->next = newimage->next;
						deallocate(newimage, sizeof(image_meta));
						newimage = NULL;
					} else {
						prev = newimage;
						newimage = newimage->next;
					}
				}
				break;
			case 4:
				printf("Image Name: ");
				bzero( name, 16 );

				if ( receive_until ( name, '\n', 15) == 0 ) {
					printf("[ERROR] Failed to receive name\n");
					continue;
				}

				newimage = root.next;

				while ( newimage ) {
					if ( strcmp( newimage->name, name) == 0 ) {
						break;
					} else {
						newimage = newimage->next;
					}
				}

				if ( newimage != NULL ) {
					if ( selectRenderer( newimage) == 0 ) {
						printf("[ERROR] Failed to render image\n");
						return 0;
					}
				} else {
					printf("[ERROR] Failed to locate image\n");
				}

				break;
			case 5:
				return 0;
				break;
			default:
				printf("[ERROR] Invalid option: @d\n", selection);
				break;
		};

	}

}

int main(void)
{
	char *image = NULL;
	int image_length = 0;
	int magic = 0;

	menu();
	return 0;

	image_length = readData( &image );

	if ( image_length == 0 ) {
		printf("[ERROR] Failed to read image\n");
		return 0;
	}

	if ( image_length < 4 ) {
		return 0;
	}

}
