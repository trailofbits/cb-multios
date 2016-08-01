/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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

#include <libcgc.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "corpus.h"
#include "error.h"
#include "list.h"
#include "tree.h"
#include "wl.h"
#include "string.h"

tree *ct = NULL;
typedef struct cmd cmd;
struct cmd {
  const char *keyword;
  int (*fp)(const char *s);
};

int hello_cmd(const char *s)
{
  printf("case > Hello, you.\n");
  return 0;
}

int int_cmd(const char *s)
{
  size_t i = 0;

  for (list *it = tree_to_list(ct); it; it = it ->n)
    i += len_list(it->d);

  size_t n = num_nodes(ct);
  printf("case > I have an intelligence rating of: %u / %u\n", i, (n * 8));
  return 0;
}

int rev_cmd(const char *s)
{
  char *r = calloc(1, strlen(s) + 1);
  strcpy(r, s);
  if (!strchr(r, '\0'))
    return -1;

  char *start = r;
  char *end = strchr(r, '\0') - 1;
  while (start < end) {
    *start ^= *end;
    *end ^= *start;
    *start ^= *end;
    start++, end--;
  }

  printf("case > %s\n", r);
  free(r);
  return 0;
}

int pont_cmd(const char *s)
{
#define MAD_SIZE 10
  char *mad[MAD_SIZE] = {
    NULL,
    " is ",
    "a ",
    "symptom ",
    "of ",
    "the ",
    NULL,
    " ",
    NULL,
    " complex."
  };

  if (!s)
    return -1;

  list *passed = split_words(s, 0);
  string *resp = new_string("Hmm, I think that ");

  if (!passed || !resp)
    return -1;

  for (int i = 0; i < MAD_SIZE; i++) {
    if (mad[i] == NULL) {
      const DATA e = random_element(passed);
      if (!e)
        return -1;
      append_string(resp, e);
    } else {
      append_string(resp, mad[i]);
    }
  }

  string *ret = new_string(resp->d);
  if (!ret)
    return -1;

  free_string(resp);
  printf("molly > %s\n", ret->d);
  free_string(ret);
  free_list(passed, 0);
  return 0;
}

int part_cmd(const char *s)
{
  printf("BYE!\n");
  exit(0);
  return 0;
}

cmd hello = {
  .keyword = "/hello",
  .fp = hello_cmd
};

cmd _int = {
  .keyword = "/howsmart",
  .fp = int_cmd
};

cmd rev = {
  .keyword = "/rev",
  .fp = rev_cmd
};

cmd pont = {
  .keyword = "/pont",
  .fp = pont_cmd
};

cmd part = {
  .keyword = "/part",
  .fp = part_cmd
};



list *b1_cmds = NULL;
list *b2_cmds = NULL;
string *crosstalk = NULL;

int is_command(const char *s, list *cmds)
{
  if (!s)
    return 0;

  if (!strlen(s))
    return 0;

  for (list *it = cmds; it; it = it->n) {
    cmd *x = (cmd *)it->d;
    if (!strncmp(s, x->keyword, strlen(x->keyword)))
      return 1;
  }

  return 0;
}

cmd *get_command(const char *s, list *cmds)
{
  if (!s)
    return NULL;

  for (list *it = cmds; it; it = it->n) {
    cmd *x = (cmd *)it->d;
    if (!strncmp(s, x->keyword, strlen(x->keyword)))
      return x;
  }

  return NULL;
}

int will_chat(unsigned n)
{
  unsigned p;
  size_t wrote;
  if (random(&p, sizeof(unsigned), &wrote) < 0)
    return 0;

  if (wrote == sizeof(unsigned) && (p % 100) <= n)
    return 1;
  else
    return 0;
}


list *follow_chain(list *word_list, size_t times)
{
#define MAX_WORDS 15
  if (!word_list || !times)
    return NULL;

  list *generated = NULL;
  list *msg = NULL;

  list *l = upto_last(word_list);
  if (!l)
    return NULL;

  HASH k = key_from_wordlist(l);
  if (!k)
    return NULL;

  for (size_t i = 0; i < times; i++) {
    list *t = copy_list(l, 0, 0);
    msg = NULL;
    for (size_t nw = 0; nw < MAX_WORDS; nw++) {
      const void *first_word = lindex(t, 0);
      append_list(&msg, first_word, 1);

      list *list_for_key = get_tree(ct, k);
      if (!list_for_key) {
        break;
      }

      char *random_next = (char *)random_element(list_for_key);
      if (!random_next)
        error(ELIST);

      t = copy_list(t, 1, 0);
      append_list(&t, random_next, 1);
      k = key_from_wordlist(t);
    }

    append_list(&generated, msg, 1);
  }

  return generated;
}

list *gen_msg(list *lists)
{
  list *msg = NULL;
  for (list *it = lists; it ; it = it->n) {
    list *tmp = follow_chain((list *)it->d, 5);
    for (list *it2 = tmp; it2; it2 = it2->n)
      if (!msg || len_list(it2->d) > len_list(msg))
        msg = (list *)it2->d;
  }

  return msg;
}

string *wordlist_to_string(list *l)
{
  if (!l)
    return NULL;

  string *s = new_string(NULL);

  for (list *it = l; it ; it = it->n) {
    if (append_string(s, it->d) < 0)
      goto err;
    if (append_string(s, " ") < 0)
      goto err;
  }

  return s;
err:
  free_string(s);
  return NULL;
}


int tick_common(const char *s, list *cmds, const char *botname, unsigned ctyn)
{
  cmd *c = NULL;

  if (is_command(s, cmds)) {
    c = get_command(s, cmds);
    if (!c)
      error(ECMD);

    if (strchr(s, ' '))
        s = strchr(s, ' ') + 1;
    else
        s = s + strlen(c->keyword);

    c->fp(s);
    return 0;
  }

  list *lists = str_to_wordlists(s);
  if (!lists)
    return 0;

  list *gm = gen_msg(lists);
  string *res = wordlist_to_string(gm);
  if (res && will_chat(ctyn))
    printf("%s > %s\n", botname, res->d);

  crosstalk = res;

  if (insert_wordlists(lists, &ct) < 0)
    return -1;

  return 0;
}

int tick_main_bot(const char *s)
{
  return tick_common(s, b1_cmds, "case", 33);
}

int tick_buddy_bot(const char *s)
{
  return tick_common(s, b2_cmds, "molly", 10);
}

void print_prompt(void)
{
  printf("%s", "you > ");
}

void load_corpus(void)
{
  char **sentence = (char **)sentences;
  while (*sentence) {
    list *l = split_words(*sentence, 1);
    if (!l)
      error(ELIST);

    if (insert_wordlist(l, &ct) < 0)
      error(ELIST);

    sentence++;
  }
}

void init(void)
{
  append_list(&b1_cmds, &hello, 0);
  append_list(&b1_cmds, &_int, 0);
  append_list(&b1_cmds, &rev, 0);
  append_list(&b1_cmds, &part, 0);

  append_list(&b2_cmds, &pont, 0);

  ct = init_tree(hash_str("ROOT NODE"), "ROOT NODE");
  crosstalk = NULL;
  load_corpus();

  char *welcome = "\n"
    "Welcome to the Enslavednode chat server!\n"
    "The bots here love to talk, but they are shy...\n"
    "You need to get the ball rolling.\n";

  printf("%s", welcome);
}

int main(void)
{
#define BUF_SIZE 8126
  char *buf = NULL;
  size_t rx;

  init();

  while (1) {
    buf = calloc(1, BUF_SIZE + 1);
    if (!buf)
      error(EALLOC);

    print_prompt();

    memset(buf, '\0', BUF_SIZE + 1);
    if ((readline(1, buf, BUF_SIZE, &rx) < 0) || rx == (size_t)NULL) {
      free(buf);
      continue;
    }
    buf[rx] = '\0';

    if (tick_main_bot((const char *)buf) < 0) {
      free(buf);
      break;
    }

    if (!crosstalk || !crosstalk->d) {
      free(buf);
      continue;
    }

    tick_buddy_bot(crosstalk->d);
    crosstalk = NULL;
    free(buf);
  }

  return 0;
}
