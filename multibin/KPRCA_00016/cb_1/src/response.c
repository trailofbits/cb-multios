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

#include <libcgc.h>
#include <stdlib.h>
#include <string.h>
#include "response.h"

#define SFD_SERVER  3
#define SFD_CLIENT 4

extern user_t *cur_user;

void send_response(response_t *res, enum cmd_t cmd)
{
  packet_t* packet = new_packet(T_RESPONSE, cmd);
  if (packet == NULL)
    return;
  packet->body_len = 2 * sizeof(int) + res->data_len;
  packet->body = malloc(packet->body_len);
  if (packet->body)
  {
    memcpy(packet->body, (char *)res, 2 * sizeof(int));
    if (res->data_len > 0 && res->data != NULL)
      memcpy(packet->body + 2 * sizeof(int), res->data, res->data_len);
    packet->checksum = calc_checksum(packet);
    size_t size = sizeof(packet_t) - sizeof(char *);
    transmit(SFD_SERVER, (char *)packet, size, NULL);
    transmit(SFD_SERVER, packet->body, packet->body_len, NULL);
  }

  free_packet(packet);
}

void send_register_res(int status, user_t *user)
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

  send_response(&res, CMD_REGISTER);
}

void send_login_res(int status, user_t *user)
{
  response_t res;
  res.status_code = status;

  if (status == STATUS_OK)
  {
    if (user == NULL)
      return;
    res.data = malloc(sizeof(short) + sizeof(int));
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

  send_response(&res, CMD_LOGIN);

  if (res.data)
    free(res.data);
}

void send_list_res(int status, msg_queue messages, int num_msg)
{
  int i, cnt;
  char *dp;
  message_t *msg;
  response_t res;
  res.status_code = status;

  if (status == STATUS_OK)
  {
    if (num_msg > 0 && messages == NULL)
      goto fail;
    res.data_len = sizeof(short) + num_msg * (4 * sizeof(short));
    res.data = malloc(res.data_len);
    if (res.data == NULL)
      goto fail;
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
fail:
    res.data = NULL;
    res.data_len = 0;
  }

  send_response(&res, CMD_LIST);

  if (res.data)
    free(res.data);
}

void send_view_res(int status, message_t *msg)
{
  response_t res;
  res.status_code = status;

  if (status == STATUS_OK)
  {
    if (msg == NULL)
      goto fail;
    res.data_len = sizeof(message_t) - sizeof(char *) + msg->text_len;
    res.data = malloc(res.data_len);
    if (res.data == NULL)
      goto fail;
    memcpy(res.data, (char *)msg, sizeof(message_t) - sizeof(char *));
    memcpy(res.data + sizeof(message_t) - sizeof(char *), msg->text, msg->text_len);
  }
  else
  {
fail:
    res.data = NULL;
    res.data_len = 0;
  }

  send_response(&res, CMD_VIEW);
}

void send_send_res(int status)
{
  response_t res;
  res.status_code = status;
  res.data = NULL;
  res.data_len = 0;

  send_response(&res, CMD_SEND);
}

void send_delete_res(int status, int num_msg)
{
  response_t res;
  res.status_code = status;

  if (status == STATUS_OK)
  {
    res.data = malloc(sizeof(int));
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

  send_response(&res, CMD_DELETE);

  if (res.data)
    free(res.data);
}

int handle_response(enum cmd_t cmd, response_t *res)
{
  switch (cmd)
  {
    case CMD_REGISTER:
      if (res->status_code == STATUS_OK)
      {
        fdprintf(STDOUT, "[INFO] Registration Successful! (%s)\n", res->data);
        return 0;
      }
      else if (res->status_code == STATUS_EXISTS)
        fdprintf(STDOUT, "[ERROR] Username already exists.\n");
      else if (res->status_code == STATUS_FAIL)
        fdprintf(STDOUT, "[ERROR] Registration Failed..\n");
      else
        fdprintf(STDOUT, "[ERROR] Bad format.\n");
      break;
    case CMD_LOGIN:
      if (res->status_code == STATUS_OK)
      {
        fdprintf(STDOUT, "[INFO] Login Successful!\n");
        return 0;
      }
      else if (res->status_code == STATUS_FAIL)
        fdprintf(STDOUT, "[INFO] Login Failed.\n");
      else
        fdprintf(STDOUT, "[ERROR] Bad format.\n");
      break;
    case CMD_LIST:
      if (res->status_code == STATUS_OK)
        return 0;
      else
        fdprintf(STDOUT, "[ERROR] List Failed.\n");
      break;
    case CMD_VIEW:
      if (res->status_code == STATUS_OK)
        return 0;
      else
        fdprintf(STDOUT, "[ERROR] View Failed.\n");
      break;
    case CMD_SEND:
      if (res->status_code == STATUS_OK)
        return 0;
      else if (res->status_code == STATUS_FAIL)
        fdprintf(STDOUT, "[ERROR] Send Failed.\n");
      else
        fdprintf(STDOUT, "[ERROR] Bad format.\n");
      break;
    case CMD_DELETE:
      if (res->status_code == STATUS_OK)
      {
        fdprintf(STDOUT, "[INFO] Successfully deleted.\n");
        return 0;
      }
      else if (res->status_code == STATUS_FAIL)
        fdprintf(STDOUT, "[ERROR] Delete Failed.\n");
      else
        fdprintf(STDOUT, "[ERROR] Bad format.\n");
      break;
    default:
      fdprintf(STDOUT, "[ERROR] Unknown command type.\n");
      break;
  }
  return -1;
}

