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
#include "cgc_cstring.h"
#include "cgc_cstdlib.h"

#include "cgc_blubber.h"
#include "cgc_constants.h"
#include "cgc_time.h"
#include "cgc_vector.h"
#include "cgc_rand.h"
#include "cgc_words.h"

blub::blub(char* _author, char* data)
{
  id = (uint32_t)this;

  cgc_size_t l = cgc_strlen(_author);
  cgc_strncpy(username, _author, l);

  cgc_memcpy(content, data, BLUB_MAX);

  ts = tick();
}

blubber::blubber(void)
{
  last_read = 0;
}

void blubber::set_username(char* _username)
{
  cgc_strcpy(username, _username);
}

blub* blubber::gen_blub(void)
{
  char buf[BLUB_MAX + 1];
  cgc_size_t rem = BLUB_MAX;
  int misses = 0;

  cgc_memset(buf, 0, BLUB_MAX + 1);

  while (0 < rem && misses < 8)
  {
    const char* word = words[choice() % (sizeof(words) / sizeof(char *))];
    if (cgc_strlen(word) + cgc_strlen(" ") <= rem)
    {
      cgc_size_t offset = cgc_strlen(buf);
      if (offset > 0)
      {
        cgc_strcpy(buf + offset, " ");
        cgc_strcpy(buf + offset + 1, word);
      }
      else
      {
        cgc_strcpy(buf + offset, word);
      }

      rem = BLUB_MAX - cgc_strlen(buf);
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
