/*
 * Author: Garrett Barboza <garrett.barboza@kapricasecurity.com>
 *
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

#include <ctype.h>

#define NUM_ASCII_CHAR 128
#define ASCII_MASK 0x7F

// SPACE is first printable
#define SPACE 0x20

// DEL is only char after SPACE that is CNTRL
#define DEL 0x7F

static const unsigned char _punct[NUM_ASCII_CHAR] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0
};

static const unsigned char _xdigit[NUM_ASCII_CHAR] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

int isalnum(int c)
{
  return isalpha(c) || isdigit(c);
}

int isalpha(int c)
{
  return islower(c) || isupper(c);
}

int isascii(int c)
{
  return !(c & ~ASCII_MASK);
}

int isblank(int c)
{
  return (c == ' ' || c == '\t');
}

int iscntrl(int c)
{
  return c == DEL || c < SPACE;
}

int isdigit(int c)
{
  return (unsigned int ) c - '0' < 10;
}

int isgraph(int c)
{
  return c != ' ' && isprint(c);
}

int islower(int c)
{
  return (unsigned int) c - 'a' < 26;
}

int isprint(int c)
{
  return c >= SPACE && c != DEL;
}

int ispunct(int c)
{
  return _punct[c];
}

int isspace(int c)
{
  return (c > 8 && c < 14) || c == ' ';
}

int isupper(int c)
{
  return (unsigned int ) c - 'A' < 26;
}

int isxdigit(int c)
{
  return _xdigit[c];
}

int toascii(int c)
{
  return c & ASCII_MASK;
}

int tolower(int c)
{
  if (isupper(c))
    return c | SPACE;

  return c;
}

int toupper(int c)
{
  if (islower(c))
    return c & (~SPACE & ASCII_MASK);

  return c;
}
