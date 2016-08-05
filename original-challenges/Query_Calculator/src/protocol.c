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

#include <libcgc.h>
#include <string.h>

#include "protocol.h"

void tx(char* bytes, size_t count);
void rx(char* byte_buf, size_t count);

void protocol_send_str(char* str) {
  uint16 len = strlen(str);
  
  tx((char*)&(len), sizeof(len));
  tx(str, len);
}

void protocol_with_recv_string(void (^block)(uint16 len, char* str)) {
  char  len_buf[sizeof(uint16)];
  char* len_buf_ptr = (char*)&len_buf;

  rx(len_buf_ptr, sizeof(uint16));

  uint16 len = *((uint16*) len_buf_ptr);
  
  char  str_buf[len];
  char* str_buf_ptr = (char*)&str_buf;

  rx(str_buf_ptr, len);

  block(len, str_buf_ptr);
}

void tx(char* bytes, size_t count) {
  size_t total_sent = 0;

  while(total_sent < count) {
    size_t sent_this_time = 0;

    int status = transmit(STDOUT,
                          bytes + total_sent,
                          count - total_sent,
                          &sent_this_time);

    if (status != 0) _terminate(-1);
    if (sent_this_time == 0) _terminate(-1);

    total_sent += sent_this_time;
  }
}

void rx(char* byte_buf, size_t count) {
  size_t total_rcvd = 0;

  while(total_rcvd < count) {
    size_t rcvd_this_time = 0;

    int status = receive(STDIN,
                         byte_buf + total_rcvd,
                         count - total_rcvd,
                         &rcvd_this_time);

    if (status != 0) _terminate(-1);
    if (rcvd_this_time == 0) _terminate(-1);

    total_rcvd += rcvd_this_time;
  }
}
