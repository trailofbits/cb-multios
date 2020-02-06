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

#include "cgc_ctype.h"
#include "cgc_string.h"

#include "cgc_tokenize.h"

DEF_LIST_APPEND(tok, char *);

static int ok_for_sym(char c)
{
  if (c == '(' || c == ')' || cgc_isspace(c))
    return 0;
  else
    return 1;
}

tok_list *cgc_tokenize(char *expr)
{
  cgc_size_t len = cgc_strlen(expr);
  cgc_size_t i = 0;

  tok_list *l = cgc_malloc(sizeof(tok_list));
  if (l == NULL)
    return NULL;
  l->value = "START";

  while (i < len) {
    while (cgc_isspace(expr[i]))
      i++;

    if (expr[i] == '(' || expr[i] == ')') {
      char *v = cgc_malloc(2);
      if (v == NULL)
        return NULL;
      v[0] = expr[i];
      v[1] = '\0';
      if (tok_list_append(l, v) < 0)
        return NULL;
      i++;
      continue;
    }

    if (cgc_isalnum(expr[i])) {
      cgc_size_t start = i;

      while (cgc_isalnum(expr[i]) && i < len)
        i++;

      if (i < start)
        return NULL;

      char *v = cgc_malloc(i - start + 1);
      if (v == NULL)
        return NULL;
      cgc_strncpy(v, expr + start, i - start);
      if (tok_list_append(l, v) < 0)
        return NULL;
    } else{
      return NULL;
    }
  }

  return l->next;
}
