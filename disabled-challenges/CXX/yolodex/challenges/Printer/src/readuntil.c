#include "cgc_readuntil.h"

#define BUFSZ 128
static unsigned char rxbuf[BUFSZ];
static int rxcnt;
static int rxidx;

static int cgc_next_byte()
{
  cgc_size_t rxd;
  if (rxidx < rxcnt)
    return rxbuf[rxidx++];
  if (cgc_receive(STDIN, rxbuf, BUFSZ, &rxd) != 0 || rxd == 0)
    return -1;
  rxcnt = rxd;
  rxidx = 0;
  return rxbuf[rxidx++];
}

int cgc_read_until(int fd, char *buf, cgc_size_t len, char delim)
{
  cgc_size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    int ch = cgc_next_byte();
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

int cgc_read_n(int fd, char *buf, cgc_size_t len)
{
  cgc_size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    int ch = cgc_next_byte();
    if (ch == -1)
      return -1;
    *c = ch;
    c++;
  }
  return c - buf;
}
