/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
/**
 * @file list.h
 * 
 * Macros for operating on intrusive doubly-linked lists.
 */

#ifndef LIST_H_
#define LIST_H_

/**
 * Declare a list of a certain (struct) type.
 *
 * @param type The type of each node in the list
 */
#define LIST_OF(type) struct { type *head, *tail; }

/**
 * Declare the intrusive next and previous pointers inside an element struct.
 *
 * @param type The type of each node in the list
 */
#define LIST_ELEMS(type) struct { type *next, *prev; }

/**
 * Initializes a list.
 *
 * @param list A pointer to the list
 */
#define LIST_INIT(list) do { (list)->head = (list)->tail = NULL; } while (0)

/**
 * Initializes the next and previous pointers inside an element struct.
 *
 * @param elems A pointer to the list elements
 */
#define LIST_ELEMS_INIT(elems) do { (elems)->next = (elems)->prev = NULL; } while (0)

/**
 * Insert a new node into a list, before a target node.
 *
 * @param list A pointer to the list
 * @param name The name of the list element struct inside of a node struct
 * @param succ The node to preceded with the new node
 * @param toadd The new node to add
 */
#define LIST_INSERT(list, name, succ, toadd) do {                           \
    (toadd)->name.next = (toadd)->name.prev = NULL;                         \
                                                                            \
    if ((list)->head == NULL && (list)->tail == NULL) {                     \
        (list)->head = (list)->tail = toadd;                                \
    } else if (succ == NULL) {                                              \
        (toadd)->name.prev = (list)->tail;                                  \
        (list)->tail->name.next = toadd;                                    \
        (toadd)->name.next = NULL;                                          \
        (list)->tail = toadd;                                               \
    } else if (succ == (list)->head) {                                      \
        (toadd)->name.next = (list)->head;                                  \
        (list)->head->name.prev = toadd;                                    \
        (toadd)->name.prev = NULL;                                          \
        (list)->head = toadd;                                               \
    } else {                                                                \
        (toadd)->name.prev = (succ)->name.prev;                             \
        (toadd)->name.next = succ;                                          \
        (succ)->name.prev->name.next = toadd;                               \
        (succ)->name.prev = toadd;                                          \
    }                                                                       \
} while (0)

/**
 * Insert a node at the beginning of a list.
 *
 * @param list A pointer to the list
 * @param name The name of the list element struct inside of a node struct
 * @param toadd The new node to add
 */
#define LIST_PUSH_FRONT(list, name, toadd) LIST_INSERT(list, name, (list)->head, toadd)

/**
 * Insert a node at the end of a list.
 *
 * @param type The type of each node in the list
 * @param list A pointer to the list
 * @param name The name of the list element struct inside of a node struct
 * @param toadd The new node to add
 */
#define LIST_PUSH_BACK(type, list, name, toadd) LIST_INSERT(list, name, (type *)NULL, toadd)

/**
 * Remove a node from a list
 *
 * WARNING: Always remove a temporary, don't try e.g.
 *      LIST_REMOVE(list, list, list->head).
 * 
 * @param list A pointer to the list
 * @param name The name of the list element struct inside of a node struct
 * @param torem The node to remove
 */
#define LIST_REMOVE(list, name, torem) do {                                 \
    if ((torem)->name.prev == NULL)                                         \
        (list)->head = (torem)->name.next;                                  \
    else                                                                    \
        (torem)->name.prev->name.next = (torem)->name.next;                 \
                                                                            \
    if ((torem)->name.next == NULL)                                         \
        (list)->tail = (torem)->name.prev;                                  \
    else                                                                    \
        (torem)->name.next->name.prev = (torem)->name.prev;                 \
} while (0)

/**
 * Remove the first node in a list and assign to ret
 *
 * @param list A pointer to the list
 * @param name The name of the list element struct inside of a node struct
 * @param ret The value to assign the removed node to
 */
#define LIST_POP_FRONT(list, name, ret) do {                                \
    ret = (list)->head;                                                     \
    if (ret)                                                                \
        LIST_REMOVE(list, name, ret);                                       \
} while (0)

/**
 * Remove the last node in a list and assign to ret
 *
 * @param list A pointer to the list
 * @param name The name of the list element struct inside of a node struct
 * @param ret The value to assign the removed node to
 */
#define LIST_POP_BACK(list, name, ret) do {                                 \
    ret = (list)->tail;                                                     \
    if (ret)                                                                \
        LIST_REMOVE(list, name, ret);                                       \
} while (0)

/**
 * Traverse a list in the forward direction.
 *
 * @param list A pointer to the list
 * @param name The name of the list element struct inside of a node struct
 * @param cur The variable to use as an iterator
 */
#define LIST_FOR_EACH(list, name, cur)                                      \
    for (cur = (list)->head; cur != NULL; cur = (cur)->name.next)

/**
 * Traverse a list in the backwards direction.
 *
 * @param list A pointer to the list
 * @param name The name of the list element struct inside of a node struct
 * @param cur The variable to use as an iterator
 */
#define LIST_FOR_EACH_REVERSE(list, name, cur)                              \
    for (cur = (list)->tail; cur != NULL; cur = (cur)->name.prev)

#endif /* LIST_H_ */

