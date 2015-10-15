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
#include "readuntil.h"

#include "lsimp.h"

#define CURRENT_VER ((char) 103)
#define MAX_BUF_LEN 2048

lsimp_msg_t *head = NULL, *tail = NULL;

enum op_t {
  OP_QUEUE = 0,
  OP_PROCESS = 1,
  OP_QUIT = 2
};

typedef struct data_node {
  lsimp_data_t *data;
  struct data_node *next;
} data_node_t;

data_node_t* sorted(data_node_t *list)
{
  if (list)
  {
    data_node_t *s = NULL, *next = list, *cur = NULL, *c = NULL;;
    if (list->next == NULL)
      return list;

    while (next)
    {
      cur = next;
      next = cur->next;
      if (s == NULL || cur->data->seq < s->data->seq)
      {
        cur->next = s;
        s = cur;
      }
      else
      {
        c = s;
        while (c)
        {
          if (c->next == NULL || cur->data->seq < c->data->seq)
          {
            cur->next = c->next;
            c->next = cur;
            break;
          }
          c = c->next;
        }
      }
    }
    return s;
  }
  return NULL;
}

void queue_msg(lsimp_msg_t *msg)
{
  if (msg == NULL)
    return;

  if (head == NULL)
    head = tail = msg;
  else
  {
    tail->next = msg;
    tail = msg;
  }
  printf("QUEUED\n");
}

void clear_queue()
{
  if (head)
  {
    lsimp_msg_t *msg = head, *old = msg;
    while (msg)
    {
      if (msg->type == LMT_KEYX)
      {
        if (msg->keyx.key)
          free(msg->keyx.key);
      }
      else if (msg->type == LMT_DATA)
      {
        if (msg->data.data)
          free(msg->data.data);
      }
      else if (msg->type == LMT_TEXT)
      {
        if (msg->text.msg)
          free(msg->text.msg);
      }
      old = msg;
      msg = msg->next;
      free(old);
    }
  }
  printf("QUEUE CLEARED\n");
}

void process()
{
  int ttl = 0;
  lsimp_keyx_t *keyx = NULL;
  lsimp_helo_t *helo = NULL;
  data_node_t *dchain = NULL, *dtail = NULL;
  lsimp_msg_t *msg = head;

  if (head)
  {
    while (msg)
    {
      if (helo && ttl > helo->ttl)
        break;
      if (msg->type == LMT_HELO)
      {
        if (helo == NULL)
        {
          if (msg->helo.version == CURRENT_VER)
          {
            helo = &msg->helo;
            printf("HELO [VERSION %d] [SECURE %s] [TTL %d]\n",
                helo->version, helo->secure_mode ? "on" : "off", helo->ttl);
          }
          else
            printf("INVALID VERSION\n");
        }
      }
      else if (msg->type == LMT_KEYX)
      {
        if (helo == NULL)
          break;
        if (keyx == NULL)
        {
          if (!helo->secure_mode)
          {
            printf("KEYX IN NON-SECURE\n");
            break;
          }
          if (msg->keyx.key_len == 0)
          {
            printf("NO KEY\n");
            break;
          }

          keyx = &msg->keyx;

          printf("KEYX ");
          printf("[OPTION ");
          if ((keyx->option & 0x0F) == 0x07)
            printf("prepend | ");
          else
            printf("append | ");
          if ((keyx->option & 0xF0) == 0x30)
          {
            printf("inverted] ");
            int i;
            for (i = 0; i < keyx->key_len; ++i)
              keyx->key[i] = ~keyx->key[i];
          }
          else
            printf("as-is] ");
          printf("[LEN %d]\n", keyx->key_len);
        }
      }
      else if (msg->type == LMT_DATA)
      {
        if (helo == NULL)
          break;
        if (!helo->secure_mode)
        {
          printf("DATA IN NON-SECURE\n");
          break;
        }
        if (keyx == NULL)
        {
          printf("DATA BEFORE KEYX\n");
          break;
        }
        printf("DATA [SEQ %d] [LEN %d]\n", msg->data.seq, msg->data.data_len);
        if (dchain == NULL)
        {
          if ((dchain = (data_node_t *)malloc(sizeof(data_node_t))) != NULL)
          {
            dchain->data = &msg->data;
            dchain->next = NULL;
            dtail = dchain;
          }
        }
        else
        {
          if ((dtail->next = (data_node_t *)malloc(sizeof(data_node_t))) != NULL)
          {
            dtail = dtail->next;
            dtail->data = &msg->data;
            dtail->next = NULL;
          }
        }
      }
      else if (msg->type == LMT_TEXT)
      {
        if (helo == NULL)
          break;
        if (helo->secure_mode)
        {
          printf("TEXT IN SECURE\n");
          break;
        }
        if (msg->text.msg_len == 0)
        {
          printf("NO TEXT MSG\n");
          break;
        }
        printf("TEXT [LEN %d] [MSG %s]\n", msg->text.msg_len, msg->text.msg);
      }
      msg = msg->next;
      ttl++;
    }
  }

  if (helo == NULL)
    printf("HELO MISSING\n");

  if (dchain)
  {
    // dtail is wrong after this, but it's okay
    data_node_t *p = sorted(dchain);
    printf("SECURE MESSAGE:\n");
    int seq = 1, old = 0;
    while (p)
    {
      if (old == p->data->seq)
      {
        printf("(SEQ #%d DUP)", old);
        p = p->next;
        continue;
      }
      if (seq != p->data->seq)
        printf("(SEQ #%d MISSING)", seq);
      else
      {
        if (decode_data(keyx, p->data))
          printf("%s", p->data->data);
        p = p->next;
      }
      old = seq++;
    }
    printf("\n");
  }

  printf("PROCESS DONE\n");
  clear_queue();
  head = tail = NULL;
}

void quit()
{
  printf("QUIT\n");
  exit(0);
}

int main()
{
  unsigned int len;
  char buf[MAX_BUF_LEN];
  lsimp_msg_t *msg;

  while (1)
  {
    if (read_n(STDIN, (char *)&len, sizeof(len)) <= 0)
      return -1;
    if (len > MAX_BUF_LEN || len < sizeof(int))
      return -1;
    if (read_n(STDIN, (char *)&buf, len) <= 0)
      return -1;

    switch (*(int *)buf)
    {
      case OP_QUEUE:
        msg = parse_msg(buf + sizeof(int), len - sizeof(int));
        if (msg != NULL)
          queue_msg(msg);
        else
          printf("FAILED TO QUEUE\n");
        break;
      case OP_PROCESS:
        process();
        break;
      case OP_QUIT:
        quit();
        break;
      default:
        return -1;
    }
  }

  return 0;
}
