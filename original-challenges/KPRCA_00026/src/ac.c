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
#include <ctype.h>
#include <wrapper.h>
#include <libcgc.h>
#include <filaments.h>
#include <mutex.h>
#include "ac.h"

int num_words = 0;
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
  size_t start;
  size_t end;
} ac_queue[MAX_QUEUE];
static size_t ac_queue_head, ac_queue_tail, ac_queue_count;
static char *ac_buffer;
static size_t ac_idx;
static mutex_t ac_mutex;

void ac_init()
{
  int i;
  for (i = 0; i < MAX_AC_LIST; ++i)
  {
    if (word_list[i].typo[0] == 0)
      break;
    num_words++;
  }
  mutex_init(&ac_mutex);
}

void ac_add_custom(char *typo, char *correct)
{
  if (typo && correct && num_words < MAX_AC_LIST)
  {
    int i;
    for (i = 0; i < num_words; ++i)
    {
      if (strcmp(typo, word_list[i].typo) == 0)
        return;
    }
    if (strlen(typo) < MAX_AC_LEN &&
        strlen(correct) < MAX_AC_LEN &&
        strlen(typo) > 0)
    {
      strcpy(word_list[num_words].typo, typo);
      strcpy(word_list[num_words].correct, correct);
      num_words++;
    }
  }
}

void ac_process(void *ud)
{
  char word[MAX_AC_LEN];
  int dummy;
  while (1)
  {
    size_t i;
    int j;

    while (ac_buffer != NULL && ac_queue_count > 0)
    {
      mutex_lock(&ac_mutex);
#ifdef PATCHED
      if (ac_buffer == NULL)
      {
        mutex_unlock(&ac_mutex);
        break;
      }
#endif
      i = ac_queue_head;
      size_t start = ac_queue[i].start, end = ac_queue[i].end;

      if (end-start < sizeof(word))
      {
        memcpy(word, &ac_buffer[start], end-start);
        word[end-start] = 0;
      }
      else
      {
        word[0] = 0;
      }
      mutex_unlock(&ac_mutex);

      int diff = 0;
      for (j = 0; j < num_words; ++j)
      {
        if (strcmp(word, word_list[j].typo) == 0)
        {
          char *newbuf;
          diff = strlen(word_list[j].correct) - strlen(word);
          mutex_lock(&ac_mutex);

          if (diff < 0)
            // memmove before we shrink the buffer
            memmove(&ac_buffer[end + diff], &ac_buffer[end], ac_idx - end);
          // adjust buffer size to new size plus null character
          newbuf = realloc(ac_buffer, ac_idx + 1 + diff);
          if (newbuf != NULL)
          {
            ac_buffer = newbuf;
            if (diff > 0)
              // memmove after we enlarge the buffer
              memmove(&ac_buffer[end + diff], &ac_buffer[end], ac_idx - end);
            memcpy(&ac_buffer[start], word_list[j].correct, strlen(word_list[j].correct));
            ac_idx += diff;
          }

          mutex_unlock(&ac_mutex);
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

    filaments_yield();
  }
}

char *ac_read(int fd, char term)
{
  size_t rx;
  ac_queue_count = ac_queue_head = ac_queue_tail = ac_idx = 0;
  ac_buffer = NULL;

  while (1)
  {
    // read next word
    size_t count = 0;
    char word[MAX_AC_LEN];
    for (count = 0; count < MAX_AC_LEN; count++)
    {
      if (receive(fd, &word[count], 1, &rx) != 0 || rx == 0)
        goto fail;
      if (word[count] == term || !isalpha(word[count]))
      {
        count++;
        break;
      }
    }

#ifdef PATCHED
    mutex_lock(&ac_mutex);
#endif
    char *newbuf = realloc(ac_buffer, ac_idx+count+1);
    if (newbuf == NULL)
      goto fail;

#ifndef PATCHED
    mutex_lock(&ac_mutex);
#endif
    ac_buffer = newbuf;
    memcpy(&ac_buffer[ac_idx], word, count);
    ac_idx += count;
    ac_buffer[ac_idx] = 0;
    mutex_unlock(&ac_mutex);

    if (count > 1)
    {
      // append word to ac queue [start, ac_idx)
      while (ac_queue_count >= MAX_QUEUE)
        // wait until queue is no longer full
        filaments_yield();

      size_t i = ac_queue_tail;
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
    filaments_yield();

  char *buf = ac_buffer;
  ac_buffer = NULL;
  buf[ac_idx-1] = 0;
  return buf;

fail:
  mutex_lock(&ac_mutex);
  free(ac_buffer);
  ac_buffer = NULL;
  mutex_unlock(&ac_mutex);
  return NULL;
}
