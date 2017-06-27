#include "libcgc.h"
#include "cgc_types.h"
#include "cgc_protocol.h"
#include "cgc_lexer.h"
#include "cgc_stack.h"
#include "cgc_string.h"
#include "cgc_stdio.h"
#include "cgc_malloc.h"
#include "cgc_eval.h"

#define RANDOM_PAGE_ADDRESS 0x4347C000
#define RANDOM_PAGE_LENGTH 0x1000

void cgc_say_hello();
void cgc_run_loop();

int main(int cgc_argc, char *cgc_argv[]) {
  cgc_types_check();
  cgc_lexer_test();
  cgc_stack_test();
  cgc_compiler_test();
  cgc_eval_test();

  cgc_say_hello();

  cgc_run_loop();
  
  return 0;
}

void cgc_say_hello() {
  unsigned char* magic_page = (unsigned char*)RANDOM_PAGE_ADDRESS;
  char qry[80];
  uint16 len = cgc_sprintf(qry, "FIND $d + $d + $d + $d FROM dual",
                       magic_page[0],
                       magic_page[1],
                       magic_page[2],
                       magic_page[3]);
  lexer_list* ll = cgc_lex_string(len, qry);
  compiler* clr = cgc_compile(ll);
  sint32 result = cgc_eval(clr);
  char result_buf[80];
  len = cgc_sprintf(result_buf, "cqltor ready $d", result);
  cgc_protocol_send_str(result_buf);
}

void cgc_run_loop() {
  while(1) {
    cgc_protocol_with_recv_string(^void(uint16 len, char* str) {
        if ((len == 4) && (cgc_strcmp("exit", str) == 0)) {
          cgc__terminate(0);
        }
        
        lexer_list* ll = cgc_lex_string(len, str);
        if (F_ERROR == ll->content->flavor) {
          cgc_protocol_send_str("lexer error");
          return;
        }

        compiler* clr = cgc_compile(ll);
        if (NULL != clr->error_lexeme) {
          cgc_protocol_send_str("compiler error");
          return;
        }

        sint32 result = cgc_eval(clr);
        char* result_buf = cgc_calloc(16); //cgc_log10(2^32) < 16
        uint64 count = cgc_sprintf(result_buf, "$d", result);
        cgc_protocol_send_str(result_buf);
        cgc_free(result_buf);
      });
  }
}
