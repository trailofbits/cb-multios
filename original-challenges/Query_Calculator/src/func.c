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

#include <libcgc.h>
#include "string.h"
#include "char.h"
#include "func.h"
#include "malloc.h"
#include "protocol.h"
#include "eval.h"

#define FUNC(name, func) if (0 == strcmp(name, func_name)) return func(stk);

void ord(stack_elem* stk) {
  sint32 offset = stack_pop_sint32(stk);
  char* body = stack_pop_str(stk);

#ifdef PATCHED_1
  if (offset < 1) _terminate(-1);
  if (offset > strlen(body)) _terminate(-1);
#endif
  
  sint32 char_value = ((unsigned char*)body)[offset - 1];
  
  stack_push_sint32(stk, char_value);
}

void upcase(stack_elem* stk) {
  char* body = stack_pop_str(stk);
  uint32 len = strlen(body);
  char* new = calloc(len + 1);
  for (uint32 i = 0; i <= len; i++) {
    char cur = body[i];
    new[i] = char_is_lower(cur) ? (cur - 0x20) : cur;
  }
  stack_push_str(stk, new);
}


void downcase(stack_elem* stk) {
  char* body = stack_pop_str(stk);
  uint32 len = strlen(body);
  char* new = calloc(len + 1);
  for (uint32 i = 0; i <= len; i++) {
    char cur = body[i];
    new[i] = char_is_upper(cur) ? (cur + 0x20) : cur;
  }
  stack_push_str(stk, new);
}

void len(stack_elem* stk) {
  char* body = stack_pop_str(stk);
  uint32 len = strlen(body);
  stack_push_sint32(stk, len);
}

void idx(stack_elem* stk) {
  char needle = stack_pop_str(stk)[0];
  char* haystack = stack_pop_str(stk);
  uint32 len = strlen(haystack);
  for (uint32 i = 0; i <= len; i++) {
    char cur = haystack[i];
    if (cur == needle) {
      stack_push_sint32(stk, i + 1);
      return;
    }
  }
}

void ridx(stack_elem* stk) {
  char needle = stack_pop_str(stk)[0];
  char* haystack = stack_pop_str(stk);
  uint32 len = strlen(haystack);
  for (sint32 i = len; i >= 0; i--) {
    char cur = haystack[i];
    if (cur == needle) {
      stack_push_sint32(stk, i + 1);
      return;
    }
  }
}

void chomp(stack_elem* stk) {
  char* body = stack_pop_str(stk);
  uint32 len = strlen(body);
  char* new = calloc(len + 1);

  uint32 idx = 0;
  uint32 jdx = 0;
  while (char_is_whitespace(body[idx]) && (0 != body[idx])) {
    idx++;
  }

  while (!char_is_whitespace(body[idx]) && (0 != body[idx])) {
    new[jdx] = body[idx];
    idx++;
    jdx++;
  }
  
  stack_push_str(stk, new);
}

void func_eval(stack_elem* stk) {
  char* body = stack_pop_str(stk);
  sint32 result = eval_string(body);
  stack_push_sint32(stk, result);
}

void func_dispatch(stack_elem* stk, char* func_name) {
  FUNC("ord", ord);
  FUNC("upcase", upcase);
  FUNC("downcase", downcase);
  FUNC("len", len);
  FUNC("idx", idx);
  FUNC("ridx", ridx);
  FUNC("chomp", chomp);
  FUNC("eval", func_eval);

  protocol_send_str("eval error, unrecognized func");
  _terminate(-1);
}
