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

#include "isopropyl.h"
#include "churn.h"
#include "handler.h"
#include "messages.h"

#define ECHO_MAX_LEN 80

HANDLER(seed){
  churn_item* replacement = (churn_item*)(extract_seed_req(frame));
  churn_initialize(replacement);
  send_empty_frame(SEED_RESP_ID);
}

HANDLER(rand){
  size_t byte_count = *(size_t*)(extract_rand_req(frame));
  uint8* buf;

  if (allocate(byte_count, 0, (void**)(&buf))) {
    _terminate(-1);
  }

  for (size_t i = 0; i < byte_count; i++) {
    buf[i] = churn_rand_uint8();
  }

  protocol_frame template;
  template.type = RAND_RESP_ID;
  template.length = byte_count;

  protocol_frame* payload = allocate_frame(template);
  payload->value = (void*) buf;

  send_frame(payload);

  free_frame(payload);
  deallocate(buf, byte_count);
}

HANDLER(guess){
  uint64 guess = *(uint64*)(extract_guess_req(frame));
  uint64 actual = churn_rand_uint64();

  if (guess != actual) _terminate(-1);

  send_empty_frame(GUESS_RESP_ID);
}

HANDLER(echo){
  char buf[ECHO_MAX_LEN + 2];
  void* meh;
  protocol_frame* payload;
  protocol_frame template;

  if (frame->length == 0) return;

  char* data = (char*)(extract_echo_req(frame));
#ifdef PATCHED
  if (frame->length > ECHO_MAX_LEN) {
    _terminate(-1);
  }
#endif

  size_t i = 0;
  while(1) {
    buf[i] = data[i];
    if (0 == data[i]) break;
#ifdef PATCHED
    if (i >= frame->length) break;
#endif
    i++;
  }

  template.type = ECHO_RESP_ID;
  template.length = frame->length;

  payload = allocate_frame(template);
  meh = payload->value;
  payload->value = (void*) &buf;

  send_frame(payload);
  payload->value = meh;

  free_frame(payload);
}
