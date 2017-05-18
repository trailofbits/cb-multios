/*
 * Copyright (c) 2016 Kaprica Security, Inc.
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

#include "cgc_cstdint.h"
#include "cgc_cstdio.h"
#include "cgc_cstring.h"
#include "cgc_stdint.h"

#include "cgc_blubber.h"
#include "cgc_constants.h"
#include "cgc_time.h"

#ifdef DEBUG
#define dbg(M, ...) fprintf(stderr, "SRV DEBUG: " M "\n", ##__VA_ARGS__);
#else
#define dbg(M, ...)
#endif

#define ID 1
unsigned long x = ID * 983985;

typedef struct
{
  FILE* tx;
  FILE* rx;
  int n;
  int fd;
  bool registered;
  bool waiting;
  uint32_t last_read;
  blubber* blubber;
} client_state;

client_state* new_client(int n)
{
  client_state* c = new client_state;
  c->n = n;
  if (n == 0)
  {
    c->fd = 0;
    c->tx = cgc_stdout;
    c->rx = cgc_stdin;
  }
  else
  {
    c->fd = 3 + (2 * (n - 1) + 1);
    c->tx = cgc_fopen(c->fd, F_WRITE);
    c->rx = cgc_fopen(c->fd, F_READ);
  }

  cgc_fbuffered(c->tx, 0);
  cgc_fbuffered(c->rx, 0);

  c->last_read = 0;
  c->registered = false;
  c->blubber = new blubber();
  return c;
}

typedef struct
{
  client_state** clients;
  cgc_size_t num_clients;
  cgc_size_t num_alive;
  bool finished = false;
  FILE* log;
} server_state;

server_state* new_server(cgc_size_t n)
{
  server_state* s = new server_state;
  s->log = cgc_stderr;
  s->num_clients = n;
  s->clients = (client_state **)cgc_calloc(sizeof(client_state*), n);

  dbg("Allocating %d clients", n);
  for (cgc_size_t i = 0; i < n; ++i)
  {
    s->clients[i] = new_client(i);
  }

  return s;
}

bool client_ready(client_state* c)
{
  int ready = 0;
  cgc_fd_set set;
  FD_ZERO(&set);
  FD_SET(c->fd, &set);
  struct cgc_timeval t;
  t.tv_sec = 0;
  t.tv_usec = 100000;
  if ((cgc_fdwait(c->fd + 1, &set, nullptr, &t, &ready) == 0) && ready > 0)
  {
    if (FD_ISSET(c->fd, &set))
    {
      return true;
    }
  }

  return false;
}

void handle_read(server_state* s, client_state* c)
{
  vector unread;
  for (cgc_size_t i = 0; i < s->num_clients; ++i)
  {
    client_state* other = s->clients[i];
    if (c->blubber->subs.contains(other->blubber))
    {
      for (cgc_size_t j = 0; j < other->blubber->blubs.length(); j++)
      {
        blub* b = (blub*)other->blubber->blubs.get(j);
        if (b->ts > c->last_read)
        {
          unread.add(b);
        }
      }
    }
  }

  int to_read = unread.length();
  dbg("Sending %d %d blubs", c->n, to_read);
  cgc_fwrite(&to_read, sizeof(to_read), c->tx);

  for (cgc_size_t i = 0; i < to_read; ++i)
  {
    blub* b = (blub*)unread.get(i);
    cgc_fwrite(&b->id, sizeof(b->id), c->tx);
    cgc_fwrite(b->username, USERNAME_MAX, c->tx);
    cgc_fwrite(b->content, BLUB_MAX, c->tx);
    c->last_read = b->ts;
  }
}

void handle_blub(client_state* c)
{
  if (c->n == 0)
  {
    char tmp[BLUB_MAX + 1];
    cgc_fprintf(c->tx, "...: ");
    if (!client_ready(c) || cgc_freaduntil(tmp, BLUB_MAX, EOT_C, c->rx) < 0)
    {
      dbg("Failed to read blub");
      return;
    }
    tmp[BLUB_MAX] = '\0';

    dbg("Recorded blub (%s) %d", tmp, cgc_strlen(tmp))
    c->blubber->record_blub(tmp);
  }
  else
  {
    blub* b = c->blubber->gen_blub();
    if (b)
    {
      dbg("Recorded blub (%s) %d", b->content, cgc_strlen(b->content));
      dbg("Genned blub (%s)", b->content);
    }
  }
}

void handle_reblub(server_state* s, client_state* c)
{
  char username[USERNAME_MAX + 1];
  if (!client_ready(c) || cgc_freaduntil(username, USERNAME_MAX, EOT_C, c->rx) < 0)
  {
    dbg("Failed to read reblub username");
    return;
  }
  username[USERNAME_MAX] = '\0';

  int idx = 0;
  char num[16];
  if (!client_ready(c) || cgc_freaduntil(num, sizeof(num) - 1, EOT_C, c->rx) < 0)
  {
    dbg("Failed to read reblub number");
    return;
  }

  idx = cgc_strtol(num, NULL, 10);

  dbg("(%s) attempting to reblub (%s)'s %d blub", c->blubber->username, username, idx);
  for (cgc_size_t i = 0; i < s->num_clients; ++i)
  {
    client_state* other = s->clients[i];
    // Make sure author exists and client is subbed to them.
    if (cgc_strcmp(other->blubber->username, username) == 0 && c->blubber->subs.contains(other->blubber))
    {
      dbg("Found (%s) in (%s)'s subs", other->blubber->username, c->blubber->username);
      if (other->blubber->blubs.length() > idx)
      {
        dbg("Fetching (%s) %d blub", other->blubber->username, idx);
        blub* b = (blub*)other->blubber->blubs.get(idx);
        if (b)
        {
          dbg("(%s) reblubbed (%s)'s %d blub", c->blubber->username, other->blubber->username, idx);
          blub* n = new blub(c->blubber->username, b->content);
          c->blubber->blubs.add(n);
        }
      }
    }
  }
}

void handle_sub(server_state* s, client_state* c)
{
  char username[USERNAME_MAX + 1];
  if (!client_ready(c) || cgc_freaduntil(username, USERNAME_MAX, EOT_C, c->rx) < 0)
  {
    dbg("Failed read sub username");
    return;
  }
  username[USERNAME_MAX] = '\0';

  dbg("Attempting to sub (%s) to (%s)", c->blubber->username, username);
  for (cgc_size_t i = 0; i < s->num_clients; ++i)
  {
    client_state* other = s->clients[i];
    if (cgc_strcmp(other->blubber->username, username) == 0)
    {
      if (c->blubber->subs.contains(other->blubber))
      {
        dbg("(%s) is already subbed to (%s)", c->blubber->username, username);
        return;
      }
      else
      {
        dbg("Subbed (%s) to (%s)", c->blubber->username, username);
        c->blubber->subs.add(other->blubber);
        return;
      }
    }
  }
  dbg("Failed to sub (%s) to (%s)", c->blubber->username, username);
}

int run_server(server_state* state)
{
  for (cgc_size_t i = 0; i < state->num_clients; ++i)
  {
    client_state* c = state->clients[i];

    if (!c->registered && !state->finished)
    {
      char username[USERNAME_MAX + 1];
      cgc_memset(username, 0, sizeof(username));
      if (!client_ready(c) || cgc_freaduntil(username, USERNAME_MAX, EOT_C, c->rx) < 0)
      {
        continue;
      }

      dbg("Registered %d as (%s)", c->n, username);
      cgc_fprintf(c->tx, (char *)"Welcome to blubber, %s" EOT_S, username);
      c->registered = true;
      c->blubber->set_username(username);
      state->num_alive++;
    }

    if ((state->num_clients != state->num_alive) && !state->finished)
    {
      continue;
    }

    // Prompt
    if (!c->waiting)
    {
      if (state->finished && c->registered)
      {
        dbg("Killing %d", c->n);
        cgc_fprintf(c->tx, QUIT_ID_S EOT_S);
        c->registered = false;
        state->num_alive--;
        if (!state->num_alive)
        {
          dbg("Killing server");
          return -1;
        }
      }
      else
      {
        dbg("Prompting %d", c->n);
        cgc_fprintf(c->tx, "(*) " EOT_S);
        c->waiting = true;
      }
    }

    // Get command
    char command = '\x00';
    if (!client_ready(c) || cgc_fread(&command, 1, c->rx) != 1)
    {
      continue;
    }

    char dump;
    if (client_ready(c))
    {
      cgc_freaduntil(&dump, 1, EOT_C, c->rx);
      dbg("Unwaiting %d", c->n);
      c->waiting = false;
    }

    dbg("Read command: %c from %d", command, c->n);
    switch (command)
    {
      case 'r':
        handle_read(state, c);
        break;
      case 'e':
        state->finished = true;
        break;
      case 's':
        handle_sub(state, c);
        break;
      case 'b':
        handle_blub(c);
        break;
      case 'y':
        handle_reblub(state, c);
        break;
    }

    if (command)
    {
      dbg("Unwaiting %d", c->n);
      c->waiting = false;
    }
  }

  return 0;
}

extern "C" int main(int secret_page_i,  char *unused[]) {
    secret_page_i = CGC_FLAG_PAGE_ADDRESS;

#ifndef DEBUG
    cgc_fxlat(cgc_stdin, "9an538n9av3;5");
    cgc_fxlat(cgc_stdout, "9an538n9av3;5");
#endif

    uint32_t volatile *secret_page = (uint32_t *)secret_page_i;
    uint32_t sig = 0;
    for (cgc_size_t i = 0; i < 0x1000 / sizeof(uint32_t); i++)
    {
      sig ^= *(secret_page + i);
    }
    cgc_fwrite(&sig, sizeof(sig), cgc_stdout);

    dbg("Starting");
    server_state* state = new_server(NUM_CLIENTS);
    while (0 == run_server(state)) {}
    dbg("Exiting");
    return 0;
}
