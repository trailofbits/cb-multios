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
#include "error.h"

void _error(int x, char *file, int line)
{
  switch (x) {
  case EALLOC:
    fdprintf(STDERR, "%s:%d - allocation error\n", file, line);
    break;
  case ETREE:
    fdprintf(STDERR, "%s:%d - something broke with the tree\n", file, line);
    break;
  case ELIST:
    fdprintf(STDERR, "%s:%d - something broke with the list\n", file, line);
    break;
  case ECMD:
    fdprintf(STDERR, "%s:%d - something broke with commands\n", file, line);
    break;
  case ERAND:
    fdprintf(STDERR, "%s:%d - random failed, getting out of here.\n", file, line);
    break;
  default:
    fdprintf(STDERR, "%s:%d - unknown error\n", file, line);
  }

  exit(1);
}
