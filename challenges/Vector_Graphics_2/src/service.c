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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_canvas.h"
#include "cgc_paint.h"
#include "cgc_io.h"
#include "cgc_vgf.h"
#include "cgc_pmp.h"

int main(int cgc_argc, char *cgc_argv[]) {
  uint16_t file_length;

  // Read 2 byte length field
  if (cgc_ReceiveAll(&file_length, sizeof(file_length)) != 0) {
    return -1;
  }
  
  // Allocate space for file
  uint8_t *file_data;
  if (cgc_allocate(file_length, 0, (void **)&file_data) != 0) {
    cgc__terminate(-1);
  }
  uint8_t *file_end = file_data + file_length;

  // Read VGF File 
  if (cgc_ReceiveAll(file_data, file_length) != 0) {
    return -1;
  }

  // Verify image header
  VGF_Header *header = (VGF_Header *)file_data;
  file_data += sizeof(VGF_Header);
  if (file_data >= file_end) {
    return -1;
  }
  if (cgc_VGFVerify(header) != 0) {
    return -1;
  }

  // Create canvas
  Canvas *c;
  if (cgc_CreateCanvas(&c, header->y_size, header->x_size, header->layers) != 0) {
    return -1;
  }

  // Process image objects (render layers)
  if (cgc_VGFProcess(&file_data,file_end, c) != 0) {
    return -1;
  }

  // Process image colors
  uint8_t num_colors = *file_data;
  file_data += 1;
 
  if (num_colors > CANVAS_MAX_COLORS) {
    return -1;
  }

  // Process colors
  for (int i = 0; i < num_colors; i++) {
    if (file_data >= file_end) {
      return -1;
    }
    c->colors[i].red = *(uint8_t *)(file_data + 2);
    c->colors[i].blue = *(uint8_t *)(file_data + 1);
    c->colors[i].green = *(uint8_t *)file_data;
    file_data += sizeof(RGB_Color);
  }
    
  // Flatten Canvas
  cgc_FlattenCanvas(c);

  // Generate the PMP file from the canvas
  PMP_File pmp;
  if (cgc_PMPGenerate(&pmp, c) != 0) {
    return -1;
  }

  // Transmit the PMP file
  if (cgc_PMPTransmit(&pmp) != 0) {
    return -1;
  }

  // Deallocate the PMP file and canvas
  cgc_PMPDeallocate(&pmp);
  cgc_DestroyCanvas(&c);
  
  return 0;
}