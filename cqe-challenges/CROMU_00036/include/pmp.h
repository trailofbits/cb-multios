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
#ifndef PMP_H
#define PMP_H

#pragma pack(push, 1)
typedef struct PMP_Header_s {
  uint16_t magic;
  uint32_t filesize;
  uint32_t reserved;
  uint32_t header_size;
} PMP_Header;

typedef struct PMP_Info_s {
  uint32_t size;
  uint32_t x_size;
  uint32_t y_size;
  uint32_t magic1;
  uint32_t reserved1;
  uint32_t image_size;
  uint32_t magic2;
  uint32_t magic3;
  uint32_t reserved2;
  uint32_t reserved3;
} PMP_Info;

typedef struct PMP_File_s {
  PMP_Header header;
  PMP_Info info;
  int data_size;
  void *data;
} PMP_File;
#pragma pack(pop)

int PMPGenerate(PMP_File *pmp, Canvas *c);
int PMPTransmit(PMP_File *pmp);
void PMPDeallocate(PMP_File *pmp);

#endif
