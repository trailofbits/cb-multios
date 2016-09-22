#include <libcgc.h>
#include "types.h"
#include "protocol.h"
#include "lexer.h"
#include "stack.h"
#include "string.h"
#include "stdio.h"
#include "malloc.h"
#include "eval.h"

#define RANDOM_PAGE_ADDRESS 0x4347C000
#define RANDOM_PAGE_LENGTH 0x1000

void say_hello();
void run_loop();

int main(void) {
  types_check();
  lexer_test();
  stack_test();
  compiler_test();
  eval_test();

  say_hello();

  run_loop();
  
  return 0;
}

void say_hello() {
  unsigned char* magic_page = (unsigned char*)RANDOM_PAGE_ADDRESS;
  char qry[80];
  uint16 len = sprintf(qry, "FIND $d + $d + $d + $d FROM dual",
                       magic_page[0],
                       magic_page[1],
                       magic_page[2],
                       magic_page[3]);
  lexer_list* ll = lex_string(len, qry);
  compiler* clr = compile(ll);
  sint32 result = eval(clr);
  char result_buf[80];
  len = sprintf(result_buf, "cqltor ready $d", result);
  protocol_send_str(result_buf);
}

void run_loop() {
  while(1) {
    protocol_with_recv_string(^void(uint16 len, char* str) {
        if ((len == 4) && (strcmp("exit", str) == 0)) {
          _terminate(0);
        }
        
        lexer_list* ll = lex_string(len, str);
        if (F_ERROR == ll->content->flavor) {
          protocol_send_str("lexer error");
          return;
        }

        compiler* clr = compile(ll);
        if (NULL != clr->error_lexeme) {
          protocol_send_str("compiler error");
          return;
        }

        sint32 result = eval(clr);
        char* result_buf = calloc(16); //log10(2^32) < 16
        uint64 count = sprintf(result_buf, "$d", result);
        protocol_send_str(result_buf);
        free(result_buf);
      });
  }
}
