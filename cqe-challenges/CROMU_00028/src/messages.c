/*

Author: Bryce Kerley <bk@cromulence.co>

Copyright (c) 2014-2015 Cromulence LLC

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

// Generated at 2015-01-25 14:32:33 -0500
#include "protocol.h"
#include "messages.h"

void* extract_scramble_req(protocol_frame* frame) {
  if (frame->type != 1) _terminate(-1);
  if (frame->length != 2) _terminate(-1);
  return frame->value;
}

void* extract_check_req(protocol_frame* frame) {
  if (frame->type != 16) _terminate(-1);
  if (frame->length != 2) _terminate(-1);
  return frame->value;
}

void* extract_add_req(protocol_frame* frame) {
  if (frame->type != 32) _terminate(-1);
  if (frame->length != 2) _terminate(-1);
  return frame->value;
}

void* extract_subtract_req(protocol_frame* frame) {
  if (frame->type != 48) _terminate(-1);
  if (frame->length != 2) _terminate(-1);
  return frame->value;
}
