/*

Author: Debbie Nuttall <debbie@cromulence.co>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include <libcgc.h>
#include "stdlib.h"
#include "io.h"

int strlen(char *s) {
  char *e = s;
  while (*e != '\0') e++;
  return (e - s);
}

void bzero(char *s, size_t length) {
  while (length > 0) {
    *s++ = '\0';
    length--;
  }
}

void memcpy(char *d, char *s, size_t num) {
  while(num > 0) {
    *d++ = *s++;
    num--;
  }
}

int atoi(char *s) {
  if (s == NULL) {
    return 0;
  }

  int negative = 0;
  int num_digits = 0;
  int number = 0;

  while(*s != '\0')
  {
    if ((*s == '-') && (num_digits==0)) {
      negative = 1;
      s++;
      continue;
    }
    if (*s < '0' || *s > '9') {
      return number;
    }
    number = (number * 10) + (*s - '0');
    num_digits++;
    s++;
    if (num_digits > 10) {
      return number;
    }
  }
  if (negative) {
    return (-1 * number);
  } else {
    return number;
  }
}

// This function counts the number of single null
// terminated strings stopping after the first double null is found
int count_strings(char *s) {
  int count = 0;
  while (*s != '\0' || *(s+1) != '\0') {
    if (*(s+1) == '\0') {
      count++;
    }
    s++;
  }
  return count;
}

// This function returns a pointer to the next null terminated string
// If it encounters a double null it returns 0;
char *next_string(char *s) {
  char *n = s;
  while (*n != '\0') {
    n++;
  }
  n++;
  if (*n == '\0') {
    return 0;
  } else {
    return n;
  }
}


