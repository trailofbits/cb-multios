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
#include "cgc_stdlib.h"
#include "cgc_stdio.h"
#include "cgc_malloc.h"
#include "cgc_transport.h"

int cgc_ReceiveBytes(uint8_t *buffer, int length)
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
  return 0;
}



int cgc_TransmitBytes(uint8_t *buffer, int length)
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


void cgc_ResetTransportMessage(TransportMessage *tpMessage)
{
  if (tpMessage == NULL) 
  {
    return;
  }
  tpMessage->currentOffset = 0;
}

int cgc_ReceiveTransportMessage(TransportMessage **ptpMessage)
{
  TransportMessage *tpMessage= cgc_calloc(sizeof(TransportMessage));
  cgc_ReceiveBytes((uint8_t *)&tpMessage->reserved, sizeof(tpMessage->reserved));
  if (tpMessage->reserved != 0)
  {
    goto FAIL;
  }
  cgc_ReceiveBytes((uint8_t *)&tpMessage->size, sizeof(tpMessage->size));
  if (tpMessage->size > MAX_TRANSPORT_SIZE)
  {
    goto FAIL;
  }
  tpMessage->data = cgc_calloc(tpMessage->size);
  cgc_ReceiveBytes((uint8_t *)tpMessage->data, tpMessage->size);
  
  *ptpMessage = tpMessage;
  return 0;

FAIL:
  cgc_DestroyTransportMessage(&tpMessage);
  *ptpMessage = NULL;
  return -1;
}

void cgc_DestroyTransportMessage(TransportMessage **ptpMessage)
{
  if (ptpMessage == NULL)
  {
    cgc__terminate(-1);
  }
  TransportMessage *tpMessage = *ptpMessage;
  if (tpMessage == NULL)
  {
    return;
  }
  if (tpMessage->data != NULL) 
  {
    cgc_free(tpMessage->data);
    tpMessage->data = NULL;
  }
  cgc_free(tpMessage);
  *ptpMessage = NULL;

}

void cgc_SendTransportMessage(TransportMessage *tpMessage) 
{
  cgc_TransmitBytes((uint8_t *)&tpMessage->reserved, sizeof(tpMessage->reserved));
  cgc_TransmitBytes((uint8_t *)&tpMessage->size, sizeof(tpMessage->size));
  cgc_TransmitBytes((uint8_t *)tpMessage->data, tpMessage->size);
}

int cgc_ReadFromTransportMessage(TransportMessage *tpMessage, uint8_t *buffer, int size)
{
  if ((tpMessage == NULL) || (buffer == NULL))
  {
    return -1;
  }
  if (tpMessage->data == NULL)
  {
    return -1;
  }
  if (size > MAX_TRANSPORT_SIZE || tpMessage->currentOffset + size > tpMessage->size )
  {
    return -1;
  }
  cgc_memcpy(buffer, (uint8_t *)tpMessage->data + tpMessage->currentOffset, size);
  tpMessage->currentOffset += size;

  return 0;
}