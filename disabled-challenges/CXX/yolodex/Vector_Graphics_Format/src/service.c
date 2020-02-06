/*

Author: Jason Williams <jdw@cromulence.com>

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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_io.h"
#include "cgc_vgf.h"
#include "cgc_pixelmap.h"

#define INPUT_FILE_SIZE_MAXIMUM     (20000)

int main(int cgc_argc, char *cgc_argv[])
{
    cgc_setup_io( STDIN, STDOUT );

    tVGFParsedFile *pFile;

#ifdef PATCHED
    uint16_t fileSize = cgc_read_u16();
#else
    int16_t fileSize = cgc_read_u16();
#endif

    if ( fileSize > INPUT_FILE_SIZE_MAXIMUM )
        cgc__terminate( -3 );

    // Read in file data
    uint8_t *pFileData = (uint8_t*)cgc_malloc( INPUT_FILE_SIZE_MAXIMUM );

    // Read loop for file data
    uint32_t readCount = 0;
    for ( readCount = 0; readCount < fileSize; readCount++ )
        pFileData[readCount] = cgc_read_u8();

    if ( readCount != fileSize )
        cgc__terminate( -3 );

    if ( cgc_vgf_parse_data( pFileData, fileSize, &pFile ) != VGF_PARSE_SUCCESS )
        cgc__terminate( -3 );

    // Free memory
    cgc_free( pFileData );

    int32_t renderSize;
    uint8_t *pRenderData;

    if ( (renderSize = cgc_vgf_get_render_size( pFile )) <= 0 )
        cgc__terminate( -3 );

    // Allocate render buffer
    uint32_t destLen = renderSize;
    pRenderData = (uint8_t*)cgc_malloc( destLen );

    if ( cgc_vgf_render_file( pFile, pRenderData, &destLen ) != 0 )
        cgc__terminate( -3 );

    uint32_t pmSize;
    uint8_t *pPMFileData;

    if ( cgc_pixelmap_write_file( &pPMFileData, &pmSize, pRenderData, cgc_vgf_get_width( pFile ), cgc_vgf_get_height( pFile ) ) <= 0 )
        cgc__terminate( -3 );

    // Free the render buffer
    cgc_free( pRenderData );

    // Send the complete file
    cgc_size_t tx_bytes = pmSize;
    cgc_size_t writeCur;
    for ( writeCur = 0; writeCur < tx_bytes; writeCur++ )
        cgc_write_u8( pPMFileData[writeCur] );

    cgc_free( pPMFileData );

    cgc_vgf_destroy_file( pFile );

    return 0;
}
