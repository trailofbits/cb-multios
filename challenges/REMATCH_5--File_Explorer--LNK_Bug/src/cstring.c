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
#include "cgc_stdint.h"
#include "cgc_stdio.h"
#include "cgc_malloc.h"
#include "cgc_cstring.h"

int cgc_ReceiveBytes(char *buffer, int length)
{
  int totalBytes = 0;
  int returnValue;
  cgc_size_t bytesReceived;

  if (buffer == NULL) 
  {
    return -1;
  }

  while (totalBytes < length)
  {
    returnValue = cgc_receive(STDIN, buffer + totalBytes, length - totalBytes, &bytesReceived);
    if (returnValue != 0) 
    {
      cgc__terminate(-1);
    }
    if (bytesReceived == 0)
    {
      cgc__terminate(-1);
    }
    totalBytes += bytesReceived;
  }
  return totalBytes;
}


int cgc_TransmitBytes(char *buffer, int length)
{
  int totalBytes = 0;
  int returnValue = 0;
  cgc_size_t bytesSent;

  while (totalBytes < length)
  {
    returnValue = cgc_transmit(STDOUT, buffer + totalBytes, length - totalBytes, &bytesSent);
    if (returnValue != 0)
    {
      cgc__terminate(-1);
    }
    if (bytesSent == 0)
    {
      cgc__terminate(-1);
    }
    totalBytes += bytesSent;
  }
  return 0;
}

cString *cgc_ReceiveCString(int maxLen)
{
  cString *newString = cgc_calloc(sizeof(cString));
  if (cgc_ReceiveBytes((char *)&newString->length, sizeof(newString->length)) != sizeof(newString->length))
  {
    cgc_DestroyCString(newString);
    return NULL;
  }
  if (newString->length > maxLen)
  {
    cgc_printf("FATAL\n");
    cgc__terminate(-2);
  }
  if (newString->length > 0)
    {
    newString->string = cgc_calloc(newString->length + 1) ;
    if (cgc_ReceiveBytes(newString->string, newString->length) != newString->length)
    {
      cgc_DestroyCString(newString);
      return NULL;
    }
  }
  return newString;
}

void cgc_DestroyCString(cString *s)
{
  if (s)
  {
    cgc_free(s->string);
  }
  cgc_free(s);
}

void cgc_TransmitCString(cString *s)
{
  cgc_TransmitBytes((char *)&s->length, sizeof(s->length));
  cgc_TransmitBytes(s->string, s->length);
}

