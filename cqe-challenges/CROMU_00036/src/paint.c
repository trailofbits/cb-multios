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
#include <libcgc.h>
#include "stdlib.h"
#include "stdint.h"
#include "canvas.h"
#include "paint.h"


// Get the RGB color at a particular location in the canvas
RGB_Color *GetColor(Canvas *c, uint16_t y, uint16_t x, uint8_t layer) {
  uint8_t *current_layer = c->layers[layer];
  int color = current_layer[y * c->x_size + x];
  return &c->colors[color];
}

// Get the color index at a particular location in the canvas
int GetColorIndex(Canvas *c, uint16_t y, uint16_t x, uint8_t layer) {
  uint8_t *current_layer = c->layers[layer];
  return current_layer[y * c->x_size + x];
}

// Set the color index at a particular location in the canvas
void SetColor(Canvas *c, uint16_t y, uint16_t x, uint8_t layer, uint8_t color) {

  uint8_t *current_layer = c->layers[layer];

  if ( current_layer == NULL ) {
    return;
  }

#ifdef PATCHED
  if (y >= c->y_size || x >= c->x_size) {
    return;
  }
#endif 

  current_layer[y * c->x_size + x] = color;
}

void PaintTriangle(Canvas *c, uint8_t layer, uint8_t color, uint8_t fill, VGF_Triangle *triangle) {
  if (triangle->x0 >= c->x_size || triangle->x1 >= c->x_size || triangle->x2 >= c->x_size) {
    return;
  }
  if (triangle->y0 >= c->y_size || triangle->y1 >= c->y_size || triangle->y2 >= c->y_size) {
    return;
  }

  if (fill == 0) {
    // Draw outline
    ConnectPoints(c, layer, color, triangle->x0, triangle->y0, triangle->x1, triangle->y1);
    ConnectPoints(c, layer, color, triangle->x2, triangle->y2, triangle->x0, triangle->y0);
    ConnectPoints(c, layer, color, triangle->x1, triangle->y1, triangle->x2, triangle->y2);
  } else {
    // Fill triangle
    // Sort points top to bottom
    uint16_t *x0, *y0, *x1, *y1, *x2, *y2;

    if (triangle->y0 > triangle->y1) {
      x0 = &triangle->x1;
      y0 = &triangle->y1;
      x1 = &triangle->x0;
      y1 = &triangle->y0;
    } else {
      x0 = &triangle->x0;
      y0 = &triangle->y0;
      x1 = &triangle->x1;
      y1 = &triangle->y1;
    }
    if (*y1 > triangle->y2) {
      x2 = x1;
      y2 = y1;
      if (*y0 > triangle->y2) {
        x1 = x0;
        y1 = y0;
        x0 = &triangle->x2;
        y0 = &triangle->y2;
      }
      else {
        x1 = &triangle->x2;
        y1 = &triangle->y2;
      }
    } else {
      x2 = &triangle->x2;
      y2 = &triangle->y2;
    }

    // ...
    uint32_t last_y, x_low, x_high;
    uint32_t y;

    x_low = *x0;
    x_high = *x0;

    if (*x1 < x_low) {
      x_low = *x1;
    } else if (*x1 > x_high) {
      x_high = *x1;
    } 
    if (*x2 < x_low) {
      x_low = *x2;
    } else if (*x2 > x_high) {
      x_high = *x2;
    }

    // Flat triangle
    if (*y2 == *y0) {
      if (x_high > x_low) {
        ConnectPoints(c, layer, color, x_low, *y0, x_high - 1, *y0);
      }
      return;
    }
   
    if (*y1 == *y2) {
      last_y = *y1;
    } else {
      last_y = *y1 - 1;
    }

    int step_low, step_high;
    step_low = 0;
    step_high = 0;

    if (*y0 == *y1) {
      // Draw base of triangle
      x_low = *x0;
      x_high = *x1;
      if (x_low > x_high) {
        x_high = *x0;
        x_low = *x1;
      }
      if (x_high > x_low) {
        ConnectPoints(c, layer, color, x_low, *y0, x_high - 1, *y0);
      }
      y = *y1;
    } else {
      y = *y0;
      while (y <= last_y) {
        x_high = *x0 + step_high / (*y2 - *y0);
        x_low = *x0 + step_low / (*y1 - *y0);

        step_high += *x2 - *x0;
        step_low += *x1 - *x0;

        if (x_low > x_high) {
          int swap = x_low;
          x_low = x_high;
          x_high = swap;
        }

        if (x_high > x_low) {
          ConnectPoints(c, layer, color, x_low, y, x_high - 1, y);
        }
        y++;
      }
    }

    step_high = (*x2 - *x0) * (y - *y0);
    step_low = (*x2 - *x1) * (y - *y1);

    while (y <= *y2) {
      x_high = *x0 + step_high / (*y2 - *y0);
      x_low = *x1 + step_low / (*y2 - *y1);

      step_high += *x2 - *x0;
      step_low += *x2 - *x1;

      if (x_low > x_high) {
        int swap = x_low;
        x_low = x_high;
        x_high = swap;
      }

      if (x_high > x_low) {
        ConnectPoints(c, layer, color, x_low, y, x_high - 1, y);
      }
      y++;
    }
  } 
}


void PaintRectangle(Canvas *c, uint8_t layer, uint8_t color, uint8_t fill, VGF_Rectangle *rectangle) {
  if ((rectangle->x_start >= c->x_size) || (rectangle->y_start >= c->y_size)) {
    return;
  }
  if (rectangle->x_start + rectangle->x_len >= c->x_size) {
    return;
  }
  if (rectangle->y_start + rectangle->y_len >= c->y_size) {
    return;
  }

  if (rectangle->x_len == 0 && rectangle->y_len == 0) {
    return;
  }

  ConnectPoints(c, layer, color, rectangle->x_start, rectangle->y_start, rectangle->x_start, rectangle->y_start + rectangle->y_len);
  ConnectPoints(c, layer, color, rectangle->x_start, rectangle->y_start + rectangle->y_len, rectangle->x_start + rectangle->x_len, rectangle->y_start + rectangle->y_len);
  ConnectPoints(c, layer, color, rectangle->x_start + rectangle->x_len, rectangle->y_start, rectangle->x_start + rectangle->x_len, rectangle->y_start + rectangle->y_len);
  ConnectPoints(c, layer, color, rectangle->x_start, rectangle->y_start, rectangle->x_start + rectangle->x_len, rectangle->y_start );

  // Fill if necessary
  if ((fill == 1) && (rectangle->x_len > 1)) {
    for (uint16_t y_position = 1; y_position < rectangle->y_len; y_position++) {
      ConnectPoints(c, layer, color, rectangle->x_start + 1, rectangle->y_start + y_position, rectangle->x_start + rectangle->x_len - 1, rectangle->y_start + y_position);
    }
  }

}

void PaintSquare(Canvas *c, uint8_t layer, uint8_t color, uint8_t fill, VGF_Square *square) {
  if ((square->x_start >= c->x_size) || (square->y_start >= c->y_size)) {
    return;
  }
  if (square->x_start + square->x_len >= c->x_size) {
    return;
  }
  if (square->y_start + square->x_len >= c->y_size) {
    return;
  }

  if (square->x_len == 0) {
    return;
  }

  ConnectPoints(c, layer, color, square->x_start, square->y_start, square->x_start, square->y_start + square->x_len);
  ConnectPoints(c, layer, color, square->x_start, square->y_start + square->x_len, square->x_start + square->x_len, square->y_start + square->x_len);
  ConnectPoints(c, layer, color, square->x_start + square->x_len, square->y_start, square->x_start + square->x_len, square->y_start + square->x_len);
  ConnectPoints(c, layer, color, square->x_start, square->y_start, square->x_start + square->x_len, square->y_start );

  // Fill if necessary
  if ((fill == 1) && (square->x_len > 1)) {
    for (uint16_t y_position = 1; y_position < square->x_len; y_position++) {
      ConnectPoints(c, layer, color, square->x_start + 1, square->y_start + y_position, square->x_start + square->x_len - 1, square->y_start + y_position);
    }
  }

}

void ConnectPoints(Canvas *c, uint8_t layer, uint8_t color, uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end) {

  int width, height, dots, x_dir, y_dir;
  if (x_end > x_start) {
    width = x_end - x_start;
    x_dir = 1;
  } else {
    width = x_start - x_end;
    x_dir = -1;
  }
  if (y_end > y_start) {
    height = y_end - y_start;
    y_dir = 1;
  } else {
    height = y_start - y_end;
    y_dir = -1;
  }
  if (height > width) {
    dots = height;
  } else {
    dots = width;
  }

  int x = x_start;
  int y = y_start;
  int x_inc = 0;
  int y_inc = 0;
  int count = 0;

  while (count <= dots + 1) {
    SetColor(c, y, x, layer, color);
    x_inc += width;
    y_inc += height;
    if (x_inc > dots) {
      x+=x_dir;
      x_inc -= dots;
    }
    if (y_inc > dots)  {
      y+=y_dir;
      y_inc -= dots;
    }
    count++;
  }
}

void PaintLine(Canvas *c, uint8_t layer, uint8_t color, uint8_t fill, VGF_Line *line) {
  if ((line->x_start >= c->x_size) || (line->x_start > line->x_end)) {
    return;
  }
  if ((line->y_start >= c->y_size) || (line->y_start > line->y_end)) {
    return;
  }
  if ((line->y_end >= c->y_size) || (line->x_end >= c->x_size)) {
    return;
  }
  ConnectPoints(c, layer, color, line->x_start, line->y_start, line->x_end, line->y_end);
}

void PaintCircle(Canvas *c, uint8_t layer, uint8_t color, uint8_t fill, VGF_Circle *circle) {

  if ((circle->x_start >= c->x_size) || (circle->y_start >= c->y_size)) {
    return;
  }
  if ((circle->x_start + circle->radius >= c->x_size) ||
    (circle->y_start + circle->radius >= c->y_size)) {
    return;
  }
   if ((circle->x_start - circle->radius < 0) ||
    (circle->y_start - circle->radius < 0)) {
    return;
  }
  int x, y, x_pos, y_pos;
  x = 0;
  y = circle->radius;
  int radius_error = 1 - circle->radius;
  int ddf_x, ddf_y;
  ddf_x = 1;
  ddf_y = -2 * circle->radius;
  x_pos = circle->x_start;
  y_pos = circle->y_start;

  if (fill == 0) {
    SetColor(c, y_pos + circle->radius, x_pos, layer, color);
    SetColor(c, y_pos - circle->radius, x_pos, layer, color);
    SetColor(c, y_pos, x_pos + circle->radius, layer, color);
    SetColor(c, y_pos, x_pos - circle->radius, layer, color);
  } else {
    ConnectPoints(c, layer, color, x_pos, y_pos - y, x_pos, y_pos + y - 1);
  }
  while (x < y) {
    if (radius_error >= 0) {
      y--;
      ddf_y += 2;
      radius_error += ddf_y;
    }
    x++;
    ddf_x += 2;
    radius_error += ddf_x;

    if (fill == 0) {
      // Draw outline
      SetColor(c, y_pos + y, x_pos + x, layer, color);
      SetColor(c, y_pos + y, x_pos - x, layer, color);
      SetColor(c, y_pos - y, x_pos + x, layer, color);
      SetColor(c, y_pos - y, x_pos - x, layer, color);
      
      SetColor(c, y_pos + x, x_pos + y, layer, color);
      SetColor(c, y_pos + x, x_pos - y, layer, color);
      SetColor(c, y_pos - x, x_pos + y, layer, color);
      SetColor(c, y_pos - x, x_pos - y, layer, color);
    } else {
      // Fill circle
      if (y > 0) { 
        ConnectPoints(c, layer, color, x_pos + x, y_pos - y, x_pos + x, y_pos + y - 1);
        ConnectPoints(c, layer, color, x_pos - x, y_pos - y, x_pos - x, y_pos + y - 1);
      } 
      if (x > 0) {
        ConnectPoints(c, layer, color, x_pos + y, y_pos - x, x_pos + y, y_pos + x - 1);
        ConnectPoints(c, layer, color, x_pos - y, y_pos - x, x_pos - y, y_pos + x - 1);
      }
    }
  }
}


void PaintSpray(Canvas *c, uint8_t layer, uint8_t color, uint8_t fill, VGF_Spray *spray) {

  if ((spray->x_start >= c->x_size) || (spray->y_start >= c->y_size)) {
    return;
  }

  if (spray->magic != 0x59745974) {
    return;
  }

  if (spray->density > 100 || spray->density == 0) {
    return;
  }

  int step = 100 / spray->density;

  if (step <= 0) {
    return;
  }

  int x_pos = spray->x_start;
  int y_pos = spray->y_start;
  int width = spray->width;

  while ((x_pos < spray->x_start + width) && (x_pos < c->x_size)) {
    SetColor(c, y_pos, x_pos, layer, color);
    x_pos += step;
  }

  x_pos = spray->x_start;

  while ((x_pos > spray->x_start - width) && (x_pos >= 0)) {
    SetColor(c, y_pos, x_pos, layer, color);
    x_pos -= step;
  }  

  x_pos = spray->x_start;

  while ((y_pos < spray->y_start + width) && (y_pos < c->y_size)) {
    SetColor(c, y_pos, x_pos, layer, color);
    y_pos += step;
  }

  y_pos = spray->y_start;

  while ((y_pos > spray->y_start - width) && (y_pos >= 0)) {
    SetColor(c, y_pos, x_pos, layer, color);
    y_pos -= step;
  }

  SetColor(c, spray->y_start, spray->x_start + width, layer, color);
  SetColor(c, spray->y_start, spray->x_start - width, layer, color);
  SetColor(c, spray->y_start + width, spray->x_start, layer, color);
  SetColor(c, spray->y_start - width, spray->x_start, layer, color);

}

