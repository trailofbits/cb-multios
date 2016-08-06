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
#include "libc.h"

#include "isopropyl.h"
#include "messages.h"
#include "protocol.h"
#include "churn.h"
#include "handler.h"

const int gauntlet_count = 32;

void seed();
void gauntlet();
void operate();

int main(void) {
  send_empty_frame(HELLO_ID);
  expect_empty_frame(HELLO_ID);

  seed();
  gauntlet();

  while(1) {
    operate();
  }

  return 0;
}

void seed() {
  protocol_frame* seed_data = expect_frame(SEED_REQ_ID);
  handle_seed(seed_data);
  free_frame(seed_data);
}

void gauntlet() {
  for (int i = 0; i < gauntlet_count; i++) {
    protocol_frame* guess_data = expect_frame(GUESS_REQ_ID);
    handle_guess(guess_data);
    free_frame(guess_data);
  }
}

void operate() {
  transmit(STDERR, ".", 1, NULL);
  protocol_frame* frame = receive_frame();

  switch(frame->type) {
  case SEED_REQ_ID:
    handle_seed(frame);
    break;
  case RAND_REQ_ID:
    handle_rand(frame);
    break;
  case GUESS_REQ_ID:
    handle_guess(frame);
    break;
  case ECHO_REQ_ID:
    handle_echo(frame);
    break;
  default:
    _terminate(-1);
  }

  free_frame(frame);
}
