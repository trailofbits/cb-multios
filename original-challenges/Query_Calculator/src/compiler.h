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
#include "types.h"
#include "lexer.h"

typedef enum operation_type_enum {
  OP_NOP = 0,
  OP_PUSH_SINT32,
  OP_PUSH_CHARACTER_LITERAL,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_FUNCALL
} operation_type;

typedef struct operation_str {
  struct operation_str* next;
  operation_type type;
  sint32 sint32_value;
  uint16 character_literal_length;
  char* character_literal_value;
  char* function_name;
} operation;

typedef struct compiler_str {
  operation* find_list;
  char* relation_name;
  uint16 error_position;
  lexeme* error_lexeme;
} compiler;

compiler* compile(lexer_list* lexemes);
void compiler_free(compiler* cmp);

void compiler_test();
