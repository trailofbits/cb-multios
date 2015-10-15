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

#ifndef KTY_H 
#define KTY_H

#include <libcgc.h>
#include "array.h"
#include "hashtable.h"

#define MAX_KTY_STRING 256

#define STATE_PARSING_KTY 0
#define STATE_PARSING_KEY 1
#define STATE_PARSING_STRING 2

typedef enum kty_type {
  KTY_INT = 0,
  KTY_DOUBLE = 1,
  KTY_STRING = 2,
  KTY_OBJECT = 3,
  KTY_ARRAY = 4,
  KTY_BOOLEAN = 5,
  KTY_NULL = 6,
  KTY_CAT = 7
} kty_type_t;

typedef struct kty_item {
  kty_type_t type;
  union data {
    char i_bool;
    int i_int;
    double i_double;
    struct {
      char *s;
      int len;
    } i_string;
    array_t *i_array;
    htbl_t *i_object;
  } item;
} kty_item_t;

typedef void (kty_dumps_fn) (kty_item_t *kty);
typedef kty_item_t* (kty_loads_fn) (char *str);

typedef struct kty_parser {
  unsigned int cats;
  array_t *nyan_says;
  kty_dumps_fn *dumps;
  kty_loads_fn *loads;
} kty_parser_t;

int kty_init(kty_parser_t *parser);
void free_kty_item(void *e);

void kty_dumps(kty_item_t *kty);
kty_item_t* kty_loads(char *str);

#endif
