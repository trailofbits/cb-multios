/*
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

#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "packet.h"

#define MAX_BODY_LEN 8192

packet_t* parse_packet(int fd)
{
  size_t to_read = 0;
  char *body = NULL;
  packet_t *packet = NULL;

  packet = (packet_t *) malloc(sizeof(packet_t));
  if (packet == NULL)
    goto fail;

  /* Read the packet header */
  to_read = sizeof(packet_t) - sizeof(char *);
  if (read_n(fd, (char *)packet, to_read) != to_read)
    goto fail;

  if (packet->body_len > MAX_BODY_LEN)
    goto fail;
  body = malloc(packet->body_len);
  if (body == NULL)
    goto fail;

  /* Read the packet body */
  to_read = packet->body_len;
  if (read_n(fd, body, to_read) != packet->body_len)
    goto fail;
  packet->body = body;

  if (packet->checksum != calc_checksum(packet))
    goto fail;

  return packet;

fail:
  if (body)
    free(body);
  if (packet)
    free(packet);
  return NULL;
}

packet_t* new_packet(enum type_t type, enum cmd_t cmd)
{
  packet_t *packet = (packet_t *) malloc(sizeof(packet_t));
  if (packet == NULL)
    return NULL;

  packet->type = type;
  packet->command = cmd;
  packet->checksum = 0;
  packet->body_len = 0;
  packet->body = NULL;

  return packet;
}

void free_packet(packet_t *packet)
{
  if (packet)
  {
    if (packet->body)
      free(packet->body);
    free(packet);
  }
}

unsigned short calc_checksum(packet_t *packet)
{
  char *cur = (char *)packet;
  int i, header_sz = sizeof(packet_t) - sizeof(char *);
  unsigned short checksum = 0, orig;

  orig = packet->checksum;
  packet->checksum = 0;

  for (i = 0; i < header_sz; ++i)
  {
    checksum += checksum ^ cur[i];
  }

  cur = packet->body;
  for (i = 0; i < packet->body_len; ++i)
  {
    checksum += checksum ^ cur[i];
  }

  packet->checksum = orig;
  return checksum;
}
