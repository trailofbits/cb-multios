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
#include "error.h"

int readline(int fd, char *buf, size_t max, size_t *nrx)
{
#define READ_SIZE 1024
  char tmp[READ_SIZE + 1];
  size_t n;

  *nrx = 0;
  while (*nrx < max) {
    int ret = receive(fd, tmp, READ_SIZE, &n);

    if (ret < 0) {
      return -1;
    } else if (ret == 0 && n == (size_t)NULL) {
      break;
    } else if (ret == 0 && n != (size_t)NULL) {
      char *nl = strchr(tmp, '\n');

      // just newline, i.e. input = "\n"
      if (*nrx == 0 && nl == tmp)
        return -1;

      // found newline
      if (nl)
        n = nl - tmp;

      // exceeded bounds, truncate
      if (*nrx + n > max)
        n = max - *nrx;

      *nrx += n;
      memcpy(buf, tmp, n);
      buf += n;
      memset(tmp, '\0', READ_SIZE + 1);

      if (nl)
        break;
    }
  }

  return 0;
}
