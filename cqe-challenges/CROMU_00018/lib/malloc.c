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
#include "stdlib.h"
#include "malloc.h"

#define ALLOC_PAGE_SIZE     (4096)

#define FREE_BLOCK_NEXT( block )    (((tMallocAllocFtr *)((void *)block + (((tMallocAllocHdr *)block)->alloc_size & ~0x3)-sizeof(tMallocAllocHdr)))->pNext)
#define FREE_BLOCK_PREV( block )    (((tMallocAllocFtr *)((void *)block + (((tMallocAllocHdr *)block)->alloc_size & ~0x3)-sizeof(tMallocAllocHdr)))->pPrev)

#define SET_BIT( val, bit ) (val |= (bit))
#define CLEAR_BIT( val, bit ) (val &= ~(bit))
#define IS_BIT_SET( val, bit ) (val & (bit))

tMallocManager g_memManager;

void *calloc( size_t count, size_t obj_size )
{
    size_t allocation_size = (count * obj_size);
    void *pMemBuffer;

    pMemBuffer = malloc( allocation_size );

    memset( pMemBuffer, 0, allocation_size );

    return (pMemBuffer);
}

void *add_free_list( size_t request_size )
{
    // Include header
    size_t grow_size = (request_size + 4);

    // Increases the size of the free list
    if ( grow_size % ALLOC_PAGE_SIZE != 0 )
    {
        grow_size = (grow_size / ALLOC_PAGE_SIZE) + 1;
        grow_size *= ALLOC_PAGE_SIZE;
    }

    void *pAllocLocation;

    if ( allocate( grow_size, 0, &pAllocLocation ) != 0 )
    {
        // Out of memory
        _terminate( -2 );
    }

    // Provision allocation
    tMallocAllocHdr *pNewAllocHdr = (tMallocAllocHdr *)pAllocLocation;
    tMallocAllocFtr *pNewAllocFtr = (tMallocAllocFtr *)(pAllocLocation + (grow_size-sizeof(tMallocAllocFtr)));

    pNewAllocHdr->alloc_size = (grow_size-sizeof(tMallocAllocHdr));

    // Link at front
    pNewAllocFtr->pPrev = NULL;
    pNewAllocFtr->pNext = g_memManager.pFreeList;
    g_memManager.pFreeList = pNewAllocHdr;

    return (void*)pNewAllocHdr;
}

void *malloc( size_t alloc_size )
{
    // Allocate
    if ( alloc_size < 8 )
        alloc_size = 8;
    else if ( alloc_size % 4 != 0 )
    {
        alloc_size = (alloc_size >> 2) + 1;
        alloc_size = (alloc_size << 2);
    }

    // Scan free list for available objects
    void *pFreeCur;

    pFreeCur = g_memManager.pFreeList;

    for (;;)
    {
        if ( pFreeCur == NULL )
        {
            // End of list -- no suitable allocations available
            pFreeCur = add_free_list( alloc_size );
        }

        tMallocAllocHdr *pFreeCurHeader = ((tMallocAllocHdr *)pFreeCur);
        tMallocAllocFtr *pFreeCurFooter = ((tMallocAllocFtr *)(pFreeCur + (pFreeCurHeader->alloc_size & ~0x3)-sizeof(tMallocAllocHdr)));

        // Check for a suitable allocation
        if ( pFreeCurHeader->alloc_size >= alloc_size )
        {
            // Claim this allocation
            void *pClaimAllocation = (pFreeCur + sizeof(tMallocAllocHdr));

            // Split chunk
            size_t size_remaining = pFreeCurHeader->alloc_size - alloc_size;

            // Allocate this chunk and set size...
            pFreeCurHeader->alloc_size = alloc_size;

            // Set it to being inuse
            SET_BIT( pFreeCurHeader->alloc_size, MALLOC_INUSE_FLAG_BIT );

            if ( size_remaining >= (sizeof(tMallocAllocHdr) + sizeof(tMallocAllocFtr)) )
            {
                // Build a new free block
                void *pNewChunk = (pFreeCur + (alloc_size + sizeof(tMallocAllocHdr)));

                tMallocAllocHdr *pNewChunkHeader = ((tMallocAllocHdr *)pNewChunk);
                pNewChunkHeader->alloc_size = (size_remaining - sizeof(tMallocAllocHdr));

                tMallocAllocFtr *pNewChunkFooter = pFreeCurFooter;

                if ( ((void *)pNewChunkHeader + (pNewChunkHeader->alloc_size & ~0x3)-sizeof(tMallocAllocHdr)) != pFreeCurFooter )
                {
                    printf( "Footer != in malloc" );
                    _terminate( -3 );
                }

                // Fix top link (if we need to)
                if ( g_memManager.pFreeList == pFreeCur )
                {
                    g_memManager.pFreeList = (void *)pNewChunkHeader;

                    if ( pNewChunkFooter->pNext )
                        FREE_BLOCK_PREV( pNewChunkFooter->pNext ) = pNewChunkHeader;
                }
                else
                {
                    // Fix up links
                    if ( pNewChunkFooter->pPrev )
                        FREE_BLOCK_NEXT( pNewChunkFooter->pPrev ) = pNewChunk;

                    if ( pNewChunkFooter->pNext )
                        FREE_BLOCK_PREV( pNewChunkFooter->pNext ) = pNewChunk;
                }

                // Mark the object as having a next object (aids in coalescing)
                SET_BIT( pFreeCurHeader->alloc_size, MALLOC_NEXT_FLAG_BIT );
            }
            else
            {
                // Fix link (if we need to)
                if ( g_memManager.pFreeList == pFreeCur )
                {
                    g_memManager.pFreeList = (void *)pFreeCurFooter->pNext;

                    if ( pFreeCurFooter->pNext )
                        FREE_BLOCK_PREV( pFreeCurFooter->pNext ) = NULL;
                }
                else
                {
                    // Link around
                    if ( pFreeCurFooter->pPrev )
                        FREE_BLOCK_NEXT( pFreeCurFooter->pPrev ) = pFreeCurFooter->pNext;

                    if ( pFreeCurFooter->pNext )
                        FREE_BLOCK_PREV( pFreeCurFooter->pNext ) = pFreeCurFooter->pPrev;
                }
            }


            // Clear the allocation
            memset( (void *)(pFreeCur + sizeof(tMallocAllocHdr)), 0, alloc_size );

            // Return the allocated memory
            return (pFreeCur+sizeof(tMallocAllocHdr));
        }

        // Goto NEXT
        pFreeCur = pFreeCurFooter->pNext;
    }
}

void free( void *pItem )
{
    // Free an object and coalesce to neighboring block if available

    // Check neighbor for coalescing
    tMallocAllocHdr *pItemHdr = (tMallocAllocHdr *)(pItem - sizeof(tMallocAllocHdr));

    // Verify inuse bit is set
    if ( !IS_BIT_SET(pItemHdr->alloc_size, MALLOC_INUSE_FLAG_BIT) )
    {
        // Error object cannot be freed (inuse bit is not set)
        _terminate( -2 );
    }

    // Do we have a neighbor??? IF so perform coalescing
    if ( IS_BIT_SET( pItemHdr->alloc_size, MALLOC_NEXT_FLAG_BIT) )
    {
        tMallocAllocHdr *pNeighbor = (pItem + (pItemHdr->alloc_size & ~0x3));

        // Is neighbor inuse? If not -- go ahead and coalesce
        if ( !IS_BIT_SET(pNeighbor->alloc_size, MALLOC_INUSE_FLAG_BIT) )
        {
            // Coalesce!
            size_t coalesceSize = (pItemHdr->alloc_size & ~0x3) + (pNeighbor->alloc_size & ~0x3) + sizeof(tMallocAllocHdr);

            // Set size
            // The inuse bit is cleared here
            pItemHdr->alloc_size = coalesceSize;

            // Set the next flag if the neighbor block has a next flag set
            if ( IS_BIT_SET( pNeighbor->alloc_size, MALLOC_NEXT_FLAG_BIT ) )
                SET_BIT( pItemHdr->alloc_size, MALLOC_NEXT_FLAG_BIT );

            // Relink
            if ( g_memManager.pFreeList == pNeighbor )
            {
                g_memManager.pFreeList = pItemHdr;

                tMallocAllocFtr *pItemFtr = ((tMallocAllocFtr *)((void *)pItemHdr + coalesceSize-sizeof(tMallocAllocHdr)));

                if ( pItemFtr->pNext )
                    FREE_BLOCK_PREV( pItemFtr->pNext ) = pItemHdr;
            }
            else
            {
                tMallocAllocFtr *pItemFtr = ((tMallocAllocFtr *)((void *)pItemHdr + coalesceSize-sizeof(tMallocAllocHdr)));

                // Fix up links
                if ( pItemFtr->pPrev )
                    FREE_BLOCK_NEXT( pItemFtr->pPrev ) = pItemHdr;

                if ( pItemFtr->pNext )
                    FREE_BLOCK_PREV( pItemFtr->pNext ) = pItemHdr;
            }

            // Done
            return;
        }
    }

    // No coalesce possible, just link it to the top of the list
    CLEAR_BIT( pItemHdr->alloc_size, MALLOC_INUSE_FLAG_BIT );

    tMallocAllocFtr *pItemFtr = ((tMallocAllocFtr *)((void *)pItemHdr + (pItemHdr->alloc_size & ~0x3)-sizeof(tMallocAllocHdr)));

    pItemFtr->pNext = g_memManager.pFreeList;
    pItemFtr->pPrev = NULL;

    if ( g_memManager.pFreeList )
        FREE_BLOCK_PREV( g_memManager.pFreeList ) = pItemHdr;

    // Move to top of list
    g_memManager.pFreeList = pItemHdr;

    // Done
    return;
}
