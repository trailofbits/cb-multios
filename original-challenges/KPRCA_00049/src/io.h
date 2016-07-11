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

#ifndef __IO_H
#define __IO_H

#define CLIENT_TO_SERVER_IN 3
#define CLIENT_TO_SERVER_OUT 4
#define SERVER_TO_CLIENT_IN 5
#define SERVER_TO_CLIENT_OUT 6

#define EOT 0x04
#define ETB 0x17

int send_n_bytes(int fd, size_t n, char* buf);
int read_n_bytes(int fd, size_t n, char* buf);
int read_until(int fd, size_t n, char terminator, char* buf);
int transmit_string(int fd, char* buf);

#ifdef DEBUG
  #define dbg(s, ...) fdprintf(STDERR, "DEBUG %s:%d:\t" s "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
  #define dbg(s, ...)
#endif

#define err(s, ...) \
({ \
  fdprintf(STDERR, "ERROR %s:%d:\t" s "\n", __FILE__, __LINE__, ##__VA_ARGS__); \
  exit(1); \
})

#define check_alloc(p) \
({ \
  if (p == NULL) err("bad alloc"); \
})

#endif
