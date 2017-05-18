#include "cgc_libc.h"

void cgc_transmit_all(int fd, const void* buf, cgc_size_t len)
{
  cgc_size_t rx_bytes = 0;
  cgc_size_t total = 0;
  int ret = 0;
  
  if (buf == NULL)
  {
    cgc__terminate(-1);
  }

  do 
  {
    ret = cgc_transmit(fd, buf + total, len - total, &rx_bytes);
    if (ret != 0)
    {
      cgc__terminate(-2);
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
  cgc_size_t off;
  cgc_size_t numAvail;
} RecvBuffer;

RecvBuffer cgc_gRecvBuffers[MAX_FDS] = {};

void cgc_receive_all(int fd, void* buf, cgc_size_t len)
{
  cgc_size_t rx_bytes = 0;
  cgc_size_t total = 0;
  int ret = 0;

  if ( (fd < 0) || (fd >= MAX_FDS) )
  {
    cgc__terminate(-1);
  }

  do
  {
    if (cgc_gRecvBuffers[fd].numAvail > 0)
    {
      for (rx_bytes = 0; cgc_gRecvBuffers[fd].numAvail > 0; rx_bytes++)
      {
        *((char*)(buf + total)) = cgc_gRecvBuffers[fd].buf[cgc_gRecvBuffers[fd].off];
        cgc_gRecvBuffers[fd].off++;
        cgc_gRecvBuffers[fd].numAvail--;
        total++;
        if (total >= len)
        {
          return;
        }
      }
      cgc_gRecvBuffers[fd].off = 0;
      cgc_gRecvBuffers[fd].numAvail = 0;
      continue; //go to the next iteration
    }
    ret = cgc_receive(fd, buf+total, len-total, &rx_bytes);
    if ( (ret != 0) || (rx_bytes == 0) )
    {
      cgc__terminate(ret);
    }
    total += rx_bytes;
  } while (total < len);

  if (buf == NULL)
  {
    cgc__terminate(-1);
  }
}

cgc_size_t cgc_receive_until(int fd, char* buf, cgc_size_t len, char delim)
{

  int ret = 0;
  cgc_size_t rx_bytes = 0;

  char c = 0;
  cgc_size_t count = 0;
  if (buf == NULL)
  {
    return (0);
  }

  if ( (fd < 0) || (fd >= MAX_FDS) )
  {
    cgc__terminate(-1);
  }

  do
  {
    if (cgc_gRecvBuffers[fd].numAvail <= 0)
    {
      ret = cgc_receive(fd, cgc_gRecvBuffers[fd].buf, RECV_BUF_SIZE, &rx_bytes);
      if ( (ret != 0) || (rx_bytes == 0) )
      {
        cgc__terminate(-ret);
      }
      cgc_gRecvBuffers[fd].off = 0;
      cgc_gRecvBuffers[fd].numAvail = rx_bytes;
      continue; //next iteration
    }

    c = cgc_gRecvBuffers[fd].buf[cgc_gRecvBuffers[fd].off];
    buf[count] = c;
    cgc_gRecvBuffers[fd].off++;
    cgc_gRecvBuffers[fd].numAvail--;
    count++;
  } while ( (count < (len - 1)) && (c != delim) );
  
  buf[count] = '\0'; //append NULL character

  return  (count);
}

int cgc_strcmp(const char* s1, const char* s2)
{
  cgc_size_t i = 0;

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

cgc_size_t cgc_strcpyUntil(char* dst, const char* src, char delim)
{
  cgc_size_t i = 0;
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
