#include "libpov.h"

uint32_t cgc_hexStrToUint32(const unsigned char* str)
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

uint32_t cgc_flipEndian(uint32_t t)
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

int main(int cgc_argc, char *cgc_argv[])
{
  char* s = "E 1 3337AFF0 10101090\n";
  char* p = "P 1\n";
  unsigned char buf[128];
  uint32_t temp = 0;

  type2_vals t2v;
  cgc_type2_negotiate(&t2v);

  cgc_transmit_all(STDOUT, s, cgc_strlen(s));
  cgc_transmit_all(STDOUT, p, cgc_strlen(p));
  cgc_length_read(STDIN, buf, 128);
  buf[8] = '\0';
  temp = cgc_hexStrToUint32(buf);
  temp = cgc_flipEndian(temp);
  cgc_type2_submit((unsigned char*)(&temp), 4);
  return (0);
}

