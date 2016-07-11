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

// Allocates memory for each layer and creates new canvas object
int CreateCanvas(Canvas **can, uint16_t y_size, uint16_t x_size, uint8_t layers) {
  
  if (layers > CANVAS_MAX_LAYERS) {
    return -1;
  }
  #ifdef PATCHED
  if (layers == 0) {
    return -1;
  }
  #endif 
  Canvas *c;
  if (allocate(sizeof(Canvas), 0, (void **)&c) != 0) {
    _terminate(-1);
  }
  memset(c, 0, sizeof(Canvas));
  c->y_size = y_size;
  c->x_size = x_size;

  // Create layers
  for (int i = 0; i < layers; i++) {
    if (allocate(y_size * x_size, 0, (void **)&(c->layers[i])) != 0) {
      _terminate(-1);
    }
    // Initialize with default color
    memset(c->layers[i], CANVAS_DEFAULT_COLOR, y_size * x_size);
  }
  c->num_layers = layers;
  *can = c;
  return 0;
}

// Deallocate the memory used by the Canvas structure
void DestroyCanvas(Canvas **c) {
  if (*c == NULL) {
    return;
  }
  for (int l=0; l < (*c)->num_layers; l++) {
    if ((*c)->layers[l] != NULL) {
      deallocate((*c)->layers[l], (*c)->y_size * (*c)->x_size);
      (*c)->layers[l] = NULL;
    }
  }
  deallocate(*c, sizeof(Canvas));
  *c = NULL;
}

// Flattens the canvas 
// Starting from layer 1 and moving up, any non-default colors are overlayed onto layer 0
void FlattenCanvas(Canvas *c) {
  for (int l = 1; l < c->num_layers; l++) {
    for (int y = 0; y < c->y_size; y++) {
      for (int x = 0; x < c->x_size; x++) {
        int color = GetColorIndex(c, y, x, l);
        if (color != CANVAS_DEFAULT_COLOR) {
          SetColor(c, y, x, 0, color);
        }
      }
    }
  }
}