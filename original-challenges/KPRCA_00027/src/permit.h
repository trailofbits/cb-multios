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

#ifndef PERMIT_H
#define PERMIT_H

#include <libcgc.h>
#include <string.h>

#define MAX_SPOT_NUMBER 200
#define MAX_NUM_PERMITS 5
#define MAX_BUF_LEN     64
#define MASTER_KEY_LEN  16

enum __attribute__ ((__packed__)) presult_t {
  PRES_OK = 0x00,
  PRES_ERROR = 0x10,
  PRES_EXPIRED = 0x20,
  PRES_INVALID_LICENSE = 0x30,
  PRES_INVALID_TOKEN = 0x40,
  PRES_INVALID_SPOT = 0x50
};

typedef struct __attribute__ ((__packed__)) ppermit {
  char permit_token[8];
  char license_number[10];
  int num_entrances;
  int spot_number;
} ppermit_t;

typedef struct __attribute__ ((__packed__)) ppring {
  int num_permits;
  ppermit_t permits[MAX_NUM_PERMITS];
} ppring_t;

ppermit_t* permit_new(char *license_number, int num_entrances, int spot_number);
ppring_t* pring_new(int num_permits, ppermit_t permits[]);
ppring_t* pring_refactor(ppring_t *pring);
int permit_test(ppermit_t *permit, int spot_number, char *license_number);
int pring_test(ppring_t *pring, int spot_numbers[], char* license_numbers);
void destroy_permit(ppermit_t *permit);
void destroy_permit_ring(ppring_t *pring);

#endif
