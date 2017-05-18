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


struct node *cgc_list_create_node(void *data) {

	struct node *np = cgc_malloc(sizeof(struct node));
	if (NULL == np) {
		return np;
	}
	np->data = data;
	np->next = 0;
	np->prev = 0;
	return np;
}

void cgc_list_destroy_node(struct list *l, struct node **n) {

	// destroy node->data
	if (NULL != l->ndf) {
		l->ndf((*n)->data);
	}
	(*n)->data = NULL;
	(*n)->next = NULL;
	(*n)->prev = NULL;

	// destroy node
	cgc_free(*n);
	*n = NULL;
}

void cgc_list_init(struct list *l, nodeDataFreeFn ndf) {
	l->length = 0;
	l->dummy.data = NULL;
	l->dummy.next = &(l->dummy);
	l->dummy.prev = &(l->dummy);
	l->ndf = ndf;
}

void cgc_list_destroy(struct list *l) {
	if ((NULL != l) && (0 < cgc_list_length(l))) {
		while (NULL != cgc_list_head_node(l)) {
			struct node *h = cgc_list_pop(l);
			cgc_list_destroy_node(l, &h);
		}
	}
	l->dummy.next = &(l->dummy);
	l->dummy.prev = &(l->dummy);
}

void cgc_list_insert_node_at_end(struct list *l, struct node *new) {
	if ((NULL != l) && (NULL != new)) {
		struct node *t = cgc_list_tail_node(l);

		new->next = &(l->dummy);
		new->prev = l->dummy.prev;

		l->dummy.prev = new;

		if (NULL == t) {
			l->dummy.next = new;
		} else {
			t->next = new;
		}

		l->length++;
	}
}

void cgc_list_insert_at_end(struct list *l, void *d) {
	if (NULL != l) {
		struct node *new = cgc_list_create_node(d);
		cgc_list_insert_node_at_end(l, new);
	}
}

void cgc_list_insert_node_at_start(struct list *l, struct node *new) {
	if ((NULL != l) && (NULL != new)) {
		struct node *h = cgc_list_head_node(l);

		new->prev = &(l->dummy);
		new->next = l->dummy.next;

		l->dummy.next = new;

		if (NULL == h) {
			l->dummy.prev = new;
		} else {
			h->prev = new;
		}

		l->length++;
	}
}

void cgc_list_insert_at_start(struct list *l, void *d) {
	if (NULL != l) {
		struct node *new = cgc_list_create_node(d);
		cgc_list_insert_node_at_start(l, new);
	}
}

struct node *cgc_list_pop(struct list *l) {
	if (NULL == l) {
		return NULL;
	}

	struct node *h = cgc_list_head_node(l);
	cgc_list_remove_node(l, h);
	return h;
}

void cgc_list_remove_node(struct list *l, struct node *n) {
	if ((NULL != n) && (0 < l->length)) {
		struct node *prev = n->prev;
		struct node *next = n->next;
		prev->next = next;
		next->prev = prev;

		n->prev = NULL;
		n->next = NULL;
		l->length--;
	}
}

struct node *cgc_list_head_node(struct list *l) {
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

unsigned int cgc_list_length(struct list *l) {
	return l->length;
}

struct node *cgc_list_find_node_with_data(struct list *l, unsigned char (*predFn)(const void *, void *), void *data) {

	if ((NULL != l) && (NULL != data)) {
		struct node *n = cgc_list_head_node(l);
		for (unsigned int i = 0; i < l->length; i++) {
			if (TRUE == predFn((const void *)n->data, data)) {
				return n;
			} else {
				n = n->next;
			}
		}
	}

	return NULL;
}

