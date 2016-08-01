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

#include <libcgc.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "kty.h"

#define MAX_KTY_LENGTH 8192

kty_parser_t *parser;
kty_item_t *my_kty;

int read_until(int fd, char *buf, size_t len, char delim)
{
  size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    size_t rx;
    if (receive(fd, c, 1, &rx) != 0 || rx == 0)
      return -1;
    if (*(c++) == delim)
      break;
  }
  *(c-1) = '\0';
  return c - buf;
}

void import_kty(char *buf)
{
  if (my_kty != NULL)
  {
    free_kty_item(my_kty);
    my_kty = NULL;
  }

  parser->cats = 0;
  my_kty = parser->loads(buf);

  if (my_kty == NULL)
    fdprintf(STDOUT, "Error!\n");
}

void print_kty()
{
  if (my_kty == NULL)
  {
    fdprintf(STDOUT, "Error!\n");
    return;
  }

  parser->cats = 0;
  parser->dumps(my_kty);
}

void nyan()
{
  int i;
  char *c;
  char buf[1024] = {0};
  char nyan_cat[] = "\n\n\
+      o     +              o\n\
    +             o     +       +\n\
o          +\n\
    o  +           +        +\n\
+        o     o       +        o\n\
-_-_-_-_-_-_-_,------,      o\n\
_-_-_-_-_-_-_-|   /\\_/\\\n\
-_-_-_-_-_-_-~|__( ^ .^)  +     +\n\
_-_-_-_-_-_-_-\"\"  \"\"\n\
+      o         o   +       o\n\
    +         +\n\
o        o         o      o     +\n\
    o           +\n\
+      +     o        o      +\n\n";

  if (my_kty == NULL)
  {
    fdprintf(STDOUT, "Error!\n");
    return;
  }
  parser->dumps(my_kty);
  if (parser->cats < 3)
    return;

  fdprintf(STDOUT, "%s", nyan_cat);

  c = buf;
  for (i = 0; i < array_length(parser->nyan_says); ++i)
  {
    kty_item_t *item = array_get(parser->nyan_says, i);
#if PATCHED
    int sz = (buf + sizeof(buf) - c) - strlen(item->item.i_string.s);
    sz = sz > 0 ? strlen(item->item.i_string.s) : (buf + sizeof(buf) - c - 1);
    memcpy(c, item->item.i_string.s, sz);
#else
    strcpy(c, item->item.i_string.s);
#endif
    c += item->item.i_string.len;
  }
  fdprintf(STDOUT, "NYAN SAYS...\n\"\n%s\n\"", buf);
}

void quit()
{
  fdprintf(STDOUT, "\n\n=^.^=// Bye!\n\n");
  exit(0);
}

void menu()
{
  fdprintf(STDOUT, "=======================\n");
  fdprintf(STDOUT, " 1. Import KTY\n");
  fdprintf(STDOUT, " 2. Print KTY\n");
  fdprintf(STDOUT, " 3. Quit\n");
  fdprintf(STDOUT, "=======================\n");
}

int main()
{
  char buf[MAX_KTY_LENGTH];
  char select[16];
  fdprintf(STDOUT, "KTY Pretty Printer v0.1\n");

  parser = (kty_parser_t *) malloc(sizeof(kty_parser_t));
  if (kty_init(parser) != 0)
  {
    fdprintf(STDOUT, "Error!\n");
    quit();
  }

  menu();
  while (read_until(STDIN, select, sizeof(select), '\n') > 0)
  {
    int menu = strtol(select, NULL, 10);
    switch (menu)
    {
      case 1:
        if (read_until(STDIN, buf, MAX_KTY_LENGTH, '\x00') > 0)
          import_kty(buf);
        else
          fdprintf(STDOUT, "Error!\n");
        break;
      case 2:
        print_kty();
        break;
      case 3:
        quit();
        break;
      case 777:
        nyan();
        break;
      default:
        fdprintf(STDOUT, "Invalid menu. Try again.\n");
        break;
    }
  }
  return 0;
}
