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
#include "cgc_libc.h"

#include "cgc_isopropyl.h"
#include "cgc_messages.h"
#include "cgc_protocol.h"
#include "cgc_churn.h"
#include "cgc_handler.h"

const int cgc_gauntlet_count = 32;

void cgc_seed();
void cgc_gauntlet();
void cgc_operate();

int main(int cgc_argc, char *cgc_argv[]) {
  cgc_send_empty_frame(HELLO_ID);
  cgc_expect_empty_frame(HELLO_ID);

  cgc_seed();
  cgc_gauntlet();

  while(1) {
    cgc_operate();
  }

  return 0;
}

void cgc_seed() {
  protocol_frame* seed_data = cgc_expect_frame(SEED_REQ_ID);
  cgc_handle_seed(seed_data);
  cgc_free_frame(seed_data);
}

void cgc_gauntlet() {
  for (int i = 0; i < cgc_gauntlet_count; i++) {
    protocol_frame* guess_data = cgc_expect_frame(GUESS_REQ_ID);
    cgc_handle_guess(guess_data);
    cgc_free_frame(guess_data);
  }
}

void cgc_operate() {
  cgc_transmit(STDERR, ".", 1, NULL);
  protocol_frame* frame = cgc_receive_frame();

  switch(frame->type) {
  case SEED_REQ_ID:
    cgc_handle_seed(frame);
    break;
  case RAND_REQ_ID:
    cgc_handle_rand(frame);
    break;
  case GUESS_REQ_ID:
    cgc_handle_guess(frame);
    break;
  case ECHO_REQ_ID:
    cgc_handle_echo(frame);
    break;
  default:
    cgc__terminate(-1);
  }

  cgc_free_frame(frame);
}
