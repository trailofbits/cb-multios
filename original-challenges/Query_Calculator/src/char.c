/*

Copyright (c) 2016 Cromulence LLC

Authors: Bryce Kerley <bk@cromulence.com>

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

#include "char.h"

uint8 char_is_num(char c) {
  return (('0' <= c) && ('9' >= c));
}

uint8 char_is_lower(char c) {
  return (('a' <= c) && ('z' >= c));
}

uint8 char_is_upper(char c) {
  return (('A' <= c) && ('Z' >= c));
}

uint8 char_is_alpha(char c) {
  return char_is_lower(c) || char_is_upper(c);
}

uint8 char_is_whitespace(char c) {
  if (c == ' ') return 1;
  if (c == '\n') return 1;
  if (c == '\t') return 1;
  if (c == '\v') return 1;
  
  return 0;
}
