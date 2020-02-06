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
#include "libcgc.h"
#include "cgc_stdint.h"
#include "cgc_stdio.h"
#include "cgc_stdlib.h"
#include "cgc_malloc.h"
#include "cgc_sls.h"
#include "cgc_msls.h"
#include "cgc_msls_handshake.h"

uint32_t *pRandom = (uint32_t *)RANDOM_BASE;

uint32_t cgc_get_cgc_random()
{
  uint32_t random = *pRandom ^ *(pRandom + 1);
  pRandom += 2;
  if (pRandom + 2 >= (uint32_t *)RANDOM_END)
  {
    pRandom = (uint32_t *)RANDOM_BASE;
  }
  return random;
}

SLS_FUNCTION_PTRS *cgc_msls_get_sls_functions()
{
  SLS_FUNCTION_PTRS *functions = cgc_calloc(sizeof(SLS_FUNCTION_PTRS));

  functions->receive_msg = &cgc_msls_receive_msg;
  functions->send_msg = &cgc_msls_send_msg;
  functions->cleanup = &cgc_msls_cleanup;
  functions->version_check = &cgc_msls_version_check;
  functions->send_error_msg = &cgc_msls_send_error_msg;
  functions->generate_checksum = &cgc_msls_generate_checksum;
  functions->handle_heartbeat = &cgc_msls_handle_heartbeat;
  functions->destroy_message = &cgc_msls_destroy_msg;
  functions->handle_handshake = &cgc_msls_handle_handshake;
  functions->get_connection = &cgc_msls_get_connection;
  functions->set_cookie = &cgc_msls_set_cookie;
  functions->lookup_context = &cgc_msls_lookup_context;
  functions->handle_application  = &cgc_msls_handle_application;
  functions->handle_changespec = &cgc_msls_handle_changespec;
  functions->handle_error = &cgc_msls_handle_error;
  return functions;
}


SLS_MESSAGE *cgc_msls_receive_msg(SERVER_STATE *state)
{
  // Receive msg
  cgc_debug_print("Receive MSG\n");
  SLS_MESSAGE *msg = cgc_calloc(sizeof(SLS_MESSAGE));
  cgc_receive_fixed((uint8_t *)&msg->length, sizeof(msg->length));
  cgc_debug_print("msg length: $d\n", msg->length);
  if ((msg->length < SLS_HEADER_LENGTH) || (msg->length > MSLS_MAX_MSG_LENGTH))
  {
    state->functions->send_error_msg(MSLS_ERROR_LENGTH, MSLS_SEVERITY_CRITICAL);
    goto cleanup;
  }
  
  cgc_receive_fixed((uint8_t *)&msg->version, sizeof(msg->version)); 
  cgc_receive_fixed((uint8_t *)&msg->type, sizeof(msg->type));
  cgc_receive_fixed((uint8_t *)&msg->checksum, sizeof(msg->checksum)); 
  cgc_receive_fixed((uint8_t *)&msg->connection_id, sizeof(msg->connection_id));
  cgc_receive_fixed((uint8_t *)&msg->msg_length, sizeof(msg->msg_length)); 
  if (msg->msg_length != msg->length - SLS_HEADER_LENGTH)
  {
    cgc_debug_print("Length: $d expected: $d received: $d\n", msg->length, msg->length - SLS_HEADER_LENGTH, msg->msg_length);
    state->functions->send_error_msg(MSLS_ERROR_LENGTH, MSLS_SEVERITY_CRITICAL);
    goto cleanup;
  }
  if (msg->msg_length > 0)
  {
    msg->message = cgc_calloc(msg->msg_length);
    cgc_receive_fixed(msg->message, msg->msg_length);
  }
  if (!state->functions->version_check(msg->version))
  {
    state->functions->send_error_msg(MSLS_ERROR_VERSION, MSLS_SEVERITY_CRITICAL);
    goto cleanup;   
  }
  if (state->functions->generate_checksum(msg) != msg->checksum)
  {
    state->functions->send_error_msg(MSLS_ERROR_CHECKSUM, MSLS_SEVERITY_CRITICAL);
    goto cleanup;
  }
  return msg;

cleanup:
  cgc_msls_destroy_msg(msg);
  return NULL;
}


int cgc_msls_send_msg(SLS_MESSAGE *msg)
{
  // Send Message
  if (msg == NULL)
  {
    return -1;
  }
  msg->checksum = cgc_msls_generate_checksum_outgoing(msg);
  cgc_debug_print("Send MSG\n");
  cgc_transmit_fixed((uint8_t *)&msg->length, sizeof(msg->length));
  cgc_transmit_fixed((uint8_t *)&msg->version, sizeof(msg->version));
  cgc_transmit_fixed((uint8_t *)&msg->type, sizeof(msg->type));
  cgc_transmit_fixed((uint8_t *)&msg->checksum, sizeof(msg->checksum));
  cgc_transmit_fixed((uint8_t *)&msg->connection_id, sizeof(msg->connection_id));
  cgc_transmit_fixed((uint8_t *)&msg->msg_length, sizeof(msg->msg_length));
  if (msg->msg_length > 0)
  {
   
    switch(msg->type)
    {
      case SLS_TYPE_CHANGESPEC:
        break;
      case SLS_TYPE_ERROR:
        cgc_transmit_fixed((uint8_t *)msg->message, msg->msg_length);
        break;
      case SLS_TYPE_HANDSHAKE:
      {
        SLS_HANDSHAKE_MESSAGE *hs_msg = (SLS_HANDSHAKE_MESSAGE *)msg->message;
        if (hs_msg == NULL)
          break;
        cgc_transmit_fixed((uint8_t *)hs_msg, SLS_HANDSHAKE_HEADER_LEN);
        if ((hs_msg->msg_length > 0)&&(hs_msg->message != NULL))
        {
          cgc_transmit_fixed((uint8_t *)hs_msg->message, hs_msg->msg_length);
        }
        break;
      }
      case SLS_TYPE_APPLICATION:
      {
        SLS_APPLICATION_MESSAGE *ap_msg = (SLS_APPLICATION_MESSAGE *)msg->message;
        cgc_transmit_fixed((uint8_t *)&ap_msg->type, sizeof(ap_msg->type));
        cgc_transmit_fixed((uint8_t *)&ap_msg->length, sizeof(ap_msg->length));
        if ((ap_msg->length > 0)&&(ap_msg->contents))
        {
          cgc_transmit_fixed((uint8_t *)ap_msg->contents, ap_msg->length);
        }
        break;
      }
      case SLS_TYPE_HEARTBEAT:
      {
        SLS_HEARTBEAT_MESSAGE *hb_msg = (SLS_HEARTBEAT_MESSAGE *)msg->message;
        if (hb_msg == NULL)
          break;
        cgc_transmit_fixed((uint8_t *)&hb_msg->type, sizeof(hb_msg->type));
        cgc_transmit_fixed((uint8_t *)&hb_msg->payload_length, sizeof(hb_msg->payload_length));
        if ((hb_msg->payload_length > 0)&&(hb_msg->payload != NULL))
        {
          cgc_transmit_fixed(hb_msg->payload, hb_msg->payload_length);
        }
        break;
      }
      case SLS_TYPE_SHUTDOWN:
        break;
      default:
        break;
    }
  }
  return 0;
}

void cgc_msls_cleanup(SERVER_STATE *state)
{
  cgc_debug_print("Exiting\n");
  SLS_MESSAGE *msg= cgc_calloc(sizeof(SLS_MESSAGE));
  msg->type = SLS_TYPE_SHUTDOWN;
  msg->version = SLS_VERSION;
  msg->length = SLS_HEADER_LENGTH;
  cgc_msls_send_msg(msg);
  cgc_free(msg);
  for (int i=0; i< MAX_CONNECTIONS; i++)
  {
    cgc_destroy_context(state->connections[i]);
  }
  cgc_free(state->cookie_base);
  cgc_free(state->functions);
  return;
}

int cgc_msls_version_check(uint16_t version)
{
  return (version == SLS_VERSION);
}

void cgc_msls_destroy_msg(SLS_MESSAGE *msg)
{
  if (msg)
  {
    switch(msg->type)
    {
      case SLS_TYPE_CHANGESPEC:
        break;
      case SLS_TYPE_ERROR:
      {
        cgc_free(msg->message);
        break;
      }
      case SLS_TYPE_HANDSHAKE:
      {
        SLS_HANDSHAKE_MESSAGE *hs_msg = (SLS_HANDSHAKE_MESSAGE *)msg->message;
        if (hs_msg)
        {
          cgc_free(hs_msg->message);
          cgc_free(hs_msg);
        }
        break;
      }
      case SLS_TYPE_APPLICATION:
      {
        SLS_APPLICATION_MESSAGE *ap_msg = (SLS_APPLICATION_MESSAGE *)msg->message;
        if ((ap_msg->length > 0) && (ap_msg->contents))
        {
          cgc_free(ap_msg->contents);
        }
        break;
      }
      case SLS_TYPE_HEARTBEAT:
      {
        SLS_HEARTBEAT_MESSAGE *hb_msg = (SLS_HEARTBEAT_MESSAGE *)msg->message;
        if (hb_msg)
        {
          cgc_free(hb_msg->payload);
          cgc_free(hb_msg);
        }
      }
      case SLS_TYPE_SHUTDOWN:
        break;
      default:
        break;
    }
    cgc_free(msg);
  }
}

void cgc_msls_encrypt(uint8_t *buffer, uint32_t length, CLIENT_CONTEXT *connection)
{
  int keyIndex = 0;
  for( int i = 0; i < length; i++)
  {
    buffer[i] = buffer[i] ^ (connection->client_key[keyIndex]&0xff) ^ (connection->server_secret[keyIndex] &0xff);
    if (++keyIndex >= 128)
    {
      keyIndex = 0;
    }
  }
}

void cgc_msls_decrypt(uint8_t *buffer, uint32_t length, CLIENT_CONTEXT *connection)
{
  int keyIndex = 0;
  for( int i = 0; i < length; i++)
  {
    buffer[i] = buffer[i] ^ (connection->server_key[keyIndex]&0xff) ^ (connection->client_secret[keyIndex] &0xff);
    if (++keyIndex >= 128)
    {
      keyIndex = 0;
    }
  }
}

void cgc_msls_send_error_msg(uint16_t error_code, uint8_t severity)
{
  cgc_debug_print("Error: $x\n", error_code);
  SLS_MESSAGE *msg = cgc_calloc(sizeof(SLS_MESSAGE));
  msg->type = SLS_TYPE_ERROR;
  SLS_ERROR_MESSAGE *error_msg = cgc_calloc(sizeof(SLS_ERROR_MESSAGE));
  error_msg->error_code = error_code;
  error_msg->severity = severity;
  msg->message = (uint8_t *)error_msg;
  msg->msg_length = sizeof(SLS_ERROR_MESSAGE);
  msg->length = msg->msg_length + SLS_HEADER_LENGTH;
  cgc_msls_send_msg(msg);
  cgc_msls_destroy_msg(msg);
}

uint32_t cgc_msls_generate_checksum(SLS_MESSAGE *msg)
{
  uint32_t checksum = 0;
  for (int i=0; i < msg->msg_length; i++)
  {
    checksum = ((checksum << 8) | (checksum >> 24)) ^ msg->message[i];
  }
  return checksum;
}

uint32_t cgc_msls_generate_checksum_outgoing(SLS_MESSAGE *msg)
{
  uint32_t checksum = 0;
  switch(msg->type)
  {
    case SLS_TYPE_CHANGESPEC:
    case SLS_TYPE_ERROR: 
    case SLS_TYPE_SHUTDOWN:
    {
      for (int i=0; i < msg->msg_length; i++)
      {
        checksum = ((checksum << 8) | (checksum >> 24)) ^ msg->message[i];
      }
      break;
    }
    case SLS_TYPE_APPLICATION:
    {
      SLS_APPLICATION_MESSAGE *ap_msg = (SLS_APPLICATION_MESSAGE *)msg->message;
      if (ap_msg)
      {
        for (int i=0; i < SLS_APPLICATION_HEADER_LEN; i++)
        {
          checksum = ((checksum << 8) | (checksum >> 24)) ^ msg->message[i];
        }
        for (int i=0; i < ap_msg->length; i++)
        {
          checksum = ((checksum << 8) | (checksum >> 24)) ^ ap_msg->contents[i];
        }
      }  
      break;
    }
    case SLS_TYPE_HEARTBEAT:
    {
      SLS_HEARTBEAT_MESSAGE *hb_msg = (SLS_HEARTBEAT_MESSAGE *)msg->message;
      if (hb_msg)
      {
        for (int i=0; i < SLS_HEARTBEAT_HEADER_LEN; i++)
        {
          checksum = ((checksum << 8) | (checksum >> 24)) ^ msg->message[i];
        }
        for (int i=0; i < hb_msg->payload_length; i++)
        {
          checksum = ((checksum << 8) | (checksum >> 24)) ^ hb_msg->payload[i];
        }
      }  
      break;
    }
    case SLS_TYPE_HANDSHAKE:
    {
      SLS_HANDSHAKE_MESSAGE *hs_msg = (SLS_HANDSHAKE_MESSAGE *)msg->message;
      if (hs_msg)
      {
        for (int i=0; i < SLS_HANDSHAKE_HEADER_LEN; i++)
        {
          checksum = ((checksum << 8) | (checksum >> 24)) ^ msg->message[i];
        }
        for (int i=0; i < hs_msg->msg_length; i++)
        {
          checksum = ((checksum << 8) | (checksum >> 24)) ^ hs_msg->message[i];
        }
      } 
      break;
    }
    default:
      break;
  }
  return checksum;
}

