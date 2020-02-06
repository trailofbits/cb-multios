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

#include "cgc_list.h"
#include "cgc_error.h"
#include "cgc_tree.h"

static char *chain_term = "\x15\x15";
static char *word_sep = "\x89\x89";

char *cgc_word_list_to_str(const list *l)
{
  if (!l)
    return NULL;

#define START_SIZE 128
  char *flat = cgc_calloc(1, START_SIZE);
  cgc_size_t cur_size = START_SIZE;

  if (!flat)
    error(EALLOC);

  const list *p = l;

  while (p && p->d) {
    cgc_size_t cur_len = cgc_strlen(flat);
    if (cgc_strlen(flat) + cgc_strlen(p->d) + cgc_strlen(word_sep) + 1 > cur_size) {
      cur_size = (cgc_strlen(flat) + cgc_strlen(p->d) + cgc_strlen(word_sep) + 1) * 2;
      flat = cgc_realloc(flat, cur_size);
      if (!flat)
        error(EALLOC);

      cgc_memset(flat + cur_len, 0, cur_size - cur_len);
    }

    cgc_strcat(flat, p->d);
    cgc_strcat(flat, word_sep);
    p = p->n;
  }

  return flat;
}

HASH cgc_hash_str(char *s)
{
  HASH h = 0xdeedacedfacedead;
  while (*s++)
    h = (h * 33) + *s;
  return h;
}

list *cgc_split_words(const char *line, int add_term)
{
  char *p = NULL;
  char *line_end = NULL;
  list *words = NULL;

  if (!line)
    return NULL;

  p = cgc_calloc(1, cgc_strlen(line) + 1);
  char *to_free = p;
  if (!p)
    error(EALLOC);
  cgc_strncpy(p, line, cgc_strlen(line));
  line_end = p + cgc_strlen(line);

  while (p < line_end) {
    while(cgc_isspace(*p))
      p++;

    char *word_start = p;
    char *word_end = p;

    while (word_end < line_end && cgc_isprint(*word_end) && !cgc_isspace(*word_end))
      word_end++;
    *word_end = '\0';

    char *wc = cgc_calloc(1, cgc_strlen(word_start) + 1);
    cgc_strcpy(wc, word_start);
    cgc_append_list(&words, wc, 1);
    p = word_end + 1;
  }

  if (add_term) {
    char *wc = cgc_calloc(1, cgc_strlen(chain_term) + 1);
    cgc_strcpy(wc, chain_term);
    cgc_append_list(&words, chain_term, 1);
  }

  cgc_free(to_free);
  return words;
}

list *cgc_chunk_words(list *words, cgc_size_t chunk_size)
{
  cgc_size_t num_words = cgc_len_list(words);
  list *chunks = NULL;

  if (num_words <= chunk_size)
    return NULL;

  cgc_size_t num_chunks = num_words - chunk_size;
  if (num_chunks > num_words)
    return NULL;

  for (cgc_size_t i = 0; i < num_chunks; i++) {
    list *chunk = cgc_copy_list(words, i, i + chunk_size + 1);
    if (!chunk)
      error(EALLOC);
    cgc_append_list(&chunks, chunk, 1);
  }

  return chunks;
}

list *cgc_upto_last(const list *l)
{
  if (!l || cgc_len_list(l) < 2)
    return NULL;

  return cgc_copy_list(l, 0, cgc_len_list(l) - 1);
}

HASH cgc_key_from_wordlist(const list *l)
{
  char *k = cgc_word_list_to_str(l);
  if (!k)
    return 0;

  HASH x = cgc_hash_str(k);
  cgc_free(k);
  return x;
}

int cgc_insert_wordlist(const list *word_list, tree **t)
{
  if (!word_list || !t)
    return -1;

  list *all_but_last = cgc_upto_last(word_list);
  if (!all_but_last)
    return 0;

  HASH h = cgc_key_from_wordlist((list *)all_but_last);
  if (!h)
    return -1;

  const DATA v = cgc_lindex((list *)word_list, -1);
  if (!v)
    error(ELIST);

  if (!*t) {
    *t = cgc_init_tree(h, v);
  } else {
    if (cgc_ins_tree(*t, h, v) < 0)
      error(ETREE);
  }

  return 0;
}

int cgc_insert_wordlists(const list *word_lists, tree **t)
{
  if (!word_lists)
    return -1;

  for (const list *it = word_lists; it; it = it->n)
    if (cgc_insert_wordlist(it->d, t) < 0)
      return -1;

  return 0;
}

list *cgc_str_to_wordlists(const char *s)
{
  cgc_size_t len = cgc_strlen(s);
  char *x = cgc_calloc(1, len + 1);
  cgc_strncpy(x, s, len);
  x[len] = '\0';

  list *words = cgc_split_words(x, 1);
  if (!words)
    return NULL;

  cgc_free(x);

#define CHAIN_LENGTH 2
  list *chunks = cgc_chunk_words(words, CHAIN_LENGTH);
  if (!chunks)
    return NULL;

  return chunks;
}
