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

#include <libcgc.h>
#include "sheap.h"
#define DEBUG 1


#define MAX_HEADS 6
#define PG_SZ 4096
#define CHUNK_BASE 2
#define MIN_ELEMENTS 8
#define LAZY_THRESH 703842
#define OK 0
#define MAX_MEM 512000000

typedef struct HEAP_MEM {
	size_t chunk_size;
	size_t n_backing;
	size_t n_chunks;
	size_t ll_md_sz;
	size_t backing_sz;
	alloc_head_t * backing;
	alloc_head_t * inuse;
	alloc_head_t * freelist;

} HEAP_MEM_T;

typedef struct HEAP {
	HEAP_MEM_T heads[MAX_HEADS];
} HEAP_T;



static HEAP_T sheap_heap;

size_t MEM_ALLOC = 0;

alloc_node_t *alloc_backing(HEAP_MEM_T *hm){
	alloc_node_t * n;
	hm->ll_md_sz = (sizeof(alloc_node_t) + hm->chunk_size);
	size_t backing_sz =  hm->ll_md_sz * hm->n_chunks ;
	hm->backing_sz = backing_sz;
	int backing_head_r =  allocate(backing_sz, 0, (void **) &n);
	if(backing_head_r != 0)
		return NULL;

	
	return n;
}

alloc_node_t * add_backing_for_chunks(HEAP_MEM_T *hm){
	
	alloc_node_t *backing_mem = alloc_backing(hm);
	if(backing_mem == NULL)
		return NULL;

	int ret =add_node(hm->backing, backing_mem);
	// add first memory, if we exhuast then we add an new backing chunk
	assert(ret == 0);
	hm->n_backing += 1;
	return backing_mem;
}

void add_backing_chunks_to_freelist(HEAP_MEM_T *hm, alloc_node_t *backing_head){
	
	assert(backing_head != NULL);
	
	for(int i =0; i < hm->n_chunks; i++){

		size_t offset = hm->ll_md_sz *i;
		// hacky cast to get right offset
		alloc_node_t *a =  (alloc_node_t *)((void *) backing_head + offset);

		add_node(hm->freelist, a);
	}
}

int init_backing(HEAP_MEM_T *hm){

	
	hm->freelist = init_ll();
	hm->inuse = init_ll();
	hm->backing = init_ll();
	alloc_node_t *bn = add_backing_for_chunks(hm);
	if(bn == NULL)
		return ENOMEM;
	alloc_node_t *backing_head = get_head(hm->backing);
	add_backing_chunks_to_freelist(hm, backing_head);

	return 0;
}


HEAP_MEM_T * get_chunk_head_for_sz(size_t s){
	for(int i = 0; i < MAX_HEADS; i++){
		// select our chunk
		HEAP_MEM_T * current_heap_head = &(sheap_heap.heads[i]);
		size_t current_chunk_sz = current_heap_head->chunk_size;

		if(s < current_chunk_sz ){
			// lazy init of chunk head size
			if(current_heap_head->backing == NULL){

				int ret = init_backing(current_heap_head);
				if(ret != 0)
					_terminate(ret);



				assert(current_heap_head->backing != NULL);
				return current_heap_head;

			}
			else
				return current_heap_head;

		}
	}
	return NULL;
}
void * max_backing_addr(alloc_node_t *an, HEAP_MEM_T *hh){
	return ((void *) an + hh->backing_sz );
}

alloc_node_t * get_backing_with_ptr(alloc_node_t *an, HEAP_MEM_T *hh){
	alloc_node_t *bh = get_head(hh->backing);
	while(bh != NULL){
		if( ((void *) bh <= (void *) an)  && (void *)an <= max_backing_addr(an, hh)){
			return bh;
		}
		bh = bh->next;
	}
	return NULL;
}

void mod_refcount_on_backing(alloc_node_t *back_head, HEAP_MEM_T *hh, char direction){
	alloc_node_t *n = back_head;
	while(n != NULL){
		if( (void *) back_head <= (void *) n  && (void * ) n <= max_backing_addr(back_head, hh)){
			if(direction == -1)
				assert(back_head->refcount != 0);

			back_head->refcount += direction;

			return;
		}
		n = n->next;
	}

}

void * add_alloc(HEAP_MEM_T *hm, alloc_node_t *nxtmem){
	if(nxtmem == NULL)
		return NULL;
	if(remove_node(hm->freelist, nxtmem) != OK)
		return NULL;

	if(add_node(hm->inuse, nxtmem) != OK)
		return NULL;

	void * nn = (void *) nxtmem;
	void * mem = nn + sizeof(alloc_node_t);
	assert(mem-sizeof(alloc_node_t) == (void *) get_head(hm->inuse));
	return mem;
}




void * get_next_free_chunk(HEAP_MEM_T *hm){
	alloc_node_t *nxtmem = get_head(hm->freelist);

	void * a;
	if(nxtmem == NULL){
		
		alloc_node_t *new_backing = add_backing_for_chunks(hm);
		if(new_backing == NULL)
			return NULL;
		add_backing_chunks_to_freelist(hm, new_backing);
		nxtmem = get_head(hm->freelist);

		a =  add_alloc(hm, nxtmem);
		assert(a != NULL);
		assert(a-sizeof(alloc_node_t) == (void *) get_head(hm->inuse));

		return a;
	}

	 a = add_alloc(hm, nxtmem);

	 assert(a-sizeof(alloc_node_t) == (void *) get_head(hm->inuse));
	 return a;


}

void malloc_init(){
	int start = 4;
	for(int j = 0; j < MAX_HEADS; j++){
		HEAP_MEM_T *hm = &(sheap_heap.heads[j]);
		hm->chunk_size = (int) pow(CHUNK_BASE+j, j+start);
		hm->n_chunks = MIN_ELEMENTS;

		if(hm->chunk_size < LAZY_THRESH){
			int r = init_backing(hm);

			if(r != 0)
				_terminate(ENOMEM);
		}


	}
}





void * malloc(size_t s){

	HEAP_MEM_T * heap_head = get_chunk_head_for_sz(s);
	if(heap_head == NULL)
		return NULL;
	if(MEM_ALLOC + s > MAX_MEM){
		_terminate(ENOMEM);
	}
	void * r =  get_next_free_chunk(heap_head);
	if(r != NULL)
		MEM_ALLOC += heap_head->chunk_size;
	return r;

}


void free(void *pz){
	HEAP_MEM_T * current_heap_head;
	void *pp = pz - sizeof(alloc_node_t);
	int x;

	for(int i = 0; i <= MAX_HEADS; i++){
		// select our chunk
		current_heap_head = &(sheap_heap.heads[i]);

		alloc_node_t *bh =  get_head(current_heap_head->backing);
		// p should be sizeof(alloc_node_t)+alloc_node_t_p so subtract size
		
		int j = 0;
		while(bh != NULL){


			alloc_node_t *have_node = get_node(current_heap_head->inuse, (alloc_node_t *) pp);
			if(have_node != NULL){

				if(remove_node(current_heap_head->inuse, have_node) != 0){
					_terminate(15);
				}

				int r = add_node(current_heap_head->freelist, have_node);
				assert(r == 0);
				MEM_ALLOC -= current_heap_head->chunk_size;
				return;
			}
		
				

			bh = bh->next;	


		}


		
	}
	_terminate(EFAULT);


}


