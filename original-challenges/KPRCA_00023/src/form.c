/*
 * Copyright (c) 2014 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include <stdlib.h>
#include <string.h>

#include "form.h"
#include "input.h"

extern page_t education;
static const char *cmd_lbls[NUM_CMDS] = {
  "NEXT",
  "PREV",
  "UPDATE",
  "HELP",
  "EXIT"
};

static int handler_index(form_t *form, char *buf)
{
  int i;
  char *p = buf;
  char cmd_buf[MAX_CMD_SIZE];

  while (*p == '*' && p - buf < 2)
    p++;

  for (i = 0; i < NUM_CMDS; i++) {
    memcpy(cmd_buf, p, strlen(cmd_lbls[i]));
    cmd_buf[strlen(cmd_lbls[i])] = '\0';
    if (strncasecmp(cmd_buf, cmd_lbls[i], strlen(cmd_lbls[i])) == 0)
      return i;
  }

  return -1;
}

static int is_cmd(form_t *form, char *buf)
{
  if (strncmp("**", buf, 2))
    return 0;

  return handler_index(form, buf) >= 0;
}

static int page_complete(form_t *form)
{
  question_t *cur = form->cur_page->questions;
  int completed = 1;
  while (cur != NULL)
    if (!cur->optional && cur->answer == NULL) {
      completed = 0;
      break;
    } else {
      cur = cur->next;
    }

  return completed && form->cur_question == NULL;
}

static void print_title(form_t *form)
{
  if (strncmp(form->cur_page->title, "Fin", 3) == 0)
    printf("\nFinal Questions\n");
  else
    printf("\n%s Form\n", form->cur_page->title);
}


static int handle_cmd(form_t *form, char *buf)
{
  char *arg = malloc(strlen(buf) + 1);
  int ret;
  if (arg == NULL)
    return -1;
  strcpy(arg, buf);
  arg[strlen(buf)] = '\0';
  char *cmd = strsep(&arg, " ");
  int i = handler_index(form, cmd);
  if (i < 0) {
    ret = i;
    goto out;
  }

  ret = form->handlers[i](form, arg);
out:
  if (cmd != NULL) {
    free(cmd);
  }
  return ret;
}

static int handle_answer(form_t *form, char *input)
{
  if (!form->cur_question->validator(input))
    return 1;

  if (form->cur_question->answer != NULL) {
    free(form->cur_question->answer);
  }

  form->cur_question->answer = malloc(strlen(input) + 1);
  if (form->cur_question->answer == NULL)
    return -1;

  strcpy(form->cur_question->answer, input);
  return 0;
}

static int next_question(form_t *form)
{
  if (form->cur_question == NULL)
    return -1;

  if (form->cur_question->next == NULL) {
    form->cur_page->completed = 1;
  } else {
    form->cur_question = form->cur_question->next;
  }
  return 0;
}

static void print_page(form_t *form)
{
  question_t *cur = form->cur_page->questions;
  if (strncmp(form->cur_page->title, "Edu", 3) == 0)
    printf("\n*********Highest %s:*********\n", form->cur_page->title);
  else if (strncmp(form->cur_page->title, "Emp", 3) == 0)
    printf("\n*********Most Recent Employer:*********\n", form->cur_page->title);
  else if (strncmp(form->cur_page->title, "Fin", 3) == 0)
    printf("\n*********Final Screening:*********\n", form->cur_page->title);
  else
    printf("\n*********%s:*********\n", form->cur_page->title);

  for (; cur != NULL; cur = cur->next)
    if (cur->answer != NULL)
      printf("%s=%s\n", cur->title, cur->answer);
    else
      printf("%s=\n", cur->title);
}

static void prompt_next(void)
{
  printf("\nType **next to continue\n");
}


static int next_page(form_t *form)
{
  if (form->cur_page == NULL)
    return -1;

  if (form->cur_page->next == NULL)
    return 1;

  form->cur_page = form->cur_page->next;
  form->cur_question = form->cur_page->questions;
  return 0;
}

static void print_next_title(form_t *form)
{

  if (form->cur_page->next->title == NULL)
    printf("%s", form->ending);
  else if (strncmp(form->cur_page->next->title, "Fin", 3) == 0)
    printf("\nFinal Questions\n");
  else
    printf("\n%s Form\n", form->cur_page->next->title);
}

static void prompt_q(question_t *q)
{
  if (q->hint != NULL)
    printf("%s%s: ", q->title, q->hint);
  else
    printf("%s: ", q->title);
}

int handle_next(form_t *form, char *arg)
{
  int ret;

  if (form->cur_page->title == NULL) {
    return 1;
  }

  if (!form->cur_page->completed) {
    print_next_title(form);
    printf("You must complete the previous page before proceeding to this page\n");
    return 1;
  }

  ret = next_page(form);
  if (ret < 0)
    return -1;

  if (ret != 0) {
    return 2;
  }

  while(form->cur_question != NULL && form->cur_question->next != NULL && form->cur_question->answer != NULL)
    form->cur_question = form->cur_question->next;

  return 1;
}

int handle_exit(form_t *form, char *arg)
{
  printf("Thank you!\n");
  exit(0);
  return 0;
}

int handle_help(form_t *form, char *arg)
{
  printf("%s", form->help);
  return 1;
}

int handle_prev(form_t *form, char *arg)
{
  if (form->cur_page == NULL)
    return -1;

  if (form->cur_page->prev == NULL) {
    print_title(form);
    return 0;
  }

  form->cur_page = form->cur_page->prev;
  form->cur_question = form->cur_page->questions;

  return 1;
}

int handle_update(form_t *form, char *arg)
{
  question_t *cur;
  char *input_buf;

  if (!form->cur_page->completed) {
    printf("Cannot update field until all fields are inputted\n");
    return 1;
  }

  if (arg == NULL)
    return 1;

  cur = form->cur_page->questions;
  for(; cur != NULL; cur = cur->next)
    if (strncmp(cur->title, arg, strlen(cur->title)) == 0)
      break;

  if (cur == NULL) {
    printf("Could not find specified field\n");
    printf("Update Unsuccessful\n");
    return 1;
  }

  input_buf = malloc(LINE_SIZE);
  if (input_buf == NULL)
    return -1;

  prompt_q(cur);
  if (read_line(input_buf) < 0)
    return -1;

  if ((strlen(input_buf) == 0) && cur->optional) {
    if (input_buf != NULL) {
      free(input_buf);
    }

    if (cur->answer != NULL) {
      free(cur->answer);
    }

    cur->answer = NULL;
    return 1;
  }

  if (!cur->validator(input_buf)) {
    if (input_buf != NULL) {
      free(input_buf);
    }

    printf("Bad input.\n");
    printf("Update Unsuccessful\n");
    return 1;
  }

  if (cur->answer == NULL) {
    cur->answer = input_buf;
#ifdef PATCHED
  } else if (strncmp(cur->answer, input_buf, strlen(input_buf)) == 0) {
#else
  } else if (strncmp(cur->answer, input_buf, strlen(cur->answer)) == 0) {
#endif
    strcpy(cur->answer, input_buf);
    free(input_buf);
  } else {
    free(cur->answer);
    cur->answer = input_buf;
  }

  return 1;
}

void print_prompt(form_t *form, int with_title, int done)
{

  if (form->cur_page->title == NULL) {
    printf("%s", form->ending);
    return;
  }

  if (with_title)
    print_title(form);

  if (form->cur_page->completed) {
    print_page(form);
    prompt_next();
    return;
  }

  prompt_q(form->cur_question);
}

int handle_line(form_t *form, char *buf)
{
  int ret;

  if (is_cmd(form, buf))
    return handle_cmd(form, buf);

  if (form->cur_page->completed || form->cur_question == NULL) {
    return 1;
  }

  if (strlen(buf) == 0) {
    if (!form->cur_question->optional)
      return 0;
  } else {
    ret = handle_answer(form, buf);
    if (ret < 0)
      return -1;
    if (ret != 0)
      return 0;
  }

  ret = next_question(form);
  if (ret < 0)
    return -1;
  else
    return 0;

}

void print_greeting(form_t *form)
{
  printf("%s", form->greeting);
}
