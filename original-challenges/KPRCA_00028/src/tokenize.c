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

#include <ctype.h>
#include <string.h>

#include "tokenize.h"

DEF_LIST_APPEND(tok, char *);

static int ok_for_sym(char c)
{
  if (c == '(' || c == ')' || isspace(c))
    return 0;
  else
    return 1;
}

tok_list *tokenize(char *expr)
{
  size_t len = strlen(expr);
  size_t i = 0;

  tok_list *l = malloc(sizeof(tok_list));
  if (l == NULL)
    return NULL;
  l->value = "START";

  while (i < len) {
    while (isspace(expr[i]))
      i++;

    if (expr[i] == '(' || expr[i] == ')') {
      char *v = malloc(2);
      if (v == NULL)
        return NULL;
      v[0] = expr[i];
      v[1] = '\0';
      if (tok_list_append(l, v) < 0)
        return NULL;
      i++;
      continue;
    }

    if (isalnum(expr[i])) {
      size_t start = i;

      while (isalnum(expr[i]) && i < len)
        i++;

      if (i < start)
        return NULL;

      char *v = malloc(i - start + 1);
      if (v == NULL)
        return NULL;
      strncpy(v, expr + start, i - start);
      if (tok_list_append(l, v) < 0)
        return NULL;
    } else{
      return NULL;
    }
  }

  return l->next;
}
