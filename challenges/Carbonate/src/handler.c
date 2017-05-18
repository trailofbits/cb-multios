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

#include "cgc_carbonate.h"
#include "cgc_scramble.h"
#include "cgc_handler.h"
#include "cgc_messages.h"
#include "cgc_set.h"

HANDLER(scramble) {
  uint16 value = *(uint16*)(cgc_extract_scramble_req(frame));
  cgc_scramble_add(value);
  cgc_send_empty_frame(SCRAMBLE_RESP_ID);
}

HANDLER(check) {
  uint16 value = *(uint16*)(cgc_extract_check_req(frame));
  uint8 result = cgc_check_set(set, value);

  uint32 response = result ? CHECK_FOUND_RESP_ID : CHECK_NOT_FOUND_RESP_ID;

  cgc_send_empty_frame(response);
}

HANDLER(add) {
  uint16 value = *(uint16*)(cgc_extract_add_req(frame));

  cgc_add_set(set, value);

  cgc_send_empty_frame(ADD_RESP_ID);
}

HANDLER(subtract) {
  uint16 value = *(uint16*)(cgc_extract_subtract_req(frame));

  cgc_subtract_set(set, value);

  cgc_send_empty_frame(SUBTRACT_RESP_ID);
}

HANDLER(check_safe) {
  uint16 value = *(uint16*)(cgc_extract_check_req(frame));
  uint8 result = cgc_check_set(set, value & SET_MASK);

  uint32 response = result ? CHECK_FOUND_RESP_ID : CHECK_NOT_FOUND_RESP_ID;

  cgc_send_empty_frame(response);
}

HANDLER(add_safe) {
  uint16 value = *(uint16*)(cgc_extract_add_req(frame));

  cgc_add_set(set, value & SET_MASK);

  cgc_send_empty_frame(ADD_RESP_ID);
}

HANDLER(subtract_safe) {
  uint16 value = *(uint16*)(cgc_extract_subtract_req(frame));

  cgc_subtract_set(set, value & SET_MASK);

  cgc_send_empty_frame(SUBTRACT_RESP_ID);
}
