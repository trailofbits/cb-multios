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

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <libcgc.h>
#include "permit.h"

enum __attribute__ ((__packed__)) result_t {
  RES_OK = 0x00,
  RES_ERROR = 0x10,
};

enum __attribute__ ((__packed__)) cmd_t {
  CMD_AUTH,
  CMD_NEW_PERMIT,
  CMD_NEW_PERMIT_RING,
  CMD_REFACTOR_RING,
  CMD_TEST_PERMIT,
  CMD_TEST_PERMIT_RING
};

typedef struct skey {
  char seesion_key[MASTER_KEY_LEN];
  int num_used;
} skey_t;

void handle_command(char *buf, int buf_len);
void handle_auth(char *buf, int buf_len);
void handle_new_permit(char *buf, int buf_len);
void handle_new_permit_ring(char *buf, int buf_len);
void handle_refactor_ring(char *buf, int buf_len);
void handle_test_permit(char *buf, int buf_len);
void handle_test_permit_ring(char *buf, int buf_len);

#endif
