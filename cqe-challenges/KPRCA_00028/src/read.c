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
#include <stdlib.h>

int read_balanced_expression(int fd, char *buf, size_t max)
{
  size_t rx = 0;
  size_t depth = 0;
  char nl;

  while (receive(fd, buf, 1, &rx) == 0) {
    if (rx ==  0)
      break;

    // Ensure first character is a open paren
    if (depth == 0 && *buf != '(')
        return -1;

    if (*buf == '(') {
      if (depth == SIZE_MAX)
        return -1;
      else
        depth += 1;
    } else if (*buf == ')') {
      if (depth == 0)
        return -1;
      else
        depth -= 1;
    }

    max -= rx;
    if (max == 0)
      break;
    buf += rx;

    if (depth == 0)
      break;
  }

  // chomp
  while (receive(fd, &nl, 1, &rx) == 0) {
    if (rx == 0 || nl == '\n')
      break;
    if (!isspace(nl))
      return -1;
  }

  *buf = '\0';
  return depth;
}
