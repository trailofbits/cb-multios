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
#ifndef SERVICE_H
#define SERVICE_H

#include "stdlib.h"

#define MAX_FILTERS 16

#define MODE_FILE 1
#define MODE_STREAM 2

#define DISPLAY_PHYSICAL    0x0001
#define DISPLAY_TRANSPORT   0x0002
#define DISPLAY_NETWORK     0x0004
#define DISPLAY_APPLICATION 0x0008
#define DISPLAY_STATS       0x0010
#define DISPLAY_CONTENT     0x0020

#define PHYSICAL_LAYER    1
#define TRANSPORT_LAYER     2
#define NETWORK_LAYER     3
#define APPLICATION_LAYER 4

typedef struct SystemState_s {
  uint8_t mode;
  uint16_t display_flags;
  uint8_t num_filters;
  struct PacketFilter_s *filters[MAX_FILTERS];
  struct Statistics_s *stats;
} SystemState;

#endif