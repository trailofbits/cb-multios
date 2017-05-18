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

#include "cgc_stdlib.h"
#include "cgc_malloc.h"
#include "cgc_string.h"
#include "cgc_lexer.h"
#include "cgc_types.h"
#include "cgc_char.h"

#define streq(s1, s2) (0 == cgc_strcmp(s1, s2))
#define flmatch(s1,s2, flav) if streq(s1, s2) return flav;

typedef enum character_class_enum {
  C_LETTER,
  C_DIGIT,
  C_WHITESPACE,
  C_PLUS,
  C_MINUS,
  C_ASTERISK,
  C_SOLIDUS,
  C_UNDERSCORE,
  C_COMMA,
  C_OPEN_PAREN,
  C_CLOSE_PAREN,
  C_APOSTROPHE,
  C_UNRECOGNIZED
} character_class;

typedef struct lexer_state_str {
  uint16 total_length;
  char* entire;
  char* remainder;
  lexer_list* head;
  lexer_list* tail;
  uint8 error;
} lexer_state;

character_class cgc_classify(char c);
void cgc_free_lexer_list(lexer_list* to_free);
void cgc_free_lexeme(lexeme*);
lexeme_flavor cgc_get_flavor(lexeme* to_flavor);

lexer_state cgc_lex_single_byte(lexer_state in);
lexer_state cgc_lex_character_literal(lexer_state in);
lexer_state cgc_lex_word(lexer_state in);
lexer_state cgc_lex_number(lexer_state in);

lexer_state cgc_lexer_error(lexer_state in);

sint16 cgc_remaining_bytes(lexer_state st);

lexer_list* cgc_lex_string(uint16 len, char* str) {
  lexer_state st;
  st.error = 0;
  st.total_length = len;
  st.entire = st.remainder = str;
  st.head = st.tail = cgc_calloc(sizeof(lexer_list));
    
  while (cgc_remaining_bytes(st) > 0) {
    char peek = st.remainder[0];
    switch (cgc_classify(peek)) {
    case C_WHITESPACE:
      st.remainder++;
      break;
    case C_PLUS:
    case C_MINUS:
    case C_ASTERISK:
    case C_SOLIDUS:
    case C_COMMA:
    case C_OPEN_PAREN:
    case C_CLOSE_PAREN:
      st = cgc_lex_single_byte(st);
      break;
    case C_APOSTROPHE:
      st = cgc_lex_character_literal(st);
      break;
    case C_LETTER:
      st = cgc_lex_word(st);
      break;
    case C_DIGIT:
      st = cgc_lex_number(st);
      break;
    default:
      st = cgc_lexer_error(st);
    }
  }

  return st.head->next;
}

character_class cgc_classify(char c) {
  switch (c) {
  case ' ': return C_WHITESPACE;
  case '+': return C_PLUS;
  case '-': return C_MINUS;
  case '*': return C_ASTERISK;
  case '/': return C_SOLIDUS;
  case '_': return C_UNDERSCORE;
  case ',': return C_COMMA;
  case '(': return C_OPEN_PAREN;
  case ')': return C_CLOSE_PAREN;
  case '\'': return C_APOSTROPHE;
  }

  if (cgc_char_is_num(c)) return C_DIGIT;
  if (cgc_char_is_alpha(c)) return C_LETTER;

  return C_UNRECOGNIZED;
}

void cgc_free_lexer_list(lexer_list* to_free) {
  cgc_free_lexeme(to_free->content);
  lexer_list* next_to_free;
  if (NULL == (next_to_free = to_free->next)) return;

  cgc_free(to_free);
  return cgc_free_lexer_list(next_to_free);
}

void cgc_free_lexeme(lexeme* to_free) {
  if (NULL == to_free) return;
  
  cgc_free(to_free->bytes);
  cgc_free(to_free);
}

lexeme_flavor cgc_get_single_byte_flavor(char first_byte);

lexeme_flavor cgc_get_flavor(lexeme* to_flavor) {
  char* b = to_flavor->bytes;
  
  if (to_flavor->bytes_len == 2) {
    return cgc_get_single_byte_flavor(b[0]);
  }
  
  flmatch("FIND", b, F_FIND);
  flmatch("FROM", b, F_FROM);

  lexeme_flavor candidate = cgc_get_single_byte_flavor(b[0]);

  if ((candidate != F_INTEGER_LITERAL) &&
      (candidate != F_IDENTIFIER)) {
    // no multiple-byte types other than these
    return F_ERROR;
  }
  
  for (uint16 i = 1; i < (to_flavor->bytes_len - 1); i++) {
    char c = b[i];
    if (!cgc_char_is_num(c) && (candidate == F_INTEGER_LITERAL)) {
      // hack this part to support floats
      return F_ERROR;
    }

    if (!cgc_char_is_alpha(c) &&
        !cgc_char_is_num(c) &&
        (c != '_') &&
        (candidate == F_IDENTIFIER)) {
      // non-alphanumeric or underscore in identifier
      return F_ERROR;
    }
  }

  return candidate;
}

lexeme_flavor cgc_get_single_byte_flavor(char first_byte) {
  // catch symbols
  switch (first_byte) {
  case '+': return F_PLUS;
  case '-': return F_MINUS;
  case '*': return F_ASTERISK;
  case '/': return F_SOLIDUS;
  case ',': return F_COMMA;
  case '(': return F_OPEN_PAREN;
  case ')': return F_CLOSE_PAREN;
  }

  // single digit integers
  if (cgc_char_is_num(first_byte)) return F_INTEGER_LITERAL;

  // single-letter identifiers
  if (cgc_char_is_alpha(first_byte)) return F_IDENTIFIER;
  
  return F_ERROR;  
}

lexer_state cgc_lex_single_byte(lexer_state in) {
  lexer_state out = in;
  lexer_list* new_tail = out.tail->next = cgc_calloc(sizeof(lexer_list));
  out.tail = new_tail;
  lexeme* content = new_tail->content = cgc_calloc(sizeof(lexeme));
  char b = in.remainder[0];
  content->flavor = cgc_get_single_byte_flavor(b);
  content->bytes_len = 1;
  content->bytes = cgc_calloc(2);
  content->bytes[0] = b;
  out.remainder++;
  
  return out;
}

lexer_state cgc_lex_character_literal(lexer_state in) {
  lexer_state out = in;
  char* apostrophe = in.remainder;
  char* cur = apostrophe + 1;
  uint16 bytes_len = 0;

  while (cur[0] != '\'') {
    bytes_len++;
    cur++;
  }

  lexer_list* new_tail = out.tail->next = cgc_calloc(sizeof(lexer_list));
  out.tail = new_tail;
  lexeme* content = new_tail->content = cgc_calloc(sizeof(lexeme));
  content->flavor = F_CHARACTER_LITERAL;
  content->bytes_len = bytes_len;
  content->bytes = cgc_calloc(bytes_len + 1);

  for (uint16 i = 0; i < bytes_len; i++) {
    content->bytes[i] = apostrophe[i+1];
  }

  out.remainder += bytes_len + 2;
  
  return out;
}

lexer_state cgc_lex_word(lexer_state in) {
  lexer_state out = in;
  char* start = in.remainder;
  char* cur = in.remainder;
  uint16 bytes_len = 0;

  while (cgc_char_is_alpha(cur[0]) || cgc_char_is_num(cur[0])) {
    bytes_len++;
    cur++;
  }

  lexer_list* new_tail = out.tail->next = cgc_calloc(sizeof(lexer_list));
  out.tail = new_tail;
  lexeme* content = new_tail->content = cgc_calloc(sizeof(lexeme));
  content->bytes_len = bytes_len;
  content->bytes = cgc_calloc(bytes_len + 1);
  cgc_memcpy(content->bytes, start, bytes_len);
  content->flavor = cgc_get_flavor(content);

  out.remainder += bytes_len;
  
  return out;
}

lexer_state cgc_lex_number(lexer_state in) {
  lexer_state out = in;
  char* start = in.remainder;
  char* cur = in.remainder;
  uint16 bytes_len = 0;

  while (cgc_char_is_num(cur[0]) && bytes_len <= 5) {
    bytes_len++;
    cur++;
  }

  lexer_list* new_tail = out.tail->next = cgc_calloc(sizeof(lexer_list));
  out.tail = new_tail;
  lexeme* content = new_tail->content = cgc_calloc(sizeof(lexeme));
  content->bytes_len = bytes_len;
  content->bytes = cgc_calloc(bytes_len + 1);
  cgc_memcpy(content->bytes, start, bytes_len);
  content->flavor = F_INTEGER_LITERAL;

  out.remainder = cur;
  return out;
}

lexer_state cgc_lexer_error(lexer_state in) {
  lexer_state out = in;
  out.error = 1;
  lexer_list* new_tail = out.tail->next = cgc_calloc(sizeof(lexer_list));
  out.tail = new_tail;
  lexeme* err = new_tail->content = cgc_calloc(sizeof(lexeme));
  err->flavor = F_ERROR;
  err->bytes_len = (in.remainder - in.entire + 1);
  err->bytes = cgc_calloc(err->bytes_len + 1);
  cgc_memcpy(err->bytes, in.remainder, err->bytes_len - 1);

  return out;
}

sint16 cgc_remaining_bytes(lexer_state st) {
  if (st.error) return 0;
  
  uint16 so_far = st.remainder - st.entire;
  return st.total_length - so_far;
}

void cgc_assert_lexeme_flavor(lexeme_flavor desired, lexeme* lexeme) {
  lexeme_flavor actual = lexeme->flavor;
  if (desired != actual) {
    // SET BREAKPOINT HERE
    cgc__terminate(-1);
  }
}

void cgc_assert_lex(lexeme_flavor desired, char* str) {
  lexer_list* out = cgc_lex_string(cgc_strlen(str), str);
  if ((desired == F_ERROR) && (NULL == out)) return;
  lexeme_flavor actual = out->content->flavor;

  if (desired != actual) {
    cgc__terminate(-1);
  }
}

#define assert_chase(des, count) cgc_assert_lexeme_flavor(des, cgc_lex_chase(lexed, count));

lexeme* cgc_lex_chase(lexer_list* list, uint16 count) {
  if (count == 0) return list->content;
  return cgc_lex_chase(list->next, count - 1);
}

void cgc_lexer_test() {
  lexeme blank;
  lexeme* l = &blank;
  
  cgc_assert_lex(F_FIND, "FIND");
  cgc_assert_lex(F_INTEGER_LITERAL, "5");
  cgc_assert_lex(F_INTEGER_LITERAL, "12345");
  cgc_assert_lex(F_INTEGER_LITERAL, "987715");
  cgc_assert_lex(F_INTEGER_LITERAL, "5.5");
  cgc_assert_lex(F_ERROR, ".5");
  cgc_assert_lex(F_PLUS, "+");
  cgc_assert_lex(F_PLUS, "+5.5");
  cgc_assert_lex(F_MINUS, "-");
  cgc_assert_lex(F_ASTERISK, "*");
  cgc_assert_lex(F_SOLIDUS, "/");
  cgc_assert_lex(F_FROM, "FROM");
  cgc_assert_lex(F_IDENTIFIER, "dual");
  cgc_assert_lex(F_IDENTIFIER, "my_cool_table_12345");
  cgc_assert_lex(F_OPEN_PAREN, "(");
  cgc_assert_lex(F_COMMA, ",");
  cgc_assert_lex(F_CLOSE_PAREN, ")");
  cgc_assert_lex(F_CHARACTER_LITERAL, "'abc'");

  char* sample = "FIND 1 + 2 / 3 * 4 FROM my_cool_table_12345";
  lexer_list* lexed = cgc_lex_string(cgc_strlen(sample), sample);

  assert_chase(F_FIND, 0);
  assert_chase(F_INTEGER_LITERAL, 1);
  assert_chase(F_PLUS, 2);
  assert_chase(F_INTEGER_LITERAL, 3);
  assert_chase(F_SOLIDUS, 4);
  assert_chase(F_INTEGER_LITERAL, 5);
  assert_chase(F_ASTERISK, 6);
  assert_chase(F_INTEGER_LITERAL, 7);
  assert_chase(F_FROM, 8);
  assert_chase(F_IDENTIFIER, 9);

  sample = "FIND 'abc' FROM rad_table";
  lexed = cgc_lex_string(cgc_strlen(sample), sample);

  assert_chase(F_CHARACTER_LITERAL, 1);

  sample = "FIND func('abc', 1, 2) FROM cool_table";
  lexed = cgc_lex_string(cgc_strlen(sample), sample);

  assert_chase(F_FIND, 0);
  assert_chase(F_IDENTIFIER, 1);
  assert_chase(F_OPEN_PAREN, 2);
  assert_chase(F_CHARACTER_LITERAL, 3);
  assert_chase(F_COMMA, 4);
  assert_chase(F_INTEGER_LITERAL, 5);
  assert_chase(F_COMMA, 6);
  assert_chase(F_INTEGER_LITERAL, 7);
  assert_chase(F_CLOSE_PAREN, 8);
  assert_chase(F_FROM, 9);
  assert_chase(F_IDENTIFIER, 10);
}
