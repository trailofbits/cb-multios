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

#include "libcgc.h"
#include "cgc_ctype.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_common.h"
#include "cgc_corpus.h"
#include "cgc_error.h"
#include "cgc_list.h"
#include "cgc_tree.h"
#include "cgc_wl.h"
#include "cgc_string.h"

tree *cgc_ct = NULL;
typedef struct cmd cmd;
struct cmd {
  const char *keyword;
  int (*fp)(const char *s);
};

int cgc_hello_cmd(const char *s)
{
  cgc_printf("case > Hello, you.\n");
  return 0;
}

int cgc_int_cmd(const char *s)
{
  cgc_size_t i = 0;

  for (list *it = cgc_tree_to_list(cgc_ct); it; it = it ->n)
    i += cgc_len_list(it->d);

  cgc_size_t n = cgc_num_nodes(cgc_ct);
  cgc_printf("case > I have an intelligence rating of: %u / %u\n", i, (n * 8));
  return 0;
}

int cgc_rev_cmd(const char *s)
{
  char *r = cgc_calloc(1, cgc_strlen(s) + 1);
  cgc_strcpy(r, s);
  if (!cgc_strchr(r, '\0'))
    return -1;

  char *start = r;
  char *end = cgc_strchr(r, '\0') - 1;
  while (start < end) {
    *start ^= *end;
    *end ^= *start;
    *start ^= *end;
    start++, end--;
  }

  cgc_printf("case > %s\n", r);
  cgc_free(r);
  return 0;
}

int cgc_pont_cmd(const char *s)
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

  list *passed = cgc_split_words(s, 0);
  string *resp = cgc_new_string("Hmm, I think that ");

  if (!passed || !resp)
    return -1;

  for (int i = 0; i < MAD_SIZE; i++) {
    if (mad[i] == NULL) {
      const DATA e = cgc_random_element(passed);
      if (!e)
        return -1;
      cgc_append_string(resp, e);
    } else {
      cgc_append_string(resp, mad[i]);
    }
  }

  string *ret = cgc_new_string(resp->d);
  if (!ret)
    return -1;

  cgc_free_string(resp);
  cgc_printf("molly > %s\n", ret->d);
  cgc_free_string(ret);
  cgc_free_list(passed, 0);
  return 0;
}

int cgc_part_cmd(const char *s)
{
  cgc_printf("BYE!\n");
  cgc_exit(0);
  return 0;
}

cmd hello = {
  .keyword = "/hello",
  .fp = cgc_hello_cmd
};

cmd _int = {
  .keyword = "/howsmart",
  .fp = cgc_int_cmd
};

cmd rev = {
  .keyword = "/rev",
  .fp = cgc_rev_cmd
};

cmd pont = {
  .keyword = "/pont",
  .fp = cgc_pont_cmd
};

cmd part = {
  .keyword = "/part",
  .fp = cgc_part_cmd
};



list *cgc_b1_cmds = NULL;
list *cgc_b2_cmds = NULL;
string *cgc_crosstalk = NULL;

int cgc_is_command(const char *s, list *cmds)
{
  if (!s)
    return 0;

  if (!cgc_strlen(s))
    return 0;

  for (list *it = cmds; it; it = it->n) {
    cmd *x = (cmd *)it->d;
    if (!cgc_strncmp(s, x->keyword, cgc_strlen(x->keyword)))
      return 1;
  }

  return 0;
}

cmd *cgc_get_command(const char *s, list *cmds)
{
  if (!s)
    return NULL;

  for (list *it = cmds; it; it = it->n) {
    cmd *x = (cmd *)it->d;
    if (!cgc_strncmp(s, x->keyword, cgc_strlen(x->keyword)))
      return x;
  }

  return NULL;
}

int cgc_will_chat(unsigned n)
{
  unsigned p;
  cgc_size_t wrote;
  if (cgc_random(&p, sizeof(unsigned), &wrote) < 0)
    return 0;

  if (wrote == sizeof(unsigned) && (p % 100) <= n)
    return 1;
  else
    return 0;
}


list *cgc_follow_chain(list *word_list, cgc_size_t times)
{
#define MAX_WORDS 15
  if (!word_list || !times)
    return NULL;

  list *generated = NULL;
  list *msg = NULL;

  list *l = cgc_upto_last(word_list);
  if (!l)
    return NULL;

  HASH k = cgc_key_from_wordlist(l);
  if (!k)
    return NULL;

  for (cgc_size_t i = 0; i < times; i++) {
    list *t = cgc_copy_list(l, 0, 0);
    msg = NULL;
    for (cgc_size_t nw = 0; nw < MAX_WORDS; nw++) {
      const void *first_word = cgc_lindex(t, 0);
      cgc_append_list(&msg, first_word, 1);

      list *list_for_key = cgc_get_tree(cgc_ct, k);
      if (!list_for_key) {
        break;
      }

      char *random_next = (char *)cgc_random_element(list_for_key);
      if (!random_next)
        error(ELIST);

      t = cgc_copy_list(t, 1, 0);
      cgc_append_list(&t, random_next, 1);
      k = cgc_key_from_wordlist(t);
    }

    cgc_append_list(&generated, msg, 1);
  }

  return generated;
}

list *cgc_gen_msg(list *lists)
{
  list *msg = NULL;
  for (list *it = lists; it ; it = it->n) {
    list *tmp = cgc_follow_chain((list *)it->d, 5);
    for (list *it2 = tmp; it2; it2 = it2->n)
      if (!msg || cgc_len_list(it2->d) > cgc_len_list(msg))
        msg = (list *)it2->d;
  }

  return msg;
}

string *cgc_wordlist_to_string(list *l)
{
  if (!l)
    return NULL;

  string *s = cgc_new_string(NULL);

  for (list *it = l; it ; it = it->n) {
    if (cgc_append_string(s, it->d) < 0)
      goto err;
    if (cgc_append_string(s, " ") < 0)
      goto err;
  }

  return s;
err:
  cgc_free_string(s);
  return NULL;
}


int cgc_tick_common(const char *s, list *cmds, const char *botname, unsigned ctyn)
{
  cmd *c = NULL;

  if (cgc_is_command(s, cmds)) {
    c = cgc_get_command(s, cmds);
    if (!c)
      error(ECMD);

    if (cgc_strchr(s, ' '))
        s = cgc_strchr(s, ' ') + 1;
    else
        s = s + cgc_strlen(c->keyword);

    c->fp(s);
    return 0;
  }

  list *lists = cgc_str_to_wordlists(s);
  if (!lists)
    return 0;

  list *gm = cgc_gen_msg(lists);
  string *res = cgc_wordlist_to_string(gm);
  if (res && cgc_will_chat(ctyn))
    cgc_printf("%s > %s\n", botname, res->d);

  cgc_crosstalk = res;

  if (cgc_insert_wordlists(lists, &cgc_ct) < 0)
    return -1;

  return 0;
}

int cgc_tick_main_bot(const char *s)
{
  return cgc_tick_common(s, cgc_b1_cmds, "case", 33);
}

int cgc_tick_buddy_bot(const char *s)
{
  return cgc_tick_common(s, cgc_b2_cmds, "molly", 10);
}

void cgc_print_prompt(void)
{
  cgc_printf("%s", "you > ");
}

void cgc_load_corpus(void)
{
  char **sentence = (char **)sentences;
  while (*sentence) {
    list *l = cgc_split_words(*sentence, 1);
    if (!l)
      error(ELIST);

    if (cgc_insert_wordlist(l, &cgc_ct) < 0)
      error(ELIST);

    sentence++;
  }
}

void cgc_init(void)
{
  cgc_append_list(&cgc_b1_cmds, &hello, 0);
  cgc_append_list(&cgc_b1_cmds, &_int, 0);
  cgc_append_list(&cgc_b1_cmds, &rev, 0);
  cgc_append_list(&cgc_b1_cmds, &part, 0);

  cgc_append_list(&cgc_b2_cmds, &pont, 0);

  cgc_ct = cgc_init_tree(cgc_hash_str("ROOT NODE"), "ROOT NODE");
  cgc_crosstalk = NULL;
  cgc_load_corpus();

  char *welcome = "\n"
    "Welcome to the Enslavednode chat server!\n"
    "The bots here love to talk, but they are shy...\n"
    "You need to get the ball rolling.\n";

  cgc_printf("%s", welcome);
}

int main(int cgc_argc, char *cgc_argv[])
{
#define BUF_SIZE 8126
  char *buf = NULL;
  cgc_size_t rx;

  cgc_init();

  while (1) {
    buf = cgc_calloc(1, BUF_SIZE + 1);
    if (!buf)
      error(EALLOC);

    cgc_print_prompt();

    cgc_memset(buf, '\0', BUF_SIZE + 1);
    if ((cgc_readline(1, buf, BUF_SIZE, &rx) < 0) || rx == (cgc_size_t)NULL) {
      cgc_free(buf);
      continue;
    }
    buf[rx] = '\0';

    if (cgc_tick_main_bot((const char *)buf) < 0) {
      cgc_free(buf);
      break;
    }

    if (!cgc_crosstalk || !cgc_crosstalk->d) {
      cgc_free(buf);
      continue;
    }

    cgc_tick_buddy_bot(cgc_crosstalk->d);
    cgc_crosstalk = NULL;
    cgc_free(buf);
  }

  return 0;
}
