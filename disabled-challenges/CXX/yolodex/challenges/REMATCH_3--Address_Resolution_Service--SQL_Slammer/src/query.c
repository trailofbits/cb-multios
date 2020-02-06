/*

Author: Debbie Nuttall <debbie@cromulence.com>

Copyright (c) 2016 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include "libcgc.h"
#include "cgc_malloc.h"
#include "cgc_string.h"
#include "cgc_stdlib.h"
#include "cgc_service.h"

query *cgc_DestroyQuery(query *pQuery) 
{
  if (pQuery == NULL) 
  {
    return NULL;
  }
  if(pQuery->data != NULL) 
  {
    cgc_free(pQuery->data);
  }
  cgc_free(pQuery);
  return NULL;
}

query *cgc_ParseQuery(char *inputBuffer)
{
  if (inputBuffer == NULL) {
    return NULL;
  }
  query *pQuery = cgc_calloc(sizeof(query));
  pQuery->type = inputBuffer[0];
  pQuery->length = cgc_strlen(&inputBuffer[1]);
  pQuery->data = cgc_calloc(pQuery->length + 1);
  cgc_strcpy((char *)pQuery->data, &inputBuffer[1]);
  return pQuery;
}