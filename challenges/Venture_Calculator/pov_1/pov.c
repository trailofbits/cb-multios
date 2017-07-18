#include "libpov.h"

int cgc_send_string(int fd, char* s)
{
  unsigned l = cgc_strlen(s);

  if (!l)
    return -1;

  return cgc_transmit_all(fd, s, cgc_strlen(s));
}

uint32_t cgc_ReadScreen(unsigned char** Lines)
{
#ifdef DEBUG
  return 0;
#endif
  unsigned char* cgc_read;
  unsigned read_len;
  unsigned LineCnt = 0;

  for (;;)
  {
    cgc_send_string(STDERR, "READING\n");
    cgc_delimited_read(STDIN, &cgc_read, &read_len, (unsigned char *)"\n", 1);
    Lines[LineCnt++] = cgc_read;

    if (!cgc_strncmp("----", (const char *)cgc_read, 4)  || !cgc_strncmp("Erro", (const char *)cgc_read, 4))
      break;
    cgc_send_string(STDERR, (char *)cgc_read);
  }

  cgc_send_string(STDERR, "DONE\n");
  return LineCnt;;
}

#define MAX_LINES 0x1000
int main(int cgc_argc, char *cgc_argv[])
{
    type2_vals t2v;
    unsigned char* ScreenBuf[MAX_LINES];
    unsigned LineCnt;

#ifndef DEBUG
    cgc_type2_negotiate(&t2v);
#else
    (void)t2v;
#endif

    cgc_transmit_all(STDOUT, "l23k", 4);

    cgc_send_string(STDERR, "GOING\n");
    LineCnt = cgc_ReadScreen(ScreenBuf);
    for (unsigned Index = 0; Index < 64; ++Index)
    {
      cgc_send_string(STDERR, "LOOP\n");
      cgc_send_string(STDOUT, "0\n");
      LineCnt = cgc_ReadScreen(ScreenBuf);
    }

    cgc_send_string(STDOUT, "shuf\n");
    LineCnt = cgc_ReadScreen(ScreenBuf);
    cgc_send_string(STDOUT, "4986\n");
    LineCnt = cgc_ReadScreen(ScreenBuf);
    cgc_send_string(STDOUT, "4\n");
    LineCnt = cgc_ReadScreen(ScreenBuf);
    cgc_send_string(STDOUT, "dupr\n");
    LineCnt = cgc_ReadScreen(ScreenBuf);


    char* s = (char *)ScreenBuf[LineCnt - 2];
    s = cgc_strchr(s, ':');
    s += 2;

    int m = cgc_strtol(s, NULL, 10);
    unsigned char secret[4];
    cgc_memcpy(secret, (void *)&m, 4);

    secret[0] ^= 0x14;
    secret[1] ^= 0x15;
    secret[2] ^= 0x16;
    secret[3] ^= 0x17;

    cgc_send_string(STDERR, (char *)s);
    cgc_send_string(STDERR, "----->\n");
    cgc_type2_submit((unsigned char *)secret, 4);
    cgc_send_string(STDOUT, "quit\n");
}
