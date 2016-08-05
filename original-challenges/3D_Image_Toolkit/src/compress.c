/*

Copyright (c) 2016 Cromulence LLC

Authors: Dan Czarnecki <cgc@cromulence.com>

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

#include "compress.h"

// 8-bit color
//
//    1  1  1  1  1  1  1  1
//    R  R  R  G  G  B  B  B
//

enum {
  R,
  G,
  B
};

int red_blue[8]  = { 0x00, 0x20, 0x40, 0x60, 0xA0, 0xC0, 0xE0, 0xFF };
int green[4]     = { 0x00, 0x60, 0xB0, 0xFF };

uint8_t ClosestMatch(uint8_t type, int16_t val) {
  uint8_t close_diff = 0xff;
  uint8_t temp_diff = 0;
  uint8_t max_idx = ((type == R || type == B) ? 8 : 4);
  uint8_t close_idx = max_idx;

  int i;

  for(i = 0; i < max_idx; i++) {
    if (type == R || type == B)
      temp_diff = ABS((int)(val - red_blue[i]));
    else
      temp_diff = ABS((int)(val - green[i]));

    if (temp_diff < close_diff) {
      close_diff = temp_diff;
      close_idx = i;
    }
  }

  return close_idx;

}

void Compress(t3DCPixel **px_list, uint8_t *compressed_data, uint16_t *data_len) {
  if (px_list == NULL) {
    return;
  }

  uint8_t color = 0;
  uint8_t coord = 0;

  t3DCPixel *px = NULL;
  uint16_t count = MAX_PIXELS * 7; // (x, y, z, color)
  uint16_t i = 0;
  int p_idx = 0;

  while (i < count) {
    color = 0;
    px = px_list[p_idx++];
    // red
    color += (ClosestMatch(R, px->r) << 5);

    // green
    color += (ClosestMatch(G, px->g) << 3);

    // blue
    color += (ClosestMatch(B, px->b) << 0);

    memcpy(compressed_data+i, &px->x, sizeof(int16_t));
    i += sizeof(int16_t);

    memcpy(compressed_data+i, &px->y, sizeof(int16_t));
    i += sizeof(int16_t);

    memcpy(compressed_data+i, &px->z, sizeof(int16_t));
    i += sizeof(int16_t);

    memcpy(compressed_data+i, &color, 1);
    i++;
  }

  memcpy(data_len, &i, 2);

  return;
}


void Decompress(uint8_t *in_data, uint8_t *out_data, uint16_t *data_len) {
  uint32_t in_offset = 0;
  uint32_t out_offset = 0;

  int p_idx = 0;
  uint8_t color;
  uint8_t r,g,b;

  while (in_offset < *data_len) {
    memcpy(out_data+out_offset, in_data+in_offset, sizeof(int16_t));
    out_offset += sizeof(int16_t);
    in_offset += sizeof(int16_t);

    memcpy(out_data+out_offset, in_data+in_offset, sizeof(int16_t));
    out_offset += sizeof(int16_t);
    in_offset += sizeof(int16_t);

    memcpy(out_data+out_offset, in_data+in_offset, sizeof(int16_t));
    out_offset += sizeof(int16_t);
    in_offset += sizeof(int16_t);

    color = in_data[in_offset++];

    // red
    r = ((0xe0) & color) >> 5;

    // green
    g = ((0x18) & color) >> 3;

    // blue
    b = ((0x7) & color) >> 0;

    out_data[out_offset++] = red_blue[r];
    out_data[out_offset++] = green[g];
    out_data[out_offset++] = red_blue[b];

    out_data[out_offset++] = 0xff;

  }

  memcpy(data_len, &out_offset, 2);

  return;
}

void WriteOut(t3DCPixel **px_list, uint8_t *data, uint16_t data_len) {
  // load into our pixel data

  if (px_list == NULL) {
    return;
  }

  uint16_t offset = 0;
  uint16_t i = 0;
  t3DCPixel *tmp;

  while (offset < data_len) {
    tmp = px_list[i];

    offset += 6;

    memcpy(&tmp->r, data+offset, 1);
    offset++;
    memcpy(&tmp->g, data+offset, 1);
    offset++;
    memcpy(&tmp->b, data+offset, 1);
    offset++;
    tmp->a = 0xff;
    offset++;

    i++;

  }

}
