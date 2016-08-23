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
#include <string.h>
#include "user.h"

int add_user(user_list_t *list, user_t *user)
{
  if (user)
  {
    user_t *u;
    int auth_code;
    random(&auth_code, sizeof(auth_code), NULL);

    if (*list == NULL)
    {
      user->user_id = 1;
      *list = user;
    }
    else
    {
      for (u = *list; u->next != NULL; u = u->next);
      if (u->user_id == MAX_NUM_USERS)
        return -1;
      user->user_id = u->user_id + 1;
      u->next = user;
    }
    user->auth_code = auth_code;
    user->next = NULL;
    return 0;
  }
  return -1;
}

user_t* find_user(user_list_t list, char *username)
{
  user_t *ret = NULL;
  if (list && username)
  {
    for (user_t *u = list; u != NULL; u = u->next)
    {
      if (strcmp(username, u->username) == 0)
      {
        ret = u;
        break;
      }
    }
  }
  return ret;
}

user_t* find_user_by_id(user_list_t list, unsigned short user_id)
{
  user_t *ret = NULL;
  if (list)
  {
    for (user_t *u = list; u != NULL; u = u->next)
    {
      if (user_id == u->user_id)
      {
        ret = u;
        break;
      }
    }
  }
  return ret;
}

user_t* get_user(user_list_t list, unsigned short user_id, unsigned int auth_code)
{
  user_t *ret = NULL;
  if (list)
  {
    for (user_t *u = list; u != NULL; u = u->next)
    {
      if (user_id == u->user_id && auth_code == u->auth_code)
      {
        ret = u;
        break;
      }
    }
  }
  return ret;
}
