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
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "user.h"
#include "msg_queue.h"
#include "packet.h"
#include "request.h"
#include "response.h"
#include "message.h"

#define MAX_NUM_MSG 100

#define SFD_SERVER  3
#define SFD_CLIENT 4

int is_alnum_str(char *str)
{
  int i, ret = 0;
  for (i = 0; i < strlen(str); ++i)
    ret |= !isalnum(str[i] & 0xFF);
  return !ret;
}

void list_messages(user_t *user, msg_queue messages)
{
  int num_msg = 0;
  message_t *msg = NULL;
  node_t *node = NULL;
  msg_queue tmp_queue = NULL;

  if (user == NULL)
    goto fail;

  for (node = messages; node != NULL; node = node->next)
  {
    if (node->msg && user->user_id == node->msg->to_id)
    {
      // Only show up to MAX_NUM_MSG messages
      if (num_msg > MAX_NUM_MSG)
        break;
      if (enq_msg(&tmp_queue, node->msg) != 0)
        goto fail;
      num_msg++;
    }
  }

  send_list_res(STATUS_OK, tmp_queue, num_msg);
  while ((msg = deq_msg(&tmp_queue)) != NULL);
  return;

fail:
  send_list_res(STATUS_FAIL, NULL, 0);
  while ((msg = deq_msg(&tmp_queue)) != NULL);
}

void view_message(user_t *user, msg_queue messages, int msg_id)
{
  int msg_cnt = 1, num_msg = 0;
  node_t *node = NULL;
  message_t *msg = NULL;
  msg_queue tmp_queue = NULL;

  if (user == NULL)
    goto fail;

  for (node = messages; node != NULL; node = node->next)
  {
    if (node->msg && user->user_id == node->msg->to_id)
    {
      if (enq_msg(&tmp_queue, node->msg) != 0)
        goto fail;
      num_msg++;
    }
  }

  if (msg_id > num_msg)
    goto fail;

  for (node = tmp_queue; node != NULL; node = node->next)
  {
    if (node->msg && msg_cnt == msg_id)
    {
      send_view_res(STATUS_OK, node->msg);
      break;
    }
    msg_cnt++;
  }

  while ((msg = deq_msg(&tmp_queue)) != NULL);
  return;

fail:
  send_view_res(STATUS_FAIL, NULL);
  while ((msg = deq_msg(&tmp_queue)) != NULL);
}

void send_message(msg_queue *messages, message_t *msg)
{
  if (enq_msg(messages, msg) != 0)
    send_send_res(STATUS_FAIL);
  else
    send_send_res(STATUS_OK);
}

void delete_message(user_t *user, msg_queue *messages, int msg_id)
{
  int msg_cnt = 1, num_msg = 0;
  node_t *node = NULL;
  message_t *msg = NULL;
  msg_queue tmp_queue = NULL;

  if (user == NULL)
    goto fail;

  for (node = *messages; node != NULL; node = node->next)
  {
    if (node->msg && user->user_id == node->msg->to_id)
    {
      if (enq_msg(&tmp_queue, node->msg) != 0)
        goto fail;
      num_msg++;
    }
  }

#if PATCHED
  if (msg_id < 1 || msg_id > num_msg)
#else
  if (msg_id < 1UL || msg_id > num_msg)
#endif
    goto fail;
  for (node = tmp_queue; ; node = node->next)
  {
    if (node->msg && msg_cnt == msg_id)
    {
      if ((msg = deq_msg_at(&tmp_queue, msg_id - 1)) == NULL)
        goto fail;
      break;
    }
    msg_cnt++;
  }

  msg_cnt = 0;
  for (node = *messages; node != NULL; node = node->next)
  {
    if (node->msg && node->msg == msg)
      break;
    msg_cnt++;
  }

  if ((msg = deq_msg_at(messages, msg_cnt)) == NULL)
    goto fail;
  free_message(msg);
  send_delete_res(STATUS_OK, num_msg - 1);

  while ((msg = deq_msg(&tmp_queue)) != NULL);
  return;

fail:
  send_delete_res(STATUS_FAIL, 0);
  while ((msg = deq_msg(&tmp_queue)) != NULL);

}

int main()
{
  user_t *cur_user = NULL;
  user_list_t users = NULL;
  msg_queue messages = NULL;
  packet_t *packet = NULL;

  fdprintf(STDERR, "[INFO] LulzChat Server v0.1\n");

  while (1)
  {
    /* Read input */
    if ((packet = parse_packet(SFD_SERVER)) != NULL)
    {
      if (packet->type != T_REQUEST)
        goto fail;

      int read_sz = 0;
      user_t *to_user = NULL;

      switch (packet->command)
      {
        case CMD_LOGIN:
          {
            user_t *tmp_user;
            login_req_t login;
            if (packet->body_len < sizeof(login))
            {
              send_login_res(STATUS_BAD, NULL);
              goto fail;
            }
            memcpy(&login, packet->body, sizeof(login));

            login.username[MAX_USERNAME_LEN - 1] = '\0';
            login.password[MAX_PASSWORD_LEN - 1] = '\0';

            if (!is_alnum_str(login.username) || !is_alnum_str(login.password))
            {
              send_login_res(STATUS_BAD, NULL);
              goto fail;
            }

            if ((tmp_user = find_user(users, login.username)) != NULL &&
                strcmp(tmp_user->password, login.password) == 0)
            {
              fdprintf(STDERR, "[INFO] %s has logged in.\n", login.username);
              send_login_res(STATUS_OK, tmp_user);
              cur_user = tmp_user;
            }
            else
            {
              fdprintf(STDERR, "[ERROR] Login failed.\n");
              send_login_res(STATUS_FAIL, NULL);
              goto fail;
            }
          }
          break;
        case CMD_REGISTER:
          {
            user_t *new_user;
            register_req_t reg;
            if (packet->body_len < sizeof(reg))
            {
              send_register_res(STATUS_BAD, NULL);
              goto fail;
            }
            memcpy(&reg, packet->body, sizeof(reg));
            if ((new_user = find_user(users, reg.username)) != NULL)
            {
              fdprintf(STDERR, "[ERROR] Username already exists.\n");
              send_register_res(STATUS_EXISTS, NULL);
              goto fail;
            }
            if (strcmp(reg.password, reg.password_confirm) != 0)
            {
              fdprintf(STDERR, "[ERROR] Password didn't match.\n");
              send_register_res(STATUS_FAIL, NULL);
              goto fail;
            }

            new_user = (user_t *) malloc(sizeof(user_t));
            strcpy(new_user->username, reg.username);
            strcpy(new_user->password, reg.password);
            if (add_user(&users, new_user) == 0)
            {
              fdprintf(STDERR, "[INFO] Successfully registered!\n");
              send_register_res(STATUS_OK, new_user);
            }
            else
            {
              fdprintf(STDERR, "[ERROR] Failed to add a user.\n");
              send_register_res(STATUS_FAIL, NULL);
            }
          }
          break;
        case CMD_LIST:
          {
            list_req_t list;
            if (packet->body_len < sizeof(list))
            {
              send_list_res(STATUS_BAD, NULL, 0);
              goto fail;
            }
            memcpy(&list, packet->body, sizeof(list));
            cur_user = get_user(users, list.user_id, list.auth_code);
            list_messages(cur_user, messages);
            cur_user = NULL;
          }
          break;
        case CMD_VIEW:
          {
            view_req_t view;
            if (packet->body_len < sizeof(view))
            {
              send_view_res(STATUS_BAD, NULL);
              goto fail;
            }
            memcpy(&view, packet->body, sizeof(view));
            cur_user = get_user(users, view.user_id, view.auth_code);
            view_message(cur_user, messages, view.message_id);
            cur_user = NULL;
          }
          break;
        case CMD_SEND:
          {
            send_req_t send;
            read_sz = sizeof(send) - sizeof(message_t *);
            if (packet->body_len < read_sz)
            {
              send_send_res(STATUS_BAD);
              goto fail;
            }
            memcpy(&send, packet->body, read_sz);

            if ((cur_user = get_user(users, send.user_id, send.auth_code)) == NULL)
            {
              send_send_res(STATUS_DENIED);
              goto fail;
            }

            to_user = find_user(users, send.username);
            if (to_user == NULL)
            {
              send_send_res(STATUS_FAIL);
              goto fail;
            }

            if (packet->body_len - read_sz > 0)
              send.msg = parse_message(packet->body + read_sz, cur_user, to_user, packet->body_len - read_sz);
            if (send.msg == NULL)
            {
              send_send_res(STATUS_BAD);
              goto fail;
            }
            send_message(&messages, send.msg);
            cur_user = NULL;
          }
          break;
        case CMD_DELETE:
          {
            delete_req_t delete;
            if (packet->body_len < sizeof(delete))
            {
              send_delete_res(STATUS_BAD, 0);
              goto fail;
            }
            memcpy(&delete, packet->body, sizeof(delete));
            cur_user = get_user(users, delete.user_id, delete.auth_code);
            delete_message(cur_user, &messages, delete.message_id);
            cur_user = NULL;
          }
          break;
        case CMD_QUIT:
          {
            exit(0);
          }
          break;
        default:
          fdprintf(STDERR, "[ERROR] Unknown command.\n");
          break;
      }
    }
    else
    {
      fdprintf(STDERR, "[ERROR] Invalid packet detected.\n");
    }
fail:
    free_packet(packet);
    cur_user = NULL;
  }

  return 0;
}
