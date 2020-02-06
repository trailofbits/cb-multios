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

#ifndef BST_H
#define BST_H 1

#define NULL_NODE NULL

// NOTE: this is a Binary Search Tree that stores signed int value in each node.

struct bst_node {
	int key;
	void *data;
	struct bst_node *parent;
	struct bst_node *left;
	struct bst_node *right;
};

struct bst {
	struct bst_node *root;
	unsigned int count;
	struct bst_node *iter_node;
	unsigned char iter_asc;
};

typedef struct bst_node bst_node_t;
typedef struct bst 		bst_t;


/**
 * Create a new node containing key.
 *
 * @param key Int value to store in node
 * @return Pointer to new node.
 */
bst_node_t *cgc_bst_create_node(int key);

/**
 * Delete a node (assume node already been removed from BST)
 *
 * @param node 	Pointer to node pointer
 */
void cgc_bst_delete_node(bst_node_t **node);

/**
 * Initialize an empty binary search tree.
 *
 * @param bst 	Pointer to BST
 */
void cgc_bst_init(bst_t *bst);

/**
 * Search binary search tree for node containing key.
 *
 * @param bst 	Pointer to a Binary Search Tree
 * @param key 	Key to find in the BST
 * @return Pointer to node in BST containing key, else NULL_NODE.
 */
bst_node_t *cgc_bst_search(bst_t *bst, int key);

/**
 * Find node containing key having max value in subtree rooted at node.
 *
 * @param node 	Pointer to a Binary Search Tree node
 * @return Node with maximum key in subtree rooted at node.
 */
bst_node_t *cgc_bst_max_node_subtree(bst_node_t *node);

/**
 * Find key having max value in subtree rooted at node.
 *
 * @param node 	Pointer to a Binary Search Tree node
 * @return Maximum key in subtree rooted at node.
 */
int cgc_bst_max_subtree(bst_node_t *node);

/**
 * Find node containing key having max value.
 *
 * @param bst 	Pointer to a Binary Search Tree
 * @return Node with maximum key in bst.
 */
bst_node_t *cgc_bst_max_node(bst_t *bst);

/**
 * Find key having max value.
 *
 * @param bst 	Pointer to a Binary Search Tree
 * @return Maximum key in bst.
 */
int cgc_bst_max(bst_t *bst);

/**
 * Find node containing key having min value in subtree rooted at node.
 *
 * @param node 	Pointer to a Binary Search Tree node
 * @return Node having minimum key in subtree rooted at node.
 */
bst_node_t *cgc_bst_min_node_subtree(bst_node_t *node);

/**
 * Find key having min value in subtree rooted at node.
 *
 * @param node 	Pointer to a Binary Search Tree node
 * @return Minimum key in subtree rooted at node.
 */
int cgc_bst_min_subtree(bst_node_t *node);

/**
 * Find node containing key having min value.
 *
 * @param bst 	Pointer to a Binary Search Tree
 * @return Node with minimum key in bst.
 */
bst_node_t *cgc_bst_min_node(bst_t *bst);

/**
 * Find key having min value.
 *
 * @param bst 	Pointer to a Binary Search Tree
 * @return Minimum key in bst.
 */
int cgc_bst_min(bst_t *bst);

/**
 * Find node having key with the next lower value.
 *
 * @param node 	Pointer to a Binary Search Tree node
 * @return Pointer to node in BST containing lower key, else NULL_NODE.
 */
bst_node_t *cgc_bst_predecessor(bst_node_t *node);

/**
 * Find node having key with the next higher value.
 *
 * @param node 	Pointer to a Binary Search Tree node
 * @return Pointer to node in BST containing higher key, else NULL_NODE.
 */
bst_node_t *cgc_bst_successor(bst_node_t *node);

/**
 * Find first/last node in bst when sorted ascending or descending.
 *
 * @param bst 			Pointer to a Binary Search Tree
 * @param ascending 	TRUE if want to iterated ascending, else FALSE.
 * @return Pointer to node in BST containing highest/lowest key, else NULL_NODE if empty.
 */
bst_node_t *cgc_bst_iter_start(bst_t *bst, unsigned char ascending);

/**
 * Find next node in bst when sorted ascending or descending.
 *
 * @param bst	Pointer to a Binary Search Tree
 * @return Pointer to node in BST containing next highest/lowest key, else NULL_NODE if done.
 */
bst_node_t *cgc_bst_iter_next(bst_t *bst);

/**
 * Indicate if bst_iter has reached the end.
 *
 * @param bst	Pointer to a Binary Search Tree
 * @return TRUE if at the end, else FALSE.
 */
int cgc_bst_iter_end(bst_t *bst);

/**
 * Insert new node into binary search tree.
 *
 * @param bst 	Pointer to a Binary Search Tree
 * @param node 	Node to insert into the BST
 */
void cgc_bst_insert_node(bst_t *bst, bst_node_t *node);

/**
 * Insert new key into binary search tree.
 *
 * @param bst 	Pointer to a Binary Search Tree
 * @param key 	Key to insert into the BST
 */
void cgc_bst_insert(bst_t *bst, int key);

/**
 * Remove node from binary search tree.
 *
 * @param bst 	Pointer to a Binary Search Tree
 * @param node 	Node to remove from the BST
 * @return Pointer to removed node (caller should free this).
 */
bst_node_t *cgc_bst_remove_node(bst_t *bst, bst_node_t *node);

/**
 * Remove node with key from binary search tree.
 *
 * @param bst 	Pointer to a Binary Search Tree
 * @param key 	Key to remove from the BST
 * @return Pointer to removed node, if key is found, else NULL_NODE.
 */
bst_node_t *cgc_bst_remove(bst_t *bst, int key);


/**
 * Indicate if bst has zero nodes.
 *
 * @param bst 	Pointer to a Binary Search Tree
 * @return TRUE if empty, else FALSE.
 */
int cgc_bst_is_empty(bst_t *bst);

#endif
