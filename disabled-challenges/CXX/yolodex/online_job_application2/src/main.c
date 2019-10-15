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

#include "cgc_stdint.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_form.h"
#include "cgc_input.h"

extern form_t cgc_af86;

int main(int cgc_argc, char *cgc_argv[])
{
  char line_buf[LINE_SIZE];
  int with_title = 1;
  int ret;
  int done = 0;

  cgc_af86.init();
  cgc_print_greeting(&cgc_af86);
  while (1) {
    cgc_print_prompt(&cgc_af86, with_title, done);
    with_title = 0;
    cgc_memset(line_buf, 0, LINE_SIZE);
    if (cgc_read_line(line_buf) < 0)
      break;

    ret = cgc_handle_line(&cgc_af86, line_buf);
    if (ret < 0)
      break;
    else if (ret == 1)
      with_title = 1;
    else if (ret == 2)
      done = 1;
    else if (ret == 3) {
      with_title = 1;
      done = 0;
    }
  }
  return 0;
}
