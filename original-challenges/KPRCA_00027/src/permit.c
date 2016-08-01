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
#include "permit.h"

int _validate_permit_token(char *token);
int _validate_license_number(char *license_number);

ppermit_t* permit_new(char *license_number, int num_entrances, int spot_number)
{
  ppermit_t *permit = NULL;
  if (_validate_license_number(license_number) != 0 ||
      spot_number > MAX_SPOT_NUMBER)
    return NULL;
  if ((permit = (ppermit_t *) malloc(sizeof(ppermit_t))) != NULL)
  {
    int i, cs;
    random(permit->permit_token, sizeof(permit->permit_token), NULL);
    permit->permit_token[4] = 0x55;
    for (i = 0; i < sizeof(permit->permit_token) - 1; ++i)
      cs += ((int) permit->permit_token[i]) & 0xFF;
    permit->permit_token[sizeof(permit->permit_token) - 1] = (char) (cs % 0xAB);
    strncpy(permit->license_number, license_number, sizeof(permit->license_number) - 1);
    permit->num_entrances = num_entrances;
    permit->spot_number = spot_number;
  }
  return permit;
}

ppring_t* pring_new(int num_permits, ppermit_t permits[])
{
  ppring_t *pring = NULL;
  if ((pring = (ppring_t *) malloc(sizeof(ppring_t))) != NULL)
  {
    int i;
    ppermit_t *permit;
    memset(pring, 0, sizeof(ppring_t));
    for (i = 0; i < num_permits; ++i)
      memcpy(&pring->permits[i], &permits[i], sizeof(ppermit_t));
    pring->num_permits = num_permits;
  }
  return pring;
}

ppring_t* pring_refactor(ppring_t *pring)
{
  if (pring && pring->num_permits <= MAX_NUM_PERMITS)
  {
    int i = 0, j = 0, found = 1, count = 0;
    int n = pring->num_permits;

    while (found)
    {
      found = 0;
      for (i = 0; i < pring->num_permits; ++i)
      {
        if (pring->permits[i].num_entrances <= 0)
        {
          found = 1;
          count++;
          for (j = i; j < pring->num_permits - 1; ++j)
          {
            memcpy(&pring->permits[j], &pring->permits[j + 1], sizeof(ppermit_t));
          }
          pring->num_permits--;
          break;
        }
      }
    }
    if (count > 0)
      memset(&pring->permits[n - count], 0, count * sizeof(ppermit_t));
  }
  return pring;
}

int _validate_permit_token(char *token)
{
  int i, cs = 0;
  if (token[4] != 0x55)
    return -1;
  for (i = 0; i < 7; ++i)
    cs += ((int) token[i]) & 0xFF;
  if (token[7] != (char) (cs % 0xAB))
    return -1;
  return 0;
}

int _validate_license_number(char *license_number)
{
  int i, count = 0;
  if (strlen(license_number) > 9)
    return -1;
  for (i = 0; i < strlen(license_number); ++i)
  {
    if (!isalnum(license_number[i] & 0xFF))
      return -1;
    if (!isalpha(license_number[i] & 0xFF))
      count++;
  }
  if (count < 1 || count > 4)
    return -1;
  return 0;
}

int permit_test(ppermit_t *permit, int spot_number, char *license_number)
{
  if (permit && license_number)
  {
    if (_validate_permit_token(permit->permit_token) != 0)
      return PRES_INVALID_TOKEN;
    if (_validate_license_number(permit->license_number) != 0 ||
        strcmp(permit->license_number, license_number) != 0)
      return PRES_INVALID_LICENSE;
    if (permit->num_entrances <= 0)
      return PRES_EXPIRED;
    if (spot_number > MAX_SPOT_NUMBER)
      return PRES_INVALID_SPOT;
    if (permit->spot_number != spot_number)
      return PRES_INVALID_SPOT;

    return PRES_OK;
  }
  return PRES_ERROR;
}

int pring_test(ppring_t *pring, int spot_numbers[], char* license_numbers)
{
  if (pring && spot_numbers && license_numbers)
  {
    int i, res;
    for (i = 0; i < pring->num_permits; ++i)
    {
      res = permit_test(&pring->permits[i], spot_numbers[i], &license_numbers[i * 10]);
      if (res != PRES_OK)
        return res;
    }
    return PRES_OK;
  }
  return PRES_ERROR;
}

void destroy_permit(ppermit_t *permit)
{
  if (permit)
    free(permit);
}

void destroy_permit_ring(ppring_t *pring)
{
  if (pring)
    free(pring);
}
