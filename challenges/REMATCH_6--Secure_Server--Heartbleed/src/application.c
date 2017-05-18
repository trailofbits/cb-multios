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
#include "cgc_string.h"
#include "cgc_stdlib.h"
#include "cgc_malloc.h"
#include "cgc_sls.h"
#include "cgc_msls.h"
#include "cgc_msls_handshake.h"
#include "cgc_application.h"

uint8_t APPLICATION_MSG_BOARD[APPLICATION_MAX_MESSAGES][APPLICATION_MSG_LENGTH];
int cgc_numMessages = 0;

void cgc_msls_handle_application(SERVER_STATE *state, CLIENT_CONTEXT *connection,  SLS_MESSAGE *msg)
{
  cgc_debug_print("Handling Application Message ($d)\n", msg->msg_length);
  if (msg->msg_length < SLS_APPLICATION_HEADER_LEN)
  {
    return;
  }
  SLS_APPLICATION_MESSAGE *ap_msg = (SLS_APPLICATION_MESSAGE *)msg->message;
  
  cgc_debug_print("Type: $d Len: $d\n", ap_msg->type, ap_msg->length);
  switch(ap_msg->type)
  {
    case APPLICATION_TYPE_LIST_BOARD:
    {
      cgc_debug_print("APP: List Board\n");
      SLS_MESSAGE *response = cgc_calloc(sizeof(SLS_MESSAGE));
      SLS_APPLICATION_MESSAGE *ap_response = cgc_calloc(sizeof(SLS_APPLICATION_MESSAGE));
      APPLICATION_RESPONSE_MSG *ar_msg = cgc_calloc(sizeof(APPLICATION_RESPONSE_MSG));
      response->type = SLS_TYPE_APPLICATION;
      response->version = SLS_VERSION;
      response->connection_id = msg->connection_id;
      response->message = (uint8_t *)ap_response;
      response->length = SLS_HEADER_LENGTH + SLS_APPLICATION_HEADER_LEN + sizeof(APPLICATION_RESPONSE_MSG);
      response->msg_length = SLS_APPLICATION_HEADER_LEN + sizeof(APPLICATION_RESPONSE_MSG);
      ap_response->type = APPLICATION_TYPE_RESPONSE;
      ap_response->length = sizeof(APPLICATION_RESPONSE_MSG);
      ap_response->contents = (uint8_t *)ar_msg;
      cgc_sprintf((char *)ar_msg->message, "$d of $d slots filled\n", cgc_numMessages, APPLICATION_MAX_MESSAGES);
      cgc_msls_encrypt(ap_response->contents, ap_response->length, connection);
      cgc_msls_send_msg(response);
      cgc_msls_destroy_msg(response);
      break;
    }
    case APPLICATION_TYPE_POST_MESSAGE:
    {
      if (ap_msg->length < sizeof(APPLICATION_POST_MSG))
      {
        return;
      }
      cgc_msls_decrypt(((uint8_t *)ap_msg + SLS_APPLICATION_HEADER_LEN), ap_msg->length, connection);
      APPLICATION_POST_MSG *post_msg = (APPLICATION_POST_MSG *)((uint8_t *)ap_msg + SLS_APPLICATION_HEADER_LEN);
      int ret_code = cgc_post_new_message(post_msg->message);
      cgc_debug_print("Posting to slot $d\n", cgc_numMessages-1);
      SLS_MESSAGE *response = cgc_calloc(sizeof(SLS_MESSAGE));
      SLS_APPLICATION_MESSAGE *ap_response = cgc_calloc(sizeof(SLS_APPLICATION_MESSAGE));
      APPLICATION_RESPONSE_MSG *ar_msg = cgc_calloc(sizeof(APPLICATION_RESPONSE_MSG));
      response->type = SLS_TYPE_APPLICATION;
      response->version = SLS_VERSION;
      response->connection_id = msg->connection_id;
      response->message = (uint8_t *)ap_response;
      response->length = SLS_HEADER_LENGTH + SLS_APPLICATION_HEADER_LEN + sizeof(APPLICATION_RESPONSE_MSG);
      response->msg_length = SLS_APPLICATION_HEADER_LEN + sizeof(APPLICATION_RESPONSE_MSG);
      ap_response->type = APPLICATION_TYPE_RESPONSE;
      ap_response->length = sizeof(APPLICATION_RESPONSE_MSG);
      ap_response->contents = (uint8_t *)ar_msg;
      cgc_sprintf((char *)ar_msg->message, "POST returned: $d\n", ret_code);
      cgc_msls_encrypt(ap_response->contents, ap_response->length, connection);
      cgc_msls_send_msg(response);
      cgc_msls_destroy_msg(response);
      break;
    }
    case APPLICATION_TYPE_DELETE_MESSAGE:
    {
      if (ap_msg->length < sizeof(APPLICATION_DELETE_MSG))
      {
        return;
      }
      cgc_msls_decrypt(((uint8_t *)ap_msg + SLS_APPLICATION_HEADER_LEN), ap_msg->length, connection);
      APPLICATION_DELETE_MSG *del_msg = (APPLICATION_DELETE_MSG *)((uint8_t *)ap_msg + SLS_APPLICATION_HEADER_LEN);
      int ret_code = cgc_delete_message(del_msg->msg_num);
      cgc_debug_print("Deleting message $d\n", del_msg->msg_num);
      SLS_MESSAGE *response = cgc_calloc(sizeof(SLS_MESSAGE));
      SLS_APPLICATION_MESSAGE *ap_response = cgc_calloc(sizeof(SLS_APPLICATION_MESSAGE));
      APPLICATION_RESPONSE_MSG *ar_msg = cgc_calloc(sizeof(APPLICATION_RESPONSE_MSG));
      response->type = SLS_TYPE_APPLICATION;
      response->version = SLS_VERSION;
      response->connection_id = msg->connection_id;
      response->message = (uint8_t *)ap_response;
      response->length = SLS_HEADER_LENGTH + SLS_APPLICATION_HEADER_LEN + sizeof(APPLICATION_RESPONSE_MSG);
      response->msg_length = SLS_APPLICATION_HEADER_LEN + sizeof(APPLICATION_RESPONSE_MSG);
      ap_response->type = APPLICATION_TYPE_RESPONSE;
      ap_response->length = sizeof(APPLICATION_RESPONSE_MSG);
      ap_response->contents = (uint8_t *)ar_msg;
      cgc_sprintf((char *)ar_msg->message, "DELETE returned: $d\n", ret_code);
      cgc_msls_encrypt(ap_response->contents, ap_response->length, connection);
      cgc_msls_send_msg(response);
      cgc_msls_destroy_msg(response);
      break;
    }
    case APPLICATION_TYPE_CLEAR_BOARD:
    {
      cgc_clear_message_board();
      SLS_MESSAGE *response = cgc_calloc(sizeof(SLS_MESSAGE));
      SLS_APPLICATION_MESSAGE *ap_response = cgc_calloc(sizeof(SLS_APPLICATION_MESSAGE));
      APPLICATION_RESPONSE_MSG *ar_msg = cgc_calloc(sizeof(APPLICATION_RESPONSE_MSG));
      response->type = SLS_TYPE_APPLICATION;
      response->version = SLS_VERSION;
      response->connection_id = msg->connection_id;
      response->message = (uint8_t *)ap_response;
      response->length = SLS_HEADER_LENGTH + SLS_APPLICATION_HEADER_LEN + sizeof(APPLICATION_RESPONSE_MSG);
      response->msg_length = SLS_APPLICATION_HEADER_LEN + sizeof(APPLICATION_RESPONSE_MSG);
      ap_response->type = APPLICATION_TYPE_RESPONSE;
      ap_response->length = sizeof(APPLICATION_RESPONSE_MSG);
      ap_response->contents = (uint8_t *)ar_msg;
      cgc_sprintf((char *)ar_msg->message, "Cleared Board\n", cgc_numMessages, APPLICATION_MAX_MESSAGES);
      cgc_msls_encrypt(ap_response->contents, ap_response->length, connection);
      cgc_msls_send_msg(response);
      cgc_msls_destroy_msg(response);
      break;
    }
    case APPLICATION_TYPE_READ_MESSAGE:
     {
      if (ap_msg->length < sizeof(APPLICATION_READ_MSG))
      {
        return;
      }
      cgc_msls_decrypt(((uint8_t *)ap_msg + SLS_APPLICATION_HEADER_LEN), ap_msg->length, connection);
      APPLICATION_READ_MSG *read_msg = (APPLICATION_READ_MSG *)((uint8_t *)ap_msg + SLS_APPLICATION_HEADER_LEN);

      cgc_debug_print("Reading slot $d\n", read_msg->msg_num);
      SLS_MESSAGE *response = cgc_calloc(sizeof(SLS_MESSAGE));
      SLS_APPLICATION_MESSAGE *ap_response = cgc_calloc(sizeof(SLS_APPLICATION_MESSAGE));
      APPLICATION_RESPONSE_MSG *ar_msg = cgc_calloc(sizeof(APPLICATION_RESPONSE_MSG));
      response->type = SLS_TYPE_APPLICATION;
      response->version = SLS_VERSION;
      response->connection_id = msg->connection_id;
      response->message = (uint8_t *)ap_response;
      response->length = SLS_HEADER_LENGTH + SLS_APPLICATION_HEADER_LEN + sizeof(APPLICATION_RESPONSE_MSG);
      response->msg_length = SLS_APPLICATION_HEADER_LEN + sizeof(APPLICATION_RESPONSE_MSG);
      ap_response->type = APPLICATION_TYPE_RESPONSE;
      ap_response->length = sizeof(APPLICATION_RESPONSE_MSG);
      ap_response->contents = (uint8_t *)ar_msg;
      if (read_msg->msg_num >= APPLICATION_MAX_MESSAGES)
      {
        cgc_sprintf((char *)ar_msg->message, "INVALID MESSAGE");
      } else {
        cgc_memcpy((char *)ar_msg->message, APPLICATION_MSG_BOARD[read_msg->msg_num], APPLICATION_MSG_LENGTH);
      }
      cgc_msls_encrypt(ap_response->contents, ap_response->length, connection);
      cgc_msls_send_msg(response);
      cgc_msls_destroy_msg(response);
      break;
    }
    default:
      return;
  }

}

void cgc_clear_message_board()
{
  cgc_memset(APPLICATION_MSG_BOARD, 0, sizeof(APPLICATION_MSG_BOARD));
  cgc_numMessages = 0;
}


int cgc_delete_message(uint8_t msg_num)
{
  if (msg_num >= APPLICATION_MAX_MESSAGES)
  {
    return -1;
  }
  cgc_memset(APPLICATION_MSG_BOARD[msg_num], 0, APPLICATION_MSG_LENGTH);
  for (int i = msg_num; i < APPLICATION_MAX_MESSAGES - 1; i++)
  {
    cgc_memcpy(APPLICATION_MSG_BOARD[i], APPLICATION_MSG_BOARD[i+1], APPLICATION_MSG_LENGTH);
  }
  cgc_numMessages--;
  return 1;
}

int cgc_post_new_message(uint8_t *message)
{
  if (cgc_numMessages >= APPLICATION_MAX_MESSAGES)
  {
    return -1;
  }
  cgc_memcpy(APPLICATION_MSG_BOARD[cgc_numMessages], message, APPLICATION_MSG_LENGTH);
  cgc_numMessages++;
  return 1;
}

