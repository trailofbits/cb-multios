#include "cgc_mylibc.h"
#include "cgc_defs.h"

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

int cgc_findFDs(const char* server, int* pIn, int* pOut)
{
  if ( (server == NULL) || (pIn == NULL) || (pOut == NULL) )
  {
    return (-1);
  }

  for (cgc_size_t i = 0; (i < MAX_SERVERS) && (gServers[i].server[0] != '\0'); i++)
  {
    if (cgc_strcmp(gServers[i].server, server) == 0)
    {
      *pIn = gServers[i].in;
      *pOut = gServers[i].out;
      return (0);
    }
  }
  return (-1);
}

void cgc_sendGoodbyes()
{
  ProtoMsg msg;
  msg.type = PROTO_BYE;
  msg.msgLen = 0;

  for (cgc_size_t i = 0; (i < MAX_SERVERS) && (gServers[i].server[0] != '\0'); i++)
  {
    cgc_sendMsg(gServers[i].out, &msg, sizeof(msg));
  }
}

uint8_t gBuf[PAGE_SIZE];

int cgc_doGet(const char* page, int in, int out)
{
  ProtoMsg msg;
  cgc_size_t temp = 0;
  
  if (page == NULL)
  {
    return (-1);
  }
  
  msg.type = PROTO_GET;

  msg.msgLen = cgc_strlen(page);

  cgc_sendMsg(out, &msg, sizeof(msg));

  cgc_sendMsg(out, page, msg.msgLen);

  cgc_recvMsg(in, &msg, sizeof(msg));
 
  if (msg.type != PROTO_GET_ACK)
  {
    return (-1);
  }

  while (temp < msg.msgLen)
  {
    if ((msg.msgLen - temp) > PAGE_SIZE)
    {
      cgc_recvMsg(in, gBuf, PAGE_SIZE);
      cgc_sendMsg(STDOUT, gBuf, PAGE_SIZE);
      temp += PAGE_SIZE;
    }
    else 
    {
      cgc_recvMsg(in, gBuf, msg.msgLen - temp);
      cgc_sendMsg(STDOUT, gBuf, msg.msgLen - temp);
      temp = msg.msgLen;
    }
  }

  cgc_sendMsg(STDOUT, gTERM, sizeof(gTERM) - 1);

  return (0);
}

int cgc_parseAndGetPage(char* buf, char** pStart, char** pEnd, const char* uidStr)
{
  char* start = NULL;
  char* end = NULL;
  
  if ( (buf == NULL) || (pStart == NULL) || (pEnd == NULL) || (uidStr == NULL) )
  {
    return (-1);
  }

  start = buf + cgc_strlen(uidStr);
  if (cgc_strstr(start, gGet1) != start)
  {
    return (-1);
  }

  start = start + sizeof(gGet1) - 1;
  end = cgc_strrstr(start, gGet2);
  if (end == NULL)
  {
    return (-1);
  }

  //reset the NULL character so start is the web-address
  *end = '\0';
  //reset the NULL character again so that start is the domain
  end = cgc_strchr(start, '/');
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
  if (cgc_findFDs(start, &inFD, &outFD) != 0)
  {
    cgc_printf("SERVER [#s] NOT FOUND\n", start);
    return (0);
  } 

  return (cgc_doGet(end, inFD, outFD));
}

int main(int cgc_argc, char *cgc_argv[])
{
  char* buf = NULL;
  char* name = NULL;
  char* start = NULL;
  char* end = NULL;
  char uidStr[24];
  uint32_t uid = 0;
  cgc_ssize_t sret = 0;
 
  E_States state = INIT_STATE;
  cgc_printf_setFlushOnNewline(1);

  if (cgc_allocate(PAGE_SIZE, 0, (void**)&buf) != 0)
  {
    return (-1);
  }

  do
  {
    sret = cgc_readLine(STDIN, buf, PAGE_SIZE);
    if (sret > 0)
    {
      //remove the '\n' character
      buf[sret-1] = '\0';
    }
    switch (state)
    {
      case (INIT_STATE):
      {
        if (cgc_strstr(buf, gBye) == buf)
        {
          state = GOODBYE_STATE;
        }
        else if (cgc_strstr(buf, gHello) == buf)
        {
          name = buf + sizeof(gHello) - 1;
          //get a new random uid
          cgc_random(&uid, sizeof(uid), NULL); 
          cgc_snprintf(uidStr, 24, "#x", uid);
          cgc_printf("#s#s#s#s#s\n", gHelloReply1, name, gHelloReply2, uidStr, gHelloReply3);
          state = CONNECTED_STATE;
        }
        else
        {
          cgc_printf("BAD CMD\n");
        }
        break;
      }
      case (CONNECTED_STATE):
      {
        if (cgc_strstr(buf, gBye) == buf)
        {
          state = GOODBYE_STATE;
        }
        else if (cgc_strstr(buf, uidStr) != buf)
        {
          cgc_printf("BAD CMD\n");
        }
        else if (cgc_parseAndGetPage(buf, &start, &end, uidStr) != 0)
        {
          cgc_printf("BAD CMD\n");
        }
        break;
      }
      default:
      {
        break;
      }
    }
  } while (state != GOODBYE_STATE);
          
  cgc_printf("#s\n", gBye);
  cgc_sendGoodbyes();

  return (0);
}
