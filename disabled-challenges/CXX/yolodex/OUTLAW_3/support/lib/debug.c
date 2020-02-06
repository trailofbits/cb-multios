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

#ifdef DEBUG

#include "debug.h"

///////////////

static FILE std_files[3] = { {0, _FILE_STATE_OPEN}, {1, _FILE_STATE_OPEN}, {2, _FILE_STATE_OPEN} };

FILE *stdin = &std_files[0];
FILE *stdout = &std_files[1];
FILE *stderr = &std_files[2];

int isalpha(int c) {
   return (type_flags[c & 0xff] & IS_ALPHA) != 0;
}

int isdigit(int c) {
   return (type_flags[c & 0xff] & IS_DIGIT) != 0;
}

int isxdigit(int c) {
   return (type_flags[c & 0xff] & IS_XDIGIT) != 0;
}

// int toupper(int c) {
//    if (isalpha(c)) {
//       return c & ~0x20;
//    }
//    return c;
// }

int vfprintf(FILE * stream, const char *format, va_list ap) {
   return vdprintf(stream->fd, format, ap);
}

int fprintf(FILE * stream, const char *format, ...) {
   va_list va;
   va_start(va, format);
   return vfprintf(stream, format, va);
}

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
                  int len = strlen(s_arg, '\0');
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