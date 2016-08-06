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

#include <libcgc.h>
#include "bst.h"
#include "malloc.h"
#include "stdlib.h"
#include "service.h"

    
int insert_node(bst_node_type **head, data_item_type *data, unsigned long make_key()) {

bst_node_type *tmp_node;
unsigned long key_val=0;
data_item_type *next_ptr;
	

	// if no data was passed in, return error
	if (data==0)
		return(-1);


	// make sure the tree already exists
	if (!*head) {

		*head=(bst_node_type *)calloc(1, sizeof(bst_node_type));

		// memory allocation failed
		if (!*head) {

			return(-1);
		}

		// it does exist now, so just stick our data in it since no searching necessary
		key_val=make_key(data);

		if (key_val > 0) {

			(*head)->data=data;
			(*head)->data_count = 1;
			(*head)->key=key_val;
			return(0);
		}
		else {

			return(-1);
		}


	}  // if (!head)


	key_val=make_key(data);


	tmp_node=*head;


	while (1) {

		if (key_val < tmp_node->key) {

			if (tmp_node->left != 0) {

				tmp_node=tmp_node->left;
			}
			else {

				tmp_node->left=(bst_node_type *)calloc(1, sizeof(bst_node_type));

				if (!tmp_node->left) {
					return(-1);
				}

				tmp_node->left->data=data;
				tmp_node->left->data_count=1;
				tmp_node->left->key=key_val;
				return(0);
			}
		}
			
		else if (key_val > tmp_node->key) {


			if (tmp_node->right !=0) {

				tmp_node=tmp_node->right;
			}
			else {

				tmp_node->right=(bst_node_type *)calloc(1, sizeof(bst_node_type));

				if (!tmp_node->right) {
					return(-1);
				}

				tmp_node->right->data=data;
				tmp_node->right->data_count=1;
				tmp_node->right->key=key_val;
				return(0);
			}

		}
		// should only happen if the keys are equal
		else   {  
		
			// if the strings don't match, its a key collision
			if (strcmp(tmp_node->data->name, data->name)!=0) {

				// so move to the end of the linked list and add the new data
				next_ptr=tmp_node->data;

				while (next_ptr->next != 0)
					next_ptr=next_ptr->next;

				next_ptr->next = data;

				// increment the count of the number in this linked list
				tmp_node->data_count++;


			}
			return(0);

		}
			
	}


}  // insert_node()



int delete_node(bst_node_type **head, char *str, unsigned long key) {

bst_node_type *tmp_node, *promote_node, *previous_node;
data_item_type *prev_ptr, *next_ptr;

	if (!*head) {

		return(0);
	}

	// first locate the node
	tmp_node=*head;

	while(tmp_node->key != key) {

		previous_node=tmp_node;

		if (key < tmp_node->key) {

			tmp_node=tmp_node->left;
		}
		else {

			tmp_node=tmp_node->right;
		}

		// didn't find the key, just return
		if (tmp_node==0) {

			return(0);
		}

	}

	// a new special case since this implementation allows for multiple values stored for the same key
	// if there is more than one data element in the matching node, the node won't get deleted
	if (tmp_node->data_count > 1) {

		prev_ptr=tmp_node->data;
		next_ptr=prev_ptr->next;

		// check the first entry because if its the match we need to update the pointer stored in the BST node
		if (strcmp(tmp_node->data->name, str)==0) {

			free(prev_ptr);
			tmp_node->data=next_ptr;
			tmp_node->data_count--;
			return (0);

		}

		// otherwise, cycle through the remainder of the linked list looking for a match
		while (next_ptr!= 0) {

			//	printf("looking for appended element\n");
			if (strcmp(next_ptr->name, str)==0) {

				prev_ptr->next = next_ptr->next;
				tmp_node->data_count--;

#ifdef PATCHED
#else				
				next_ptr=next_ptr->next;
#endif
				free(next_ptr);

				break;
			}
			else {

				prev_ptr=next_ptr;
				next_ptr=next_ptr->next;

			}

		}

		return(0);
	}

	// if the node has no children, delete it
	if (tmp_node->left == 0 && tmp_node->right == 0) {

		//printf("only one child node on this delete\n");
		if (tmp_node==*head) {

			free((*head)->data);
			free(*head);
			*head=0;
			return 0;
		}

		if (previous_node->key > key) 
			previous_node->left=0;

		else
			previous_node->right=0;

		free(tmp_node->data);
		free(tmp_node);
	}

	// if the node has two children, promote its in-order predecessor and then delete the old node.
	else if (tmp_node->left != 0 && tmp_node->right !=0 ) {

		// first find the node to be promoted.  Go left in the tree, and then all the way right.
		previous_node=tmp_node;
		promote_node=tmp_node->left;

		while (promote_node->right != 0) {
			previous_node=promote_node;
			promote_node=promote_node->right;
		}

		// Now delete the data from the node to be deleted  and move the promote node's data there
		free(tmp_node->data);
		tmp_node->data=promote_node->data;
		

		// now delete the old location of the promote node
		if (promote_node->key > previous_node->key) {

			previous_node->right=promote_node->left;

		}
		else {
			previous_node->left=promote_node->left;

		}

		tmp_node->key=promote_node->key;
		tmp_node->data_count=promote_node->data_count;
		free(promote_node);


	}
	// if the node has one child, promote that child
	else {


		if (tmp_node==*head) {

			free((*head)->data);

			if (tmp_node->left !=0)
				*head=(*head)->left;
			else
				*head=(*head)->right;

			free(tmp_node);

			return 0;
		}


		if (tmp_node->left != 0) 
			promote_node=tmp_node->left;
		else
			promote_node=tmp_node->right;

		if (previous_node->key > key) 
			previous_node->left=promote_node;

		else
			previous_node->right=promote_node;

		free(tmp_node->data);
		free(tmp_node);	

	}

return(0);


} // delete_node()

void *find_node_by_key(bst_node_type *head, unsigned long key) {

bst_node_type *tmp_node;


	if (!head) {

		return(0);
	}

	tmp_node=head;

	while(tmp_node->key != key) {

		if (key < tmp_node->key) {

			tmp_node=tmp_node->left;
		}
		else {

			tmp_node=tmp_node->right;
		}

		// key not found, return 0
		if (tmp_node==0) {

			return(0);
		}

	}

	// otherwise, return the address of the node
	return(tmp_node->data);


} // find_node()



int walk_tree(bst_node_type *node) {
data_item_type *tmp_ptr;

	if (node==0)
		return 0;

	// recursively walk the tree and print out the data from each node
	// classically called in-order traversal

	// first go left
	if (node->left != 0)
		walk_tree(node->left);

	// now process this node
	// since this can now be a linked list of data, set a pointer to the head
	tmp_ptr=node->data;

	// walk the linked list
	while (tmp_ptr!= 0) {
		printf("@s\n", tmp_ptr->name);
		tmp_ptr=tmp_ptr->next;
	}

	// now walk the right side of the node
	if (node->right !=0)
		walk_tree(node->right);

	return(0);

} // walk_tree()


// this is used to make a key for the BST based on the input string
unsigned long make_key_from_name(void *data_item) {

unsigned long key_val;
char *tmp;


	key_val = 0;

	tmp=((data_item_type *)data_item)->name;

	key_val=str_token(tmp);

	return(key_val);

}

// count the nodes in the tree, noting how many are in the left vs right of the tree
int count_bst_stats(bst_node_type *head, bst_stats_type *stats) {

	unsigned int total_node_count;
	unsigned int left_node_count;
	unsigned int right_node_count;
	unsigned int percent_left;
	unsigned int percent_right;

	bst_stats_type left_stats, right_stats;

	if (head == 0 || stats == 0)
		return -1;

	stats->node_count = 0;
	left_stats.node_count = 0;
	right_stats.node_count = 0;

	// first count the left side of the tree
	if (head->left != 0) {

		count_nodes(head->left, & left_stats);
	}

	left_node_count= left_stats.node_count;


	// then count the right side
	if (head->right != 0) {

		count_nodes(head->right, &right_stats);
	}

	right_node_count= right_stats.node_count;

	total_node_count = left_node_count + right_node_count;

	// include the head node in the total count if there's data
	if (head->data)
		total_node_count++;

	stats->node_count = total_node_count;


	// if there are less than 2 nodes, there can't be any in the left or right subtrees.
	if (total_node_count < 2) {

		stats->percent_left = 0;
		stats->percent_right = 0;
	}
	else { 
		// but don't include it when calculating the balance of the tree so sub 1
		stats->percent_left = left_node_count * 100 / (total_node_count - 1);
		stats->percent_right = right_node_count * 100 / (total_node_count - 1);
	}


return 0;

}

 
 // recursive function to count the number of nodes in the tree
int count_nodes(bst_node_type *node, bst_stats_type *stats) {


	if (node->left != 0) {

		count_nodes(node->left, stats);
	}

	stats->node_count++;


	if (node->right != 0) {

		count_nodes(node->right, stats);
	}

	return 0;

}

