#include <libpov.h>

char* msgs[25] = {
"Hello?\n",
"What is wrong Bob?\n",
"Well what do you remember?\n",
"Can you describe the lights?\n",
"Do you see anything else?\n",
"A lot? Like how much a lot?\n",
"Why don't you go closer for a better look?\n",
"What do you see now?\n",
"How so?\n",
"What does it say?\n",
"Can you give me an example?\n",
"Ohh I see. Why don't you tell me about the lights.\n",
"Is there a pattern to them?\n",
"Well why don't you read some lights to me.\n",
"4347C003\n", //14
"Sure\n",
"4347C002\n", //16
"Sure\n",
"4347C001\n", //18
"Sure\n",
"4347C000\n", //20
"Nope\n",
"I don't know.\n",
"Sorry, but I am out of ideas\n",
"Sorry but this is it. Out of ideas.\n",
};

unsigned char parseByte(char* buf)
{
  int i = 0;
  unsigned char ret = 0;
  for (i = 0; i < 8; i++)
  {
    if (buf[i] == 'G')
    {
      ret = (ret << 1) | 0x01;
    }
    else
    {
      ret = (ret << 1) & 0xFE;
    }
  } 

  return (ret);
}

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
  uint32_t temp = 0;
  char buf[512];
  int i = 0;
  type2_vals t2v;
  type2_negotiate(&t2v);


  //Read in the original Hello, message
  receive_until(STDIN, buf, 512, '\n');

  for (i = 0; i < 25; i++)
  {
    transmit_all(STDOUT, msgs[i], strlen(msgs[i]));
    receive_until(STDIN, buf, 512, '\n');

    if ( (i == 14) || (i == 16) || (i == 18) || (i == 20) )
    {
      temp = (temp << 8) | parseByte(buf);
      transmit_all(STDERR, buf, strlen(buf));
      receive_until(STDIN, buf, 512, '\n');
    }

    if ( i == 20 )
    {
      type2_submit((unsigned char*)(&temp), 4);
      return (0);
    }
  }

  return (0);
}

