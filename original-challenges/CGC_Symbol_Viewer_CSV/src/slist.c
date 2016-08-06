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
#include "slist.h"

sl_node* sl_insert(sl_node *head, void *elem, cmp_fn cmp)
{
  sl_node *cur, *prev, *new;

  /* Check null */
  if (elem)
  {
    new = (sl_node *) malloc(sizeof(sl_node));
    if (new)
    {
      new->elem = elem;

      if (head == NULL)
      {
        /* New element should be the head */
        head = new;
        head->next = NULL;
      }
      else
      {
        /* Find the right place to insert */
        cur = head;
        prev = NULL;
        while (cur)
        {
          if (cmp(cur->elem, new->elem) > 0)
            break;
          prev = cur;
          cur = cur->next;
        }

        /* New element should be the tail */
        if (cur == NULL)
          prev->next = new;
        /* Else */
        else
        {
          /* New element belongs to the head */
          if (prev == NULL)
          {
            new->next = head;
            head = new;
          }
          /* New element should be in the middle */
          else
          {
            new->next = prev->next;
            prev->next = new;
          }
        }
      }
    }
  }
  return head;
}

void sl_destroy(sl_node *head, free_fn ffn)
{
  sl_node *cur, *tmp;

  /* Initialize node pointers */
  cur = tmp = head;

  /* Free each node and its element inside */
  while (cur)
  {
    tmp = cur->next;
    if (cur->elem)
      ffn(cur->elem);
    free(cur);
    cur = tmp;
  }
}
