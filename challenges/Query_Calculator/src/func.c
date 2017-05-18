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

#include "libcgc.h"
#include "cgc_string.h"
#include "cgc_char.h"
#include "cgc_func.h"
#include "cgc_malloc.h"
#include "cgc_protocol.h"
#include "cgc_eval.h"

#define FUNC(name, func) if (0 == cgc_strcmp(name, func_name)) return func(stk);

void cgc_ord(stack_elem* stk) {
  sint32 offset = cgc_stack_pop_sint32(stk);
  char* body = cgc_stack_pop_str(stk);

#ifdef PATCHED_1
  if (offset < 1) cgc__terminate(-1);
  if (offset > cgc_strlen(body)) cgc__terminate(-1);
#endif
  
  sint32 char_value = ((unsigned char*)body)[offset - 1];
  
  cgc_stack_push_sint32(stk, char_value);
}

void cgc_upcase(stack_elem* stk) {
  char* body = cgc_stack_pop_str(stk);
  uint32 len = cgc_strlen(body);
  char* new = cgc_calloc(len + 1);
  for (uint32 i = 0; i <= len; i++) {
    char cur = body[i];
    new[i] = cgc_char_is_lower(cur) ? (cur - 0x20) : cur;
  }
  cgc_stack_push_str(stk, new);
}


void cgc_downcase(stack_elem* stk) {
  char* body = cgc_stack_pop_str(stk);
  uint32 len = cgc_strlen(body);
  char* new = cgc_calloc(len + 1);
  for (uint32 i = 0; i <= len; i++) {
    char cur = body[i];
    new[i] = cgc_char_is_upper(cur) ? (cur + 0x20) : cur;
  }
  cgc_stack_push_str(stk, new);
}

void len(stack_elem* stk) {
  char* body = cgc_stack_pop_str(stk);
  uint32 len = cgc_strlen(body);
  cgc_stack_push_sint32(stk, len);
}

void cgc_idx(stack_elem* stk) {
  char needle = cgc_stack_pop_str(stk)[0];
  char* haystack = cgc_stack_pop_str(stk);
  uint32 len = cgc_strlen(haystack);
  for (uint32 i = 0; i <= len; i++) {
    char cur = haystack[i];
    if (cur == needle) {
      cgc_stack_push_sint32(stk, i + 1);
      return;
    }
  }
}

void cgc_ridx(stack_elem* stk) {
  char needle = cgc_stack_pop_str(stk)[0];
  char* haystack = cgc_stack_pop_str(stk);
  uint32 len = cgc_strlen(haystack);
  for (sint32 i = len; i >= 0; i--) {
    char cur = haystack[i];
    if (cur == needle) {
      cgc_stack_push_sint32(stk, i + 1);
      return;
    }
  }
}

void cgc_chomp(stack_elem* stk) {
  char* body = cgc_stack_pop_str(stk);
  uint32 len = cgc_strlen(body);
  char* new = cgc_calloc(len + 1);

  uint32 idx = 0;
  uint32 jdx = 0;
  while (cgc_char_is_whitespace(body[idx]) && (0 != body[idx])) {
    idx++;
  }

  while (!cgc_char_is_whitespace(body[idx]) && (0 != body[idx])) {
    new[jdx] = body[idx];
    idx++;
    jdx++;
  }
  
  cgc_stack_push_str(stk, new);
}

void cgc_func_eval(stack_elem* stk) {
  char* body = cgc_stack_pop_str(stk);
  sint32 result = cgc_eval_string(body);
  cgc_stack_push_sint32(stk, result);
}

void cgc_func_dispatch(stack_elem* stk, char* func_name) {
  FUNC("ord", cgc_ord);
  FUNC("upcase", cgc_upcase);
  FUNC("downcase", cgc_downcase);
  FUNC("len", len);
  FUNC("idx", cgc_idx);
  FUNC("ridx", cgc_ridx);
  FUNC("chomp", cgc_chomp);
  FUNC("eval", cgc_func_eval);

  cgc_protocol_send_str("eval error, unrecognized func");
  cgc__terminate(-1);
}
