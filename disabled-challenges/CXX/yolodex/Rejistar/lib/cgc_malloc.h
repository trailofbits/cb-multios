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
#include "cgc_cbstring.h"

#define setBit(A, k)   ( A[((k)/32)] |=  (1 << ((k)%32)) )
#define clearBit(A, k) ( A[((k)/32)] &= ~(1 << ((k)%32)) )
#define testBit(A, k)  ( A[((k)/32)] &   (1 << ((k)%32)) )

#define _SC_PAGESIZE 4096
#define MAX_RUNS 10
#define BITMAP_SIZE 64
#define POOL_NUM 11

#define ALLOCATE_ERROR 1

typedef struct {
	unsigned int bitmap[64];
	unsigned int size;
	void* memory;
	void* next;
} Run;

typedef struct {
	Run run[MAX_RUNS];
} Pool;

typedef struct {
	cgc_size_t size;
	void* memory;
	void* next;
} LargeChunk;

/**
* Allocate size number of bytes from the heap
* 
* @param size The number of bytes to allocate
*
* @return a pointer the allocated memory
*/
void* cgc_malloc(cgc_size_t size);

/**
* Deallocate the chunk of memory at address ptr
* 
* @param ptr The address of the chunk to deallocate
*
* @return None
*/
void cgc_free(void* ptr);
