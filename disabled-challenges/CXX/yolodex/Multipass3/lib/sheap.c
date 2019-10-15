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
#include "cgc_sheap.h"
#define DEBUG 1


#define MAX_HEADS 6
#define PG_SZ 4096
#define CHUNK_BASE 2
#define MIN_ELEMENTS 8
#define LAZY_THRESH 703842
#define OK 0
#define MAX_MEM 512000000

typedef struct HEAP_MEM {
	cgc_size_t chunk_size;
	cgc_size_t n_backing;
	cgc_size_t n_chunks;
	cgc_size_t ll_md_sz;
	cgc_size_t backing_sz;
	alloc_head_t * backing;
	alloc_head_t * inuse;
	alloc_head_t * freelist;

} HEAP_MEM_T;

typedef struct HEAP {
	HEAP_MEM_T heads[MAX_HEADS];
} HEAP_T;



static HEAP_T sheap_heap;

cgc_size_t cgc_MEM_ALLOC = 0;

alloc_node_t *cgc_alloc_backing(HEAP_MEM_T *hm){
	alloc_node_t * n;
	hm->ll_md_sz = (sizeof(alloc_node_t) + hm->chunk_size);
	cgc_size_t backing_sz =  hm->ll_md_sz * hm->n_chunks ;
	hm->backing_sz = backing_sz;
	int backing_head_r =  cgc_allocate(backing_sz, 0, (void **) &n);
	if(backing_head_r != 0)
		return NULL;

	
	return n;
}

alloc_node_t * cgc_add_backing_for_chunks(HEAP_MEM_T *hm){
	
	alloc_node_t *backing_mem = cgc_alloc_backing(hm);
	if(backing_mem == NULL)
		return NULL;

	int ret =cgc_add_node(hm->backing, backing_mem);
	// add first memory, if we exhuast then we add an new backing chunk
	assert(ret == 0);
	hm->n_backing += 1;
	return backing_mem;
}

void cgc_add_backing_chunks_to_freelist(HEAP_MEM_T *hm, alloc_node_t *backing_head){
	
	assert(backing_head != NULL);
	
	for(int i =0; i < hm->n_chunks; i++){

		cgc_size_t offset = hm->ll_md_sz *i;
		// hacky cast to get right offset
		alloc_node_t *a =  (alloc_node_t *)((void *) backing_head + offset);

		cgc_add_node(hm->freelist, a);
	}
}

int cgc_init_backing(HEAP_MEM_T *hm){

	
	hm->freelist = cgc_init_ll();
	hm->inuse = cgc_init_ll();
	hm->backing = cgc_init_ll();
	alloc_node_t *bn = cgc_add_backing_for_chunks(hm);
	if(bn == NULL)
		return ENOMEM;
	alloc_node_t *backing_head = cgc_get_head(hm->backing);
	cgc_add_backing_chunks_to_freelist(hm, backing_head);

	return 0;
}


HEAP_MEM_T * cgc_get_chunk_head_for_sz(cgc_size_t s){
	for(int i = 0; i < MAX_HEADS; i++){
		// cgc_select our chunk
		HEAP_MEM_T * current_heap_head = &(sheap_heap.heads[i]);
		cgc_size_t current_chunk_sz = current_heap_head->chunk_size;

		if(s < current_chunk_sz ){
			// lazy init of chunk head size
			if(current_heap_head->backing == NULL){

				int ret = cgc_init_backing(current_heap_head);
				if(ret != 0)
					cgc__terminate(ret);



				assert(current_heap_head->backing != NULL);
				return current_heap_head;

			}
			else
				return current_heap_head;

		}
	}
	return NULL;
}
void * cgc_max_backing_addr(alloc_node_t *an, HEAP_MEM_T *hh){
	return ((void *) an + hh->backing_sz );
}

alloc_node_t * cgc_get_backing_with_ptr(alloc_node_t *an, HEAP_MEM_T *hh){
	alloc_node_t *bh = cgc_get_head(hh->backing);
	while(bh != NULL){
		if( ((void *) bh <= (void *) an)  && (void *)an <= cgc_max_backing_addr(an, hh)){
			return bh;
		}
		bh = bh->next;
	}
	return NULL;
}

void cgc_mod_refcount_on_backing(alloc_node_t *back_head, HEAP_MEM_T *hh, char direction){
	alloc_node_t *n = back_head;
	while(n != NULL){
		if( (void *) back_head <= (void *) n  && (void * ) n <= cgc_max_backing_addr(back_head, hh)){
			if(direction == -1)
				assert(back_head->refcount != 0);

			back_head->refcount += direction;

			return;
		}
		n = n->next;
	}

}

void * cgc_add_alloc(HEAP_MEM_T *hm, alloc_node_t *nxtmem){
	if(nxtmem == NULL)
		return NULL;
	if(cgc_remove_node(hm->freelist, nxtmem) != OK)
		return NULL;

	if(cgc_add_node(hm->inuse, nxtmem) != OK)
		return NULL;

	void * nn = (void *) nxtmem;
	void * mem = nn + sizeof(alloc_node_t);
	assert(mem-sizeof(alloc_node_t) == (void *) cgc_get_head(hm->inuse));
	return mem;
}




void * cgc_get_next_free_chunk(HEAP_MEM_T *hm){
	alloc_node_t *nxtmem = cgc_get_head(hm->freelist);

	void * a;
	if(nxtmem == NULL){
		
		alloc_node_t *new_backing = cgc_add_backing_for_chunks(hm);
		if(new_backing == NULL)
			return NULL;
		cgc_add_backing_chunks_to_freelist(hm, new_backing);
		nxtmem = cgc_get_head(hm->freelist);

		a =  cgc_add_alloc(hm, nxtmem);
		assert(a != NULL);
		assert(a-sizeof(alloc_node_t) == (void *) cgc_get_head(hm->inuse));

		return a;
	}

	 a = cgc_add_alloc(hm, nxtmem);

	 assert(a-sizeof(alloc_node_t) == (void *) cgc_get_head(hm->inuse));
	 return a;


}

void cgc_malloc_init(){
	int start = 4;
	for(int j = 0; j < MAX_HEADS; j++){
		HEAP_MEM_T *hm = &(sheap_heap.heads[j]);
		hm->chunk_size = (int) cgc_pow(CHUNK_BASE+j, j+start);
		hm->n_chunks = MIN_ELEMENTS;

		if(hm->chunk_size < LAZY_THRESH){
			int r = cgc_init_backing(hm);

			if(r != 0)
				cgc__terminate(ENOMEM);
		}


	}
}





void * cgc_malloc(cgc_size_t s){

	HEAP_MEM_T * heap_head = cgc_get_chunk_head_for_sz(s);
	if(heap_head == NULL)
		return NULL;
	if(cgc_MEM_ALLOC + s > MAX_MEM){
		cgc__terminate(ENOMEM);
	}
	void * r =  cgc_get_next_free_chunk(heap_head);
	if(r != NULL)
		cgc_MEM_ALLOC += heap_head->chunk_size;
	return r;

}


void cgc_free(void *pz){
	HEAP_MEM_T * current_heap_head;
	void *pp = pz - sizeof(alloc_node_t);
	int x;

	for(int i = 0; i <= MAX_HEADS; i++){
		// cgc_select our chunk
		current_heap_head = &(sheap_heap.heads[i]);

		alloc_node_t *bh =  cgc_get_head(current_heap_head->backing);
		// p should be sizeof(alloc_node_t)+alloc_node_t_p so subtract size
		
		int j = 0;
		while(bh != NULL){


			alloc_node_t *have_node = cgc_get_node(current_heap_head->inuse, (alloc_node_t *) pp);
			if(have_node != NULL){

				if(cgc_remove_node(current_heap_head->inuse, have_node) != 0){
					cgc__terminate(15);
				}

				int r = cgc_add_node(current_heap_head->freelist, have_node);
				assert(r == 0);
				cgc_MEM_ALLOC -= current_heap_head->chunk_size;
				return;
			}
		
				

			bh = bh->next;	


		}


		
	}
	cgc__terminate(EFAULT);


}


