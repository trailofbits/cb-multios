#include "libcgc.h"

#include "cgc_words.h"

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

cgc_size_t cgc_strlen(char* str)
{
  cgc_size_t ret = 0; 
  if (str == NULL)
  {
    return (0);
  }
  for (ret = 0; str[ret] != '\0'; ret++)
  {
  }
  return (ret);
}

cgc_size_t cgc_transmit_all(char* buf, cgc_size_t size)
{
  cgc_size_t rx_bytes = 0;
  cgc_size_t total = 0;
  int ret = 0;
  if (buf == NULL)
  {
    return (0);
  }
  
  do
  {
    ret = cgc_transmit(STDOUT, buf, size - total, &rx_bytes);
    if ( (ret != 0) || (rx_bytes == 0) )
    {
      cgc__terminate(1);
    }
    total += rx_bytes;
  }
  while (total < size);

  return (size);
}

cgc_size_t cgc_transmit_str(char* buf)
{
  cgc_size_t len = cgc_strlen(buf);
  return (cgc_transmit_all(buf, len));
}

cgc_size_t cgc_receive_all(char* buf, cgc_size_t size)
{
  cgc_size_t rx_bytes = 0;
  cgc_size_t total = 0;
  int ret = 0;
  if (buf == NULL)
  {
    return (0);
  }
  
  do
  {
    ret = cgc_receive(STDIN, buf, size-total, &rx_bytes);
    if ( (ret != 0) || (rx_bytes == 0) )
    {
      cgc__terminate(1);
    }
    total += rx_bytes;
  }
  while (total < size);
  
  return (size);
}

cgc_size_t cgc_readline(char* buf, cgc_size_t len)
{
  if (buf == NULL)
  {
    return (0);
  }

  cgc_size_t count = 0;
  int ret = 0;
  char c = 0;
  cgc_size_t rx_bytes = 0;
  do
  {
    ret = cgc_receive(STDIN, &c, 1, &rx_bytes);
    if ( (ret != 0) || (rx_bytes == 0) )
    {
      cgc__terminate(1);
    }
    buf[count] = c;
    count++;
  } while ( (c != '\n') && (count < len) );

  return (count); 
}

char cgc_rotN(char c, int n)
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

cgc_size_t cgc_strrotcpy(char* dst, char* src, int rot)
{
  if ( (src == NULL) || (dst == NULL) )
  {
    return (0);
  }

  cgc_size_t ret = 0;
  for (ret = 0; src[ret] != '\0'; ret++)
  {
    dst[ret] = cgc_rotN(src[ret], rot);
  }

  dst[ret] = '\0';
  return (ret);
}

char** cgc_gWords = NULL;
char* cgc_gWordData = NULL;

int cgc_init(int rot)
{
  int ret = 0;
  cgc_size_t numWords = NUM_WORDS;

  //first allocate enough space for the wordlist
  ret = cgc_allocate( sizeof(gSeedWords), 0, (void**)(&cgc_gWords));
  if (ret != 0)
  {
    return (ret);
  }

  //now calculate how many bytes we need to store the words themselves
  cgc_size_t total = 0;
  int i = 0;
  for (i = 0; i < numWords; i++)
  {
    total += cgc_strlen(gSeedWords[i]);
    total += 1; //for the NULL character
  }
 
  ret = cgc_allocate(total, 0, (void**)(&cgc_gWordData));
  if (ret != 0)
  {
    return (ret);
  } 

  //now that we have both we can fill in the data  
  cgc_size_t temp = 0;
  char* pTemp = cgc_gWordData;
  for (i = 0; i < numWords; i++)
  {
    cgc_gWords[i] = pTemp;
    pTemp += cgc_strrotcpy(pTemp, gSeedWords[i], rot);
    pTemp += 1; //for the NULL character
  }
  
  for ( ; i < (PAGE_SIZE / sizeof(char*)); i++)
  {
    cgc_gWords[i] = 0;
  }

  return (0);
}

int cgc_toInt(char c1, char c2)
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

uint32_t cgc_RANDOM()
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

int cgc_strcmp(char* s1, char* s2)
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

void cgc_my_srand(uint32_t seed)
{
  gRandRegister = seed;
}

void cgc_scramble(char* dst, char* src, cgc_size_t len)
{
#if PATCHED
  if ( (dst == NULL) || (src == NULL) )
  {
    return;
  }
#endif

  int i = 0;
  uint32_t r = (cgc_RANDOM() % 3) + 2;

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

int main(int cgc_argc, char *cgc_argv[])
{
#define BUF_SIZE 64
#define READLINE(_buf, _len) do { sret = cgc_readline(_buf, _len); if (sret == 0) { cgc__terminate(1); } } while (0)

  char buf[BUF_SIZE] = {};
  int i = 0;
  int ret = 0;
  int temp = 0;
  cgc_size_t sret = 0;
  char c = '\n';

  cgc_transmit_str(ENTER_NUM_MSG);
  READLINE(buf, BUF_SIZE);
  
  i = cgc_toInt(buf[0], buf[1]);
  if (cgc_init(i+1) != 0)
  {
    return (-1);
  }
 
  //initialize the LFSR
  cgc_my_srand(*((int*)buf));
  
  for (i = 0; i < NUM_ROUNDS; i++)
  {
    if (i == 0)
    {
      cgc_transmit_str(WORD_MSG);
    }
    else 
    {
      cgc_transmit_str(NEXT_WORD_MSG);
    }

    temp = cgc_RANDOM() % NUM_WORDS;
    cgc_scramble(buf, cgc_gWords[temp], BUF_SIZE);
    cgc_transmit_str(buf);
    cgc_transmit_all(&c, 1);
    READLINE(buf, BUF_SIZE);
  
    buf[sret-1] = '\0';

    if (cgc_strcmp(buf, cgc_gWords[temp]) != 0)
    {
      cgc_transmit_str(LOSE_MSG);
      return (0);
    }
  }

  cgc_transmit_str(FINAL_RND_MSG);      
  READLINE(buf, BUF_SIZE);
  
  i = cgc_toInt(buf[0], buf[1]);

#if PATCHED
  i = i % NUM_WORDS;
#endif

  cgc_scramble(buf, cgc_gWords[i], BUF_SIZE);

  cgc_transmit_str(buf);
  cgc_transmit_all(&c, 1);
  READLINE(buf, BUF_SIZE);
  
  buf[sret-1] = '\0';

  if (cgc_strcmp(buf, cgc_gWords[i]) != 0)
  {
    cgc_transmit_str(LOSE_MSG);
  }
  else
  {
    cgc_transmit_str(WIN_MSG);
  }
  return (0);
}

