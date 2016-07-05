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

#ifndef __PARSE_CVF__
#define __PARSE_CVF__
#include <libcgc.h>
#include <stdlib.h>
#include <malloc.h>

#include "bitstream.h"

/**
 * Structure to store the rendering of a single frame
 **/
typedef struct frame {
	/// Height of the frame to be rendered
	unsigned int height;

	/// Width of the frame to be rendered
	unsigned int width;

	/// Pointer a character array of the rendered image. The length is equal to height*width
	char *image;
} frame, *pframe;

/**
 * Structure to store a single pixel dictionary. The length of the array is equal to the "charCount" field
 **/
typedef struct pixelDict {
	/// Number of characters available in the pixel array
	unsigned int charCount;

	/// Pointer to the array to be used with this dictionary.
	char *pixelArray;
} pixelDict, *ppixelDict;

/**
 * Main structure to store a single CVF video
 **/
typedef struct cvf {
	/// Height of the video in characters
	unsigned int height;

	/// Width of the video in characters.
	unsigned int width;

	/// Number of video frames.
	unsigned int frameCount;

	/// Buffer to store the optional name field
	char name[256];

	/// Buffer to store the optional description field
	char desc[256];

	/// Array of pixel dictionary structures used to render frames using a custom dictionary
	pixelDict pds[8];

	/// Count of frames rendered
	unsigned int rCount;

	/// Pointer to an array of rendered framed pointers. The length is determined by "frameCount"
	pframe *renderedFrames;
} cvf, *pcvf;

/// Calculates the number of bits needed for a given size.
unsigned int bitsNeeded( unsigned int length );

int parseCVFFrame( pBitStream pbs, pcvf pNewImage );
void displayCVFFrame( pcvf pNewImage );

int parseCVFPixelDict( pBitStream pbs, pcvf pNewImage, int index );

/// Parses the description section
int parseCVFDescription( pBitStream pbs, pcvf pNewImage );

/// Parses the name section.
int parseCVFName( pBitStream pbs, pcvf pNewImage );

/// Parses the header section
int parseCVFHeader( pBitStream pbs, pcvf pNewImage );

/// renders the image
void renderCVF( pBitStream pbs );

/// Initializes a new cvf structure
pcvf initCVF( void );

/// Frees the video structure
void freeCVF( pcvf cvf );

#endif
