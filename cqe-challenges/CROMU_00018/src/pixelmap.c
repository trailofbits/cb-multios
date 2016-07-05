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
#include <stdlib.h>
#include <libcgc.h>
#include "pixelmap.h"

#define PMP_HEADER_FILE_TYPE            (0x4D50)
#define PMP_HEADER_COMPRESSION_NONE     (0)
#define PMP_HEADER_BITCOUNT_24BIT_RGB   (24)

#define PMP_FILE_HEADER_SIZE       (14)
#define PMP_INFO_HEADER_SIZE       (40)


typedef struct __attribute__ ((__packed__)) tagPixelmapFileHeader
{
    uint16_t    pmType;
    uint32_t    pmSize;
    uint16_t    pmReserved1;
    uint16_t    pmReserved2;
    uint32_t    pmOffBits;
} tPixelmapFileHeader;


typedef struct __attribute__ ((__packed__)) tagPixelmapInfoHeader
{
    uint32_t    piSize;
    uint32_t    piWidth;
    uint32_t    piHeight;
    uint16_t    piPlanes;
    uint16_t    piBitCount;
    uint32_t    piCompression;
    uint32_t    piSizeImage;
    uint32_t    piXPelsPerMeter;
    uint32_t    piYPelsPerMeter;
    uint32_t    piClrUsed;
    uint32_t    piClrImportant;
} tPixelmapInfoHeader;

// Binary writing helpers
uint32_t pm_write_u32( uint8_t *pData, uint32_t *pFilePos, uint32_t value )
{
    *((uint32_t*)(pData+(*pFilePos))) = value;
    (*pFilePos) += sizeof(value);

    return (sizeof(value));
}

uint32_t pm_write_u16( uint8_t *pData, uint32_t *pFilePos, uint16_t value )
{
    *((uint16_t*)(pData+(*pFilePos))) = value;
    (*pFilePos) += sizeof(value);

    return (sizeof(value));
}

uint32_t pm_write_u8( uint8_t *pData, uint32_t *pFilePos, uint8_t value )
{
    *((uint8_t*)(pData+(*pFilePos))) = value;
    (*pFilePos) += sizeof(value);

    return (sizeof(value));
}

int32_t pixelmap_write_file( uint8_t **pFileData, uint32_t *pFileSize, uint8_t *rgb_data, uint32_t width, uint32_t height )
{
    uint32_t pmImageSize;
    uint32_t row, col;
    tPixelmapFileHeader oFileHeader;
    tPixelmapInfoHeader oInfoHeader;

    if ( width == 0 || height == 0 )
        return -1;

    if ( rgb_data == NULL )
        return -1;

    if ( PMP_FILE_HEADER_SIZE != sizeof(tPixelmapFileHeader) )
        return -1;

    if ( PMP_INFO_HEADER_SIZE != sizeof(tPixelmapInfoHeader) )
        return -1;

    oFileHeader.pmOffBits = (PMP_FILE_HEADER_SIZE + PMP_INFO_HEADER_SIZE);
    oFileHeader.pmType = PMP_HEADER_FILE_TYPE;
    oFileHeader.pmReserved1 = 0;
    oFileHeader.pmReserved2 = 0;

    // Calculate overall image size for RGB
    uint32_t col_size;

    col_size = (width * 3);

    if ( col_size % 4 != 0 )
        col_size = (col_size & ~0x3) + 4;

    pmImageSize = (col_size * height);

    oFileHeader.pmSize = pmImageSize + PMP_FILE_HEADER_SIZE + PMP_INFO_HEADER_SIZE;

    if ( oFileHeader.pmSize % 4 != 0 )
        oFileHeader.pmSize = (oFileHeader.pmSize & ~0x3) + 4;

    oInfoHeader.piHeight = height;
    oInfoHeader.piWidth = width;

    oInfoHeader.piSize = PMP_INFO_HEADER_SIZE;
    oInfoHeader.piBitCount = PMP_HEADER_BITCOUNT_24BIT_RGB;
    oInfoHeader.piCompression = PMP_HEADER_COMPRESSION_NONE;

    oInfoHeader.piPlanes = 1;
    oInfoHeader.piClrUsed = 0;
    oInfoHeader.piClrImportant = 0;
    oInfoHeader.piXPelsPerMeter = 2835; // 72 DPI
    oInfoHeader.piYPelsPerMeter = 2835; // 72 DPI

    oInfoHeader.piSizeImage = pmImageSize;

    // Allocate file data
    (*pFileData) = malloc( oFileHeader.pmSize );
    (*pFileSize) = oFileHeader.pmSize;

    uint8_t *pData = (*pFileData);
    uint32_t filePos = 0;

    // Write out file data...
    memcpy( (pData+filePos), &oFileHeader, sizeof(oFileHeader) );
    filePos += sizeof(oFileHeader);

    memcpy( (pData+filePos), &oInfoHeader, sizeof(oInfoHeader) );
    filePos += sizeof(oInfoHeader);

    for ( row = height; row > 0; row-- )
    {
        uint32_t col_byte_count = 0;
        for ( col = 0; col < width; col++ )
        {
            uint8_t red, green, blue;
            uint32_t data_offset = ((row-1) * (width*3));

            red = rgb_data[data_offset + (col*3)+2];
            green = rgb_data[data_offset + (col*3)+1];
            blue = rgb_data[data_offset + (col*3)+0];

            pm_write_u8( pData, &filePos, red );
            pm_write_u8( pData, &filePos, green );
            pm_write_u8( pData, &filePos, blue );

            col_byte_count += 3;
        }

        // Pad to 4-bytes
        while ( col_byte_count % 4 != 0 )
        {
            pData[filePos++] = 0x0;
            col_byte_count++;
        }
    }


    // Generate file data
    return (filePos);
}

int32_t pixelmap_get_size( uint32_t width, uint32_t height )
{
    int32_t pmp_size = PMP_FILE_HEADER_SIZE + PMP_INFO_HEADER_SIZE;
    int32_t col_size = (width * 3);

    // Add padding to 4-byte boundaries
    if ( col_size % 4 )
        col_size = (col_size & ~0x3) + 4;

    pmp_size = pmp_size + (col_size * height);

    return (pmp_size);
}
