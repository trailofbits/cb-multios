/*

Author: Debbie Nuttall <debbie@cromulence.com>

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
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "sls.h"
#include "msls.h"
#include "msls_handshake.h"

void msls_handle_heartbeat(SLS_MESSAGE *msg)
{
  debug_print("Handling Heartbeat\n");
  SLS_MESSAGE *response = calloc(sizeof(SLS_MESSAGE));
  SLS_HEARTBEAT_MESSAGE *hb_response = calloc(sizeof(SLS_HEARTBEAT_MESSAGE));
  response->type = SLS_TYPE_HEARTBEAT;
  response->version = SLS_VERSION;
  response->connection_id = msg->connection_id;
  hb_response->type = MSLS_HEARTBEAT_RESPONSE;
  const SLS_HEARTBEAT_MESSAGE *hb_request = (SLS_HEARTBEAT_MESSAGE *)msg->message;
  const uint8_t *request_payload = (uint8_t *)msg->message + SLS_HEARTBEAT_HEADER_LEN;
  hb_response->payload_length = hb_request->payload_length;
#ifdef PATCHED_1
  if (hb_response->payload_length > msg->msg_length - SLS_HEARTBEAT_HEADER_LEN)
  {
    hb_response->payload_length = msg->msg_length - SLS_HEARTBEAT_HEADER_LEN;
  }
  if (hb_response->payload_length > 64)
  {
    hb_response->payload_length = 64;
  }
#endif 
  if (hb_response->payload_length > 0)
  {
    hb_response->payload = calloc(hb_response->payload_length);
    debug_print("Reading heartbeats from $x to $x\n", request_payload, request_payload + hb_response->payload_length );
    memcpy(hb_response->payload, request_payload, hb_response->payload_length);
  }
  
  response->msg_length =  hb_response->payload_length + SLS_HEARTBEAT_HEADER_LEN;
  response->message = (uint8_t *)hb_response;
  response->length = response->msg_length + SLS_HEADER_LENGTH;
  debug_print("Sending HB response. Length: $d\n", hb_response->payload_length);
  msls_send_msg(response);
  msls_destroy_msg(response);
}

void msls_handle_changespec(SERVER_STATE *state, CLIENT_CONTEXT *connection, SLS_MESSAGE *msg)
{
  SLS_CHANGESPEC_MESSAGE *cs_msg = (SLS_CHANGESPEC_MESSAGE *)msg->message;
  if (cs_msg == NULL)
  {
    return;
  }
  if (connection == NULL)
  {
    return;
  }
  connection->cipher_suite = cs_msg->new_cipher_suite;
  msls_send_server_hello(connection);
}

void msls_handle_error(SERVER_STATE *state, SLS_MESSAGE *msg)
{
  CLIENT_CONTEXT *connection = state->functions->lookup_context(state, msg->connection_id);
  SLS_ERROR_MESSAGE *er_msg = (SLS_ERROR_MESSAGE *)msg->message;
  if (er_msg == NULL)
  {
    return;
  }
  switch (er_msg->severity)
  {
    case MSLS_SEVERITY_WARNING:
      debug_print("Received Client Warning $x\n", er_msg->error_code);
      break;
    case MSLS_SEVERITY_CRITICAL:
      if (connection)
      {
        debug_print("Received Critical Error $x. Shutting down connection.\n", er_msg->error_code);
        connection->is_connected = 0;
      }
      break;
    case MSLS_SEVERITY_FATAL:
      debug_print("Received Fatal Error $x. Shutting down server\n", er_msg->error_code);
      state->should_exit = 1;
      break;
    default:
      debug_print("Unknown Error Code $x $x\n", er_msg->error_code, er_msg->severity);
      break;
  }
}
