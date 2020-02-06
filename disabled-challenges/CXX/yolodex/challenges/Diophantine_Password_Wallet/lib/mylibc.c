#include "libcgc.h"
#include "cgc_mylibc.h"


cgc_ssize_t cgc_readLine(int fd, char* buf, cgc_size_t len)
{
  char c = '\0';
  int ret = 0;
  cgc_size_t i = 0;
  cgc_size_t numRead;
  cgc_size_t temp = len;

  if (buf == NULL)
  {
    return (-EINVAL);
  }

  //loop until the character is cgc_read
  do
  {
    ret = cgc_receive(fd, &c, sizeof(char), &numRead);
    if ( (ret != 0) || (numRead == 0) )
    {
      cgc__terminate(ret);
    }

    buf[i] = c; 
    i++;
    if (i >= temp)
    {
      i = temp - 1;
    }
  } while ( c != '\n');
 
  buf[i] = '\0';

  return (i);
}

cgc_size_t cgc_myStrLen(const char* str)
{
  cgc_size_t i = 0;

  if (str == NULL)
  {
    return (0);
  }

  for (i = 0; str[i] != '\0'; i++)
  {
  }

  return (i);
}

cgc_size_t cgc_my_printf(const char* str)
{
  cgc_size_t rx_bytes;
  cgc_size_t total = 0; 
  cgc_size_t len = 0;
  int ret = 0;
  if (str == NULL)
  {
    return (-1);
  }

  len = cgc_myStrLen(str);
  do
  {
    ret = cgc_transmit(STDOUT, str + total, len - total, &rx_bytes);
    if ( (ret != 0) )
    {
      cgc__terminate(ret);
    }
    total += rx_bytes;
  } while (total < len);

  return (total);
}

//minlen is used for leading 0's in the fractional part
int cgc_snprintdecimal(char* str, cgc_size_t len, uint32_t num)
{
  int i = 0;
  int j = 0;
  uint32_t rem = 0;
  char temp[24]; //the maximum uint64_t value is 2^64 - 1
                 // which is approx 10^20 so 24 characters should be good
  temp[0] = '0';
  temp[0] = '\0';

  if ( (str == NULL) || (len < 2) )
  {
    return (-1);
  }

  if (num == 0)
  {
    str[0] = '0';
    str[1] = '\0';
    return (1);
  }

  while (num != 0)
  {
    rem = num % 10; //get the remainder
    temp[i] = '0' + rem;
    num = num / 10; //divide it by 10 
    i++;
  }

  //now see if everything fits
  if (i < len)
  {
    //remember this is NOT a null terminated string
    i--; // decrement i first to get to the last character written
    while (i >= 0)
    {
      str[j] = temp[i]; 
      j++; //move j up
      i--; //move i down
    }  
    str[j] = '\0';
    return (j);
  }

  return (-1); 
}

uint32_t cgc_strToUint32(const char* str)
{
  int i = 0;
  uint64_t temp64 = 0;
  uint32_t temp = 0;

  if (str == NULL)
  {
    return (0);
  }

  while ( (str[i] >= '0') && (str[i] <= '9') )
  {
    temp = str[i] - '0';
    temp64 *= 10;
    temp64 += temp;
    i++;
  }

  return ((uint32_t)temp64);
}


