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
#ifndef SLS_H 
#define SLS_H




typedef struct SLSMessage_s {
  uint16_t length;
  uint16_t version;
  uint8_t type;
  uint32_t checksum;
  uint32_t connection_id;
  uint16_t msg_length;
  uint8_t *message;
} SLS_MESSAGE;

#define SLS_HEADER_LENGTH (2+2+1+4+4+2)

typedef struct ClientContext_s {
  uint32_t connection_id;
  uint8_t in_handshake;
  uint32_t last_sequence_number;
  uint8_t is_connected;
  uint8_t client_done;
  uint8_t have_key;
  uint16_t cipher_suite;
  uint32_t *client_key;
  uint32_t *server_key;
  uint32_t *client_secret;
  uint32_t *server_secret;
  uint32_t *cookie;
  uint32_t *magic;
} CLIENT_CONTEXT;

#define MAX_CONNECTIONS 32
// Server State
typedef struct ServerState_s {
  uint8_t is_initialized;
  uint8_t should_exit;
  struct SLSFunctions_s *functions;
  CLIENT_CONTEXT *connections[MAX_CONNECTIONS];
  uint32_t *cookie_base;
} SERVER_STATE;



typedef struct SLSFunctions_s {
  SLS_MESSAGE *(*receive_msg)(SERVER_STATE *);
  int (*send_msg)(SLS_MESSAGE *);
  void (*cleanup)(SERVER_STATE *);
  int (*version_check)(uint16_t);
  void (*send_error_msg)(uint16_t, uint8_t);
  uint32_t (*generate_checksum)(SLS_MESSAGE *);
  void (*handle_heartbeat)(SLS_MESSAGE *);
  void (*destroy_message)(SLS_MESSAGE *);
  void (*handle_handshake)(SERVER_STATE *, SLS_MESSAGE *);
  CLIENT_CONTEXT *(*get_connection)(SERVER_STATE *,uint32_t);
  void (*set_cookie)(SERVER_STATE *);
  CLIENT_CONTEXT *(*lookup_context)(SERVER_STATE *, uint32_t);
  void (*handle_application)(SERVER_STATE *, CLIENT_CONTEXT *, SLS_MESSAGE *);
  void (*handle_changespec)(SERVER_STATE *, CLIENT_CONTEXT *, SLS_MESSAGE *);
  void (*handle_error)(SERVER_STATE *, SLS_MESSAGE *);

} SLS_FUNCTION_PTRS;

#pragma pack(push, 1)
typedef struct SLSError_s {
  uint16_t error_code;
  uint8_t  severity;
} SLS_ERROR_MESSAGE;

typedef struct SLSHandshake_s {
  uint16_t msg_type;
  uint32_t sequence_number;
  uint32_t client_id;
  uint16_t msg_length;
  uint8_t *message;
} SLS_HANDSHAKE_MESSAGE;
#define SLS_HANDSHAKE_HEADER_LEN (2+4+4+2)

typedef struct SLSHeartbeat_s {
  uint8_t type;
  uint16_t payload_length;
  uint8_t *payload;
} SLS_HEARTBEAT_MESSAGE;
#define SLS_HEARTBEAT_HEADER_LEN (1 + 2)

typedef struct SLSChangespec_s {
  uint16_t new_cipher_suite;
} SLS_CHANGESPEC_MESSAGE;

typedef struct SLSApplication_s {
  uint8_t type;
  uint16_t length;
  uint8_t *contents;
} SLS_APPLICATION_MESSAGE;
#define SLS_APPLICATION_HEADER_LEN (1 + 2)

#pragma pack(pop)

#define SLS_VERSION 0xff01

#define SLS_TYPE_CHANGESPEC 0x01
#define SLS_TYPE_ERROR      0x02
#define SLS_TYPE_HANDSHAKE  0x03
#define SLS_TYPE_APPLICATION 0x04
#define SLS_TYPE_HEARTBEAT  0x05
#define SLS_TYPE_SHUTDOWN   0x06

#endif