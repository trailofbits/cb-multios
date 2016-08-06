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

#include <libcgc.h>
#include "protocol.h"

void receive_eventually(int fd, void* destination, size_t expected);
void send_eventually(int fd, void* payload, size_t expected);

protocol_frame* allocate_frame(protocol_frame template) {
  protocol_frame* candidate;
  if (allocate(sizeof(protocol_frame), 0, (void**)(&candidate))) {
    _terminate(-1);
  }

  candidate->type = template.type;
  candidate->length = template.length;

  if (candidate->length == 0) return candidate;

  if (allocate(template.length, 0, (void**)(&(candidate->value)))) {
    _terminate(-1);
  }

  return candidate;
}

protocol_frame* expect_frame(uint8 type) {
  protocol_frame* candidate = receive_frame();
  if (candidate->type != type) {
    _terminate(-1);
  }

  return candidate;
}

protocol_frame* receive_frame() {
  protocol_frame candidate;
  candidate.type = candidate.length = 0;

  size_t need_received = sizeof(candidate.type) + sizeof(candidate.length);
  size_t actual_received = 0;

  receive_eventually(STDIN,
                     &candidate,
                     sizeof(candidate.type) + sizeof(candidate.length));

  protocol_frame* payload = allocate_frame(candidate);

  if (payload->length == 0) return payload;

  receive_eventually(STDIN,
                     payload->value,
                     payload->length);


  return payload;
}

void send_frame(protocol_frame* payload) {
  size_t sent_bytes;
  send_eventually(STDOUT,
                      (void*)(payload),
                      sizeof(payload->type) + sizeof(payload->length));


  send_eventually(STDOUT,
                      (void*)(payload->value),
                      payload->length);

}

void send_empty_frame(uint8 type) {
  protocol_frame payload;
  payload.type = type;
  payload.length = 0;
  payload.value = NULL;
  send_frame(&payload);
};

void expect_empty_frame(uint8 type) {
  protocol_frame* payload = expect_frame(type);
  free_frame(payload);
}

void free_frame(protocol_frame* fr) {
  if (fr->value != NULL) {
    if (deallocate(fr->value, fr->length)) {
      _terminate(-1);
    }
  }

  if (deallocate(fr, sizeof(fr))) {
    _terminate(-1);
  }
}

void send_eventually(int fd, void* payload, size_t expected) {
  size_t actual = 0;
  void* buf = payload;

  while (actual < expected){
    int errcode = 0;
    size_t count = 0;
    errcode = transmit(fd, buf, expected - actual, &count);
    
    if (errcode) _terminate(-1);

    actual += count;
    buf += count;
  }
}

void receive_eventually(int fd, void* destination, size_t expected) {
  size_t actual = 0;
  void* buf = destination;

  while (actual < expected) {
    int errcode = 0;
    size_t count = 0;
    errcode = receive(fd, buf, expected - actual, &count);

    if (errcode) _terminate(-1);
    if (count == 0) _terminate(-1); // eof

    actual += count;
    buf += count;
  }
}
