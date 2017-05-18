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

#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_common.h"
#include "cgc_error.h"
#include "cgc_string.h"

string *cgc_new_string(char *d)
{
  string *s = cgc_calloc(1, sizeof(string));
  if (!s)
    error(EALLOC);

  s->d = cgc_calloc(1, DEFAULT_S_SZ);
  if (!s->d)
    error(EALLOC);
  s->cap = DEFAULT_S_SZ;

  if (d) {
#ifdef PATCHED
    cgc_size_t nz = (cgc_strlen(d) + 1) * 2;
    s->d = cgc_realloc(s->d, nz);
    if (!s->d)
      error(EALLOC);
    s->d[nz] = '\0';
    s->cap = nz;
#endif
    cgc_strcpy(s->d, d);
  }

  return s;
}

int cgc_set_string(string *s, char *d)
{
  if (!d || !s)
    return -1;

  cgc_memset(s->d, '\0', s->cap);

  if (cgc_strlen(d) + 1 > s->cap) {
    s->cap = (cgc_strlen(d) + cgc_strlen(s->d) + 1) * 2;
    s->d = cgc_realloc(s->d, s->cap);
    if (!s->d)
      error(EALLOC);
  }

  cgc_strncpy(s->d, d, s->cap);
  return 0;
}

int cgc_append_string(string *s, const char *d)
{
  if (!d || !s)
    return -1;

  if (cgc_strlen(d) + cgc_strlen(s->d) + 1 > s->cap) {
    s->cap = (cgc_strlen(d) + cgc_strlen(s->d) + 1) * 2;
    s->d = cgc_realloc(s->d, s->cap);
    if (!s->d)
      error(EALLOC);
  }

  cgc_strcat(s->d, d);
  return 0;
}

int cgc_contains_string(string *s, const char *sub)
{
  if (!s || !sub)
    return 0;

  const char *s1 = s->d;
  const char *s2 = sub;
  cgc_size_t sub_len = cgc_strlen(sub);
  cgc_size_t dom_len = cgc_strlen(s->d);

  if (dom_len < sub_len)
    return 0;

  if (dom_len == 0 || sub_len == 0)
    return (dom_len == sub_len) && (*s1 == *s2);

  if (dom_len == sub_len)
    return cgc_strcmp((char *)s1, s2) == 0;

  while (*s1) {
    s2 = sub;
    dom_len = cgc_strlen(s1);
    const char *s3 = s1;
    cgc_size_t matched = 0;

    while (matched < sub_len && matched < dom_len && *s2++ == *s3++)
      matched++;

    if (matched == sub_len)
      return 1;
    else
      s1++;
  }

  return 0;
}

void cgc_free_string(string *s)
{
  if (!s)
    return;

  if (s->d)
    cgc_free(s->d);
}
