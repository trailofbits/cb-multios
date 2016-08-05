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

#include <malloc.h>
#include "stack.h"

stack_elem* stack_create() {
  stack_elem* top = calloc(sizeof(stack_elem));
  top->next = NULL;
  top->type = ST_TOP;

  return top;
}

void stack_free(stack_elem* stk) {
  if (NULL == stk) return;
  
  stack_elem* next = stk->next;
  free(stk);

  return stack_free(next);
}

stack_elem_type stack_next(stack_elem* stk) {
  if (stack_empty(stk)) return ST_TOP;
  return stk->next->type;
}

uint64 stack_empty(stack_elem* stk) {
  if (NULL == stk->next) return 1;
  return 0;
}

void stack_push_sint32(stack_elem* stk, sint32 i) {
  stack_elem* new_node = calloc(sizeof(stack_elem));
  stack_elem* previous_top = stk->next;
  new_node->next = previous_top;
  new_node->type = ST_SINT32;
  new_node->sint32 = i;
  stk->next = new_node;
}

void stack_push_uint64(stack_elem* stk, uint64 i) {
  stack_elem* new_node = calloc(sizeof(stack_elem));
  stack_elem* previous_top = stk->next;
  new_node->next = previous_top;
  new_node->type = ST_UINT64;
  new_node->uint64 = i;
  stk->next = new_node;
}

void stack_push_sint64(stack_elem* stk, sint64 i) {
  stack_elem* new_node = calloc(sizeof(stack_elem));
  stack_elem* previous_top = stk->next;
  new_node->next = previous_top;
  new_node->type = ST_SINT64;
  new_node->sint64 = i;
  stk->next = new_node;
}

void stack_push_lexeme_flavor(stack_elem* stk, lexeme_flavor f) {
  stack_elem* new_node = calloc(sizeof(stack_elem));
  stack_elem* previous_top = stk->next;
  new_node->next = previous_top;
  new_node->type = ST_LEXEME_FLAVOR;
  new_node->lexeme_flavor = f;
  stk->next = new_node;
}

void stack_push_operation_type(stack_elem* stk, operation_type t) {
  stack_elem* new_node = calloc(sizeof(stack_elem));
  stack_elem* previous_top = stk->next;
  new_node->next = previous_top;
  new_node->type = ST_OPERATION_TYPE;
  new_node->operation_type = t;
  stk->next = new_node;
}

void stack_push_str(stack_elem* stk, char* str) {
  stack_elem* new_node = calloc(sizeof(stack_elem));
  stack_elem* previous_top = stk->next;
  new_node->next = previous_top;
  new_node->type = ST_STR;
  new_node->str = str;
  stk->next = new_node;
}

sint32 stack_pop_sint32(stack_elem* stk) {
  stack_elem* old_top = stk->next;
  stack_elem* new_top = stk->next->next;
  sint32 val = old_top->sint32;
  stk->next = new_top;
  free(old_top);
  return val;
}

uint64 stack_pop_uint64(stack_elem* stk) {
  stack_elem* old_top = stk->next;
  stack_elem* new_top = stk->next->next;
  uint64 val = old_top->uint64;
  stk->next = new_top;
  free(old_top);
  return val;
}

sint64 stack_pop_sint64(stack_elem* stk) {
  stack_elem* old_top = stk->next;
  stack_elem* new_top = stk->next->next;
  sint64 val = old_top->sint64;
  stk->next = new_top;
  free(old_top);
  return val;
}

lexeme_flavor stack_pop_lexeme_flavor(stack_elem* stk) {
  stack_elem* old_top = stk->next;
  stack_elem* new_top = stk->next->next;
  lexeme_flavor val = old_top->lexeme_flavor;
  stk->next = new_top;
  free(old_top);
  return val;
}

operation_type stack_pop_operation_type(stack_elem* stk) {
  stack_elem* old_top = stk->next;
  stack_elem* new_top = stk->next->next;
  operation_type val = old_top->operation_type;
  stk->next = new_top;
  free(old_top);
  return val;
}

char* stack_pop_str(stack_elem* stk) {
  stack_elem* old_top = stk->next;
  stack_elem* new_top = stk->next->next;
  char* val = old_top->str;
  stk->next = new_top;
  free(old_top);
  return val;
}

void assert_lexeme_flavor_equal(lexeme_flavor expected, lexeme_flavor actual) {
  if (expected == actual) return;
  _terminate(-1);
}

void assert_uint64_equal(uint64 expected, uint64 actual) {
  if (expected == actual) return;
  _terminate(-1);
}

void refute_uint64_equal(uint64 expected, uint64 actual) {
  if (expected != actual) return;
  _terminate(-1);
}

void stack_test() {
  stack_elem* first = stack_create();

  refute_uint64_equal(0, stack_empty(first));

  stack_push_uint64(first, 12345);
  assert_uint64_equal(0, stack_empty(first));

  assert_uint64_equal(12345, stack_pop_uint64(first));
  refute_uint64_equal(0, stack_empty(first));
  
  stack_push_uint64(first, 444);
  assert_uint64_equal(0, stack_empty(first));

  stack_push_lexeme_flavor(first, F_ASTERISK);
  assert_lexeme_flavor_equal(F_ASTERISK, stack_pop_lexeme_flavor(first));

  assert_uint64_equal(0, stack_empty(first));

  assert_uint64_equal(444, stack_pop_uint64(first));
  refute_uint64_equal(0, stack_empty(first));
}
