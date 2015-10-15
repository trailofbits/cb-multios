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
#ifndef CANVAS_H
#define CANVAS_H

#define CANVAS_MAX_LAYERS 6
#define CANVAS_MAX_COLORS 20
#define CANVAS_DEFAULT_COLOR CANVAS_MAX_COLORS

#pragma pack(push, 1)
typedef struct RGB_Color_s {
  uint8_t red;
  uint8_t blue;
  uint8_t green;
} RGB_Color;
#pragma pack(pop)

typedef struct Canvas_s {
  uint16_t y_size;
  uint16_t x_size;
  uint8_t num_layers;
  uint8_t *layers[CANVAS_MAX_LAYERS];
  RGB_Color colors[CANVAS_MAX_COLORS + 1];
} Canvas;

int CreateCanvas(Canvas **can, uint16_t y_size, uint16_t x_size, uint8_t layers);
void FlattenCanvas(Canvas *c);
void DestroyCanvas(Canvas **c);

#endif