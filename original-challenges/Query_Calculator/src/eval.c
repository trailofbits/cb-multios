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
#include "eval.h"
#include "func.h"
#include "lexer.h"
#include "stack.h"
#include "string.h"
#include "protocol.h"

#define POP_POP second = stack_pop_sint32(stk); first = stack_pop_sint32(stk)
#define POP_POP_OP(op) POP_POP; stack_push_sint32(stk, first op second); break;

sint32 eval(compiler* clr) {
  operation* op = clr->find_list;
  stack_elem* stk = stack_create();

  do {
    sint32 first, second;
    
    switch (op->type) {
    case OP_PUSH_SINT32:
      stack_push_sint32(stk, op->sint32_value);
      break;
    case OP_ADD:
      POP_POP_OP(+);
    case OP_SUBTRACT:
      POP_POP_OP(-);
    case OP_MULTIPLY:
      POP_POP_OP(*);
    case OP_DIVIDE:
      POP_POP_OP(/);
    case OP_PUSH_CHARACTER_LITERAL:
      stack_push_str(stk, op->character_literal_value);
      break;
    case OP_FUNCALL:
      func_dispatch(stk, op->function_name);
      break;
    case OP_NOP:
      break;
    default:
      protocol_send_str("eval error, unrecognized operation");
      _terminate(-1);
    }

    op = op->next;
  } while (NULL != op);

  sint32 final_result = stack_pop_sint32(stk);

  if (!stack_empty(stk)) {
    protocol_send_str("eval error, left over stack entries");
    _terminate(-1);
  }

  return final_result;
}

sint32 eval_string(char* str) {
  lexer_list* ll = lex_string(strlen(str), str);
  compiler* clr = compile(ll);
  return eval(clr);
}

void assert_eval(sint32 expected, char* qry) {
  sint32 actual = eval_string(qry);
  if (expected != actual) _terminate(-1);
}

void eval_test() {
  assert_eval(0, "FIND 1 - 1 FROM dual");
  assert_eval(6, "FIND 1 + 2 + 3 FROM dual");
  assert_eval(3, "FIND 1 + 2 * 3 - 4 FROM dual");
  assert_eval(7, "FIND 1 + 2 * 3 FROM dual");
  assert_eval(0x41, "FIND ord('ABC', 1) FROM dual");
  assert_eval(0x42, "FIND ord('ABC', 2) FROM dual");
  assert_eval(0x43, "FIND ord('ABC', 3) FROM dual");
  assert_eval(0x41, "FIND ord(upcase('abc'), 1) FROM dual");
  assert_eval(0x61, "FIND ord(downcase('ABC'), 1) FROM dual");
  assert_eval(5, "FIND len('abcde') FROM dual");
  assert_eval(3, "FIND idx('abcde', 'c') FROM udal");
  assert_eval(3, "FIND ridx('abaco', 'a') FROM dual");
  assert_eval(2, "FIND eval('FIND 1 + 1 FROM dual') FROM dual");
  assert_eval(0x41, "FIND ord(chomp(' ABC'), 1) FROM dual");
}
