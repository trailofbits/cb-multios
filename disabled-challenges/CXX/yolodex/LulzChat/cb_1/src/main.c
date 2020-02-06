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
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_ctype.h"

#include "cgc_user.h"
#include "cgc_msg_queue.h"
#include "cgc_packet.h"
#include "cgc_request.h"
#include "cgc_response.h"
#include "cgc_message.h"

#define MAX_NUM_MSG 100

#define SFD_SERVER_W 3
#define SFD_SERVER_R 4
#define SFD_CLIENT_W 5
#define SFD_CLIENT_R 6

int cgc_is_alnum_str(char *str)
{
  int i, ret = 0;
  for (i = 0; i < cgc_strlen(str); ++i)
    ret |= !cgc_isalnum(str[i] & 0xFF);
  return !ret;
}

void cgc_list_messages(user_t *user, msg_queue messages)
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
      if (cgc_enq_msg(&tmp_queue, node->msg) != 0)
        goto fail;
      num_msg++;
    }
  }

  cgc_send_list_res(STATUS_OK, tmp_queue, num_msg);
  while ((msg = cgc_deq_msg(&tmp_queue)) != NULL);
  return;

fail:
  cgc_send_list_res(STATUS_FAIL, NULL, 0);
  while ((msg = cgc_deq_msg(&tmp_queue)) != NULL);
}

void cgc_view_message(user_t *user, msg_queue messages, int msg_id)
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
      if (cgc_enq_msg(&tmp_queue, node->msg) != 0)
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
      cgc_send_view_res(STATUS_OK, node->msg);
      break;
    }
    msg_cnt++;
  }

  while ((msg = cgc_deq_msg(&tmp_queue)) != NULL);
  return;

fail:
  cgc_send_view_res(STATUS_FAIL, NULL);
  while ((msg = cgc_deq_msg(&tmp_queue)) != NULL);
}

void cgc_send_message(msg_queue *messages, message_t *msg)
{
  if (cgc_enq_msg(messages, msg) != 0)
    cgc_send_send_res(STATUS_FAIL);
  else
    cgc_send_send_res(STATUS_OK);
}

void cgc_delete_message(user_t *user, msg_queue *messages, int msg_id)
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
      if (cgc_enq_msg(&tmp_queue, node->msg) != 0)
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
      if ((msg = cgc_deq_msg_at(&tmp_queue, msg_id - 1)) == NULL)
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

  if ((msg = cgc_deq_msg_at(messages, msg_cnt)) == NULL)
    goto fail;
  cgc_free_message(msg);
  cgc_send_delete_res(STATUS_OK, num_msg - 1);

  while ((msg = cgc_deq_msg(&tmp_queue)) != NULL);
  return;

fail:
  cgc_send_delete_res(STATUS_FAIL, 0);
  while ((msg = cgc_deq_msg(&tmp_queue)) != NULL);

}

int main(int cgc_argc, char *cgc_argv[])
{
  user_t *cur_user = NULL;
  user_list_t users = NULL;
  msg_queue messages = NULL;
  packet_t *packet = NULL;

  cgc_fdprintf(STDERR, "[INFO] LulzChat Server v0.1\n");

  while (1)
  {
    /* Read input */
    if ((packet = cgc_parse_packet(SFD_CLIENT_R)) != NULL)
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
              cgc_send_login_res(STATUS_BAD, NULL);
              goto fail;
            }
            cgc_memcpy(&login, packet->body, sizeof(login));

            login.username[MAX_USERNAME_LEN - 1] = '\0';
            login.password[MAX_PASSWORD_LEN - 1] = '\0';

            if (!cgc_is_alnum_str(login.username) || !cgc_is_alnum_str(login.password))
            {
              cgc_send_login_res(STATUS_BAD, NULL);
              goto fail;
            }

            if ((tmp_user = cgc_find_user(users, login.username)) != NULL &&
                cgc_strcmp(tmp_user->password, login.password) == 0)
            {
              cgc_fdprintf(STDERR, "[INFO] %s has logged in.\n", login.username);
              cgc_send_login_res(STATUS_OK, tmp_user);
              cur_user = tmp_user;
            }
            else
            {
              cgc_fdprintf(STDERR, "[ERROR] Login failed.\n");
              cgc_send_login_res(STATUS_FAIL, NULL);
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
              cgc_send_register_res(STATUS_BAD, NULL);
              goto fail;
            }
            cgc_memcpy(&reg, packet->body, sizeof(reg));
            if ((new_user = cgc_find_user(users, reg.username)) != NULL)
            {
              cgc_fdprintf(STDERR, "[ERROR] Username already exists.\n");
              cgc_send_register_res(STATUS_EXISTS, NULL);
              goto fail;
            }
            if (cgc_strcmp(reg.password, reg.password_confirm) != 0)
            {
              cgc_fdprintf(STDERR, "[ERROR] Password didn't match.\n");
              cgc_send_register_res(STATUS_FAIL, NULL);
              goto fail;
            }

            new_user = (user_t *) cgc_malloc(sizeof(user_t));
            cgc_strcpy(new_user->username, reg.username);
            cgc_strcpy(new_user->password, reg.password);
            if (cgc_add_user(&users, new_user) == 0)
            {
              cgc_fdprintf(STDERR, "[INFO] Successfully registered!\n");
              cgc_send_register_res(STATUS_OK, new_user);
            }
            else
            {
              cgc_fdprintf(STDERR, "[ERROR] Failed to add a user.\n");
              cgc_send_register_res(STATUS_FAIL, NULL);
            }
          }
          break;
        case CMD_LIST:
          {
            list_req_t list;
            if (packet->body_len < sizeof(list))
            {
              cgc_send_list_res(STATUS_BAD, NULL, 0);
              goto fail;
            }
            cgc_memcpy(&list, packet->body, sizeof(list));
            cur_user = cgc_get_user(users, list.user_id, list.auth_code);
            cgc_list_messages(cur_user, messages);
            cur_user = NULL;
          }
          break;
        case CMD_VIEW:
          {
            view_req_t view;
            if (packet->body_len < sizeof(view))
            {
              cgc_send_view_res(STATUS_BAD, NULL);
              goto fail;
            }
            cgc_memcpy(&view, packet->body, sizeof(view));
            cur_user = cgc_get_user(users, view.user_id, view.auth_code);
            cgc_view_message(cur_user, messages, view.message_id);
            cur_user = NULL;
          }
          break;
        case CMD_SEND:
          {
            send_req_t send;
            read_sz = sizeof(send) - sizeof(message_t *);
            if (packet->body_len < read_sz)
            {
              cgc_send_send_res(STATUS_BAD);
              goto fail;
            }
            cgc_memcpy(&send, packet->body, read_sz);

            if ((cur_user = cgc_get_user(users, send.user_id, send.auth_code)) == NULL)
            {
              cgc_send_send_res(STATUS_DENIED);
              goto fail;
            }

            to_user = cgc_find_user(users, send.username);
            if (to_user == NULL)
            {
              cgc_send_send_res(STATUS_FAIL);
              goto fail;
            }

            if (packet->body_len - read_sz > 0)
              send.msg = cgc_parse_message(packet->body + read_sz, cur_user, to_user, packet->body_len - read_sz);
            if (send.msg == NULL)
            {
              cgc_send_send_res(STATUS_BAD);
              goto fail;
            }
            cgc_send_message(&messages, send.msg);
            cur_user = NULL;
          }
          break;
        case CMD_DELETE:
          {
            delete_req_t delete;
            if (packet->body_len < sizeof(delete))
            {
              cgc_send_delete_res(STATUS_BAD, 0);
              goto fail;
            }
            cgc_memcpy(&delete, packet->body, sizeof(delete));
            cur_user = cgc_get_user(users, delete.user_id, delete.auth_code);
            cgc_delete_message(cur_user, &messages, delete.message_id);
            cur_user = NULL;
          }
          break;
        case CMD_QUIT:
          {
            cgc_exit(0);
          }
          break;
        default:
          cgc_fdprintf(STDERR, "[ERROR] Unknown command.\n");
          break;
      }
    }
    else
    {
      cgc_fdprintf(STDERR, "[ERROR] Invalid packet detected.\n");
    }
fail:
    cgc_free_packet(packet);
    cur_user = NULL;
  }

  return 0;
}
