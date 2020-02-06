#include "libcgc.h"
#include "cgc_libc.h"

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

int cgc_vprintf(const char *format, va_list ap);
int cgc_vfprintf(FILE *stream, const char *format, va_list ap);
int cgc_vdprintf(int fd, const char *format, va_list ap);
int cgc_vsnprintf(char *str, cgc_size_t size, const char *format, va_list ap);

int errno;

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

char *cgc_strsep(char **stringp, const char *delim) {
   char *tok = *stringp;
   char *endp = NULL;
   if (*stringp == NULL) {
      return NULL;
   }
   while (*delim) {
      char *d;
      for (d = tok; *d && (endp == NULL || d < endp); d++) {
         if (*d == *delim) {
            endp = d;
            break;
         }
      }
      delim++;
   }
   if (endp != NULL) {
      *endp++ = '\0';
   }
   *stringp = endp;
   return tok;
}

static int cgc_valueOf(char ch, int base) {
   if (cgc_isdigit(ch)) {
      int x = ch - '0';
      return x < base ? x : -1;
   }
   else if (cgc_isalpha(ch)) {
      int x = cgc_toupper(ch) - 'A' + 10;
      return x < base ? x : -1;
   }
   return -1;
}

long cgc_strtol(const char *str, char **endptr, int base) {
   const char *n = str;
   int neg = 0;
   int digit;
   long result = 0;
   if (base != 0 && (base < 2 || base > 36)) {
      errno = EINVAL;
      return 0;
   }

   //init *endptr to beginning of string
   if (endptr) {
      *endptr = (char*)str;
   }

   //skip white space
   while (cgc_isspace(*n)) n++;

   //deal with possible sign
   if (*n == '+') {
      n++;
   }
   else if (*n == '-') {
      n++;
      neg = 1;
   }

   //handle base == 0
   if (base == 0) {
      base = 10;
      if (*n == '0') {
         base = 8;
         n++;
         if (*n == 'X' || *n == 'x') {
            base = 16;
            n++;
         }
      }
   }

   while ((digit = cgc_valueOf(*n, base)) != -1) {
      long next = result * base + digit;
      if (next < result) {
         //overflow
         errno = ERANGE;
         return neg ? LONG_MIN : LONG_MAX;
      }
      result = next;
      n++;
      if (endptr) {
         //*endptr points to character after last converted digit
         *endptr = (char*)n;
      }
   }

   return neg ? -result : result;
}

unsigned int cgc_htonl(unsigned int hostlong) {
 __asm__ ("bswapl %%eax"
          : "=a" (hostlong)
          : "a" (hostlong)
          );
   return hostlong;
}

int cgc_transmit_all(int fd, const char *buf, const cgc_size_t size) {
    cgc_size_t sent = 0;
    cgc_size_t sent_now = 0;
    int ret;

    if (!buf)
        return 1;

    if (!size)
        return 2;

    while (sent < size) {
        ret = cgc_transmit(fd, buf + sent, size - sent, &sent_now);
        if (ret != 0) {
            return 3;
        }
        sent += sent_now;
    }

    return 0;
}

void *cgc_memset(void *dst, int c, unsigned int n) {
   char *d = (char*)dst;
   while (n--) {*d++ = (char)c;}
   return dst;
}

int cgc_memcmp(const void *b1, const void *b2, cgc_size_t n) {
   unsigned char *p1 = (unsigned char*)b1;
   unsigned char *p2 = (unsigned char*)b2;
   while (n > 0 && *p1 == *p2) {
      p1++;
      p2++;
      n--;
   }
   return n == 0 ? 0 : (*p1 - *p2);
}

int cgc_strcmp(const char *s1, const char *s2) {
   while (*s1 != '\0' && *s2 != '\0'  && *s1 == *s2) {
      s1++;
      s2++;
   }
   return *s1 - *s2;
}

char *cgc_strcpy(char *dst, const char *src) {
   char *d = dst;
   while ((*d++ = *src++) != 0) {}
   return dst;
}

cgc_size_t cgc_strlen(const char *str) {
   cgc_size_t res = 0;
   while (*str++) {res++;}
   return res;
}

char *cgc_strchr(const char *s, int c) {
   while (*s && *s != c) {s++;}
   return (char*)(*s ? s : (c ? NULL : s));
}

int cgc_snprintf(char *str, cgc_size_t size, const char *format, ...) {
   va_list va;
   va_start(va, format);
   return cgc_vsnprintf(str, size, format, va);
}

struct _str_printer {
   char *outbuf;
   unsigned int max;
   unsigned int count;
};

//if flag != 0 return number of chars output so far
static unsigned int cgc_strn_printer(char ch, void *_sp, int flag) {
   struct _str_printer *sp = (struct _str_printer *)_sp;
   if (flag) {
      return sp->count;
   }
   else if (sp->count < sp->max) {
      *(sp->outbuf) = ch;
      (sp->outbuf)++;
   }
   sp->count++;
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

int cgc_fprintf(FILE * stream, const char *format, ...) {
   va_list va;
   va_start(va, format);
   return cgc_vfprintf(stream, format, va);
}

struct _fd_printer {
   int fd;
   int err;
   unsigned int count;
};

//if flag != 0 return number of chars output so far
static unsigned int cgc_fd_printer(char ch, void *_fp, int flag) {
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
   int ch = 0;
   cgc_size_t rx_bytes;

   //first check to see if a character has been "unget"
   if ((stream->state & _FILE_HAVE_LAST) != 0) {
      stream->state &= ~_FILE_HAVE_LAST;
      return stream->last;
   }
   if (cgc_receive(stream->fd, &ch, 1, &rx_bytes) != 0) {
      stream->state |= _FILE_STATE_ERROR;
      return EOF;
   }
   else if (rx_bytes == 0) {
      stream->state |= _FILE_STATE_EOF;
      return EOF;
   }
   else {
      return ch;
   }
}

int cgc_vsnprintf(char *str, cgc_size_t size, const char *format, va_list ap) {
   struct _str_printer sp;
   sp.outbuf = str;
   sp.max = size;
   sp.count = 0;
   cgc_printf_core(cgc_strn_printer, &sp, format, ap);
   if (sp.count < sp.max) {
      *sp.outbuf = 0;
   }
   else if (sp.max > 0) {
      str[size - 1] = 0;
   }
   return sp.count;
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


