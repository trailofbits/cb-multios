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

#ifndef PACKET_H
#define PACKET_H

enum __attribute__ ((__packed__)) type_t {
  T_REQUEST,
  T_RESPONSE
};

enum __attribute__ ((__packed__)) cmd_t {
  CMD_REGISTER,
  CMD_LOGIN,
  CMD_LIST,
  CMD_VIEW,
  CMD_SEND,
  CMD_DELETE,
  CMD_QUIT
};

typedef struct packet {
  enum type_t type;
  enum cmd_t command;
  unsigned short checksum;
  unsigned int body_len;
  char *body;
} packet_t;

packet_t* cgc_parse_packet(int fd);
packet_t* cgc_new_packet(enum type_t, enum cmd_t);
void cgc_free_packet(packet_t *);

unsigned short cgc_calc_checksum(packet_t *);

#endif
