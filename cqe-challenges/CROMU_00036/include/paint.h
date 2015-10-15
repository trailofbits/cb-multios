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
#ifndef PAINT_H
#define PAINT_H
#include "vgf.h"
#include "canvas.h"

RGB_Color *GetColor(Canvas *c, uint16_t y, uint16_t x, uint8_t layer);
int GetColorIndex(Canvas *c, uint16_t y, uint16_t x, uint8_t layer);
void SetColor(Canvas *c, uint16_t y, uint16_t x, uint8_t layer, uint8_t color);
void PaintTriangle(Canvas *c, uint8_t layer, uint8_t color, uint8_t fill, VGF_Triangle *triangle);
void ConnectPoints(Canvas *c, uint8_t layer, uint8_t color, uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end);
void PaintRectangle(Canvas *c, uint8_t layer, uint8_t color, uint8_t fill, VGF_Rectangle *rectangle);
void PaintSquare(Canvas *c, uint8_t layer, uint8_t color, uint8_t fill, VGF_Square *square);
void PaintSpray(Canvas *c, uint8_t layer, uint8_t color, uint8_t fill, VGF_Spray *spray);
void PaintLine(Canvas *c, uint8_t layer, uint8_t color, uint8_t fill, VGF_Line *line);
void PaintCircle(Canvas *c, uint8_t layer, uint8_t color, uint8_t fill, VGF_Circle *circle);

#endif