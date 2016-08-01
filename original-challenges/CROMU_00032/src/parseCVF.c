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

#include "parseCVF.h"

#define LOOPIE 0xfffffff

size_t receiveWrapper( void *outdata, size_t length )
{
	size_t count = 0;
	size_t bytesRead = 0;
	unsigned char *tbuff = (unsigned char *)outdata;

	if ( outdata == NULL ) {
		return 0;
	}

	while ( bytesRead < length ) {
		count = 0;

		if ( receive( 0, tbuff + bytesRead, 1, &count ) != 0 ) {
			printf("[ERROR] Read fail\n");
			return 0;
		}
		bytesRead += count;
	}

	return bytesRead;
}
void freeCVF( pcvf cvf )
{
	unsigned int index = 0;
	if ( cvf == NULL ) {
		return;
	}

	while ( index < 8 ) {
		if ( cvf->pds[index].pixelArray != NULL ) {
			free( cvf->pds[index].pixelArray);
			cvf->pds[index].pixelArray = NULL;
			cvf->pds[index].charCount = 0;
		}	
		index++;
	}

	if ( cvf->renderedFrames != NULL ) {
		index = 0;
		while ( index < cvf->rCount ) {
			if ( cvf->renderedFrames[index] != NULL ) {
				if ( cvf->renderedFrames[index]->image != NULL ) {
					free( cvf->renderedFrames[index]->image);
					cvf->renderedFrames[index]->image = NULL;
					cvf->renderedFrames[index]->height = 0;
					cvf->renderedFrames[index]->width = 0;
				}
				free(cvf->renderedFrames[index]);
				cvf->renderedFrames[index] = NULL;

			}
			index++;
		}
		free(cvf->renderedFrames);
		cvf->renderedFrames = NULL;
	}

	free(cvf);

	return;
}

int playVideo( pcvf cvf )
{
	int index = 0;
	int length = 0;
	pframe rf = NULL;
	int sleepi = 1;
	int tb = 0;
	size_t count = 0;

	if ( cvf == NULL ) {
		return 0;
	}

	if ( cvf->renderedFrames == NULL ) {
		return 0;
	}

	length = cvf->width * cvf->height;

	printf("--------------------Playing video-------------------\n");
	printf("INFO: Height: $d Width: $d Frames: $d\n", cvf->height, cvf->width, cvf->rCount);
	printf("INFO: Set your terminal height so that only the '|'s show.\n");
	printf("INFO: This will provide a better viewing experience\n");
	printf("INFO: When ready press a key...\n");

	for ( int i = 0; i < cvf->height; i++ ) {
		printf("|\n");
	}

	while ( receiveWrapper( &tb, 1 ) == 0 ) {
		return 0;
	}

	while ( index < cvf->rCount ) {
		rf = cvf->renderedFrames[index];

		if ( rf == NULL ) {
			return 0;
		}

		for (int i = 0; i < length; i++) {
			if ( i != 0 && i % rf->width == 0 ) {
				printf("\n");
			}
			printf("$c", rf->image[i]);
		}

		index++;
		printf("\n");

		/// SLEPIE
		/// This was here for a slightly more realistic video feel but
		/// When there are a lot of frames it caused the poller to time out
		/// It is left here just for posterity.
		//for (int i = 0; i < LOOPIE; i++) { sleepi <<= 1; sleepi *= 1234; }
	}

	/// Add the new frame
	return sleepi;
}

unsigned int bitsNeeded( unsigned int size )
{
	unsigned int count = 0;

	if ( size == 0 ) {
		return 1;
	}

	while ( size ) {
		count++;
		size >>= 1;
	}

	return count;
}

int parseCVFFrame( pBitStream pbs, pcvf pNewImage )
{
	unsigned int flag = 0x00;
	unsigned char frame_type = 0;
	unsigned char index_type = 0;
	unsigned char pixel_dict = 0;
	unsigned char custom_dict = 0;
	pframe newFrame = NULL;
	ppixelDict dictionary = NULL;
	pixelDict standard_dictionary;

	unsigned int length = 0;
	unsigned int index = 0;
	
	unsigned int xbits = 0;
	unsigned int ybits = 0;
	unsigned int pixel_index_length = 0;
	unsigned int pixel_count = 0;
	unsigned int pixel_count_bits = 0;
	unsigned int pixel_bits = 0;

	if ( pbs == NULL ) {
		return 0;
	}

	if ( pNewImage == NULL ) {
		return 0;
	}

	/// Test that header has been parsed
	if ( pNewImage->height == 0 ) {
		printf("[ERROR] Header must be specified prior to frame rendering.\n");
		return 0;
	}

#ifdef PATCHED
	/// Ensure that we have not passed the specified number of frames
	if ( pNewImage->frameCount <= pNewImage->rCount ) {
		printf("[ERROR] Too many frames\n");
		return 0;
	}
#endif

	/// First 8 bits of each frame is a flag field.
	if ( readBits( pbs, 8, &flag) == 0 ) {
		return 0;
	}

	/// Bit 7 indicates full frame or individual pixels
	frame_type = (flag >> 7) & 0x1;

	/// Bit 6 indicates x/y or index based
	/// This has not been implemented and probably won't be
	index_type = (flag>>6) & 0x1;
	
	/// Bits 5-3 indicate dictionary
	pixel_dict = (flag>>3) & 0x7;

	/// Custom or reserved. Only used if pixel_dict is 0
	custom_dict = flag&0x7;

	/// The first frame must be a full frame
	if ( pNewImage->rCount == 0 && frame_type != 0 ) {
		printf("[ERROR] First frame must be full\n");
		return 0;
	}

	/// If using a custom dictionary ensure that the dictionary has chars
	if ( pixel_dict == 0 ) {
		if ( pNewImage->pds[custom_dict].charCount == 0 ) {
			printf("[ERROR] Custom Dictionary $d does not exist\n", pixel_dict);
			return 0;
		}

		/// Setup the pixel dictionary
		dictionary = &(pNewImage->pds[custom_dict]);
	} else if ( pixel_dict == 1 ) {
		standard_dictionary.charCount = 2;
		standard_dictionary.pixelArray = " .";
		dictionary = &standard_dictionary;
	} else if ( pixel_dict == 2 ) {
		standard_dictionary.charCount = 4;
		standard_dictionary.pixelArray = " .|#";
		dictionary = &standard_dictionary;
	} else if ( pixel_dict == 3 ) {
		standard_dictionary.charCount = 8;
		standard_dictionary.pixelArray = " .|#@$()";
		dictionary = &standard_dictionary;
	} else if ( pixel_dict == 4 ) {
		standard_dictionary.charCount = 16;
		standard_dictionary.pixelArray = " .|#@$()*HOEWM%&";
		dictionary = &standard_dictionary;
	} else if ( pixel_dict == 5 ) {
		standard_dictionary.charCount = 42;
		standard_dictionary.pixelArray = " .|#@$()*HOEWM%&abcdefghijklmnopqrstuvwxyz";
		dictionary = &standard_dictionary;
	} else if ( pixel_dict == 6 ) {
		standard_dictionary.charCount = 62;
		standard_dictionary.pixelArray = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		dictionary = &standard_dictionary;
	} else if ( pixel_dict == 7 ) {
		standard_dictionary.charCount = 0x5f;
		standard_dictionary.pixelArray = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
		dictionary = &standard_dictionary;
	}

	/// Calculate the length of each pixel in bits based upon the
	///	total number of potential characters - 1. For example
	///	4 characters only requires 2 bits.
	pixel_bits = bitsNeeded( dictionary->charCount - 1);

	/// allocate the new frame
	newFrame = malloc( sizeof(frame) );

	if ( newFrame == NULL ) {
		return 0;
	}

	length = pNewImage->height * pNewImage->width;
	newFrame->height = pNewImage->height;
	newFrame->width = pNewImage->width;

	newFrame->image = malloc( length );	

	if ( newFrame->image == NULL ) {
		free(newFrame);
		newFrame = NULL;
		return 0;
	}

	/// If the frame type is incremental then the number of pixels
	///	must be specified. The bit length of pixel count is the
	///	floor of log2( height * width )
	if ( frame_type == 1 ) {

		pixel_count = 0;

		/// I do not subtract one here because it is not 0 indexed
		pixel_index_length = bitsNeeded( length );

		if ( readBits( pbs, pixel_index_length, (&pixel_count)) == 0 ) {
			free(newFrame->image);
			newFrame->image = NULL;
			free(newFrame);
			newFrame = NULL;
			return 0;
		}

		if ( pixel_count == 0 ) {
			printf("[ERROR] Empty frames not allowed\n");
			free(newFrame->image);
			newFrame->image = NULL;
			free(newFrame);
			newFrame = NULL;
			return 0;
		}

		/// calculate the index length
		pixel_count_bits = bitsNeeded( length - 1 );
	} else {
		/// For a full frame the number of pixels is height * width
		pixel_count = length;
	}

	/// If frame type is 0 meaning a full frame then the index type does
	///	not matter since every pixel from left to right top to bottom
	///	is required.
	if ( frame_type == 0 ) {
		/// Set the base image to all spaces
		memset( newFrame->image, 0x20, length );

		xbits = 0;
		while ( xbits < pixel_count ) {
			if ( readBits( pbs, pixel_bits, &ybits) == 0 ) {
				free(newFrame->image);
				newFrame->image = NULL;
				free(newFrame);
				newFrame = NULL;
				return 0;
			}

			if ( ybits > dictionary->charCount ) {
				printf("[ERROR] invalid pixel\n");
				free(newFrame->image);
				newFrame->image = NULL;
				free(newFrame);
				newFrame = NULL;
				return 0;
			}

			/// Set the frame image data
			newFrame->image[ xbits ] = dictionary->pixelArray[ybits];

			/// Clear the var
			ybits = 0;
			xbits++;
		}

		/// Calculate remaining bits
		xbits = (8 - ( ( pixel_count * pixel_bits) % 8 )) %8;

	} else {
		/// An incremental image requires a copy of the previously rendered frame
		if ( pNewImage->renderedFrames[ pNewImage->rCount - 1] == NULL ) {
			free(newFrame->image);
			newFrame->image = NULL;
			free(newFrame);
			newFrame = NULL;
			return 0;
		}

		memcpy( newFrame->image, pNewImage->renderedFrames[ pNewImage->rCount-1 ]->image, length );

		/// Read index and then pixel
		for ( int i = 0; i < pixel_count; i++ ) {
			xbits = 0;
			ybits = 0;

			if ( readBits( pbs, pixel_count_bits, &xbits) == 0 ) {
				free( newFrame->image);
				newFrame->image = NULL;
				free(newFrame);
				newFrame = NULL;
				printf("[ERROR] Failed to read pixel index\n");
				return 0;
			}

			if ( readBits( pbs, pixel_bits, &ybits) == 0 ) {
				free( newFrame->image);
				newFrame->image = NULL;
				free(newFrame);
				newFrame = NULL;
				printf("[ERROR] Failed to read pixel value\n");
				return 0;
			}


			if ( xbits >= length ) {
				printf("[ERROR] Index out of image bounds\n");
				free(newFrame->image);
				newFrame->image = NULL;
				free(newFrame);
				newFrame = NULL;
				return 0;
			}

			if ( ybits >= dictionary->charCount ) {
				printf("[ERROR] Pixel beyond dictionary bounds\n");
				free(newFrame->image);
				newFrame->image = NULL;
				free(newFrame);
				newFrame = NULL;
				return 0;
			}

			newFrame->image[ xbits ] = dictionary->pixelArray[ybits];
		}

		/// Calculate the remaining padding
		/// Pixel index bits + (index+value)*count
		xbits = pixel_index_length;
		xbits += ( pixel_count_bits + pixel_bits ) * pixel_count;
		xbits %= 8;
		xbits = (8 - xbits) % 8;
	}

	/// Consume any padding bits
	if ( xbits ) {
		if ( readBits( pbs, xbits, &ybits) == 0 ) {
			free(newFrame->image);
			newFrame->image = NULL;
			free(newFrame);
			newFrame = NULL;
			printf("[ERROR] Failed to read padding bits\n");
			return 0;
		}
	}

	/// Add the new frame
	pNewImage->renderedFrames[ pNewImage->rCount ] = newFrame;

	/// Increment the parsed frame count
	pNewImage->rCount++;

	return 1;
}

int parseCVFPixelDict( pBitStream pbs, pcvf pNewImage, int index )
{
	unsigned int pixelCount = 0;
	unsigned int t = 0;
	char *pixelArray = NULL;

	if ( pbs == NULL ) {
		return 0;
	}

	if ( pNewImage == NULL ) {
		return 0;
	}

	if ( index < 0 || index > 7 ) {
		return 0;
	}

	/// If the pixel dictionary has already been specified then fail
	if ( pNewImage->pds[index].charCount != 0 ) {
		printf("[ERROR] Only one type %d pixel allowed.\n");
		return 0;
	}

	/// Read the 8 bit count field
	if ( readBits( pbs, 8, &pixelCount) == 0 ) {
		return 0;
	}

	if ( pixelCount == 0 ) {
		printf("[ERROR] Zero length pixel dictionary not allowed.\n");
		return pixelCount;
	}

	pixelArray = malloc( pixelCount + 1 );

	if (pixelArray == NULL ) {
		return 0;
	}

	memset( pixelArray, 0, pixelCount + 1 );

	/// Loop to read the specified number of pixels
	for (unsigned int i = 0; i < pixelCount; i++) {
		if ( readBits( pbs, 8, &t) == 0 ) {
			printf("[ERROR] Failed to read custom pixel dictionary\n");
			free(pixelArray);
			pixelArray = NULL;
			return 0;
		}

		pixelArray[i] = (unsigned char)(t&0xff);
		t = 0;
	}

	memset( &pNewImage->pds[index], 0, sizeof(pixelDict) );

	pNewImage->pds[index].charCount = pixelCount;
	pNewImage->pds[index].pixelArray = pixelArray;

	return 1;
}

int parseCVFDescription( pBitStream pbs, pcvf pNewImage )
{
	unsigned int descLength = 0;
	unsigned int index = 0;
	unsigned char c;
	unsigned int t;

	if ( pbs == NULL ) {
		return 0;
	}

	if ( pNewImage == NULL ) {
		return 0;
	}

	/// Due to the later check it should be impossible to have multiple
	///	description sections of non-zero length
	if ( pNewImage->desc[0] != '\x00' ) {
		return 0;
	}

	/// Read the description length
	if ( readBits( pbs, 8, &descLength) == 0 ) {
		return 0;
	}

	if ( descLength > 255 ) {
		return 0;
	}

	/// Read the description data
	for( index = 0; index < descLength; index++ ) {
		if ( readBits( pbs, 8, &t) == 0 ) {
			return 0;
		}

		pNewImage->desc[index] = (char)(t&0xff);
		t = 0;
	}

	/// Ensure that the data is valid
	for( index = 0; index < descLength; index++ ) {
		c = pNewImage->desc[index];

		if ( !isalpha( c ) && !isdigit( c ) && !isspace( c ) ) {
			printf("[ERROR] Invalid character in description\n");
			return 0;
		}
	}

	return 1;
}

int parseCVFName( pBitStream pbs, pcvf pNewImage )
{
	unsigned int nameLength = 0;
	unsigned int t = 0;

	if ( pbs == NULL || pNewImage == NULL ) {
		return 0;
	}

	/// If the name has already been read then error out
	if ( pNewImage->name[0] != '\x00' ) {
		return 0;
	}

	/// First 8 bits are name length
	if ( readBits( pbs, 8, &nameLength) == 0 ) {
		return 0;
	}

	/// Last byte must be a null so a max of 255 bytes
	if ( nameLength > 255 ) {
		return 0;
	}

	for ( int i = 0; i < nameLength; i++ ) {
		if ( readBits( pbs, 8, &t) == 0 ) {
			return 0;
		}

		pNewImage->name[i] = (char)(t&0xff);
		t = 0;
	}

	/// Ensure valid characters in the name field
	for ( int i = 0; i < nameLength; i++) {
		if ( !isascii( pNewImage->name[i] ) ){
			printf("[ERROR] Invalid value in name field\n");
			return 0;
		}
	}

	return 1;
}

int parseCVFHeader( pBitStream pbs, pcvf pNewImage )
{
	if ( pbs == NULL ) {
		return 0;
	}

	if ( pNewImage == NULL ) {
		return 0;
	}

	/// A 0 height is not allowed so if the current value
	/// is non-zero then a header has already been parsed.
	/// Multiple headers are not permitted so error out
	if ( pNewImage->height != 0 ) {
		printf("[ERROR] Multiple header sections are not permitted.\n");
		return 0;
	}

	/// Read 8 bits of height
	if ( readBits( pbs, 8, &(pNewImage->height) ) == 0 ) {
		return 0;
	}

	if ( pNewImage->height == 0 ) {
		printf("[ERROR] Zero length height is not permitted\n");
		return 0;
	}

	/// Maximum height is 35 characters
	if ( pNewImage->height > 35 ) {
		printf("[ERROR] Height must be less than 35\n");
		return 0;
	}

	/// Read 8 bits of width
	if ( readBits( pbs, 8, &(pNewImage->width) ) == 0 ) {
		return 0;
	}

	if ( pNewImage->width == 0 ) {
		printf("[ERROR] Zero length width is not permitted\n");
		return 0;
	}

	/// Maximum width is 128 characters
	if ( pNewImage->width > 128 ) {
		printf("[ERROR] Width must be less than 128\n");
		return 0;
	}

	/// Read 16 Bits frame count
	if ( readBits( pbs, 16, &(pNewImage->frameCount) ) == 0 ) {
		return 0;
	}

	/// Maximum frame count is 2048
	if ( pNewImage->frameCount > 2048 ) {
		printf("[ERROR] Maximum frame count is 2048\n");
		return 0;
	}

	/// Zero frame count is not permitted
	if ( pNewImage->frameCount == 0 ) {
		printf("[ERROR] Zero frame count is not permitted\n");
		return 0;
	}

	/// Allocate frame structure pointer array
	pNewImage->renderedFrames = malloc( sizeof( pframe ) * pNewImage->frameCount);

	if ( pNewImage->renderedFrames == NULL ) {
		return 0;
	}

	memset( pNewImage->renderedFrames, 0x00, sizeof(pframe) * pNewImage->frameCount); 

	return 1;
}

void renderCVF( pBitStream pbs )
{
	unsigned int tdata = 0;
	pcvf NewImage = NULL;

	if ( pbs == NULL ) {
		return;
	}

	/// Read the first 4 bytes of the image. This should be
	/// The magic 0x00, 'C', 'V', 'F'
	if ( readBits( pbs, 32, &tdata) == 0 ) {
		return;
	}

	if ( tdata != 0x00435646 ) {
		printf("[ERROR] Invalid magic: $d\n", tdata);
		return;
	}

	NewImage = initCVF( );

	if (NewImage == NULL ) {
		return;
	}

	/// This loop starts by reading 2 bytes. Those two bytes
	///	should be the section type such as 0x1111 for the header
	///	Depending on this value the proper function is called to read and
	///	parse the data.
	/// The loop stops when there is nothing left to read.
	tdata = 0;

	while( readBits( pbs, 16, &tdata) != 0 ) {
		switch( tdata ) {
			case 0x1111:
				if ( parseCVFHeader( pbs, NewImage ) == 0 ) {
					freeCVF( NewImage );
					NewImage = NULL;
					return;
				}

				break;
			case 0x2222:
				if ( parseCVFName( pbs, NewImage ) == 0 ) {
					freeCVF( NewImage );
					NewImage = NULL;
					return;
				}

				break;
			case 0x3333:
				if ( parseCVFDescription( pbs, NewImage ) == 0 ) {
					freeCVF( NewImage);
					NewImage = NULL;
					return;
				}

				break;
			case 0x4444:
			case 0x4445:
			case 0x4446:
			case 0x4447:
			case 0x4448:
			case 0x4449:
			case 0x444A:
			case 0x444B:
				tdata -= 0x4444;

				if ( parseCVFPixelDict( pbs, NewImage, tdata) == 0 ) {
					freeCVF( NewImage );
					NewImage = NULL;
					return;
				}

				break;
			case 0x5555:

				if ( parseCVFFrame( pbs, NewImage ) == 0 ) {
					freeCVF( NewImage );
					NewImage = NULL;
					return;
				}

				break;
			default:
				printf("[ERROR] Invalid section type: $d\n", tdata);
				return;
				break;

		}
		tdata = 0;

	}

	/// At this point it is successfully parsed and ready to be played.
	playVideo(NewImage);
	freeCVF(NewImage);

	return;
}

pcvf initCVF( void )
{
	pcvf nc = NULL;

	nc = malloc( sizeof( cvf ) );

	if ( nc == NULL ) {
		return nc;
	}

	memset( nc, 0, sizeof(cvf) );

	return nc;
}
