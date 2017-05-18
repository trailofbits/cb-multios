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

#ifndef LIST_H
#define LIST_H 1

/**
 * Doubly-linked list
 *
 * This linked list has an empty head node in the initial list.
 * 
 * The list stores a count of the nodes it contains in 'length'
 */

/**
 * Pointer to function to free the data element of a node.
 *
 * @param data Data element of a struct node
 */
typedef void (*nodeDataFreeFn)(void *);

struct node {
	void *data;
	struct node *next;
	struct node *prev;
};

struct list {
	unsigned int length;
	struct node dummy;
	nodeDataFreeFn ndf;
};

/**
 * Create a node and assign its data element.
 *
 * @param data Data element
 * @return VA of new node, or NULL on error
 */
struct node *cgc_list_create_node(void *data);

/**
 * Destroy the node and its data element. 
 *  If node is still in the list, remove from list first.
 *
 * @param l List containing node n
 * @param n Node to destory
 */
void cgc_list_destroy_node(struct list *l, struct node **n);

/**
 * Allocate a new list
 *
 * @param l List
 * @param ndf Node data free'ing function
 */
void cgc_list_init(struct list *l, nodeDataFreeFn ndf);

/**
 * Destroy a list
 *
 * @param l List
 */
void cgc_list_destroy(struct list *l);

/**
 * Insert new node at end of list.
 *
 * @param l List
 * @param d Pointer to data to insert into new node
 */
void cgc_list_insert_node_at_end(struct list *l, struct node *new);

/**
 * Insert data element into a new node at end of list.
 *
 * @param l List
 * @param d Pointer to data to insert into new node
 */
void cgc_list_insert_at_end(struct list *l, void *d);

/**
 * Insert new node at start of list
 *
 * @param l List
 * @param d Pointer to data to insert into new node
 */
void cgc_list_insert_node_at_start(struct list *l, struct node *new);

/**
 * Insert data element into a new node at start of list
 *
 * @param l List
 * @param d Pointer to data to insert into new node
 */
void cgc_list_insert_at_start(struct list *l, void *d);

/**
 * Remove the first node from the start of list.
 *
 * @param l List
 * @return VA of node or NULL of empty list
 */
struct node *cgc_list_pop(struct list *l);

/**
 * Remove node from list
 *
 * @param l Pointer to list
 * @param n Node to remove from list
 */
void cgc_list_remove_node(struct list *l, struct node *n);

/**
 * Get head node of list
 *
 * @param l Pointer to list
 * @return VA of head node or NULL if empty
 */
struct node *cgc_list_head_node(struct list *l);

/**
 * Get tail node of list
 *
 * @param l Pointer to list
 * @return VA of tail node or NULL if empty
 */
struct node *cgc_list_tail_node(struct list *l);

/**
 * Get length of list
 *
 * @param l List
 * @return Length of list
 */
unsigned int cgc_list_length(struct list *l);

/**
 * Find the node in the list that contains the given data
 *
 * @param l List
 * @param pred Predicate function
 * @param data Pointer to data element to pass into predicate fn
 * @return VA of node or NULL if not found
 */
struct node *cgc_list_find_node_with_data(struct list *l, unsigned char (*predFn)(const void *, void *), void *data);


#endif
