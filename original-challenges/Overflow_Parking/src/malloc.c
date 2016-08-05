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

#include <libc.h>

#define ADDHEAP(x) _addchunk(x,&heapl)
#define ADDFREE(x) _addchunk(x,&freel)
//just for readability
#define RMHEAP(x) _rmchunk(x)
#define RMFREE(x) _rmchunk(x)

struct chunk {
   struct chunk *prev;
   struct chunk *next;
   size_t size;
} typedef chunk_t;

char *page;
size_t page_remaining;
chunk_t freel;
chunk_t heapl;

static void _addchunk(chunk_t *c, chunk_t *h) {
    c->prev = h->prev;
    c->next = h;
    h->prev->next = c;
    h->prev = c;
}

static void _rmchunk(chunk_t *c) {
    c->prev->next = c->next;
    c->next->prev = c->prev;
}

void *malloc(size_t s) {
    void *p;
    chunk_t *c = &freel;
    size_t total = s;
    //printf("Alloc @h\n",s);

    if (s == 0) {
        return NULL;
    }

    #ifdef PATCHED_1
    if (total > INT_MAX) {
        return NULL;
    }
    #endif

    //initialize lists if needed
    //we assume both need to be initialized
    if (!freel.next) {
        freel.next = &freel;
        freel.prev = &freel;
        heapl.next = &heapl;
        heapl.prev = &heapl;
    }

    total += sizeof(chunk_t);

    //check free list to see if we have any matches
    do {
        if (c->size >= total) {
            RMFREE(c);
            ADDHEAP(c);
            //printf("Return 2 @h\n",c);
            return (char*)c+sizeof(chunk_t);
        }
        c = c->next;
    } while(c != &freel);

    //check if we have room left
    //
    if (page) {
        if (page_remaining >= total) {
            //we have enough, do it
            c = (chunk_t*)page;
            c->size = total;
            page += total;
            page_remaining -= total;
            ADDHEAP(c);
            //printf("Return 1 @h\n",c);
            return ((char*)c+sizeof(chunk_t));
        } else {
            //we don't have enough for a useful allocation. add remaining to free list
            if (page_remaining > sizeof(chunk_t)) {
                //we add page to free list
                ADDFREE((chunk_t*)page);
                page = NULL;
            } else {
                //we leak mem because it's as useless as I am lazy :-/
                page = NULL;
            }
        }
    }



    //no suitable free chunk
    //we need a new page, and will have returned at this point if we don't
    ALLOCRWX(total,p);

    page = (char *)p + total;
    page = (char *)((uint32_t)page & ~(PAGE_SIZE-1));
    //printf("@h\n",page);
    page_remaining = PAGE_SIZE - ((size_t)((char *)p+total) - (size_t)page);
    page += PAGE_SIZE-page_remaining;

    if (page_remaining <= sizeof(chunk_t))
        page = NULL;

    c = (chunk_t*)p;
    c->size = s;
    ADDHEAP(c);
    //printf("Return 3 @h\n",c);

    return (char*)c + sizeof(chunk_t);
}

void free(void *p) {
    //printf("Free @h\n",((char*)p - sizeof(chunk_t)));
    RMHEAP((chunk_t*)((char*)p - sizeof(chunk_t)));
    ADDFREE((chunk_t*)((char*)p - sizeof(chunk_t)));
}

void *calloc(size_t s) {
    void *p = malloc(s);
    if (!p)
        return NULL;
    memset(p, '\0', s);
    return p;
}
