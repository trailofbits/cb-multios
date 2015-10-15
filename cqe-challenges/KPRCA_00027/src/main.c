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
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "protocol.h"

int read_n(int fd, char *buf, size_t len)
{
  size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    size_t rx;
    if (receive(fd, c, 1, &rx) != 0 || rx == 0)
      break;
    c++;
  }
  return c - buf;
}

int read_until(int fd, char *buf, size_t len, char delim)
{
  size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    size_t rx;
    if (receive(fd, c, 1, &rx) != 0 || rx == 0)
      return -1;
    if (*(c++) == delim)
      break;
  }
  *(c-1) = '\0';
  return c - buf;
}

int main()
{
  int length = 0;
  char buf[8192];

  while (read_n(STDIN, (char *)&length, sizeof(int)) > 0)
  {
    if (length >= sizeof(buf))
      return 0;
    if (read_n(STDIN, buf, length) > 0)
    {
      handle_command(buf, length);
    }
  }
  return 0;
}
