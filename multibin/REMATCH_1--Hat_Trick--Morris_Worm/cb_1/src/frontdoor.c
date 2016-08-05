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
#include <libcgc.h>
#include "stdio.h"
#include "string.h"
#include "libc.h"

#define FD_TO_LOOKUPD 3
#define FD_TO_MAIN 6
#define FD_TO_MAILSEND 9
#define FD_TO_ISH 7

void print(char *s) {
  send_all(s, strlen(s));
}

int main(void) {
  int i;
  char input[2048];
  char output[2048];
  int bytes_received = 0;
  // Receive service request
  do {
    printf("frontdoor:");
    memset(input, 0, sizeof(input));
    bytes_received = receive_until(input, sizeof(input), '\n');
    replace(input, ' ', '\0', 1);
    if (equals(input, "lookupd")) {
      char *s = input +  strlen("lookupd ");
      int s_len = bytes_received - strlen("lookupd ");
      if (s_len < 0) s_len = 0;
      s_len = force_newline(s, sizeof(input) - strlen("lookupd "), s_len);
      send_all_fd(FD_TO_LOOKUPD, s, s_len);
      while ((bytes_received = receive_until_fd(FD_TO_MAIN, output, sizeof(output),'\n')) > 0) {
        if (output[0] == '\0') {
          break;
        }
        force_newline(output, sizeof(output), bytes_received);
        print(output);
      }
    }
    else if (equals(input, "mailsend")) {
      char *s = input +  strlen("mailsend ");
      int s_len = bytes_received - strlen("mailsend ");
      if (s_len < 0) s_len = 0;
      s_len = force_newline(s, sizeof(input) - strlen("mailsend "), s_len);
      send_all_fd(FD_TO_MAILSEND, s, s_len);
      while ((bytes_received = receive_until_fd(FD_TO_MAIN, output, sizeof(output),'\n')) > 0) {
        if (output[0] == '\0') {
          break;
        }
        force_newline(output, sizeof(output), bytes_received);
        print(output);
      }
    }
    else if (equals(input, "ish")) {
      char *s = input +  strlen("ish ");
      int s_len = bytes_received - strlen("ish ");
      if (s_len < 0) s_len = 0;
      s_len = force_newline(s, sizeof(input) - strlen("ish "), s_len);
      send_all_fd(FD_TO_ISH, s, s_len);
      while ((bytes_received = receive_until_fd(FD_TO_MAIN, output, sizeof(output),'\n')) > 0) {
        if (output[0] == '\0') {
          break;
        }
        force_newline(output, sizeof(output), bytes_received);
        print(output);
      }
    }
    else if (equals(input, "quit")) {
      break;
    }
    else {
      print("Unknown Service Request\n");
      break;
    }
  } while (1);

  char end[] = "terminate\n";
  send_all_fd(FD_TO_LOOKUPD, end , sizeof(end));
  send_all_fd(FD_TO_MAILSEND, end , sizeof(end) );  
  send_all_fd(FD_TO_ISH, end , sizeof(end));
  struct timeval timeout;
  printf("Goodbye\n");
  return 0;
}
