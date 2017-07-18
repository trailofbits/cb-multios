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

#include "libcgc.h"
#include "cgc_protocol.h"

void cgc_receive_eventually(int fd, void* destination, cgc_size_t expected);
void cgc_send_eventually(int fd, void* payload, cgc_size_t expected);

protocol_frame* cgc_allocate_frame(protocol_frame template) {
  protocol_frame* candidate;
  if (cgc_allocate(sizeof(protocol_frame), 0, (void**)(&candidate))) {
    cgc__terminate(-1);
  }

  candidate->type = template.type;
  candidate->length = template.length;

  if (candidate->length == 0) return candidate;

  if (cgc_allocate(template.length, 0, (void**)(&(candidate->value)))) {
    cgc__terminate(-1);
  }

  return candidate;
}

protocol_frame* cgc_expect_frame(uint8 type) {
  protocol_frame* candidate = cgc_receive_frame();
  if (candidate->type != type) {
    cgc__terminate(-1);
  }

  return candidate;
}

protocol_frame* cgc_receive_frame() {
  protocol_frame candidate;
  candidate.type = candidate.length = 0;

  cgc_size_t need_received = sizeof(candidate.type) + sizeof(candidate.length);
  cgc_size_t actual_received = 0;

  cgc_receive_eventually(STDIN,
                     &candidate,
                     sizeof(candidate.type) + sizeof(candidate.length));

  protocol_frame* payload = cgc_allocate_frame(candidate);

  if (payload->length == 0) return payload;

  cgc_receive_eventually(STDIN,
                     payload->value,
                     payload->length);


  return payload;
}

void cgc_send_frame(protocol_frame* payload) {
  cgc_size_t sent_bytes;
  cgc_send_eventually(STDOUT,
                      (void*)(payload),
                      sizeof(payload->type) + sizeof(payload->length));


  cgc_send_eventually(STDOUT,
                      (void*)(payload->value),
                      payload->length);

}

void cgc_send_empty_frame(uint8 type) {
  protocol_frame payload;
  payload.type = type;
  payload.length = 0;
  payload.value = NULL;
  cgc_send_frame(&payload);
};

void cgc_expect_empty_frame(uint8 type) {
  protocol_frame* payload = cgc_expect_frame(type);
  cgc_free_frame(payload);
}

void cgc_free_frame(protocol_frame* fr) {
  if (fr->value != NULL) {
    if (cgc_deallocate(fr->value, fr->length)) {
      cgc__terminate(-1);
    }
  }

  if (cgc_deallocate(fr, sizeof(fr))) {
    cgc__terminate(-1);
  }
}

void cgc_send_eventually(int fd, void* payload, cgc_size_t expected) {
  cgc_size_t actual = 0;
  void* buf = payload;

  while (actual < expected){
    int errcode = 0;
    cgc_size_t count = 0;
    errcode = cgc_transmit(fd, buf, expected - actual, &count);
    
    if (errcode) cgc__terminate(-1);

    actual += count;
    buf += count;
  }
}

void cgc_receive_eventually(int fd, void* destination, cgc_size_t expected) {
  cgc_size_t actual = 0;
  void* buf = destination;

  while (actual < expected) {
    int errcode = 0;
    cgc_size_t count = 0;
    errcode = cgc_receive(fd, buf, expected - actual, &count);

    if (errcode) cgc__terminate(-1);
    if (count == 0) cgc__terminate(-1); // eof

    actual += count;
    buf += count;
  }
}
