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
// Main switching service selects between lookupd, mailsend, ish
#include "libcgc.h"
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_libc.h"

#define FD_TO_LOOKUPD 3
#define FD_TO_MAIN 6
#define FD_TO_MAILSEND 9
#define FD_TO_ISH 7

void cgc_print(char *s) {
  cgc_send_all(s, cgc_strlen(s));
}

int main(int cgc_argc, char *cgc_argv[]) {
  int i;
  char input[2048];
  char output[2048];
  int bytes_received = 0;
  // Receive service request
  do {
    cgc_printf("frontdoor:");
    cgc_memset(input, 0, sizeof(input));
    bytes_received = cgc_receive_until(input, sizeof(input), '\n');
    cgc_replace(input, ' ', '\0', 1);
    if (cgc_equals(input, "lookupd")) {
      char *s = input +  cgc_strlen("lookupd ");
      int s_len = bytes_received - cgc_strlen("lookupd ");
      if (s_len < 0) s_len = 0;
      s_len = cgc_force_newline(s, sizeof(input) - cgc_strlen("lookupd "), s_len);
      cgc_send_all_fd(FD_TO_LOOKUPD, s, s_len);
      while ((bytes_received = cgc_receive_until_fd(FD_TO_MAIN, output, sizeof(output),'\n')) > 0) {
        if (output[0] == '\0') {
          break;
        }
        cgc_force_newline(output, sizeof(output), bytes_received);
        cgc_print(output);
      }
    }
    else if (cgc_equals(input, "mailsend")) {
      char *s = input +  cgc_strlen("mailsend ");
      int s_len = bytes_received - cgc_strlen("mailsend ");
      if (s_len < 0) s_len = 0;
      s_len = cgc_force_newline(s, sizeof(input) - cgc_strlen("mailsend "), s_len);
      cgc_send_all_fd(FD_TO_MAILSEND, s, s_len);
      while ((bytes_received = cgc_receive_until_fd(FD_TO_MAIN, output, sizeof(output),'\n')) > 0) {
        if (output[0] == '\0') {
          break;
        }
        cgc_force_newline(output, sizeof(output), bytes_received);
        cgc_print(output);
      }
    }
    else if (cgc_equals(input, "ish")) {
      char *s = input +  cgc_strlen("ish ");
      int s_len = bytes_received - cgc_strlen("ish ");
      if (s_len < 0) s_len = 0;
      s_len = cgc_force_newline(s, sizeof(input) - cgc_strlen("ish "), s_len);
      cgc_send_all_fd(FD_TO_ISH, s, s_len);
      while ((bytes_received = cgc_receive_until_fd(FD_TO_MAIN, output, sizeof(output),'\n')) > 0) {
        if (output[0] == '\0') {
          break;
        }
        cgc_force_newline(output, sizeof(output), bytes_received);
        cgc_print(output);
      }
    }
    else if (cgc_equals(input, "quit")) {
      break;
    }
    else {
      cgc_print("Unknown Service Request\n");
      break;
    }
  } while (1);

  char end[] = "terminate\n";
  cgc_send_all_fd(FD_TO_LOOKUPD, end , sizeof(end));
  cgc_send_all_fd(FD_TO_MAILSEND, end , sizeof(end) );  
  cgc_send_all_fd(FD_TO_ISH, end , sizeof(end));
  struct cgc_timeval timeout;
  cgc_printf("Goodbye\n");
  return 0;
}
