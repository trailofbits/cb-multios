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
#include "io.h"
#include "pmp.h"

int PMPGenerate(PMP_File *pmp, Canvas *c) {
  int row_pad = 0;
  int odd_bytes = (c->x_size * 3) % 4;
  if (odd_bytes != 0) {
    row_pad = 4 - odd_bytes;
  }

  pmp->header.magic = 0x4d50;
  pmp->header.reserved = 0;
  pmp->header.header_size = sizeof(PMP_Info) + sizeof(PMP_Header);
  pmp->header.filesize = pmp->header.header_size + c->y_size * (c->x_size * 3 + row_pad);

  int file_pad = 0;
  odd_bytes = pmp->header.filesize % 4;
  if (odd_bytes != 0) {
    file_pad = 4 - odd_bytes;
    pmp->header.filesize = pmp->header.filesize + file_pad;
  }

  pmp->data_size = c->y_size * (c->x_size * 3 + row_pad) + file_pad;
  if (allocate(pmp->data_size, 0, (void **)&pmp->data) != 0) {
    _terminate(-1);
  } 
  memset(pmp->data, 0, pmp->data_size); 

  pmp->info.size = sizeof(PMP_Info);
  pmp->info.y_size = c->y_size;
  pmp->info.x_size = c->x_size;
  pmp->info.magic1 = 0x00180001;
  pmp->info.reserved1 = 0;
  pmp->info.image_size = c->y_size * (c->x_size * 3 + row_pad);
  pmp->info.magic2 = 0xb13;
  pmp->info.magic3 = 0xb13;
  pmp->info.reserved2 = 0;
  pmp->info.reserved3 = 0;

  char *data = pmp->data;
  int x, y;
  for (y = c->y_size - 1; y >= 0; y--) {
    for (x = 0; x < c->x_size; x++) {
      RGB_Color *color = GetColor(c, y, x, 0);
      memcpy(data, color, sizeof(RGB_Color));
      data += sizeof(RGB_Color);
    }
    data += row_pad;
  }
  return 0;
}

// Transmit the PMP file 
// returns 0 for success, -1 for failure
int PMPTransmit(PMP_File *pmp) {
  if (SendAll(&pmp->header, sizeof(PMP_Header)) != 0) {
    return -1;
  }
  if (SendAll(&pmp->info, sizeof(PMP_Info)) != 0) {
    return -1;
  }
  if (SendAll(pmp->data, pmp->data_size) != 0) {
    return -1;
  }
  return 0;
}


// Deallocate the memory used within the PMP_File structure
void PMPDeallocate(PMP_File *pmp) {
  if (pmp->data != 0) {
    deallocate(pmp->data, pmp->data_size);
  }
  pmp->data_size = 0;
}
