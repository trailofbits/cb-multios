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

#include <stdlib.h>
#include "stack.h"

stack_t* stack_new(unsigned int size)
{
  stack_t *stack = malloc(sizeof(stack_t));
  if (stack == NULL)
    return NULL;
  stack->length = 0;
  stack->size = size;
  stack->elems = (void **) malloc(size * sizeof(void *));
  return stack;
}

void _stack_resize(stack_t *stack, unsigned int size)
{
  void *new = realloc(stack->elems, size * sizeof(void *));
  if (new)
  {
    stack->elems = new;
    stack->size = size;
  }
}

void stack_push(stack_t *stack, void *elem)
{
  if (stack->length == stack->size)
    _stack_resize(stack, stack->size * 2);
  stack->elems[stack->length] = elem;
  stack->length++;
}

void* stack_pop(stack_t *stack)
{
  if (stack->length > 0)
  {
    if (stack->length == stack->size / 2)
      _stack_resize(stack, stack->size / 2);
    stack->length--;
    return stack->elems[stack->length];
  }
  return NULL;
}

void* stack_peek(stack_t *stack)
{
  if (stack->length > 0)
    return stack->elems[stack->length - 1];
  return NULL;
}

void stack_destroy(stack_t *stack)
{
  if (stack)
  {
    if (stack->elems)
      free(stack->elems);
    stack->length = 0;
    stack->size = 0;
    stack->elems = NULL;
  }
}

