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

#include "cgc_errno.h"
#include "cgc_stdint.h"
#include "cgc_bst.h"
#include "cgc_malloc.h"
#include "cgc_memset.h"


bst_node_t *cgc_bst_create_node(int key) {

	bst_node_t *np = cgc_malloc(sizeof(bst_node_t));
	if (NULL == np) {
		cgc__terminate(ERRNO_ALLOC);
	}
	np->key = key;
	np->data = NULL;
	np->parent = NULL_NODE;
	np->left = NULL_NODE;
	np->right = NULL_NODE;
	return np;
}

void cgc_bst_delete_node(bst_node_t **node) {
	cgc_memset(*node, '\0', sizeof(bst_node_t));
	cgc_free(*node);
}

void cgc_bst_init(bst_t *bst) {
	bst->root = NULL_NODE;
	bst->count = 0;
	bst->iter_node = NULL_NODE;
	bst->iter_asc = TRUE;
}

bst_node_t *cgc_bst_search(bst_t *bst, int key) {
	bst_node_t *node = bst->root;
	while ((node != NULL_NODE) && (node->key != key)) {
		if (key < node->key) {
			node = node->left;
		} else {
			node = node->right;
		}
	}

	return node;
}

bst_node_t *cgc_bst_max_node_subtree(bst_node_t *node) {
	while ((NULL_NODE != node) && (NULL_NODE != node->right)) node = node->right;

	return node;
}

int cgc_bst_max_subtree(bst_node_t *node) {
	return cgc_bst_max_node_subtree(node)->key;
}

bst_node_t *cgc_bst_max_node(bst_t *bst) {
	bst_node_t *node = bst->root;
	return cgc_bst_max_node_subtree(node);
}

int cgc_bst_max(bst_t *bst) {
	bst_node_t *node = bst->root;
	return cgc_bst_max_subtree(node);
}

bst_node_t *cgc_bst_min_node_subtree(bst_node_t *node) {
	while ((NULL_NODE != node) && (NULL_NODE != node->left)) node = node->left;

	return node;
}

int cgc_bst_min_subtree(bst_node_t *node) {
	return cgc_bst_min_node_subtree(node)->key;
}

bst_node_t *cgc_bst_min_node(bst_t *bst) {
	return cgc_bst_min_node_subtree(bst->root);
}

int cgc_bst_min(bst_t *bst) {
	return cgc_bst_min_subtree(bst->root);
}

bst_node_t *cgc_bst_predecessor(bst_node_t *node) {
	if (NULL_NODE != node->left) {
		return cgc_bst_max_node_subtree(node->left);
	}
	bst_node_t *n_child = node;
	bst_node_t *n_parent = node->parent;
	while ((n_parent != NULL_NODE) && (n_child == n_parent->left)) {
		n_child = n_parent;
		n_parent = n_parent->parent;
	}

	return n_parent;
}

bst_node_t *cgc_bst_successor(bst_node_t *node) {
	if (NULL_NODE != node->right) {
		return cgc_bst_min_node_subtree(node->right);
	}
	bst_node_t *n_child = node;
	bst_node_t *n_parent = node->parent;
	while ((n_parent != NULL_NODE) && (n_child == n_parent->right)) {
		n_child = n_parent;
		n_parent = n_parent->parent;
	}

	return n_parent;
}

bst_node_t *cgc_bst_iter_start(bst_t *bst, unsigned char ascending) {
	bst->iter_asc = ascending;
	bst_node_t *n;
	if (TRUE == bst->iter_asc) {
		bst->iter_node = cgc_bst_min_node(bst);
	} else {
		bst->iter_node = cgc_bst_max_node(bst);
	}
	return bst->iter_node;
}

bst_node_t *cgc_bst_iter_next(bst_t *bst) {
	if (TRUE == bst->iter_asc) {
		bst->iter_node = cgc_bst_successor(bst->iter_node);
	} else {
		bst->iter_node = cgc_bst_predecessor(bst->iter_node);
	}
	return bst->iter_node;
}

int cgc_bst_iter_end(bst_t *bst) {
	return NULL_NODE == bst->iter_node;
}

void cgc_bst_insert_node(bst_t *bst, bst_node_t *node) {
	bst_node_t *n_parent = bst->root;
	bst_node_t *n_child = bst->root;

	while (n_child != NULL_NODE) {
		n_parent = n_child;
		if (node->key < n_child->key) {
			n_child = n_child->left;
		} else {
			n_child = n_child->right;
		}
	}

	node->parent = n_parent;
	if (NULL_NODE == n_parent) {
		bst->root = node;
	} else if (node->key < n_parent->key) {
		n_parent->left = node;
	} else {
		n_parent->right = node;
	}

	bst->count++;
}

void cgc_bst_insert(bst_t *bst, int key) {
	bst_node_t *n = cgc_bst_create_node(key);
	cgc_bst_insert_node(bst, n);
}

bst_node_t *cgc_bst_remove_node(bst_t *bst, bst_node_t *node) {
	bst_node_t *n_splice;
	bst_node_t *n_child;
	if ((NULL_NODE == node->left) || (NULL_NODE == node->right)) {
		n_splice = node;
	} else {
		n_splice = cgc_bst_successor(node);
	}

	if (NULL_NODE != n_splice->left) {
		n_child = n_splice->left;
	} else {
		n_child = n_splice->right;
	}

	if (NULL_NODE != n_child) {
		n_child->parent = n_splice->parent;
	}

	if (NULL_NODE == n_splice->parent) {
		bst->root = n_child;
	} else if (n_splice == n_splice->parent->left) {
		n_splice->parent->left = n_child;
	} else {
		n_splice->parent->right = n_child;
	}

	if (n_splice != node) {
		node->key = n_splice->key;
	}


	bst->count--;

	return n_splice;
}

bst_node_t *cgc_bst_remove(bst_t *bst, int key) {
	bst_node_t *node = cgc_bst_search(bst, key);
	if (NULL_NODE == node) return node;

	return cgc_bst_remove_node(bst, node);
}

int cgc_bst_is_empty(bst_t *bst) {
	return NULL_NODE == bst->root;
}

