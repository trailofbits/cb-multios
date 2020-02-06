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
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_ctype.h"

#include "cgc_protocol.h"

int cgc_read_n(int fd, char *buf, cgc_size_t len)
{
  cgc_size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    cgc_size_t rx;
    if (cgc_receive(fd, c, 1, &rx) != 0 || rx == 0)
      break;
    c++;
  }
  return c - buf;
}

int cgc_read_until(int fd, char *buf, cgc_size_t len, char delim)
{
  cgc_size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    cgc_size_t rx;
    if (cgc_receive(fd, c, 1, &rx) != 0 || rx == 0)
      return -1;
    if (*(c++) == delim)
      break;
  }
  *(c-1) = '\0';
  return c - buf;
}

int main(int cgc_argc, char *cgc_argv[])
{
  int length = 0;
  char buf[8192];

  while (cgc_read_n(STDIN, (char *)&length, sizeof(int)) > 0)
  {
    if (length >= sizeof(buf))
      return 0;
    if (cgc_read_n(STDIN, buf, length) > 0)
    {
      cgc_handle_command(buf, length);
    }
  }
  return 0;
}
