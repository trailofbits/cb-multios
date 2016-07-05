/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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
#include <ctype.h>

#include "lsimp.h"

int compute_guard(unsigned char *buf, unsigned int buf_len)
{
  unsigned int i, guard = 0;
  for (i = 0; i < buf_len; ++i)
    guard = (guard << 10) ^ (guard + buf[i]);
  return guard;
}

int decode_data(lsimp_keyx_t *keyx, lsimp_data_t *data)
{
  int i;

  if (data->data_len < 4)
    return 0;

  if ((keyx->option & 0x0F) == 0x07)
    memmove(data->data, data->data + 4, data->data_len);
  data->data_len -= 4;

  for (i = 0; i < data->data_len; ++i)
    data->data[i] ^= keyx->key[i % keyx->key_len];

  if ((keyx->option & 0x0F) != 0x07)
    data->data[data->data_len] = '\0';
  return 1;
}

lsimp_msg_t* parse_msg(char *buf, unsigned int buf_len)
{
  int dword;
  unsigned int obl = buf_len;
  char *pos = buf;
  lsimp_msg_t *msg = NULL;

  if (buf_len < 4)
    goto fail;

  msg = (lsimp_msg_t *)malloc(sizeof(lsimp_msg_t));
  if (msg == NULL)
    goto fail;
  memset(msg, 0, sizeof(lsimp_msg_t));

  while (buf_len >= 4)
  {
#if PATCHED
    if (msg->type) break;
#endif
    if (buf_len == 4) break;
    dword = *(int *)(pos);
    pos += sizeof(int);
    buf_len -= sizeof(int);
    switch (dword)
    {
      case LMT_HELO:
        msg->type = LMT_HELO;
        if (buf_len >= sizeof(char))
        {
          msg->helo.version = *(pos++);
          buf_len--;
        }
        if (buf_len >= sizeof(char))
        {
          msg->helo.secure_mode = *(pos++);
          buf_len--;
        }
        if (buf_len >= sizeof(int))
        {
          msg->helo.ttl = *(int *)(pos);
          pos += sizeof(int);
          buf_len -= sizeof(int);
        }
        break;
      case LMT_KEYX:
        msg->type = LMT_KEYX;
        if (buf_len >= sizeof(char))
        {
          msg->keyx.option = *(pos++);
          buf_len--;
        }
        if (buf_len >= sizeof(int))
        {
          msg->keyx.key_len = *(int *)(pos);
          pos += sizeof(int);
          buf_len -= sizeof(int);
        }
        if (msg->keyx.key_len > MAX_KEY_LEN || buf_len < msg->keyx.key_len)
          goto fail;
        if (msg->keyx.key_len > 0)
        {
          msg->keyx.key = malloc(msg->keyx.key_len);
          if (msg->keyx.key == NULL)
            goto fail;
          memmove(msg->keyx.key, pos, msg->keyx.key_len);
          pos += msg->keyx.key_len;
          buf_len -= msg->keyx.key_len;
        }
        break;
      case LMT_DATA:
        msg->type = LMT_DATA;
        if (buf_len >= sizeof(int))
        {
          msg->data.seq = *(int *)(pos);
          pos += sizeof(int);
          buf_len -= sizeof(int);
        }
        if (msg->data.seq < 1)
          goto fail;
        if (buf_len >= sizeof(int))
        {
          msg->data.data_len = *(int *)(pos);
          pos += sizeof(int);
          buf_len -= sizeof(int);
        }
        if (msg->data.data_len > MAX_DATA_LEN && buf_len < msg->data.data_len)
          goto fail;
        if (msg->data.data_len > 0)
        {
          msg->data.data = malloc(msg->data.data_len + 1);
          if (msg->data.data == NULL)
            goto fail;
          memset(msg->data.data, 0, msg->data.data_len + 1);
          memmove(msg->data.data, pos, msg->data.data_len);
          pos += msg->data.data_len;
          buf_len -= msg->data.data_len;
        }
        break;
      case LMT_TEXT:
        msg->type = LMT_TEXT;
        if (buf_len >= sizeof(int))
        {
          msg->text.msg_len = *(int *)(pos);
          pos += sizeof(int);
          buf_len -= sizeof(int);
        }
        if (msg->text.msg_len > MAX_TEXT_LEN && buf_len < msg->text.msg_len)
          goto fail;
        if (msg->text.msg_len > 0)
        {
          msg->text.msg = malloc(msg->text.msg_len + 1);
          if (msg->text.msg == NULL)
            goto fail;
          memset(msg->text.msg, 0, msg->text.msg_len + 1);
          memmove(msg->text.msg, pos, msg->text.msg_len);
          pos += msg->text.msg_len;
          buf_len -= msg->text.msg_len;
        }
        break;
      default:
        break;
    }
  }

  if (buf_len < 4)
    goto fail;
  int guard = *(int *)(pos);
  if (guard != compute_guard((unsigned char *)buf, obl - sizeof(int)))
    goto fail;

  return msg;

fail:
  if (msg)
    free(msg);
  return NULL;
}
