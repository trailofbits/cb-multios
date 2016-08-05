#pragma once
#include "protocol.h"
// generated at 2015-12-23 13:57:55 -0500

// hello
typedef struct {
  float64 pos0;
} hello_contents;
#define HELLO_ID 0
#define HELLO_EXPECTED_LENGTH 8
hello_contents* extract_hello(protocol_frame* frame);

// unrecognized_id_error
typedef struct {
  uint8 pos0;
} unrecognized_id_error_contents;
#define UNRECOGNIZED_ID_ERROR_ID 1
#define UNRECOGNIZED_ID_ERROR_EXPECTED_LENGTH 1
unrecognized_id_error_contents* extract_unrecognized_id_error(protocol_frame* frame);

// terminate
// can't struct #<Message 9/terminate contents=0 decode_contents=empty bytes=0>
#define TERMINATE_ID 9
#define TERMINATE_EXPECTED_LENGTH 0
void* extract_terminate(protocol_frame* frame);

// check_req
typedef struct {
  float64 pos0;
  float64 pos1;
} check_req_contents;
#define CHECK_REQ_ID 10
#define CHECK_REQ_EXPECTED_LENGTH 16
check_req_contents* extract_check_req(protocol_frame* frame);

// check_resp
typedef struct {
  uint8 pos0;
} check_resp_contents;
#define CHECK_RESP_ID 11
#define CHECK_RESP_EXPECTED_LENGTH 1
check_resp_contents* extract_check_resp(protocol_frame* frame);

// double_req
// can't struct #<Message 20/double_req contents=-1 decode_contents=variable bytes=variable>
#define DOUBLE_REQ_ID 20
#define DOUBLE_REQ_EXPECTED_LENGTH variable
void* extract_double_req(protocol_frame* frame);

// double_resp
// can't struct #<Message 21/double_resp contents=-1 decode_contents=variable bytes=variable>
#define DOUBLE_RESP_ID 21
#define DOUBLE_RESP_EXPECTED_LENGTH variable
void* extract_double_resp(protocol_frame* frame);

// query_req
// can't struct #<Message 30/query_req contents=-1 decode_contents=variable bytes=variable>
#define QUERY_REQ_ID 30
#define QUERY_REQ_EXPECTED_LENGTH variable
void* extract_query_req(protocol_frame* frame);

// query_resp
typedef struct {
  float64 pos0;
} query_resp_contents;
#define QUERY_RESP_ID 31
#define QUERY_RESP_EXPECTED_LENGTH 8
query_resp_contents* extract_query_resp(protocol_frame* frame);
