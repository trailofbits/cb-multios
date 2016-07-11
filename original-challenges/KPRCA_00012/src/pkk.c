/*
 * Author: Brian Pak <brian.pak@kapricasecurity.com>
 * Author: Andrew Wesie <andrew.wesie@kapricasecurity.com>
 *
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

#include <stdlib.h>
#include <string.h>

#include "pkk.h"

char* skip_whitespace(char *p, int max_len)
{
  while (*p == '\n' || *p == '\r' || *p == ' ' || *p == '\t')
  {
    if (max_len == 0)
      break;
    p++;
    max_len--;
  }
  return p;
}

pkk_t* parse_pkk(char *data, unsigned int len)
{
  unsigned int sofar = 0;
  char *c = data;
  pkk_t *pkk = NULL;

  if (data == NULL)
    goto fail;

  pkk = (pkk_t *) malloc(sizeof(pkk_t));
  if (pkk == NULL)
    goto fail;

  /* Header */
  if (memcmp(c, "PK\n", 3) != 0)
    goto fail;
  c += 3;
  c = skip_whitespace(c, len - 3);
  if (data + len <= c)
    goto fail;

  /* Read comments */
  while (1)
  {
    if (*c == '#')
      while (*c != '\n' && c < data + len) c++;
    else
      break;
  }
  if (data + len <= c)
    goto fail;

  /* Width and Height */
  int width, height;
  height = strtoul(c, &c, 10);
  width = strtoul(c, &c, 10);

  c = skip_whitespace(c, data + len - c);

  /* Max color value */
  if (strtoul(c, &c, 10) != 255)
    goto fail;

  /* Skip one byte (whitespace) */
  c++;

  /* Copy pixel data */
  pkk = (pkk_t *) malloc(sizeof(pkk_t));
  pkk->width = width;
  pkk->height = height;
  if (sizeof(pixel_t) > (0xFFFFFFFF / width) / height)
    goto fail;
#ifdef PATCHED
  if ((c - data) + sizeof(pixel_t) * width * height > len)
#else
  if (c + sizeof(pixel_t) * width * height > data + len)
#endif
    goto fail;
  pkk->pixels = (pixel_t *) malloc(sizeof(pixel_t) * width * height);
  if (pkk->pixels == NULL)
    goto fail;
  memcpy(pkk->pixels, c, sizeof(pixel_t) * width * height);
  return pkk;

fail:
  free_pkk(pkk);
  return NULL;
}

char* output_pkk(pkk_t *pkk, int *out_len)
{
  char *cur;
  unsigned int len;
  len = sizeof(pixel_t) * pkk->width * pkk->height + 3 + 50 + 1 + 3 + 1;
  char *buffer = NULL;

  buffer = malloc(len);
  if (buffer == NULL)
    goto fail;
  memset(buffer, '\0', len);

  cur = buffer;
  strcpy(cur, "PK\n");

  cur += 3;
  int n = sprintf(cur, "%d %d\n255\n", pkk->height, pkk->width);
  if (n == -1)
    goto fail;
  cur += n;

  int i;
  for (i = 0; i < pkk->width * pkk->height; ++i)
  {
    *cur = pkk->pixels[i].r;
    *(cur+1) = pkk->pixels[i].g;
    *(cur+2) = pkk->pixels[i].b;
    cur += 3;
  }

  *out_len = cur - buffer;
  return buffer;

fail:
  if (buffer)
    free(buffer);
  *out_len = 0;
  return NULL;
}

void free_pkk(pkk_t *pkk)
{
  if (pkk)
  {
    if (pkk->pixels)
      free(pkk->pixels);
    free(pkk);
  }
}
