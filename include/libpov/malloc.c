
#include <libcgc.h>

/*
 * This is a simple heap implementation based solely on allocate
 * It makes no effort to be fast/efficient/any other thing you would want
 *
 * For large blocks (> PAGE_SIZE) allocate is used to satisfy the reqeust
 * Smaller block are allocated on a first fit basis from the small block heap
 * which is structured as a linked list of BLOCKs
 * A block contains a BLOCK_HDR followed by a variable number of CHUNKs
 * All blocks contain a special "end chunk" at the very end of the block
 * whose size is set to -1
 * A CHUNK consists of a CHUNK_HDR followed by a variable sized block of user data
 * A CHUNK_HDR contain prev_size and size fields. A CHUNK is "in use" if the low
 * bit of its size field is set to 1. prev_size is always valid and no user data
 * should ever spill into the prev_size field
 *
 * Allocation of small blocks (< PAGE_SIZE) is slow because it requires a linear
 * search through the small block head so potentially O(n) where n is the number of
 * allocated blocks
 *
 * Deallocation should be O(1)
 */

#define BLOCK_SIZE 0x100000
#define PAGE_SIZE 0x1000
#define PAGE_MASK (PAGE_SIZE-1)

#ifndef NULL
#define NULL ((void*)0)
#endif

void *cgc_memcpy(void *dst, const void *src, cgc_size_t n);
int cgc_allocate(cgc_size_t len, int proti, void **addr);
int cgc_deallocate(void *addr, cgc_size_t len);
void *cgc_memset(void *b, int c, cgc_size_t len);

typedef struct _CHUNK_HDR {
   cgc_size_t prev_size;
   cgc_size_t size;
} CHUNK_HDR;

typedef struct _BLOCK_HDR {
   struct _BLOCK_HDR *next; //pointer to next heap block
   cgc_size_t size;             //size of this block (always BLOCK_SIZE)
} BLOCK_HDR;

static BLOCK_HDR *heap_base = NULL;

static CHUNK_HDR *cgc_get_chunk(void *ptr) {
   return (CHUNK_HDR*)(((char*)ptr) - sizeof(CHUNK_HDR));
}

static cgc_size_t cgc_get_chunk_size(void *ptr) {
   return cgc_get_chunk(ptr)->size;
}

static BLOCK_HDR *cgc_block_init(void) {
   BLOCK_HDR *blk;
   if (cgc_allocate(BLOCK_SIZE, 0, (void**)&blk) == 0) {
      CHUNK_HDR *chk = (CHUNK_HDR *)(blk + 1);
      chk->prev_size = 0;
      chk->size = BLOCK_SIZE - 2 * sizeof(BLOCK_HDR);
      blk->next = NULL;
      blk->size = BLOCK_SIZE;
      chk = (CHUNK_HDR*)(chk->size + (char*)chk);
      chk->prev_size = BLOCK_SIZE - 2 * sizeof(BLOCK_HDR);
      chk->size = (cgc_size_t)-1;
      return blk;
   }
   return NULL;
}

static void cgc_heap_init(void) {
   heap_base = cgc_block_init();
}

/*
 * this is the main allocator, it is awful
 * size is the user requested size to that we add 8 then round to next multiple of 8
 * hint is used for reallocs and suggests that we would like the same block back if possible
 *    some minimal amount of effort is expended to try to make that happen
 * basic algorithm is:
 *   all requests > PAGE_SIZE are allocated using allocate
 *   all other requests are allocated by first fit scan through the heap
 */
static void *cgc_alloc_main(cgc_size_t size, void *hint) {
   if (heap_base == NULL) {
      cgc_heap_init();
   }
   size = (size + 8 + 7) & ~7;
   if (hint != NULL) {
      CHUNK_HDR *c = cgc_get_chunk(hint);
      cgc_size_t csize = c->size & ~7;
      if (csize < PAGE_SIZE && size < PAGE_SIZE) {
         CHUNK_HDR *nc = (CHUNK_HDR*)(csize + (char*)c);
         if (size < csize) {
            //shrinking
            CHUNK_HDR *mc = (CHUNK_HDR*)(size + (char*)c);
            mc->prev_size = size;
            mc->size = csize - size;
            c->size = size | 1;
            nc->prev_size = mc->size;
            return hint;
         }
         else if ((nc->size & 1) == 0) {
            cgc_size_t sz = csize + nc->size;
            if (sz >= size) {
               CHUNK_HDR *c3 = (CHUNK_HDR*)(nc->size + (char*)nc);
               if (size == sz) {
                  c3->prev_size = size;
               }
               else {
                  CHUNK_HDR *mc = (CHUNK_HDR*)(size + (char*)c);
                  mc->prev_size = size;
                  mc->size = sz - size;
                  c3->prev_size = mc->size;
               }
               c->size = size | 1;
               return hint;
            }
         }
      }
      else if (c->size >= PAGE_SIZE && size >= PAGE_SIZE) {
         if (size < c->size) {
            //make no changes to allocation
            return hint;
         }
         //if there is a good way to know whether the following pages are unused then
         //implement something here otherwise fall into code below to map a new block
      }
   }
   //unable to grow existing chunk so allocate a new one
   if (size > PAGE_SIZE) {
      //blocks > PAGE_SIZE are just allocated in
      size = (size + PAGE_MASK) & ~PAGE_MASK;
      CHUNK_HDR *c;
      if (cgc_allocate(size, 0, (void**)&c) == 0) {
         c->prev_size = 0;
         c->size = size;
         return c + 1;
      }
      return NULL;
   }
   //first fit
   BLOCK_HDR *pblk = NULL;
   BLOCK_HDR *blk = heap_base;
   CHUNK_HDR *c = (CHUNK_HDR *)(blk + 1);
   while (blk != NULL) {
      while (c->size != (cgc_size_t)-1) {
         cgc_size_t csize = c->size & ~7;
         CHUNK_HDR *nc = (CHUNK_HDR*)(csize + (char*)c);
         if ((c->size & 1) == 0 && csize >= size) {
            if (csize == size) {
               //perfect fit
               //don't need a new intermediate header
               c->size |= 1;
            }
            else {
               //split block
               CHUNK_HDR *n = (CHUNK_HDR*)(size + (char*)c);
               n->prev_size = size;
               n->size = c->size - size;
               c->size = size | 1;
               nc->prev_size = n->size;
            }
            return c + 1;
         }
         c = (CHUNK_HDR*)(csize + (char*)c);
      }
      pblk = blk;
      blk = blk->next;
      c = (CHUNK_HDR *)(blk + 1);
   }
   //link in a new block
   pblk->next = blk = cgc_block_init();
   c = (CHUNK_HDR *)(blk + 1);
   CHUNK_HDR *pc = (CHUNK_HDR*)(size + (char*)c);
   pc->prev_size = size;
   pc->size = c->size - size;
   c->size = size | 1;         
   return c + 1;
}

void *cgc_malloc(cgc_size_t size) {
   return cgc_alloc_main(size, NULL);
}

/*
 * For allocated chunks, just deallocate
 * For all others, try to consolidate forward and backward
 */
void cgc_free(void *ptr) {
   if (ptr != NULL) {
      CHUNK_HDR *chk = cgc_get_chunk(ptr);
      chk->size &= ~7;
      if (chk->size > PAGE_SIZE) {
         cgc_deallocate(chk, chk->size);
      }
      else {
         //forward consolidation
         CHUNK_HDR *nxt = (CHUNK_HDR*)(chk->size + (char*)chk);
         if ((nxt->size & 1) == 0) {
            chk->size += nxt->size;
         }
         if (chk->prev_size != 0) {
            //backward consolidation
            CHUNK_HDR *prev = (CHUNK_HDR*)(((char*)chk) - chk->prev_size);
            if ((prev->size & 1) == 0) {
               prev->size += chk->size;
            }
         }
      }
   }
}

void *cgc_realloc(void *ptr, cgc_size_t size) {
   void *res = cgc_alloc_main(size, ptr);
   if (ptr != NULL) {
      cgc_size_t chunk_size = cgc_get_chunk_size(ptr);
      if (res != NULL && res != ptr) {
         //block has been moved
         cgc_memcpy(res, ptr, chunk_size - sizeof(CHUNK_HDR));
         cgc_free(ptr);
      }
   }
   return res;
}


