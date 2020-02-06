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
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_form.h"
#include "cgc_input.h"

extern page_t education;
static const char *cmd_lbls[NUM_CMDS] = {
  "NEXT",
  "PREV",
  "UPDATE",
  "HELP",
  "EXIT"
};

static int cgc_handler_index(form_t *form, char *buf)
{
  int i;
  char *p = buf;
  char cmd_buf[MAX_CMD_SIZE];

  while (*p == '*' && p - buf < 2)
    p++;

  for (i = 0; i < NUM_CMDS; i++) {
    cgc_memcpy(cmd_buf, p, cgc_strlen(cmd_lbls[i]));
    cmd_buf[cgc_strlen(cmd_lbls[i])] = '\0';
    if (cgc_strncasecmp(cmd_buf, cmd_lbls[i], cgc_strlen(cmd_lbls[i])) == 0)
      return i;
  }

  return -1;
}

static int cgc_is_cmd(form_t *form, char *buf)
{
  if (cgc_strncmp("**", buf, 2))
    return 0;

  return cgc_handler_index(form, buf) >= 0;
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

static void cgc_print_title(form_t *form)
{
  if (cgc_strncmp(form->cur_page->title, "Fin", 3) == 0)
    cgc_printf("\nFinal Questions\n");
  else
    cgc_printf("\n%s Form\n", form->cur_page->title);
}


static int cgc_handle_cmd(form_t *form, char *buf)
{
  char *arg = cgc_malloc(cgc_strlen(buf) + 1);
  int ret;
  if (arg == NULL)
    return -1;
  cgc_strcpy(arg, buf);
  arg[cgc_strlen(buf)] = '\0';
  char *cmd = cgc_strsep(&arg, " ");
  int i = cgc_handler_index(form, cmd);
  if (i < 0) {
    ret = i;
    goto out;
  }

  ret = form->handlers[i](form, arg);
out:
  if (cmd != NULL) {
    cgc_free(cmd);
  }
  return ret;
}

static int cgc_handle_answer(form_t *form, char *input)
{
  if (!form->cur_question->validator(input))
    return 1;

  if (form->cur_question->answer != NULL) {
    cgc_free(form->cur_question->answer);
  }

  form->cur_question->answer = cgc_malloc(cgc_strlen(input) + 1);
  if (form->cur_question->answer == NULL)
    return -1;

  cgc_strcpy(form->cur_question->answer, input);
  return 0;
}

static int cgc_next_question(form_t *form)
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

static void cgc_print_page(form_t *form)
{
  question_t *cur = form->cur_page->questions;
  if (cgc_strncmp(form->cur_page->title, "Edu", 3) == 0)
    cgc_printf("\n*********Highest %s:*********\n", form->cur_page->title);
  else if (cgc_strncmp(form->cur_page->title, "Emp", 3) == 0)
    cgc_printf("\n*********Most Recent Employer:*********\n", form->cur_page->title);
  else if (cgc_strncmp(form->cur_page->title, "Fin", 3) == 0)
    cgc_printf("\n*********Final Screening:*********\n", form->cur_page->title);
  else
    cgc_printf("\n*********%s:*********\n", form->cur_page->title);

  for (; cur != NULL; cur = cur->next)
    if (cur->answer != NULL)
      cgc_printf("%s=%s\n", cur->title, cur->answer);
    else
      cgc_printf("%s=\n", cur->title);
}

static void cgc_prompt_next(void)
{
  cgc_printf("\nType **next to continue\n");
}


static int cgc_next_page(form_t *form)
{
  if (form->cur_page == NULL)
    return -1;

  if (form->cur_page->next == NULL)
    return 1;

  form->cur_page = form->cur_page->next;
  form->cur_question = form->cur_page->questions;
  return 0;
}

static void cgc_print_next_title(form_t *form)
{

  if (form->cur_page->next->title == NULL)
    cgc_printf("%s", form->ending);
  else if (cgc_strncmp(form->cur_page->next->title, "Fin", 3) == 0)
    cgc_printf("\nFinal Questions\n");
  else
    cgc_printf("\n%s Form\n", form->cur_page->next->title);
}

static void cgc_prompt_q(question_t *q)
{
  if (q->hint != NULL)
    cgc_printf("%s%s: ", q->title, q->hint);
  else
    cgc_printf("%s: ", q->title);
}

int cgc_handle_next(form_t *form, char *arg)
{
  int ret;

  if (form->cur_page->title == NULL) {
    return 1;
  }

  if (!form->cur_page->completed) {
    cgc_print_next_title(form);
    cgc_printf("You must complete the previous page before proceeding to this page\n");
    return 1;
  }

  ret = cgc_next_page(form);
  if (ret < 0)
    return -1;

  if (ret != 0) {
    return 2;
  }

  while(form->cur_question != NULL && form->cur_question->next != NULL && form->cur_question->answer != NULL)
    form->cur_question = form->cur_question->next;

  return 1;
}

int cgc_handle_exit(form_t *form, char *arg)
{
  cgc_printf("Thank you!\n");
  cgc_exit(0);
  return 0;
}

int cgc_handle_help(form_t *form, char *arg)
{
  cgc_printf("%s", form->help);
  return 1;
}

int cgc_handle_prev(form_t *form, char *arg)
{
  if (form->cur_page == NULL)
    return -1;

  if (form->cur_page->prev == NULL) {
    cgc_print_title(form);
    return 0;
  }

  form->cur_page = form->cur_page->prev;
  form->cur_question = form->cur_page->questions;

  return 1;
}

int cgc_handle_update(form_t *form, char *arg)
{
  question_t *cur;
  char *input_buf;

  if (!form->cur_page->completed) {
    cgc_printf("Cannot update field until all fields are inputted\n");
    return 1;
  }

  if (arg == NULL)
    return 1;

  cur = form->cur_page->questions;
  for(; cur != NULL; cur = cur->next)
    if (cgc_strncmp(cur->title, arg, cgc_strlen(cur->title)) == 0)
      break;

  if (cur == NULL) {
    cgc_printf("Could not find specified field\n");
    cgc_printf("Update Unsuccessful\n");
    return 1;
  }

  input_buf = cgc_malloc(LINE_SIZE);
  if (input_buf == NULL)
    return -1;

  cgc_prompt_q(cur);
  if (cgc_read_line(input_buf) < 0)
    return -1;

  if ((cgc_strlen(input_buf) == 0) && cur->optional) {
    if (input_buf != NULL) {
      cgc_free(input_buf);
    }

    if (cur->answer != NULL) {
      cgc_free(cur->answer);
    }

    cur->answer = NULL;
    return 1;
  }

  if (!cur->validator(input_buf)) {
    if (input_buf != NULL) {
      cgc_free(input_buf);
    }

    cgc_printf("Bad input.\n");
    cgc_printf("Update Unsuccessful\n");
    return 1;
  }

  if (cur->answer == NULL) {
    cur->answer = input_buf;
#ifdef PATCHED
  } else if (cgc_strncmp(cur->answer, input_buf, cgc_strlen(input_buf)) == 0) {
#else
  } else if (cgc_strncmp(cur->answer, input_buf, cgc_strlen(cur->answer)) == 0) {
#endif
    cgc_strcpy(cur->answer, input_buf);
    cgc_free(input_buf);
  } else {
    cgc_free(cur->answer);
    cur->answer = input_buf;
  }

  return 1;
}

void cgc_print_prompt(form_t *form, int with_title, int done)
{

  if (form->cur_page->title == NULL) {
    cgc_printf("%s", form->ending);
    return;
  }

  if (with_title)
    cgc_print_title(form);

  if (form->cur_page->completed) {
    cgc_print_page(form);
    cgc_prompt_next();
    return;
  }

  cgc_prompt_q(form->cur_question);
}

int cgc_handle_line(form_t *form, char *buf)
{
  int ret;

  if (cgc_is_cmd(form, buf))
    return cgc_handle_cmd(form, buf);

  if (form->cur_page->completed || form->cur_question == NULL) {
    return 1;
  }

  if (cgc_strlen(buf) == 0) {
    if (!form->cur_question->optional)
      return 0;
  } else {
    ret = cgc_handle_answer(form, buf);
    if (ret < 0)
      return -1;
    if (ret != 0)
      return 0;
  }

  ret = cgc_next_question(form);
  if (ret < 0)
    return -1;
  else
    return 0;

}

void cgc_print_greeting(form_t *form)
{
  cgc_printf("%s", form->greeting);
}
