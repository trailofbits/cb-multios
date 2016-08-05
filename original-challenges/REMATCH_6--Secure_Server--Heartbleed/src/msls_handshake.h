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
#ifndef MSLS_HANDSHAKE_H
#define MSLS_HANDSHAKE_H

#define COOKIE_BASE1 MAGIC_PAGE
#define COOKIE_BASE2 (MAGIC_PAGE + 128*4)
#define SERVER_SECRET1 (MAGIC_PAGE + 512)
#define SERVER_SECRET2 (MAGIC_PAGE + 512 + 128*4)
#define PUBLIC_KEY_BASE1 (MAGIC_PAGE + 1024)
#define PUBLIC_KEY_BASE2 (MAGIC_PAGE + 1024 + 128*4)
#define RANDOM_BASE (MAGIC_PAGE + 2048)
#define RANDOM_END (MAGIC_PAGE + 4096)

#define MSLS_HS_CLIENT_HELLO 0x51
#define MSLS_HS_HELLO_VERIFY 0x52
#define MSLS_HS_SERVER_HELLO 0x53
#define MSLS_HS_CERTIFICATE  0x54
#define MSLS_HS_SERVER_KEYX  0x55
#define MSLS_HS_CLIENTKEYX   0x56
#define MSLS_HS_SERVER_DONE  0x57
#define MSLS_HS_CLIENT_DONE  0x58
#define MSLS_HS_FINISH       0x59


#pragma pack(push, 1)
typedef struct MSLSClientHello_s {
  uint16_t client_version;
  uint32_t random;
  uint32_t session_id;
  uint32_t cookie[MSLS_COOKIE_SIZE];
  uint16_t cipher_suites[MAX_CIPHER_SUITES];
} MSLS_CLIENT_HELLO_MSG;

#define PUBLIC_KEY_LEN  128

typedef struct MSLSHelloVerify_s {
  uint16_t server_version;
  uint32_t cookie[MSLS_COOKIE_SIZE];
} MSLS_HELLO_VERIFY_MSG;

typedef struct MSLSServerHello_s {
  uint16_t server_version;
  uint32_t random;
  uint16_t cipher_suite;
} MSLS_SERVER_HELLO_MSG;

#define NAME_LEN 32
typedef struct MSLSCertificate_s {
  uint16_t certificate_id;
  uint8_t name[NAME_LEN];
  uint32_t public_key[PUBLIC_KEY_LEN];
  uint32_t issuer_id;
} MSLS_CERTIFICATE_MSG;

typedef struct MSLSServerKeyX_s {
  uint32_t key[PUBLIC_KEY_LEN];
} MSLS_SERVER_KEYX_MSG;

typedef struct MSLSClientKeyX_s {
  uint32_t key[PUBLIC_KEY_LEN];
  uint32_t pre_secret[PUBLIC_KEY_LEN];
} MSLS_CLIENT_KEYX_MSG;

typedef struct MSLSFinished_s {
  uint32_t hash[PUBLIC_KEY_LEN];
} MSLS_FINISHED_MSG;

#pragma pack(pop)


void destroy_context(CLIENT_CONTEXT *context);
void msls_destroy_connection(SERVER_STATE *state, uint32_t client_id);
CLIENT_CONTEXT *msls_get_connection(SERVER_STATE *state, uint32_t client_id);
void msls_set_cookie(SERVER_STATE *state);
CLIENT_CONTEXT *msls_lookup_context(SERVER_STATE *state, uint32_t client_id);
void msls_send_server_hello(CLIENT_CONTEXT *context);
void msls_send_hello_verify(SERVER_STATE *state, uint32_t connection_id);
void msls_send_keyx(CLIENT_CONTEXT *context);
void msls_send_hello_done(CLIENT_CONTEXT *context);
void msls_send_finish(CLIENT_CONTEXT *context);
void msls_encrypt(uint8_t *buffer, uint32_t length, CLIENT_CONTEXT *connection);
void msls_decrypt(uint8_t *buffer, uint32_t length, CLIENT_CONTEXT *connection);
#endif