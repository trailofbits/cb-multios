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

#include <cstdint.h>
#include <cstdio.h>
#include <cstring.h>
#include <stdint.h>

#include "blubber.h"
#include "constants.h"
#include "rand.h"
#include "time.h"

#define ID 1

#define xstr(s) str(s)
#define str(s) #s

#ifdef DEBUG
#define dbg(M, ...) fprintf(stderr, "C" xstr(ID)" DEBUG: " M "\n", ##__VA_ARGS__);
#else
#define dbg(M, ...)
#endif

unsigned long x = ID * 983985;

struct blub_artifact
{
  size_t id;
  char username[USERNAME_MAX + 1];
  char blub[BLUB_MAX + 1];
};

void check_quit(char* s)
{
  if (strstr(s, QUIT_ID_S) != NULL)
  {
    dbg("Exiting.");
    _terminate(0);
  }
}

int handle_read(FILE* rx, FILE* tx, vector* read_blubs)
{
  size_t id;
  char username[USERNAME_MAX + 1];
  char content[BLUB_MAX + 1];

  fprintf(tx, "r" EOT_S);

  int to_read = 0;
  if (fread(&to_read, sizeof(to_read), rx) != sizeof(to_read))
  {
    dbg("Failed to read count");
    return 0;
  }
  check_quit((char *)&to_read);

  dbg("Reading %d blubs", to_read);
  for (size_t i = 0; i < to_read; ++i)
  {
    memset(username, 0, sizeof(username));
    memset(content, 0, sizeof(content));

    if (fread(&id, sizeof(id), rx) != sizeof(id))
    {
      dbg("Failed to read id");
      break;
    }
    check_quit((char *)&id);
    dbg("Got id: %d", id);

    if (fread(username, USERNAME_MAX, rx) < 0)
    {
      break;
    }

    check_quit(username);
    dbg("Read username %s", username);

    if (fread(content, BLUB_MAX, rx) < 0)
    {
      break;
    }

    check_quit(content);
    dbg("Read blub %s", content);

    blub_artifact* b = new blub_artifact;
    b->id = id;
    memcpy(b->username, username, sizeof(username));
    memcpy(b->blub, content, sizeof(content));
    read_blubs->add(b);
  }

  return 0;
}

int handle_blub(FILE* rx, FILE* tx)
{
  fprintf(tx, "b" EOT_S);
  return 0;
}

int handle_reblub(FILE* rx, FILE* tx, vector* read_blubs)
{
  if (read_blubs->length() == 0)
  {
    fprintf(tx, "y" EOT_S);
    fprintf(tx, "%s" EOT_S, "asdf");
    fprintf(tx, "%d" EOT_S, 0);
    return 0;
  }

  int pick = choice() % read_blubs->length();
  blub* b = (blub*)read_blubs->get(pick);
  if (!b)
  {
    fprintf(tx, "y" EOT_S);
    fprintf(tx, "%s" EOT_S, "asdf");
    fprintf(tx, "%d" EOT_S, 0);
    return 0;
  }

  int n = 0;
  for (size_t i = 0; i < read_blubs->length(); ++i)
  {
    if (strcmp(b->username, ((blub *)read_blubs->get(i))->username) == 0)
      n++;
  }

  fprintf(tx, "y" EOT_S);
  fprintf(tx, "%s" EOT_S, b->username);
  fprintf(tx, "%d" EOT_S, n);
  return 0;
}

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    char *secret_page = (char *)secret_page_i;
    (void) secret_page;

#ifndef DEBUG
    fxlat(stdin, "9an538n9av3;5");
    fxlat(stdout, "9an538n9av3;5");
#endif

    char buf[5];
    int fd = 3 + (2 * (ID - 1) + 0);
    FILE* rx = fopen(fd, F_READ);
    FILE* tx = fopen(fd, F_WRITE);
    fbuffered(tx, 0);
    fbuffered(rx, 0);

    dbg("Starting...");
    fprintf(tx, "client_%d" EOT_S, ID);
    freaduntil(buf, 5, EOT_C, rx);
    check_quit(buf);
    dbg("Registered...");

    vector read_blubs;

    // sub to all other clients
    for (size_t i = 0; i < NUM_CLIENTS; i++)
    {
      if (i != ID)
      {
        dbg("Subbing to %d", i);
        fprintf(tx, "s" EOT_S "client_%d" EOT_S, i);
        freaduntil(buf, 5, EOT_C, rx);
        check_quit(buf);
        dbg("Subbed to %d", i);
      }
    }

    // switch between blubbing, reblubbing, and reading
    for (;;)
    {
      // get past prompt
      freaduntil(buf, 5, EOT_C, rx);
      check_quit(buf);
      dbg("Got prompt...");
      switch (choice() % 3)
      {
        case 0: // read
          {
            dbg("Doing read");
            handle_read(rx, tx, &read_blubs);
            break;
          }
        case 1: // blub
          {
            dbg("Doing blub");
            handle_blub(rx, tx);
            break;
          }
        case 2: // reblub
          {
            dbg("Trying reblub");
            handle_reblub(rx, tx, &read_blubs);
            break;
          }
      }
    }

    return 0;
}
