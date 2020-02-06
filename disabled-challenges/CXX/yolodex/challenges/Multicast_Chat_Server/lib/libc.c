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

#include "libcgc.h"
#include "cgc_libc.h"

cgc_ssize_t
cgc_read_all(int fd, void *buf, cgc_size_t n)
{
    cgc_ssize_t ret = 0;
    cgc_size_t cgc_read;

    while (n) {
        if (cgc_receive(fd, (char *)(buf + ret), n, &cgc_read) != 0)
            return -1;

        n -= cgc_read;
        ret += cgc_read;
    }

    return ret;
}

cgc_ssize_t
cgc_write_all(int fd, void *buf, cgc_size_t n)
{
    cgc_ssize_t ret = 0;
    cgc_size_t written;

    while (n) {
        if (cgc_transmit(fd, (char *)(buf + ret), n, &written) != 0)
            return -1;

        n -= written;
        ret += written;
    }

    return ret;
}

cgc_ssize_t
cgc_read_line(int fd, char **buf)
{
    // This should be placed in BSS
    static char scratch_page[PAGE_SIZE];

    char c = '\0';
    cgc_ssize_t ret = 0;
    cgc_size_t cgc_read;

    if (!buf)
        return -1;

    while (c != '\n' && ret < PAGE_SIZE - 1) {
        //if (cgc_receive(fd, &c, 1, &cgc_read) != 0 || cgc_read != 1)
        //    return -1;


        scratch_page[ret++] = c;
    }

    // Null-terminate string
    if ((*buf = cgc_calloc(ret + 1)) == NULL)
        return -1;

    cgc_memcpy(*buf, scratch_page, ret);
    return ret;
}

void *
cgc_memset(void *ptr_, int val, cgc_size_t n)
{
    unsigned char *ptr = ptr_;
    while (n--)
        *ptr++ = (unsigned char)val;
    return ptr_;
}

void *
cgc_memcpy(void *dst_, const void *src_, cgc_size_t n)
{
    unsigned char *dst = dst_;
    const unsigned char *src = src_;
    while (n--)
        *dst++ = *src++;
    return dst_;
}

void *
cgc_memmove(void *dst_, const void *src_, cgc_size_t n)
{
    unsigned char *dst = dst_;
    const unsigned char *src = src_;

    if (dst == src)
        return dst;
    else if (src < dst)
        while (n--)
            dst[n] = src[n];
    else
        while (n--)
            *dst++ = *src++;

    return dst_;
}

int
cgc_memcmp(const void *a_, const void *b_, cgc_size_t n)
{
    const unsigned char *a = a_;
    const unsigned char *b = b_;

    while (n--)
        if (*a++ != *b++)
            return *(a - 1) - *(b - 1);

    return 0;
}

cgc_size_t
cgc_strlen(const char *s) {
    cgc_size_t ret = 0;
    while (*s++)
        ret++;
    return ret;
}

cgc_size_t
cgc_strnlen(const char *s, cgc_size_t n)
{
    cgc_size_t ret = 0;
    while (n-- && *s++)
        ret++;
    return ret;
}

int
cgc_strcmp(const char *a, const char *b)
{
    for (; *a && *a == *b; a++, b++)
        ;
    return *(const unsigned char *)a - *(const unsigned char *)b;
}

int
cgc_strncmp(const char *a, const char *b, cgc_size_t n)
{
    for (; --n && *a && *a == *b; a++, b++)
        ;
    return *(const unsigned char *)a - *(const unsigned char *)b;
}

char *
cgc_strcpy(char *dst, const char *src)
{
    cgc_size_t i = 0;
    for (; src[i]; i++)
        dst[i] = src[i];
    dst[i] = '\0';
    return dst;
}

char *
cgc_strncpy(char *dst, const char *src, cgc_size_t n)
{
    cgc_size_t i = 0;
    for (; i < n && src[i]; i++)
        dst[i] = src[i];
    for (; i < n; i++)
        dst[i] = '\0';

    return dst;
}

char *
cgc_strcat(char *dst, const char *src)
{
    char *ret = dst;
    dst += cgc_strlen(dst);
    cgc_strcpy(dst, src);
    return ret;
}

char *
cgc_strncat(char *dst, const char *src, cgc_size_t n)
{
    char *ret = dst;
    dst += cgc_strlen(dst);
    cgc_strncpy(dst, src, n);
    dst[n] = '\0';
    return ret;
}

char *
cgc_strchr(const char *s, char c)
{
    for (; *s; s++)
        if (*s == c)
            return (char *)s;
    return NULL;
}

char *
cgc_strrchr(const char *s, char c)
{
    const char *orig_s = s;
    for (; *s; s++)
        ;
    for (; s >= orig_s; s--)
        if (*s == c)
            return (char *)s;
    return NULL;
}

char *
cgc_strtok(char *s, char d)
{
    static char *prev = NULL;
    char *token, *ret;

    if (s == NULL && (prev == NULL || cgc_strlen(prev) == 0))
        return NULL;

    if (prev == NULL || cgc_strlen(prev) == 0)
        prev = s;

    while (*prev == d)
        prev++;

    if (cgc_strlen(prev) == 0)
        return NULL;

    ret = prev;
    if ((token = cgc_strchr(prev, d)) != NULL) {
        *token = '\0';
        prev = token + 1;
    } else {
        prev = NULL;
    }

    return ret;
}

char
cgc_to_hex(unsigned char v)
{
    if (v < 10)
        return '0' + v;
    else if (v < 16)
        return 'a' + (v - 10);
    else
        return '\0';
}

unsigned char
cgc_to_bin(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    else if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    else
        return 0;
}

char *
cgc_bin_to_hex(char *dst, const void *src_, cgc_size_t n)
{
    cgc_size_t i;
    const unsigned char *src = src_;

    for (i = 0; i < n; i++) {
        *dst++ = cgc_to_hex(src[i] >> 4);
        *dst++ = cgc_to_hex(src[i] & 0xf);
    }

    return dst;
}

unsigned int
cgc_hex_to_uint(char *s)
{
    unsigned int ret = 0;
    cgc_size_t i;

    for (i = 4; i > 0; i--) {
        ret = (ret << 8) | (cgc_to_bin(s[2 * (i - 1)]) << 4);
        ret |= cgc_to_bin(s[2 * (i - 1) + 1]);
    }

    return ret;
}

char *
cgc_itoa(int val, char *s)
{
    char tmp = '\0';
    char *t = s;
    char *ret = s;

    if (val == 0)
        return cgc_strcpy(s, "0");

    if (val < 0) {
        s++;
        *t++ = '-';
        val = -val;
    }

    while (val) {
        *t++ = '0' + val % 10;
        val /= 10;
    }
    *t-- = '\0';

    while (t - s > 0) {
        tmp = *s;
        *s++ = *t;
        *t-- = tmp;
    }

    return ret;
}

int cgc_atoi(char *buf){
    int dir = 1;
    int start = 0;
    if(buf[start] == '-')
        dir = -1;

    int final = 0;
    for(int i = start; i < cgc_strlen(buf); ++i ){
        final = final * 10 + buf[i] - '0';
    }
    final *= dir;

    return final;
}

/* The following is verbatim from EAGLE_00004, but isn't included in the
 * released binary (DEBUG is not defined), so this reuse shouldn't be a concern.
 */
#ifdef DEBUG

#ifdef WIN
#include <stdarg.h>
#else
typedef __builtin_va_list va_list;
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#endif

static FILE std_files[3] = { {0, _FILE_STATE_OPEN}, {1, _FILE_STATE_OPEN}, {2, _FILE_STATE_OPEN} };

FILE *cgc_stdin = &std_files[0];
FILE *cgc_stdout = &std_files[1];
FILE *cgc_stderr = &std_files[2];

int vfprintf(FILE *stream, const char *format, va_list ap);
int vdprintf(int fd, const char *format, va_list ap);

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

int isalpha(int c) {
   return (type_flags[c & 0xff] & IS_ALPHA) != 0;
}

int isdigit(int c) {
   return (type_flags[c & 0xff] & IS_DIGIT) != 0;
}

int isxdigit(int c) {
   return (type_flags[c & 0xff] & IS_XDIGIT) != 0;
}

int toupper(int c) {
   if (isalpha(c)) {
      return c & ~0x20;
   }
   return c;
}

int vfprintf(FILE * stream, const char *format, va_list ap) {
   return vdprintf(stream->fd, format, ap);
}

int fprintf(FILE * stream, const char *format, ...) {
   va_list va;
   va_start(va, format);
   return vfprintf(stream, format, va);
}

int cgc_printf(const char *format, ...) {
   va_list va;
   va_start(va, format);
   return vfprintf(cgc_stdout, format, va);
}

struct _fd_printer {
   int fd;
   int err;
   unsigned int count;
};

//if flag != 0 return number of chars output so far
static unsigned int fd_printer(char ch, void *_fp, int flag) {
   struct _fd_printer *fp = (struct _fd_printer *)_fp;
   if (flag) {
      return fp->count;
   }
   else {
      fp->count++;
      cgc_transmit(fp->fd, &ch, 1, NULL);
   }
   return 0;
}

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

static char *r_utoa(unsigned int val, char *outbuf) {
   char *p = outbuf;
   *p = '0';
   while (val) {
      *p++ = (val % 10) + '0';
      val /= 10;
   }
   return p != outbuf ? (p - 1) : p;
}

//outbuf needs to be at least 22 chars
static char *r_llotoa(unsigned long long val, char *outbuf) {
   char *p = outbuf;
   *p = '0';
   while (val) {
      *p++ = (val & 7) + '0';
      val >>= 3;
   }
   return p != outbuf ? (p - 1) : p;
}

static char *r_otoa(unsigned int val, char *outbuf) {
   return r_llotoa(val, outbuf);
}

//outbuf needs to be at least 22 chars
static char *r_llxtoa(unsigned long long val, char *outbuf, int caps) {
   char *p = outbuf;
   *p = '0';
   while (val) {
      char digit = (char)(val & 0xf);
      if (digit < 10) {
         digit += '0';
      }
      else {
         digit = caps ? (digit + 'A' - 10) : (digit + 'a' - 10);
      }
      *p++ = digit;
      val >>= 4;
   }
   return p != outbuf ? (p - 1) : p;
}

static char *r_xtoa(unsigned int val, char *outbuf, int caps) {
   return r_llxtoa(val, outbuf, caps);
}

static int hex_value_of(char ch) {
   if (isdigit(ch)) {
      return ch - '0';
   }
   else if (isalpha(ch)) {
      return toupper(ch) - 'A' + 10;
   }
   return -1;
}

//func is responsible for outputing the given character
//user is a pointer to data required by func
static void printf_core(unsigned int (*func)(char, void *, int), void *user, const char *format, va_list ap) {
   int state = STATE_NORMAL;
   int flags;
   int digit_count = 0;
   int value = 0;
   char ch;
   int arg_count = 0;
   int width_value;
   int prec_value;
   int field_arg;
   int length;
   char **args = (char**)ap;
   for (ch = *format++; ch; ch = *format++) {
      switch (state) {
         case STATE_NORMAL:
            if (ch == '%') {
               state = STATE_PERCENT;
            }
            else if (ch == '\\') {
               state = STATE_ESCAPE;
            }
            else {
               func(ch, user, 0);
            }
            break;
         case STATE_ESCAPE:
            switch (ch) {
               case 'n':
                  func('\n', user, 0);
                  break;
               case 't':
                  func('\t', user, 0);
                  break;
               case 'r':
                  func('\r', user, 0);
                  break;
               case 'b':
                  func('\b', user, 0);
                  break;
               case 'f':
                  func('\f', user, 0);
                  break;
               case 'v':
                  func('\v', user, 0);
                  break;
               case '\\': case '\'': case '"':
                  func(ch, user, 0);
                  break;
               case 'x':
                  state = STATE_HEX;
                  digit_count = 0;
                  value = 0;
                  break;
               default:
                  if (ch > '0' && ch < '8') {
                     state = STATE_OCTAL;
                     digit_count = 1;
                     value = ch - '0';
                  }
                  else {
                     func(*format, user, 0);
                  }
                  break;
            }
            if (state == STATE_ESCAPE) {
               state = STATE_NORMAL;
            }
            break;
         case STATE_PERCENT:
            if (ch == '%') {
               func(ch, user, 0);
               state = STATE_NORMAL;
            }
            else {
               state = STATE_NARG;
               flags = 0;
               format--;
            }
            break;
         case STATE_OCTAL:
            if (ch > '0' && ch < '8' && digit_count < 3) {
               digit_count++;
               value = value * 8 + (ch - '0');
               if (digit_count == 3) {
                  func(value, user, 0);
                  state = STATE_NORMAL;
               }
            }
            else {
               func(value, user, 0);
               state = STATE_NORMAL;
               format--;
            }
            break;
         case STATE_HEX:
            if (isxdigit(ch) && digit_count < 2) {
               digit_count++;
               value = value * 16 + hex_value_of(ch);
               if (digit_count == 2) {
                  func(value, user, 0);
                  state = STATE_NORMAL;
               }
            }
            else {
               func(value, user, 0);
               state = STATE_NORMAL;
               format--;
            }
            break;
         case STATE_NARG:
            width_value = -1;
            prec_value = -1;
            flags = 0;
            length = 0;
            field_arg = -1;
            if (ch == '0') {
               format--;
               state = STATE_FLAGS;
               break;
            }
            if (isdigit(ch)) {
               //could be width or could be arg specifier or a 0 flag
               //width and arg values don't start with 0
               width_value = 0;
               while (isdigit(ch)) {
                  width_value = width_value * 10 + (ch - '0');
                  ch = *format++;
               }
               if (ch == '$') {
                  field_arg = width_value - 1;
                  width_value = 0;
                  state = STATE_FLAGS;
               }
               else {
                  //this was a width
                  format--;
                  state = STATE_PRECISION;
               }
            }
            else {
               format--;
               state = STATE_FLAGS;
            }
            break;
         case STATE_FLAGS:
            switch (ch) {
               case '\'':
                  flags |= FLAGS_TICK;
                  break;
               case '-':
                  flags |= FLAGS_LEFT;
                  break;
               case '+':
                  flags |= FLAGS_SIGN;
                  break;
               case ' ':
                  flags |= FLAGS_SPACE;
                  break;
               case '#':
                  flags |= FLAGS_HASH;
                  break;
               case '0':
                  flags |= FLAGS_ZERO;
                  break;
               default:
                  format--;
                  if ((flags & (FLAGS_ZERO | FLAGS_LEFT)) == (FLAGS_ZERO | FLAGS_LEFT)) {
                     //if both '-' and '0' appear, '0' is ignored
                     flags &= ~FLAGS_ZERO;
                  }
                  state = STATE_WIDTH;
                  break;
            }
            break;
         case STATE_WIDTH:
            if (ch == '*') {
               ch = *format++;
               int width_arg = 0;
               if (isdigit(ch)) {
                  while (isdigit(ch)) {
                     width_arg = width_arg * 10 + (ch - '0');
                     ch = *format++;
                  }
                  width_arg--;
                  if (ch != '$') {
                     //error
                  }
               }
               else {
                  width_arg = arg_count++;
                  format--;
               }
               width_value = (int)args[width_arg];
            }
            else if (isdigit(ch)) {
               width_value = 0;
               while (isdigit(ch)) {
                  width_value = width_value * 10 + (ch - '0');
                  ch = *format++;
               }
               format--;
            }
            else {
               //no width specified
               format--;
            }
            state = STATE_PRECISION;
            break;
         case STATE_PRECISION:
            if (ch == '.') {
               //have a precision
               ch = *format++;
               if (ch == '*') {
                  ch = *format++;
                  int prec_arg = 0;
                  if (isdigit(ch)) {
                     while (isdigit(ch)) {
                        prec_arg = prec_arg * 10 + (ch - '0');
                        ch = *format++;
                     }
                     prec_arg--;
                     if (ch != '$') {
                        //error
                     }
                  }
                  else {
                     prec_arg = arg_count++;
                     format--;
                  }
                  prec_value = (int)args[prec_arg];
               }
               else if (isdigit(ch)) {
                  prec_value = 0;
                  while (isdigit(ch)) {
                     prec_value = prec_value * 10 + (ch - '0');
                     ch = *format++;
                  }
                  format--;
               }
               else {
                  //no precision specified
                  format--;
               }
            }
            else {
               //no precision specified
               format--;
            }
            state = STATE_LENGTH;
            break;
         case STATE_LENGTH:
            switch (ch) {
               case 'h':
                  length = LENGTH_H;
                  if (*format == 'h') {
                     length++;
                     format++;
                  }
                  break;
               case 'l':
                  length = LENGTH_L;
                  if (*format == 'l') {
//                     length++;
                     format++;
                  }
                  break;
               case 'j':
                  length = LENGTH_J;
                  break;
               case 'z':
                  length = LENGTH_Z;
                  break;
               case 't':
                  length = LENGTH_T;
                  break;
               case 'L':
                  length = LENGTH_CAPL;
                  break;
               default:
                  format--;
                  break;
            }
            state = STATE_CONVERSION;
            break;
         case STATE_CONVERSION: {
            char num_buf[32];
            char *num_ptr;
            int use_caps = 1;
            int sign;
            int val;
            if (field_arg == -1) {
               field_arg = arg_count++;
            }
            switch (ch) {
               case 'd': case 'i': {
                  int len;
                  switch (length) {
                     case LENGTH_H:
                        val = (short)(int)args[field_arg];
                        sign = val < 0;
                        if (sign) {
                           val = -val;
                        }
                        num_ptr = r_utoa(val, num_buf);
                        break;
                     case LENGTH_HH:
                        val = (char)(int)args[field_arg];
                        sign = val < 0;
                        if (sign) {
                           val = -val;
                        }
                        num_ptr = r_utoa(val, num_buf);
                        break;
                     case LENGTH_L:
                     default:
                        val = (long)args[field_arg];
                        sign = val < 0;
                        if (sign) {
                           val = -val;
                        }
                        num_ptr = r_utoa(val, num_buf);
                        break;
                  }
                  len = num_ptr - num_buf + 1;
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = len;
                     if (sign || (flags & FLAGS_SIGN)) {
                        width_value++;
                     }
                  }
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                     if ((flags & FLAGS_ZERO) != 0 && prec_value < width_value) {
                        //widen precision if necessary to pad to width with '0'
                        if (sign || (flags & FLAGS_SIGN)) {
                           prec_value = width_value - 1;
                        }
                        else {
                           prec_value = width_value;
                        }
                     }
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     //number won't need leading zeros
                     flags &= ~FLAGS_ZERO;
                  }
                  if (flags & FLAGS_LEFT) {
                     if (sign) {
                        func('-', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     else if ((flags & FLAGS_SIGN) != 0) {
                        func('+', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > (prec_value + 1)) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     if (sign) {
                        func('-', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     else if ((flags & FLAGS_SIGN) != 0) {
                        func('+', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     if (width_value > prec_value) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'o': {
                  int len;
                  switch (length) {
                     case LENGTH_H:
                        num_ptr = r_otoa((unsigned short)(unsigned int)args[field_arg], num_buf);
                        break;
                     case LENGTH_HH:
                        num_ptr = r_otoa((unsigned char)(unsigned int)args[field_arg], num_buf);
                        break;
                     case LENGTH_L:
                     default:
                        num_ptr = r_otoa((unsigned long)args[field_arg], num_buf);
                        break;
                  }
                  if (flags & FLAGS_HASH) {
                     if (*num_ptr != '0') {
                        num_ptr++;
                        *num_ptr = '0';
                     }
                  }
                  len = num_ptr - num_buf + 1;
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = len;
                  }
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                     if ((flags & FLAGS_ZERO) != 0 && prec_value < width_value) {
                        //widen precision if necessary to pad to width with '0'
                        prec_value = width_value;
                     }
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     flags &= ~FLAGS_ZERO;
                  }
                  if (flags & FLAGS_LEFT) {
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > prec_value) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'u': {
                  int len;
                  switch (length) {
                     case LENGTH_H:
                        num_ptr = r_utoa((unsigned short)(unsigned int)args[field_arg], num_buf);
                        break;
                     case LENGTH_HH:
                        num_ptr = r_utoa((unsigned char)(unsigned int)args[field_arg], num_buf);
                        break;
                     case LENGTH_L:
                     default:
                        num_ptr = r_utoa((unsigned long)args[field_arg], num_buf);
                        break;
                  }
                  len = num_ptr - num_buf + 1;
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = len;
                  }
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                     if ((flags & FLAGS_ZERO) != 0 && prec_value < width_value) {
                        //widen precision if necessary to pad to width with '0'
                        prec_value = width_value;
                     }
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     flags &= ~FLAGS_ZERO;
                  }
                  if (flags & FLAGS_LEFT) {
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > prec_value) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'x':
                  use_caps = 0;  //now fall into X case
               case 'X': {
                  int len;
                  switch (length) {
                     case LENGTH_H:
                        num_ptr = r_xtoa((unsigned short)(unsigned int)args[field_arg], num_buf, use_caps);
                        break;
                     case LENGTH_HH:
                        num_ptr = r_xtoa((unsigned char)(unsigned int)args[field_arg], num_buf, use_caps);
                        break;
                     case LENGTH_L:
                     default:
                        num_ptr = r_xtoa((unsigned long)args[field_arg], num_buf, use_caps);
                        break;
                  }
                  len = num_ptr - num_buf + 1;
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = len;
                  }
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                     if ((flags & FLAGS_ZERO) != 0 && prec_value < width_value) {
                        //widen precision if necessary to pad to width with '0'
                        prec_value = width_value;
                     }
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     flags &= ~FLAGS_ZERO;
                  }
                  if (flags & FLAGS_LEFT) {
                     if (flags & FLAGS_HASH && (len != 1 || *num_ptr != '0')) {
                        func('0', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                        func(use_caps ? 'X' : 'x', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > (prec_value + 2)) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     if (flags & FLAGS_HASH && (len != 1 || *num_ptr != '0')) {
                        func('0', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                        func(use_caps ? 'X' : 'x', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     else {
                        while (width_value > prec_value) {
                           func(' ', user, 0);
                           width_value--;
                        }
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'f': case 'F':
                  break;
               case 'e': case 'E':
                  break;
               case 'g': case 'G':
                  break;
               case 'a': case 'A':
                  break;
               case 'c': {
                  unsigned char ch = (unsigned char)(unsigned int)args[field_arg];
                  if (width_value == -1) {
                     width_value = 1;
                  }
                  if (flags & FLAGS_LEFT) {
                     func((char)ch, user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > 1) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     func(ch, user, 0);
                  }
                  break;
               }
               case 's': {
                  const char *s_arg = (const char *)args[field_arg];
                  int len = cgc_strlen(s_arg);
                  if (width_value == -1) {
                     //by default min length is the entire string
                     width_value = len;
                  }
                  if (prec_value == -1 || prec_value > len) {
                     //by default max is entire string but no less than width
                     prec_value = len;
                  }
                  if (flags & FLAGS_LEFT) {
                     while (prec_value != 0) {
                        func(*s_arg++, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > prec_value) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     while (prec_value != 0) {
                        func(*s_arg++, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'p': {
                  int len;
                  flags |= FLAGS_HASH;
                  num_ptr = r_xtoa((unsigned int)args[field_arg], num_buf, 0);
                  len = num_ptr - num_buf + 1;
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     flags &= ~FLAGS_ZERO;
                  }
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = prec_value + 2;
                  }
                  if (flags & FLAGS_LEFT) {
                     func('0', user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     func('x', user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > (prec_value + 2)) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     func('0', user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     func('x', user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'n': {
                  void *np = (void*)args[field_arg];
                  unsigned int len = func(0, user, 1);
                  switch (length) {
                     case LENGTH_HH:
                        *(unsigned char*)np = (unsigned char)len;
                        break;
                     case LENGTH_H:
                        *(unsigned short*)np = (unsigned short)len;
                        break;
                     case LENGTH_L:
                     default:
                        *(unsigned int*)np = len;
                        break;
                  }
                  break;
               }
               case 'C':
                  break;
               case 'S':
                  break;
               default:
                  break;
            }
            state = STATE_NORMAL;
            break;
         }
      }
   }
}

int vdprintf(int fd, const char *format, va_list ap) {
   struct _fd_printer fp;
   fp.fd = fd;
   fp.err = 0;
   fp.count = 0;
   printf_core(fd_printer, &fp, format, ap);
   return fp.count;
}

#endif /* DEBUG */

// Take from EAGLE_00005

#include "libcgc.h"
#include "cgc_libc.h"

#ifdef WIN
#include <stdarg.h>
#else
typedef __builtin_va_list va_list;

#define va_start(ap, last) __builtin_va_start(ap, last)
#endif

struct _FILE {
   int fd;
   int state;
   cgc_size_t max;
   cgc_size_t curr;
   unsigned char buf[4096];
};

static FILE std_files[3] = { {0, _FILE_STATE_OPEN}, {1, _FILE_STATE_OPEN}, {2, _FILE_STATE_OPEN} };

FILE *cgc_stdin = &std_files[0];
FILE *cgc_stdout = &std_files[1];
FILE *cgc_stderr = &std_files[2];

int cgc_vprintf(const char *format, va_list ap);
int cgc_vfprintf(FILE *stream, const char *format, va_list ap);
int cgc_vdprintf(int fd, const char *format, va_list ap);

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

int cgc_isalnum(int c) {
   return (type_flags[c & 0xff] & IS_ALNUM) != 0;
}

int cgc_isalpha(int c) {
   return (type_flags[c & 0xff] & IS_ALPHA) != 0;
}

int cgc_isascii(int c) {
   return c >= 0 && c < 128;
}

int cgc_isblank(int c) {
   return (type_flags[c & 0xff] & IS_BLANK) != 0;
}

int cgc_iscntrl(int c) {
   return (type_flags[c & 0xff] & IS_CTRL) != 0;
}

int cgc_isdigit(int c) {
   return (type_flags[c & 0xff] & IS_DIGIT) != 0;
}

int cgc_isgraph(int c) {
   return c > ' ' && c <= '~';
}

int cgc_islower(int c) {
   return (type_flags[c & 0xff] & IS_LOWER) != 0;
}

int cgc_isprint(int c) {
   return c >= ' ' && c <= '~';
}

int cgc_ispunct(int c) {
   return cgc_isprint(c) && (type_flags[c & 0xff] & (IS_SPACE | IS_ALNUM)) == 0;
}

int cgc_isspace(int c) {
   return (type_flags[c & 0xff] & IS_SPACE) != 0;
}

int cgc_isupper(int c) {
   return (type_flags[c & 0xff] & IS_UPPER) != 0;
}

int cgc_isxdigit(int c) {
   return (type_flags[c & 0xff] & IS_XDIGIT) != 0;
}

int cgc_toupper(int c) {
   if (cgc_isalpha(c)) {
      return c & ~0x20;
   }
   return c;
}

int cgc_tolower(int c) {
   if (cgc_isalpha(c)) {
      return c | 0x20;
   }
   return c;
}

int cgc_transmit_all(int fd, const void *buf, const cgc_size_t size) {
    cgc_size_t sent = 0;
    cgc_size_t sent_now = 0;
    int ret;

    if (!buf)
        return 1;

    if (!size)
        return 2;

    while (sent < size) {
        ret = cgc_transmit(fd, sent + (const char*)buf, size - sent, &sent_now);
        if (ret != 0) {
            return 3;
        }
        sent += sent_now;
    }

    return 0;
}

int cgc_printf(const char *format, ...) {
   va_list va;
   va_start(va, format);
   return cgc_vprintf(format, va);
}

int cgc_vprintf(const char *format, va_list ap) {
   return cgc_vfprintf(cgc_stdout, format, ap);
}

int cgc_vfprintf(FILE * stream, const char *format, va_list ap) {
   return cgc_vdprintf(stream->fd, format, ap);
}

struct _fd_printer {
   int fd;
   int err;
   unsigned int count;
   unsigned char buf[4096];
};

//if flag != 0 return number of chars output so far
static unsigned int cgc_fd_printer(char ch, void *_fp, int flag) {
   struct _fd_printer *fp = (struct _fd_printer *)_fp;
   if (flag == 0) {
      fp->buf[fp->count++ % sizeof(fp->buf)] = ch;
      if ((fp->count % sizeof(fp->buf)) == 0) {
         if (cgc_transmit_all(fp->fd, &ch, sizeof(fp->buf)) != 0) {
            cgc__terminate(1);
         }
      }
   }
   else if (flag == 1) {
      return fp->count;
   }
   else if (flag == 2) {
      unsigned int rem = fp->count % sizeof(fp->buf);
      if (rem != 0) {
         if (cgc_transmit_all(fp->fd, fp->buf, rem) != 0) {
            cgc__terminate(1);
         }
      }
   }
   return 0;
}

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

static char *cgc_r_utoa(unsigned int val, char *outbuf) {
   char *p = outbuf;
   *p = '0';
   while (val) {
      *p++ = (val % 10) + '0';
      val /= 10;
   }
   return p != outbuf ? (p - 1) : p;
}

//outbuf needs to be at least 22 chars
static char *cgc_r_llotoa(unsigned long long val, char *outbuf) {
   char *p = outbuf;
   *p = '0';
   while (val) {
      *p++ = (val & 7) + '0';
      val >>= 3;
   }
   return p != outbuf ? (p - 1) : p;
}

static char *cgc_r_otoa(unsigned int val, char *outbuf) {
   return cgc_r_llotoa(val, outbuf);
}

//outbuf needs to be at least 22 chars
static char *cgc_r_llxtoa(unsigned long long val, char *outbuf, int caps) {
   char *p = outbuf;
   *p = '0';
   while (val) {
      char digit = (char)(val & 0xf);
      if (digit < 10) {
         digit += '0';
      }
      else {
         digit = caps ? (digit + 'A' - 10) : (digit + 'a' - 10);
      }
      *p++ = digit;
      val >>= 4;
   }
   return p != outbuf ? (p - 1) : p;
}

static char *cgc_r_xtoa(unsigned int val, char *outbuf, int caps) {
   return cgc_r_llxtoa(val, outbuf, caps);
}

static int cgc_hex_value_of(char ch) {
   if (cgc_isdigit(ch)) {
      return ch - '0';
   }
   else if (cgc_isalpha(ch)) {
      return cgc_toupper(ch) - 'A' + 10;
   }
   return -1;
}

//func is responsible for outputing the given character
//user is a pointer to data required by func
static void cgc_printf_core(unsigned int (*func)(char, void *, int), void *user, const char *format, va_list ap) {
   int state = STATE_NORMAL;
   int flags;
   int digit_count = 0;
   int value = 0;
   char ch;
   int arg_count = 0;
   int width_value;
   int prec_value;
   int field_arg;
   int length;
   char **args = (char**)ap;
   for (ch = *format++; ch; ch = *format++) {
      switch (state) {
         case STATE_NORMAL:
            if (ch == '%') {
               state = STATE_PERCENT;
            }
            else if (ch == '\\') {
               state = STATE_ESCAPE;
            }
            else {
               func(ch, user, 0);
            }
            break;
         case STATE_ESCAPE:
            switch (ch) {
               case 'n':
                  func('\n', user, 0);
                  break;
               case 't':
                  func('\t', user, 0);
                  break;
               case 'r':
                  func('\r', user, 0);
                  break;
               case 'b':
                  func('\b', user, 0);
                  break;
               case 'f':
                  func('\f', user, 0);
                  break;
               case 'v':
                  func('\v', user, 0);
                  break;
               case '\\': case '\'': case '"':
                  func(ch, user, 0);
                  break;
               case 'x':
                  state = STATE_HEX;
                  digit_count = 0;
                  value = 0;
                  break;
               default:
                  if (ch > '0' && ch < '8') {
                     state = STATE_OCTAL;
                     digit_count = 1;
                     value = ch - '0';
                  }
                  else {
                     func(*format, user, 0);
                  }
                  break;
            }
            if (state == STATE_ESCAPE) {
               state = STATE_NORMAL;
            }
            break;
         case STATE_PERCENT:
            if (ch == '%') {
               func(ch, user, 0);
               state = STATE_NORMAL;
            }
            else {
               state = STATE_NARG;
               flags = 0;
               format--;
            }
            break;
         case STATE_OCTAL:
            if (ch > '0' && ch < '8' && digit_count < 3) {
               digit_count++;
               value = value * 8 + (ch - '0');
               if (digit_count == 3) {
                  func(value, user, 0);
                  state = STATE_NORMAL;
               }
            }
            else {
               func(value, user, 0);
               state = STATE_NORMAL;
               format--;
            }
            break;
         case STATE_HEX:
            if (cgc_isxdigit(ch) && digit_count < 2) {
               digit_count++;
               value = value * 16 + cgc_hex_value_of(ch);
               if (digit_count == 2) {
                  func(value, user, 0);
                  state = STATE_NORMAL;
               }
            }
            else {
               func(value, user, 0);
               state = STATE_NORMAL;
               format--;
            }
            break;
         case STATE_NARG:
            width_value = -1;
            prec_value = -1;
            flags = 0;
            length = 0;
            field_arg = -1;
            if (ch == '0') {
               format--;
               state = STATE_FLAGS;
               break;
            }
            if (cgc_isdigit(ch)) {
               //could be width or could be arg specifier or a 0 flag
               //width and arg values don't start with 0
               width_value = 0;
               while (cgc_isdigit(ch)) {
                  width_value = width_value * 10 + (ch - '0');
                  ch = *format++;
               }
               if (ch == '$') {
                  field_arg = width_value - 1;
                  width_value = 0;
                  state = STATE_FLAGS;
               }
               else {
                  //this was a width
                  format--;
                  state = STATE_PRECISION;
               }
            }
            else {
               format--;
               state = STATE_FLAGS;
            }
            break;
         case STATE_FLAGS:
            switch (ch) {
               case '\'':
                  flags |= FLAGS_TICK;
                  break;
               case '-':
                  flags |= FLAGS_LEFT;
                  break;
               case '+':
                  flags |= FLAGS_SIGN;
                  break;
               case ' ':
                  flags |= FLAGS_SPACE;
                  break;
               case '#':
                  flags |= FLAGS_HASH;
                  break;
               case '0':
                  flags |= FLAGS_ZERO;
                  break;
               default:
                  format--;
                  if ((flags & (FLAGS_ZERO | FLAGS_LEFT)) == (FLAGS_ZERO | FLAGS_LEFT)) {
                     //if both '-' and '0' appear, '0' is ignored
                     flags &= ~FLAGS_ZERO;
                  }
                  state = STATE_WIDTH;
                  break;
            }
            break;
         case STATE_WIDTH:
            if (ch == '*') {
               ch = *format++;
               int width_arg = 0;
               if (cgc_isdigit(ch)) {
                  while (cgc_isdigit(ch)) {
                     width_arg = width_arg * 10 + (ch - '0');
                     ch = *format++;
                  }
                  width_arg--;
                  if (ch != '$') {
                     //error
                  }
               }
               else {
                  width_arg = arg_count++;
                  format--;
               }
               width_value = (int)args[width_arg];
            }
            else if (cgc_isdigit(ch)) {
               width_value = 0;
               while (cgc_isdigit(ch)) {
                  width_value = width_value * 10 + (ch - '0');
                  ch = *format++;
               }
               format--;
            }
            else {
               //no width specified
               format--;
            }
            state = STATE_PRECISION;
            break;
         case STATE_PRECISION:
            if (ch == '.') {
               //have a precision
               ch = *format++;
               if (ch == '*') {
                  ch = *format++;
                  int prec_arg = 0;
                  if (cgc_isdigit(ch)) {
                     while (cgc_isdigit(ch)) {
                        prec_arg = prec_arg * 10 + (ch - '0');
                        ch = *format++;
                     }
                     prec_arg--;
                     if (ch != '$') {
                        //error
                     }
                  }
                  else {
                     prec_arg = arg_count++;
                     format--;
                  }
                  prec_value = (int)args[prec_arg];
               }
               else if (cgc_isdigit(ch)) {
                  prec_value = 0;
                  while (cgc_isdigit(ch)) {
                     prec_value = prec_value * 10 + (ch - '0');
                     ch = *format++;
                  }
                  format--;
               }
               else {
                  //no precision specified
                  format--;
               }
            }
            else {
               //no precision specified
               format--;
            }
            state = STATE_LENGTH;
            break;
         case STATE_LENGTH:
            switch (ch) {
               case 'h':
                  length = LENGTH_H;
                  if (*format == 'h') {
                     length++;
                     format++;
                  }
                  break;
               case 'l':
                  length = LENGTH_L;
                  if (*format == 'l') {
//                     length++;
                     format++;
                  }
                  break;
               case 'j':
                  length = LENGTH_J;
                  break;
               case 'z':
                  length = LENGTH_Z;
                  break;
               case 't':
                  length = LENGTH_T;
                  break;
               case 'L':
                  length = LENGTH_CAPL;
                  break;
               default:
                  format--;
                  break;
            }
            state = STATE_CONVERSION;
            break;
         case STATE_CONVERSION: {
            char num_buf[32];
            char *num_ptr;
            int use_caps = 1;
            int sign;
            int val;
            // long long llval;
            if (field_arg == -1) {
               field_arg = arg_count++;
            }
            switch (ch) {
               case 'd': case 'i': {
                  int len;
                  switch (length) {
                     case LENGTH_H:
                        val = (short)(int)args[field_arg];
                        sign = val < 0;
                        if (sign) {
                           val = -val;
                        }
                        num_ptr = cgc_r_utoa(val, num_buf);
                        break;
                     case LENGTH_HH:
                        val = (char)(int)args[field_arg];
                        sign = val < 0;
                        if (sign) {
                           val = -val;
                        }
                        num_ptr = cgc_r_utoa(val, num_buf);
                        break;
                     case LENGTH_L:
                     default:
                        val = (long)args[field_arg];
                        sign = val < 0;
                        if (sign) {
                           val = -val;
                        }
                        num_ptr = cgc_r_utoa(val, num_buf);
                        break;
                  }
                  len = num_ptr - num_buf + 1;
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = len;
                     if (sign || (flags & FLAGS_SIGN)) {
                        width_value++;
                     }
                  }
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                     if ((flags & FLAGS_ZERO) != 0 && prec_value < width_value) {
                        //widen precision if necessary to pad to width with '0'
                        if (sign || (flags & FLAGS_SIGN)) {
                           prec_value = width_value - 1;
                        }
                        else {
                           prec_value = width_value;
                        }
                     }
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     //number won't need leading zeros
                     flags &= ~FLAGS_ZERO;
                  }
                  if (flags & FLAGS_LEFT) {
                     if (sign) {
                        func('-', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     else if ((flags & FLAGS_SIGN) != 0) {
                        func('+', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > (prec_value + 1)) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     if (sign) {
                        func('-', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     else if ((flags & FLAGS_SIGN) != 0) {
                        func('+', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     if (width_value > prec_value) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'o': {
                  int len;
                  switch (length) {
                     case LENGTH_H:
                        num_ptr = cgc_r_otoa((unsigned short)(unsigned int)args[field_arg], num_buf);
                        break;
                     case LENGTH_HH:
                        num_ptr = cgc_r_otoa((unsigned char)(unsigned int)args[field_arg], num_buf);
                        break;
                     case LENGTH_L:
                     default:
                        num_ptr = cgc_r_otoa((unsigned long)args[field_arg], num_buf);
                        break;
                  }
                  if (flags & FLAGS_HASH) {
                     if (*num_ptr != '0') {
                        num_ptr++;
                        *num_ptr = '0';
                     }
                  }
                  len = num_ptr - num_buf + 1;
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = len;
                  }
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                     if ((flags & FLAGS_ZERO) != 0 && prec_value < width_value) {
                        //widen precision if necessary to pad to width with '0'
                        prec_value = width_value;
                     }
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     flags &= ~FLAGS_ZERO;
                  }
                  if (flags & FLAGS_LEFT) {
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > prec_value) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'u': {
                  int len;
                  switch (length) {
                     case LENGTH_H:
                        num_ptr = cgc_r_utoa((unsigned short)(unsigned int)args[field_arg], num_buf);
                        break;
                     case LENGTH_HH:
                        num_ptr = cgc_r_utoa((unsigned char)(unsigned int)args[field_arg], num_buf);
                        break;
                     case LENGTH_L:
                     default:
                        num_ptr = cgc_r_utoa((unsigned long)args[field_arg], num_buf);
                        break;
                  }
                  len = num_ptr - num_buf + 1;
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = len;
                  }
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                     if ((flags & FLAGS_ZERO) != 0 && prec_value < width_value) {
                        //widen precision if necessary to pad to width with '0'
                        prec_value = width_value;
                     }
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     flags &= ~FLAGS_ZERO;
                  }
                  if (flags & FLAGS_LEFT) {
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > prec_value) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'x':
                  use_caps = 0;  //now fall into X case
               case 'X': {
                  int len;
                  switch (length) {
                     case LENGTH_H:
                        num_ptr = cgc_r_xtoa((unsigned short)(unsigned int)args[field_arg], num_buf, use_caps);
                        break;
                     case LENGTH_HH:
                        num_ptr = cgc_r_xtoa((unsigned char)(unsigned int)args[field_arg], num_buf, use_caps);
                        break;
                     case LENGTH_L:
                     default:
                        num_ptr = cgc_r_xtoa((unsigned long)args[field_arg], num_buf, use_caps);
                        break;
                  }
                  len = num_ptr - num_buf + 1;
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = len;
                  }
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                     if ((flags & FLAGS_ZERO) != 0 && prec_value < width_value) {
                        //widen precision if necessary to pad to width with '0'
                        prec_value = width_value;
                     }
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     flags &= ~FLAGS_ZERO;
                  }
                  if (flags & FLAGS_LEFT) {
                     if (flags & FLAGS_HASH && (len != 1 || *num_ptr != '0')) {
                        func('0', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                        func(use_caps ? 'X' : 'x', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > (prec_value + 2)) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     if (flags & FLAGS_HASH && (len != 1 || *num_ptr != '0')) {
                        func('0', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                        func(use_caps ? 'X' : 'x', user, 0);
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     else {
                        while (width_value > prec_value) {
                           func(' ', user, 0);
                           width_value--;
                        }
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'f': case 'F':
                  break;
               case 'e': case 'E':
                  break;
               case 'g': case 'G':
                  break;
               case 'a': case 'A':
                  break;
               case 'c': {
                  unsigned char ch = (unsigned char)(unsigned int)args[field_arg];
                  if (width_value == -1) {
                     width_value = 1;
                  }
                  if (flags & FLAGS_LEFT) {
                     func((char)ch, user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > 1) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     func(ch, user, 0);
                  }
                  break;
               }
               case 's': {
                  const char *s_arg = (const char *)args[field_arg];
                  int len = cgc_strlen(s_arg);
                  if (width_value == -1) {
                     //by default min length is the entire string
                     width_value = len;
                  }
                  if (prec_value == -1 || prec_value > len) {
                     //by default max is entire string but no less than width
                     prec_value = len;
                  }
                  if (flags & FLAGS_LEFT) {
                     while (prec_value != 0) {
                        func(*s_arg++, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > prec_value) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     while (prec_value != 0) {
                        func(*s_arg++, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'p': {
                  int len;
                  flags |= FLAGS_HASH;
                  num_ptr = cgc_r_xtoa((unsigned int)args[field_arg], num_buf, 0);
                  len = num_ptr - num_buf + 1;
                  if (prec_value == -1) {
                     //by default max is entire value
                     prec_value = len;
                  }
                  else {
                     if (prec_value < len) {
                        prec_value = len;
                     }
                     flags &= ~FLAGS_ZERO;
                  }
                  if (width_value == -1) {
                     //by default min length is the entire value
                     width_value = prec_value + 2;
                  }
                  if (flags & FLAGS_LEFT) {
                     func('0', user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     func('x', user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                        if (width_value > 0) {
                           width_value--;
                        }
                     }
                     while (width_value != 0) {
                        func(' ', user, 0);
                        width_value--;
                     }
                  }
                  else {
                     while (width_value > (prec_value + 2)) {
                        func(' ', user, 0);
                        width_value--;
                     }
                     func('0', user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     func('x', user, 0);
                     if (width_value > 0) {
                        width_value--;
                     }
                     while (prec_value > len) {
                        func('0', user, 0);
                        prec_value--;
                     }
                     while (prec_value != 0) {
                        func(*num_ptr--, user, 0);
                        prec_value--;
                     }
                  }
                  break;
               }
               case 'n': {
                  void *np = (void*)args[field_arg];
                  unsigned int len = func(0, user, 1);
                  switch (length) {
                     case LENGTH_HH:
                        *(unsigned char*)np = (unsigned char)len;
                        break;
                     case LENGTH_H:
                        *(unsigned short*)np = (unsigned short)len;
                        break;
                     case LENGTH_L:
                     default:
                        *(unsigned int*)np = len;
                        break;
                  }
                  break;
               }
               case 'C':
                  break;
               case 'S':
                  break;
               default:
                  break;
            }
            state = STATE_NORMAL;
            break;
         }
      }
   }
   func(0, user, 2);
}

int cgc_vdprintf(int fd, const char *format, va_list ap) {
   struct _fd_printer fp;
   fp.fd = fd;
   fp.err = 0;
   fp.count = 0;
   cgc_printf_core(cgc_fd_printer, &fp, format, ap);
   return fp.count;
}

int cgc_fgetc(FILE *stream) {
   if (stream->curr < stream->max) {
      return stream->buf[stream->curr++];
   }
   stream->curr = stream->max = 0;

   if (cgc_receive(stream->fd, stream->buf, sizeof(stream->buf), &stream->max) != 0) {
      stream->state |= _FILE_STATE_ERROR;
      return EOF;
   }
   else if (stream->max == 0) {
      stream->state |= _FILE_STATE_EOF;
      return EOF;
   }
   else {
      return stream->buf[stream->curr++];
   }
}

int cgc_getc(FILE *stream) {
   return cgc_fgetc(stream);
}

int cgc_getchar(void) {
   return cgc_getc(cgc_stdin);
}

char *cgc_fgets(char *s, int size, FILE *stream) {
   int idx = 0;
   while (idx < (size - 1)) {
      int ch = cgc_fgetc(stream);
      if (ch == EOF) {  //error or eof
         if ((stream->state & _FILE_STATE_EOF) != 0) {
            if (idx > 0) {
               break;
            }
         }
         return NULL;
      }
      else {
         s[idx++] = ch;
         if (ch == '\n') {
            break;
         }
      }
   }
   s[idx] = '\0';
   return s;
}

int cgc_fread(void *buf, cgc_size_t size, cgc_size_t nmemb, FILE *f) {
   cgc_size_t nitems;
   cgc_size_t n;
   cgc_size_t i = 0;
   for (nitems = 0; nitems < nmemb; nitems++) {
      for (n = 0; n < size; n++) {
         int ch = cgc_fgetc(f);
         if (ch == EOF) {
            return nitems;
         }
         ((char*)buf)[i++] = ch;
      }
   }
   return nitems;
}



