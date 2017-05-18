/*

Copyright (c) 2016 Cromulence LLC

Authors: Bryce Kerley <bk@cromulence.com>

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
#include "cgc_string.h"

#include "cgc_protocol.h"

void cgc_tx(char* bytes, cgc_size_t count);
void cgc_rx(char* byte_buf, cgc_size_t count);

void cgc_protocol_send_str(char* str) {
  uint16 len = cgc_strlen(str);
  
  cgc_tx((char*)&(len), sizeof(len));
  cgc_tx(str, len);
}

void cgc_protocol_with_recv_string(void (^block)(uint16 len, char* str)) {
  char  len_buf[sizeof(uint16)];
  char* len_buf_ptr = (char*)&len_buf;

  cgc_rx(len_buf_ptr, sizeof(uint16));

  uint16 len = *((uint16*) len_buf_ptr);
  
  char  str_buf[len];
  char* str_buf_ptr = (char*)&str_buf;

  cgc_rx(str_buf_ptr, len);

  block(len, str_buf_ptr);
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
