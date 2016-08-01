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
#include "readuntil.h"
#include "memo.h"

memo_t* new_memo(memo_fn view_fn, memo_fn update_fn, memo_fn delete_fn)
{
  memo_t *memo = NULL;
  if ((memo = (memo_t *)malloc(sizeof(memo_t))) != NULL)
  {
    memo->id = -1;
    memset(memo->subject, 0, sizeof(memo->subject));
    memo->date.year = 1970;
    memo->date.month = 1;
    memo->date.date = 1;
    memo->priority = PRI_NORMAL;
    memo->body = malloc(16);
    strcpy(memo->body, "");
    memo->mfuns[MOP_VIEW] = view_fn;
    memo->mfuns[MOP_UPDATE] = update_fn;
    memo->mfuns[MOP_DELETE] = delete_fn;
  }
  return memo;
}

enum mresult_t default_view_memo(memo_t *memo)
{
  int i;
  char buf[2] = { 0 };
  if (memo)
  {
    printf("[%d] %s\n", memo->id, memo->subject);
    printf("Date: %04d-%02d-%02d\n", memo->date.year, memo->date.month, memo->date.date);
    printf("Priority: ");
    switch (memo->priority)
    {
      case PRI_LOW:
        printf("*__ (Low)\n");
        break;
      case PRI_NORMAL:
        printf("**_ (Normal)\n");
        break;
      case PRI_HIGH:
        printf("*** (High)\n");
        break;
    }
    printf("------------------------------\n");
    size_t len = strlen(memo->body);
    for (i = 0; i < len; ++i)
    {
      if (i % 29 == 0)
        printf("\n");
      buf[0] = memo->body[i];
      printf("%s", buf);
    }
    printf("\n");
    return MRES_OK;
  }
  return MRES_ERROR_INTERNAL;
}

enum mresult_t default_update_memo(memo_t *o_memo)
{
  int ret = MRES_ERROR_INTERNAL;
  if (o_memo)
  {
    memo_t *memo = NULL;
    int num;
    char buf[MAX_MEMO_BODY];
    int bytes;
    if ((memo = new_memo(o_memo->mfuns[MOP_VIEW], o_memo->mfuns[MOP_UPDATE], o_memo->mfuns[MOP_DELETE])) == NULL)
      goto fail;
    printf("subject? ");
    if ((bytes = read_until(STDIN, buf, MAX_MEMO_BODY, '\n')) < 0)
      goto fail;
    if (strlen(buf) >= MAX_MEMO_SUBJECT)
      goto fail;
    if (buf[0] != '\0')
      strcpy(memo->subject, buf);
    else
      strcpy(memo->subject, o_memo->subject);
    printf("year? ");
    if ((bytes = read_until(STDIN, buf, MAX_MEMO_BODY, '\n')) < 0)
      goto fail;
    if (buf[0] != '\0')
    {
      num = strtol(buf, NULL, 10);
      memo->date.year = num;
    }
    else
      memo->date.year = o_memo->date.year;
    printf("month? ");
    if ((bytes = read_until(STDIN, buf, MAX_MEMO_BODY, '\n')) < 0)
      goto fail;
    if (buf[0] != '\0')
    {
      num = strtol(buf, NULL, 10);
      memo->date.month = num;
    }
    else
      memo->date.month = o_memo->date.month;
    printf("date? ");
    if ((bytes = read_until(STDIN, buf, MAX_MEMO_BODY, '\n')) < 0)
      goto fail;
    if (buf[0] != '\0')
    {
      num = strtol(buf, NULL, 10);
      memo->date.date = num;
    }
    else
      memo->date.date = o_memo->date.date;
    printf("priority? ");
    if ((bytes = read_until(STDIN, buf, MAX_MEMO_BODY, '\n')) < 0)
      goto fail;
    if (buf[0] != '\0')
    {
      num = strtol(buf, NULL, 10);
      memo->priority = num;
    }
    else
      memo->priority = o_memo->priority;
    printf("body? ");
    const char *body = readall_until(STDIN, '\n');
    if (body == NULL)
      goto fail;

    if (body[0] != '\0')
    {
      char *new_body = realloc(memo->body, strlen(body) + 1);
      if (new_body == NULL)
        goto fail;
      memo->body = new_body;
      strcpy(memo->body, body);
    }
    else
    {
      memo->body = strdup(o_memo->body);
    }

    memo->id = o_memo->id;

    if ((ret = validate_memo(memo)) != MRES_OK)
      goto fail;

    memcpy(o_memo->subject, memo->subject, MAX_MEMO_SUBJECT);
    memcpy(&o_memo->date, &memo->date, sizeof(memo->date));

    char *tmp = o_memo->body;
    o_memo->body = memo->body;
    memo->body = tmp;

    o_memo->priority = memo->priority;

    memo->mfuns[MOP_DELETE](memo);
    return MRES_OK;
  }

fail:
  return ret;
}

enum mresult_t default_delete_memo(memo_t *memo)
{
  if (memo)
  {
    free(memo->body);
    free(memo);
    return MRES_OK;
  }
  return MRES_ERROR_INTERNAL;
}

enum mresult_t validate_memo(memo_t *memo)
{
  if (memo)
  {
    int i;
    if (memo->id < 0 || memo->id >= MAX_MEMO_ID)
      return MRES_ERROR_MEMO_ID;
    for (i = 0; i < strlen(memo->subject); ++i)
    {
      if (!isalnum(memo->subject[i]) && !isspace(memo->subject[i]))
        return MRES_ERROR_SUBJECT;
    }
    if (memo->date.year < 1970 || memo->date.year > 2500 ||
        memo->date.month < 1 || memo->date.month > 12 ||
        memo->date.date < 1 || memo->date.date > 31)
    {
      /* No robust check on dates (e.g. leap year, # days in a month) */
      return MRES_ERROR_DATE;
    }
    if (memo->priority != PRI_LOW && memo->priority != PRI_NORMAL &&
        memo->priority != PRI_HIGH)
      return MRES_ERROR_PRIORITY;
    size_t len = strlen(memo->body); // cache length
    for (i = 0; i < len; ++i)
    {
      char c = memo->body[i];
      if (!isalnum(c) && !isspace(c) && c != '.' && c != ',' &&
          c != '!' && c != '\"' && c != '\'' && c != ':' && c != ';')
        return MRES_ERROR_BODY;
    }
    return MRES_OK;
  }
  return MRES_ERROR_INTERNAL;
}
