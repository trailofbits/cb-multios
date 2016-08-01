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
#include <filaments.h>
#include <ctype.h>
#include "readuntil.h"
#include "memo.h"
#include "ac.h"

typedef struct entry {
  memo_t *memo;
  struct entry *next;
} entry_t;

entry_t *memos = NULL;
int g_num_memos = 0;
char g_memo_ids[MAX_MEMO_ID] = { 0 };

int _find_memo_id()
{
  int i;
  for (i = 0; i < MAX_MEMO_ID; ++i)
  {
    if (g_memo_ids[i] == 0)
      return i;
  }
  return -1;
}

void add_memo()
{
  int num;
  int ret = 0;
  char buf[MAX_MEMO_BODY];
  int bytes;
  entry_t *node, *temp;
  memo_t *memo;
  if ((memo = new_memo(default_view_memo, default_update_memo, default_delete_memo)) != NULL &&
      (node = (entry_t *)malloc(sizeof(entry_t))) != NULL)
  {
    printf("subject? ");
    if ((bytes = read_until(STDIN, buf, MAX_MEMO_BODY, '\n')) < 0)
      goto fail;
    if (strlen(buf) >= MAX_MEMO_SUBJECT)
      goto fail;
    strcpy(memo->subject, buf);
    printf("year? ");
    if ((bytes = read_until(STDIN, buf, MAX_MEMO_BODY, '\n')) < 0)
      goto fail;
    num = strtol(buf, NULL, 10);
    memo->date.year = num;
    printf("month? ");
    if ((bytes = read_until(STDIN, buf, MAX_MEMO_BODY, '\n')) < 0)
      goto fail;
    num = strtol(buf, NULL, 10);
    memo->date.month = num;
    printf("date? ");
    if ((bytes = read_until(STDIN, buf, MAX_MEMO_BODY, '\n')) < 0)
      goto fail;
    num = strtol(buf, NULL, 10);
    memo->date.date = num;
    printf("priority? ");
    if ((bytes = read_until(STDIN, buf, MAX_MEMO_BODY, '\n')) < 0)
      goto fail;
    num = strtol(buf, NULL, 10);
    memo->priority = num;
    printf("body? ");
    memo->body = ac_read(STDIN, '\n');
    if (memo->body == NULL)
      goto fail;

    if (g_num_memos >= MAX_MEMO_ID)
      goto fail;
    memo->id = _find_memo_id();

    if ((ret = validate_memo(memo)) != MRES_OK)
      goto fail;

    g_memo_ids[memo->id] = 1;
    g_num_memos++;
    node->memo = memo;
    if (memos == NULL)
    {
      memos = node;
      memos->next = NULL;
    }
    else
    {
      temp = memos;
      while (temp->next != NULL)
      {
        temp = temp->next;
      }
      node->next = NULL;
      temp->next = node;
    }
    printf("id: %d created.\n", memo->id);
    return;
  }
fail:
  if (memo)
    memo->mfuns[MOP_DELETE](memo);
  if (node)
    free(node);
  fdprintf(STDERR, "created failed.\n");
  return;
}

void update_memo(int id)
{
  entry_t *temp;
  temp = memos;
  while (temp != NULL)
  {
    if (temp->memo && temp->memo->id == id)
    {
      temp->memo->mfuns[MOP_UPDATE](temp->memo);
      break;
    }
    temp = temp->next;
  }
}

void remove_memo(int id)
{
  entry_t *node, *temp;
  temp = memos;
  while (temp != NULL)
  {
    if (temp->memo && temp->memo->id == id)
    {
      g_memo_ids[id] = 0;
      g_num_memos--;
      if (temp == memos)
      {
        memos = temp->next;
        temp->memo->mfuns[MOP_DELETE](temp->memo);
        free(temp);
        break;
      }
      else
      {
        node->next = temp->next;
        temp->memo->mfuns[MOP_DELETE](temp->memo);
        free(temp);
        break;
      }
    }
    else
    {
      node = temp;
      temp = temp->next;
    }
  }
}

void view_memo(int id)
{
  entry_t *temp;
  temp = memos;
  while (temp != NULL)
  {
    if (temp->memo && temp->memo->id == id)
    {
      temp->memo->mfuns[MOP_VIEW](temp->memo);
      break;
    }
    temp = temp->next;
  }
}

void quit()
{
  printf("bye!\n");
  exit(0);
}

void menu()
{
  printf("======================\n");
  printf(" 1. New memo\n");
  printf(" 2. View memo\n");
  printf(" 3. Update memo\n");
  printf(" 4. Delete memo\n");
  printf(" 5. Add custom AC word\n");
  printf(" 6. Quit\n");
  printf("======================\n");
}

int main()
{
  char input[4];
  char typo[MAX_AC_LEN], correct[MAX_AC_LEN];
  filaments_init();
  filaments_new(ac_process, NULL);
  printf("====== 3M v0.2 ======\n");

  menu();
  ac_init();
  while (1)
  {
    int menu_n, memo_id = -1;
    int bytes;
    if ((bytes = read_until(STDIN, input, sizeof(input), '\n')) < 0)
      return 0;
    menu_n = strtol(input, NULL, 10);

    switch (menu_n)
    {
      case 1:
        add_memo();
        break;
      case 2:
        printf("id? ");
        if ((bytes = read_until(STDIN, input, sizeof(input), '\n')) < 0)
          break;
        if (input[0] != '\0')
        {
          memo_id = strtol(input, NULL, 10);
          view_memo(memo_id);
        }
        break;
      case 3:
        printf("id? ");
        if ((bytes = read_until(STDIN, input, sizeof(input), '\n')) < 0)
          break;
        memo_id = strtol(input, NULL, 10);
        update_memo(memo_id);
        break;
      case 4:
        printf("id? ");
        if ((bytes = read_until(STDIN, input, sizeof(input), '\n')) < 0)
          break;
        memo_id = strtol(input, NULL, 10);
        remove_memo(memo_id);
        break;
      case 5:
        memset(typo, 0, sizeof(typo));
        memset(correct, 0, sizeof(correct));
        printf("typo? ");
        if ((bytes = read_until(STDIN, typo, sizeof(typo), '\n')) < 0)
          break;
        printf("correct? ");
        if ((bytes = read_until(STDIN, correct, sizeof(correct), '\n')) < 0)
          break;
        ac_add_custom(typo, correct);
        break;
      case 6:
        quit();
        break;
      default:
        printf("invalid menu, try again.\n");
        break;
    }
  }
}
