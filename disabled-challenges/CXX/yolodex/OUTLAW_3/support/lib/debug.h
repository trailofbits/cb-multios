/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#ifdef DEBUG

#include "string.h"
#include "conv.h"

// //
// The following is verbatim from EAGLE_00004, but isn't included in the 
// released binary (DEBUG is not defined), so this reuse shouldn't be a concern.
// //

#define _FILE_STATE_OPEN  1
#define _FILE_STATE_ERROR 2
#define _FILE_STATE_EOF   4
#define _FILE_HAVE_LAST   8

typedef struct _FILE {
   int fd;
   int state;
   int last;
} FILE;

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

typedef __builtin_va_list va_list;
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) __builtin_va_arg(ap, type)

#define IS_DIGIT     1
#define IS_UPPER     2
#define IS_LOWER     4
#define IS_SPACE     8
#define IS_XDIGIT    16
#define IS_CTRL      32
#define IS_BLANK     64

#define IS_ALPHA     (IS_LOWER | IS_UPPER)
#define IS_ALNUM     (IS_ALPHA | IS_DIGIT)

static unsigned char type_flags[256] = {
     0, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL,
     IS_CTRL, IS_SPACE | IS_BLANK, IS_SPACE, IS_SPACE, IS_SPACE, IS_SPACE, IS_CTRL, IS_CTRL,

     IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL,
     IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL, IS_CTRL,

     IS_SPACE | IS_BLANK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

     IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT,
     IS_DIGIT | IS_XDIGIT, IS_DIGIT | IS_XDIGIT, 0, 0, 0, 0, 0, 0,

     0, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER | IS_XDIGIT, IS_UPPER,
     IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER,

     IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER, IS_UPPER,
     IS_UPPER, IS_UPPER, IS_UPPER, 0, 0, 0, 0, 0,

     0, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER | IS_XDIGIT, IS_LOWER,
     IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER,

     IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER, IS_LOWER,
     IS_LOWER, IS_LOWER, IS_LOWER, 0, 0, 0, 0, 0,
};

int isalpha(int c);

int isdigit(int c);

int isxdigit(int c);

// int toupper(int c);

int vfprintf(FILE * stream, const char *format, va_list ap);

int fprintf(FILE * stream, const char *format, ...);

struct _fd_printer {
   int fd;
   int err;
   unsigned int count;
};

//if flag != 0 return number of chars output so far
static unsigned int fd_printer(char ch, void *_fp, int flag);

#define STATE_NORMAL 0
#define STATE_ESCAPE 1
#define STATE_PERCENT 2
#define STATE_OCTAL 3
#define STATE_HEX 4
#define STATE_FLAGS 5
#define STATE_WIDTH 6
#define STATE_PRECISION 7
#define STATE_LENGTH 8
#define STATE_CONVERSION 9
#define STATE_WIDTH_ARG 10
#define STATE_WIDTH_VAL 11
#define STATE_PRECISION_ARG 12
#define STATE_PRECISION_VAL 13
#define STATE_NARG 15

#define FLAGS_TICK 1
#define FLAGS_LEFT 2
#define FLAGS_SIGN 4
#define FLAGS_SPACE 8
#define FLAGS_HASH 16
#define FLAGS_ZERO 32

#define LENGTH_H 1
#define LENGTH_HH 2
#define LENGTH_L 3
#define LENGTH_J 5
#define LENGTH_Z 6
#define LENGTH_T 7
#define LENGTH_CAPL 8

static char *r_utoa(unsigned int val, char *outbuf);

//outbuf needs to be at least 22 chars
static char *r_llotoa(unsigned long long val, char *outbuf);

static char *r_otoa(unsigned int val, char *outbuf);

//outbuf needs to be at least 22 chars
static char *r_llxtoa(unsigned long long val, char *outbuf, int caps);

static char *r_xtoa(unsigned int val, char *outbuf, int caps);

static int hex_value_of(char ch);

//func is responsible for outputing the given character
//user is a pointer to data required by func
static void printf_core(unsigned int (*func)(char, void *, int), void *user, const char *format, va_list ap);

int vdprintf(int fd, const char *format, va_list ap);

///////////////

extern const char *CB_NAME;

#define DBG_SIMPLE(args...) \
  fprintf(stderr, args);

#define DBG(args...) \
  fprintf(stderr, "%s | %s:%u @ %s() | ", CB_NAME, __FILE__, __LINE__, __func__); \
  DBG_SIMPLE(args);

#define ERR(args...) \
  DBG(args); \
  if(SUCCESS == ret) { ret = -1; }\
  goto bail;

#define MSG_DUMP(msg) \
  fprintf(stderr, "%s |  msg_dump:\n", CB_NAME); \
  fprintf(stderr, "%s |    msg.dst .... 0x%08x (%d)\n", CB_NAME, msg.dst, msg.dst); \
  fprintf(stderr, "%s |    msg.x ...... 0x%08x (%d)\n", CB_NAME, msg.x, msg.x); \
  fprintf(stderr, "%s |    msg.y ...... 0x%08x (%d)\n", CB_NAME, msg.y, msg.y); \
  fprintf(stderr, "%s |    msg.op ..... 0x%08x\n", CB_NAME, msg.op); \
  fprintf(stderr, "%s |    msg.nmb .... 0x%08x (%d)\n", CB_NAME, msg.nmb, msg.nmb); \
  fprintf(stderr, "%s |    msg.result\n", CB_NAME, msg.result, msg.result >> 32); \
  fprintf(stderr, "%s |      answer ... 0x%08x\n", CB_NAME, msg.result >> 32); \
  fprintf(stderr, "%s |      token .... 0x%08x\n", CB_NAME, msg.result); \

#else /* DEBUG */

#define DBG_SIMPLE(args...) do { } while (0);
#define DBG(args...) do { } while (0);
#define ERR(args...) do { } while (0);
#define MSG_DUMP(args...) do { } while (0);

#endif /* DEBUG */
