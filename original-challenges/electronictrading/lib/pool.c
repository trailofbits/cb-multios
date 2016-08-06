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
#include "libc.h"

#include "pool.h"

struct freeblk {
    LIST_ELEMS(struct freeblk) list;
};

static int pool_grow(struct pool *pool);

void
pool_init(struct pool *pool, size_t size)
{
    pool->size = MAX(size, sizeof(struct freeblk));
    LIST_INIT(&pool->freelist);
}

int
pool_destroy(struct pool *pool)
{
    int ret = 0;
    struct freeblk *cur = NULL;
    struct freeblk *kill = NULL;

    LIST_OF(struct freeblk) pagelist;

    LIST_INIT(&pagelist);

    LIST_FOR_EACH(&pool->freelist, list, cur)
        if (((uintptr_t)cur & (PAGE_SIZE - 1)) == 0) {
            LIST_REMOVE(&pool->freelist, list, cur);
            LIST_PUSH_FRONT(&pagelist, list, cur);
        }

    // Need to safely traverse and free without use after free
    cur = pagelist.head;
    while (cur != NULL) {
        kill = cur;
        cur = cur->list.next;
        if ((ret = deallocate(kill, PAGE_SIZE)) != 0)
            break;
    }

    return ret;
}

void *
pool_alloc(struct pool *pool)
{
    struct freeblk *ret = NULL;

    if (pool->freelist.head == NULL &&
            pool_grow(pool) != 0)
        return NULL;

    LIST_POP_FRONT(&pool->freelist, list, ret);

    return ret;
}

void
pool_free(struct pool *pool, void *addr)
{
    LIST_ELEMS_INIT(&((struct freeblk *)addr)->list);
    LIST_PUSH_FRONT(&pool->freelist, list, (struct freeblk *)addr);
}

static int
pool_grow(struct pool *pool)
{
    int ret = 0;
    size_t i = 0;
    size_t num_pages = PAGE_SIZE / pool->size;
    struct freeblk *toadd = NULL;
    unsigned char *page = NULL;

    if ((ret = allocate(PAGE_SIZE, 0, (void **)&page)) != 0)
        return ret;

    for (i = 0; i < num_pages; i++) {
        toadd = (struct freeblk *)(page + i * pool->size);
        LIST_PUSH_FRONT(&pool->freelist, list, toadd);
    }

    return ret;
}

