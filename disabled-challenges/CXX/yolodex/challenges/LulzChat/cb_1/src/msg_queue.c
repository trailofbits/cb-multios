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

#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_msg_queue.h"

int cgc_enq_msg(msg_queue *q, message_t *msg)
{
  if (msg)
  {
    if (*q == NULL)
    {
      *q = (node_t *) cgc_malloc(sizeof(node_t));
      if (*q == NULL)
        return -1;
      (*q)->msg = msg;
      (*q)->next = NULL;
    }
    else
    {
      node_t *n;
      node_t *tmp = (node_t *) cgc_malloc(sizeof(node_t));
      if (tmp == NULL)
        return -1;
      tmp->msg = msg;
      tmp->next = NULL;
      for (n = *q; n->next != NULL; n = n->next);
      n->next = tmp;
    }
  }
  return 0;
}

message_t* cgc_deq_msg(msg_queue *q)
{
  message_t *ret = NULL;

  if (*q)
  {
    if ((*q)->next == NULL)
    {
      ret = (*q)->msg;
      cgc_free(*q);
      *q = NULL;
    }
    else
    {
      node_t *tmp = *q;
      ret = tmp->msg;
      *q = tmp->next;
      cgc_free(tmp);
    }
  }
  return ret;
}

message_t* cgc_deq_msg_at(msg_queue *q, int idx)
{
  int i;
  message_t *ret = NULL;

  if (*q)
  {
    if ((*q)->next == NULL && idx == 1)
    {
      ret = (*q)->msg;
      cgc_free(*q);
      *q = NULL;
    }
    else
    {
      node_t *node, *prev = NULL;
      for (i = 0, node = *q; node != NULL; ++i, node = node->next)
      {
        if (i == idx)
        {
          if (prev == NULL)
            *q = node->next;
          else
            prev->next = node->next;
          ret = node->msg;
          cgc_free(node);
          break;
        }
        prev = node;
      }
    }
  }
  return ret;
}
