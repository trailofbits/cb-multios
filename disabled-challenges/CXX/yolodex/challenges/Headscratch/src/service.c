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
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_string.h"

#define MAX_PROGRAM_SIZE (8 * 1024)
#define MAX_DATA_SIZE (32 * 1024)

#ifdef DEBUG
  #define dbg(M, ...) fprintf(cgc_stderr, "DEBUG: " M "\n", ##__VA_ARGS__);
#else
  #define dbg(M, ...)
#endif

#define CHUNK_SIZE 64

static unsigned char txbuf[CHUNK_SIZE];
static int txcnt;
static unsigned char rxbuf[CHUNK_SIZE];
static int rxcnt;
static int rxidx;

void cgc_send_flush() {
  cgc_size_t sent = 0;
  while (txcnt != sent)
  {
      cgc_size_t tx;
      if (cgc_transmit(STDOUT, txbuf + sent, txcnt - sent, &tx) != 0)
          break;
      sent += tx;
  }
  txcnt = 0;
}

int cgc_get_byte() {
  if (rxcnt == rxidx)
  {
      cgc_size_t rxd;
      if (cgc_receive(STDIN, rxbuf, CHUNK_SIZE, &rxd) != 0 || rxd == 0)
          return -1;
      rxcnt = rxd;
      rxidx = 0;
  }
  return (int)rxbuf[rxidx++];
}

int cgc_send_n_bytes(int fd, char* buf, cgc_size_t n) {
  cgc_size_t nsent = 0;
  cgc_size_t tx_amt = 0;
  while (n > 0)
  {
    if (cgc_transmit(fd, buf + nsent, n - nsent < CHUNK_SIZE ? n - nsent : CHUNK_SIZE, &tx_amt) != 0)
      return -1;

    n -= tx_amt;
  }

  return 0;
}

cgc_size_t cgc_read_until_or_timeout(int fd, char* buf, cgc_size_t max, char term, struct cgc_timeval t, int* err) {
  cgc_size_t nread = 0;
  cgc_size_t rx_amt = 0;
  *err = 0;

  int rdy;
  cgc_fd_set fs;

  while (nread < max)
  {
    FD_SET(STDIN, &fs);
    if (cgc_fdwait(STDIN + 1, &fs, NULL, &t, &rdy) != 0)
    {
      *err = 1;
      return 0;
    }

    if (rdy != 1)
      break;

    do
    {
        int chr = cgc_get_byte();
        if (chr == -1)
            return 0;
        buf[nread] = chr;
        buf[nread+1] = 0;
        rx_amt = 1;

        if (cgc_strchr(buf + nread, term) != NULL)
        {
          cgc_size_t until_term = cgc_strchr(buf + nread, term) - (buf + nread);
          nread += until_term;
          cgc_send_n_bytes(STDOUT, buf + nread + 1, rx_amt - until_term - 1);
          return nread;
        }
        else
        {
          nread += rx_amt;
        }
    } while (rxcnt != rxidx && nread < max);

  }

  return nread;
}

cgc_size_t cgc_strip_program(char* buf, cgc_size_t max)
{
  char* cpy = cgc_calloc(sizeof(char), max);
  cgc_memcpy(cpy, buf, max);
  cgc_memset(buf, '\0', max);

  char* p = buf;
  cgc_size_t i;

  for (i = 0; i < max; i++)
    if (
        cpy[i] == '<' ||
        cpy[i] == '>' ||
        cpy[i] == '+' ||
        cpy[i] == '-' ||
        cpy[i] == '.' ||
        cpy[i] == ',' ||
        cpy[i] == '[' ||
        cpy[i] == ']'
    )
      *p++ = cpy[i];

  return p - buf;
}

int cgc_execute_program(char* program, cgc_size_t max) {
  char data[MAX_DATA_SIZE];
  char *ip = program;
  char *dp = data;
  int depth = 0;
  int direction = 1;

  cgc_memset(data, '\0', MAX_DATA_SIZE);

  while (ip >= program && ip < program + max)
  {
    if (depth > 0)
    {
      if (*ip == ']')
        depth -= direction;
      else if (*ip == '[')
        depth += direction;

      if (depth < 0)
      {
        dbg("depth went negative");
        return -1;
      }
      else if (depth == 0)
        direction = 1;
    }

    else if (*ip == '>')
    {
      dbg("inc dp");
#ifdef PATCHED_1
      if (dp >= data + MAX_DATA_SIZE - 1 || dp < data)
#else
      if (dp < data)
#endif
      {
        dbg("dp out of bounds");
        return -1;
      }
      else
        dp++;
    }

    else if (*ip == '<')
    {
      dbg("dec dp");
      if (dp >= data + MAX_DATA_SIZE - 1 || dp < data)
      {
        dbg("dp out of bounds");
        return -1;
      }
      else
        dp--;
    }

    else if (*ip == '+')
    {
      dbg("inc val");
      (*dp)++;
    }

    else if (*ip == '-')
    {
      dbg("dec val");
      (*dp)--;
    }

    else if (*ip == '.')
    {
      dbg("sending 1 in interp");
      txbuf[txcnt++] = *dp;
      if (txcnt == CHUNK_SIZE)
      {
          cgc_send_flush();
      }
    }

    else if (*ip == ',')
    {
      dbg("reading 1 in interp");
      cgc_send_flush();
      int ch = cgc_get_byte();
      if (ch == -1)
      {
          cgc_fprintf(cgc_stderr, "Read failed: %d\n", dp - data);
          return -1;
      }
      *dp = ch;
      if (!*dp)
      {
        dbg("null byte read");
        break;
      }
    }

    else if (*ip == '[')
    {
      dbg("open");
      if (*dp == 0)
      {
        depth++;
        direction = 1;
      }
    }
    else if (*ip == ']')
    {
      dbg("close");
      if (*dp != 0)
      {
        depth++;
        direction = -1;
      }
    }

    else
    {
      dbg("tried to execute unknown opcode");
      return -1;
    }

    ip += direction;
  }

  dbg("returning normally");
  return 0;
}

int main(int cgc_argc, char *cgc_argv[]) {
  unsigned int *secrets = (unsigned int *)0x4347C004;
  char buf[MAX_PROGRAM_SIZE];
  int err;

  cgc_printf(
      "Welcome to the headscratch interpreter.\n"
      "Enter your program to have it executed!\n"
      "%u\n", secrets[0] ^ secrets[1]);

  cgc_read_until_or_timeout(STDIN, buf, MAX_PROGRAM_SIZE, '\n', (struct cgc_timeval){.tv_sec = 3, .tv_usec = 0}, &err);
  if (err)
    return -1;

  cgc_size_t actual_size = cgc_strip_program(buf, MAX_PROGRAM_SIZE);
  if (actual_size < 1)
    return -1;

  if (cgc_execute_program(buf, actual_size) < 0)
    return -1;

  cgc_send_flush();
  txbuf[txcnt++] = '\x43';
  txbuf[txcnt++] = '\x47';
  txbuf[txcnt++] = '\xc0';
  txbuf[txcnt++] = '\x00';
  cgc_send_flush();
  return 0;
}
