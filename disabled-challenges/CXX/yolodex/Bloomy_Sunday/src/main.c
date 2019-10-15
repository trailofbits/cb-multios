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

#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_ctype.h"
#include "cgc_stdint.h"

#include "cgc_readuntil.h"
#include "cgc_bloomy.h"
#include "cgc_moomoo.h"

const char* depressing_words[] = {
  "gloomy", "un-cheerful", "tragic", "depressive", "dejected", "despondent",
  "destroyed", "disconsolate", "dispirited", "down", "downcast", "downhearted",
  "dragged", "pain", "pessimistic", "sad", "unhappy", "weeping", "death",
  "fear", "ruined", "lonely", "miserable", "anxious", "torment", "agony",
  "torture", "distress", "grief", "sorrow", "pathetic", "terrified", "scared"
};

bloomy_t *bloomy = NULL;

uint8_t cgc_submit_lyrics(char *lyrics, cgc_size_t len)
{
  int i, nl = 0, n = 0;
  cgc_size_t olen = len;
  char line[128], *s = lyrics;
  cgc_memset(lyrics, 0, len);
  while (1)
  {
    if (cgc_read_until(STDIN, line, sizeof(line), '\n') < 0)
      return 0;
    if (cgc_strcmp(line, "EOF") == 0)
      break;

    nl = 1;
    char *word, *input = line;
    while (1)
    {
      word = cgc_strsep(&input, " ");
      if (word == NULL)
        break;
      n = cgc_bloomy_check(bloomy, word);
      if (n == 1)
      {
        for (i = 0; i < sizeof(depressing_words) / sizeof(char*); ++i)
        {
          if (cgc_strcmp(depressing_words[i], word) == 0)
          {
            cgc_printf("depressing word detected.\n");
            return 0;
          }
        }
#if PATCHED
        if (cgc_strlen(word) < len - 1)
        {
#endif
        if (!nl)
        {
          cgc_strcat(s, " ");
          s++;
          len--;
        }
        cgc_strcat(s, word);
        s += cgc_strlen(word);
        len -= cgc_strlen(word);
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
        if (cgc_strlen(word) < len - 1)
        {
          if (!nl)
          {
            cgc_strcat(s, " ");
            s++;
            len--;
          }
          cgc_strcat(s, word);
          s += cgc_strlen(word);
          len -= cgc_strlen(word);
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
    if (cgc_strlen(lyrics) < olen - 1)
#else
    if (cgc_strlen(lyrics) < olen)
#endif
    {
      cgc_strcat(s, "\n");
      s++;
      len--;
    }
  }
  *s = '\0';
  return 1;
}

void cgc_print_menu()
{
  cgc_printf("1. Submit lyrics\n");
  cgc_printf("2. View lyrics\n");
  cgc_printf("-3. Quit\n");
}

void cgc_init()
{
  int i;
  bloomy = cgc_bloomy_new(128, cgc_moomoo, cgc_yooyoo, cgc_geegee);
  if (bloomy == NULL)
    cgc_exit(-1);

  for (i = 0; i < sizeof(depressing_words) / sizeof(char*); ++i)
    cgc_bloomy_add(bloomy, depressing_words[i]);
}

int main(int cgc_argc, char *cgc_argv[])
{
  uint8_t good = 0;
  char buf[8], lyrics[2048];

  cgc_printf("~=~=~=~= Bloomy Sunday =~=~=~=~\n");
  cgc_init();

  while (1)
  {
    cgc_print_menu();
    cgc_printf("> ");

   if (cgc_read_until(STDIN, buf, sizeof(buf), '\n') < 0)
     goto fail;
   switch (cgc_strtol(buf, NULL, 10))
   {
     case 1:
       good = cgc_submit_lyrics(lyrics, sizeof(lyrics));
       break;
     case 2:
       if (!good)
         cgc_printf("not good.\n");
       else
         cgc_printf("%s", lyrics);
       break;
     case -3:
       cgc_printf("Don't let the sadness grow.\n\n");
       cgc_exit(0);
       break;
     default:
       cgc_printf("Nope!\n");
       break;
   }
   cgc_printf("\n");
  }
  return 0;

fail:
  cgc_printf("fail\n");
  return -1;
}
