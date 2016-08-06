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

#ifndef MEMO_H
#define MEMO_H

#include <wrapper.h>
#include <libcgc.h>
#include <string.h>

#define MAX_MEMO_SUBJECT  32
#define MAX_MEMO_BODY     4096
#define MAX_MEMO_ID       500

enum mop_t {
  MOP_VIEW = 0,
  MOP_UPDATE = 1,
  MOP_DELETE = 2
};

enum mresult_t {
  MRES_OK = 0,
  MRES_ERROR_SUBJECT = 1,
  MRES_ERROR_DATE = 2,
  MRES_ERROR_PRIORITY = 3,
  MRES_ERROR_BODY = 4,
  MRES_ERROR_MEMO_ID = 5,
  MRES_ERROR_INTERNAL = 6
};

enum priority_t {
  PRI_LOW = 0,
  PRI_NORMAL = 1,
  PRI_HIGH = 2,
};

typedef struct date {
  int year;
  int month;
  int date;
} date_t;

typedef struct memo memo_t;
typedef enum mresult_t (*memo_fn) (memo_t *);

struct memo {
  int id;
  char subject[MAX_MEMO_SUBJECT];
  date_t date;
  enum priority_t priority;
  char *body;
  memo_fn mfuns[3];
};

memo_t* new_memo(memo_fn view_fn, memo_fn update_fn, memo_fn delete_fn);
enum mresult_t default_view_memo(memo_t *memo);
enum mresult_t default_update_memo(memo_t *memo);
enum mresult_t default_delete_memo(memo_t *memo);

enum mresult_t validate_memo(memo_t *memo);

#endif
