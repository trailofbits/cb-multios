/*
 * Copyright (c) 2015 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_string.h"

#define BLOCK_SIZE 512

static const char user_codes[] = "iCT3gePALvnIHM7tiDFtZyK5d9HmEH+flOccF+Xzpyo4Vwl39UrOlvma31gToV54Jq7HQ2uyznvZaSgRnqb8pxqG0JjTK+EkOLKR4L3gBHn1ape0jqBuzqINm956fkh/LmeIZnNbxiPiWA1SV1KAy2U7/3WErZGE3HlMKNcivjT+Je/exrnCAKW5r7J8G7VEYfv/dGHe/jJ8bDD+vUEyGhQRV3GOG4+B7TbfaUZTDSWClMKxnOGWHN8JATRw1MsVXxHTVyqK+kf/DS2MmXiaxJprWeDn+jhWpO964+FW2uYn/U/EJ2zHNDwkBw45rTqx/VeanI1KnEndeTHvfYEVUQ==";

static const unsigned char *secret_page = (const unsigned char *)0x4347C000;

#define CHUNK_SIZE 16
static unsigned char txbuf[CHUNK_SIZE];
static int txcnt;

void cgc_send_flush() {
  cgc_size_t sent = 0;
  while (txcnt != sent)
  {
      cgc_size_t tx;
      if (cgc_transmit(STDOUT, txbuf + sent, txcnt - sent, &tx) != 0)
          break;
      sent += tx;
  }
  txcnt = 0;
}

void cgc_poop_page_perfectly(void)
{
  for (cgc_size_t i = 0; i < 0x1000; i += 4)
  {
    if (txcnt == CHUNK_SIZE)
      cgc_send_flush();
    txbuf[txcnt++] = secret_page[i];
  }
  cgc_send_flush();
}

void *cgc_xcalloc(cgc_size_t nmemb, cgc_size_t size)
{
  void* mem = cgc_calloc(nmemb, size);
  if (!mem)
  {
    cgc_transmit(2, "calloc failed\n", cgc_strlen("calloc_failed\n"), NULL);
    cgc_exit(1);
  }

  return mem;
}

enum
{
  NORMAL = '0',
  HARD,
  SYMBOLIC,
  CHAR,
  BLOCK,
  DIRECTORY,
  FIFO,
  CONTIGUOUS_FILE,
};

typedef struct glue_t glue_t;
struct glue_t
{
  char f_name[100 + 1];
  char f_mode[8];
  char uid[8];
  char gid[8];
  char f_size[12];
  char mtime[12];
  char chk_sum[8];
  char type[1];
  char l_name[100 + 1];
  char indicator[6 + 1];
  char version[2];
  char u_name[32 + 1];
  char g_name[32 + 1];
  char d_maj[8];
  char d_min[8];
  char f_prefix[100 + 1];
};

cgc_size_t cgc_read_n(int fd, char* buf, cgc_size_t n, int* err)
{
  cgc_size_t n_read = 0;
  cgc_size_t rx_amt = 0;
  if (err)
    *err = 0;

  while (n_read < n)
  {
    if (cgc_receive(fd, buf + n_read, n - n_read, &rx_amt) != 0)
    {
      if (err)
        *err = 1;
      break;
    }

    if (rx_amt == 0)
      break;

    n_read += rx_amt;
  }

  return n_read;
}

void cgc_reverse(char* s)
{
  char* tmp = cgc_xcalloc(cgc_strlen(s) + 1, 1);
  for (
      int i = cgc_strlen(s) - 1, j = 0;
      i >= 0;
      i--, j++
  )
    tmp[j] = s[i];
  cgc_strcpy(s, tmp);
}

cgc_size_t cgc_read_ascii_octal(char* buf, int size, int* err)
{
  cgc_size_t val = 0;
  char* tmp = cgc_xcalloc(size, 1);
  for (cgc_size_t i = 0; i < size - 1; i++)
    tmp[i] = buf[i];
  cgc_reverse(tmp);

  for (cgc_size_t i = 0; i < size - 1; i++)
  {
    if (!tmp[i])
      break;

    if (!(tmp[i] >= '0' && tmp[i] <= '7'))
    {
      if (err)
        *err = 1;
      break;
    }

    cgc_size_t x = 1;
    for (cgc_size_t j = 0; j < i; j++)
      x *= 8;

    val += x * (tmp[i] - 0x30);
  }

  return val;
}

char* cgc_map_type(int type)
{
  switch(type)
  {
    case 0:
    case NORMAL:
      return "Normal";
    case HARD:
      return "Hard link";
    case SYMBOLIC:
      return "Symbolic link";
    case CHAR:
      return "Character device";
    case BLOCK:
      return "Block device";
    case DIRECTORY:
      return "Directory";
    case FIFO:
        return "FIFO";
    case CONTIGUOUS_FILE:
    default:
        return "Unknown";
  };
}

const char* cgc_get_user_code(int uid, int gid)
{
  cgc_fprintf(cgc_stderr, "xxx- %d - %d\n", uid, gid);
  cgc_fprintf(cgc_stderr, "xxx- %x\n", &user_codes[uid * gid]);
#ifdef PATCHED_1
  if (uid * gid < 0 || uid * gid >= sizeof(user_codes))
    return "No user info";
#endif
  return (char *)&user_codes[uid * gid];
}

cgc_size_t cgc_sent_n(int fd, char* buf, cgc_size_t cnt, int* err)
{
  cgc_size_t sent = 0;
  cgc_size_t tx_amt = 0;
  if (err)
    *err = 1;

  while (sent < cnt)
  {
    if(cgc_transmit(fd, buf + sent, cnt - sent < 64 ? cnt - sent : 64, &tx_amt) != 0)
    {
      if (err)
        *err = 1;
      break;
    }

    if (tx_amt == 0)
      break;

    sent += tx_amt;
  }

  return sent;
}

void cgc_print_entry(glue_t* block)
{
  cgc_printf("name:\t\t%s\n", block->f_name);
  cgc_printf("    mode:\t\t%s\n", block->f_mode);
  cgc_printf("    uid:\t\t%d\n", cgc_read_ascii_octal(block->uid, 8, NULL));
  cgc_printf("    gid:\t\t%d\n", cgc_read_ascii_octal(block->gid, 8, NULL));
  cgc_printf("    user_code:\t\t");
  cgc_sent_n(1, (char *)cgc_get_user_code(cgc_read_ascii_octal(block->uid, 8, NULL), cgc_read_ascii_octal(block->gid, 8, NULL)), 4, NULL);
  cgc_printf("\n");
  cgc_printf("    size:\t\t%d\n", cgc_read_ascii_octal(block->f_size, 12, NULL));
  cgc_printf("    mtime:\t\t%d\n", cgc_read_ascii_octal(block->mtime, 12, NULL));
  cgc_printf("    type:\t\t%s\n", cgc_map_type(block->type[0]));
  cgc_printf("    link_name:\t\t%s\n", block->l_name);
  cgc_printf("    magic:\t\t%s\n", block->indicator);
  cgc_printf("    version:\t\t%d\n", cgc_read_ascii_octal(block->version, 2, NULL));
  cgc_printf("    owner_name:\t\t%s\n", block->u_name);
  cgc_printf("    group_name:\t\t%s\n", block->g_name);
  cgc_printf("    dev_major:\t\t%d\n", cgc_read_ascii_octal(block->d_maj, 8, NULL));
  cgc_printf("    dev_minor:\t\t%d\n", cgc_read_ascii_octal(block->d_min, 8, NULL));
  cgc_printf("    prefix:\t\t%s\n", block->f_prefix);
}

glue_t* cgc_initialize(char* buf)
{
  char* p = buf;

  glue_t* new = cgc_xcalloc(sizeof(glue_t), 1);

  cgc_memcpy(new->f_name    , p, 100  ); p += 100;
  cgc_memcpy(new->f_mode    , p, 8    ); p += 8;
  cgc_memcpy(new->uid       , p, 8   ); p += 8;
  cgc_memcpy(new->gid       , p, 8    ); p += 8;
  cgc_memcpy(new->f_size    , p, 12   ); p += 12;
  cgc_memcpy(new->mtime     , p, 12   ); p += 12;
  cgc_memcpy(new->chk_sum   , p, 8    ); p += 8;
  cgc_memcpy(new->type      , p, 1    ); p += 1;
  cgc_memcpy(new->l_name    , p, 100  ); p += 100;
  cgc_memcpy(new->indicator , p, 6    ); p += 6;
  cgc_memcpy(new->version   , p, 2    ); p += 2;
  cgc_memcpy(new->u_name    , p, 32   ); p += 32;
  cgc_memcpy(new->g_name    , p, 32   ); p += 32;
  cgc_memcpy(new->d_maj     , p, 8    ); p += 8;
  cgc_memcpy(new->d_min     , p, 8    ); p += 8;
  cgc_memcpy(new->f_prefix  , p, 100  ); p += 100;

  return new;
}

int cgc_empty_block(char* buf)
{
  for (cgc_size_t i = 0; i < BLOCK_SIZE; i++)
    if (buf[i] != 0)
      return 0;
  return 1;
}

void cgc_skip_data(int fd, cgc_ssize_t n, int* err)
{
  char* sink[BLOCK_SIZE];

  while (n > 0 && !*err)
  {
    cgc_read_n(STDIN, (char *)sink, BLOCK_SIZE, err);
    n -= BLOCK_SIZE;
  }
}

int main(int cgc_argc, char *cgc_argv[]) {
  int err;
  int empty_cnt = 0;
  char block_buf[BLOCK_SIZE];

  cgc_poop_page_perfectly();

  for (;;)
  {
    if (cgc_read_n(STDIN, block_buf, BLOCK_SIZE, &err) != BLOCK_SIZE || err)
      break;

    if (cgc_empty_block(block_buf))
    {
      empty_cnt++;
      if (empty_cnt == 2)
        break;
      else
        continue;
    }
    else
      empty_cnt = 0;

    glue_t* block = cgc_initialize(block_buf);

    cgc_print_entry(block);

    cgc_ssize_t block_size = cgc_read_ascii_octal(block->f_size, 12, &err);
    if (err)
      break;

    cgc_skip_data(STDIN, block_size, &err);
    if (err)
      break;

    cgc_free(block);
  }
}
