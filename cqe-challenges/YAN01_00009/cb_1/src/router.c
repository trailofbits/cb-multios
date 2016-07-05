#include "mylibc.h"
#include "defs.h"

typedef struct _StrFDMap
{
  char server[STR_LEN];
  int in;
  int out;
} StrFDMap;

#define MAX_SERVERS 10

StrFDMap gServers[MAX_SERVERS] = {
  {"walkthrough", 3, 3}, 
  {"newsletter", 5, 5},
  {"", 0, 0} 
};

char gHello[] = "HELLO I AM ";
char gHelloReply1[] = "HELLO ";
char gHelloReply2[] = " YOUR UID IS ";
char gHelloReply3[] = " HOW CAN I HELP YOU";
char gGet1[] = " SAYS GET ";
char gGet2[] = " PLEASE";
char gBye[] = "GOODBYE";
char gTERM[] = "\n\t\n\t\n";

typedef enum _E_States
{
  INIT_STATE,
  CONNECTED_STATE,
  GOODBYE_STATE
} E_States;

int findFDs(const char* server, int* pIn, int* pOut)
{
  if ( (server == NULL) || (pIn == NULL) || (pOut == NULL) )
  {
    return (-1);
  }

  for (size_t i = 0; (i < MAX_SERVERS) && (gServers[i].server[0] != '\0'); i++)
  {
    if (strcmp(gServers[i].server, server) == 0)
    {
      *pIn = gServers[i].in;
      *pOut = gServers[i].out;
      return (0);
    }
  }
  return (-1);
}

void sendGoodbyes()
{
  ProtoMsg msg;
  msg.type = PROTO_BYE;
  msg.msgLen = 0;

  for (size_t i = 0; (i < MAX_SERVERS) && (gServers[i].server[0] != '\0'); i++)
  {
    sendMsg(gServers[i].out, &msg, sizeof(msg));
  }
}

uint8_t gBuf[PAGE_SIZE];

int doGet(const char* page, int in, int out)
{
  ProtoMsg msg;
  size_t temp = 0;
  
  if (page == NULL)
  {
    return (-1);
  }
  
  msg.type = PROTO_GET;

  msg.msgLen = strlen(page);

  sendMsg(out, &msg, sizeof(msg));

  sendMsg(out, page, msg.msgLen);

  recvMsg(in, &msg, sizeof(msg));
 
  if (msg.type != PROTO_GET_ACK)
  {
    return (-1);
  }

  while (temp < msg.msgLen)
  {
    if ((msg.msgLen - temp) > PAGE_SIZE)
    {
      recvMsg(in, gBuf, PAGE_SIZE);
      sendMsg(STDOUT, gBuf, PAGE_SIZE);
      temp += PAGE_SIZE;
    }
    else 
    {
      recvMsg(in, gBuf, msg.msgLen - temp);
      sendMsg(STDOUT, gBuf, msg.msgLen - temp);
      temp = msg.msgLen;
    }
  }

  sendMsg(STDOUT, gTERM, sizeof(gTERM) - 1);

  return (0);
}

int parseAndGetPage(char* buf, char** pStart, char** pEnd, const char* uidStr)
{
  char* start = NULL;
  char* end = NULL;
  
  if ( (buf == NULL) || (pStart == NULL) || (pEnd == NULL) || (uidStr == NULL) )
  {
    return (-1);
  }

  start = buf + strlen(uidStr);
  if (strstr(start, gGet1) != start)
  {
    return (-1);
  }

  start = start + sizeof(gGet1) - 1;
  end = strrstr(start, gGet2);
  if (end == NULL)
  {
    return (-1);
  }

  //reset the NULL character so start is the web-address
  *end = '\0';
  //reset the NULL character again so that start is the domain
  end = strchr(start, '/');
  if (end != NULL)
  {
    *end = '\0';
    end++; 
  }
  //end is now the page or NULL if no page is specified

  *pStart = start;
  *pEnd = end;

  int inFD = 0;
  int outFD = 0;
  if (findFDs(start, &inFD, &outFD) != 0)
  {
    printf("SERVER [#s] NOT FOUND\n", start);
    return (0);
  } 

  return (doGet(end, inFD, outFD));
}

int main(void)
{
  char* buf = NULL;
  char* name = NULL;
  char* start = NULL;
  char* end = NULL;
  char uidStr[24];
  uint32_t uid = 0;
  ssize_t sret = 0;
 
  E_States state = INIT_STATE;
  printf_setFlushOnNewline(1);

  if (allocate(PAGE_SIZE, 0, (void**)&buf) != 0)
  {
    return (-1);
  }

  do
  {
    sret = readLine(STDIN, buf, PAGE_SIZE);
    if (sret > 0)
    {
      //remove the '\n' character
      buf[sret-1] = '\0';
    }
    switch (state)
    {
      case (INIT_STATE):
      {
        if (strstr(buf, gBye) == buf)
        {
          state = GOODBYE_STATE;
        }
        else if (strstr(buf, gHello) == buf)
        {
          name = buf + sizeof(gHello) - 1;
          //get a new random uid
          random(&uid, sizeof(uid), NULL); 
          snprintf(uidStr, 24, "#x", uid);
          printf("#s#s#s#s#s\n", gHelloReply1, name, gHelloReply2, uidStr, gHelloReply3);
          state = CONNECTED_STATE;
        }
        else
        {
          printf("BAD CMD\n");
        }
        break;
      }
      case (CONNECTED_STATE):
      {
        if (strstr(buf, gBye) == buf)
        {
          state = GOODBYE_STATE;
        }
        else if (strstr(buf, uidStr) != buf)
        {
          printf("BAD CMD\n");
        }
        else if (parseAndGetPage(buf, &start, &end, uidStr) != 0)
        {
          printf("BAD CMD\n");
        }
        break;
      }
      default:
      {
        break;
      }
    }
  } while (state != GOODBYE_STATE);
          
  printf("#s\n", gBye);
  sendGoodbyes();

  return (0);
}
