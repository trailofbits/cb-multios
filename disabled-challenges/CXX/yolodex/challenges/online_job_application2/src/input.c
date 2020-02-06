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
#include "cgc_input.h"

static int cgc_splitat(int fd, char *buf, cgc_size_t max, char delim)
{
  int ret;
  cgc_size_t rx, i = 0;
  while (i < max - 1) {
    ret = cgc_receive(STDIN, buf + i, 1, &rx);
    if (ret != 0 && rx == 0)
      return -1;

    if (*(buf + i) == delim)
        break;

    i++;
  }

  *(buf + i) = '\0';
  return i;
};

int cgc_read_line(char *buf)
{
  int ret;
  while (1) {
    ret = cgc_splitat(STDIN, buf, LINE_SIZE, '\n');
    if (ret < 0)
      return -1;
    else
      return 0;
  }
}
