#include "mylibc.h"
#include "defs.h"


#define IN 6
#define OUT 6
#define MAX_LINKS 10

uint8_t gBuf[PAGE_SIZE];
char gOutBuf[PAGE_SIZE];

typedef struct _Page
{
  char* name;
  char* data;
  size_t len;
  struct _Page* links[MAX_LINKS];
} Page;

Page gPages[MAX_LINKS];

#include "pages.data"

char gPageNotFoundError[] = "PAGE NOT FOUND\n";

size_t findPage(const char* str)
{
  for (size_t i = 0; i < MAX_LINKS; i++)
  {
    if (gPages[i].len == 0)
    {
      break;
    }
    else if (strcmp(gPages[i].name, str) == 0)
    {
      return (i);
    }
  }
  return (MAX_LINKS + 1);
}

int main(void)
{
  ProtoMsg msg;
  msg.type = -1;
  msg.msgLen = 0;
  size_t i = 0;

  init_pages();

  do 
  {
    recvMsg(IN, &msg, sizeof(msg));

    switch (msg.type)
    {
      case (PROTO_GET):
      {
        if (msg.msgLen == 0)
        {
          i = 0;
        }
        else
        {
          //this could overflow if msgLen is > PAGE_SIZE
          // this is counting on the router to make sure it doesn't happen . . .
          recvMsg(IN, gBuf, msg.msgLen);
          gBuf[msg.msgLen] = '\0';
          i = findPage((char*)gBuf);  
        }

        msg.type = PROTO_GET_ACK;

        if (i >= MAX_LINKS)
        {
#ifdef PATCHED
          msg.msgLen = snprintf(gOutBuf, PAGE_SIZE, "#s : #s", (char*)gBuf, gPageNotFoundError);
#else
          msg.msgLen = snprintf(gOutBuf, PAGE_SIZE, (char*)gBuf);
          msg.msgLen += snprintf(gOutBuf + msg.msgLen, PAGE_SIZE - msg.msgLen, " : #s", gPageNotFoundError);
#endif 
          sendMsg(OUT, &msg, sizeof(msg));
          sendMsg(OUT, gOutBuf, msg.msgLen);
        }
        else
        {
          msg.msgLen = gPages[i].len;
          sendMsg(OUT, &msg, sizeof(msg));
          sendMsg(OUT, gPages[i].data, msg.msgLen);
        }

        break;
      }
      case (PROTO_BYE):
      {
        return (0);
      }
      default:
      {
        msg.type = PROTO_ERROR;
        msg.msgLen = 0;
        break;
      }
    }
  } while (1);

  return (-1);
}
