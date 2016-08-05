#include <libpov.h>

int send_string(int fd, char* s)
{
  unsigned l = strlen(s);

  if (!l)
    return -1;

  return transmit_all(fd, s, strlen(s));
}

uint32_t ReadScreen(unsigned char** Lines)
{
#ifdef DEBUG
  return 0;
#endif
  unsigned char* read;
  unsigned read_len;
  unsigned LineCnt = 0;

  for (;;)
  {
    send_string(STDERR, "READING\n");
    delimited_read(STDIN, &read, &read_len, (unsigned char *)"\n", 1);
    Lines[LineCnt++] = read;

    if (!strncmp("----", (const char *)read, 4)  || !strncmp("Erro", (const char *)read, 4))
      break;
    send_string(STDERR, (char *)read);
  }

  send_string(STDERR, "DONE\n");
  return LineCnt;;
}

#define MAX_LINES 0x1000
int main()
{
    type2_vals t2v;
    unsigned char* ScreenBuf[MAX_LINES];
    unsigned LineCnt;

#ifndef DEBUG
    type2_negotiate(&t2v);
#else
    (void)t2v;
#endif

    transmit_all(STDOUT, "l23k", 4);

    send_string(STDERR, "GOING\n");
    LineCnt = ReadScreen(ScreenBuf);
    for (unsigned Index = 0; Index < 64; ++Index)
    {
      send_string(STDERR, "LOOP\n");
      send_string(STDOUT, "0\n");
      LineCnt = ReadScreen(ScreenBuf);
    }

    send_string(STDOUT, "shuf\n");
    LineCnt = ReadScreen(ScreenBuf);
    send_string(STDOUT, "4986\n");
    LineCnt = ReadScreen(ScreenBuf);
    send_string(STDOUT, "4\n");
    LineCnt = ReadScreen(ScreenBuf);
    send_string(STDOUT, "dupr\n");
    LineCnt = ReadScreen(ScreenBuf);


    char* s = (char *)ScreenBuf[LineCnt - 2];
    s = strchr(s, ':');
    s += 2;

    int m = strtol(s, NULL, 10);
    unsigned char secret[4];
    memcpy(secret, (void *)&m, 4);

    secret[0] ^= 0x14;
    secret[1] ^= 0x15;
    secret[2] ^= 0x16;
    secret[3] ^= 0x17;

    send_string(STDERR, (char *)s);
    send_string(STDERR, "----->\n");
    type2_submit((unsigned char *)secret, 4);
    send_string(STDOUT, "quit\n");
}
