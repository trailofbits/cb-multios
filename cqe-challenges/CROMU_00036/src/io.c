/*

Author: Debbie Nuttall <debbie@cromulence.co>

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

#include <libcgc.h>
#include "stdlib.h"
#include "stdint.h"
#include "io.h"

// Transmit the entire contents of a buffer to STDOUT 
// Returns 0 for success, -1 for failure 
int SendAll(const void *buffer, size_t length) {
  size_t tx_count;
  size_t bytes_sent = 0;
  int return_value;

  while (bytes_sent < length) {
    return_value = transmit( STDOUT, buffer + bytes_sent, length - bytes_sent, &tx_count ); 
    if (return_value != 0 || tx_count == 0) {
      return -1;
    }
    bytes_sent += tx_count;
  }
  return 0;
}

// Transmit null bytes to STDOUT
// Returns 0 for success, -1 for failure 
int SendNull(size_t length) {
  char null_byte = '\0';
  size_t bytes_sent = 0;
  size_t tx_count;
  int return_value;

  while (bytes_sent < length) {
    return_value = transmit(STDOUT, &null_byte, 1, &tx_count);
    if (return_value != 0 || tx_count != 1) {
      return -1;
    }
    bytes_sent += 1;
  }
  return 0;
}

// Receive a fixed length buffer from STDIN
// Returns 0 for success, -1 for failure 
int ReceiveAll(void *buffer, size_t length) {
  size_t total_bytes_read = 0;
  size_t bytes_read;
  int return_value;
  
  while (total_bytes_read < length) {
    return_value = receive(STDIN, buffer + total_bytes_read, length - total_bytes_read, &bytes_read);
    if (return_value != 0 || bytes_read == 0) {
      return -1;
    }
    total_bytes_read += bytes_read;
  }
  return 0;
}


