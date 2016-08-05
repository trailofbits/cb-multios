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

#pragma once
#include "lexer.h"
#include "compiler.h"
#include "types.h"

typedef enum stack_elem_type_enum {
  ST_TOP = 0,
  ST_SINT32,
  ST_UINT64,
  ST_SINT64,
  ST_LEXEME_FLAVOR,
  ST_OPERATION_TYPE,
  ST_STR
} stack_elem_type;

typedef struct stack_elem_str {
  struct stack_elem_str* next;
  stack_elem_type type;
  union {
    sint32 sint32;
    uint64 uint64;
    sint64 sint64;
    lexeme_flavor lexeme_flavor;
    operation_type operation_type;
    char* str;
  };
} stack_elem;

stack_elem* stack_create();
void stack_free(stack_elem* stk);

uint64 stack_empty(stack_elem* stk);

void stack_push_sint32(stack_elem* stk, sint32 i);
void stack_push_uint64(stack_elem* stk, uint64 i);
void stack_push_sint64(stack_elem* stk, sint64 i);
void stack_push_lexeme_flavor(stack_elem* stk, lexeme_flavor f);
void stack_push_operation_type(stack_elem* stk, operation_type t);
void stack_push_str(stack_elem* stk, char* s);

sint32 stack_pop_sint32(stack_elem* stk);
uint64 stack_pop_uint64(stack_elem* stk);
sint64 stack_pop_sint64(stack_elem* stk);
lexeme_flavor stack_pop_lexeme_flavor(stack_elem* stk);
operation_type stack_pop_operation_type(stack_elem* stk);
char* stack_pop_str(stack_elem* stk);

void stack_test();
