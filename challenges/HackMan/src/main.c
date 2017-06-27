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

#include "libcgc.h"
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_ctype.h"

#define ERROR 9
#define NEW_CHALLENGE 0
#define RESET 1
#define QUIT 2

static int total = 0;
static int win = 0;

/* random.sample(open('/usr/share/dict/words', 'r').cgc_read().split('\n'), 20) */
static char* words[] = {
  "leonite", "drawdown", "conuzor", "franklin", "married",
  "excircle", "solidness", "aneuria", "constablery", "infractible",
  "speedingly", "scantlinged", "presphenoid", "diphyozooid", "twistiways",
  "didrachma", "fa", "gyte", "emblazonry", "insulize"
};

typedef struct hackman_state {
  void (*quit_handler) (void);
  void (*new_challenge_handler) (struct hackman_state *);
  char word[20];
  char progress[20];
  unsigned int num_tries;
} hackman_state_t;

int cgc_read_until(int fd, char *buf, cgc_size_t len, char delim)
{
  cgc_size_t i;
  char *c = buf;
  for (i = 0; i < len; ++i)
  {
    cgc_size_t rx;
    if (cgc_receive(fd, c, 1, &rx) != 0 || rx == 0)
      break;
    if (*(c++) == delim)
      break;
  }
  *(c-1) = '\0';
  return c - buf;
}

char cgc_parse_input(char *buf)
{
  if (cgc_read_until(STDIN, buf, 128, '\n') > 0)
  {
    switch (buf[0])
    {
      case '+':
        return NEW_CHALLENGE;
        break;
      case '/':
        return QUIT;
        break;
      case '?':
        return RESET;
        break;
      default:
        if (cgc_isalpha(buf[0]))
          return cgc_tolower(buf[0]);
        break;
    }
  }
  else
    cgc_exit(0);
  return ERROR;
}


void cgc_banner()
{
  char msg[2048];
  int i, j, cnt = 0;
  cgc_memset(msg, 0, sizeof(msg));

  for (j = 0; j < 2; ++j)
  {
    for (i = 0; i < 33; ++i)
    {
      if (i % 2)
        msg[cnt++] = '-';
      else
        msg[cnt++] = '_';
    }
    msg[cnt++] = '\n';
  }

  cgc_strcpy(&msg[cnt], "     Sh41l w3 p14y a g4m3?\n");
  cnt += 27;

  for (j = 0; j < 2; ++j)
  {
    for (i = 0; i < 33; ++i)
    {
      if (i % 2)
        msg[cnt++] = '-';
      else
        msg[cnt++] = '_';
    }
    msg[cnt++] = '\n';
  }

  cgc_fdprintf(STDOUT, "%s\n", msg);
}

void cgc_record_winner()
{
  char comment[2048];
  cgc_fdprintf(STDOUT, "###### Good Work! ######\n");
  cgc_fdprintf(STDOUT, "# Leave your comment!! #\n");
  cgc_fdprintf(STDOUT, "########################\n");
  cgc_fdprintf(STDOUT, "Comment: ");
  if (cgc_read_until(STDIN, comment, sizeof(comment), '\n') > 0)
  {
    comment[2047] = '\0';
    cgc_fdprintf(STDOUT, "You wrote: %s\n", comment);
  }
  else
    cgc_exit(0);
  total++;
}

void cgc_new_challenge(hackman_state_t *h_state)
{
  unsigned short lfsr;
  unsigned int num;
  char buf[32];
  cgc_fdprintf(STDOUT, "\n@ @ @ @ @  New Challenge  @ @ @ @ @\n");
  cgc_fdprintf(STDOUT, "Seed? ");
  if (cgc_read_until(STDIN, buf, sizeof(buf), '\n') <= 0)
    cgc_exit(0);
  num = cgc_strtoul(buf, NULL, 10);
  /* only 1 round of lfsr with user-derived state. supposed to be easy to predict */
  lfsr = ((num & 0x00FF0000) >> 16) | ((num & 0x000000FF) << 8);
  if (lfsr == 0)
    lfsr = 0xACE1u;
  num = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
  num = (lfsr >> 1) | (num << 15);

  cgc_memset(h_state->word, 0, sizeof(h_state->word));
  cgc_memset(h_state->progress, 0, sizeof(h_state->progress));
  cgc_strcpy(h_state->word, words[num % 20]);
  cgc_memset(h_state->progress, '_', cgc_strlen(words[num % 20]));
  h_state->num_tries = 0;
}

void cgc_quit_game()
{
    cgc_fdprintf(STDOUT, "\n * * * * Thank you for playing! You've won %d times! * * * *\n", total);
    cgc_exit(0);
}

void cgc_play_game()
{
#if PATCHED
  hackman_state_t h_state = {0};
#else
  hackman_state_t h_state;
#endif
  char buf[128];
  int i, found, error;

  while (1)
  {
    error = 0;
    if (win || cgc_strlen(h_state.word) == 0)
      goto new_chal;
    cgc_fdprintf(STDOUT, "[[[ Your challenge: %s ]]]\n", h_state.progress);
    cgc_fdprintf(STDOUT, "Guess a letter: ");

    switch (cgc_parse_input(buf))
    {
      case NEW_CHALLENGE:
new_chal:
        if (h_state.new_challenge_handler == NULL)
          h_state.new_challenge_handler = cgc_new_challenge;
        if (h_state.quit_handler == NULL)
          h_state.quit_handler = cgc_quit_game;
        h_state.new_challenge_handler(&h_state);
        win = 0;
        continue;
        break;
      case RESET:
        h_state.num_tries = 0;
        cgc_memset(h_state.progress, '_', cgc_strlen(h_state.word));
        cgc_fdprintf(STDOUT, "\n^^^^^ RESET ^^^^^\n\n");
        continue;
        break;
      case QUIT:
        if (h_state.quit_handler == NULL)
          h_state.quit_handler = cgc_quit_game;
        h_state.quit_handler();
        break;
      case ERROR:
        error = 1;
        break;
      default:
        h_state.num_tries++;
        break;
    }

    if (!error)
    {
      found = 0;
      for (i = 0; i < cgc_strlen(h_state.word); ++i)
      {
        if (buf[0] == h_state.word[i])
        {
          h_state.progress[i] = buf[0];
          found = 1;
        }
      }

      if (found)
      {
        found = 0;
        for (i = 0; i < cgc_strlen(h_state.progress); ++i)
          if (h_state.progress[i] == '_')
            found = 1;
        if (!found)
        {
          cgc_fdprintf(STDOUT, ">>> You got it!! \"%s\" (%d tries) <<<\n", h_state.word, h_state.num_tries);
          win = 1;
          break;
        }
      }
    }
  }
}

int main(int cgc_argc, char *cgc_argv[])
{
  char buf[128];
  cgc_fdprintf(STDOUT, "\nWelcome to HackMan v13.37\n\n");

  while (1)
  {
    if (win)
      cgc_record_winner();
    else
      cgc_banner();
    cgc_play_game();
  }

  return 0;
}
