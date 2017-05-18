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
#include "cgc_malloc.h"

static Run* pool[POOL_NUM];
static LargeChunk* largeChunks;

/**
* Get the most significant bit of the value
* 
* @param value The value to get the msb from
*
* @return an integer containing only the most significant bit of the value
*/
unsigned int cgc_getMSB(unsigned int value)
{
	unsigned int mask = 1 << 31;
	for(int i=31; i >=0; i--) {
		if((value & mask) != 0)
			return i;
		mask >>=1;
	}
	return -1;
}

/**
* Set all values in Run to zero
* 
* @param run_ptr The address of the Run
*
* @return None
*/
void cgc_clearRun(Run* run_ptr) {
	run_ptr->size = 0;

	for(int i=0; i<BITMAP_SIZE; i++)
		run_ptr->bitmap[i] = 0;

	run_ptr->memory = 0;
	run_ptr->next = 0;
}

/**
* Initialize the Run
* 
* @param run_ptr The address of the Run
* @param size The number of bytes of chunks provided by the Run
*
* @return 0 if successfull, else the error number returned by allocate
*/
int cgc_initRun(Run** run_ptr, unsigned int size)
{
	int ret;
	if((ret = cgc_allocate(_SC_PAGESIZE, 0, (void**) run_ptr)))
		return ret;
	
	Run* run;
	run = *run_ptr;
	if((ret = cgc_allocate(_SC_PAGESIZE, 0, &run->memory)))
		return ret;

	setBit(run->bitmap, 0);
	run->size = size;
	run->next = NULL;

	return 0;
}

/**
* Get the next free chunk 
* 
* @param size The size of the chunk to allocate
* @param allocated The address to store the address of the allocated chunk
*
* @return 0 if successful, -42 is something went terribly wrong
*/
int cgc_getNextFreeChunk(int size, void** allocated)
{
	int ret=0;
	int chunk_size=0;
	int bitmap_size=0;
	int index;
	Run* run_ptr;

	// Get the next run with free space
	chunk_size = (1 << size);
	bitmap_size = _SC_PAGESIZE/(1 << size);
	for(run_ptr=pool[size-1]; run_ptr != NULL && testBit(run_ptr->bitmap, bitmap_size-1); run_ptr=run_ptr->next) {
		int found=0;
		for(int i=0; i<bitmap_size; i++) {
			if(!testBit(run_ptr->bitmap, i)) {
				found=1;
				break;
			}
		}
		if(found)
			break;
	}

	// If all runs are full
	if(run_ptr == NULL) {
		cgc_initRun(&run_ptr, chunk_size);
		run_ptr->next = pool[size-1];
		pool[size-1] = run_ptr;
		*allocated = run_ptr->memory;
		return 0;
	}

	// Find free space in run
	for(int i=0; i<bitmap_size; i++) {
		if(!testBit(run_ptr->bitmap, i)) {
			char* mem_ptr;
			mem_ptr = (char *)run_ptr->memory;
			*allocated = mem_ptr + i*chunk_size;
			setBit(run_ptr->bitmap,i);
			return 0;
		}
	}


	// Should never get here
	return -42;
}

/**
* Find the Run that contains the specific chunk at addr
* 
* @param addr The address of the chunk
*
* @return The address of the Run containing the chunk
*/
Run* cgc_getRun(void* addr) {

	for(int j=0; j<POOL_NUM; j++) {
		for(Run* run_ptr = pool[j]; run_ptr != NULL; run_ptr=run_ptr->next) {
			if(run_ptr->memory == addr)
				return run_ptr;
		}
	}

	return NULL;
}

/**
* Is the bitmap clear
* 
* @param bitmap A pointer to the bitmap
*
* @return 1 if it is clear, 0 if it is not
*/
int cgc_isClear(unsigned int* bitmap) {
	for(int i = 0; i < 64; i++) {
		if(bitmap[i] != 0)
			return 0;
	}

	return 1;
}

/**
* Allocate size number of bytes from the heap
* 
* @param size The number of bytes to allocate
*
* @return a pointer the allocated memory
*/
void* cgc_malloc(cgc_size_t size) {

	void* allocated=NULL;
	unsigned int msb=0;
	int ret=0;

	// Get pool
	msb = cgc_getMSB(size);

	if(size > (1 << msb) || msb == 0)
		msb+=1;
	if(msb > 11) {
		LargeChunk* lc_ptr;
		for(lc_ptr = largeChunks; lc_ptr != NULL; lc_ptr=lc_ptr->next);
		lc_ptr = (LargeChunk *) cgc_malloc(sizeof(LargeChunk));
		if((ret = cgc_allocate(size, 0, &lc_ptr->memory)))
			return NULL;
		lc_ptr->next = largeChunks;
		largeChunks = lc_ptr;
		lc_ptr->size = size;
		return lc_ptr->memory;
	}

	if((ret = cgc_getNextFreeChunk(msb, &allocated)))
		return NULL;

	return allocated;
}

/**
* Deallocate the chunk of memory at address ptr
* 
* @param ptr The address of the chunk to deallocate
*
* @return None
*/
void cgc_free(void* ptr) {

	Run* run_ptr=NULL, *prev_run_ptr=NULL;
	int bit_index=0;
	int ret=0;
	LargeChunk *lc_ptr=NULL, *prev_ptr=NULL;

	// Check to see if ptr is a large chunk
	if(((unsigned int)ptr & 0xfff) == 0 && largeChunks != NULL) {
		for(lc_ptr = largeChunks; lc_ptr!= NULL && lc_ptr->memory != ptr; prev_ptr=lc_ptr, lc_ptr=lc_ptr->next);
	}
	
	// If ptr is a large chunk
	if (lc_ptr != NULL) {
		if((ret = cgc_deallocate(ptr, lc_ptr->size)))
			cgc__terminate(4);
		lc_ptr->memory = 0;
		lc_ptr->size = 0;
		if(prev_ptr == NULL)
			largeChunks = lc_ptr->next;
		else
			prev_ptr->next = lc_ptr->next;
		cgc_free(lc_ptr);
		return;
	}

	// Find the run the ptr belongs to
	int j;
	for(j=0; j<POOL_NUM; j++) {
		int found=0;
		for(run_ptr = pool[j], prev_run_ptr=NULL; run_ptr != NULL; prev_run_ptr=run_ptr, run_ptr=run_ptr->next) {
			if(run_ptr->memory == ((void *)((unsigned int)ptr & 0xfffff000))) {
				found=1;
				break;
			}
		}
		if(found)
			break;
	}

	// No run found
	if(run_ptr == NULL)
		return;

	// Free and zero chunk
	bit_index = (ptr - run_ptr->memory) / run_ptr->size;
	clearBit(run_ptr->bitmap, bit_index);
	cgc_bzero(ptr, run_ptr->size);

	// Deallocate empty run
	if(cgc_isClear(run_ptr->bitmap)) {
		if(prev_run_ptr == NULL)
			pool[j] = run_ptr->next;
		else
			prev_run_ptr->next = run_ptr->next;
		if((ret = cgc_deallocate(run_ptr->memory, _SC_PAGESIZE)))
			cgc__terminate(4);
		cgc_clearRun(run_ptr);
		if((ret = cgc_deallocate(run_ptr, _SC_PAGESIZE)))
			cgc__terminate(4);
		run_ptr = NULL;

	}


}