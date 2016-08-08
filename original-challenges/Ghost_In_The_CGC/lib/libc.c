#include "libc.h"

void transmit_all(int fd, const void* buf, size_t len)
{
  size_t rx_bytes = 0;
  size_t total = 0;
  int ret = 0;
  
  if (buf == NULL)
  {
    _terminate(-1);
  }

  do 
  {
    ret = transmit(fd, buf + total, len - total, &rx_bytes);
    if (ret != 0)
    {
      _terminate(-2);
    }
    total += rx_bytes;
  } while (total < len);
}

//This receive does buffering so we don't receive 1 all the time
#define RECV_BUF_SIZE 128
#define MAX_FDS 15
typedef struct _RecvBuffer
{
  char buf[RECV_BUF_SIZE];
  size_t off;
  size_t numAvail;
} RecvBuffer;

RecvBuffer gRecvBuffers[MAX_FDS] = {};

void receive_all(int fd, void* buf, size_t len)
{
  size_t rx_bytes = 0;
  size_t total = 0;
  int ret = 0;

  if ( (fd < 0) || (fd >= MAX_FDS) )
  {
    _terminate(-1);
  }

  do
  {
    if (gRecvBuffers[fd].numAvail > 0)
    {
      for (rx_bytes = 0; gRecvBuffers[fd].numAvail > 0; rx_bytes++)
      {
        *((char*)(buf + total)) = gRecvBuffers[fd].buf[gRecvBuffers[fd].off];
        gRecvBuffers[fd].off++;
        gRecvBuffers[fd].numAvail--;
        total++;
        if (total >= len)
        {
          return;
        }
      }
      gRecvBuffers[fd].off = 0;
      gRecvBuffers[fd].numAvail = 0;
      continue; //go to the next iteration
    }
    ret = receive(fd, buf+total, len-total, &rx_bytes);
    if ( (ret != 0) || (rx_bytes == 0) )
    {
      _terminate(ret);
    }
    total += rx_bytes;
  } while (total < len);

  if (buf == NULL)
  {
    _terminate(-1);
  }
}

size_t receive_until(int fd, char* buf, size_t len, char delim)
{

  int ret = 0;
  size_t rx_bytes = 0;

  char c = 0;
  size_t count = 0;
  if (buf == NULL)
  {
    return (0);
  }

  if ( (fd < 0) || (fd >= MAX_FDS) )
  {
    _terminate(-1);
  }

  do
  {
    if (gRecvBuffers[fd].numAvail <= 0)
    {
      ret = receive(fd, gRecvBuffers[fd].buf, RECV_BUF_SIZE, &rx_bytes);
      if ( (ret != 0) || (rx_bytes == 0) )
      {
        _terminate(-ret);
      }
      gRecvBuffers[fd].off = 0;
      gRecvBuffers[fd].numAvail = rx_bytes;
      continue; //next iteration
    }

    c = gRecvBuffers[fd].buf[gRecvBuffers[fd].off];
    buf[count] = c;
    gRecvBuffers[fd].off++;
    gRecvBuffers[fd].numAvail--;
    count++;
  } while ( (count < (len - 1)) && (c != delim) );
  
  buf[count] = '\0'; //append NULL character

  return  (count);
}

int strcmp(const char* s1, const char* s2)
{
  size_t i = 0;

  if (s1 == NULL)
  {
    if (s2 == NULL)
    {
      return (0);
    }
    else 
    {
      return (-1);
    }
  }
  if (s2 == NULL)
  {
    return (1);
  }
  
  while (1)
  {
    if (s1[i] == '\0')
    {
      if (s2[i] != '\0')
      {
        return (-1);
      }
      else 
      {
        return (0);
      }
    }

    if (s2[i] == '\0')
    {
      if (s1[i] != '\0')
      {
        return (1);
      }
      //else - no else since its covered above
    }
  
    if (s1[i] < s2[i])
    {
      return (-1);
    }
    if (s1[i] > s2[i])
    {
      return (1);
    }
    i++;   
  }
  //should never be here
  return (-2);
}

size_t strcpyUntil(char* dst, const char* src, char delim)
{
  size_t i = 0;
  if ( (dst == NULL) || (src == NULL) )
  {
    return (0);
  }

  for (i = 0; (src[i] != '\0') && (src[i] != delim); i++)
  {
    dst[i] = src[i];
  }
  dst[i] = '\0';
  return (i);
}
