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

void handle_double(protocol_frame* frame) {
  uint16 input_buf_len = frame->length;
  uint8 output_buf_len = monte_happy() * 2;

  if (output_buf_len < input_buf_len) {
    _terminate(-1);
  }

  if (output_buf_len < input_buf_len * 2) {
    _terminate(-1);
  }
  
  char* input_buf = (char*)(frame->value);
  char output_buf[output_buf_len];
  for (uint8 i = 0; i < input_buf_len; i++) {
    output_buf[i] = input_buf[i];
    output_buf[i + input_buf_len] = input_buf[i];
  }

  protocol_frame f;
  f.id = DOUBLE_RESP_ID;
  f.length = input_buf_len * 2;
  f.value = (void*)&output_buf;
  protocol_send(&f);
}
