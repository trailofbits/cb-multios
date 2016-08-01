#ifndef __FORM_H__
#define __FORM_H__

#define NUM_CMDS 5
#define MAX_CMD_SIZE 16

typedef struct question {
  const char *title;
  const char *hint;
  char *answer;
  char optional;
  struct question *prev, *next;
  int (*validator) (char *input);
} question_t;

typedef struct page {
  const char *title;
  struct page *prev, *next;
  question_t *questions;
  char completed;
} page_t;

typedef struct form {
  const char *greeting;
  const char *ending;
  const char *help;
  void (*init) (void);
  int (*handlers[NUM_CMDS]) (struct form *_form, char *arg);
  page_t *pages;
  page_t *cur_page;
  question_t *cur_question;
} form_t;

int handle_exit(form_t *form, char *arg);
int handle_help(form_t *form, char *arg);
int handle_next(form_t *form, char *arg);
int handle_prev(form_t *form, char *arg);
int handle_update(form_t *form, char *arg);
int handle_line(form_t *form, char *arg);
void print_prompt(form_t *form, int with_page, int done);
void print_greeting(form_t *form);

#define DEC_Q(_name, _title, _hint, _optional, _validator)  \
  static question_t _name = {                               \
    .title = _title,                                        \
    .hint = _hint,                                          \
    .answer = NULL,                                         \
    .optional = _optional,                                  \
    .prev = NULL,                                           \
    .next = NULL,                                           \
    .validator = _validator                                 \
  }

#define DEC_P(_name, _title)  \
  static page_t _name = {     \
    .title = _title,          \
    .prev = NULL,             \
    .next = NULL,             \
    .questions = NULL,        \
    .completed = 0            \
}

#define LINK(e, _prev, _next) \
  do {                        \
    e.prev = _prev;           \
    e.next = _next;           \
  } while (0)

#endif /* __FORM_H__ */
