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

#include <libcgc.h>
#include "handler.h"
#include "protocol.h"
#include "messages.h"
#include "monte.h"

void handle_unrecognized_id(uint8 id);
void handle_check(protocol_frame* rq);
void handle_query();
void handle_double(protocol_frame* frame);

void run_loop() {
  while (1) {
    protocol_with_recv_frame(^uint8 (protocol_frame* frame) {
        switch (frame->id) {
        case TERMINATE_ID:
          _terminate(0);
          break;
        case CHECK_REQ_ID:
          handle_check(frame);
          break;
        case QUERY_REQ_ID:
          handle_query();
          break;
        case DOUBLE_REQ_ID:
          handle_double(frame);
          break;
        default:
          handle_unrecognized_id(frame->id);
          return 0;
        };

        return 1;
      });
  }
}

void handle_unrecognized_id(uint8 id) {
  unrecognized_id_error_contents e;
  e.pos0 = id;
  protocol_frame f;
  f.id = UNRECOGNIZED_ID_ERROR_ID;
  f.length = UNRECOGNIZED_ID_ERROR_EXPECTED_LENGTH;
  f.value = (void*)&e;
  protocol_send(&f);
  _terminate(-1);
}

void handle_check(protocol_frame* frame) {
  check_req_contents *rq = extract_check_req(frame);

  float64 splatter = rq->pos0;
  float64 scaler = rq->pos1;

  monte_adjust(splatter, scaler);

  check_resp_contents e;
  e.pos0 = monte_happy();

  protocol_frame f;
  f.id = CHECK_RESP_ID;
  f.length = CHECK_RESP_EXPECTED_LENGTH;
  f.value = (void*)&e;

  protocol_send(&f);
}

void handle_query() {
  query_resp_contents e;
  e.pos0 = monte_gen();
  protocol_frame f;
  f.id = QUERY_RESP_ID;
  f.length = QUERY_RESP_EXPECTED_LENGTH;
  f.value = (void*)&e;
  protocol_send(&f);
}

void bufcpy(uint8 len, char* in, char* out) {
  for (uint8 i = 0; i < len; i++) {
    out[i] = in[i];
    out[i + len] = in[i];
  }
}

void double_body(protocol_frame* frame,
                 char* output_buf_addr,
                 uint8 output_buf_len) {
  protocol_frame f;
  uint16 input_buf_len = frame->length;

  f.id = DOUBLE_RESP_ID;
  f.length = input_buf_len * 2;
  f.value = (void*)output_buf_addr;

  if (output_buf_len < input_buf_len) {
    _terminate(-1);
  }

#ifdef PATCHED_1
  if (output_buf_len < input_buf_len * 2) {
    _terminate(-1);
  }
#endif

  char* input_buf = (char*)(frame->value);

  bufcpy(input_buf_len, input_buf, output_buf_addr);

  protocol_send(&f);

}

void handle_double(protocol_frame* frame) {
  uint8 intermediate_len = monte_happy() * 2;
  uint8 output_buf_len = intermediate_len - (intermediate_len % 8);
  char output_buf[output_buf_len];
  char* output_buf_addr = (char*) &output_buf;

  double_body(frame, output_buf_addr, output_buf_len);
}
