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

#include "cgc_malloc.h"
#include "cgc_stack.h"

stack_elem* cgc_stack_create() {
  stack_elem* top = cgc_calloc(sizeof(stack_elem));
  top->next = NULL;
  top->type = ST_TOP;

  return top;
}

void cgc_stack_free(stack_elem* stk) {
  if (NULL == stk) return;
  
  stack_elem* next = stk->next;
  cgc_free(stk);

  return cgc_stack_free(next);
}

stack_elem_type cgc_stack_next(stack_elem* stk) {
  if (cgc_stack_empty(stk)) return ST_TOP;
  return stk->next->type;
}

uint64 cgc_stack_empty(stack_elem* stk) {
  if (NULL == stk->next) return 1;
  return 0;
}

void cgc_stack_push_sint32(stack_elem* stk, sint32 i) {
  stack_elem* new_node = cgc_calloc(sizeof(stack_elem));
  stack_elem* previous_top = stk->next;
  new_node->next = previous_top;
  new_node->type = ST_SINT32;
  new_node->sint32 = i;
  stk->next = new_node;
}

void cgc_stack_push_uint64(stack_elem* stk, uint64 i) {
  stack_elem* new_node = cgc_calloc(sizeof(stack_elem));
  stack_elem* previous_top = stk->next;
  new_node->next = previous_top;
  new_node->type = ST_UINT64;
  new_node->uint64 = i;
  stk->next = new_node;
}

void cgc_stack_push_sint64(stack_elem* stk, sint64 i) {
  stack_elem* new_node = cgc_calloc(sizeof(stack_elem));
  stack_elem* previous_top = stk->next;
  new_node->next = previous_top;
  new_node->type = ST_SINT64;
  new_node->sint64 = i;
  stk->next = new_node;
}

void cgc_stack_push_lexeme_flavor(stack_elem* stk, lexeme_flavor f) {
  stack_elem* new_node = cgc_calloc(sizeof(stack_elem));
  stack_elem* previous_top = stk->next;
  new_node->next = previous_top;
  new_node->type = ST_LEXEME_FLAVOR;
  new_node->lexeme_flavor = f;
  stk->next = new_node;
}

void cgc_stack_push_operation_type(stack_elem* stk, operation_type t) {
  stack_elem* new_node = cgc_calloc(sizeof(stack_elem));
  stack_elem* previous_top = stk->next;
  new_node->next = previous_top;
  new_node->type = ST_OPERATION_TYPE;
  new_node->operation_type = t;
  stk->next = new_node;
}

void cgc_stack_push_str(stack_elem* stk, char* str) {
  stack_elem* new_node = cgc_calloc(sizeof(stack_elem));
  stack_elem* previous_top = stk->next;
  new_node->next = previous_top;
  new_node->type = ST_STR;
  new_node->str = str;
  stk->next = new_node;
}

sint32 cgc_stack_pop_sint32(stack_elem* stk) {
  stack_elem* old_top = stk->next;
  stack_elem* new_top = stk->next->next;
  sint32 val = old_top->sint32;
  stk->next = new_top;
  cgc_free(old_top);
  return val;
}

uint64 cgc_stack_pop_uint64(stack_elem* stk) {
  stack_elem* old_top = stk->next;
  stack_elem* new_top = stk->next->next;
  uint64 val = old_top->uint64;
  stk->next = new_top;
  cgc_free(old_top);
  return val;
}

sint64 cgc_stack_pop_sint64(stack_elem* stk) {
  stack_elem* old_top = stk->next;
  stack_elem* new_top = stk->next->next;
  sint64 val = old_top->sint64;
  stk->next = new_top;
  cgc_free(old_top);
  return val;
}

lexeme_flavor cgc_stack_pop_lexeme_flavor(stack_elem* stk) {
  stack_elem* old_top = stk->next;
  stack_elem* new_top = stk->next->next;
  lexeme_flavor val = old_top->lexeme_flavor;
  stk->next = new_top;
  cgc_free(old_top);
  return val;
}

operation_type cgc_stack_pop_operation_type(stack_elem* stk) {
  stack_elem* old_top = stk->next;
  stack_elem* new_top = stk->next->next;
  operation_type val = old_top->operation_type;
  stk->next = new_top;
  cgc_free(old_top);
  return val;
}

char* cgc_stack_pop_str(stack_elem* stk) {
  stack_elem* old_top = stk->next;
  stack_elem* new_top = stk->next->next;
  char* val = old_top->str;
  stk->next = new_top;
  cgc_free(old_top);
  return val;
}

void cgc_assert_lexeme_flavor_equal(lexeme_flavor expected, lexeme_flavor actual) {
  if (expected == actual) return;
  cgc__terminate(-1);
}

void cgc_assert_uint64_equal(uint64 expected, uint64 actual) {
  if (expected == actual) return;
  cgc__terminate(-1);
}

void cgc_refute_uint64_equal(uint64 expected, uint64 actual) {
  if (expected != actual) return;
  cgc__terminate(-1);
}

void cgc_stack_test() {
  stack_elem* first = cgc_stack_create();

  cgc_refute_uint64_equal(0, cgc_stack_empty(first));

  cgc_stack_push_uint64(first, 12345);
  cgc_assert_uint64_equal(0, cgc_stack_empty(first));

  cgc_assert_uint64_equal(12345, cgc_stack_pop_uint64(first));
  cgc_refute_uint64_equal(0, cgc_stack_empty(first));
  
  cgc_stack_push_uint64(first, 444);
  cgc_assert_uint64_equal(0, cgc_stack_empty(first));

  cgc_stack_push_lexeme_flavor(first, F_ASTERISK);
  cgc_assert_lexeme_flavor_equal(F_ASTERISK, cgc_stack_pop_lexeme_flavor(first));

  cgc_assert_uint64_equal(0, cgc_stack_empty(first));

  cgc_assert_uint64_equal(444, cgc_stack_pop_uint64(first));
  cgc_refute_uint64_equal(0, cgc_stack_empty(first));
}
