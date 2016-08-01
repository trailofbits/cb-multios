/*
 * Author: Brian Pak <brian.pak@kapricasecurity.com>
 *
 * Copyright (c) 2014 Kaprica Security, Inc.
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

#include <libcgc.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "pkk.h"

#define STEG_TAG  0xD86B74D1
#define PPM_TAG   0x03259036
#define MODE_TAG  0xBB85A71C
#define TEXT_TAG  0xBFEFDDE9
#define END_TAG   0xAB660AF0

#define SECRET_TAG      0xB58333C6
#define SECRET_END_TAG  0x0507A018

#define MODE_EM   0x1337
#define MODE_EX   0x7331

#define MAX_PPM_SIZE  (1 * 1024 * 1024)
#define MAX_TEXT_LEN  1000

#define GET_BIT(b, i) (((b) >> (8 - (i))) & 1)

typedef struct input {
  unsigned int total_size;
  unsigned int pkk_size;
  pkk_t *pkk_data;
  unsigned short mode;
  unsigned short text_size;
  char *text_data;
} input_t;

int read_n(int fd, char *buf, size_t len)
{
  size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    size_t rx;
    if (receive(fd, c, 1, &rx) != 0 || rx == 0)
      break;
    c++;
  }
  return c - buf;
}

int readuntil(int fd, char *buf, size_t len, char delim)
{
  size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    size_t rx;
    if (receive(fd, c, 1, &rx) != 0 || rx == 0)
      break;
    if (*(c++) == delim)
      break;
  }
  *(c-1) = '\0';
  return c - buf;
}

void cleanup_input(input_t *input)
{
  if (input)
  {
    if (input->pkk_data)
      free_pkk(input->pkk_data);
    if (input->text_data)
      free(input->text_data);
    free(input);
  }
}

input_t* parse_input()
{
  unsigned int dword;
  unsigned short word;
  input_t *input = NULL;
  unsigned int total_bytes = 0;

  input = (input_t *) malloc(sizeof(input_t));
  if (input == NULL)
    goto fail;

  if (read_n(STDIN, (char *)&dword, sizeof(dword)) != sizeof(dword) || dword != STEG_TAG)
    goto fail;
  total_bytes += sizeof(dword);
  if (read_n(STDIN, (char *)&dword, sizeof(dword)) != sizeof(dword))
    goto fail;
  total_bytes += sizeof(dword);
  input->total_size = dword;
  if (read_n(STDIN, (char *)&dword, sizeof(dword)) != sizeof(dword) || dword != PPM_TAG)
    goto fail;
  total_bytes += sizeof(dword);
  if (read_n(STDIN, (char *)&dword, sizeof(dword)) != sizeof(dword))
    goto fail;
  total_bytes += sizeof(dword);
  input->pkk_size = dword;
  if (input->pkk_size > 0 && input->pkk_size < MAX_PPM_SIZE)
  {
    char *pkk_data = malloc(input->pkk_size);
    if (read_n(STDIN, pkk_data, input->pkk_size) != input->pkk_size)
      goto fail;
    input->pkk_data = parse_pkk(pkk_data, input->pkk_size);
    if (input->pkk_data == NULL)
      goto fail;
    total_bytes += input->pkk_size;
  }
  if (read_n(STDIN, (char *)&dword, sizeof(dword)) != sizeof(dword) || dword != MODE_TAG)
    goto fail;
  total_bytes += sizeof(dword);
  if (read_n(STDIN, (char *)&word, sizeof(word)) != sizeof(word))
    goto fail;
  total_bytes += sizeof(word);
  input->mode = word;
  if (read_n(STDIN, (char *)&dword, sizeof(dword)) != sizeof(dword) || dword != TEXT_TAG)
    goto fail;
  total_bytes += sizeof(dword);
  if (read_n(STDIN, (char *)&word, sizeof(word)) != sizeof(word))
    goto fail;
  total_bytes += sizeof(word);
  input->text_size = word;
  if (input->text_size > 0)
  {
    if (input->text_size > MAX_TEXT_LEN)
      goto fail;
    input->text_data = malloc(input->text_size);
    if (read_n(STDIN, (char *)input->text_data, input->text_size) != input->text_size)
      goto fail;
    total_bytes += input->text_size;
  }
  if (read_n(STDIN, (char *)&dword, sizeof(dword)) != sizeof(dword) || dword != END_TAG)
    goto fail;
  total_bytes += sizeof(dword);

  if (total_bytes != input->total_size)
    goto fail;

  return input;

fail:
  cleanup_input(input);
  return NULL;
}

int embed_text(pkk_t *pkk, char *text, unsigned short len)
{
  int size;
  char *message, *cur;
  char *pixel;

  if (pkk && text && pkk->pixels)
  {
    pixel = (char *) pkk->pixels;
    size = sizeof(int) * 2 + sizeof(short) + len;
    if (pkk->width * pkk->height * sizeof(pixel_t) / 8 < size)
      return -1;
    message = malloc(size);
    if (message == NULL)
      return -1;
    cur = message;
    *(int *)cur = SECRET_TAG;
    cur += sizeof(int);
    *(short *)cur = len;
    cur += sizeof(short);
    memcpy(cur, text, len);
    cur += len;
    *(int *)cur = SECRET_END_TAG;

    int i, j;
    for (i = 0; i < size; ++i)
    {
      char c = message[i];

      for (j = 1; j <= 8; ++j)
      {
        int lsb = *pixel & 1;
        if (lsb != GET_BIT(c, j))
        {
          if (lsb)
            *pixel = *pixel & ~1;
          else
            *pixel = *pixel | 1;
        }
        pixel++;
      }
    }

    return 0;
  }

  return -1;
}

char recover_byte(char **pixel)
{
  int j;
  char c = '\0';
  for (j = 0; j < 8; ++j)
  {
    c = c << 1;
    int lsb = **pixel & 1;
    c |= lsb;
    (*pixel)++;
  }

  return c;
}

int extract_text(pkk_t *pkk, char *buf)
{
  char c;
  char *pixel;
  if (pkk && buf && pkk->pixels)
  {
    int i, j, tag = 0;
    short text_size;
    pixel = (char *) pkk->pixels;

    for (i = 0; i < 4; ++i)
    {
      c = recover_byte(&pixel);
      tag |= ((c << 8*i) & (0xFF << 8*i));
    }
    if (tag != SECRET_TAG)
      return -1;

    for (i = 0; i < 2; ++i)
    {
      c = recover_byte(&pixel);
      text_size |= ((c << 8*i) & (0xFF << 8*i));
    }

    /* Bug: Not checking text_size */
#if PATCHED
    for (i = 0; i < text_size && i < MAX_TEXT_LEN; ++i)
#else
    for (i = 0; i < text_size; ++i)
#endif
    {
      c = recover_byte(&pixel);
      buf[i] = c;
    }

    tag = 0;
    for (i = 0; i < 4; ++i)
    {
      c = recover_byte(&pixel);
      tag |= ((c << 8*i) & (0xFF << 8*i));
    }
    if (tag != SECRET_END_TAG)
      return -1;

    return 0;
  }

  return -1;
}

int main()
{
  char text[MAX_TEXT_LEN];
  int out_len;
  char *output;
  input_t *input;

  if ((input = parse_input()) == NULL)
  {
    printf("[ERROR] Failed to parse input.\n");
    return -1;
  }

  switch (input->mode)
  {
    case MODE_EM:
      if (embed_text(input->pkk_data, input->text_data, input->text_size) != 0)
        printf("[ERROR] Failed to embed your message.\n");
      else
      {
        output = output_pkk(input->pkk_data, &out_len);
        if (output)
        {
          transmit(STDOUT, output, out_len, NULL);
          free(output);
        }
      }
      break;
    case MODE_EX:
      if (extract_text(input->pkk_data, text) != 0)
        printf("[ERROR] Failed to extract the message.\n");
      else
      {
        printf("Secret Text: %s\n", text);
      }
      break;
    default:
      printf("[ERROR] Invalid mode.\n");
      break;
  }

  cleanup_input(input);
  return 0;
}
