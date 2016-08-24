/*

Author: Jason Williams <jdw@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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

extern "C"
{
#include <libcgc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <prng.h>
}

#include "common.h"
#include "clf.h"
#include "vm.h"
#include "peripheral.h"

void InitRNG( void *secret_page )
{
	seed_prng_array( (uint32_t*)secret_page, 32 );
}

int __attribute__((fastcall)) main(int secret_page_i, char *unused[]) 
{
	void *secret_page = (void *)secret_page_i;

	InitRNG( secret_page );

	CCLF oLoader;

	uint32_t fileSize;

	ReadBytes( (uint8_t*)&fileSize, 4 );

	if ( fileSize > CCLF::MAX_LOADER_FILE_SIZE )
	{
		printf( "Exiting\n" );
		return (-1);
	}

	uint8_t *pLoaderFile = new uint8_t[fileSize];

	ReadBytes( pLoaderFile, fileSize );

	// Begin loading
	if ( !oLoader.LoadFile( pLoaderFile, fileSize ) )
	{
		printf( "Exiting\n" );
		return (-1);
	}

	// Delete file -- not needed anymore
	delete pLoaderFile;

	CVM oVM( secret_page );

	if ( !oVM.Init( &oLoader ) )
	{
		printf( "Exiting\n" );
		return (-1);
	}

	oVM.Run( );

	return 0;
}
