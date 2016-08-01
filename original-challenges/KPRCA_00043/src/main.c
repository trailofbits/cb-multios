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

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#include "readuntil.h"
#include "bloomy.h"
#include "moomoo.h"

const char* depressing_words[] = {
  "gloomy", "un-cheerful", "tragic", "depressive", "dejected", "despondent",
  "destroyed", "disconsolate", "dispirited", "down", "downcast", "downhearted",
  "dragged", "pain", "pessimistic", "sad", "unhappy", "weeping", "death",
  "fear", "ruined", "lonely", "miserable", "anxious", "torment", "agony",
  "torture", "distress", "grief", "sorrow", "pathetic", "terrified", "scared"
};

bloomy_t *bloomy = NULL;

uint8_t submit_lyrics(char *lyrics, size_t len)
{
  int i, nl = 0, n = 0;
  size_t olen = len;
  char line[128], *s = lyrics;
  memset(lyrics, 0, len);
  while (1)
  {
    if (read_until(STDIN, line, sizeof(line), '\n') < 0)
      return 0;
    if (strcmp(line, "EOF") == 0)
      break;

    nl = 1;
    char *word, *input = line;
    while (1)
    {
      word = strsep(&input, " ");
      if (word == NULL)
        break;
      n = bloomy_check(bloomy, word);
      if (n == 1)
      {
        for (i = 0; i < sizeof(depressing_words) / sizeof(char*); ++i)
        {
          if (strcmp(depressing_words[i], word) == 0)
          {
            printf("depressing word detected.\n");
            return 0;
          }
        }
#if PATCHED
        if (strlen(word) < len - 1)
        {
#endif
        if (!nl)
        {
          strcat(s, " ");
          s++;
          len--;
        }
        strcat(s, word);
        s += strlen(word);
        len -= strlen(word);
#if PATCHED
        }
        else
        {
          *s = '\0';
          return 1;
        }
#endif
      }
      else if (n == 0)
      {
        if (strlen(word) < len - 1)
        {
          if (!nl)
          {
            strcat(s, " ");
            s++;
            len--;
          }
          strcat(s, word);
          s += strlen(word);
          len -= strlen(word);
        }
        else
        {
          *s = '\0';
          return 1;
        }
      }
      else
        return 0;
      nl = 0;
    }
#ifdef PATCHED
    if (strlen(lyrics) < olen - 1)
#else
    if (strlen(lyrics) < olen)
#endif
    {
      strcat(s, "\n");
      s++;
      len--;
    }
  }
  *s = '\0';
  return 1;
}

void print_menu()
{
  printf("1. Submit lyrics\n");
  printf("2. View lyrics\n");
  printf("-3. Quit\n");
}

void init()
{
  int i;
  bloomy = bloomy_new(128, moomoo, yooyoo, geegee);
  if (bloomy == NULL)
    exit(-1);

  for (i = 0; i < sizeof(depressing_words) / sizeof(char*); ++i)
    bloomy_add(bloomy, depressing_words[i]);
}

int main()
{
  uint8_t good = 0;
  char buf[8], lyrics[2048];

  printf("~=~=~=~= Bloomy Sunday =~=~=~=~\n");
  init();

  while (1)
  {
    print_menu();
    printf("> ");

   if (read_until(STDIN, buf, sizeof(buf), '\n') < 0)
     goto fail;
   switch (strtol(buf, NULL, 10))
   {
     case 1:
       good = submit_lyrics(lyrics, sizeof(lyrics));
       break;
     case 2:
       if (!good)
         printf("not good.\n");
       else
         printf("%s", lyrics);
       break;
     case -3:
       printf("Don't let the sadness grow.\n\n");
       exit(0);
       break;
     default:
       printf("Nope!\n");
       break;
   }
   printf("\n");
  }
  return 0;

fail:
  printf("fail\n");
  return -1;
}
