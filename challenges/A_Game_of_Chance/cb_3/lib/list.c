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
#include "libcgc.h"
#include "cgc_stdint.h"
#include "cgc_list.h"
#include "cgc_malloc.h"
#include "cgc_memset.h"

struct node *list_create_node(void *data) {

	struct node *np = malloc(sizeof(struct node));
	if (NULL == np) {
		return np;
	}
	np->data = data;
	np->next = 0;
	np->prev = 0;
	return np;
}

void list_destroy_node(struct list *l, struct node **n) {

	// destroy node->data
	if (NULL != l->ndf) {
		l->ndf((*n)->data);
	}
	(*n)->data = NULL;
	(*n)->next = NULL;
	(*n)->prev = NULL;

	// destroy node
	free(*n);
	*n = NULL;
}

void list_init(struct list *l, nodeDataFreeFn ndf) {
	l->length = 0;
	l->dummy.data = NULL;
	l->dummy.next = &(l->dummy);
	l->dummy.prev = &(l->dummy);
	l->ndf = ndf;
}

void list_destroy(struct list *l) {
	while (NULL != list_head_node(l)) {
		struct node *h = list_pop(l);
		list_destroy_node(l, &h);
	}
	l->length = 0;
	l->dummy.next = NULL;
	l->dummy.prev = NULL;
	l->ndf = NULL;
}

void list_insert_before_node(struct node *existing, struct node *new) {
	new->next = existing;
	new->prev = existing->prev;

	new->prev->next = new;
	new->next->prev = new;
}

void list_insert_after_node(struct node *existing, struct node *new) {
	list_insert_before_node(existing->next, new);
}

void list_insert_node_at_end(struct list *l, struct node *new) {
	struct node *t = list_end_marker(l);
	list_insert_before_node(t, new);

	l->length++;
}

void list_insert_at_end(struct list *l, void *d) {
	struct node *new = list_create_node(d);
	list_insert_node_at_end(l, new);
}

void list_insert_node_at_start(struct list *l, struct node *new) {
	struct node *t = list_start_marker(l);
	list_insert_after_node(t, new);

	l->length++;
}

void list_insert_at_start(struct list *l, void *d) {
	struct node *new = list_create_node(d);
	list_insert_node_at_start(l, new);
}

void cgc_list_insert_node_sorted(struct list *l, struct node *new, unsigned char (*predFn)(const void *, void *), unsigned char desc) {
	struct node *cur = NULL;

	if (0 == l->length) {
		list_insert_node_at_start(l, new);
	} else {
		cur = list_head_node(l);
		while ((cur != list_end_marker(l)) && (desc != predFn(new->data, cur->data))) {
			cur = list_next_node(cur);
		}
		list_insert_before_node(cur, new);
		l->length++;
	}
}

void list_insert_sorted(struct list *l, void *d, unsigned char (*predFn)(const void *, void *), unsigned char desc) {
	struct node *new = list_create_node(d);
	cgc_list_insert_node_sorted(l, new, predFn, desc);
}

struct node *list_pop(struct list *l) {
	struct node *h = list_head_node(l);
	if (NULL == h) return h;

	list_remove_node(l, h);
	return h;
}

void list_remove_node(struct list *l, struct node *n) {
	struct node *prev = n->prev;
	struct node *next = n->next;
	prev->next = next;
	next->prev = prev;

	n->prev = NULL;
	n->next = NULL;
	l->length--;
}

struct node *list_head_node(struct list *l) {
	if (&(l->dummy) == l->dummy.next) {
		return NULL;
	}
	return l->dummy.next;
}

struct node *cgc_list_tail_node(struct list *l) {
	if (&(l->dummy) == l->dummy.prev) {
		return NULL;
	}
	return l->dummy.prev;
}

struct node *list_next_node(struct node *cur_node) {
	return cur_node->next;
}

struct node *list_start_marker(struct list *l) {
	return list_end_marker(l);
}

struct node *list_end_marker(struct list *l) {
	return &(l->dummy);
}

unsigned int cgc_list_length(struct list *l) {
	return l->length;
}

struct node *cgc_list_find_node_with_data(struct list *l, unsigned char (*predFn)(const void *, void *), void *data) {
	struct node *n = list_head_node(l);
	struct node *end = list_end_marker(l);
	while ((NULL != n) && (n != end)) {
		if (TRUE == predFn((const void *)n->data, data)) {
			return n;
		} else {
			n = n->next;
		}
	}
	return NULL;
}

