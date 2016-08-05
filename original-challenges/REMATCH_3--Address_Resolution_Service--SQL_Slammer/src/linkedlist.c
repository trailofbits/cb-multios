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
#include "malloc.h"
#include "stdio.h"
#include "linkedlist.h"


linkedList *NewList(int type) {
  linkedList *list = calloc(sizeof(linkedList));
  list->type = type;
  return list;
}


int AddToList(linkedList *list, void *object, int type) {
  if (list == NULL) {
    return -1;
  }
  if (object == NULL) {
    return -1;
  }
  if (type != list->type) {
    return -1;
  }
  link *newLink = calloc(sizeof(link));
  newLink->type = type;
  newLink->object = object;
  if (list->root == NULL) {
    list->root = newLink;
    return 1;
  }
  link *next = list->root;
  while (next->next != NULL) {
    next = next->next;
  }
  next->next = newLink;
  newLink->prev = next;
  return 1;
}


int RemoveFromList(linkedList *list, void *object) 
{
  if (list == NULL) 
  {
    return -1;
  }
  if (object == NULL) 
  {
    return -1;
  }
  if (list->root->object == object) 
  {
    link *toDelete = list->root ;
    list->root = list->root->next;
    list->root->prev = NULL;
    free(toDelete);
    return 1;
  }
  link *prev= list->root;
  link *this = list->root->next;
  while (this != NULL && this->object != object) 
  {
    prev = this;
    this = this->next;
  }
  if (this != NULL) 
  {
    link *toDelete = this;
    prev->next = this->next;
    if (prev->next != NULL) 
    {
      prev->next->prev = prev;
    }
    return 1;
  } 
  return -1;
}

void DumpList(linkedList *list) {
  if (list == NULL)
  {
    printf("Empty List\n");
    return;
  }
  printf("List Type: $x\n", list->type);
  int i = 0;
  link *this = list->root;
  while (this != NULL) {
    printf("$d) $s\n", i++, (char *)this->object);
    this = this->next;
  }
}