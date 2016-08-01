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
#ifndef __LIST_H_
#define __LIST_H_

#include <stdlib.h>

#define DEF_LIST(name, data_type)                               \
  typedef struct name##_list {                                  \
    data_type value;                                            \
    struct name##_list *prev;                                   \
    struct name##_list *next;                                   \
  } name##_list;                                                \

#define DEF_LIST_APPEND(name, data_type)                        \
  int name##_list_append(name##_list *list, data_type value) {  \
    if (list == NULL)                                           \
      return -1;                                                \
    name##_list *n = malloc(sizeof(name##_list));               \
    if (n == NULL)                                              \
      exit(1);                                                  \
    while (list->next != NULL)                                  \
      list = list->next;                                        \
    list->next = n;                                             \
    n->next = NULL;                                             \
    n->prev = list;                                             \
    n->value = value;                                           \
    return 0;                                                   \
  }

#endif /* __LIST_H_ */
