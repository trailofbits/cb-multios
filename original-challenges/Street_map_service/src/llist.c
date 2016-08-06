/*

Author: James Connor (jymbo@cromulence.co)

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
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <mymath.h>
#include "service.h"
#include "llist.h"

psListNode get_last_element_s(psList thisList){
	psListNode thisNode = NULL; 
	psListNode tempNode = NULL;
	thisNode = thisList->listRoot;
	while (thisNode != NULL){
		tempNode = thisNode;
		thisNode = thisNode->next;
	}
	return tempNode;
}
//returns NULL if no elements
pdListNode get_last_element_d(pdList thisList){
	pdListNode thisNode = NULL; 
	pdListNode tempNode = NULL;
	thisNode = thisList->listRoot;
	while (thisNode != NULL){
		tempNode = thisNode;
		thisNode = thisNode->next;
	}
	return tempNode;
}

psList create_single_list(){
	psList thisList = NULL;
	if (  allocate( sizeof(sList), 0, (void**)&thisList ) !=0  ){
		puts("\n**Allocate returned an error.\n");
		_terminate(1);	
	}
	bzero(thisList, sizeof(sList));
	thisList->listRoot = NULL;
	thisList->count = 0;
	return thisList;
}


//create double linked list 
pdList create_double_list(){
	pdList thisList = NULL;
	if (  allocate( sizeof(dList), 0, (void**)&thisList ) !=0  ){
			puts("\n**Allocate returned an error.\n");
			_terminate(1);
	}
	bzero(thisList, sizeof(dList));
	thisList->listRoot = NULL;
	thisList->count = 0;
	return thisList;
}




//if prev is null, insert as first node. if prev is last append
pdListNode insert_double_list_node(pdList thisList, pdListNode prevNode){
	pdListNode newNode = NULL;


	//allocate a node
	if (  allocate( sizeof(dListNode), 0, (void**)&newNode ) != 0  ){
		puts("\n**Allocate returned an error.\n");
		_terminate(1);
		}
	bzero(newNode, sizeof(dListNode));
	//cases are 
	//1) newlist insert at listroot, new->next is null, new->prev is null, listroot is new
	//2) existing insert at listroot, new->next is listroot, new->prev is null, listroot is new, new->next->prev is new
	//3) existing insert after prevNode where prevNode is not last node, new->next is prevNode->next, new-prev is prevNode, new->prev->next is new, new->next->prev is new
	//4) existing insert after prevNode where prevNode is last node, new->prev is prevNode, new->next is NULL, new->prev->next is new 
	//case 1 & 2
	if (prevNode == NULL){
		newNode->next = thisList->listRoot;
		thisList->listRoot = newNode;
	//case 3 & 4
	} else {  
		newNode->next = prevNode->next;
	}
	//prevNode is either NULL or prevNode
	newNode->prev = prevNode;
//if there is a next node, set next->prev to new
	if (newNode->next != NULL){
		newNode->next->prev = newNode;
	}
//if there is a prev node, set prev->next to new
	if (newNode->prev != NULL){
		newNode->prev->next = newNode;
	}
	thisList->count++;
	return newNode;
}

//returns pointer to prevNode, or null if first node is deleted
pdListNode delete_double_list_node(pdList thisList, pdListNode deletedNode){
	//empty list
	pdListNode retNode = NULL;	
	if ( (deletedNode == NULL) || (thisList->count == 0) ){
		puts("**Cannot delete and empty list.");
		return NULL;
	}

	//cases are:
	//1) delete first element in 1 element list, resulting in empty list
	//		listRoot = NULL, deallocate node
	//2) delete first element in >1 element list.
	//		listRoot = deletedNode->next, deletedNode->next->prev = NULL, deallocate node 
	//3) delete nth element in list where n+1 exists
	// 		 deletedNode->prev->next = deletedNode->next, deletedNode->next->prev = deletedNode->prev, deallocate node
	//4) delete nth element in list where n is last element
	//		deletedNode->prev->next = NULL, deallocate node
	//case 1 & 2
	//deletedNode->prev == NULL
	if (deletedNode == thisList->listRoot){
		thisList->listRoot = deletedNode->next;
	//case 3 & 4
	}else {
		//not first, there must be a prev, so point it to next, which may be NULL
		deletedNode->prev->next = deletedNode->next;
	}
	// if there is a next, point it to prev, which may be NULL
	if (deletedNode->next != NULL){
		deletedNode->next->prev = deletedNode->prev;
	}

	retNode = deletedNode->prev;
	deallocate(deletedNode, sizeof(dListNode));
	thisList->count--;
	return retNode;
}


// if prevNode is NULL insert at begining, else insert after prevNode
// returns pointer to inserted node
psListNode insert_single_list_node(psList thisList, psListNode prevNode){
	psListNode newNode = NULL;
	psListNode tempNode = NULL;
	if (  allocate( sizeof(sListNode), 0, (void**)&newNode ) != 0  ){
		puts("\n**Allocate returned an error.\n");
		_terminate(1);
		}
	bzero(newNode, sizeof(sListNode));
	//cases are 
	//1) newlist insert at listroot, new->next is null, listroot is new
	//2) existing insert at listroot, new->next is listroot, listroot is new
	//3) existing insert after prevNode where prevNode is not last node, new->next is prevNode->next, prevNode->next is new
	//4) existing insert after prevNode where prevNode is last node, new->next is NULL, prev->next is new 
	//case 1 & 2	

	if (prevNode == NULL){
		newNode->next = thisList->listRoot;
		thisList->listRoot = newNode;

	//case 3 & 4
	}else{
		newNode->next = prevNode->next;
		prevNode->next = newNode;
	}
	thisList->count++;
	return newNode;
}	
