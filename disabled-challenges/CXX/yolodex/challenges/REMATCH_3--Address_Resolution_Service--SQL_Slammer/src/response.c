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
#include "cgc_libc.h"
#include "cgc_malloc.h"
#include "cgc_stdio.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_service.h"

response *cgc_DestroyResponse(response *pResponse)
{
  if (pResponse == NULL) 
  {
    return NULL;
  }

  if (pResponse->data != NULL) 
  {
    cgc_free(pResponse->data);
  }
  cgc_free(pResponse);
  return NULL;
}

response *cgc_GenerateBlankResponse() 
{
  response *pResponse;
  pResponse = cgc_calloc(sizeof(response));
  return pResponse;
}

int cgc_AddToResponse(response *pResponse, char *pString) 
{
  if (pString == NULL) 
  {
    return -1;
  }
  int newLength = cgc_strlen(pString);
  if (pResponse->data != NULL) 
  {
    newLength += pResponse->size;
  }
  char *newData = cgc_calloc(newLength + 1);
  char *newDataPtr = newData;

  if (pResponse->data != NULL) 
  {
    cgc_strncpy(newData, (char *)pResponse->data, pResponse->size);
    newDataPtr += pResponse->size;
  }
  cgc_strcpy(newDataPtr, pString);
  cgc_free(pResponse->data);
  pResponse->data = (uint8_t *)newData;
  pResponse->size = newLength;
  return 1;
}

int cgc_DumpResponse(response *pResponse) 
{
  if (pResponse == NULL) 
  {
    return -1;
  }
  cgc_printf("Response Length: $d\n", pResponse->size);
  cgc_printf("Response Data: $s\n", pResponse->data);
  return 0;
}

int cgc_SendResponse(response *pResponse) 
{
  if (pResponse == NULL) 
  {
    return -1;
  }
  char byte = RESPONSE;
  if (cgc_SendBytes(&byte, 1) != 1) 
  {
    return -1;
  }
  if (cgc_SendBytes((char *)&(pResponse->size), sizeof(pResponse->size)) != 2)
  {
    return -1;
  }
  if (cgc_SendBytes((char *)pResponse->data, pResponse->size) != pResponse->size) 
  {
    return -1;
  }
  if (cgc_SendBytes("\0", 1) != 1) 
  {
    return -1;
  }
  return 0;
}