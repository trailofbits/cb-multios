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
#include "cgc_ctype.h"
#include "cgc_wrapper.h"
#include "libcgc.h"
#include "cgc_filaments.h"
#include "cgc_mutex.h"
#include "cgc_ac.h"

int cgc_num_words = 0;
ac_t word_list[MAX_AC_LIST] = {
  {"acceptible", "acceptable"}, {"amature", "amateur"},
  {"arguement", "argument"}, {"beleive", "believe"},
  {"calender", "calendar"}, {"cemetary", "cemetery"},
  {"collectable", "collectible"}, {"concensus", "consensus"},
  {"equiptment", "equipment"}, {"existance", "existence"},
  {"firey", "fiery"}, {"foriegn", "foreign"},
  {"guage", "gauge"}, {"greatful", "grateful"},
  {"harrass", "harass"}, {"ignorence", "ignorance"},
  {"lisense", "license"}, {"maintenence", "maintenance"},
  {"relevent", "relevant"}, {"wierd", "weird"},
};

#define MAX_QUEUE 1024
static struct {
  cgc_size_t start;
  cgc_size_t end;
} ac_queue[MAX_QUEUE];
static cgc_size_t ac_queue_head, ac_queue_tail, ac_queue_count;
static char *ac_buffer;
static cgc_size_t ac_idx;
static mutex_t ac_mutex;

void cgc_ac_init()
{
  int i;
  for (i = 0; i < MAX_AC_LIST; ++i)
  {
    if (word_list[i].typo[0] == 0)
      break;
    cgc_num_words++;
  }
  mutex_init(&ac_mutex);
}

void cgc_ac_add_custom(char *typo, char *correct)
{
  if (typo && correct && cgc_num_words < MAX_AC_LIST)
  {
    int i;
    for (i = 0; i < cgc_num_words; ++i)
    {
      if (cgc_strcmp(typo, word_list[i].typo) == 0)
        return;
    }
    if (cgc_strlen(typo) < MAX_AC_LEN &&
        cgc_strlen(correct) < MAX_AC_LEN &&
        cgc_strlen(typo) > 0)
    {
      cgc_strcpy(word_list[cgc_num_words].typo, typo);
      cgc_strcpy(word_list[cgc_num_words].correct, correct);
      cgc_num_words++;
    }
  }
}

void cgc_ac_process(void *ud)
{
  char word[MAX_AC_LEN];
  int dummy;
  while (1)
  {
    cgc_size_t i;
    int j;

    while (ac_buffer != NULL && ac_queue_count > 0)
    {
      cgc_mutex_lock(&ac_mutex);
#ifdef PATCHED
      if (ac_buffer == NULL)
      {
        cgc_mutex_unlock(&ac_mutex);
        break;
      }
#endif
      i = ac_queue_head;
      cgc_size_t start = ac_queue[i].start, end = ac_queue[i].end;

      if (end-start < sizeof(word))
      {
        cgc_memcpy(word, &ac_buffer[start], end-start);
        word[end-start] = 0;
      }
      else
      {
        word[0] = 0;
      }
      cgc_mutex_unlock(&ac_mutex);

      int diff = 0;
      for (j = 0; j < cgc_num_words; ++j)
      {
        if (cgc_strcmp(word, word_list[j].typo) == 0)
        {
          char *newbuf;
          diff = cgc_strlen(word_list[j].correct) - cgc_strlen(word);
          cgc_mutex_lock(&ac_mutex);

          if (diff < 0)
            // memmove before we shrink the buffer
            cgc_memmove(&ac_buffer[end + diff], &ac_buffer[end], ac_idx - end);
          // adjust buffer size to new size plus null character
          newbuf = cgc_realloc(ac_buffer, ac_idx + 1 + diff);
          if (newbuf != NULL)
          {
            ac_buffer = newbuf;
            if (diff > 0)
              // memmove after we enlarge the buffer
              cgc_memmove(&ac_buffer[end + diff], &ac_buffer[end], ac_idx - end);
            cgc_memcpy(&ac_buffer[start], word_list[j].correct, cgc_strlen(word_list[j].correct));
            ac_idx += diff;
          }

          cgc_mutex_unlock(&ac_mutex);
          break;
        }
      }

      for (j = 0, i = ac_queue_head; j < ac_queue_count; j++, i = (i + 1) % MAX_QUEUE)
      {
        ac_queue[i].start += diff;
        ac_queue[i].end += diff;
      }

      // remove from queue once we finished all the processing
      ac_queue_head = (ac_queue_head + 1) % MAX_QUEUE;
      ac_queue_count--;
    }

    cgc_filaments_yield();
  }
}

char *cgc_ac_read(int fd, char term)
{
  cgc_size_t rx;
  ac_queue_count = ac_queue_head = ac_queue_tail = ac_idx = 0;
  ac_buffer = NULL;

  while (1)
  {
    // cgc_read next word
    cgc_size_t count = 0;
    char word[MAX_AC_LEN];
    for (count = 0; count < MAX_AC_LEN; count++)
    {
      if (cgc_receive(fd, &word[count], 1, &rx) != 0 || rx == 0)
        goto fail;
      if (word[count] == term || !cgc_isalpha(word[count]))
      {
        count++;
        break;
      }
    }

#ifdef PATCHED
    cgc_mutex_lock(&ac_mutex);
#endif
    char *newbuf = cgc_realloc(ac_buffer, ac_idx+count+1);
    if (newbuf == NULL)
      goto fail;

#ifndef PATCHED
    cgc_mutex_lock(&ac_mutex);
#endif
    ac_buffer = newbuf;
    cgc_memcpy(&ac_buffer[ac_idx], word, count);
    ac_idx += count;
    ac_buffer[ac_idx] = 0;
    cgc_mutex_unlock(&ac_mutex);

    if (count > 1)
    {
      // append word to ac queue [start, ac_idx)
      while (ac_queue_count >= MAX_QUEUE)
        // wait until queue is no longer full
        cgc_filaments_yield();

      cgc_size_t i = ac_queue_tail;
      ac_queue_tail = (ac_queue_tail + 1) % MAX_QUEUE;
      ac_queue_count++;

      ac_queue[i].start = ac_idx-count;
      ac_queue[i].end = ac_idx-1;
    }

    if (ac_buffer[ac_idx-1] == term)
      break;
  }

  // wait for ac process to finish
  while (ac_queue_count > 0)
    cgc_filaments_yield();

  char *buf = ac_buffer;
  ac_buffer = NULL;
  buf[ac_idx-1] = 0;
  return buf;

fail:
  cgc_mutex_lock(&ac_mutex);
  cgc_free(ac_buffer);
  ac_buffer = NULL;
  cgc_mutex_unlock(&ac_mutex);
  return NULL;
}
