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
#include "cgc_util.h"
#include "cgc_coffee.h"

#define MAX_NUM_MSG 100

#define SFD_SERVER_W 3
#define SFD_SERVER_R 4
#define SFD_CLIENT_W 5
#define SFD_CLIENT_R 6

user_t cur_user;

int cgc_is_alnum_str(char *str)
{
  int i, ret = 0;
  for (i = 0; i < cgc_strlen(str); ++i)
    ret |= !cgc_isalnum(str[i] & 0xFF);
  return !ret;
}

void cgc_quit()
{
  quit_req_t q;
  cgc_fdprintf(STDOUT, "[INFO] Bye!\n");
  q.code = 0;
  cgc_send_request(&q, CMD_QUIT);
  cgc_exit(0);
}

void cgc_help()
{
  cgc_fdprintf(STDOUT, "---- Commands --------------------\n");
  cgc_fdprintf(STDOUT, " 'h'elp - display this help menu\n");
  cgc_fdprintf(STDOUT, " 'r'egister - register a user\n");
  cgc_fdprintf(STDOUT, " 'l'ogin - login\n");
  cgc_fdprintf(STDOUT, " 'o'ut - logout\n");
  cgc_fdprintf(STDOUT, " 'e'numerate - list messages\n");
  cgc_fdprintf(STDOUT, " 'v'iew - view a message\n");
  cgc_fdprintf(STDOUT, " 's'end - send a message\n");
  cgc_fdprintf(STDOUT, " 'd'elete - delete a message\n");
  cgc_fdprintf(STDOUT, " 'q'uit - quit\n");
  cgc_fdprintf(STDOUT, "----------------------------------\n");
}

void cgc_register_user()
{
  packet_t *p = NULL;
  response_t res;
  register_req_t reg;

  cgc_fdprintf(STDOUT, "\n[[[ REGISTER ]]]\n");
  cgc_fdprintf(STDOUT, "- username: ");
  if (cgc_read_until(STDIN, reg.username, MAX_USERNAME_LEN, '\n') < 0)
    goto fail;
  cgc_fdprintf(STDOUT, "- password: ");
  if (cgc_read_until(STDIN, reg.password, MAX_PASSWORD_LEN, '\n') < 0)
    goto fail;
  cgc_fdprintf(STDOUT, "- password confirm: ");
  if (cgc_read_until(STDIN, reg.password_confirm, MAX_PASSWORD_LEN, '\n') < 0)
    goto fail;

  cgc_send_request(&reg, CMD_REGISTER);
  cgc_fdprintf(STDOUT, "\n");

  p = cgc_parse_packet(SFD_SERVER_R);
  if (p == NULL)
      goto fail;
  if (p->body_len < 2 * sizeof(int))
      goto fail;
  cgc_memcpy(&res, p->body, 2 * sizeof(int));
  if (res.data_len > 0)
      res.data = p->body + 2 * sizeof(int);
  cgc_handle_response(p->command, &res);

fail:
  if (p)
    cgc_free(p);
}

void cgc_logout_user()
{
  if (cur_user.user_id == 0)
    cgc_fdprintf(STDOUT, "[ERROR] Not logged in.\n");
  else
  {
    cgc_memset(cur_user.username, 0, MAX_USERNAME_LEN);
    cgc_memset(cur_user.password, 0, MAX_PASSWORD_LEN);
    cur_user.user_id = 0;
    cur_user.auth_code = 0;
    cgc_fdprintf(STDOUT, "[INFO] Successfully logged out.\n");
  }
}

void cgc_login_user()
{
  packet_t *p = NULL;
  response_t res;
  login_req_t login;

  cgc_fdprintf(STDOUT, "\n[[[ LOGIN ]]]\n");
  cgc_fdprintf(STDOUT, "- username: ");
  if (cgc_read_until(STDIN, login.username, MAX_USERNAME_LEN, '\n') < 0)
    goto fail;
  cgc_fdprintf(STDOUT, "- password: ");
  if (cgc_read_until(STDIN, login.password, MAX_PASSWORD_LEN, '\n') < 0)
    goto fail;

  cgc_send_request(&login, CMD_LOGIN);

  p = cgc_parse_packet(SFD_SERVER_R);
  if (p == NULL)
      goto fail;
  if (p->body_len < 2 * sizeof(int))
      goto fail;
  cgc_memcpy(&res, p->body, 2 * sizeof(int));
  if (res.data_len > 0)
      res.data = p->body + 2 * sizeof(int);
  if (cgc_handle_response(p->command, &res) == 0)
  {
    if (p->body_len - 2 * sizeof(int) >= res.data_len &&
        res.data_len >= sizeof(short) + sizeof(int))
    {
      if (cur_user.user_id != 0)
        cgc_logout_user();
      cgc_strcpy(cur_user.username, login.username);
      cgc_strcpy(cur_user.password, login.password);
      cur_user.user_id = *((short *) res.data);
      cur_user.auth_code = *((int *) &res.data[2]);
    }
  }

fail:
  if (p)
    cgc_free(p);
}

int cgc_list_messages()
{
  short num_msg = 0, i;
  packet_t *p = NULL;
  response_t res;
  list_req_t list;

  if (cur_user.user_id == 0)
  {
    cgc_fdprintf(STDOUT, "[ERROR] Login first, please.\n");
    goto fail;
  }

  list.user_id = cur_user.user_id;
  list.auth_code = cur_user.auth_code;
  cgc_send_request(&list, CMD_LIST);

  p = cgc_parse_packet(SFD_SERVER_R);
  if (p == NULL)
      goto fail;
  if (p->body_len < 2 * sizeof(int))
      goto fail;
  cgc_memcpy(&res, p->body, 2 * sizeof(int));
  if (res.data_len > 0)
      res.data = p->body + 2 * sizeof(int);
  if (cgc_handle_response(p->command, &res) == 0)
  {
    if (p->body_len - 2 * sizeof(int) >= res.data_len &&
        res.data_len >= sizeof(short))
    {
      num_msg = *((short *) res.data);
      if (res.data_len - sizeof(short) < num_msg * (4 * sizeof(short)))
        goto fail;
      int cnt = 0;
      char *dp = res.data + sizeof(short);
      cgc_fdprintf(STDOUT, "\n[[[ MESSAGES ]]]\n");
      cgc_fdprintf(STDOUT, "idx. <from_id, length, type>\n");
      cgc_fdprintf(STDOUT, "----------------------------\n");
      for (i = 0, cnt = 0; cnt < num_msg; cnt++)
      {
        unsigned short type = *((unsigned short *) (dp + i));
        unsigned short from_id = *((unsigned short *) (dp + i + 4));
        unsigned short text_len = *((unsigned short *) (dp + i + 6));
        if (type == TYPE_PROTECTED)
          cgc_fdprintf(STDOUT, "%d. <%d, N/A, Protected>\n", cnt + 1, from_id);
        else
          cgc_fdprintf(STDOUT, "%d. <%d, %d bytes, Normal>\n", cnt + 1, from_id, text_len - 1);
        i += 4 * sizeof(short);
      }
      cgc_fdprintf(STDOUT, "Total %d message(s).\n\n", num_msg);
    }
  }

fail:
  if (p)
    cgc_free(p);

  return num_msg;
}

void cgc_display_message(message_t msg)
{
  char *msg_text = NULL;
  char *type_string = msg.type == TYPE_PROTECTED ? "Protected" : "Normal";
  cgc_fdprintf(STDOUT, "From: USER_%d\n", msg.from_id);
  cgc_fdprintf(STDOUT, "Type: %s\n", type_string);
  if (msg.type == TYPE_PROTECTED)
  {
    unsigned int key[4];
    char *unprotected = cgc_malloc(MAX_TEXT_LEN + 1);
    if (unprotected == NULL)
    {
      cgc_fdprintf(STDOUT, "Message: N/A (Error occurred)\n");
      return;
    }
    cgc_memset(unprotected, 0, MAX_TEXT_LEN + 1);
    cgc_strncpy(unprotected, msg.text, MAX_TEXT_LEN);
    key[0] = cur_user.auth_code;
    key[1] = cur_user.auth_code ^ cur_user.user_id;
    key[2] = cur_user.auth_code ^ cur_user.user_id;
    key[3] = cur_user.auth_code;
    cgc_unprotect_msg(key, unprotected, MAX_TEXT_LEN);
    msg_text = unprotected;
    cgc_free(unprotected);
  }
  else
  {
    msg_text = msg.text;
  }

  if (msg_text)
  {
    cgc_fdprintf(STDOUT, "Length: %d byte(s)\n", cgc_strlen(msg_text));
    cgc_fdprintf(STDOUT, "Message: %s\n", msg_text);
  }
  else
  {
    cgc_fdprintf(STDOUT, "Length: N/A\n");
    cgc_fdprintf(STDOUT, "Message: N/A (Error occurred)\n");
  }
}

void cgc_view_message()
{
  packet_t *p = NULL;
  response_t res;
  char *c, buf[32];
  int msg_id = -1;
  view_req_t view;

  if (cur_user.user_id == 0)
  {
    cgc_fdprintf(STDOUT, "[ERROR] Login first, please.\n");
    return;
  }

  /* Print out messages */
  int num_msg = cgc_list_messages();
  if (num_msg == 0)
  {
    cgc_fdprintf(STDOUT, "[INFO] You have no message.\n");
    goto fail;
  }

  cgc_fdprintf(STDOUT, "Select idx > ");
  if (cgc_read_until(STDIN, buf, sizeof(buf), '\n') < 0)
    goto fail;
  msg_id = cgc_strtol(buf, &c, 10);
  if (buf == c)
    goto fail;

  if (msg_id < 1 || msg_id > num_msg)
  {
    cgc_fdprintf(STDOUT, "[ERROR] Invalid idx.\n");
    goto fail;
  }

  view.user_id = cur_user.user_id;
  view.auth_code = cur_user.auth_code;
  view.message_id = msg_id;
  cgc_send_request(&view, CMD_VIEW);
  cgc_fdprintf(STDOUT, "\n");

  p = cgc_parse_packet(SFD_SERVER_R);
  if (p == NULL)
      goto fail;
  if (p->body_len < 2 * sizeof(int))
      goto fail;
  cgc_memcpy(&res, p->body, 2 * sizeof(int));
  if (res.data_len > 0)
      res.data = p->body + 2 * sizeof(int);
  if (cgc_handle_response(p->command, &res) == 0)
  {
    if (p->body_len - 2 * sizeof(int) >= res.data_len &&
        res.data_len >= sizeof(message_t) - sizeof(char *))
    {
      message_t msg;
      cgc_memcpy(&msg, res.data, sizeof(message_t) - sizeof(char *));
      msg.text = res.data + sizeof(message_t) - sizeof(char *);
      cgc_display_message(msg);
    }
  }

fail:
  if (p)
    cgc_free(p);
}

void cgc_send_message()
{
  packet_t *p = NULL;
  response_t res;
  int type = 0, msg_len = 0;
  char *c, buf[MAX_TEXT_LEN];
  message_t msg;
  send_req_t send;

  if (cur_user.user_id == 0)
  {
    cgc_fdprintf(STDOUT, "[ERROR] Login first, please.\n");
    return;
  }

  cgc_fdprintf(STDOUT, "\n[[[ SEND ]]]\n");
  cgc_fdprintf(STDOUT, " - To: ");
  if (cgc_read_until(STDIN, send.username, MAX_USERNAME_LEN, '\n') < 0)
    goto fail;
  cgc_fdprintf(STDOUT, " - Type (0: normal, 1: protected): ");
  if (cgc_read_until(STDIN, buf, sizeof(buf), '\n') < 0)
    goto fail;
  type = cgc_strtol(buf, &c, 10);
  if (buf == c)
    goto fail;
  cgc_memset(buf, '\0', sizeof(buf));
  cgc_fdprintf(STDOUT, " - Message: ");
  if ((msg_len = cgc_read_until(STDIN, buf, MAX_TEXT_LEN, '\n')) < 0)
    goto fail;
  cgc_fdprintf(STDOUT, "\n");

  msg.type = type == 1 ? TYPE_PROTECTED : TYPE_NORMAL;
  msg.to_id = -1;
  msg.from_id = cur_user.user_id;
  msg.text_len = msg_len;

  if (msg.type == TYPE_PROTECTED)
  {
    unsigned int key[4];
    key[0] = cur_user.auth_code;
    key[1] = cur_user.auth_code ^ cur_user.user_id;
    key[2] = cur_user.auth_code ^ cur_user.user_id;
    key[3] = cur_user.auth_code;
    cgc_protect_msg(key, buf, MAX_TEXT_LEN);
    msg.text_len = MAX_TEXT_LEN;
  }
  msg.text = buf;

  send.user_id = cur_user.user_id;
  send.auth_code = cur_user.auth_code;
  send.msg = &msg;
  cgc_send_request(&send, CMD_SEND);

  p = cgc_parse_packet(SFD_SERVER_R);
  if (p == NULL)
      goto fail;
  if (p->body_len < 2 * sizeof(int))
      goto fail;
  cgc_memcpy(&res, p->body, 2 * sizeof(int));
  if (res.data_len > 0)
      res.data = p->body + 2 * sizeof(int);
  cgc_handle_response(p->command, &res);

fail:
  if (p)
    cgc_free(p);
}

void cgc_delete_message()
{
  packet_t *p = NULL;
  response_t res;
  char *c, buf[32];
  int msg_id = -1;
  delete_req_t delete;

  if (cur_user.user_id == 0)
  {
    cgc_fdprintf(STDOUT, "[ERROR] Login first, please.\n");
    return;
  }

  /* Print out messages */
  int num_msg = cgc_list_messages();
  if (num_msg == 0)
  {
    cgc_fdprintf(STDOUT, "[INFO] You have no message.\n");
    goto fail;
  }

  cgc_fdprintf(STDOUT, "Select idx > ");
  if (cgc_read_until(STDIN, buf, sizeof(buf), '\n') < 0)
    goto fail;
  msg_id = cgc_strtol(buf, &c, 10);
  if (buf == c)
    goto fail;

  delete.user_id = cur_user.user_id;
  delete.auth_code = cur_user.auth_code;
  delete.message_id = msg_id;
  cgc_send_request(&delete, CMD_DELETE);
  cgc_fdprintf(STDOUT, "\n");

  p = cgc_parse_packet(SFD_SERVER_R);
  if (p == NULL)
      goto fail;
  if (p->body_len < 2 * sizeof(int))
      goto fail;
  cgc_memcpy(&res, p->body, 2 * sizeof(int));
  if (res.data_len > 0)
      res.data = p->body + 2 * sizeof(int);
  if (cgc_handle_response(p->command, &res) == 0)
  {
    if (p->body_len - 2 * sizeof(int) >= res.data_len &&
        res.data_len >= sizeof(int))
    {
      num_msg = *((int *) res.data);
      cgc_fdprintf(STDOUT, "%d message(s) left.\n", num_msg);
    }
  }

fail:
  if (p)
    cgc_free(p);
}

int main(int cgc_argc, char *cgc_argv[])
{
  char buf[4096];
  user_list_t users = NULL;
  msg_queue messages = NULL;
  packet_t *packet = NULL;

  cur_user.user_id = 0;

  cgc_fdprintf(STDOUT, "[INFO] LulzChat Client v0.1\n");
  cgc_fdprintf(STDOUT, "[INFO] Type 'h' for help menu\n");

  while (1)
  {
    /* Read input */
    cgc_fdprintf(STDOUT, "> ");
    if (cgc_read_until(STDIN, buf, sizeof(buf),'\n') <= 0)
      cgc_quit();

    switch (buf[0])
    {
      case 'H':
      case 'h':
        cgc_help();
        break;
      case 'R':
      case 'r':
        cgc_register_user();
        break;
      case 'L':
      case 'l':
        cgc_login_user();
        break;
      case 'O':
      case 'o':
        cgc_logout_user();
        break;
      case 'E':
      case 'e':
        cgc_list_messages();
        break;
      case 'V':
      case 'v':
        cgc_view_message();
        break;
      case 'S':
      case 's':
        cgc_send_message();
        break;
      case 'D':
      case 'd':
        cgc_delete_message();
        break;
      case 'Q':
      case 'q':
        cgc_quit();
        break;
      default:
        cgc_fdprintf(STDIN, "[ERROR] Unknown command.\n");
        break;
    }

  }

  return 0;
}
