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

#include "carbonate.h"
#include "messages.h"
#include "protocol.h"
#include "scramble.h"
#include "handler.h"

void scramble();
void cool_set_stuff();
void safe_set_stuff();

int main(void) {
  send_empty_frame(HELLO_ID);
  expect_empty_frame(HELLO_ID);

  scramble();

#ifdef PATCHED
    while (1) {
      safe_set_stuff();
    }
#else
  if (scramble_okay()) {
    while(1) {
      cool_set_stuff();
    }
  } else {
    while (1) {
      safe_set_stuff();
    }
  }
#endif

  return 0;
}

void scramble() {
  while (!scramble_done()) {
    protocol_frame* scramble_data = expect_frame(SCRAMBLE_REQ_ID);
    handle_scramble(NULL, scramble_data);
    free_frame(scramble_data);
  }

}

void cool_set_stuff() {
  with_set(^(set_t set) {
      while(1) {
        protocol_frame* frame = receive_frame();

        switch(frame->type) {
        case CHECK_REQ_ID:
          handle_check(set, frame);
          break;
        case ADD_REQ_ID:
          handle_add(set, frame);
          break;
        case SUBTRACT_REQ_ID:
          handle_subtract(set, frame);
          break;
        case CLEAR_REQ_ID:
          free_frame(frame);
          send_empty_frame(CLEAR_RESP_ID);
          return; // leaves with_set block, clearing set
        default:
          _terminate(-1);
        }

        free_frame(frame);
      }
    });
}

void safe_set_stuff() {
  with_set(^(set_t set) {
      while(1) {
        protocol_frame* frame = receive_frame();

        switch(frame->type) {
        case CHECK_REQ_ID:
          handle_check_safe(set, frame);
          break;
        case ADD_REQ_ID:
          handle_add_safe(set, frame);
          break;
        case SUBTRACT_REQ_ID:
          handle_subtract_safe(set, frame);
          break;
        case CLEAR_REQ_ID:
          free_frame(frame);
          send_empty_frame(CLEAR_RESP_ID);
          return; // leaves with_set block, clearing set
        default:
          _terminate(-1);
        }

        free_frame(frame);
      }
    });
}
