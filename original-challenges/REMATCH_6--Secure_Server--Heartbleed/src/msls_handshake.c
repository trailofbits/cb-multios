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
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "malloc.h"
#include "sls.h"
#include "msls.h"
#include "msls_handshake.h"

void msls_handle_handshake(SERVER_STATE *state, SLS_MESSAGE *msg)
{
  if (!state || !msg)
  {
    return;
  }
  if (msg->msg_length < SLS_HANDSHAKE_HEADER_LEN)
  {
    msls_send_error_msg(MSLS_ERROR_LENGTH, MSLS_SEVERITY_CRITICAL);
    return;
  }
  const SLS_HANDSHAKE_MESSAGE *hs_msg = (SLS_HANDSHAKE_MESSAGE *)msg->message;
  if (hs_msg->client_id != msg->connection_id)
  {
    debug_print("client_id $x != connection id $x\n", hs_msg->client_id , msg->connection_id);
    msls_send_error_msg(MSLS_ERROR_CONNECTION, MSLS_SEVERITY_CRITICAL);
    return;
  }
  CLIENT_CONTEXT *connection = msls_lookup_context(state, msg->connection_id);
  switch(hs_msg->msg_type)
  {
    case MSLS_HS_CLIENT_HELLO:
    {
      debug_print("Received Client Hello\n");
      if (hs_msg->msg_length != sizeof(MSLS_CLIENT_HELLO_MSG))
      {
        msls_send_error_msg(MSLS_ERROR_LENGTH, MSLS_SEVERITY_CRITICAL);
        return;
      }
      const MSLS_CLIENT_HELLO_MSG *hs_hello_msg = (MSLS_CLIENT_HELLO_MSG *)((uint8_t *)hs_msg + SLS_HANDSHAKE_HEADER_LEN);
      // Check cookie
      for (int i=0; i < MSLS_COOKIE_SIZE; i++)
      { 
        if (hs_hello_msg->cookie[i] != (state->cookie_base[i] ^ msg->connection_id))
        {
          debug_print("Cookie failed\n");
          msls_send_hello_verify(state, msg->connection_id);
          return;
        }
      }
      debug_print("Done checking cookie\n");
      connection = msls_get_connection(state, msg->connection_id);
      if (!connection)
      {
        msls_send_error_msg(MSLS_ERROR_CONNECTION, MSLS_SEVERITY_FATAL);
        state->should_exit = 1;
        return;
      }
      connection->is_connected = 0;
      connection->in_handshake = 1;
      connection->have_key = 0;
      connection->client_done = 0;
      connection->last_sequence_number = 0;
      int index = get_random() % (MAX_CIPHER_SUITES - 1);
      connection->cipher_suite = hs_hello_msg->cipher_suites[index];
      msls_send_server_hello(connection);
      msls_send_keyx(connection);
      msls_send_hello_done(connection);
      if (connection->magic)
      {
        free(connection->magic);
        connection->magic = NULL;
      }
      break;
    }
    case MSLS_HS_CLIENTKEYX:
    {
      debug_print("Received Client Keyx\n");
      if (!connection)
      {
        msls_send_error_msg(MSLS_ERROR_CONNECTION, MSLS_SEVERITY_CRITICAL);
        return;
      }
      if (!connection->in_handshake)
      {
        msls_send_error_msg(MSLS_ERROR_OUTOFORDER, MSLS_SEVERITY_WARNING);
        return;
      }
      if (hs_msg->msg_length != sizeof(MSLS_CLIENT_KEYX_MSG))
      {
        msls_send_error_msg(MSLS_ERROR_LENGTH, MSLS_SEVERITY_CRITICAL);
        return;
      }
      // check and increment last sequence num
      if (hs_msg->sequence_number != ++connection->last_sequence_number)
      {
        msls_send_error_msg(MSLS_ERROR_SEQUENCE, MSLS_SEVERITY_WARNING);
        return;
      }
      const MSLS_CLIENT_KEYX_MSG *hs_keyx_msg = (MSLS_CLIENT_KEYX_MSG *)((uint8_t *)hs_msg + SLS_HANDSHAKE_HEADER_LEN);

      // Read the client key from the message
      connection->client_key = calloc(sizeof(uint32_t) *PUBLIC_KEY_LEN);
      memcpy((uint8_t *)connection->client_key, (uint8_t *)hs_keyx_msg->key, sizeof(uint32_t) *PUBLIC_KEY_LEN);
      connection->have_key = 1;
      
      // Read pre-master secret from message
      connection->client_secret = calloc(sizeof(uint32_t) * PUBLIC_KEY_LEN);
      for (int i = 0; i < PUBLIC_KEY_LEN; i++)
      {
        connection->client_secret[i] = connection->server_key[i] ^ hs_keyx_msg->pre_secret[i];
      }

      break;
    }
    case MSLS_HS_CLIENT_DONE:
    {
      debug_print("Received Client Done\n");
      if (!connection)
      {
        msls_send_error_msg(MSLS_ERROR_CONNECTION, MSLS_SEVERITY_CRITICAL);
        return;
      }
      if ((!connection->in_handshake)||(!connection->have_key))
      {
        msls_send_error_msg(MSLS_ERROR_OUTOFORDER, MSLS_SEVERITY_WARNING);
        return;
      }
      if (hs_msg->msg_length != 0)
      {
        debug_print("expected length: $d got length: $d\n",sizeof(MSLS_FINISHED_MSG), hs_msg->msg_length); 
        msls_send_error_msg(MSLS_ERROR_LENGTH, MSLS_SEVERITY_CRITICAL);
        return;
      }
      if (hs_msg->sequence_number != ++connection->last_sequence_number)
      {
        msls_send_error_msg(MSLS_ERROR_SEQUENCE, MSLS_SEVERITY_WARNING);
        return;
      }
      // send finish
      msls_send_finish(connection);
      connection->client_done = 1;
      break;
    }
    case MSLS_HS_FINISH:
    {
      debug_print("received client finished\n");
      if (!connection)
      {
        msls_send_error_msg(MSLS_ERROR_CONNECTION, MSLS_SEVERITY_CRITICAL);
        return;
      }
      if ((!connection->in_handshake)||(!connection->have_key)||(!connection->client_done))
      {
        msls_send_error_msg(MSLS_ERROR_OUTOFORDER, MSLS_SEVERITY_WARNING);
        return;
      }

      if (hs_msg->msg_length != sizeof(MSLS_FINISHED_MSG))
      {
        debug_print("expected length: $d got length: $d\n",sizeof(MSLS_FINISHED_MSG), hs_msg->msg_length); 
        msls_send_error_msg(MSLS_ERROR_LENGTH, MSLS_SEVERITY_CRITICAL);
        return;
      }
      if (hs_msg->sequence_number != ++connection->last_sequence_number)
      {
        msls_send_error_msg(MSLS_ERROR_SEQUENCE, MSLS_SEVERITY_WARNING);
        return;
      }
      const MSLS_FINISHED_MSG *hs_fin_msg = (MSLS_FINISHED_MSG *)((uint8_t *)hs_msg + SLS_HANDSHAKE_HEADER_LEN);

      // verify finish hash
      for (int i=0; i < PUBLIC_KEY_LEN; i++)
      {
        if (hs_fin_msg->hash[i] != (connection->server_secret[i] ^ connection->server_key[i] ^ connection->cookie[i]))
        {
          msls_send_error_msg(MSLS_ERROR_HASH, MSLS_SEVERITY_CRITICAL);
          return;
        }
      }
      connection->is_connected = 1;
      connection->in_handshake = 0;
  
      break;
    }
    default:
    {
      msls_send_error_msg(MSLS_ERROR_HANDSHAKE_TYPE, MSLS_SEVERITY_FATAL);
      state->should_exit = 1;
      return;
    }
  }
}

void msls_send_hello_verify(SERVER_STATE *state, uint32_t connection_id)
{
  SLS_MESSAGE *msg = calloc(sizeof(SLS_MESSAGE));
  SLS_HANDSHAKE_MESSAGE *hs_msg = calloc(sizeof(SLS_HANDSHAKE_MESSAGE));
  MSLS_HELLO_VERIFY_MSG *hs_hv_msg = calloc(sizeof(MSLS_HELLO_VERIFY_MSG));

  // Create MSLS_HELLO_VERIFY_MSG
  hs_hv_msg->server_version = SLS_VERSION;
  for (int i=0; i< MSLS_COOKIE_SIZE; i++)
  {
    hs_hv_msg->cookie[i] = state->cookie_base[i] ^ connection_id;
  }
 // Create SLS_HS_MSG Wrapper
  hs_msg->msg_type = MSLS_HS_HELLO_VERIFY;
  hs_msg->sequence_number = 0;
  hs_msg->client_id = connection_id;
  hs_msg->msg_length = sizeof(MSLS_HELLO_VERIFY_MSG);
  hs_msg->message = (uint8_t *)hs_hv_msg;
  // Create SLS MSG Wrapper
  msg->length = SLS_HEADER_LENGTH + SLS_HANDSHAKE_HEADER_LEN + sizeof(MSLS_HELLO_VERIFY_MSG);
  msg->version = SLS_VERSION;
  msg->type = SLS_TYPE_HANDSHAKE;
  msg->connection_id = connection_id;
  msg->msg_length = SLS_HANDSHAKE_HEADER_LEN + sizeof(MSLS_HELLO_VERIFY_MSG);
  msg->message = (uint8_t *)hs_msg;

  msls_send_msg(msg);
  msls_destroy_msg(msg);
}

void msls_send_server_hello(CLIENT_CONTEXT *context)
{
  SLS_MESSAGE *msg = calloc(sizeof(SLS_MESSAGE));
  SLS_HANDSHAKE_MESSAGE *hs_msg = calloc(sizeof(SLS_HANDSHAKE_MESSAGE));
  MSLS_SERVER_HELLO_MSG *hs_sh_msg = calloc(sizeof(MSLS_SERVER_HELLO_MSG));

  // Create MSLS_SERVER_HELLO_MSG
  hs_sh_msg->server_version = SLS_VERSION;
  hs_sh_msg->random = get_random();
  hs_sh_msg->cipher_suite = context->cipher_suite;
  // Create SLS_HS_MSG Wrapper
  hs_msg->msg_type = MSLS_HS_SERVER_HELLO;
  hs_msg->sequence_number = ++context->last_sequence_number;
  hs_msg->client_id = context->connection_id;
  hs_msg->msg_length = sizeof(MSLS_SERVER_HELLO_MSG);
  hs_msg->message = (uint8_t *)hs_sh_msg;
  // Create SLS MSG Wrapper
  msg->length = SLS_HEADER_LENGTH + SLS_HANDSHAKE_HEADER_LEN + sizeof(MSLS_SERVER_HELLO_MSG);
  msg->version = SLS_VERSION;
  msg->type = SLS_TYPE_HANDSHAKE;
  msg->connection_id = context->connection_id;
  msg->msg_length = SLS_HANDSHAKE_HEADER_LEN + sizeof(MSLS_SERVER_HELLO_MSG);
  msg->message = (uint8_t *)hs_msg;

  msls_send_msg(msg);
  msls_destroy_msg(msg);
}


void msls_send_keyx(CLIENT_CONTEXT *context)
{
  SLS_MESSAGE *msg = calloc(sizeof(SLS_MESSAGE));
  SLS_HANDSHAKE_MESSAGE *hs_msg = calloc(sizeof(SLS_HANDSHAKE_MESSAGE));
  MSLS_SERVER_KEYX_MSG *hs_kx_msg = calloc(sizeof(MSLS_SERVER_KEYX_MSG));

  // Create MSLS_SERVER_KEYX_MSG
  context->server_key = calloc(sizeof(uint32_t) * PUBLIC_KEY_LEN);
  for (int i=0; i< PUBLIC_KEY_LEN; i++)
  { 
    context->server_key[i] = ((uint32_t *)PUBLIC_KEY_BASE1)[i] ^ ((uint32_t *)PUBLIC_KEY_BASE2)[i];
    hs_kx_msg->key[i] = context->server_key[i];
  }
  // Create SLS_HS_MSG Wrapper
  hs_msg->msg_type = MSLS_HS_SERVER_KEYX;
  hs_msg->sequence_number = ++context->last_sequence_number;
  hs_msg->client_id = context->connection_id;
  hs_msg->msg_length = sizeof(MSLS_SERVER_KEYX_MSG);
  hs_msg->message = (uint8_t *)hs_kx_msg;
  // Create SLS MSG Wrapper
  msg->length = SLS_HEADER_LENGTH + SLS_HANDSHAKE_HEADER_LEN + sizeof(MSLS_SERVER_KEYX_MSG);
  msg->version = SLS_VERSION;
  msg->type = SLS_TYPE_HANDSHAKE;
  msg->connection_id = context->connection_id;
  msg->msg_length = SLS_HANDSHAKE_HEADER_LEN + sizeof(MSLS_SERVER_KEYX_MSG);
  msg->message = (uint8_t *)hs_msg;

  msls_send_msg(msg);
  msls_destroy_msg(msg);

}

void msls_send_hello_done(CLIENT_CONTEXT *context)
{
  SLS_MESSAGE *msg = calloc(sizeof(SLS_MESSAGE));
  SLS_HANDSHAKE_MESSAGE *hs_msg = calloc(sizeof(SLS_HANDSHAKE_MESSAGE));
  
  // Create SLS_HS_MSG Wrapper
  hs_msg->msg_type = MSLS_HS_SERVER_DONE;
  hs_msg->sequence_number = ++context->last_sequence_number;
  hs_msg->client_id = context->connection_id;
  hs_msg->msg_length = 0;
  hs_msg->message = NULL;
  // Create SLS MSG Wrapper
  msg->length = SLS_HEADER_LENGTH + SLS_HANDSHAKE_HEADER_LEN ;
  msg->version = SLS_VERSION;
  msg->type = SLS_TYPE_HANDSHAKE;
  msg->connection_id = context->connection_id;
  msg->msg_length = SLS_HANDSHAKE_HEADER_LEN ;
  msg->message = (uint8_t *)hs_msg;

  msls_send_msg(msg);
  msls_destroy_msg(msg);

}

void msls_send_finish(CLIENT_CONTEXT *context)
{
  SLS_MESSAGE *msg = calloc(sizeof(SLS_MESSAGE));
  SLS_HANDSHAKE_MESSAGE *hs_msg = calloc(sizeof(SLS_HANDSHAKE_MESSAGE));
  MSLS_FINISHED_MSG *hs_fin_msg = calloc(sizeof(MSLS_FINISHED_MSG));

  // Generate server secret
  context->server_secret = calloc(PUBLIC_KEY_LEN * sizeof(uint32_t));
  for (int i=0; i < PUBLIC_KEY_LEN; i++)
  {
    context->server_secret[i] = ((uint32_t *)SERVER_SECRET1)[i] ^ ((uint32_t *)SERVER_SECRET2)[i];
  }
  // Create FINISHED Message
  for (int i=0; i < PUBLIC_KEY_LEN; i++)
  {
    hs_fin_msg->hash[i] = context->server_secret[i] ^ context->client_secret[i] ^ context->client_key[i] ^ context->cookie[i];
  }

  // Create SLS_HS_MSG Wrapper
  hs_msg->msg_type = MSLS_HS_FINISH;
  hs_msg->sequence_number = ++context->last_sequence_number;
  hs_msg->client_id = context->connection_id;
  hs_msg->msg_length = sizeof(MSLS_FINISHED_MSG);
  hs_msg->message = (uint8_t *)hs_fin_msg;

  // Create SLS MSG Wrapper
  msg->length = SLS_HEADER_LENGTH + SLS_HANDSHAKE_HEADER_LEN + sizeof(MSLS_FINISHED_MSG);
  msg->version = SLS_VERSION;
  msg->type = SLS_TYPE_HANDSHAKE;
  msg->connection_id = context->connection_id;
  msg->msg_length = SLS_HANDSHAKE_HEADER_LEN + sizeof(MSLS_FINISHED_MSG);
  msg->message = (uint8_t *)hs_msg;

  msls_send_msg(msg);
  msls_destroy_msg(msg); 
}

CLIENT_CONTEXT *msls_get_connection(SERVER_STATE *state, uint32_t client_id)
{
  if (!state)
  {
    return NULL;
  }

  CLIENT_CONTEXT *connection = msls_lookup_context(state, client_id);
  if (connection != NULL)
  {
    return connection;
  }
  // Not found, create a new one
  for (int i=0; i<MAX_CONNECTIONS; i++)
  {
    if (state->connections[i] == NULL)
    {

      connection = calloc(sizeof(CLIENT_CONTEXT));
      debug_print("Created connection at $x\n", connection);
      connection->connection_id = client_id;
      state->connections[i] = connection;
      uint32_t *cookie = calloc(MSLS_COOKIE_SIZE * sizeof(uint32_t));
      uint32_t *magic = calloc(MSLS_COOKIE_SIZE * sizeof(uint32_t));
      memcpy(cookie, (uint8_t *)COOKIE_BASE1, MSLS_COOKIE_SIZE * sizeof(uint32_t));
      memcpy(magic, (uint8_t *)COOKIE_BASE2 , MSLS_COOKIE_SIZE * sizeof(uint32_t));
      for (int j = 0; j < MSLS_COOKIE_SIZE; j++)
      {
        cookie[j] = (cookie[j] ^ magic[j]) ^ client_id;
      }
      // Leave some magic page behind on the heap
      debug_print("leaving some magic at: $x\n", magic);
      connection->magic = magic;
      connection->cookie = cookie;
      return connection;
    }
  }
  // Connections full
  return NULL;
}

CLIENT_CONTEXT *msls_lookup_context(SERVER_STATE *state, uint32_t client_id)
{
  if (!state)
  {
    return NULL;
  }

  CLIENT_CONTEXT *connection = NULL;
  for (int i=0; i<MAX_CONNECTIONS; i++)
  {
    connection = state->connections[i];
    if (connection && connection->connection_id == client_id)
    {
      return connection;
    }
  }
  return NULL;
}

void msls_destroy_connection(SERVER_STATE *state, uint32_t client_id)
{
  if (!state)
  {
    return;
  }
  CLIENT_CONTEXT *connection = NULL;
  for (int i=0; i<MAX_CONNECTIONS; i++)
  {
    connection = state->connections[i];
    if (connection && connection->connection_id == client_id)
    {
      destroy_context(connection);
      state->connections[i] = NULL;
    }
  }
}

void msls_set_cookie(SERVER_STATE *state)
{
  state->cookie_base = calloc(MSLS_COOKIE_SIZE * sizeof(uint32_t));
  for (int i=0; i< MSLS_COOKIE_SIZE; i++)
  {
    state->cookie_base[i] = *(uint32_t *)(COOKIE_BASE1 + i*4) ^ *(uint32_t *)(COOKIE_BASE2 + i*4) ;
  }
}


void destroy_context(CLIENT_CONTEXT *context)
{
  if (context)
  {
    free(context->cookie);
    free(context->client_key);
    free(context->server_key);
    free(context->server_secret);
    free(context->client_secret);
  }
  return;
}