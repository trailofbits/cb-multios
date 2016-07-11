#include <libcgc.h>

#include "words.h"

typedef unsigned int uint32_t;
#define PAGE_SIZE 4096

char gValidChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
#define VALID_CHARS_LEN (sizeof(gValidChars) - 1)
#define IS_VALID_CHAR(_c) ( ((_c >= 'a') && (_c <= 'z')) || ((_c >= 'A') && (_c <= 'Z')) || ((_c >= '0') && (_c <= '9')) )
#define NUM_WORDS (sizeof(gSeedWords) / sizeof(char*))
#define NUM_ROUNDS 10

#define ENTER_NUM_MSG "Please Enter a 2 Digit Number\n"
#define WORD_MSG "Word: "
#define LOSE_MSG "You Lose\n"
#define WIN_MSG "You Win!\n"
#define NEXT_WORD_MSG "Next Word: "
#define FINAL_RND_MSG "Final Round. Chose another 2 digit number\n"

size_t strlen(char* str)
{
  size_t ret = 0; 
  if (str == NULL)
  {
    return (0);
  }
  for (ret = 0; str[ret] != '\0'; ret++)
  {
  }
  return (ret);
}

size_t transmit_all(char* buf, size_t size)
{
  size_t rx_bytes = 0;
  size_t total = 0;
  int ret = 0;
  if (buf == NULL)
  {
    return (0);
  }
  
  do
  {
    ret = transmit(STDOUT, buf, size - total, &rx_bytes);
    if ( (ret != 0) || (rx_bytes == 0) )
    {
      _terminate(1);
    }
    total += rx_bytes;
  }
  while (total < size);

  return (size);
}

size_t transmit_str(char* buf)
{
  size_t len = strlen(buf);
  return (transmit_all(buf, len));
}

size_t receive_all(char* buf, size_t size)
{
  size_t rx_bytes = 0;
  size_t total = 0;
  int ret = 0;
  if (buf == NULL)
  {
    return (0);
  }
  
  do
  {
    ret = receive(STDIN, buf, size-total, &rx_bytes);
    if ( (ret != 0) || (rx_bytes == 0) )
    {
      _terminate(1);
    }
    total += rx_bytes;
  }
  while (total < size);
  
  return (size);
}

size_t readline(char* buf, size_t len)
{
  if (buf == NULL)
  {
    return (0);
  }

  size_t count = 0;
  int ret = 0;
  char c = 0;
  size_t rx_bytes = 0;
  do
  {
    ret = receive(STDIN, &c, 1, &rx_bytes);
    if ( (ret != 0) || (rx_bytes == 0) )
    {
      _terminate(1);
    }
    buf[count] = c;
    count++;
  } while ( (c != '\n') && (count < len) );

  return (count); 
}

char rotN(char c, int n)
{
  int temp = 0;
  n = n % VALID_CHARS_LEN;

  if ( (c >= 'a') && (c <= 'z') )
  {
    temp = c - 'a'; //temp is the offset
  }
  else if ( (c >= 'A') && (c <= 'Z') )
  {
    temp = c - 'A' + 26;
  }
  else if ( (c >= '0') && (c <= '9') )
  {
    temp = c - '0' + 52;
  } 
  else
  {
    return (c); //no rotation
  }

  temp += n;
  temp = temp % VALID_CHARS_LEN;
  return (gValidChars[temp]);
}

size_t strrotcpy(char* dst, char* src, int rot)
{
  if ( (src == NULL) || (dst == NULL) )
  {
    return (0);
  }

  size_t ret = 0;
  for (ret = 0; src[ret] != '\0'; ret++)
  {
    dst[ret] = rotN(src[ret], rot);
  }

  dst[ret] = '\0';
  return (ret);
}

char** gWords = NULL;
char* gWordData = NULL;

int init(int rot)
{
  int ret = 0;
  size_t numWords = NUM_WORDS;

  //first allocate enough space for the wordlist
  ret = allocate( sizeof(gSeedWords), 0, (void**)(&gWords));
  if (ret != 0)
  {
    return (ret);
  }

  //now calculate how many bytes we need to store the words themselves
  size_t total = 0;
  int i = 0;
  for (i = 0; i < numWords; i++)
  {
    total += strlen(gSeedWords[i]);
    total += 1; //for the NULL character
  }
 
  ret = allocate(total, 0, (void**)(&gWordData));
  if (ret != 0)
  {
    return (ret);
  } 

  //now that we have both we can fill in the data  
  size_t temp = 0;
  char* pTemp = gWordData;
  for (i = 0; i < numWords; i++)
  {
    gWords[i] = pTemp;
    pTemp += strrotcpy(pTemp, gSeedWords[i], rot);
    pTemp += 1; //for the NULL character
  }
  
  for ( ; i < (PAGE_SIZE / sizeof(char*)); i++)
  {
    gWords[i] = 0;
  }

  return (0);
}

int toInt(char c1, char c2)
{
  int ret = 0;

  if ( (c1 >= '0') && (c1 <= '9') )
  {
    ret = c1 - '0';
    if ( (c2 >= '0') && (c2 <= '9') )
    {
      ret *= 10;
      ret += c2 - '0'; 
      return (ret);
    }
    else if (c2 != '\0')
    {
      return (ret); 
    }  
    else
    {
      return (0);
    }
  }

  return (0);
}

/** This LFSR pesudo random number generator is from Bruce Schneier's
 *    1992 article in Dr. Dobbs www.schneier.com/paper-pseudorandom-sequence.html
 *  As the article says, this is not a very good generator. But it is good
 *    enough for our purposes
 *  Instead of just returning the last bit, we return the whole uint32
**/
static uint32_t gRandRegister = 0xDA2bAC9C;

uint32_t RANDOM()
{
  gRandRegister = ((((gRandRegister >> 31)
             ^ (gRandRegister >> 6)
             ^ (gRandRegister >> 4)
             ^ (gRandRegister >> 2)
             ^ (gRandRegister >> 1)
             ^ gRandRegister)
             & 0x00000001)
             << 31)
             | (gRandRegister >> 1);

  return (gRandRegister);
}

int strcmp(char* s1, char* s2)
{
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

  int i = 0;
  while (s1[i] != '\0')
  {
    if (s2[i] == '\0')
    {
      return (1);
    } 
    if (s1[i] < s2[i])
    {
      return (-1);
    }
    else if (s1[i] > s2[i])
    {
      return (1);
    }

    i++;
  }

  if (s2[i] == '\0')
  {
    return (0);
  }
  
  return (-1);
}

#define rand() RANDOM()

void srand(uint32_t seed)
{
  gRandRegister = seed;
}

void scramble(char* dst, char* src, size_t len)
{
#if PATCHED
  if ( (dst == NULL) || (src == NULL) )
  {
    return;
  }
#endif

  int i = 0;
  uint32_t r = (rand() % 3) + 2;

  while ( (src[i] != '\0') && (i < len) )
  {
    if (IS_VALID_CHAR(src[i]))
    {
      if (i % r)
      {
        dst[i] = src[i];
      }
      else
      {
        dst[i] = '_';
      }       
    }    
    else
    {
      dst[i] = src[i];
    }
    i++;
  }
  dst[i] = '\0';
}

int main(void)
{
#define BUF_SIZE 64
#define READLINE(_buf, _len) do { sret = readline(_buf, _len); if (sret == 0) { _terminate(1); } } while (0)

  char buf[BUF_SIZE];
  int i = 0;
  int ret = 0;
  int temp = 0;
  size_t sret = 0;
  char c = '\n';

  transmit_str(ENTER_NUM_MSG);
  READLINE(buf, BUF_SIZE);
  
  i = toInt(buf[0], buf[1]);
  if (init(i+1) != 0)
  {
    return (-1);
  }
 
  //initialize the LFSR
  srand(*((int*)buf));
  
  for (i = 0; i < NUM_ROUNDS; i++)
  {
    if (i == 0)
    {
      transmit_str(WORD_MSG);
    }
    else 
    {
      transmit_str(NEXT_WORD_MSG);
    }

    temp = rand() % NUM_WORDS;
    scramble(buf, gWords[temp], BUF_SIZE);
    transmit_str(buf);
    transmit_all(&c, 1);
    READLINE(buf, BUF_SIZE);
  
    buf[sret-1] = '\0';

    if (strcmp(buf, gWords[temp]) != 0)
    {
      transmit_str(LOSE_MSG);
      return (0);
    }
  }

  transmit_str(FINAL_RND_MSG);      
  READLINE(buf, BUF_SIZE);
  
  i = toInt(buf[0], buf[1]);

#if PATCHED
  i = i % NUM_WORDS;
#endif

  scramble(buf, gWords[i], BUF_SIZE);

  transmit_str(buf);
  transmit_all(&c, 1);
  READLINE(buf, BUF_SIZE);
  
  buf[sret-1] = '\0';

  if (strcmp(buf, gWords[i]) != 0)
  {
    transmit_str(LOSE_MSG);
  }
  else
  {
    transmit_str(WIN_MSG);
  }
  return (0);
}

