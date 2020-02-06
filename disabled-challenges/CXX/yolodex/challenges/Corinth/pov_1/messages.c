#include "libcgc.h"
#include "cgc_protocol.h"
#include "cgc_messages.h"
//generated at 2015-12-23 13:57:55 -0500

// hello
hello_contents* cgc_extract_hello(protocol_frame* frame) {
  if (frame->id != 0) cgc__terminate(-1);
  if (frame->length != HELLO_EXPECTED_LENGTH) cgc__terminate(-1);
  return (hello_contents*) frame->value;
}

// unrecognized_id_error
unrecognized_id_error_contents* cgc_extract_unrecognized_id_error(protocol_frame* frame) {
  if (frame->id != 1) cgc__terminate(-1);
  if (frame->length != UNRECOGNIZED_ID_ERROR_EXPECTED_LENGTH) cgc__terminate(-1);
  return (unrecognized_id_error_contents*) frame->value;
}

// terminate
void* cgc_extract_terminate(protocol_frame* frame) {
  if (frame->id != 9) cgc__terminate(-1);
  if (frame->length != TERMINATE_EXPECTED_LENGTH) cgc__terminate(-1);
  return (void*) frame->value;
}

// check_req
check_req_contents* cgc_extract_check_req(protocol_frame* frame) {
  if (frame->id != 10) cgc__terminate(-1);
  if (frame->length != CHECK_REQ_EXPECTED_LENGTH) cgc__terminate(-1);
  return (check_req_contents*) frame->value;
}

// check_resp
check_resp_contents* cgc_extract_check_resp(protocol_frame* frame) {
  if (frame->id != 11) cgc__terminate(-1);
  if (frame->length != CHECK_RESP_EXPECTED_LENGTH) cgc__terminate(-1);
  return (check_resp_contents*) frame->value;
}

// double_req
void* cgc_extract_double_req(protocol_frame* frame) {
  if (frame->id != 20) cgc__terminate(-1);
  return (void*) frame->value;
}

// double_resp
void* cgc_extract_double_resp(protocol_frame* frame) {
  if (frame->id != 21) cgc__terminate(-1);
  return (void*) frame->value;
}

// query_req
void* cgc_extract_query_req(protocol_frame* frame) {
  if (frame->id != 30) cgc__terminate(-1);
  return (void*) frame->value;
}

// query_resp
query_resp_contents* cgc_extract_query_resp(protocol_frame* frame) {
  if (frame->id != 31) cgc__terminate(-1);
  if (frame->length != QUERY_RESP_EXPECTED_LENGTH) cgc__terminate(-1);
  return (query_resp_contents*) frame->value;
}
