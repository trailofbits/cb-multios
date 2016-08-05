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
#include <cstring.h>
#include <cstdlib.h>

#include "blubber.h"
#include "constants.h"
#include "time.h"
#include "vector.h"
#include "rand.h"
#include "words.h"

blub::blub(char* _author, char* data)
{
  id = (uint32_t)this;

  size_t l = strlen(_author);
  strncpy(username, _author, l);

  memcpy(content, data, BLUB_MAX);

  ts = tick();
}

blubber::blubber(void)
{
  last_read = 0;
}

void blubber::set_username(char* _username)
{
  strcpy(username, _username);
}

blub* blubber::gen_blub(void)
{
  char buf[BLUB_MAX + 1];
  size_t rem = BLUB_MAX;
  int misses = 0;

  memset(buf, 0, BLUB_MAX + 1);

  while (0 < rem && misses < 8)
  {
    const char* word = words[choice() % (sizeof(words) / sizeof(char *))];
    if (strlen(word) + strlen(" ") <= rem)
    {
      size_t offset = strlen(buf);
      if (offset > 0)
      {
        strcpy(buf + offset, " ");
        strcpy(buf + offset + 1, word);
      }
      else
      {
        strcpy(buf + offset, word);
      }

      rem = BLUB_MAX - strlen(buf);
    }
    else
    {
      misses++;
    }
  }

  buf[BLUB_MAX] = '\0';

  blub* n = record_blub(buf);
  return n;
}

void blubber::subscribe(blubber* b)
{
  if (!subs.contains(b))
  {
    subs.add(b);
  }
}

void blubber::unsubscribe(blubber* b)
{
  if (subs.contains(b))
  {
    subs.remove(subs.index_of(b));
  }
}

blub* blubber::record_blub(char* buf)
{
  blub* n = new blub(username, buf);
  blubs.add(n);
  return n;
}
