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
#include "libcgc.h"
#include "cgc_string.h"
#include "cgc_libc.h"


int _pw_stayopen;

int cgc_receive_all(char *buf, int length) {
  return cgc_receive_all_fd(STDIN, buf, length);
}


int cgc_receive_all_fd(int fd, char *buf, int length) {

  int total_received = 0;
  int ret;
  cgc_size_t bytes_received;
  while (total_received < length) {
    ret = cgc_receive(fd, buf + total_received, length - total_received, &bytes_received);
    if (ret !=0 ) {
      // error
      return -1;
    }
    if (bytes_received == 0) {
      break;
    }
    total_received += bytes_received;
  }

  return total_received;
}

int cgc_receive_until(char *buf, int length, char delim) {
  return cgc_receive_until_fd(STDIN, buf, length, delim);
}

// Receives bytes from the given fd until delim is found. 
// Output buf will always be null terminated. Output buf does not contain delim.
// Returns bytes received not including delim or null 
int cgc_receive_str_until_fd(int fd, char *buf, int length, char delim) {
  int total_received = 0;
  int ret;
  cgc_size_t bytes_received;
  char c;
  buf[0] = '\0';
  while (1) {
    ret = cgc_receive(fd, &c, 1, &bytes_received);
    if (ret !=0 ) {
      // error
      return -1;
    }
    if (bytes_received == 0) {
      break;
    }
    if (c == delim) {
      goto DONE;
    }
    if (total_received < length - 1) {
      *(buf + total_received++) = c;      
    }
  }

DONE:
  *(buf + total_received) = '\0';
  return total_received;
}

// Receives bytes from the given fd until delim is found. 
// Output buf will not always be null terminated. Output buf does not contain delim. 
// Returns bytes received not including delim or null
int cgc_receive_until_fd(int fd, char *buf, int length, char delim) {
  int total_received = 0;
  int ret;
  cgc_size_t bytes_received;
  char c;
  buf[0] = '\0';
  while (1) {
    ret = cgc_receive(fd, &c, 1, &bytes_received);
    if (ret !=0 ) {
      // error
      return -1;
    }
    if (bytes_received == 0) {
      break;
    }
    if (c == delim) {
      goto DONE;
    }
    if (total_received < length) {
      *(buf + total_received++) = c;      
    }
  }

DONE:
  if (total_received < length) {
    *(buf + total_received) = '\0';
  } 
  return total_received;
}

int cgc_send_all(char *buf, int length) {
  return cgc_send_all_fd(STDOUT, buf, length);
}

int cgc_send_all_fd(int fd, char *buf, int length) {
  int total_sent = 0;
  int ret;
  cgc_size_t bytes_sent;
  while(total_sent < length) {
    ret = cgc_transmit(fd, buf + total_sent, length - total_sent, &bytes_sent);
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


// Return 1 if string 'd' equals string 's', otherwise return 0
int cgc_equals(char *d, char *s) {
  while (*d == *s) {
    if (*d == '\0')
      return 1;
    s++;
    d++;
  }
  return 0;
}
  
// Replace 'find' char with 'replace' char in the string 's' up to 'num' instances. 
// If 'num' is 0, replace all instances. 
// Returns number of instances that were replaced. 
int cgc_replace(char *s, char find, char replace, int num) {
  int count = 0;
  while (*s != '\0') {
    if ((num != 0) && (count >= num)) {
      break;
    }
    if (*s == find) {
      *s = replace;
      count++;
    }
    s++;
  }
  return count;
}



// Adds a newline character to the end of s. 
// size informs the function of the total size of the s buffer
// length informs the function of the length of useful string within the buffer
// The newline will be added at the end of the useful string or, if the string is max length, in the last position of the buffer
// Returns the new length of the useful string including the newline character
// Buffer will only be null terminated if size permits
int cgc_force_newline(char *s, int size, int bytes) {
  if (bytes == size) {
      s[bytes - 1] = '\n';
    } else {
      if (s[bytes-1] != '\n') {
        s[bytes++] = '\n';
      }
      if (bytes < size) {
        s[bytes] = '\0';
      }
    }
  return bytes;
}


int cgc_getopt(int argc, char **argv, char *optstring, int *opt_index) {
  
  int option = -1;
  if (*opt_index >= argc || !argv[*opt_index]) {
    goto DONE;
  }
  for (int i = 0; i < cgc_strlen(optstring); i++) {
    if (*argv[*opt_index] == optstring[i]) {
      option = optstring[i];
      (*opt_index)++;
      goto DONE;
    }
  }
  (*opt_index)++;
  option = 0;
    
DONE:
  return option;
}



void cgc_bcopy(char *s, char *d, cgc_size_t size) {
  while (size > 0) {
    *d = *s;
    d++;s++;size--;
  }
}


void cgc_exit(int e) {
  cgc__terminate(e);
}
