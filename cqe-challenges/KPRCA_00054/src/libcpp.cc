/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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

extern "C" {
#include <stdlib.h>
};

extern void terminate(int);
extern "C" {
  void __cxa_pure_virtual() { exit(0); }
};

void *operator new(unsigned int sz) {
  return malloc(sz);
}

void *operator new[](unsigned int sz) {
  return ::operator new(sz);
}

void operator delete(void *p) {
  free(p);
}

void operator delete[](void *p) {
  ::operator delete(p);
}

#define __hidden __attribute__((__visibility__("hidden")))

void *__dso_handle; /* required symbol, but not used */

extern "C" {
  extern void (*__init_array_start[])(int, char **, char **) __hidden;
  extern void (*__init_array_end[])(int, char **, char **) __hidden;
};

void call_inits(void) {
  size_t asize;
  void (*fn)(int, char **, char **);

  asize = __init_array_end - __init_array_start;
  for (size_t n = 0; n < asize; n++) {
    fn = __init_array_start[n];
    if (fn && (long)fn != 1)
      fn(0, (char **)NULL, (char **)NULL);
  }
}

extern "C" {
  int __cxa_atexit(void (*func)(void *), void *arg, void *dso);
};

static struct exit_handlers {
  void (*func)(void *);
  void *arg;
} exit_handlers[100];
static int nhandlers = 0;

int __cxa_atexit(void (*func)(void *), void *arg, void *dso) {
  if (nhandlers == sizeof(exit_handlers)/sizeof(exit_handlers[0]))
    return (-1);
  exit_handlers[nhandlers].func = func;
  exit_handlers[nhandlers].arg = arg;
  nhandlers++;
  return (0);
}
