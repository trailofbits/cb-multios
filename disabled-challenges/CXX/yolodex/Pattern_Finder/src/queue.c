/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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
#include "libcgc.h"

#include "cgc_stdio.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_assert.h"
#include "cgc_safe.h"
#include "cgc_queue.h"

void cgc_InitializeQueue(queue* Queue)
{
#define INITIAL_QUEUE_SIZE 2
  Queue->Size = 0;
  Queue->Capacity = INITIAL_QUEUE_SIZE;
  Queue->Elements = cgc_xcalloc(sizeof(void *), INITIAL_QUEUE_SIZE);
  Queue->KnownHead = -1;
}

void cgc_FreeQueue(queue* Queue)
{
  if (Queue)
  {
    if (Queue->Elements)
    {
      cgc_free(Queue->Elements);
    }

    cgc_free(Queue);
  }
}

// This maintains relative ordering
void cgc_ShiftQueueElementsToFront(queue* Queue)
{
  cgc_size_t QueueIndex;
  cgc_size_t SwapSrcIndex;
  cgc_size_t SwapDstIndex;

  if (!Queue)
    return;

  for (;;)
  {
    SwapSrcIndex = SwapDstIndex = Queue->Capacity;

    for (QueueIndex = 0; QueueIndex < Queue->Capacity; QueueIndex++)
    {
      if (SwapDstIndex == Queue->Capacity && !Queue->Elements[QueueIndex])
        SwapDstIndex = QueueIndex;
      else if (SwapDstIndex != Queue->Capacity && SwapSrcIndex == Queue->Capacity && Queue->Elements[QueueIndex])
        SwapSrcIndex = QueueIndex;

      if (SwapSrcIndex < Queue->Capacity && SwapDstIndex < Queue->Capacity)
        break;
    }

    if (SwapSrcIndex == Queue->Capacity || SwapDstIndex == Queue->Capacity)
      break;

    Queue->Elements[SwapDstIndex] = Queue->Elements[SwapSrcIndex];
    Queue->Elements[SwapSrcIndex] = NULL;
  }
}

void cgc_Enqueue(queue* Queue, void* Element)
{
  Assert(Queue->Elements[Queue->Size] == NULL, "E1");
  Queue->Elements[Queue->Size++] = Element;

  Queue->KnownHead = -1;

  // Double queue capacity
  if (Queue->Size == Queue->Capacity)
  {
    cgc_size_t NewCapacity = Queue->Capacity * 2;
    Assert(NewCapacity > Queue->Capacity, "E2");

    void** NewElements = cgc_xcalloc(sizeof(void *), NewCapacity);
    cgc_memcpy(NewElements, Queue->Elements, sizeof(void *) * Queue->Size);

    cgc_free(Queue->Elements);
    Queue->Elements = NewElements;
    Queue->Capacity = NewCapacity;
  }

}

void* cgc_Dequeue(queue* Queue)
{
  void* Result = NULL;
  cgc_size_t QueueIndex;

  Queue->KnownHead = -1;

  if (!Queue)
    return NULL;

  for (QueueIndex = 0; QueueIndex < Queue->Size; QueueIndex++)
  {
    if (Queue->Elements[QueueIndex])
    {
      Result = Queue->Elements[QueueIndex];
      Queue->Elements[QueueIndex] = NULL;
      break;
    }
  }

  if ((QueueIndex & 0xFF) == 0xFF)
    cgc_ShiftQueueElementsToFront(Queue);

  return Result;
}

void* cgc_Peek(queue* Queue)
{
  cgc_size_t QueueIndex;
  if (!Queue)
    return NULL;

  if (Queue->KnownHead >= 0)
      return Queue->Elements[Queue->KnownHead];

  for (QueueIndex = 0; QueueIndex < Queue->Size; QueueIndex++)
  {
    if (Queue->Elements[QueueIndex])
    {
      Queue->KnownHead = QueueIndex;
      return Queue->Elements[QueueIndex];
    }
  }

  return NULL;
}
