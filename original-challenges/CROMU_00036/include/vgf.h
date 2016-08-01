/*

Author: Debbie Nuttall <debbie@cromulence.co>

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
#ifndef VGF_H
#define VGF_H
#include "canvas.h"

#define VGF_MAGIC 0x78330909
#define VGF_VERSION 0x0001
#define VGF_MAX_WIDTH 512
#define VGF_MAX_HEIGHT 512

#define VGF_OBJECT_TRIANGLE 1
#define VGF_OBJECT_RECTANGLE 0 
#define VGF_OBJECT_LINE 2 
#define VGF_OBJECT_CIRCLE 3
#define VGF_OBJECT_SQUARE 4
#define VGF_OBJECT_SPRAY 5
#define VGF_OBJECT_LAST 100

#pragma pack(push, 1)

typedef struct VGF_Header_s {
  uint32_t magic;
  uint16_t version;
  uint16_t y_size;
  uint16_t x_size;
  uint8_t layers;
} VGF_Header;


typedef struct VGF_Object_s {
  uint8_t type;
  uint8_t layer;
  uint8_t color;
  uint8_t fill;
} VGF_Object;

typedef struct VGF_Triangle_s {
  uint16_t  x0;
  uint16_t  y0;
  uint16_t  x1;
  uint16_t  y1;
  uint16_t  x2;
  uint16_t  y2;
} VGF_Triangle;

typedef struct VGF_Rectangle_s {
  uint16_t x_start;
  uint16_t y_start;
  uint16_t x_len;
  uint16_t y_len;
} VGF_Rectangle;

typedef struct VGF_Square_s {
  uint16_t x_start;
  uint16_t y_start;
  uint16_t x_len;
} VGF_Square;

typedef struct VGF_Line_s {
  uint16_t x_start;
  uint16_t y_start;
  uint16_t x_end;
  uint16_t y_end;
} VGF_Line;

typedef struct VGF_Circle_s {
  uint16_t x_start;
  uint16_t y_start;
  uint16_t radius;
} VGF_Circle;

typedef struct VGF_Spray_s {
  uint16_t x_start;
  uint16_t y_start;
  uint16_t width;
  uint16_t density;
  uint32_t magic;
} VGF_Spray;

#pragma pack(pop)

int VGFVerify(VGF_Header *header);
int VGFProcess(uint8_t **file_data_in, uint8_t *file_end, Canvas *c);

#endif