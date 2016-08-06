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
* Routines for manipulating intrusive doubly-linked lists, based on Linux kernel list.h
*   interface
*/

#ifndef LIST_H_
#define LIST_H_

#include "libc.h"

struct list_node {
    struct list_node *next, *prev;
};

struct list {
    struct list_node *head, *tail;
};

/**
 * Initialize a list
 *
 * @param list A pointer to the list
 */
#define list_init(list) do { (list)->head = (list)->tail = NULL; } while (0)

/**
 * Get the entry associated with a particular node.
 *
 * @param type The type of the list entry
 * @param member The member of the entry containing the list node
 * @param node The list node
 * @return The entry associated with the node
 */
#define list_entry(type, member, node) CONTAINEROF(type, member, node)

/**
 * Traverse a list in the forward direction.
 *
 * @param list A pointer to the list
 * @param cur The variable to use as an iterator
 */
#define list_for_each(list, cur)                                        \
    for (cur = (list)->head; cur != NULL; cur = (cur)->next)

/**
 * Traverse a list in the backwards direction.
 *
 * @param list A pointer to the list
 * @param cur The variable to use as an iterator
 */
#define list_for_each_reverse(list, cur)                                \
    for (cur = (list)->tail; cur != NULL; cur = (cur)->prev)

/**
 * Traverse a list's entries in the forward direction.
 *
 * @param type The type of each list entry
 * @param member The member of each entry containing the list's nodes
 * @param list A pointer to the list
 * @param cur The variable to use as an iterator
 */
#define list_for_each_entry(type, member, list, cur)                    \
    for (cur = list_entry(type, member, (list)->head);                  \
         cur != NULL;                                                   \
         cur = list_entry(type, member, (cur)->member.next))

/**
 * Traverse a list's entries in the backwards direction.
 *
 * @param type The type of each list entry
 * @param member The member of each entry containing the list's nodes
 * @param list A pointer to the list
 * @param cur The variable to use as an iterator
 */
#define list_for_each_entry_reverse(type, member, list, cur)            \
    for (cur = list_entry(type, member, (list)->tail);                  \
         cur != NULL;                                                   \
         cur = list_entry(type, member, (cur)->member.prev))

/**
 * Safely traverse a list in the forward direction using a temporary.
 *
 * @param list A pointer to the list
 * @param n Temporary variable
 * @param cur The variable to use as an iterator
 */
#define list_for_each_safe(list, n, cur)                                \
    for (cur = (list)->head, n = cur ? cur->next : NULL;                \
         cur != NULL;                                                   \
         cur = n, n = cur ? (cur)->next : NULL)

/**
 * Safely traverse a list in the backwards direction using a temporary.
 *
 * @param list A pointer to the list
 * @param n Temporary variable
 * @param cur The variable to use as an iterator
 */
#define list_for_each_safe_reverse(list, n, cur)                        \
    for (cur = (list)->tail, n = cur ? cur->prev : NULL;                \
         cur != NULL;                                                   \
         cur = n, n = cur ? (cur)->prev : NULL)

/**
 * Safely traverse a list's entries in the forward direction using a temporary.
 *
 * @param type The type of each list entry
 * @param member The member of each entry containing the list's nodes
 * @param list A pointer to the list
 * @param n Temporary variable
 * @param cur The variable to use as an iterator
 */
#define list_for_each_entry_safe(type, member, list, n, cur)            \
    for (cur = list_entry(type, member, (list)->head),                  \
         n = cur ? list_entry(type, member, (cur)->member.next) : NULL; \
         cur != NULL;                                                   \
         cur = n,                                                       \
         n = cur ? list_entry(type, member, (cur)->member.next) : NULL)

/**
 * Safely traverse a list's entries in the backwards direction using a
 * temporary.
 *
 * @param type the type of each list entry
 * @param member the member of each entry containing the list's nodes
 * @param list a pointer to the list
 * @param n Temporary variable
 * @param cur The variable to use as an iterator
 */
#define list_for_each_entry_safe_reverse(type, member, list, n, cur)    \
    for (cur = list_entry(type, member, (list)->tail),                  \
         n = cur ? list_entry(type, member, (cur)->member.prev) : NULL; \
         cur != NULL;                                                   \
         cur = n,                                                       \
         n = cur ? list_entry(type, member, (cur)->member.prev) : NULL)

/**
 * Get the length of a list.
 *
 * @param list The list
 * @return The length of the list
 */
static inline unsigned int
list_length(struct list *list)
{
    unsigned int ret = 0;
    struct list_node *cur;

    list_for_each(list, cur)
        ret++;

    return ret;
}

/**
 * Insert a new node before a specific node.
 *
 * @param list The list
 * @param succ The node to insert before
 * @param toadd The node to add
 */
static inline void
list_insert_before(struct list *list, struct list_node *succ,
        struct list_node *toadd)
{
    if (toadd == NULL)
        return;

    toadd->next = toadd->prev = NULL;
    if (list->head == NULL && list->tail == NULL) {
        // Singleton list
        list->head = list->tail = toadd;
    } else if (succ == NULL) {
        // Insert at tail
        toadd->prev = list->tail;
        list->tail->next = toadd;
        toadd->next = NULL;
        list->tail = toadd;
    } else if (succ == list->head) {
        // Insert at head
        toadd->next = list->head;
        list->head->prev = toadd;
        toadd->prev = NULL;
        list->head = toadd;
    } else {
        // General case
        toadd->prev = succ->prev;
        toadd->next = succ;
        succ->prev->next = toadd;
        succ->prev = toadd;
    }
}

/**
 * Insert a new entry before a specific entry.
 *
 * @param type The type of the list entry
 * @param member The member of each entry containing the list's nodes
 * @param list A pointer to the list
 * @param succ The entry to insert before
 * @param toadd The entry to add
 */
#define list_insert_entry_before(type, member, list, succ, toadd)       \
    list_insert_before(list, succ ? &((type *)(succ))->member : NULL,   \
            &(toadd)->member)

/**
 * Insert a new node after a specific node.
 *
 * @param list The list
 * @param pred The node to insert after
 * @param toadd The node to add
 */
static inline void
list_insert_after(struct list *list, struct list_node *pred,
        struct list_node *toadd)
{
    if (pred == NULL)
        list_insert_before(list, list->head, toadd);
    else
        list_insert_before(list, pred->next, toadd);
}

/**
 * Insert a new entry after a specific entry.
 *
 * @param type The type of the list entry
 * @param member The member of each entry containing the list's nodes
 * @param list The list
 * @param pred The entry to insert after
 * @param toadd The entry to add
 */
#define list_insert_entry_after(type, member, list, pred, toadd)        \
    list_insert_after(list, pred ? &((type *)(pred))->member : NULL,    \
            &(toadd)->member)

/**
 * Insert a new node at the head of a list.
 *
 * @param list The list
 * @param toadd The node to add
 */
static inline void
list_push_front(struct list *list, struct list_node *toadd)
{
    list_insert_before(list, list->head, toadd);
}

/**
 * Insert a new entry at the head of a list.
 *
 * @param type The type of the list entry
 * @param member The member of each entry containing the list's nodes
 * @param list A pointer to the list
 * @param toadd The entry to add
 */
#define list_push_entry_front(type, member, list, toadd)                \
    list_push_front(list, &(toadd)->member)

/**
 * Insert a new node at the tail of a list.
 *
 * @param list The list
 * @param toadd The node to add
 */
static inline void
list_push_back(struct list *list, struct list_node *toadd)
{
    list_insert_after(list, list->tail, toadd);
}

/**
 * Insert a new entry at the tail of a list.
 *
 * @param type The type of the list entry
 * @param member The member of each entry containing the list's nodes
 * @param list A pointer to the list
 * @param toadd The entry to add
 */
#define list_push_entry_back(type, member, list, toadd)                 \
    list_push_back(list, &(toadd)->member)

/**
 * Insert a new node in order as specified by a comparison function.
 *
 * @param list The list
 * @param toadd The node to add
 * @param cmp The comparison function
 */
static inline void
list_insert_in_order(struct list *list, struct list_node *toadd,
        int (*cmp)(const struct list_node *, const struct list_node *))
{
    struct list_node *cur;
    list_for_each(list, cur)
        if (cmp(toadd, cur) >= 0) {
            list_insert_before(list, cur, toadd);
            return;
        }

    list_push_back(list, toadd);
}

/**
 * Insert a new entry in order as specified by a comparison function.
 *
 * Note: the comparision function still operates on struct list_nodes.
 *
 * @param type The type of each list entry
 * @param member The member of each entry containing the list's nodes
 * @param list A pointer to the list
 * @param toadd The entry to add
 * @param cmp The comparison function
 */
#define list_insert_entry_in_order(type, member, list, toadd, cmp)      \
    list_insert_in_order(list, &(toadd)->member, cmp)

/**
 * Find a node in the list based on a predicate function.
 *
 * @param list The list
 * @param pred The predicate function
 * @param data Data to pass to the predicate function
 * @return The first list_node that matches from the head of the list, or NULL
 *      if not found
 */
static inline struct list_node *
list_find(const struct list *list, int (*pred)(const struct list_node *, void *),
        void *data)
{
    struct list_node *cur;
    list_for_each(list, cur)
        if (pred(cur, data))
            return cur;

    return NULL;
}

/**
 * Find an entry in the list based on a predicate function.
 *
 * Note: the predicate function still operates on struct list_nodes.
 *
 * @param type The type of each list entry
 * @param member The member of each entry containing the list's nodes
 * @param list A pointer to the list
 * @param pred The predicate function
 * @param data Data to pass to the predicate function
 * @return The first entry that matches from the head of the list, or NULL if
 *      not found
 */
#define list_find_entry(type, member, list, pred, data)                 \
    list_entry(type, member, list_find(list, pred, data))

/**
 * Remove a node from a list.
 *
 * @param list The list
 * @param torem The node to remove
 */
static inline void
list_remove(struct list *list, struct list_node *torem)
{
    if (torem == NULL)
        return;

    if (torem->prev == NULL)
        list->head = torem->next;
    else
        torem->prev->next = torem->next;

    if (torem->next == NULL)
        list->tail = torem->prev;
    else
        torem->next->prev = torem->prev;
}

/**
 * Remove an entry from a list.
 *
 * @param type The type of each list entry
 * @param member The member of each entry containing the list's nodes
 * @param list A pointer to the list
 * @param torem The entry to remove
 */
#define list_remove_entry(type, member, list, torem) ({                 \
    type *__torem = (torem);                                            \
    list_remove(list, __torem ? &__torem->member : NULL);               \
})

/**
 * Remove and return the node at the head of the list.
 *
 * @param list The list
 * @return The node at the head of the list
 */
static inline struct list_node *
list_pop_front(struct list *list)
{
    struct list_node *ret = list->head;
    list_remove(list, ret);
    return ret;
}

/**
 * Remove and return the entry at the head of the list.
 *
 * @param type The type of each list entry
 * @param member The member of each entry containing the list's nodes
 * @param list A pointer to the list
 * @return The entry at the head of the list
 */
#define list_pop_entry_front(type, member, list)                        \
    list_entry(type, member, list_pop_front(list))

/**
 * Remove and return the node at the tail of the list.
 *
 * @param list The list
 * @return The node at the tail of the list
 */
static inline struct list_node *
list_pop_back(struct list *list)
{
    struct list_node *ret = list->tail;
    list_remove(list, ret);
    return ret;
}

/**
 * Remove and return the entry at the tail of the list.
 *
 * @param type The type of each list entry
 * @param member The member of each entry containing the list's nodes
 * @param list A pointer to the list
 * @return The entry at the tail of the list
 */
#define list_pop_entry_back(type, member, list)                         \
    list_entry(type, member, list_pop_back(list))

#endif /* LIST_H_ */
