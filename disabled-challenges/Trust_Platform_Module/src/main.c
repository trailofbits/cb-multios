#include "libcgc.h"
#include "cgc_libc.h"

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

#define PAGE_SIZE 4096
#define PAGE_MASK (~0xFFF)

#define TEXT_START (0x080480a0 & PAGE_MASK)
#define TEXT_SIZE (PAGE_SIZE)
#define TEXT_END ((TEXT_START + TEXT_SIZE) & PAGE_MASK)

#define HASH_SIZE 128 

#define MAGIC_PAGE 0x4347C000

static inline int cgc_isValidAddr(const void* addr)
{
#ifdef PATCHED_1
  if ( (((uint32_t)addr & PAGE_MASK) == 0) || (((uint32_t)addr & PAGE_MASK) == (MAGIC_PAGE & PAGE_MASK) ) )
#else
  if ( (((uint32_t)addr & PAGE_MASK) == 0) || (((uint32_t)addr & PAGE_MASK) == (0 & PAGE_MASK) ) )
#endif
  {
    return (0);
  }

  return (cgc_fdwait(-1,NULL,NULL,addr,NULL) != EFAULT);
}

int cgc_xorHash(const uint8_t* target, cgc_size_t size, uint8_t* hashOutput)
{
  cgc_size_t i = 0;

  for (i = 0; i < HASH_SIZE; i++)
  {
    if (i < size)
    {
      hashOutput[i] ^= target[i];
    }
    //nothing to do in the else case since we are 0 padding.
  }

  return (0);
}

int cgc_HASH(const uint8_t* buf, cgc_size_t size, uint8_t* hashOutput)
{
  const uint8_t* temp = NULL;
  cgc_size_t i = 0;
  int ret = 0;

  if ( (buf == NULL) || (hashOutput == NULL) )
  {
    return (-1);
  }

  //first of all we need to zero out the target
  for (i = 0; i < HASH_SIZE; i++)
  {
    hashOutput[i] = 0;
  }

  i = 0;
  temp = buf;
  //now do the hashing
  while (temp < (buf + size))
  {
    //Before we start, lets see if temp is a valid address
    if (!cgc_isValidAddr(temp))
    {
      temp += PAGE_SIZE; //go to the next page
      //then mask back to the base
      temp = (uint8_t*)((uint32_t)temp & PAGE_MASK);
      continue;
    }

    ret = cgc_xorHash(temp, size - i, hashOutput);
    if (ret != 0)
    {
      return (ret);
    }    
    temp += HASH_SIZE; 
    i += HASH_SIZE;
  }
  return (0);
}

#define MAX_PCRS 8

uint8_t gPCRs[MAX_PCRS][HASH_SIZE];

int cgc_EXTEND(cgc_size_t pcr, const void* startAddr, const void* endAddr)
{
  uint8_t temp[HASH_SIZE];
  cgc_size_t size = 0;
  
  if (endAddr <= startAddr)
  {
    return (-1);
  }
  size = endAddr - startAddr;
  
  cgc_HASH(startAddr, size, temp);
  cgc_xorHash(temp, HASH_SIZE, gPCRs[pcr]);

  return (0);  
}

int cgc_INIT(uint8_t* hash, char c)
{
  if (hash == NULL)
  {
    return (-1);
  }

  for (cgc_size_t i = 0; i < HASH_SIZE; i++)
  {
    hash[i] = c;
  }  
  return (0);
}

int cgc_ZERO(cgc_size_t pcr)
{
  if (pcr >= MAX_PCRS)
  {
    return (-1);
  }

  return (cgc_INIT(gPCRs[pcr], 0));
}

int cgc_RESET()
{
  int ret = 0;
  for (cgc_size_t i = 0; i < MAX_PCRS; i++)
  {
    ret = cgc_INIT(gPCRs[i], i);
    if (ret != 0)
    {
      return (ret);
    }
  }
  return (0);
}

uint32_t cgc_hexStrToUint32(const char* str)
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

char gNibToHexChar[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

void cgc_hashToHexStr(const uint8_t* hash, char* str)
{
  int i = 0;
  char c = 0;
  for (i = 0; i < HASH_SIZE; i++)
  {
    c = hash[i];
    str[i * 2] = gNibToHexChar[ (c >> 4) & (0xF) ];
    str[(i * 2)+1] = gNibToHexChar[ c & (0xF) ];
  }
}

cgc_size_t cgc_findChar(const char* str, char c)
{
  cgc_size_t i = 0;
  for (i = 0; (str[i] != c) && (str[i] != '\0'); i++);
  if (str[i] == '\0')
  {
    return (-1);
  }
  return (i);
}

int main(int cgc_argc, char *cgc_argv[])
{
  char cmd[64];
  uint8_t hash[HASH_SIZE];
  uint8_t buf[HASH_SIZE];
  char hashStr[(HASH_SIZE * 2) + 1]; //add a character for \n
  cgc_size_t pcr = 0;
  cgc_size_t off = 0;
  cgc_size_t off2 = 0;
  uint32_t startAddr;
  uint32_t endAddr;
  cgc_size_t sret = 0;
  cgc_size_t totalRead = 0;

  while (1)
  {
#ifdef PATCHED_2
    sret = cgc_receive_until(STDIN, cmd, 64, '\n');
#else
    sret = cgc_receive_until(STDIN, cmd, 128, '\n');
#endif
    cmd[63] = '\0'; //always end the cstr
    cmd[sret-1] = '\0'; //always end the cstr
    switch(cmd[0])
    {
      case ('R') :
      {
        cgc_RESET();
        break;
      }
      case ('Z') :
      {
        off = cgc_findChar(cmd, ' ');
        if (off == -1)
        {
          return (0);
        }
        pcr = cgc_hexStrToUint32(cmd + off + 1);
        cgc_ZERO(pcr);
        break;
      }
      case ('E') :
      {
        off = cgc_findChar(cmd, ' ');
        if (off == -1)
        {
          return (0);
        }

        off2 = cgc_findChar(cmd + off + 1, ' ');
        if (off2 == -1)
        {
          return (0);
        }
        off2 += off + 1; //off2 is relative to off + 1

        cmd[off2] = '\0';
        pcr = cgc_hexStrToUint32(cmd + off + 1);

        off = cgc_findChar(cmd + off2 + 1, ' ');
        if (off == -1)
        {
          return (0);
        }
        off += off2 + 1;
        cmd[off] = '\0';
        startAddr = cgc_hexStrToUint32(cmd + off2 + 1);

        endAddr = startAddr + cgc_hexStrToUint32(cmd + off + 1); 

        if (startAddr < endAddr)
        {
          cgc_EXTEND(pcr, (void*)startAddr, (void*)endAddr);
        }
        else
        {
          return (0);
        }
        break;
      }
      case ('P') :
      {
        off = cgc_findChar(cmd, ' ');
        if (off == -1)
        {
          return (0);
        }
        pcr = cgc_hexStrToUint32(cmd + off + 1);
        if (pcr >= MAX_PCRS)
        { 
          return (0);
        }
        cgc_hashToHexStr(gPCRs[pcr], hashStr);
        hashStr[(HASH_SIZE) * 2] = '\n';
        cgc_transmit_all(STDOUT, hashStr, (HASH_SIZE*2) + 1);
        break;
      }
      case ('H') :
      {
        off = cgc_findChar(cmd, ' ');
        if (off == -1)
        {
          return (0);
        }

        pcr = cgc_hexStrToUint32(cmd + off + 1);
        if (pcr == -1)
        { 
          return (0);
        }
        
        cgc_INIT(hash, 0);
        //In this case PCR is the contents of the data
        totalRead = 0;
        while (totalRead < pcr)
        {
          sret = pcr - totalRead;
          if ( sret >= HASH_SIZE )
          {
            sret = HASH_SIZE;
            cgc_receive_all(STDIN, buf, HASH_SIZE);
          }
          else
          {
            cgc_receive_all(STDIN, buf, sret);
          }
          cgc_xorHash(buf, sret, hash);
          totalRead += sret;
        }

        cgc_hashToHexStr(hash, hashStr);
        hashStr[(HASH_SIZE) * 2] = '\n';
        cgc_transmit_all(STDOUT, hashStr, (HASH_SIZE*2) + 1);
        break;
      }
      case ('\0'):
      {
        break;
      }
      default :
      {
        return (0);
      }
    }
  }

  return (0);
}

