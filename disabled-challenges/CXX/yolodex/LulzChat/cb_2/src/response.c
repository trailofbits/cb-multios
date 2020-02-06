/*
 * Copyright (c) 2014 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_response.h"

extern user_t *cur_user;

void cgc_send_response(response_t *res, enum cmd_t cmd)
{
  packet_t* packet = cgc_new_packet(T_RESPONSE, cmd);
  if (packet == NULL)
    return;
  packet->body_len = 2 * sizeof(int) + res->data_len;
  packet->body = cgc_malloc(packet->body_len);
  if (packet->body)
  {
    cgc_memcpy(packet->body, (char *)res, 2 * sizeof(int));
    if (res->data_len > 0 && res->data != NULL)
      cgc_memcpy(packet->body + 2 * sizeof(int), res->data, res->data_len);
    packet->checksum = cgc_calc_checksum(packet);
    cgc_size_t size = sizeof(packet_t) - sizeof(char *) + packet->body_len;
    cgc_transmit(STDOUT, (char *)packet, size, NULL);
  }

  cgc_free_packet(packet);
}

void cgc_send_register_res(int status, user_t *user)
{
  response_t res;
  res.status_code = status;

  if (status == STATUS_OK)
  {
    if (user == NULL)
      return;
    res.data = user->username;
    res.data_len = MAX_USERNAME_LEN;
  }
  else
  {
    res.data = NULL;
    res.data_len = 0;
  }

  cgc_send_response(&res, CMD_REGISTER);
}

void cgc_send_login_res(int status, user_t *user)
{
  response_t res;
  res.status_code = status;

  if (status == STATUS_OK)
  {
    if (user == NULL)
      return;
    res.data = cgc_malloc(sizeof(short) + sizeof(int));
    if (res.data == NULL)
      return;
    *((short *) res.data) = user->user_id;
    *((int *) &res.data[2]) = user->auth_code;
    res.data_len = sizeof(short) + sizeof(int);
  }
  else
  {
    res.data = NULL;
    res.data_len = 0;
  }

  cgc_send_response(&res, CMD_LOGIN);

  if (res.data)
    cgc_free(res.data);
}

void cgc_send_list_res(int status, msg_queue messages, int num_msg)
{
  int i, cnt;
  char *dp;
  message_t *msg;
  response_t res;
  res.status_code = status;

  if (status == STATUS_OK)
  {
    if (messages == NULL)
      return;
    res.data = cgc_malloc(sizeof(short) + num_msg * (4 * sizeof(short)));
    if (res.data == NULL)
      return;
    *((short *) res.data) = num_msg;
    dp = res.data + sizeof(short);
    for (i = 0, cnt = 0; cnt < num_msg; cnt++)
    {
      msg = messages->msg;
      if (msg == NULL)
        return;
      *((unsigned short *) (dp + i)) = msg->type;
      *((unsigned short *) (dp + i + 2)) = msg->to_id;
      *((unsigned short *) (dp + i + 4)) = msg->from_id;
      *((unsigned short *) (dp + i + 6)) = msg->text_len;
      i += 4 * sizeof(short);
      messages = messages->next;
    }
  }
  else
  {
    res.data = NULL;
    res.data_len = 0;
  }

  cgc_send_response(&res, CMD_LIST);

  if (res.data)
    cgc_free(res.data);
}

void cgc_send_view_res(int status, message_t *msg)
{
  response_t res;
  res.status_code = status;

  if (status == STATUS_OK)
  {
    if (msg == NULL)
      return;
    res.data = (char *) msg;
    res.data_len = sizeof(message_t);
  }
  else
  {
    res.data = NULL;
    res.data_len = 0;
  }

  cgc_send_response(&res, CMD_VIEW);
}

void cgc_send_send_res(int status)
{
  response_t res;
  res.status_code = status;
  res.data = NULL;
  res.data_len = 0;

  cgc_send_response(&res, CMD_SEND);
}

void cgc_send_delete_res(int status, int num_msg)
{
  response_t res;
  res.status_code = status;

  if (status == STATUS_OK)
  {
    res.data = cgc_malloc(sizeof(int));
    if (res.data == NULL)
      return;
    *((int *) res.data) = num_msg;
    res.data_len = sizeof(int);
  }
  else
  {
    res.data = NULL;
    res.data_len = 0;
  }

  cgc_send_response(&res, CMD_DELETE);

  if (res.data)
    cgc_free(res.data);
}

int cgc_handle_response(enum cmd_t cmd, response_t *res)
{
  switch (cmd)
  {
    case CMD_REGISTER:
      if (res->status_code == STATUS_OK)
      {
        cgc_fdprintf(STDOUT, "[INFO] Registration Successful! (%s)\n", res->data);
        return 0;
      }
      else if (res->status_code == STATUS_EXISTS)
        cgc_fdprintf(STDOUT, "[ERROR] Username already exists.\n");
      else if (res->status_code == STATUS_FAIL)
        cgc_fdprintf(STDOUT, "[ERROR] Registration Failed..\n");
      else
        cgc_fdprintf(STDOUT, "[ERROR] Bad format.\n");
      break;
    case CMD_LOGIN:
      if (res->status_code == STATUS_OK)
      {
        cgc_fdprintf(STDOUT, "[INFO] Login Successful!\n");
        return 0;
      }
      else if (res->status_code == STATUS_FAIL)
        cgc_fdprintf(STDOUT, "[ERROR] Login Failed.\n");
      else
        cgc_fdprintf(STDOUT, "[ERROR] Bad format.\n");
      break;
    case CMD_LIST:
      if (res->status_code == STATUS_OK)
        return 0;
      else
        cgc_fdprintf(STDOUT, "[ERROR] List Failed.\n");
      break;
    case CMD_VIEW:
      if (res->status_code == STATUS_OK)
        return 0;
      else
        cgc_fdprintf(STDOUT, "[ERROR] View Failed.\n");
      break;
    case CMD_SEND:
      if (res->status_code == STATUS_OK)
        return 0;
      else if (res->status_code == STATUS_FAIL)
        cgc_fdprintf(STDOUT, "[ERROR] Send Failed.\n");
      else
        cgc_fdprintf(STDOUT, "[ERROR] Bad format.\n");
      break;
    case CMD_DELETE:
      if (res->status_code == STATUS_OK)
      {
        cgc_fdprintf(STDOUT, "[INFO] Successfully deleted.\n");
        return 0;
      }
      else if (res->status_code == STATUS_FAIL)
        cgc_fdprintf(STDOUT, "[ERROR] Delete Failed.\n");
      else
        cgc_fdprintf(STDOUT, "[ERROR] Bad format.\n");
      break;
    default:
      cgc_fdprintf(STDOUT, "[ERROR] Unknown command type.\n");
      break;
  }
  return -1;
}

