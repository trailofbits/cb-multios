
#include <libcgc.h>

#define LONG_MAX 0x7FFFFFFF
#define LONG_MIN 0x80000000

#define LLONG_MAX 0x7FFFFFFFFFFFFFFFLL
#define LLONG_MIN 0x8000000000000000LL

#define ULONG_MAX 0xFFFFFFFF

#define ULLONG_MAX 0xFFFFFFFFFFFFFFFFLL

int isalpha(int c);
int isdigit(int c);
int toupper(int c);
int isspace(int c);

static int valueOf(char ch, int base) {
   if (isdigit(ch)) {
      int x = ch - '0';
      return x < base ? x : -1;
   }
   else if (isalpha(ch)) {
      int x = toupper(ch) - 'A' + 10;
      return x < base ? x : -1;
   }
   return -1;
}

long strtol(const char *str, char **endptr, int base) {
   const char *n = str;
   int neg = 0;
   int digit;
   long result = 0;
   if (base != 0 && (base < 2 || base > 36)) {
//      errno = EINVAL;
      return 0;
   }
   
   //init *endptr to beginning of string
   if (endptr) {
      *endptr = (char*)str;
   }
   
   //skip white space
   while (isspace(*n)) n++;
   
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
   
   while ((digit = valueOf(*n, base)) != -1) {
      long next = result * base + digit;
      if (next < result) {
         //overflow
//         errno = ERANGE;
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

unsigned long strtoul(const char *str, char **endptr, int base) {
   const char *n = str;
   int neg = 0;
   int digit;
   unsigned long result = 0;
   if (base != 0 && (base < 2 || base > 36)) {
//      errno = EINVAL;
      return 0;
   }
   
   //init *endptr to beginning of string
   if (endptr) {
      *endptr = (char*)str;
   }
   
   //skip white space
   while (isspace(*n)) n++;
   
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
   
   while ((digit = valueOf(*n, base)) != -1) {
      unsigned long next = result * base + digit;
      if (next < result) {
         //overflow
//         errno = ERANGE;
         return ULONG_MAX;
      }
      result = next;
      n++;
      if (endptr) {
         //*endptr points to character after last converted digit
         *endptr =(char*)n;
      }  
   }
   
   return neg ? -result : result;
}
