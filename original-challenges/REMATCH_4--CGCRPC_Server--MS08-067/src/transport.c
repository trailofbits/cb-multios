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
#include <libcgc.h>
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "malloc.h"
#include "transport.h"

int ReceiveBytes(uint8_t *buffer, int length)
{
  int totalBytes = 0;
  int returnValue;
  size_t bytesReceived;

  if (buffer == NULL) 
  {
    return -1;
  }

  while (totalBytes < length)
  {
    returnValue = receive(STDIN, buffer + totalBytes, length - totalBytes, &bytesReceived);
    if (returnValue != 0) 
    {
      _terminate(-1);
    }
    if (bytesReceived == 0)
    {
      _terminate(-1);
    }
    totalBytes += bytesReceived;
  }
  return 0;
}



int TransmitBytes(uint8_t *buffer, int length)
{
  int totalBytes = 0;
  int returnValue = 0;
  size_t bytesSent;

  while (totalBytes < length)
  {
    returnValue = transmit(STDOUT, buffer + totalBytes, length - totalBytes, &bytesSent);
    if (returnValue != 0)
    {
      _terminate(-1);
    }
    if (bytesSent == 0)
    {
      _terminate(-1);
    }
    totalBytes += bytesSent;
  }
  return 0;
}


void ResetTransportMessage(TransportMessage *tpMessage)
{
  if (tpMessage == NULL) 
  {
    return;
  }
  tpMessage->currentOffset = 0;
}

int ReceiveTransportMessage(TransportMessage **ptpMessage)
{
  TransportMessage *tpMessage= calloc(sizeof(TransportMessage));
  ReceiveBytes((uint8_t *)&tpMessage->reserved, sizeof(tpMessage->reserved));
  if (tpMessage->reserved != 0)
  {
    goto FAIL;
  }
  ReceiveBytes((uint8_t *)&tpMessage->size, sizeof(tpMessage->size));
  if (tpMessage->size > MAX_TRANSPORT_SIZE)
  {
    goto FAIL;
  }
  tpMessage->data = calloc(tpMessage->size);
  ReceiveBytes((uint8_t *)tpMessage->data, tpMessage->size);
  
  *ptpMessage = tpMessage;
  return 0;

FAIL:
  DestroyTransportMessage(&tpMessage);
  *ptpMessage = NULL;
  return -1;
}

void DestroyTransportMessage(TransportMessage **ptpMessage)
{
  if (ptpMessage == NULL)
  {
    _terminate(-1);
  }
  TransportMessage *tpMessage = *ptpMessage;
  if (tpMessage == NULL)
  {
    return;
  }
  if (tpMessage->data != NULL) 
  {
    free(tpMessage->data);
    tpMessage->data = NULL;
  }
  free(tpMessage);
  *ptpMessage = NULL;

}

void SendTransportMessage(TransportMessage *tpMessage) 
{
  TransmitBytes((uint8_t *)&tpMessage->reserved, sizeof(tpMessage->reserved));
  TransmitBytes((uint8_t *)&tpMessage->size, sizeof(tpMessage->size));
  TransmitBytes((uint8_t *)tpMessage->data, tpMessage->size);
}

int ReadFromTransportMessage(TransportMessage *tpMessage, uint8_t *buffer, int size)
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
  memcpy(buffer, (uint8_t *)tpMessage->data + tpMessage->currentOffset, size);
  tpMessage->currentOffset += size;

  return 0;
}