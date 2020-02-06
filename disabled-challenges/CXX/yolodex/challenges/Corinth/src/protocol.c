/*

Author: Bryce Kerley <bk@cromulence.co>

Copyright (c) 2016 Cromulence LLC

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

#include "cgc_protocol.h"

void cgc_tx(char* bytes, cgc_size_t count);
void cgc_rx(char* byte_buf, cgc_size_t count);

void cgc_protocol_send(protocol_frame* frame) {
  cgc_tx((char*)&(frame->id), sizeof(frame->id));
  cgc_tx((char*)&(frame->length), sizeof(frame->length));

  /* tx((char*)(void*)frame, frame_size); */

  if (frame->length == 0) return;

  cgc_tx((char*)frame->value, frame->length);
}

void cgc_protocol_with_recv_frame(uint8 (^block)(protocol_frame* frame)) {
  protocol_frame frame;
  char header_buf[sizeof(frame.id) + sizeof(frame.length)];
  char* header_buf_ptr = (char*)&header_buf;

  cgc_rx(header_buf_ptr, sizeof(frame.id) + sizeof(frame.length));
  frame.id = *(uint8*)(&header_buf[0]);
  frame.length = *(uint16*)(&header_buf[1]);

  char buf[frame.length];

  cgc_rx((char*)&buf, frame.length);

  frame.value = (void*)&buf;

  block(&frame);
}

void cgc_tx(char* bytes, cgc_size_t count) {
  cgc_size_t total_sent = 0;

  while(total_sent < count) {
    cgc_size_t sent_this_time = 0;

    int status = cgc_transmit(STDOUT,
                          bytes + total_sent,
                          count - total_sent,
                          &sent_this_time);

    if (status != 0) cgc__terminate(-1);
    if (sent_this_time == 0) cgc__terminate(-1);

    total_sent += sent_this_time;
  }
}

void cgc_rx(char* byte_buf, cgc_size_t count) {
  cgc_size_t total_rcvd = 0;

  while(total_rcvd < count) {
    cgc_size_t rcvd_this_time = 0;

    int status = cgc_receive(STDIN,
                         byte_buf + total_rcvd,
                         count - total_rcvd,
                         &rcvd_this_time);

    if (status != 0) cgc__terminate(-1);
    if (rcvd_this_time == 0) cgc__terminate(-1);

    total_rcvd += rcvd_this_time;
  }
}
