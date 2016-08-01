/*

Author: Dustin Fraze <df@cromulence.co>

Copyright (c) 2015 Cromulence LLC

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

#include "trie.h"

#include <libcgc.h>
#include "stdlib.h"

trie * initTrie() {
	trie *ret;
	ret = calloc(sizeof(trie), 1);
	return ret;
}

void insertInTrie(trie *root, char *key,  void* value) {
	int i;
	trie *ptr;

	ptr = root;
	if(ptr->children == NULL) {
		ptr->children = calloc(sizeof(trie), 1);
		ptr->children->tag = key[0];
	}

	ptr = ptr->children;

	for(i=0;i<=strlen(key);i++) {
		while(ptr->next != NULL) {
			if(ptr->tag == key[i]) {
				break;
			} else {
				ptr = ptr->next;
			}
		}
		if(ptr->tag == key[i])
		{
			if (key[i] == 0)
  				break;
			if(ptr->children == NULL) {
				ptr->children = calloc(sizeof(trie), 1);
				ptr->children->tag = key[i+1];
			}
			ptr = ptr->children;
		} else {
			ptr->next = calloc(sizeof(trie), 1);
			ptr->next->tag = key[i];
			ptr = ptr->next;
			while(i<strlen(key)) {
				ptr->children = calloc(sizeof(trie), 1);
				ptr->children->tag = key[++i];
				ptr = ptr->children;
			}
			break;
		}
	}

	ptr->value = value;
}

trie * findInTrie(trie *root, char * key) {
	trie *ptr;
	trie *current;
	trie *ret = NULL;
	int i = 0;

	current = root;

	if(current->children != NULL) {
		current = current->children;
	} else {
		return NULL;
	}

	while(1) {
		for(ptr = current; ptr != NULL; ptr = ptr->next) {
			if(ptr->tag == key[i]) {
				ret = ptr;
				break;
			}
		}
		if(ret == NULL)
			return ptr;

		if(key[i] == 0) {
			if(ret->value == NULL)
				return NULL;
			return ret;
		}

		if(ptr != NULL)
			current = ptr->children;
		else
			return NULL;
		i++;
	}
	return ret;
}
