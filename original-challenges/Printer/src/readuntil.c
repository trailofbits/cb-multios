#include "readuntil.h"

#define BUFSZ 128
static unsigned char rxbuf[BUFSZ];
static int rxcnt;
static int rxidx;

static int next_byte()
{
  size_t rxd;
  if (rxidx < rxcnt)
    return rxbuf[rxidx++];
  if (receive(STDIN, rxbuf, BUFSZ, &rxd) != 0 || rxd == 0)
    return -1;
  rxcnt = rxd;
  rxidx = 0;
  return rxbuf[rxidx++];
}

int read_until(int fd, char *buf, size_t len, char delim)
{
  size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    int ch = next_byte();
    if (ch == -1)
      return -1;
    *c = ch;
    if (*c == delim)
    {
      c++;
      break;
    }
    c++;
  }
  *(c-1) = '\0';
  return c - buf;
}

int read_n(int fd, char *buf, size_t len)
{
  size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    int ch = next_byte();
    if (ch == -1)
      return -1;
    *c = ch;
    c++;
  }
  return c - buf;
}
