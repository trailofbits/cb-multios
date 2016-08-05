#include <libcgc.h>
#include "libc.h"

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#define PAGE_SIZE 4096


#define TEXT_START (0x080480a0)
#define TEXT_SIZE ( (PAGE_SIZE * 2) - 0xa0)

typedef struct _TextProtectSkip
{
  uint32_t addr;
  uint32_t size;
} TextProtectSkip;

#include "offsets.h"

/*
#define NUM_SKIPS 5
TextProtectSkip skips[NUM_SKIPS] = { {0x80486c8,5}, {0x80488ab,5}, {0x80488c6,7}, {0x804910c,10}, {0x8048210,7} };
*/

#define DATA_START (0x804C000)  
#define DATA_SIZE (PAGE_SIZE * 0x18)

//We have to be careful with the TEXT hash because the value that we are checking against will
// also be included in the text section which will change the value of the hash
// so the best way to handle this is to ignore the text protect function .. everything else
// should be static 

//can't seem to pre-determine how big the stack is that we need.

void heapProtect()
{
  int ret = 0;
  void* temp = 0;
  size_t count = 0;

  while (1)
  {
    ret = allocate(0x1000*PAGE_SIZE, 0, &temp);
    if (ret != 0)
    {
      break;
    }
    count+=0x1000;
  }
  while (1)
  {
    ret = allocate(0x100*PAGE_SIZE, 0, &temp);
    if (ret != 0)
    {
      break;
    }
    count+=0x100;
  }
  while (1)
  {
    ret = allocate(0x10*PAGE_SIZE, 0, &temp);
    if (ret != 0)
    {
      break;
    }
    count+=0x10;
  }
  while (1)
  {
    ret = allocate(0x1*PAGE_SIZE, 0, &temp);
    if (ret != 0)
    {
      break;
    }
    count+=0x1;
  }

  if (count != EXPECTED_MEMSIZE)
  {
    _terminate(-1);
  }

}

void textProtect()
{
  uint32_t hash = 0;
  uint32_t* text = (uint32_t*)(TEXT_START); 
  int i = 0;
  int bHash = 0;
  for (; (uint32_t)text < (TEXT_START + TEXT_SIZE); text += 1)
  {
    bHash = 1;
    for (i = 0; i < NUM_SKIPS; i++)
    {
      //We need to check the lower address -4 since we are reading 4 bytes at a time.
      if ( ((uint32_t)text >= (skips[i].addr - 4)) && ((uint32_t)text <= (skips[i].addr + skips[i].size)) )
      {
        bHash = 0;
        break;
      }
    }
    if (bHash)
    {
      hash ^= *text;
    }
  }

  if (hash != EXPECTED_TEXT_HASH)
  {
    _terminate(-1);
  }

}

void dataProtect()
{
  uint32_t hash = 0;
  uint32_t* data = (uint32_t*)(DATA_START);
  for (; data < (uint32_t*)(DATA_START + DATA_SIZE); data += sizeof(uint32_t))
  {
    hash ^= *data;
  }

  if (hash != EXPECTED_DATA_HASH)
  {
    _terminate(-1);
  }
}

void selfProtect()
{
  //heapProtect();
  dataProtect();
  textProtect();
}



#define MAX_OPTIONS 10
#define MAX_BRANCHES 10

typedef struct _MsgNode
{
  char* m[MAX_OPTIONS];
  size_t numOps;
  char* responses[MAX_BRANCHES];
  size_t numResponses;
  struct _MsgNode* branches[MAX_BRANCHES];
  size_t numBranches;
} MsgNode;

#include "script.h"

#define MAGIC_PAGE 0x4347C000
#define PAGE_SIZE 4096
#define PAGE_MASK (~0xFFF)

static inline int isValidAddr(const void* addr)
{
#ifdef PATCHED_2
  if ( (((uint32_t)addr & PAGE_MASK) == 0) || (((uint32_t)addr & PAGE_MASK) == (MAGIC_PAGE & PAGE_MASK) ) )
#else
  if ( (((uint32_t)addr & PAGE_MASK) == 0) || (((uint32_t)addr & PAGE_MASK) == (0 & PAGE_MASK) ) )
#endif
  {
    return (0);
  }

  return (fdwait(-1,NULL,NULL,addr,NULL) != EFAULT);
}

MsgNode* curNode = &head;

char* errorMsgs[] = {"Huh? I don't understand. Come again?", "You are still breaking up.", "Alright fine. I give up."};

int curErrorLevel = 0;

unsigned int curVal = 0;

int gSeed = 0;
//MAX_OPTIONS is 10, so this will work out fine. 
int rand()
{
  gSeed = (gSeed + 7) % 13;
  return (gSeed);
}

#define MAGC_PAGE 0x4347C000

#define MAX_MSG_SIZE 128

uint32_t hexStrToUint32(const char* str)
{
  int i = 0;
  uint32_t ret = 0;
  uint32_t temp = 0;
 
  for (i = 0; str[i] != '\0'; i++)
  {
    ret = ret << 4;
    if ( (str[i] >= '0') && (str[i] <= '9') ) 
    {
      temp = str[i] - '0';
    }
    else if ( (str[i] >= 'A') && (str[i] <= 'F') )
    {
      temp = str[i] - 'A' + 10;
    }
    else if ( (str[i] >= 'a') && (str[i] <= 'f') )
    {
      temp = str[i] - 'a' + 10;
    }
    else
    {
      return (0);
    }
    ret = ret | (temp & 0xF);
  } 

  return (ret);
}

void printLights(void* addr)
{
  uint8_t contents = 0;
  char temp[10] = "BBBBBBBB\n";
  int i = 0;

  if (isValidAddr(addr))
  {
    contents = *((uint8_t*)addr);
    //shift of 0 is undefined so we have to be careful, that is why we are looping
    // up to 7 only
    for (i = 0; i < 7; i++)
    {
      if ( (contents >> (7-i)) & 0x1 )
      {
        temp[i] = 'G'; 
      }
      else
      {
        temp[i] = 'W';
      }
    }

    //get the last bit
    if ( contents & 0x1 )
    {
      temp[7] = 'G';
    }
    else
    {
      temp[7] = 'W';
    }
  }

  transmit_all(STDOUT, temp, 9);
}

int main(void)
{
  char buf[MAX_MSG_SIZE];
  int i = 0;
  int j = 0;
  size_t numRead = 0;
  int bValidResponse = 1;
  uint32_t addr = 0;

  applyPatches();

  selfProtect();

  while (curNode != NULL)
  {
    if (bValidResponse)
    {
      i = rand() % curNode->numOps;
      fprintStr(STDOUT, curNode->m[i]);
      fprintStr(STDOUT, "\n");
    }
 
    bValidResponse = 0;

    if ((curNode->numBranches == 0) && (curNode->numResponses == 0))
    {
      return(0); //End of the road
    }

    //test the speecial condition where we are just jumping
    if ((curNode->numBranches == 1) && (curNode->numResponses == 0))
    {
      bValidResponse = 1;
      curNode = curNode->branches[0]; //just update things
      continue;
    }

#ifdef PATCHED_1
    numRead = receive_until(STDIN, buf, sizeof(buf), '\n');
#else
    numRead = receive_until(STDIN, buf, sizeof(buf) * 2, '\n');
#endif 
    if (numRead == 0)
    {
      break;
    }
    if (numRead >= sizeof(buf))
    {
      //too long of an input so just end
      break;
    }
    buf[numRead-1] = '\0'; //clear out the newline

    //Before we continue, lets see if it is the vulnerable node
    if (curNode == &vulnerability)
    {
      addr = hexStrToUint32(buf);
      printLights((void*)addr); 
      curNode = curNode->branches[0];
      bValidResponse = 1;
      curErrorLevel = 0;
      continue;
    }


    for (j = 0; j < curNode->numBranches; j++)
    {
      if (strcmp(curNode->responses[j], buf) == 0)
      {
        curNode = curNode->branches[j];
        bValidResponse = 1;
        curErrorLevel = 0;
        break;
      }
    }

    if (!bValidResponse)
    {
      fprintStr(STDOUT, errorMsgs[curErrorLevel]);
      fprintStr(STDOUT, "\n");
      curErrorLevel++;
      if (curErrorLevel > 2)
      { 
        return (0);  
      }
    }
  }

  return (0);
}

