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

#include <stdlib.h>
#include <string.h>

#include "read.h"

#define MAX_EXPRESSION_LENGTH (32768)

int repl(char *expr);

int main(void)
{
  printf("Welcome to the SLUR REPL. Type an expression to evaluate it.\n");
  char *buf = malloc(MAX_EXPRESSION_LENGTH + 1);

  if (buf == NULL)
    exit(1);

  for (;;) {
    memset(buf, '\0', MAX_EXPRESSION_LENGTH + 1);

    printf("> ");
    if (read_balanced_expression(STDIN, buf, MAX_EXPRESSION_LENGTH) != 0) {
      printf("Expression too long or unbalanced, try again.\n");
      continue;
    }

    // Maybe unbounded print here on hard to acheive error.
    if (repl(buf) != 0)
      printf("Error evaluating expression.\n");

    return 0;
  }
}
