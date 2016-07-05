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
#ifndef __VGF_H__
#define __VGF_H__

#include <stdint.h>

#define VGF_MAGIC       (0x78330909)
#define VGF_VERSION     (0x0001)

#define     VGF_OBJECT_RECT         (0)
#define     VGF_OBJECT_TRIANGLE     (1)
#define     VGF_OBJECT_LINE         (2)
#define     VGF_OBJECT_CIRCLE       (3)
#define     VGF_OBJECT_END          (100)

#define     VGF_OBJECT_SETTINGS_NOFILL      (0)
#define     VGF_OBJECT_SETTINGS_FILL        (1)

#define     VGF_ERROR_INVALID_FILE      (-1)
#define     VGF_ERROR_INVALID_VERSION   (-2)
#define     VGF_PARSE_SUCCESS           (0)

// VGF maximums
#define VGF_MAX_X       (512)
#define VGF_MAX_Y       (512)

#define VGF_MAX_LAYER   (6)

#define VGF_MAX_COLOR   (200)

// Main file format header
struct VGF_HEADER
{
    uint32_t    vgfMagic;
    uint16_t    vgfVersion;
    uint16_t    vgfHeight;      // Height in pixels
    uint16_t    vgfWidth;       // Width in pixels
    uint8_t     vgfLayerCount;  // Number of layers to render on
} __attribute__ ((__packed__));

typedef struct VGF_HEADER tVGFHeader;

// VGF files are composed of a collection of VGF objects
struct VGF_OBJECT_HEADER
{
    uint8_t     object_type;
    uint8_t     object_layer;
    uint8_t     object_color_index;     // Index to the objects color
    uint8_t     object_settings;
} __attribute__ ((__packed__));

typedef struct VGF_OBJECT_HEADER tVGFObjectHeader;

// The VGF color table
struct VGF_COLOR_TABLE
{
    uint8_t     color_count;
} __attribute__ ((__packed__));

typedef struct VGF_COLOR_TABLE tVGFColorTable;

// A single color reference in the color index table
struct VGF_COLOR_HEADER
{
    uint8_t    red;
    uint8_t    green;
    uint8_t    blue;
} __attribute__ ((__packed__));

typedef struct VGF_COLOR_HEADER tVGFColorHeader;

// A VGF circle object
struct VGF_DRAW_CIRCLE
{
    uint16_t    x_pos;
    uint16_t    y_pos;
    uint16_t    radius;
} __attribute__ ((__packed__));

typedef struct VGF_DRAW_CIRCLE tVGFDrawCircle;

// A VGF rectangle object
struct VGF_DRAW_RECT
{
    uint16_t    x_start;
    uint16_t    y_start;
    uint16_t    x_len;
    uint16_t    y_len;
} __attribute__ ((__packed__));

typedef struct VGF_DRAW_RECT tVGFDrawRect;

// A VGF triangle object
struct VGF_DRAW_TRIANGLE
{
    uint16_t    x_pos1;
    uint16_t    y_pos1;
    uint16_t    x_pos2;
    uint16_t    y_pos2;
    uint16_t    x_pos3;
    uint16_t    y_pos3;
} __attribute__ ((__packed__));

typedef struct VGF_DRAW_TRIANGLE tVGFDrawTriangle;

// A VGF line object
struct VGF_DRAW_LINE
{
    uint16_t    x_start;
    uint16_t    y_start;
    uint16_t    x_end;
    uint16_t    y_end;
} __attribute__ ((__packed__));

typedef struct VGF_DRAW_LINE tVGFDrawLine;

typedef struct VGF_OBJECT_TABLE
{
    tVGFObjectHeader obj_header;
    union
    {
        tVGFDrawLine        obj_line;
        tVGFDrawTriangle    obj_triangle;
        tVGFDrawRect        obj_rect;
        tVGFDrawCircle      obj_circle;
    } obj_data;

    // Next in the list
    struct VGF_OBJECT_TABLE *pNext;
} tVGFObjectTable;

typedef struct VGF_PARSED_FILE
{
    tVGFHeader file_header;
    tVGFObjectTable *pObjectList;

    uint8_t color_count;
    tVGFColorHeader *pColorTable;

} tVGFParsedFile;

uint16_t vgf_get_width( tVGFParsedFile *pFile );
uint16_t vgf_get_height( tVGFParsedFile *pFile );
int32_t vgf_parse_data( uint8_t *pData, uint32_t dataLen, tVGFParsedFile **pParsedFile );
void vgf_destroy_file( tVGFParsedFile *pFile );

int32_t vgf_get_render_size( tVGFParsedFile *pFile );
int32_t vgf_render_file( tVGFParsedFile *pFile, uint8_t *pDest, uint32_t *pDestLen );

void vgf_render_rect( tVGFDrawRect *pRectData, uint16_t *layer_data, uint8_t settings, uint8_t color_index, uint16_t pixel_width, uint16_t pixel_height );
void vgf_render_line( tVGFDrawLine *pLineData, uint16_t *layer_data, uint8_t settings, uint8_t color_index, uint16_t pixel_width, uint16_t pixel_height );
void vgf_render_triangle( tVGFDrawTriangle *pTriangleData, uint16_t *layer_data, uint8_t settings, uint8_t color_index, uint16_t pixel_width, uint16_t pixel_height );
void vgf_render_circle( tVGFDrawCircle *pCircleData, uint16_t *layer_data, uint8_t settings, uint8_t color_index, uint16_t pixel_wieth, uint16_t pixel_height );

#endif // __VGF_H___
