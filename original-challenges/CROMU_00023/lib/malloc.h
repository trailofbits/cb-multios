/*

Author: Jason Williams <jdw@cromulence.com>

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
#ifndef __MALLOC_H__
#define __MALLOC_H__

// In our case the lower 2-bits of the alloc_size are flags
// we enforce minimum allocation sizes of 4-bytes which frees
// up these lower 2-bits as flags
#define MALLOC_INUSE_FLAG_BIT       (1)
#define MALLOC_NEXT_FLAG_BIT        (2)
#define MALLOC_BUCKET_COUNT         (16)

typedef struct MALLOC_ALLOC_HDR
{
    size_t  alloc_size;
} tMallocAllocHdr;

// Only free blocks have these headers (minimum allocation size is therefore 8-bytes)
typedef struct MALLOC_ALLOC_FTR
{
    struct MALLOC_ALLOC_HDR *pNext;
    struct MALLOC_ALLOC_HDR *pPrev;
} tMallocAllocFtr;

typedef struct MALLOC_MANAGER
{
    void *pFreeList;
} tMallocManager;

void* calloc( size_t count, size_t obj_size );
void* malloc( size_t alloc_size );
void free( void *pMem );

#endif // __MALLOC_H__
