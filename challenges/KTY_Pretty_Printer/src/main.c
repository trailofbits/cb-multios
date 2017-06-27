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

#include "libcgc.h"
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_ctype.h"

#include "cgc_kty.h"

#define MAX_KTY_LENGTH 8192

kty_parser_t *parser;
kty_item_t *my_kty;

int cgc_read_until(int fd, char *buf, cgc_size_t len, char delim)
{
  cgc_size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    cgc_size_t rx;
    if (cgc_receive(fd, c, 1, &rx) != 0 || rx == 0)
      return -1;
    if (*(c++) == delim)
      break;
  }
  *(c-1) = '\0';
  return c - buf;
}

void cgc_import_kty(char *buf)
{
  if (my_kty != NULL)
  {
    cgc_free_kty_item(my_kty);
    my_kty = NULL;
  }

  parser->cats = 0;
  my_kty = parser->loads(buf);

  if (my_kty == NULL)
    cgc_fdprintf(STDOUT, "Error!\n");
}

void cgc_print_kty()
{
  if (my_kty == NULL)
  {
    cgc_fdprintf(STDOUT, "Error!\n");
    return;
  }

  parser->cats = 0;
  parser->dumps(my_kty);
}

void cgc_nyan()
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
    cgc_fdprintf(STDOUT, "Error!\n");
    return;
  }
  parser->dumps(my_kty);
  if (parser->cats < 3)
    return;

  cgc_fdprintf(STDOUT, "%s", nyan_cat);

  c = buf;
  for (i = 0; i < cgc_array_length(parser->nyan_says); ++i)
  {
    kty_item_t *item = cgc_array_get(parser->nyan_says, i);
#if PATCHED
    int sz = (buf + sizeof(buf) - c) - cgc_strlen(item->item.i_string.s);
    sz = sz > 0 ? cgc_strlen(item->item.i_string.s) : (buf + sizeof(buf) - c - 1);
    cgc_memcpy(c, item->item.i_string.s, sz);
#else
    cgc_strcpy(c, item->item.i_string.s);
#endif
    c += item->item.i_string.len;
  }
  cgc_fdprintf(STDOUT, "NYAN SAYS...\n\"\n%s\n\"", buf);
}

void cgc_quit()
{
  cgc_fdprintf(STDOUT, "\n\n=^.^=// Bye!\n\n");
  cgc_exit(0);
}

void cgc_menu()
{
  cgc_fdprintf(STDOUT, "=======================\n");
  cgc_fdprintf(STDOUT, " 1. Import KTY\n");
  cgc_fdprintf(STDOUT, " 2. Print KTY\n");
  cgc_fdprintf(STDOUT, " 3. Quit\n");
  cgc_fdprintf(STDOUT, "=======================\n");
}

int main(int cgc_argc, char *cgc_argv[])
{
  char buf[MAX_KTY_LENGTH];
  char cgc_select[16];
  cgc_fdprintf(STDOUT, "KTY Pretty Printer v0.1\n");

  parser = (kty_parser_t *) cgc_malloc(sizeof(kty_parser_t));
  if (cgc_kty_init(parser) != 0)
  {
    cgc_fdprintf(STDOUT, "Error!\n");
    cgc_quit();
  }

  cgc_menu();
  while (cgc_read_until(STDIN, cgc_select, sizeof(cgc_select), '\n') > 0)
  {
    int menu = cgc_strtol(cgc_select, NULL, 10);
    switch (menu)
    {
      case 1:
        if (cgc_read_until(STDIN, buf, MAX_KTY_LENGTH, '\x00') > 0)
          cgc_import_kty(buf);
        else
          cgc_fdprintf(STDOUT, "Error!\n");
        break;
      case 2:
        cgc_print_kty();
        break;
      case 3:
        cgc_quit();
        break;
      case 777:
        cgc_nyan();
        break;
      default:
        cgc_fdprintf(STDOUT, "Invalid menu. Try again.\n");
        break;
    }
  }
  return 0;
}
