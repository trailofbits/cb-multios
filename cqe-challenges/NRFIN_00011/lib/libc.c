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

#include "libc.h"

// Address fragmentation issue.
// Keep looping until we've receive'd count bytes.
// MOD from REDPILL: bails substituted for immediate returns.
int receive_all(int fd, void *buf, size_t count, size_t *rx_bytes) {

  int ret = SUCCESS;
  size_t bytes_left = count;
  size_t rx_bytes_local = 0;

  while (bytes_left) {

    rx_bytes_local = 0;

      if (SUCCESS != (ret = receive(STDIN, buf+(count-bytes_left), bytes_left, &rx_bytes_local))) {
#ifdef DEBUG
          fprintf(stderr, "[E] receive () call within receive_all() failed\n");
#endif
          return ret;
      }

      // Assume EOF if 0-lengthed buffer.
      if (0 == rx_bytes_local) {
        if (NULL != rx_bytes) { 
            *rx_bytes = count-bytes_left; 
         }
        return ret;
      }

#ifdef DEBUG
        fprintf(stderr, "[D] in receive_all(), got %d bytes\n", rx_bytes_local);
#endif
      bytes_left -= rx_bytes_local;
  }

  // If we got here, then we got all the bytes.
  if (NULL != rx_bytes) { *rx_bytes = count; }

  return ret;
}

// Address fragmentation issue.
// Keep looping until we've transmit'ed count bytes.
// MOD from REDPILL: bails substituted for immediate returns.
int transmit_all(int fd, const void *buf, size_t count, size_t *tx_bytes) {

  int ret = SUCCESS;
  size_t bytes_left = count;
  size_t tx_bytes_local = 0;

  while (bytes_left) {

    tx_bytes_local = 0;

    if (SUCCESS != (ret = transmit(STDIN, buf, bytes_left, &tx_bytes_local))) {
      #ifdef DEBUG
        fprintf(stderr, "[E] transmit () call within transmit_all() failed\n");
      #endif
        return ret;
    }

      bytes_left -= tx_bytes_local;
  }

  // If we got here, then we got all the bytes.
  if (NULL != tx_bytes) { *tx_bytes = count; }
  
  return ret;
}

// Wrapper for transmit_all() that terminates packets with our custom string 
// terminator.
int transmit_with_term(int fd, const void *buf, size_t count, size_t *tx_bytes) {

   int ret = SUCCESS;

   if (SUCCESS != (ret = transmit_all(fd, buf, count, tx_bytes))) { 
#ifdef DEBUG
      fprintf(stderr, "[E] in transmit_with_term(), during transmit (actual data)\n");
#endif
      return ret;
   }

   if (SUCCESS != (ret = transmit_all(fd, (void *)&STRING_TERMINATOR_STR, 1, tx_bytes))) { 
#ifdef DEBUG
      fprintf(stderr, "[E] in transmit_with_term(), during transmit (STRING_TERMINATOR)\n");
#endif
      return ret;
   }

   return ret;
}

// Wrapper for receive_all() that terminates buffers with our STRING_TERMINATOR.
// Destination buffer MUST be 1 byte larger than count (count+1).
int receive_with_term(int fd, void *buf, size_t count, size_t *rx_bytes) {

   int ret = SUCCESS;

   if (SUCCESS != (ret = receive_all(fd, buf, count, rx_bytes))) { 
#ifdef DEBUG
      fprintf(stderr, "[E] in receive_with_term(), during receive (actual data)\n");
#endif
      return ret;
   }

   ((char *)(buf))[count] = STRING_TERMINATOR;

   return ret;
}

// MOD FROM: KPRCA_00001
// Changed definition of string (no longer terminated by NULL) + added n arg.
char *strncpy(char *dest, const char *src, size_t n)
{
   size_t i;
   for (i = 0; (src[i] != STRING_TERMINATOR) && (0 < n--); i++) {
      dest[i] = src[i];
   }
   dest[i] = STRING_TERMINATOR;
   return dest;
}

// From the docs:
// The strcat() and strncat() functions append a copy of the null-terminated 
// string s2 to the end of the null-terminated string s1, then add a 
// terminating `\0'.  
// The strncat() function appends not more than n characters from s2, and then 
// adds a terminating `\0'.
// NOTE: not POSIX
char * strncat(char *s1, const char *s2, size_t n) {

   // Find the end of s1.
   char *cat_begin = s1 + strlen(s1);

   // Copy the specified amount to the end of s1.
   strncpy(cat_begin, s2, n);

   // Add the STRING_TERMINATOR
   cat_begin[n] = STRING_TERMINATOR;

   // Just so that we're not exactly POSIX (POSIX returns s1).
   return (char *)s2;
}

// IDENTICAL TO: REDPILL
unsigned char * memset(void *b, char c, size_t len) {

  char *ptr = (char *)b; 
  while (len) {
      ptr[len-1] = c;
      len--;
  }
  return b;
}

// Provided a haystack string and a needle string, return a ptr to the location 
// in the haystack string where the needle resides.  
// If no needle found, return NULL.
// NOTE: This function is horribly inefficient... so it probably doesn't look 
//    like a real function a CRS might be trained on.  Yey silver lining.
char * strpos(char * haystack, char * needle) {

   char * pos = NULL;
   size_t sz_haystack = strlen(haystack);
   size_t sz_needle = strlen(needle);

   // If the substring is longer than the string, then we're not finding it.
   if (sz_haystack < sz_needle) { return NULL; }

   for (int i = 0; i <= (sz_haystack-sz_needle); i++) {
      if (0 == strncmp(haystack + i, needle, sz_needle)) {
         pos = haystack + i;
         break;
      }
   }

   return pos;
}


// Read until size or we see a '\n'.
// If we receive 0 bytes, keep reading. 
// MOD from FASTLANE: STRING_TERMINATOR substituted for '\n' 
int recv_until_delim(int fd, char *buf, size_t size) {

    size_t bytes_read = 0;
    size_t cursize = size;

    if(!size)
        return 0;
 
    if (!buf)
        return -2;

    // While we still have bytes to read...
    while (0 != cursize) {

        bytes_read = 0;

        // Try reading 1 byte.
        // XXXX: We *shouldn't* need to check return value here.
        receive(fd, buf, 1, &bytes_read);
        buf += bytes_read;

        // If we read 0 bytes, we assume EOF; break.
        if (0 == bytes_read) { break; }

        // If we just read a newline, we're done; break.
        if ( *(buf-1) == STRING_TERMINATOR ) { break; }

        // Subtract cursize by the number of bytes read.
        // This shouldn't underflow because we only request 1 byte at a time.
        cursize -= bytes_read;
    }

    if (*(buf-1) != STRING_TERMINATOR)
        return -1;
    else
        *(buf-1) = STRING_TERMINATOR;

    return size-cursize;
}


// BASED ON: EAGLE_00004
// MOD: changed delimeter, added length parameter
int strncmp(const char *s1, const char *s2, size_t len) {

   while (*s1 != STRING_TERMINATOR && *s2 != STRING_TERMINATOR && *s1 == *s2) {
      if (--len == 0) { break; }
      s1++;
      s2++;
   }
   return *s1 - *s2;
}

// BASED ON: EAGLE_00004
// MOD: changed delimeter
int strcmp(const char *s1, const char *s2) {

   while (*s1 != STRING_TERMINATOR && *s2 != STRING_TERMINATOR && *s1 == *s2) {
      s1++;
      s2++;
   }
   return *s1 - *s2;
}

// BASED ON: EAGLE_00004
// MOD: changed delimeter
size_t strlen(const char *str) {
   size_t res = 0;
   while (STRING_TERMINATOR != *str++) {res++;}
   return res;
}


#ifdef DEBUG

////
// The following is verbatim from EAGLE_00004, but isn't included in the 
// released binary (DEBUG is not defined), so this reuse shouldn't be a concern.
////

typedef __builtin_va_list va_list;
#define va_start(ap, param) __builtin_va_start(ap, param)
#define va_end(ap) __builtin_va_end(ap)
#define va_arg(ap, type) __builtin_va_arg(ap, type)

static FILE std_files[3] = { {0, _FILE_STATE_OPEN}, {1, _FILE_STATE_OPEN}, {2, _FILE_STATE_OPEN} };

FILE *stdin = &std_files[0];
FILE *stdout = &std_files[1];
FILE *stderr = &std_files[2];

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
      transmit(fp->fd, &ch, 1, NULL);
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
            long long llval;
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
                  int len = strlen(s_arg);
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

#endif
// ^ DEBUG
