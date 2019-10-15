/*

Author: Bryce Kerley <bk@cromulence.co>

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

#include "libcgc.h"
#include "cgc_types.h"
#include "cgc_monte.h"
#include "cgc_protocol.h"
#include "cgc_messages.h"
#include "cgc_handler.h"

void cgc_say_hello();

int main(int cgc_argc, char *cgc_argv[]) {
  cgc_types_check();

  cgc_monte_initialize();

  cgc_say_hello();

  cgc_run_loop();

  return -1; // should never reach
}

void cgc_say_hello() {
  protocol_frame hello_resp;
  hello_contents hello_resp_contents;

  hello_resp.id = HELLO_ID;
  hello_resp.length = HELLO_EXPECTED_LENGTH;
  hello_resp.value = (void*) &hello_resp_contents;

  hello_resp_contents.pos0 = cgc_monte_gen();

  cgc_protocol_send(&hello_resp);
}
