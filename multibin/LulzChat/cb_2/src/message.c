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

#include <stdlib.h>
#include <string.h>
#include "message.h"
#include "coffee.h"

message_t* parse_message(char *data, user_t *from, user_t *to, unsigned int len)
{
  size_t header_sz = sizeof(message_t) - sizeof(char *);
  message_t *msg = NULL;
  msg = (message_t *) malloc(sizeof(message_t));
  if (msg == NULL)
    goto fail;

  if (header_sz > len)
    goto fail;

  msg->type = *((unsigned short *) &data[0]);
  msg->to_id = to->user_id;
  msg->from_id = *((unsigned short *) &data[4]);
  msg->text_len = *((unsigned short *) &data[6]);

  if (msg->from_id != from->user_id)
    goto fail;

  if (msg->text_len <= 0 || msg->text_len > MAX_TEXT_LEN)
    goto fail;

  if (len - header_sz < msg->text_len)
    goto fail;

  if (msg->type == TYPE_PROTECTED)
  {
    unsigned int key[4];
    char *unprotected = malloc(MAX_TEXT_LEN + 1);
    if (unprotected == NULL)
      goto fail;
    memset(unprotected, 0, MAX_TEXT_LEN + 1);
    strncpy(unprotected, msg->text, MAX_TEXT_LEN);
    key[0] = from->auth_code;
    key[1] = from->auth_code ^ from->user_id;
    key[2] = from->auth_code ^ (unsigned int)(-1);
    key[3] = from->auth_code;
    unprotect_msg(key, unprotected, MAX_TEXT_LEN);
    key[0] = to->auth_code;
    key[1] = to->auth_code ^ to->user_id;
    key[2] = to->auth_code ^ from->user_id;
    key[3] = to->auth_code;
    protect_msg(key, unprotected, MAX_TEXT_LEN);
    msg->text = malloc(MAX_TEXT_LEN);
    if (msg->text == NULL)
      goto fail;
    memcpy(msg->text, unprotected, MAX_TEXT_LEN);
    msg->text_len = MAX_TEXT_LEN;
  }
  else
  {
    msg->type = TYPE_NORMAL;
    msg->text = malloc(msg->text_len + 1);
    if (msg->text == NULL)
      goto fail;
    strncpy(msg->text, &data[8], msg->text_len);
  }
  return msg;

fail:
  free_message(msg);
  return NULL;
}

void free_message(message_t *msg)
{
  if (msg)
  {
    if (msg->text)
      free(msg->text);
    free(msg);
  }
}
