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

#ifndef LLIST_H
#define LLIST_H

extern "C" {
  #include <stdlib.h>
  #include <string.h>
};

template <typename T>
class List
{
  struct Element
  {
    T obj;
    Element *next;
    Element(T o, Element *n = 0) : obj(o), next(n) {}
  };
  Element *head;
  unsigned int len;

  public:
    List(Element *h = 0) : head(h), len(0) {}
    ~List();

    void add(T o);
    void remove(T o);
    Element* find(T o);
    T get(int idx);
    unsigned int length() { return len; }
    void debug();
};

template <typename T>
List<T>::~List()
{
  Element *tmp;
  while (head)
  {
    tmp = head;
    head = tmp->next;
    delete tmp;
  }
}

template <typename T>
void List<T>::add(T o)
{
  Element *item = new Element(o, 0);
  if (!head)
    head = item;
  else
  {
    Element *tmp = head;
    while (tmp && tmp->next) tmp = tmp->next;
    tmp->next = item;
  }
  len++;
}

template <typename T>
void List<T>::remove(T o)
{
  Element *item = find(o), *tmp;
  if (!item)
    return;
  if (item == head)
  {
    tmp = head->next;
    delete head;
    head = tmp;
  }
  else
  {
    tmp = head;
    while (tmp && tmp->next != item) tmp = tmp->next;
    tmp->next = item->next;
    delete item;
  }
  len--;
}

template <typename T>
typename List<T>::Element* List<T>::find(T o)
{
  if (!head)
    return 0;
  Element *tmp = head;
  while (tmp && tmp->obj != o) tmp = tmp->next;
  return tmp;
}

template <typename T>
T List<T>::get(int idx)
{
  if (!head || idx >= len)
    return 0;
  Element *tmp = head;
  while (idx--) tmp = tmp->next;
  return tmp->obj;
}

template <typename T>
void List<T>::debug()
{
  if (!head)
  {
    printf("Empty list!\n");
    return;
  }
  Element *tmp = head;
  while (tmp)
  {
    printf("[%d (%08x)] ", tmp->obj, tmp->obj);
    tmp = tmp->next;
  }
  printf("\n");
}

#endif
