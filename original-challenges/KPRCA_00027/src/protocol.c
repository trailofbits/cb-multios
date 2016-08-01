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
#include "protocol.h"

int g_auth;
char g_mkey[MASTER_KEY_LEN] = {0x49, 0x5f, 0x41, 0x4d, 0x5f, 0x59, 0x4f, 0x55, 0x52, 0x5f, 0x46, 0x41, 0x54, 0x48, 0x45, 0x52};
char g_session_key[MASTER_KEY_LEN];

void _send_response(enum result_t res, char *data, int data_len);

void handle_command(char *buf, int buf_len)
{
  if (buf_len >= 1)
  {
    char cmd = *buf;
    buf++; buf_len--;
    switch (cmd)
    {
      case CMD_AUTH:
        handle_auth(buf, buf_len);
        break;
      case CMD_NEW_PERMIT:
        handle_new_permit(buf, buf_len);
        break;
      case CMD_NEW_PERMIT_RING:
        handle_new_permit_ring(buf, buf_len);
        break;
      case CMD_REFACTOR_RING:
        handle_refactor_ring(buf, buf_len);
        break;
      case CMD_TEST_PERMIT:
        handle_test_permit(buf, buf_len);
        break;
      case CMD_TEST_PERMIT_RING:
        handle_test_permit_ring(buf, buf_len);
        break;
      default:
        _send_response(RES_ERROR, NULL, 0);
        break;
    }
  }
  else
  {
    _send_response(RES_ERROR, NULL, 0);
  }
}

void _send_response(enum result_t res, char *data, int data_len)
{
  transmit(STDOUT, &res, 1, NULL);
  if (data == NULL || data_len == 0)
    return;
  transmit(STDOUT, (char *)&data_len, sizeof(int), NULL);
  transmit(STDOUT, data, data_len, NULL);
}

void handle_auth(char *buf, int buf_len)
{
  if (buf_len >= MASTER_KEY_LEN)
  {
    if (memcmp(g_mkey, buf, MASTER_KEY_LEN) == 0)
    {
      g_auth = 3;
      random(g_session_key, MASTER_KEY_LEN, NULL);
      _send_response(RES_OK, g_session_key, MASTER_KEY_LEN);
      return;
    }
  }
  _send_response(RES_ERROR, NULL, 0);
}

void handle_new_permit(char *buf, int buf_len)
{
  if (buf_len >= MASTER_KEY_LEN + 2 * sizeof(int) + 10)
  {
    if (g_auth && memcmp(g_session_key, buf, MASTER_KEY_LEN) == 0)
    {
      ppermit_t *permit = NULL;
      buf[MASTER_KEY_LEN + 9] = '\0';

      permit = permit_new(&buf[MASTER_KEY_LEN], *(int *)&buf[MASTER_KEY_LEN + 10], *(int *)&buf[MASTER_KEY_LEN + 10 + 4]);
      if (permit)
      {
        _send_response(RES_OK, (char *)permit, sizeof(ppermit_t));
        g_auth--;
        return;
      }
    }
  }
  _send_response(RES_ERROR, NULL, 0);
}

void handle_new_permit_ring(char *buf, int buf_len)
{
  int i, c, count;
  char key[16];
  ppring_t pring;
  if (buf_len >= MASTER_KEY_LEN + sizeof(ppring_t))
  {
    memset(&pring, 0, sizeof(ppring_t));
    memcpy(key, g_session_key, MASTER_KEY_LEN);
    if (g_auth && memcmp(key, buf, MASTER_KEY_LEN) == 0)
    {
      count = *(int *)&buf[MASTER_KEY_LEN];
      if (count <= MAX_NUM_PERMITS)
      {
#if PATCHED
        for (i = 0; i < count; ++i)
#else
        for (i = 0; i <= count; ++i)
#endif
        {
          if (i == count && buf_len - MASTER_KEY_LEN - sizeof(ppring_t) == 0)
            break;
          c = MASTER_KEY_LEN + sizeof(int) + i * sizeof(ppermit_t);
          if (permit_test((ppermit_t *)&buf[c], *(int *)&buf[c + 22], &buf[c + 8]) == PRES_OK)
          {
            memcpy(&pring.permits[i], &buf[c], sizeof(ppermit_t));
            pring.num_permits++;
          }
          else
          {
            _send_response(RES_ERROR, NULL, 0);
            return;
          }
        }
        _send_response(RES_OK, (char *)&pring, sizeof(ppring_t));
        g_auth--;
        return;
      }
    }
  }
  _send_response(RES_ERROR, NULL, 0);
}

void handle_refactor_ring(char *buf, int buf_len)
{
  if (buf_len >= MASTER_KEY_LEN + sizeof(ppring_t))
  {
    if (g_auth && memcmp(g_session_key, buf, MASTER_KEY_LEN) == 0)
    {
      ppring_t *refactored;
      refactored = pring_refactor((ppring_t *)&buf[MASTER_KEY_LEN]);
      if (refactored != NULL)
      {
        _send_response(RES_OK, (char *)refactored, sizeof(ppring_t));
        destroy_permit_ring(refactored);
        g_auth--;
        return;
      }
    }
  }
  _send_response(RES_ERROR, NULL, 0);
}

void handle_test_permit(char *buf, int buf_len)
{
  if (buf_len >= MASTER_KEY_LEN + sizeof(ppermit_t) + 2 * sizeof(int))
  {
    if (g_auth && memcmp(g_session_key, buf, MASTER_KEY_LEN) == 0)
    {
      if (permit_test((ppermit_t *)&buf[MASTER_KEY_LEN], *(int *)&buf[MASTER_KEY_LEN + sizeof(ppermit_t)], &buf[MASTER_KEY_LEN + sizeof(ppermit_t) + sizeof(int)]) == PRES_OK)
      {
        _send_response(RES_OK, NULL, 0);
        g_auth--;
        return;
      }
    }
  }
  _send_response(RES_ERROR, NULL, 0);
}

void handle_test_permit_ring(char *buf, int buf_len)
{
  if (buf_len >= MASTER_KEY_LEN + MAX_NUM_PERMITS * sizeof(ppermit_t) + MAX_NUM_PERMITS * 2 * sizeof(int))
  {
    if (g_auth && memcmp(g_session_key, buf, MASTER_KEY_LEN) == 0)
    {
      if (pring_test((ppring_t *)&buf[MASTER_KEY_LEN], (int *)&buf[MASTER_KEY_LEN + sizeof(ppring_t)], (char *)&buf[MASTER_KEY_LEN + sizeof(ppring_t) + MAX_NUM_PERMITS * sizeof(int)]) == PRES_OK)
      {
        _send_response(RES_OK, NULL, 0);
        g_auth--;
        return;
      }
    }
  }
  _send_response(RES_ERROR, NULL, 0);
}

