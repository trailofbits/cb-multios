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

#include "cgc_stdlib.h"
#include "cgc_stack.h"

stack_t* cgc_stack_new(unsigned int size)
{
  stack_t *stack = cgc_malloc(sizeof(stack_t));
  if (stack == NULL)
    return NULL;
  stack->length = 0;
  stack->size = size;
  stack->elems = (void **) cgc_malloc(size * sizeof(void *));
  return stack;
}

void cgc__stack_resize(stack_t *stack, unsigned int size)
{
  void *new = cgc_realloc(stack->elems, size * sizeof(void *));
  if (new)
  {
    stack->elems = new;
    stack->size = size;
  }
}

void cgc_stack_push(stack_t *stack, void *elem)
{
  if (stack->length == stack->size)
    cgc__stack_resize(stack, stack->size * 2);
  stack->elems[stack->length] = elem;
  stack->length++;
}

void* cgc_stack_pop(stack_t *stack)
{
  if (stack->length > 0)
  {
    if (stack->length == stack->size / 2)
      cgc__stack_resize(stack, stack->size / 2);
    stack->length--;
    return stack->elems[stack->length];
  }
  return NULL;
}

void* cgc_stack_peek(stack_t *stack)
{
  if (stack->length > 0)
    return stack->elems[stack->length - 1];
  return NULL;
}

void cgc_stack_destroy(stack_t *stack)
{
  if (stack)
  {
    if (stack->elems)
      cgc_free(stack->elems);
    stack->length = 0;
    stack->size = 0;
    stack->elems = NULL;
  }
}

