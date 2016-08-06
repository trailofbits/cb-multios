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
#include "vgf.h"

// Default color not filled in
#define PIXEL_DEFAULT_COLOR_INDEX   (0xFFFF)

#define GET_XY( x, y, width ) ( (x) + ((y) * width) )

#define SWAP( a, b ) { uint16_t temp = a; a = b; b = temp; }

uint16_t vgf_get_width( tVGFParsedFile *pFile )
{
    if ( pFile == NULL )
        return 0;

    return (pFile->file_header.vgfWidth);
}

uint16_t vgf_get_height( tVGFParsedFile *pFile )
{
    if ( pFile == NULL )
        return 0;

    return (pFile->file_header.vgfHeight);
}

// Read in a vgf file
int32_t vgf_parse_data( uint8_t *pData, uint32_t dataLen, tVGFParsedFile **pParsedFile )
{
    uint32_t idx;
    uint32_t readPos;
    int32_t exitResults = VGF_ERROR_INVALID_FILE;
    tVGFHeader *pFileHeader;
    tVGFParsedFile *pParsedData = NULL;

    // Clear parsed file... set when parsing complete
    (*pParsedFile) = NULL;

    // Reset read position
    readPos = 0;

    pFileHeader = (tVGFHeader *)pData;

    if ( (readPos+sizeof(tVGFHeader)) > dataLen )
        return (VGF_ERROR_INVALID_FILE);

    if ( pFileHeader->vgfMagic != VGF_MAGIC )
        return (VGF_ERROR_INVALID_FILE);

    if ( pFileHeader->vgfVersion != VGF_VERSION )
        return (VGF_ERROR_INVALID_VERSION);

    // Check height and width
    if ( pFileHeader->vgfHeight > VGF_MAX_Y ||
         pFileHeader->vgfWidth > VGF_MAX_X )
        return (VGF_ERROR_INVALID_FILE);

    // Check layer count
    if ( pFileHeader->vgfLayerCount > VGF_MAX_LAYER )
        return (VGF_ERROR_INVALID_FILE);

    // Advance read position
    readPos += sizeof(tVGFHeader);

    // Allocated data for parsed file
    pParsedData = (tVGFParsedFile *)malloc( sizeof(tVGFParsedFile) );
    pParsedData->pObjectList = NULL;
    pParsedData->color_count = 0;
    pParsedData->pColorTable = NULL;

    // Load file header
    memcpy( &(pParsedData->file_header), pFileHeader, sizeof(tVGFHeader) );

    // Remember last object to order list
    tVGFObjectTable *pLastObjEntry = NULL;

    // Now read in objects
    for ( ;; )
    {
        uint8_t do_end = 0;
        tVGFObjectHeader *pObjectHeader;

        // Get Header
        pObjectHeader = (tVGFObjectHeader *)(pData+readPos);

        // Check length
        if ( (readPos+sizeof(tVGFObjectHeader)) > dataLen )
        {
            exitResults = VGF_ERROR_INVALID_FILE;
            goto exit_cleanup;
        }

        // Advance position
        readPos += sizeof(tVGFObjectHeader);

        // Add object and insert
        tVGFObjectTable *pNewObjEntry = (tVGFObjectTable *)malloc( sizeof( tVGFObjectTable) );
        pNewObjEntry->pNext = NULL;

        if ( pLastObjEntry == NULL )
        {
            pParsedData->pObjectList = pNewObjEntry;
            pLastObjEntry = pNewObjEntry;
        }
        else
        {
            pLastObjEntry->pNext = pNewObjEntry;
            pLastObjEntry = pNewObjEntry;
        }

        // Copy header
        pNewObjEntry->obj_header = (*pObjectHeader);

        // Load appropriate object
        switch( pObjectHeader->object_type )
        {
        case VGF_OBJECT_RECT:
            if ( (readPos+sizeof(tVGFDrawRect)) > dataLen )
            {
                exitResults = VGF_ERROR_INVALID_FILE;
                goto exit_cleanup;
            }

            pNewObjEntry->obj_data.obj_rect = *((tVGFDrawRect *)(pData+readPos));

            readPos += sizeof(tVGFDrawRect);
            break;

        case VGF_OBJECT_TRIANGLE:
            if ( (readPos+sizeof(tVGFDrawTriangle)) > dataLen )
            {
                exitResults = VGF_ERROR_INVALID_FILE;
                goto exit_cleanup;
            }

            pNewObjEntry->obj_data.obj_triangle = *((tVGFDrawTriangle *)(pData+readPos));

            readPos += sizeof(tVGFDrawTriangle);
            break;

        case VGF_OBJECT_LINE:
            if ( (readPos+sizeof(tVGFDrawLine)) > dataLen )
            {
                exitResults = VGF_ERROR_INVALID_FILE;
                goto exit_cleanup;
            }

            pNewObjEntry->obj_data.obj_line = *((tVGFDrawLine *)(pData+readPos));

            readPos += sizeof(tVGFDrawLine);
            break;

        case VGF_OBJECT_CIRCLE:
            if ( (readPos+sizeof(tVGFDrawCircle)) > dataLen )
            {
                exitResults = VGF_ERROR_INVALID_FILE;
                goto exit_cleanup;
            }

            pNewObjEntry->obj_data.obj_circle = *((tVGFDrawCircle *)(pData+readPos));

            readPos += sizeof(tVGFDrawCircle);
            break;

        case VGF_OBJECT_END:
            do_end = 1;
            break;

        default:
            exitResults = VGF_ERROR_INVALID_FILE;
            goto exit_cleanup;
            break;
        }

        // Check end?
        if ( do_end )
            break;
    }

    // Load color index
    if ( (readPos+sizeof(tVGFColorTable)) > dataLen )
    {
        exitResults = VGF_ERROR_INVALID_FILE;
        goto exit_cleanup;
    }

    pParsedData->color_count = ((tVGFColorTable *)(pData+readPos))->color_count;
    readPos += sizeof(tVGFColorTable);

    // Allocate array
    if ( pParsedData->color_count > 0 )
    {
        pParsedData->pColorTable = (tVGFColorHeader *)malloc( sizeof(tVGFColorHeader) * pParsedData->color_count );

        // Read in color data
        for ( idx = 0; idx < pParsedData->color_count; idx++ )
        {
            if ( (readPos+sizeof(tVGFColorHeader)) > dataLen )
            {
                exitResults = VGF_ERROR_INVALID_FILE;
                goto exit_cleanup;
            }

            memcpy( &(pParsedData->pColorTable[idx]), (pData+readPos), sizeof(tVGFColorHeader) );

            readPos += sizeof(tVGFColorHeader);
        }
    }

    // Parse complete
    exitResults = VGF_PARSE_SUCCESS;

exit_cleanup:
    // Check if parsing fail and need to cleanup
    if ( pParsedData && exitResults != VGF_PARSE_SUCCESS )
        vgf_destroy_file( pParsedData );

    // Check success
    if ( exitResults == VGF_PARSE_SUCCESS )
        (*pParsedFile) = pParsedData;

    return (exitResults);
}

void vgf_destroy_file( tVGFParsedFile *pFile )
{
    if ( !pFile )
        return;

    if ( pFile->pObjectList )
    {
        tVGFObjectTable *pCur;
        tVGFObjectTable *pNext;

        // Free objects
        pCur = pFile->pObjectList;

        // Free objects
        while ( pCur )
        {
            // Remember next
            pNext = pCur->pNext;

            // Free memory
            free( pCur );

            // Advance
            pCur = pNext;
        }
    }

    // Free color table
    if ( pFile->pColorTable )
        free( pFile->pColorTable );

    // Free data
    free( pFile );
}

// Get the output size of the VGF file converted to BMP
int32_t vgf_get_render_size( tVGFParsedFile *pFile )
{
    uint32_t pixel_count;
    uint32_t raw_image_size;
    uint32_t bmp_size;

    if ( pFile == NULL )
        return (-1);

    pixel_count = (pFile->file_header.vgfWidth * pFile->file_header.vgfHeight);

    raw_image_size = (pixel_count * 3);

    return (raw_image_size);
}

// Write out the VGF file to a render buffer
int32_t vgf_render_file( tVGFParsedFile *pFile, uint8_t *pDest, uint32_t *pDestLen )
{
    uint32_t pixel_count;
    uint32_t pixel_idx;
    uint16_t pixel_width, pixel_height;
    uint8_t layer_count, layer_idx;
    uint16_t *layer_data[VGF_MAX_LAYER];
    uint16_t *final_data = NULL;
    int8_t exitResults = 0;

    if ( pFile == NULL || pDest == NULL || pDestLen == NULL )
        return (-1);

    // Render each object to the appropriate layer
    // Allocate layer buffers
    pixel_width = pFile->file_header.vgfWidth;
    pixel_height = pFile->file_header.vgfHeight;
    pixel_count = (pixel_width * pixel_height);

    layer_count = (pFile->file_header.vgfLayerCount);

    // Perform layer allocation and initialization
    for ( layer_idx = 0; layer_idx < layer_count; layer_idx++ )
    {

        layer_data[layer_idx] = (uint16_t *)malloc( pixel_count*sizeof(uint16_t) );

        for ( pixel_idx = 0; pixel_idx < pixel_count; pixel_idx++ )
            layer_data[layer_idx][pixel_idx] = PIXEL_DEFAULT_COLOR_INDEX;
    }

    // Render each object to the appropriate layer
    tVGFObjectTable *pCur;

    // Iterate
    for ( pCur = pFile->pObjectList; pCur != NULL; pCur = pCur->pNext )
    {
        // Parse object information
        uint8_t obj_layer;
        uint8_t obj_color_index;
        uint16_t obj_settings;

        obj_layer = pCur->obj_header.object_layer;
        obj_color_index = pCur->obj_header.object_color_index;
        obj_settings = pCur->obj_header.object_settings;

        // Verify layer index
        if ( obj_layer >= layer_count )
        {
            exitResults = -1;
            goto exit_cleanup;
        }

        if ( obj_color_index >= pFile->color_count )
        {
            exitResults = -1;
            goto exit_cleanup;
        }

        // Render objects
        switch( pCur->obj_header.object_type )
        {
        case VGF_OBJECT_RECT:
            vgf_render_rect( &(pCur->obj_data.obj_rect), layer_data[obj_layer], obj_settings, obj_color_index, pixel_width, pixel_height );
            break;

        case VGF_OBJECT_TRIANGLE:
            vgf_render_triangle( &(pCur->obj_data.obj_triangle), layer_data[obj_layer], obj_settings, obj_color_index, pixel_width, pixel_height );
            break;

        case VGF_OBJECT_LINE:
            vgf_render_line( &(pCur->obj_data.obj_line), layer_data[obj_layer], obj_settings, obj_color_index, pixel_width, pixel_height );
            break;

        case VGF_OBJECT_CIRCLE:
            vgf_render_circle( &(pCur->obj_data.obj_circle), layer_data[obj_layer], obj_settings, obj_color_index, pixel_width, pixel_height );
            break;

        case VGF_OBJECT_END:
            // Do nothing
            break;

        default:
            // Error
            exitResults = -1;
            goto exit_cleanup;
            break;
        }
    }

    // Allocate data for final layer
    final_data = (uint16_t *)malloc( pixel_count*sizeof(uint16_t) );

    // Setup final layer
    for ( pixel_idx = 0; pixel_idx < pixel_count; pixel_idx++ )
        final_data[pixel_idx] = PIXEL_DEFAULT_COLOR_INDEX;

    // Copy each layer into the final layer (in order) to allow layers to overwrite each other
    for ( layer_idx = 0; layer_idx < layer_count; layer_idx++ )
    {
        for ( pixel_idx = 0; pixel_idx < pixel_count; pixel_idx++ )
        {
            if ( layer_data[layer_idx][pixel_idx] != PIXEL_DEFAULT_COLOR_INDEX )
                final_data[pixel_idx] = layer_data[layer_idx][pixel_idx];
        }
    }

    // Render data

    // Check destination buffer length
    if ( (*pDestLen) < (pixel_count * 3) )
    {
        exitResults = -1;
        goto exit_cleanup;
    }

    // Render
    uint32_t destPixel = 0;
    for ( pixel_idx = 0; pixel_idx < pixel_count; pixel_idx++ )
    {
        if ( final_data[pixel_idx] == PIXEL_DEFAULT_COLOR_INDEX )
        {
            // Default black background
            *(pDest+destPixel+0) = 0x00;
            *(pDest+destPixel+1) = 0x00;
            *(pDest+destPixel+2) = 0x00;
        }
        else
        {
            if ( final_data[pixel_idx] >= pFile->color_count )
            {
                exitResults = -1;
                goto exit_cleanup;
            }

            *(pDest+destPixel+0) = pFile->pColorTable[final_data[pixel_idx]].red;
            *(pDest+destPixel+1) = pFile->pColorTable[final_data[pixel_idx]].green;
            *(pDest+destPixel+2) = pFile->pColorTable[final_data[pixel_idx]].blue;
        }

        destPixel += 3;
    }

    exitResults = 0;

exit_cleanup:
    if ( final_data )
        free( final_data );

    for ( layer_idx = 0; layer_idx < layer_count; layer_idx++ )
    {
        if ( layer_data[layer_idx] )
            free( layer_data[layer_idx] );
    }

    return (exitResults);
}

void vgf_hline_helper( uint16_t x0, uint16_t y0, uint16_t len, uint16_t *layer_data, uint8_t color_index, uint16_t width, uint16_t height )
{
    if ( x0 >= width )
        return;

    if ( y0 >= height )
        return;

    uint16_t cur = 0;

    // Draw line to the right
    for ( cur = 0; cur < len; cur++ )
    {
        if ( x0 + cur >= width )
            break;

        layer_data[ GET_XY( x0+cur, y0, width ) ] = color_index;
    }
}

void vgf_vline_helper( uint16_t x0, uint16_t y0, uint16_t len, uint16_t *layer_data, uint8_t color_index, uint16_t width, uint16_t height )
{
    if ( x0 >= width )
        return;

    if ( y0 >= height )
        return;

    uint16_t cur = 0;

    // Draw line straight up
    for ( cur = 0; cur < len; cur++ )
    {
        if ( y0 + cur >= height )
            break;

        layer_data[ GET_XY( x0, y0+cur, width ) ] = color_index;
    }
}

void vgf_line_helper( uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t *layer_data, uint8_t color_index, uint16_t width, uint16_t height )
{
    // Use Bresenham's algorithm
    int16_t dx, dy;
    int16_t sx, sy;
    int16_t errx, erry;
    int16_t dist;
    int16_t x_pos = x0;
    int16_t y_pos = y0;
    int16_t count;

    dx = abs( x1 - x0 );
    dy = abs( y1 - y0 );

    if ( dx > dy )
        dist = dx;
    else
        dist = dy;

    if ( x0 < x1 )
        sx = 1;
    else
        sx = -1;

    if ( y0 < y1 )
        sy = 1;
    else
        sy = -1;

    errx = 0;
    erry = 0;

    for ( count = 0; count <= dist+1; count++ )
    {
        layer_data[ x_pos + (y_pos * width) ] = color_index;

        errx += dx;
        erry += dy;

        if ( errx > dist )
        {
            errx -= dist;
            x_pos += sx;
        }

        if ( erry > dist )
        {
            erry -= dist;
            y_pos += sy;
        }
    }
}

void vgf_render_rect( tVGFDrawRect *pRectData, uint16_t *layer_data, uint8_t settings, uint8_t color_index, uint16_t width, uint16_t height )
{
    uint16_t x_pos, y_pos;
    uint16_t x_start, y_start;
    uint16_t x_end, y_end;

    if ( pRectData == NULL )
        return;

    x_start = pRectData->x_start;
    y_start = pRectData->y_start;
    x_end = (pRectData->x_start + pRectData->x_len);
    y_end = (pRectData->y_start + pRectData->y_len);

    // Check coordinates
    if ( x_start >= width ||
         y_start >= height ||
         x_end >= width ||
         y_end >= height )
        return;

    if ( x_start > x_end )
        return;

    if ( y_start > y_end )
        return;

    // Render
    x_pos = x_start;
    y_pos = y_start;
    for ( ; x_pos < x_end; x_pos++ )
        layer_data[ x_pos + (y_pos*width) ] = color_index;

    for ( ; y_pos < y_end; y_pos++ )
        layer_data[ x_pos + (y_pos*width) ] = color_index;

    for ( ; x_pos > x_start; x_pos-- )
        layer_data[ x_pos + (y_pos*width) ] = color_index;

    for ( ; y_pos > y_start; y_pos-- )
        layer_data[ x_pos + (y_pos*width) ] = color_index;

    if ( settings & VGF_OBJECT_SETTINGS_FILL )
    {
        // Do FILL
        x_pos = x_start+1;

        for ( ; x_pos < x_end; x_pos++ )
        {
            y_pos = y_start+1;
            for ( ; y_pos < y_end; y_pos++ )
                layer_data[ x_pos + (y_pos*width) ] = color_index;
        }
    }
}


void vgf_render_circle( tVGFDrawCircle *pCircleData, uint16_t *layer_data, uint8_t settings, uint8_t color_index, uint16_t width, uint16_t height )
{
    if ( pCircleData == NULL )
        return;

    if ( pCircleData->x_pos >= width ||
         pCircleData->y_pos >= height )
        return;

    if ( pCircleData->x_pos+pCircleData->radius >= width ||
         pCircleData->y_pos+pCircleData->radius >= height )
        return;

    // BUG::
    // Missing check for lower bounds overwrite (pCircleData->x_pos - radius)
#ifdef PATCHED
    if ( pCircleData->x_pos < pCircleData->radius ||
         pCircleData->y_pos < pCircleData->radius )
        return;
#endif

    if ( settings & VGF_OBJECT_SETTINGS_FILL )
    {
        // Render circle -- same algorithm below just drawing lines across the points
        int16_t x_pos = pCircleData->x_pos;
        int16_t y_pos = pCircleData->y_pos;
        int16_t x = 0;
        int16_t y = pCircleData->radius;
        int16_t radius_error = 1 - pCircleData->radius;
        int16_t ddF_x = 1;
        int16_t ddF_y = -2 * pCircleData->radius;

        vgf_vline_helper( x_pos, y_pos-y, 2*y, layer_data, color_index, width, height );

        while ( x < y )
        {
            if ( radius_error >= 0 )
            {
                y--;
                ddF_y += 2;
                radius_error += ddF_y;
            }

            x++;
            ddF_x += 2;
            radius_error += ddF_x;

            // Draw lines vertically ||| across the circle points using Bresenham's algorithm, use the fast vline helper
            vgf_vline_helper( x_pos+x, y_pos-y, 2*y, layer_data, color_index, width, height );
            vgf_vline_helper( x_pos+y, y_pos-x, 2*x, layer_data, color_index, width, height );
            vgf_vline_helper( x_pos-x, y_pos-y, 2*y, layer_data, color_index, width, height );
            vgf_vline_helper( x_pos-y, y_pos-x, 2*x, layer_data, color_index, width, height );
        }
    }
    else
    {
        // Render circle
        int16_t x_pos = pCircleData->x_pos;
        int16_t y_pos = pCircleData->y_pos;
        int16_t x = 0;
        int16_t y = pCircleData->radius;
        int16_t radius_error = 1 - pCircleData->radius;
        int16_t ddF_x = 1;
        int16_t ddF_y = -2 * pCircleData->radius;
        uint16_t radius = pCircleData->radius;

        // Draw points
        layer_data[ GET_XY( x_pos, y_pos+radius, width ) ] = color_index;
        layer_data[ GET_XY( x_pos, y_pos-radius, width ) ] = color_index;
        layer_data[ GET_XY( x_pos+radius, y_pos, width ) ] = color_index;
        layer_data[ GET_XY( x_pos-radius, y_pos, width ) ] = color_index;

        while ( x < y )
        {
            if ( radius_error >= 0 )
            {
                y--;
                ddF_y += 2;
                radius_error += ddF_y;
            }

            x++;
            ddF_x += 2;
            radius_error += ddF_x;

            layer_data[ GET_XY( x_pos + x, y_pos + y, width ) ] = color_index;
            layer_data[ GET_XY( x_pos - x, y_pos + y, width ) ] = color_index;
            layer_data[ GET_XY( x_pos + x, y_pos - y, width ) ] = color_index;
            layer_data[ GET_XY( x_pos - x, y_pos - y, width ) ] = color_index;
            layer_data[ GET_XY( x_pos + y, y_pos + x, width ) ] = color_index;
            layer_data[ GET_XY( x_pos - y, y_pos + x, width ) ] = color_index;
            layer_data[ GET_XY( x_pos + y, y_pos - x, width ) ] = color_index;
            layer_data[ GET_XY( x_pos - y, y_pos - x, width ) ] = color_index;
        }
    }


}

void vgf_render_triangle( tVGFDrawTriangle *pTriangleData, uint16_t *layer_data, uint8_t settings, uint8_t color_index, uint16_t width, uint16_t height )
{
    uint16_t x_pos1, y_pos1;
    uint16_t x_pos2, y_pos2;
    uint16_t x_pos3, y_pos3;

    if ( pTriangleData == NULL )
        return;

    x_pos1 = pTriangleData->x_pos1;
    y_pos1 = pTriangleData->y_pos1;
    x_pos2 = pTriangleData->x_pos2;
    y_pos2 = pTriangleData->y_pos2;
    x_pos3 = pTriangleData->x_pos3;
    y_pos3 = pTriangleData->y_pos3;

    if ( x_pos1 >= width ||
         y_pos1 >= height ||
         x_pos2 >= width ||
         y_pos2 >= height ||
         x_pos3 >= width ||
         y_pos3 >= height )
        return;

    if ( settings & VGF_OBJECT_SETTINGS_FILL )
    {
        // FILL TRIANGLE
        //
        // SORT coordinates
        if ( y_pos1 > y_pos2 )
        {
            SWAP( y_pos1, y_pos2 );
            SWAP( x_pos1, x_pos2 );
        }

        if ( y_pos2 > y_pos3 )
        {
            SWAP( y_pos2, y_pos3 );
            SWAP( x_pos2, x_pos3 );
        }

        if ( y_pos1 > y_pos2 )
        {
            SWAP( y_pos1, y_pos2 );
            SWAP( x_pos1, x_pos2 );
        }

        // ORDER should now be y_pos3 >= y_pos2 >= y_pos1
        // WE WILL FILL Triangle from bottom UP in Y coordinates

        if ( y_pos1 == y_pos3 )
        {
            // Y coordinates are all equal -- draw a line
            // Find lowest X and highest X
            uint16_t xl, xh;

            xh = x_pos1;
            xl = x_pos1;

            if ( x_pos2 < xl )
                xl = x_pos2;
            else if ( x_pos2 > xh )
                xh = x_pos2;

            if ( x_pos3 < xl )
                xl = x_pos3;
            else if ( x_pos3 > xh )
                xh = x_pos3;

            // DRAW horizontal line -- use a specific horizontal line helper here to improve performance.
            vgf_hline_helper( xl, y_pos1, (xh-xl), layer_data, color_index, width, height );
        }
        else
        {
            int16_t dx31 = (x_pos3 - x_pos1);
            int16_t dy31 = (y_pos3 - y_pos1);
            int16_t dx32 = (x_pos3 - x_pos2);
            int16_t dy32 = (y_pos3 - y_pos2);
            int16_t dy21 = (y_pos2 - y_pos1);
            int16_t dx21 = (x_pos2 - x_pos1);


            // 32-bit values as these can OVERFLOW with a 512x512 width/height
            // since they are increments of delta X
            int32_t sl, sh;     // High and low scanlines -- arbitrarily chosen

            uint16_t last_y, y;
            // Bresenham's algorithm for two halves of triangle
            sl = 0;
            sh = 0;

            // CHECK FOR flat bottom triangle
            if ( y_pos2 == y_pos3 )
                last_y = y_pos2;
            else
                last_y = y_pos2-1;

            // CHECK for flat top triangle
            if ( y_pos1 == y_pos2 )
            {
                uint16_t xl,xh;

                xl = x_pos1;
                xh = x_pos2;

                if ( xl > xh )
                    SWAP( xl, xh );

                vgf_hline_helper( xl, y_pos1, (xh-xl), layer_data, color_index, width, height );

                y = y_pos2;
            }
            else
            {
                for ( y = y_pos1; y <= last_y; y++ )
                {
                    uint16_t xh = x_pos1 + sh / dy31;
                    uint16_t xl = x_pos1 + sl / dy21;

                    sh += dx31;
                    sl += dx21;

                    if ( xl > xh )
                        SWAP( xl, xh );

                    // DRAW scan line between bresenham lines
                    vgf_hline_helper( xl, y, (xh-xl), layer_data, color_index, width, height );
                }
            }

            sh = dx31 * (y - y_pos1);
            sl = dx32 * (y - y_pos2);

            for ( ; y <= y_pos3; y++ )
            {
                uint16_t xh = x_pos1 + sh / dy31;
                uint16_t xl = x_pos2 + sl / dy32;

                sh += dx31;
                sl += dx32;

                if ( xl > xh )
                    SWAP( xl, xh );

                // DRAW scan line between bresenham lines
                vgf_hline_helper( xl, y, (xh-xl), layer_data, color_index, width, height );
            }
        }
    }
    else
    {
        vgf_line_helper( x_pos1, y_pos1, x_pos2, y_pos2, layer_data, color_index, width, height );
        vgf_line_helper( x_pos2, y_pos2, x_pos3, y_pos3, layer_data, color_index, width, height );
        vgf_line_helper( x_pos3, y_pos3, x_pos1, y_pos1, layer_data, color_index, width, height );
    }
}


void vgf_render_line( tVGFDrawLine *pLineData, uint16_t *layer_data, uint8_t settings, uint8_t color_index, uint16_t width, uint16_t height )
{
    uint16_t x_start, y_start;
    uint16_t x_end, y_end;

    if ( pLineData == NULL )
        return;

    x_start = pLineData->x_start;
    y_start = pLineData->y_start;
    x_end = pLineData->x_end;
    y_end = pLineData->y_end;

    if ( x_start >= width ||
         y_start >= height ||
         x_end >= width ||
         y_end >= height )
        return;

    if ( x_start > x_end )
        return;

    if ( y_start > y_end )
        return;

    vgf_line_helper( x_start, y_start, x_end, y_end, layer_data, color_index, width, height );

    if ( settings & VGF_OBJECT_SETTINGS_FILL )
    {
        // No fill for lines!
    }
}
