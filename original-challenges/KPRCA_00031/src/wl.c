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

#include "list.h"
#include "error.h"
#include "tree.h"

static char *chain_term = "\x15\x15";
static char *word_sep = "\x89\x89";

char *word_list_to_str(const list *l)
{
  if (!l)
    return NULL;

#define START_SIZE 128
  char *flat = calloc(1, START_SIZE);
  size_t cur_size = START_SIZE;

  if (!flat)
    error(EALLOC);

  const list *p = l;

  while (p && p->d) {
    size_t cur_len = strlen(flat);
    if (strlen(flat) + strlen(p->d) + strlen(word_sep) + 1 > cur_size) {
      cur_size = (strlen(flat) + strlen(p->d) + strlen(word_sep) + 1) * 2;
      flat = realloc(flat, cur_size);
      if (!flat)
        error(EALLOC);

      memset(flat + cur_len, 0, cur_size - cur_len);
    }

    strcat(flat, p->d);
    strcat(flat, word_sep);
    p = p->n;
  }

  return flat;
}

HASH hash_str(char *s)
{
  HASH h = 0xdeedacedfacedead;
  while (*s++)
    h = (h * 33) + *s;
  return h;
}

list *split_words(const char *line, int add_term)
{
  char *p = NULL;
  char *line_end = NULL;
  list *words = NULL;

  if (!line)
    return NULL;

  p = calloc(1, strlen(line) + 1);
  char *to_free = p;
  if (!p)
    error(EALLOC);
  strncpy(p, line, strlen(line));
  line_end = p + strlen(line);

  while (p < line_end) {
    while(isspace(*p))
      p++;

    char *word_start = p;
    char *word_end = p;

    while (word_end < line_end && isprint(*word_end) && !isspace(*word_end))
      word_end++;
    *word_end = '\0';

    char *wc = calloc(1, strlen(word_start) + 1);
    strcpy(wc, word_start);
    append_list(&words, wc, 1);
    p = word_end + 1;
  }

  if (add_term) {
    char *wc = calloc(1, strlen(chain_term) + 1);
    strcpy(wc, chain_term);
    append_list(&words, chain_term, 1);
  }

  free(to_free);
  return words;
}

list *chunk_words(list *words, size_t chunk_size)
{
  size_t num_words = len_list(words);
  list *chunks = NULL;

  if (num_words <= chunk_size)
    return NULL;

  size_t num_chunks = num_words - chunk_size;
  if (num_chunks > num_words)
    return NULL;

  for (size_t i = 0; i < num_chunks; i++) {
    list *chunk = copy_list(words, i, i + chunk_size + 1);
    if (!chunk)
      error(EALLOC);
    append_list(&chunks, chunk, 1);
  }

  return chunks;
}

list *upto_last(const list *l)
{
  if (!l || len_list(l) < 2)
    return NULL;

  return copy_list(l, 0, len_list(l) - 1);
}

HASH key_from_wordlist(const list *l)
{
  char *k = word_list_to_str(l);
  if (!k)
    return 0;

  HASH x = hash_str(k);
  free(k);
  return x;
}

int insert_wordlist(const list *word_list, tree **t)
{
  if (!word_list || !t)
    return -1;

  list *all_but_last = upto_last(word_list);
  if (!all_but_last)
    return 0;

  HASH h = key_from_wordlist((list *)all_but_last);
  if (!h)
    return -1;

  const DATA v = lindex((list *)word_list, -1);
  if (!v)
    error(ELIST);

  if (!*t) {
    *t = init_tree(h, v);
  } else {
    if (ins_tree(*t, h, v) < 0)
      error(ETREE);
  }

  return 0;
}

int insert_wordlists(const list *word_lists, tree **t)
{
  if (!word_lists)
    return -1;

  for (const list *it = word_lists; it; it = it->n)
    if (insert_wordlist(it->d, t) < 0)
      return -1;

  return 0;
}

list *str_to_wordlists(const char *s)
{
  size_t len = strlen(s);
  char *x = calloc(1, len + 1);
  strncpy(x, s, len);
  x[len] = '\0';

  list *words = split_words(x, 1);
  if (!words)
    return NULL;

  free(x);

#define CHAIN_LENGTH 2
  list *chunks = chunk_words(words, CHAIN_LENGTH);
  if (!chunks)
    return NULL;

  return chunks;
}
