/*

Author: Steve Wood <swood@cromulence.co>

Copyright (c) 2014 Cromulence LLC

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

#ifndef BST_H
#define BST_H

typedef struct data_item {

	char name[1024];  // 1023 byte string plus trailing null
	struct data_item *next;

}  data_item_type;


typedef struct bst_node {

	data_item_type *data;
	unsigned long key;
	unsigned int data_count;
	struct bst_node *right;
	struct bst_node *left;

} bst_node_type;


typedef struct bst_stats {

	unsigned int node_count;
	unsigned int percent_left;
	unsigned int percent_right;


} bst_stats_type;


unsigned long str_token( char *str);
unsigned long make_key_from_name(void *data_item);

int insert_node(bst_node_type **head, data_item_type *data, unsigned long make_key());
int delete_node(bst_node_type **head, char *str, unsigned long key);
void *find_node_by_key(bst_node_type *head, unsigned long key); 
int walk_tree(bst_node_type *node);
int count_nodes(bst_node_type *node, bst_stats_type *stats);
int count_bst_stats(bst_node_type *head, bst_stats_type *stats);

#endif
