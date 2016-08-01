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

#include <libcgc.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "error.h"
#include "string.h"

string *new_string(char *d)
{
  string *s = calloc(1, sizeof(string));
  if (!s)
    error(EALLOC);

  s->d = calloc(1, DEFAULT_S_SZ);
  if (!s->d)
    error(EALLOC);
  s->cap = DEFAULT_S_SZ;

  if (d) {
#ifdef PATCHED
    size_t nz = (strlen(d) + 1) * 2;
    s->d = realloc(s->d, nz);
    if (!s->d)
      error(EALLOC);
    s->d[nz] = '\0';
    s->cap = nz;
#endif
    strcpy(s->d, d);
  }

  return s;
}

int set_string(string *s, char *d)
{
  if (!d || !s)
    return -1;

  memset(s->d, '\0', s->cap);

  if (strlen(d) + 1 > s->cap) {
    s->cap = (strlen(d) + strlen(s->d) + 1) * 2;
    s->d = realloc(s->d, s->cap);
    if (!s->d)
      error(EALLOC);
  }

  strncpy(s->d, d, s->cap);
  return 0;
}

int append_string(string *s, const char *d)
{
  if (!d || !s)
    return -1;

  if (strlen(d) + strlen(s->d) + 1 > s->cap) {
    s->cap = (strlen(d) + strlen(s->d) + 1) * 2;
    s->d = realloc(s->d, s->cap);
    if (!s->d)
      error(EALLOC);
  }

  strcat(s->d, d);
  return 0;
}

int contains_string(string *s, const char *sub)
{
  if (!s || !sub)
    return 0;

  const char *s1 = s->d;
  const char *s2 = sub;
  size_t sub_len = strlen(sub);
  size_t dom_len = strlen(s->d);

  if (dom_len < sub_len)
    return 0;

  if (dom_len == 0 || sub_len == 0)
    return (dom_len == sub_len) && (*s1 == *s2);

  if (dom_len == sub_len)
    return strcmp((char *)s1, s2) == 0;

  while (*s1) {
    s2 = sub;
    dom_len = strlen(s1);
    const char *s3 = s1;
    size_t matched = 0;

    while (matched < sub_len && matched < dom_len && *s2++ == *s3++)
      matched++;

    if (matched == sub_len)
      return 1;
    else
      s1++;
  }

  return 0;
}

void free_string(string *s)
{
  if (!s)
    return;

  if (s->d)
    free(s->d);
}
